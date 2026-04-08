/*------------------------------------------------------------------------------
* estiono.cpp : historical ionosphere-estimation utility placeholder
*
*          Copyright (C) 2012 by T.TAKASU, All rights reserved.
*
* notes   : The upstream estiono.c file was an unfinished experimental draft.
*           It referenced missing state variables and had incomplete control
*           flow, so the C++ migration keeps the command as an explicit
*           unsupported utility instead of silently pretending the draft is a
*           validated algorithm.
*
*           上游 estiono.c 是未完成的实验性草稿，引用了缺失的状态变量且
*           控制流不完整。C++ 迁移版保留该命令入口，但明确标记为暂不支持，
*           避免把未验证算法伪装成可用实现。
*-----------------------------------------------------------------------------*/
#include "rtklib.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    fprintf(stderr,
        "estiono: unsupported historical draft in this C++ migration build\n"
        "estiono: 这是上游未完成的历史草稿，当前 C++ 迁移构建中不作为可用算法发布\n"
        "use geniono or genstec for maintained ionosphere/STEC generation paths\n"
        "请优先使用 geniono 或 genstec 作为当前维护的电离层/STEC 生成路径\n");

    return 2;
}
