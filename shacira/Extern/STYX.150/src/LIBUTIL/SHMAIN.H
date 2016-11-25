/* ------------------------------------------------------------------------- */
/*                                                                           */
/* [shmain.h]      Standard Main Frame for Batch Programms                   */
/*                                                                           */
/* Copyright (c) 1995 by D\olle, Manns.                                      */
/* ------------------------------------------------------------------------- */

#include "standard.h"

#if defined( _MSDOS ) || defined( _WIN32 )
#include <setjmp.h>

static jmp_buf jb;

static void prg_abort()
{
  longjmp(jb,1);
}
#endif

main(int argc, string argv[])
{
#if defined( _MSDOS ) || defined( _WIN32 )
  setErrExitHdl(prg_abort);
  if(setjmp(jb)) return(1);
#ifdef QUICK_WINDOWS
  initStdFiles(stdout,stderr);
#endif
#endif
  program(argc,argv); /* external main function */
  return(0);
}
