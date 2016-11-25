
#ifndef __traceloc__
#define __traceloc__

#define NO_TRACING

#ifdef NO_TRACING

#define MAJOR(m)	(m)
#define MEM_OP						0x0100
#define DEV_OP						0x0200
#define _TRACE_GRAPHIC				MAJOR(100)
  #define _TRACE_SHAPE_ALLOC		(_TRACE_GRAPHIC + 1)
  #define _TRACE_GRAPH_ALLOC		(_TRACE_GRAPHIC + 2)
  #define _TRACE_GRAPH_HEAP 		(_TRACE_GRAPHIC + 3)
  #define _TRACE_SHAPE_CONTROL1		(_TRACE_GRAPHIC + 4)
  #define _TRACE_SHAPE_CONTROL2		(_TRACE_GRAPHIC + 5)
  #define _TRACE_SHAPE_CONTROL3		(_TRACE_GRAPHIC + 6)
  #define _TRACE_SHAPE_CONTROL4		(_TRACE_GRAPHIC + 7)
  #define _TRACE_SHAPE_CONTROL5		(_TRACE_GRAPHIC + 8)
  #define _TRACE_SHAPE_CONTROL6		(_TRACE_GRAPHIC + 9)
  #define _TRACE_SHAPE_CONTROL7		(_TRACE_GRAPHIC + 10)
  #define _TRACE_SHAPE_CONTROL8		(_TRACE_GRAPHIC + 11)
  #define _TRACE_RECT_TEXT_DEV		((_TRACE_GRAPHIC + 0x0010)|DEV_OP)
  #define _TRACE_RECT_TEXT_MEM		((_TRACE_GRAPHIC + 0x0010)|MEM_OP)
  #define _TRACE_RECT_BAR_DEV		((_TRACE_GRAPHIC + 0x0020)|DEV_OP)
  #define _TRACE_RECT_BAR_MEM		((_TRACE_GRAPHIC + 0x0020)|MEM_OP)
  #define _TRACE_RECT_IM_TO_SCR		((_TRACE_GRAPHIC + 0x0030)|DEV_OP|MEM_OP)
  #define _TRACE_RECT_SCR_TO_IM		((_TRACE_GRAPHIC + 0x0040)|DEV_OP|MEM_OP)
  #define _TRACE_RECT_IM_TO_IM		((_TRACE_GRAPHIC + 0x0050)|DEV_OP|MEM_OP)

#define _TRACE_FLAT					MAJOR(200)
  #define _TRACE_FLAT_OPENBIND		(_TRACE_FLAT + 1)
  #define _TRACE_FLAT_OPENALLOC		(_TRACE_FLAT + 2)
  #define _TRACE_FLAT_READADDRESS	(_TRACE_FLAT + 3)
  #define _TRACE_FLAT_READBUFFER	(_TRACE_FLAT + 3)
  #define _TRACE_FLAT_WRITEADDRESS	(_TRACE_FLAT + 3)
  #define _TRACE_FLAT_WRITEBUFFER	(_TRACE_FLAT + 3)
  #define _TRACE_FLAT_ALLOC			(_TRACE_FLAT + 4)
  #define _TRACE_FLAT_BANK			(_TRACE_FLAT + 5)
  #define _TRACE_FLAT_SETADDRESS	(_TRACE_FLAT + 6)
  #define _TRACE_FLAT_SEEK			(_TRACE_FLAT + 7)

#undef  Trace0
#define Trace0(code,severity)
#undef  Trace0b
#define Trace0b(code,severity,nbytes,data)
#undef  Trace1
#define Trace1(code,severity,arg1)
#undef  Trace1b
#define Trace1b(code,severity,arg1,nbytes,data)
#undef  Trace2
#define Trace2(code,severity,arg1,arg2)
#undef  Trace2b
#define Trace2b(code,severity,arg1,arg2,nbytes,data)
#undef  Trace3
#define Trace3(code,severity,arg1,arg2,arg3)
#undef  Trace3b
#define Trace3b(code,severity,arg1,arg2,arg3,nbytes,data)
#undef  Trace4
#define Trace4(code,severity,arg1,arg2,arg3,arg4)
#undef  Trace4b
#define Trace4b(code,severity,arg1,arg2,arg3,arg4,nbytes,data)
#undef  Trace5
#define Trace5(code,severity,arg1,arg2,arg3,arg4,arg5)
#undef  Trace5b
#define Trace5b(code,severity,arg1,arg2,arg3,arg4,arg5,nbytes,data)
#undef  Trace6
#define Trace6(code,severity,arg1,arg2,arg3,arg4,arg5,arg6)
#undef  Trace6b
#define Trace6b(code,severity,arg1,arg2,arg3,arg4,arg5,arg6,nbytes,data)

#else

/*.SI.***********************************************************************/
#if defined(__QNX4__) || defined(__QNXNTO__)
#include <sys/trace.h>
#include <sys/tracecod.h>
#endif
/*.EI.***********************************************************************/

#ifdef __QNXNTO__

#define MAJOR(m)	__M(m)
#define _UNEXP_NONRECOVR_HWERR	_TRACE_HW_SEVERITY3
#define _UNEXP_RECOVR_HWERR		_TRACE_HW_SEVERITY2
#define _EXP_HWERR				_TRACE_HW_SEVERITY1
#define _HWINFO					_TRACE_HW_SEVERITY0
#define _UNEXP_NONRECOVR_SWERR	_TRACE_SW_SEVERITY3
#define _UNEXP_RECOVR_SWERR		_TRACE_SW_SEVERITY2
#define _EXP_SWERR				_TRACE_SW_SEVERITY1
#define _SWINFO					_TRACE_SW_SEVERITY0

#elif defined(__QNX4__)

#define MAJOR(m)	(m << 12)
#define _UNEXP_NONRECOVR_HWERR	_TRACE_CRITICAL
#define _UNEXP_RECOVR_HWERR		_TRACE_SEVERE
#define _EXP_HWERR				_TRACE_EXPECTED
#define _HWINFO					_TRACE_TESTING
#define _UNEXP_NONRECOVR_SWERR	_TRACE_CRITICAL
#define _UNEXP_RECOVR_SWERR		_TRACE_SEVERE
#define _EXP_SWERR				_TRACE_EXPECTED
#define _SWINFO					_TRACE_TESTING

#endif

#define MEM_OP						0x0100
#define DEV_OP						0x0200
#define _TRACE_GRAPHIC				MAJOR(100)
  #define _TRACE_SHAPE_ALLOC		(_TRACE_GRAPHIC + 1)
  #define _TRACE_GRAPH_ALLOC		(_TRACE_GRAPHIC + 2)
  #define _TRACE_GRAPH_HEAP 		(_TRACE_GRAPHIC + 3)
  #define _TRACE_SHAPE_CONTROL1		(_TRACE_GRAPHIC + 4)
  #define _TRACE_SHAPE_CONTROL2		(_TRACE_GRAPHIC + 5)
  #define _TRACE_SHAPE_CONTROL3		(_TRACE_GRAPHIC + 6)
  #define _TRACE_SHAPE_CONTROL4		(_TRACE_GRAPHIC + 7)
  #define _TRACE_SHAPE_CONTROL5		(_TRACE_GRAPHIC + 8)
  #define _TRACE_SHAPE_CONTROL6		(_TRACE_GRAPHIC + 9)
  #define _TRACE_SHAPE_CONTROL7		(_TRACE_GRAPHIC + 10)
  #define _TRACE_SHAPE_CONTROL8		(_TRACE_GRAPHIC + 11)
  #define _TRACE_RECT_TEXT_DEV		((_TRACE_GRAPHIC + 0x0010)|DEV_OP)
  #define _TRACE_RECT_TEXT_MEM		((_TRACE_GRAPHIC + 0x0010)|MEM_OP)
  #define _TRACE_RECT_BAR_DEV		((_TRACE_GRAPHIC + 0x0020)|DEV_OP)
  #define _TRACE_RECT_BAR_MEM		((_TRACE_GRAPHIC + 0x0020)|MEM_OP)
  #define _TRACE_RECT_IM_TO_SCR		((_TRACE_GRAPHIC + 0x0030)|DEV_OP|MEM_OP)
  #define _TRACE_RECT_SCR_TO_IM		((_TRACE_GRAPHIC + 0x0040)|DEV_OP|MEM_OP)
  #define _TRACE_RECT_IM_TO_IM		((_TRACE_GRAPHIC + 0x0050)|DEV_OP|MEM_OP)

#define _TRACE_FLAT					MAJOR(200)
  #define _TRACE_FLAT_OPENBIND		(_TRACE_FLAT + 1)
  #define _TRACE_FLAT_OPENALLOC		(_TRACE_FLAT + 2)
  #define _TRACE_FLAT_READADDRESS	(_TRACE_FLAT + 3)
  #define _TRACE_FLAT_READBUFFER	(_TRACE_FLAT + 3)
  #define _TRACE_FLAT_WRITEADDRESS	(_TRACE_FLAT + 3)
  #define _TRACE_FLAT_WRITEBUFFER	(_TRACE_FLAT + 3)
  #define _TRACE_FLAT_ALLOC			(_TRACE_FLAT + 4)
  #define _TRACE_FLAT_BANK			(_TRACE_FLAT + 5)
  #define _TRACE_FLAT_SETADDRESS	(_TRACE_FLAT + 6)
  #define _TRACE_FLAT_SEEK			(_TRACE_FLAT + 7)


#ifdef TRACE_OFF
#undef  Trace0
#define Trace0(code,severity)
#undef  Trace0b
#define Trace0b(code,severity,nbytes,data)
#undef  Trace1
#define Trace1(code,severity,arg1)
#undef  Trace1b
#define Trace1b(code,severity,arg1,nbytes,data)
#undef  Trace2
#define Trace2(code,severity,arg1,arg2)
#undef  Trace2b
#define Trace2b(code,severity,arg1,arg2,nbytes,data)
#undef  Trace3
#define Trace3(code,severity,arg1,arg2,arg3)
#undef  Trace3b
#define Trace3b(code,severity,arg1,arg2,arg3,nbytes,data)
#undef  Trace4
#define Trace4(code,severity,arg1,arg2,arg3,arg4)
#undef  Trace4b
#define Trace4b(code,severity,arg1,arg2,arg3,arg4,nbytes,data)
#undef  Trace5
#define Trace5(code,severity,arg1,arg2,arg3,arg4,arg5)
#undef  Trace5b
#define Trace5b(code,severity,arg1,arg2,arg3,arg4,arg5,nbytes,data)
#undef  Trace6
#define Trace6(code,severity,arg1,arg2,arg3,arg4,arg5,arg6)
#undef  Trace6b
#define Trace6b(code,severity,arg1,arg2,arg3,arg4,arg5,arg6,nbytes,data)
#endif
#endif

#if defined(__QNX2__) || defined(__WIN32__)
#undef TRACE_OFF
#define TRACE_OFF
#ifdef TRACE_OFF
#define Trace0(code,severity)
#define Trace0b(code,severity,nbytes,data)
#define Trace1(code,severity,arg1)
#define Trace1b(code,severity,arg1,nbytes,data)
#define Trace2(code,severity,arg1,arg2)
#define Trace2b(code,severity,arg1,arg2,nbytes,data)
#define Trace3(code,severity,arg1,arg2,arg3)
#define Trace3b(code,severity,arg1,arg2,arg3,nbytes,data)
#define Trace4(code,severity,arg1,arg2,arg3,arg4)
#define Trace4b(code,severity,arg1,arg2,arg3,arg4,nbytes,data)
#define Trace5(code,severity,arg1,arg2,arg3,arg4,arg5)
#define Trace5b(code,severity,arg1,arg2,arg3,arg4,arg5,nbytes,data)
#define Trace6(code,severity,arg1,arg2,arg3,arg4,arg5,arg6)
#define Trace6b(code,severity,arg1,arg2,arg3,arg4,arg5,arg6,nbytes,data)

#else

/*
 * Trace function prototypes
 */
extern int Trace0(unsigned long code, int severity);
extern int Trace0b(unsigned long code, int severity, int nbytes, void *data);
extern int Trace1(unsigned long code, int severity, int arg1);
extern int Trace1b(unsigned long code, int severity, int arg1, int nbytes, void *data);
extern int Trace2(unsigned long code, int severity, int arg1, int arg2);
extern int Trace2b(unsigned long code, int severity, int arg1, int arg2, int nbytes, void *data);
extern int Trace3(unsigned long code, int severity, int arg1, int arg2, int arg3);
extern int Trace3b(unsigned long code, int severity, int arg1, int arg2, int arg3, int nbytes, void *data);
extern int Trace4(unsigned long code, int severity, int arg1, int arg2, int arg3, int arg4);
extern int Trace4b(unsigned long code, int severity, int arg1, int arg2, int arg3, int arg4, int nbytes, void *data);
extern int Trace5(unsigned long code, int severity, int arg1, int arg2, int arg3, int arg4, int arg5);
extern int Trace5b(unsigned long code, int severity, int arg1, int arg2, int arg3, int arg4, int arg5, int nbytes, void *data);
extern int Trace6(unsigned long code, int severity, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
extern int Trace6b(unsigned long code, int severity, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int nbytes, void *data);

#endif

#endif /* NO_TRACING */

#endif /* __traceloc__ */

