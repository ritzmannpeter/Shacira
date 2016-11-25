/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [sh_ctx.c]               Shellscript context                             */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "stdosx.h"
#include "ctx.h"


int main(int argc, string argv[])
{
  assert0(argc>1,"Usage: sh_ctx command argument ...");
  CTX_init(argc-1, &argv[1]);
  CTX_sh_list();
  CTX_quit();
  BUG_CORE;
  return(0);
}
