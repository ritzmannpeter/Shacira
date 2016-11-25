/*.SH.***********************************************************************
*
* HEADER-DATEI-NAME:
*    IQTTSK.H 
*
* BESCHREIBUNG:
*    ...
*
* UMGEBUNG:
*    ZIELRECHNER:           IQT-450
*    ENTWICKLUNGSRECHNER:   PC-AT/QNX v3.15
*    UEBERSETZER:           c86 v3.3
*    OPTIONEN:              ...
*
* VERSION:
*    VERSION:    4.0                       DATUM:   01.04.92
*    AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*    AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*    AUTOR(EN):  -TS-   T. Schoenig        TELEFON: (0761) 42257
*
* HISTORY:
*    10.03.92 -TS-    Portierung des IQT-350 auf IQT-450
*    08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*    14.07.92 -TS-    Neues Fehlerkonzept
*    29.10.92 -TS-    Makros fuer set_priority() eingefuehrt.
*                      Diese ersetzen cli() und sti(), die nur task-lokal wirken.
*    06.04.93 -PR-    TskGetTaskName entfernt
*    06.07.93 -PR-    Module tskstat und iqttsk in iqttsk integriert
*                     Neue Funktionalitaet zur Protokollierung von Taskzustaenden
*                     und deren Darstellung ergaenzt.
*
*
*
*
*
* BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
* EXPORTSCHNITTSTELLE:
*
* PROTOTYPEN:
*    Keine
*
* DATENTYPEN:
*    Keine
*
*.EH.***********************************************************************/

#ifndef _iqttsk
#define _iqttsk

/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
#ifndef _errcode
#include <errcode.h>
#define _errcode
#endif
#ifndef _debug
#include <debug.h>
#define _debug
#endif
/*.EI.***********************************************************************/

#define FifoInit(mem_type,num,size,init)
#define FifoInitPtr(mem_type,p,num,size,init)
#define FifoFree(ptr)
#define FifoPeek(ptr,entryf,n)
#define FifoChange(ptr,entryf,n)
#define FifoGet(ptr,entryf)
#define FifoPut(ptr,entryf)
#define FifoClear(ptr,n)
#define FLAT_FifoInit(segment,num,size)
#define FLAT_FifoPeek(fifo_addr,entryf,n)
#define FLAT_FifoChange(fifo_addr,entryf,n)
#define FLAT_FifoGet(fifo_addr,entryf)
#define FLAT_FifoPut(fifo_addr,entryf)
#define FLAT_FifoClear(fifo_addr,n)
#define FLAT_FifoLength(fifo_addr)


#define FifoSize(f)
#define FifoLength(f)
#define FifoEmpty(f)
#define FifoFull(f)

#define TskStart(tname,mode,wait,pulse,argv)
#define CmdStart(buffer, node, tty, trans, flags, prio, argv1, argv2)
#define TskStop(tname,base)
#define TskWait(wait)
#define TskSetEvent(ev_ptr)
#define TskWaitEvent(ev_ptr)
#define TskProtoMess(buf)
#define TskCyclWait()

#define SemInit(sema,queue_size)
#define SemInitPtr(sema,queue_size,p)
#define SemFree(sema)
#define SemP(sema)
#define SemV(sema)
#define SemPCount(sema,count)
#define SemVCount(sema,count)

#define MsgPortInit(mport)
#define MsgSend(msg,wait)
#define MsgPeek(mport,flo,fhi)
#define MsgGet(mport,flo,fhi)
#define MsgFetch(mport,flo,fhi)
#define MsgCount(p)
#define MsgReply(m)

#define TskGetFlag(flags)
#define TskSetFlag(flags,val)

#define DiagBufInit(init_bbram)
#define DIAGMSGS      0x80000000L
#define DiagPutMsg(diag,param,tid,mname,l_no)   (DebugPrintf(DIAGMSGS, "diag: %d %08x line %d\n", diag, param, l_no) == 999 ? diag: diag)
#define DiagPeekMsg(diag_msg,n)

#define TIME unsigned long
#define SEMAPHORE int
#define MIN min

#endif /* _iqttsk */









