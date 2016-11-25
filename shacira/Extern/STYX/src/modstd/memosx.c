/* -------------------------------------------------------------------------- */
/*                                                                            */
/* [memosx.c(mem_base)]        Memory Management                              */
/*                                                                            */
/* Copyright (c) 1993 by D\olle, Manns                                        */
/* -------------------------------------------------------------------------- */

#include "sysbase0.h"

#if defined( _MSDOS ) || defined( _WIN32 )
#include <windows.h>
#endif

#define MIN_OBJSIZE	1
/*I------------------------------- Memory ----------------------------------- */

static long obj_count = 0L;

long ObjCount(void)
/* allocated objects */
{
  return obj_count;
}

#ifdef _MSDOS
_NO_DLL_EXPORT_ HugeCPtr NewHMem(long objsize)
/* creates a huge object of size 'objsize'; raises exception */
{ HugeCPtr res = NULL;
  if (objsize < MIN_OBJSIZE) {
    objsize = MIN_OBJSIZE;
  }
  res = _halloc(objsize,1);
  if( res == (StdCPtr)NULL ) 
  { PHDL_FREEMEM hdl_freemem = getFreeMemHdl();
    if( hdl_freemem != (PHDL_FREEMEM)NULL )
    {
      (*hdl_freemem)(objsize);
      res = _halloc(objsize,1);
    }
    if( res == (StdCPtr)NULL ) 
      bug0(False, "halloc failed");
  }
  InterlockedIncrement(&obj_count);
  return res;
}

_NO_DLL_EXPORT_ void FreeHMem(HugeCPtr Any)
/* frees huge object 'Any' */
{
  InterlockedDecrement(&obj_count);
  _hfree(Any);
}
#endif

StdCPtr NewMem(long objsize)
/* creates an object of size 'objsize'; raises exception */
{ StdCPtr res;
  if (objsize < MIN_OBJSIZE) {
    objsize = MIN_OBJSIZE;
  }
#ifdef _MSDOS
  assert1((objsize & 0xffff0000L) == 0,"invalid objsize = %ld",objsize);
#endif
  res = malloc((unsigned int)objsize);
  if( res == (StdCPtr)NULL ) 
  { PHDL_FREEMEM hdl_freemem = getFreeMemHdl();
    if( hdl_freemem != (PHDL_FREEMEM)NULL )
    {
      (*hdl_freemem)(objsize);
      res = malloc((unsigned int)objsize);
    }
    if( res == (StdCPtr)NULL ) 
      bug2(False, "malloc failed for size %ld, res = %ld",objsize,(long)res);
  }
#if defined( _MSDOS ) || defined( _WIN32 )
  InterlockedIncrement(&obj_count);
#else
  ++obj_count;
#endif
  return res;
}

/*DOC_INTERFACE*/
#if !defined(HAVE_CONFIG_H) || defined(HAVE_REALLOC)

StdCPtr ResizeMem(StdCPtr Any, long objsize)
/* resizes an object to size 'objsize'; raises exception */
{ StdCPtr res;
  if (objsize < MIN_OBJSIZE) {
    objsize = MIN_OBJSIZE;
  }
#ifdef _MSDOS
  assert1((objsize & 0xffff0000L) == 0,"invalid objsize = %ld",objsize);
#endif
  res = realloc(Any,(unsigned int)objsize);
  if( objsize > 0 && res == (StdCPtr)NULL ) 
  { PHDL_FREEMEM hdl_freemem = getFreeMemHdl();
    if( hdl_freemem != (PHDL_FREEMEM)NULL )
    {
      (*hdl_freemem)(objsize);
      res = realloc(Any,(unsigned int)objsize);
    }
    if( res == (StdCPtr)NULL ) 
      bug2(False, "realloc failed for size %ld, res = %ld",objsize,(long)res);
  }
  if( objsize == 0 )
  {
#if defined( _MSDOS ) || defined( _WIN32 )
    InterlockedDecrement(&obj_count);
#else
    --obj_count;
#endif
  }
  return res;
}

/*DOC_INTERFACE*/
#endif

void FreeMem(StdCPtr Any)
/* frees object 'Any' */
{
#if defined( _MSDOS ) || defined( _WIN32 )
  InterlockedDecrement(&obj_count);
#else
  --obj_count;
#endif
  free(Any);
}
