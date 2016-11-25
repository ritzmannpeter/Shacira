/* -------------------------------------------------------------------------- */
/*                                                                            */
/* [xmemosx.c(mem_base)]       Memory Management                              */
/*                                                                            */
/* Copyright (c) 1993 by D\olle, Manns                                        */
/* -------------------------------------------------------------------------- */

/* Hinweis. Der Typ 'XMEM_NODE_SIZE' mu\s mit dem Datentyp 'Node' in [xmem] */
/* und der Schnittstelle zum C-Speicherverwalter 'NewMem' in [xstdosx]      */
/* abgestimmt werden.                                                       */

#include "sysbase0.h"

/*I------------------------------- Memory ----------------------------------- */

#include "xmem_imp.h"

static long obj_count = 0L;

long ObjCount(void)
/* allocated objects */
{
  return obj_count;
}

#ifdef _MSDOS
_NO_DLL_EXPORT_ HugeCPtr NewHMem(long objsize)
/* creates a huge object of size 'objsize'; raises exception */
{ byte __HUGE* res = NULL;
  res = (byte __HUGE*)_halloc(objsize,1);
  assert0(res != (byte __HUGE*)NULL, "halloc failed");
  assert0((((long)res)&1)==0, "tagging problems");
  obj_count += 1;
  return (HugeCPtr)res;
}

_NO_DLL_EXPORT_ void FreeHMem(HugeCPtr Any)
/* frees huge object 'Any' */
{
  obj_count -= 1; 
  _hfree((byte __HUGE*)Any);
}
#endif

StdCPtr NewMem(long objsize)
/* creates an object of size 'objsize'; raises exception */
{ byte* res;
  objsize += SizeOf(Node);
#ifdef _MSDOS
  assert1((objsize & 0xffff0000L) == 0,"invalid objsize = %ld",objsize);
#endif
  res = (byte*)malloc((unsigned int)objsize);
  assert1(res != (byte*)NULL, "malloc failed for size %ld",objsize);
  assert0((((long)res)&1)==0, "tagging problems");
  obj_count += 1;
  ((Node)res)->root = XMEM_ROOTVAL_EXTR;
  return (StdCPtr)(res+SizeOf(Node));
}

/*DOC_INTERFACE*/
#if !defined(HAVE_CONFIG_H) || defined(HAVE_REALLOC)

StdCPtr ResizeMem(StdCPtr Any, long objsize)
/* resizes an object to size 'objsize'; raises exception */
{ byte* res;
  objsize += SizeOf(Node);
#ifdef _MSDOS
  assert1((objsize & 0xffff0000L) == 0,"invalid objsize = %ld",objsize);
#endif
  res = realloc(Any,(unsigned int)objsize);
  assert0((((long)res)&1)==0, "tagging problems");
  if( objsize == 0 )
  {
#if defined( _MSDOS ) || defined( _WIN32 )
    InterlockedDecrement(&obj_count);
#else
    --obj_count;
#endif
  }
  return (StdCPtr)(res+SizeOf(Node));
}

/*DOC_INTERFACE*/
#endif

void FreeMem(StdCPtr Any)
/* frees object 'Any' */
{
  obj_count -= 1; free(((byte*)Any)-SizeOf(Node));
}
