// ===========================================================================
// base/driver/mn_queue.cpp                                     ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// 
// ===========================================================================


// Interface header
#include "base/driver/mn_queue.h"

// Platform dependant header
#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
   #include <process.h>
#endif




namespace ecl {




// Konstanten der Masken fuer __ECL_ASSERT__ etc.
const unsigned long IPC_ERROR = cBase::dbgError | cBase::dbgIpc;
const unsigned long IPC_WARN  = cBase::dbgWarn  | cBase::dbgIpc;

#if defined __ECL_OS2__

   /**************************************************************************\
   *                                                                         *
   *                     A N P A S S U N G E N   O S / 2                     *
   *                                                                         *
   \**************************************************************************/

   #define SHARED_MEM_NAME "\\SHAREMEM\\ECL\\QUEUES"
   #define SHARED_MEM_SIZE 0x10000

   class cOS2SharedMemory : public cBase {
      void *shared_mem;
   public:
      cOS2SharedMemory()
      {
         // Hier nur Grundinitialisierung. Eigentliche Anforderung in getPtr,
         // damit Allokation des Shared Memorys nur wenn benoetigt
         shared_mem = 0;
      }
      ~cOS2SharedMemory()
      {
         // Shared Memory freigeben
         if ( shared_mem != NULLHANDLE ) {
            DosSubUnsetMem(shared_mem);
            DosFreeMem(shared_mem);
         }
      }
      void init()
      {
         getPtr();
      }
      void *alloc(unsigned long size)
      {
         void *mem;
         APIRET rc = DosSubAllocMem(getPtr(), &mem, size);
         if ( rc ) {
            cBase::DbgError("OS/2: Could not suballocate memory, rc=%d\n", rc);
            return 0;
         }
         return mem;
      }
      void free(void *mem, unsigned long size)
      {
         APIRET rc = DosSubFreeMem(getPtr(), mem, size);
         if ( rc ) cBase::DbgError("OS/2: DosSubFreeMem returned %d\n", rc);
      }
   private:
      void *getPtr()
      {
         if ( shared_mem == 0 ) {
            APIRET rc;
            // Shared Memory oeffnen, falls noch nicht geschehen
            if ( 0 == (rc = DosGetNamedSharedMem(&shared_mem, SHARED_MEM_NAME, PAG_READ|PAG_WRITE)) ) {
               if ( 0 != (rc = DosSubSetMem(shared_mem, DOSSUB_SERIALIZE, SHARED_MEM_SIZE)) )
                  cBase::DbgError("OS/2: Could not attach to Shared Mem, rc=%d\n", rc);
            } else if ( 0 == (rc = DosAllocSharedMem(&shared_mem, SHARED_MEM_NAME, SHARED_MEM_SIZE, PAG_COMMIT|PAG_WRITE|PAG_READ)) ) {
               if ( 0 != (rc = DosSubSetMem(shared_mem, DOSSUB_INIT | DOSSUB_SERIALIZE, SHARED_MEM_SIZE)) )
                  cBase::DbgError("OS/2: Could not setup Shared Mem, rc=%d\n", rc);
            } else if ( rc ) {
               cBase::DbgError("OS/2: Could not allocate Shared Mem, rc=%d\n", rc);
            }
         }
         return shared_mem;
      }
   };

   static cOS2SharedMemory SharedMem;

#endif // __ECL_OS2__
   



// Implementierung cMsgNodeQUEUE
// ===========================================================================

cMsgNodeQUEUE::cMsgNodeQUEUE(cString name, int send_mode) :
   cMsgNode(name, send_mode)
{
   __ECL_STATISTIC__("cMsgNodeQUEUE")
   write_queue = read_queue = sync_sema = 0;
}

bool cMsgNodeQUEUE::ping()
{
   __ECL_RELEASE_TEXT__(IPC_ERROR, "cMsgBox::ping() not implemented for Queues");
   return true;
}

void cMsgNodeQUEUE::createChannel(int msg_count, int msg_size)
{
   #ifdef __ECL_OS2__
      APIRET rc;
      if ( (rc = DosCreateEventSem(0, &sync_sema, 0, FALSE)) != NO_ERROR ) {
         cBase::DbgError("OS/2: could not create event semaphore, rc = %d", rc);
         throw cErrMsg(cErrMsg::errCreateChannel, getFullName());
      }
      if ( (rc = DosCreateQueue(&read_queue, QUE_FIFO, getFullName())) != NO_ERROR ) {
         cBase::DbgError("OS/2: could not create message queue '%s', rc = %d", (const char *)getFullName(), rc);
         DosCloseEventSem(sync_sema);
         throw cErrMsg(cErrMsg::errCreateChannel, getFullName());
      }
   #else
      msg_count = msg_count;
      msg_size = msg_size;
      throw cErrMsg(cErrMsg::errUnsupportedProtocol, getFullName());
   #endif
}

void cMsgNodeQUEUE::closeChannel()
{
   #ifdef __ECL_OS2__
      if ( sync_sema ) DosCloseEventSem(sync_sema);
      if ( read_queue ) DosCloseQueue(read_queue);
   #endif
   
   sync_sema = read_queue = 0;
}

void cMsgNodeQUEUE::connectToChannel()
{
   #ifdef __ECL_OS2__
      PID pid = 0;
      APIRET rc;
      if ( write_queue != 0 ) {
         // Testen, ob die Verbindung noch steht
         ULONG dummy;
         if ( 0 != (rc = DosQueryQueue(write_queue, &dummy)) ) {
            /* DosCloseQueue( qd->que ); *???*/
            /* cBase::DbgError("OS/2: DosQueryQueue returned %d\n", rc); */
            cBase::DbgError("OS/2: Queue '%s' died, retrying\n", (const char *)getFullName());
            write_queue = 0;
         }
      }
      if ( write_queue == 0 && 0 != (rc = DosOpenQueue(&pid, &write_queue, getFullName())) ) {
         cBase::DbgError("OS/2: DosOpenQueue returned %d\n", rc);
         throw cErrMsg(cErrMsg::errOpenChannel, getFullName());
      }
   #endif
}

void cMsgNodeQUEUE::disconnectFromChannel()
{
   if ( write_queue != 0 ) {
      #ifdef __ECL_OS2__
         DosCloseQueue(write_queue);
      #endif
      write_queue = 0;
   }
}

cString cMsgNodeQUEUE::getFullName() const
{
   return "\\queues\\ecl\\" + getName();
}

void cMsgNodeQUEUE::sendMsg(cMsg msg)
{
   int size = getMsgLen(msg);

   disconnectFromChannel();
   connectToChannel();

   #ifdef __ECL_OS2__
      void *mem;

      if ( (mem = SharedMem.alloc(size)) == 0 )
         throw cErrMsg(cErrMsg::errSendToChannel, getFullName());
      memcpy(mem, getMsg(msg), size);

      APIRET rc;
      if ( 0 != (rc = DosWriteQueue(write_queue, 0, size, (PVOID)mem, 0)) ) {
         cBase::DbgError("OS/2: DosWriteQueue returned %d\n", rc);
         throw cErrMsg(cErrMsg::errSendToChannel, getFullName());
      }
   #else
      size = size;
   #endif
}

cMsg cMsgNodeQUEUE::callMsg(cMsg msg, int /*timeout*/)
{
   __ECL_RELEASE_TEXT__(IPC_WARN, "OS/2: Warning: Ignoring cMsgRecipient::call() for Queues");
   return cMsg();
}

cMsg cMsgNodeQUEUE::receiveMsg()
{
   #ifdef __ECL_OS2__
   
      ULONG size;
      BYTE prio;
      void *mem = 0;
      REQUESTDATA request = { _getpid(), 0 };
      ULONG wait = getWait() ? DCWW_WAIT : DCWW_NOWAIT;
   
      APIRET rc = DosReadQueue(read_queue, &request, &size, (PPVOID)&mem, 0, wait, &prio, sync_sema);
   
      if ( rc != NO_ERROR ) {
         if ( rc == ERROR_QUE_EMPTY ) {
            // Legaler Zustand: Keine Meldung vorhanden
            return cMsg();
         } else {
            cBase::DbgError("OS/2: DosReadQueue failed, rc = %d", rc);
            throw cErrMsg(cErrMsg::errReceiveFromChannel, getFullName());
         }
      } else {
         SharedMem.init();
         cMsg msg = newMsg(mem);
         if ( !msg.isValid() ) {
            cBase::DbgError("OS/2: Received an invalid memory block");
            throw cErrMsg(cErrMsg::errInvalidMsg, getFullName());
         } else {
            SharedMem.free(mem, size);
            return msg;
         }
      }

   #else
   
      return cMsg();

   #endif
}

bool cMsgNodeQUEUE::mustReplyMsg(const cMsg& /*msg_to_reply*/)
{
   return false;
}

void cMsgNodeQUEUE::replyMsg(const cMsg& /*msg_to_reply*/, cMsg reply_msg)
{
   __ECL_RELEASE_TEXT__(IPC_WARN, "OS/2: Warning: Ignoring cMsgBox::reply() for Queues");
}




}; // namespace ecl

