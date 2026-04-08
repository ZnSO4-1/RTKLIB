/*-----------------------------------------------------------------------------
* margelog.cpp : merge RTKLIB log and tag files
*
* notes : This utility was incomplete in the imported tree. The implementation
*         below keeps the original intent: concatenate binary log files and
*         rewrite their companion .tag offsets into the merged output.
*         该工具在导入的源码树中不完整；这里按原意合并日志及 .tag 偏移。
*-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rtklib.h"

#define HEADLEN 76
#define TAGLEN   8

/* read unsigned 32-bit little-endian value ----------------------------------*/
static unsigned int get_u32(const unsigned char *p)
{
    return ((unsigned int)p[0])|((unsigned int)p[1]<<8)|
           ((unsigned int)p[2]<<16)|((unsigned int)p[3]<<24);
}
/* write unsigned 32-bit little-endian value ---------------------------------*/
static void set_u32(unsigned char *p, unsigned int v)
{
    p[0]=(unsigned char)( v     &0xFF);
    p[1]=(unsigned char)((v>> 8)&0xFF);
    p[2]=(unsigned char)((v>>16)&0xFF);
    p[3]=(unsigned char)((v>>24)&0xFF);
}
/* copy bytes ----------------------------------------------------------------*/
static int copy_bytes(FILE *ifp, FILE *ofp, unsigned int len)
{
    unsigned char buff[4096];
    size_t n;

    while (len>0) {
        n=len<sizeof(buff)?len:sizeof(buff);
        if (fread(buff,1,n,ifp)!=n) return 0;
        if (fwrite(buff,1,n,ofp)!=n) return 0;
        len-=(unsigned int)n;
    }
    return 1;
}
/* print usage ---------------------------------------------------------------*/
static void usage(void)
{
    fprintf(stderr,"usage: margelog [-o outfile] infile ...\n");
}
/* main ----------------------------------------------------------------------*/
int main(int argc, char **argv)
{
    FILE *ifp=NULL,*itagfp=NULL,*ofp=NULL,*otagfp=NULL;
    char *ifiles[32],*ofile=(char *)"merged.log";
    char itagfile[1024],otagfile[1024];
    unsigned char head[HEADLEN],tag[TAGLEN],outtag[TAGLEN];
    unsigned int tick0=0,tick1,tick,fpos,lastpos,outpos=0,len;
    int i,n=0,stat=-1;

    for (i=1;i<argc;i++) {
        if (!strcmp(argv[i],"-o")&&i+1<argc) ofile=argv[++i];
        else if (n<(int)(sizeof(ifiles)/sizeof(ifiles[0]))) ifiles[n++]=argv[i];
    }
    if (n<=0) {
        usage();
        return -1;
    }
    sprintf(otagfile,"%s.tag",ofile);

    if (!(ofp=fopen(ofile,"wb"))||!(otagfp=fopen(otagfile,"wb"))) {
        fprintf(stderr,"out file open error: %s\n",ofile);
        goto cleanup;
    }
    for (i=0;i<n;i++) {
        sprintf(itagfile,"%s.tag",ifiles[i]);

        if (!(ifp=fopen(ifiles[i],"rb"))||!(itagfp=fopen(itagfile,"rb"))) {
            fprintf(stderr,"in file open error: %s\n",ifiles[i]);
            goto cleanup;
        }
        if (fread(head,1,HEADLEN,itagfp)!=HEADLEN) {
            fprintf(stderr,"in tag file read error: %s\n",itagfile);
            goto cleanup;
        }
        tick1=get_u32(head+60);
        if (i==0) {
            tick0=tick1;
            if (fwrite(head,1,HEADLEN,otagfp)!=HEADLEN) {
                fprintf(stderr,"out tag file write error: %s\n",otagfile);
                goto cleanup;
            }
        }
        lastpos=0;
        while (fread(tag,1,TAGLEN,itagfp)==TAGLEN) {
            tick=get_u32(tag);
            fpos=get_u32(tag+4);
            if (fpos<lastpos) {
                fprintf(stderr,"invalid tag offset: %s\n",itagfile);
                goto cleanup;
            }
            len=fpos-lastpos;
            if (!copy_bytes(ifp,ofp,len)) {
                fprintf(stderr,"log copy error: %s\n",ifiles[i]);
                goto cleanup;
            }
            set_u32(outtag,tick1+tick-tick0);
            set_u32(outtag+4,outpos+len);
            if (fwrite(outtag,1,TAGLEN,otagfp)!=TAGLEN) {
                fprintf(stderr,"out tag file write error: %s\n",otagfile);
                goto cleanup;
            }
            lastpos=fpos;
            outpos+=len;
        }
        while ((len=(unsigned int)fread(head,1,sizeof(head),ifp))>0) {
            if (fwrite(head,1,len,ofp)!=len) {
                fprintf(stderr,"log copy error: %s\n",ifiles[i]);
                goto cleanup;
            }
            outpos+=len;
        }
        fclose(ifp); ifp=NULL;
        fclose(itagfp); itagfp=NULL;
    }
    stat=0;

cleanup:
    if (ifp) fclose(ifp);
    if (itagfp) fclose(itagfp);
    if (ofp) fclose(ofp);
    if (otagfp) fclose(otagfp);
    return stat;
}
