/*----------------------------------------------------------------------------*/
/*                                                                            */
/* [prjfun.h]       PRDPS: Types of collection functions                      */
/*                                                                            */
/* Copyright (c) 1993 by Doelle, Manns                                        */
/*----------------------------------------------------------------------------*/

#ifndef PRJFUN_INCL
#define PRJFUN_INCL

#include "standard.h"

// adds dependency 
typedef void (*PFN_AddDep)(StdCPtr pBag, c_string szDepFile);

// adds rule, i.e. project group 
typedef void (*PFN_AddGrp)(StdCPtr pGBag, StdCPtr* ppTBag, StdCPtr* ppSBag);
// adds target to current rule
typedef void (*PFN_AddDst)
             (StdCPtr pTBag, c_string szDstFile, c_string szDstPath);
// adds source to current rule
typedef void (*PFN_AddSrc)(StdCPtr pSBag, c_string szSrcFile);

#endif //_INCL
