/*------------------------------------------------------------------------------
* stec.cpp : slant TEC correction reader and interpolator
*
*          Copyright (C) 2012 by T.TAKASU, All rights reserved.
*
* notes   : This downstream C++ migration restores the STEC implementation that
*           is declared by rtklib.h but missing from the imported source tree.
*           本下游 C++ 迁移补回 rtklib.h 中已声明但源码树缺失的 STEC 实现。
*-----------------------------------------------------------------------------*/
#include "rtklib.h"

#define SPOS_RID "$SPOS"
#define STEC_RID "$STEC"
#define MAXDTOUT 3600.0
#define SQR(x) ((x)*(x))

/* append stec grid ----------------------------------------------------------*/
static stec_t *add_grid(nav_t *nav, double lat, double lon)
{
    stec_t *p;

    if (nav->nn>=nav->nnmax) {
        nav->nnmax+=16;
        p=(stec_t *)realloc(nav->stec,sizeof(stec_t)*nav->nnmax);
        if (!p) {
            free(nav->stec); nav->stec=NULL; nav->nn=nav->nnmax=0;
            return NULL;
        }
        nav->stec=p;
    }
    p=nav->stec+nav->nn++;
    memset(p,0,sizeof(*p));
    p->pos[0]=lat;
    p->pos[1]=lon;
    return p;
}
/* append stec data ----------------------------------------------------------*/
static int add_data(stec_t *stec, const stecd_t *data)
{
    stecd_t *p;

    if (stec->n>=stec->nmax) {
        stec->nmax+=1024;
        p=(stecd_t *)realloc(stec->data,sizeof(stecd_t)*stec->nmax);
        if (!p) {
            free(stec->data); stec->data=NULL; stec->n=stec->nmax=0;
            return 0;
        }
        stec->data=p;
    }
    stec->data[stec->n++]=*data;
    return 1;
}
/* compare stec data ---------------------------------------------------------*/
static int cmp_stec_data(const void *p1, const void *p2)
{
    const stecd_t *q1=(const stecd_t *)p1,*q2=(const stecd_t *)p2;
    double tt=timediff(q1->time,q2->time);

    if (q1->sat!=q2->sat) return (int)q1->sat-(int)q2->sat;
    if (tt<-1E-9) return -1;
    if (tt> 1E-9) return  1;
    return 0;
}
/* read stec corrections -----------------------------------------------------*/
extern void stec_read(const char *file, nav_t *nav)
{
    FILE *fp;
    stec_t *grid=NULL;
    stecd_t data={0};
    char buff[1024],rid[32],satid[16];
    double tow,lat,lon,iono,rate,rms;
    int week,slip,sat,i;

    if (!file||!*file||!nav) return;
    if (!(fp=fopen(file,"r"))) return;

    while (fgets(buff,sizeof(buff),fp)) {
        if (sscanf(buff,"%31s",rid)<1) continue;
        if (!strcmp(rid,SPOS_RID)) {
            if (sscanf(buff,"%*s %d %lf %lf %lf",&week,&tow,&lat,&lon)>=4) {
                grid=add_grid(nav,lat,lon);
            }
        }
        else if (!strcmp(rid,STEC_RID)&&grid) {
            if (sscanf(buff,"%*s %d %lf %15s %d %lf %lf %lf",
                       &week,&tow,satid,&slip,&iono,&rate,&rms)<7) {
                continue;
            }
            if (!(sat=satid2no(satid))) continue;
            data.time=gpst2time(week,tow);
            data.sat=(unsigned char)sat;
            data.slip=(unsigned char)slip;
            data.iono=(float)iono;
            data.rate=(float)rate;
            data.rms=(float)rms;
            if (!add_data(grid,&data)) break;
        }
    }
    fclose(fp);

    for (i=0;i<nav->nn;i++) {
        if (nav->stec[i].n>1) {
            qsort(nav->stec[i].data,nav->stec[i].n,sizeof(stecd_t),cmp_stec_data);
        }
        memset(nav->stec[i].index,0,sizeof(nav->stec[i].index));
    }
}
/* search nearby stec grids --------------------------------------------------*/
extern int stec_grid(const nav_t *nav, const double *pos, int nmax, int *index,
                     double *dist)
{
    double lat=pos[0]*R2D,lon=pos[1]*R2D,d;
    int i,j,n=0;

    if (!nav||!pos||!index||!dist||nmax<=0) return 0;

    for (i=0;i<nav->nn;i++) {
        d=SQR(lat-nav->stec[i].pos[0])+SQR(lon-nav->stec[i].pos[1]);
        for (j=n;j>0&&dist[j-1]>d;j--) {
            if (j<nmax) {
                dist[j]=dist[j-1];
                index[j]=index[j-1];
            }
        }
        if (j<nmax) {
            dist[j]=d;
            index[j]=i;
            if (n<nmax) n++;
        }
    }
    for (i=0;i<n;i++) dist[i]=sqrt(dist[i]);
    return n;
}
/* get interpolated stec data ------------------------------------------------*/
extern int stec_data(stec_t *stec, gtime_t time, int sat, double *iono,
                     double *rate, double *rms, int *slip)
{
    stecd_t *p,*q;
    double tt,dt,dtq;
    int i;

    if (!stec||!iono||!rate||!rms||!slip||sat<=0) return 0;

    i=stec->index[sat-1];
    if (i<0||i>=stec->n||stec->data[i].sat!=sat) i=0;

    for (;i<stec->n&&stec->data[i].sat<sat;i++) ;
    for (;i<stec->n&&stec->data[i].sat==sat;i++) {
        p=stec->data+i;
        tt=timediff(time,p->time);
        if (fabs(tt)<=1E-9) {
            *iono=p->iono;
            *rate=p->rate;
            *rms=p->rms;
            *slip=p->slip;
            stec->index[sat-1]=i;
            return 1;
        }
        if (tt<0.0) {
            if (i==0||stec->data[i-1].sat!=sat) return fabs(tt)<=MAXDTOUT?0:0;
            q=stec->data+i-1;
            dt=timediff(p->time,q->time);
            dtq=timediff(time,q->time);
            if (dt<=0.0||dtq<-MAXDTOUT||tt<-MAXDTOUT) return 0;
            *iono=q->iono+(p->iono-q->iono)*dtq/dt;
            *rate=q->rate+(p->rate-q->rate)*dtq/dt;
            *rms =q->rms +(p->rms -q->rms )*dtq/dt;
            *slip=q->slip||p->slip;
            stec->index[sat-1]=i-1;
            return 1;
        }
    }
    if (i>0&&stec->data[i-1].sat==sat&&timediff(time,stec->data[i-1].time)<=MAXDTOUT) {
        p=stec->data+i-1;
        *iono=p->iono+p->rate*timediff(time,p->time);
        *rate=p->rate;
        *rms=p->rms;
        *slip=p->slip;
        stec->index[sat-1]=i-1;
        return 1;
    }
    return 0;
}
/* interpolate stec correction ----------------------------------------------*/
extern int stec_ion(gtime_t time, const nav_t *nav, int sat, const double *pos,
                    const double *azel, double *iono, double *rate, double *var,
                    int *brk)
{
    double dist[8],ion=0.0,rat=0.0,rms=0.0,w,sum=0.0,iono_i,rate_i,rms_i;
    int index[8],slip_i,i,n,slip=0;

    (void)azel;

    if (!nav||!pos||!iono||!rate||!var||!brk) return 0;
    if ((n=stec_grid(nav,pos,8,index,dist))<=0) return 0;

    for (i=0;i<n;i++) {
        if (!stec_data(nav->stec+index[i],time,sat,&iono_i,&rate_i,&rms_i,
                       &slip_i)) {
            continue;
        }
        w=dist[i]<=1E-9?1E12:1.0/SQR(dist[i]);
        ion+=w*iono_i;
        rat+=w*rate_i;
        rms+=w*rms_i;
        slip|=slip_i;
        sum+=w;
        if (w>1E11) break;
    }
    if (sum<=0.0) return 0;
    *iono=ion/sum;
    *rate=rat/sum;
    rms/=sum;
    *var=SQR(rms);
    *brk=slip;
    return 1;
}
/* free stec data ------------------------------------------------------------*/
extern void stec_free(nav_t *nav)
{
    int i;

    if (!nav) return;
    for (i=0;i<nav->nn;i++) free(nav->stec[i].data);
    free(nav->stec);
    nav->stec=NULL;
    nav->nn=nav->nnmax=0;
}
