// ===========================================================================
// eb_msg.cpp                                                   ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cMsg                 - Meldung.
//     |
//     +-cMsgRecipient        - Adressat (zum Senden von Meldungen).
//        |
//        +-cMsgBox           - Briefkasten (zum Empfangen von Meldungen).
//
// Das Grundgeruest eines Threads, der diese Klassen benutzt, sieht etwa
// folgendermassen aus:
//
//    cMsgBox msg_box("my_name");
//
//    while ( true ) {
//       cMsg msg = msg_box.receive();
//
//       // Meldung bearbeiten:
//       switch ( msg.getMsgId() ) {
//          ...
//       }
//
//       // Meldung weiterschicken:
//       if ( send_it_to_other ) {
//          cMsgRecipient other("other_name");
//          other.send(msg);
//       }
//
//       // Meldung beantworten?
//       if ( msg_box.mustReply(msg) ) {
//          msg_box.reply(msg, cMsg(MY_MSG_ID, "OK"));
//       }
//
//       // Meldung an sich selbst schicken
//       msg_box.send(cMsg(MY_MSG_ID, "msg"));
//    }
//
// Die Namen der Teilnehmer bestehen aus bis zu 3 Teilen:
//
//    (1) Art der verwendeten Protokolls
//    (2) Adresse (=Rechnername) des Teilnehmers (nur bei cMsgRecipient)
//    (3) Name des Teilnehmers
//
// Moegliche Protokolle sind:
//
//     Protokoll  | Beschreibung    | Call | T->T | P->P | Netz | OS/2 | W32
//    ------------+-----------------+------+------+------+------+------+------
//     :private:  | Anonyme Queues  |  Ja  |  Ja  | Nein | Nein |  Ja  |  Ja
//     :local:    | Benannte Queues |  Ja  |  Ja  |  Ja  | Nein |  Ja  |  Ja
//     :queue:    | Systemqueues    | Nein |  Ja  |  Ja  | Nein |  Ja  | Nein
//     :mslot:    | Mailslots       | Nein |  Ja  |  Ja  |  Ja  | Nein |  Ja
//     :npipe:    | Named Pipes     | (Ja) |  Ja  |  Ja  |  Ja  |  Ja  |  Ja
//                                     |      |      |      |      |      |
//                  Reply moeglich? <--+      |      |      |      |      |
//         Intraprozess (Thread zu Thread) <--+      |      |      |      |
//          Interprozess (von Prozess zu Prozess) <--+      |      |      |
//                Von Maschine zu Maschine (im Netzwerk) <--+      |      |
//                                           Laeuft unter OS/2? <--+      |
//                                                 Laeuft unter Win32? <--+
//
// Beispiele fuer den Teilnehmer "MyName":
//
//     Teilnehmername:      | Protokoll:  | Rechner:
//    ----------------------+-------------+-------------
//     MyName               | Lokal       | .
//     :npipe:MyName        | Named Pipes | .
//     mac42:MyName         | Lokal       | mac42
//     :mslot:mac42:MyName  | Mail Slots  | mac42
//
// Ausserdem ist es moeglich, anonyme cMsgBox-Objekte anzulegen. Diese
// koennen jedoch nur zur Intra-Prozesskommunikation verwendet werden.
//
// ===========================================================================

#include "base/eb_msg.hpp"
#include "base/eb_thread.hpp"
#include "base/eb_bprintf.hpp"

#include <stdlib.h>
#include <memory.h>

//#define __Use_Named_Pipes__ /* Definieren, wenn Named Pipes gewuenscht */

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
   #include <process.h>
#elif defined __ECL_W32__
   #include <windows.h>
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include <stdarg.h>
#include "base/eb_err.hpp"
#include "base/eb_str.hpp"

class cMsgNode;

#endif /*__INTERFACE__*/




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
         shared_mem = NULL;
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
            DbgError("OS/2: Could not suballocate memory, rc=%d\n", rc);
            return NULL;
         }
         return mem;
      }
      void free(void *mem, unsigned long size)
      {
         APIRET rc = DosSubFreeMem(getPtr(), mem, size);
         if ( rc ) DbgError("OS/2: DosSubFreeMem returned %d\n", rc);
      }
   private:
      void *getPtr()
      {
         if ( shared_mem == NULL ) {
            APIRET rc;
            // Shared Memory oeffnen, falls noch nicht geschehen
            if ( 0 == (rc = DosGetNamedSharedMem(&shared_mem, SHARED_MEM_NAME, PAG_READ|PAG_WRITE)) ) {
               if ( 0 != (rc = DosSubSetMem(shared_mem, DOSSUB_SERIALIZE, SHARED_MEM_SIZE)) )
                  DbgError("OS/2: Could not attach to Shared Mem, rc=%d\n", rc);
            } else if ( 0 == (rc = DosAllocSharedMem(&shared_mem, SHARED_MEM_NAME, SHARED_MEM_SIZE, PAG_COMMIT|PAG_WRITE|PAG_READ)) ) {
               if ( 0 != (rc = DosSubSetMem(shared_mem, DOSSUB_INIT | DOSSUB_SERIALIZE, SHARED_MEM_SIZE)) )
                  DbgError("OS/2: Could not setup Shared Mem, rc=%d\n", rc);
            } else if ( rc ) {
               DbgError("OS/2: Could not allocate Shared Mem, rc=%d\n", rc);
            }
         }
         return shared_mem;
      }
   };

   static cOS2SharedMemory SharedMem;

#elif defined __ECL_W32__

   /**************************************************************************\
   *                                                                         *
   *                    A N P A S S U N G E N   W i n 3 2                    *
   *                                                                         *
   \**************************************************************************/

   #define MAX_MAILSLOT_MSG_SIZE 512

#endif




// ===========================================================================
// Definition cMsgNode
// ---------------------------------------------------------------------------
//
// cBase
//  +--cMsgNode
//
// ===========================================================================

class cMsgNode : public cBase {

public:
   //
   cMsgNode(int send_mode);
   cMsgNode(cString name, int send_mode);
   virtual ~cMsgNode()
      { }

   virtual bool ping(int timeout) = 0;

   virtual void createChannel(int msg_count, int msg_size) = 0;
   virtual void closeChannel() = 0;
   virtual void connectToChannel() = 0;
   virtual void disconnectFromChannel() = 0;

   virtual cString getFullName() const = 0;
   virtual void sendMsg(cMsg msg) = 0;
   virtual cMsg callMsg(cMsg msg, int timeout) = 0;
   virtual cMsg receiveMsg() = 0;
   virtual bool mustReplyMsg(const cMsg& msg_to_reply) = 0;
   virtual void replyMsg(const cMsg& msg_to_reply, cMsg reply_msg) = 0;

   // Protokollnamen aus 'name' ermitteln ("local" falls nicht angegeben)
   static cString getProtocol(cString name);
   // Rechnernamen aus 'name' ermitteln ("." falls nicht angegeben)
   static cString getAddress(cString name);
   // Teilnehmernamen aus 'name' ermitteln
   static cString getName(cString name);

   // Teilnehmername ermitteln
   cString getName() const
      { return name; }
   // Adresse (Rechnername) ermitteln
   cString getAddress() const
      { return address; }
   // Ist der MsgNode unbenannt (anonym)?
   bool isAnonymous() const
      { return name.isEmpty(); }

   // Warte-Flag setzen
   void setWait(bool wait)
      { cMsgNode::wait = wait; }
   // Warte-Flag erfragen
   bool getWait() const
      { return wait; }

   // Transportform der Meldung liefern (const)
   cMsg::MSGHDR *getMsg(cMsg& msg) const
      { return msg.getMsg(); }
   // Transportform der Meldung liefern (non-const)
   const cMsg::MSGHDR *getMsg(const cMsg& msg) const
      { return msg.getMsg(); }
   // Laenge (Bytezahl) der Transportform ermitteln
   int getMsgLen(const cMsg& msg) const
      { return msg.getMsgLen(); }
   // Meldungsobjekt aus Rohdaten erzeugen
   cMsg newMsg(void *mem) const
      { return cMsg((cMsg::MSGHDR *)mem); }

   // Protokollspezifische Zusatzdaten 1 ermitteln
   int getPrd1(const cMsg& msg) const
      { return msg.getMsg() ? msg.getMsg()->prd1 : 0; }
   // Protokollspezifische Zusatzdaten 2 ermitteln
   int getPrd2(const cMsg& msg) const
      { return msg.getMsg() ? msg.getMsg()->prd2 : 0; }

   // Protokollspezifische Zusatzdaten 1 setzen
   void setPrd1(cMsg& msg, int value) const
      { if ( msg.getMsg() ) msg.getMsg()->prd1 = value; }
   // Protokollspezifische Zusatzdaten 2 setzen
   void setPrd2(cMsg& msg, int value) const
      { if ( msg.getMsg() ) msg.getMsg()->prd2 = value; }

   // Gewuenschtes 'send'-Verhalten, wenn Empfaenger nicht erreichbar
   int getModeAlive() const
      { return send_mode & cMsgRecipient::modeAliveMask; }
   // Gewuenschtes 'send'-Verhalten, wenn Puffer voll
   int getModeFull() const
      { return send_mode & cMsgRecipient::modeFullMask; }

private:
   cString name, address;
   bool wait;
   // Verfahren bei 'send', wenn Empfaenger nicht erreichbar bzw. Puffer voll
   int send_mode;

};

cMsgNode::cMsgNode(int send_mode)
{
   cMsgNode::wait = true;
   cMsgNode::send_mode = send_mode;
}

cMsgNode::cMsgNode(cString name, int send_mode)
{
   cMsgNode::name = getName(name);
   cMsgNode::address = getAddress(name);
   cMsgNode::wait = true;
   cMsgNode::send_mode = send_mode;
}

cString cMsgNode::getProtocol(cString name)
{
   int pos = name.getPos(":", 1);
   if ( name[0] != ':' ) return "local";
   if ( pos < 1 ) return name.getMid(1);
   return name.getSubstr(1, pos - 1);
}

cString cMsgNode::getAddress(cString name)
{
   int pos1 = 0, pos2 = 0;
   if ( name[0] == ':' ) {
      pos1 = name.getPos(":", 1) + 1;
      pos2 = name.getPos(":", pos1+1) - 1;
   } else {
      pos2 = name.getPos(":", 1) - 1;
   }
   if ( pos2 > pos1+1 ) return name.getSubstr(pos1, pos2);
   return ".";
}

cString cMsgNode::getName(cString name)
{
   int pos = 0, pos1 = 1;
   while ( (pos1 = name.getPos(":", pos)) >= 0 )
      pos = pos1 + 1;
   return name.getMid(pos);
}




// ===========================================================================
// Definition cMsgNodeLOCAL
// ---------------------------------------------------------------------------
//
// Verwendung der protokollspezifischen Zusatzdaten bei benanntem MsgNode:
//
//  - prd1 ist 1
//  - prd2 enthält die eindeutige ID einer Reply-Queue, wenn eine Antwort
//    auf diese Meldung erwartet wird. Die Reply-Queue hat den generischen
//    Namen "ecl_rq<id>" (wobei <id> die Dezimalform der Queue-ID ist).
//    Wenn keine Antwort erwartet wird, ist prd1 = 0
//
// Verwendung der protokollspezifischen Zusatzdaten bei anonymem MsgNode:
//
//  - prd1 ist 2
//  - prd2 ist ein Zeiger auf die anonyme Reply-Queue.
//
// cBase
//  +--cMsgNode
//      +--cMsgNodeLOCAL
//
// ===========================================================================

#include "base/eb_queue.hpp"

class cMsgNodeLOCAL : public cMsgNode {
   cQueueRaw *queue;
   cQueueRaw *reply_queue;
   unsigned long reply_id;

   static cSharedMem cnt_mem;    // Zaehler fuer rechnerweit eindeutige ID
   static cMutexSem cnt_sem;     // Schutzsemaphore fuer obigen Zaehler

public:

   cMsgNodeLOCAL(int send_mode) :
      cMsgNode(send_mode)
   {
      queue = NULL;
      reply_queue = NULL;
      reply_id = 0;
   }

   cMsgNodeLOCAL(cString name, int send_mode) :
      cMsgNode(name, send_mode)
   {
      queue = NULL;
      reply_queue = NULL;
      reply_id = 0;
   }

   ~cMsgNodeLOCAL()
   {
      delete reply_queue;
      delete queue;
   }

   virtual bool ping(int /*timeout*/)
   {
      if ( !isAnonymous() ) {
         return cQueueRaw::isAllocated(getFullName());
      } else {
         return true;
      }
   }

   virtual void createChannel(int msg_count, int msg_size)
   {
      cQueueBase::PUT_MODE put_mode;

      switch ( getModeFull() ) {
      case cMsgRecipient::modeFullError:     put_mode = cQueueBase::putError; break;
      case cMsgRecipient::modeFullIgnore:    put_mode = cQueueBase::putIgnore; break;
      case cMsgRecipient::modeFullOverwrite: put_mode = cQueueBase::putOverwrite; break;
      default:                               put_mode = cQueueBase::putBlock; break;
      }

      switch ( getModeAlive() ) {
      case cMsgRecipient::modeAliveCreate:
         msg_count = max(msg_count, 16);
         msg_size = max(msg_size, 128);
         break;
      case cMsgRecipient::modeAliveIgnore:
         // Eventueller Fehler wird in connectToChannel() gefangen
         break;
      case cMsgRecipient::modeAliveError:
      default:
         // Default-Verhalten
         break;
      }

      cMsg empty_msg(0, 0, NULL);
      if ( msg_size >= 0 )
         msg_size += getMsgLen(empty_msg);

      try {
         if ( isAnonymous() ) {
            queue = new0 cQueueRaw(msg_count, msg_size, put_mode);
         } else {
            queue = new0 cQueueRaw(msg_count, msg_size, getFullName(), put_mode);
         }
      } catch ( cErrBase ) {
         throw cErrMsg(cErrMsg::errCreateChannel, getFullName());
      }
   }

   virtual void closeChannel()
   {
      delete queue;
      queue = NULL;
   }

   virtual void connectToChannel()
   {
      if ( !queue ) {
         try {
            createChannel(-1, -1);
         } catch ( cErrBase ) {
            if ( getModeAlive() != cMsgRecipient::modeAliveIgnore )
               throw cErrMsg(cErrMsg::errOpenChannel, getFullName());
         }
      }
   }

   virtual void disconnectFromChannel()
   {
      if ( queue )
         closeChannel();
   }

   virtual cString getFullName() const
   {
      if ( isAnonymous() ) {
         return "<<Anonymous>>";
      } else {
         return "eclMQ" + getName();
      }
   }

   virtual void sendMsg(cMsg msg)
   {
      if ( !queue )
         connectToChannel();
      if ( !queue && getModeAlive() == cMsgRecipient::modeAliveIgnore )
         return;
      sendMsgToQueue(queue, msg);
   }

   virtual cMsg callMsg(cMsg msg, int timeout)
   {
      if ( !queue )
         connectToChannel();
      if ( !queue && getModeAlive() == cMsgRecipient::modeAliveIgnore )
         return cMsg();

      if ( timeout > 0 )
         DbgInfo("MSG: Warning: Ignoring timeout parameter in cMsgRecipient::call()");

      if ( !isAnonymous() ) {
         if ( reply_id == 0 || reply_queue == NULL ) {
            reply_id = createUniqueId();
            reply_queue = new0 cQueueRaw(1, queue->getSize(), "eclRQ" + Str((int)reply_id));
         }
         setPrd1(msg, 1); // Kennung fuer benannte MsgBox
         setPrd2(msg, reply_id);
      } else {
         if ( reply_queue == NULL ) {
            reply_queue = new0 cQueueRaw(1, queue->getSize());
         }
         setPrd1(msg, 2); // Kennung fuer anonyme MsgBox
         setPrd2(msg, (int)(void *)reply_queue);
      }

      sendMsgToQueue(queue, msg);
      return receiveMsgFromQueue(reply_queue);
   }

   virtual cMsg receiveMsg()
   {
      if ( !getWait() && queue->isEmpty() )
         return cMsg();
      return receiveMsgFromQueue(queue);
   }

   virtual bool mustReplyMsg(const cMsg& msg_to_reply)
   {
      return getPrd1(msg_to_reply) != 0;
   }

   virtual void replyMsg(const cMsg& msg_to_reply, cMsg reply_msg)
   {
      setPrd1(reply_msg, 0);
      setPrd2(reply_msg, 0);

      switch ( getPrd1(msg_to_reply) ) {
      case 1:
         {
            cQueueRaw reply_queue(-1, -1, "eclRQ" + Str(getPrd2(msg_to_reply)));
            sendMsgToQueue(&reply_queue, reply_msg);
         }
         break;
      case 2:
         sendMsgToQueue((cQueueRaw *)getPrd2(msg_to_reply), reply_msg);
         break;
      }
   }

private:

   unsigned long createUniqueId() const
   {
      cnt_sem.request();
      unsigned long id = ++(*((unsigned long *)cnt_mem.getAdr()));
      cnt_sem.release();
      return id;
   }

   void sendMsgToQueue(cQueueRaw *queue, cMsg msg)
   {
      if ( queue == NULL ) {
         DbgError("MSG: Tried to send to a non-opend queue");
         throw cErrMsg(cErrMsg::errSendToChannel, getFullName());
      }

      int msg_len = getMsgLen(msg);
      if ( msg_len > queue->getSize() ) {
         DbgError("MSG: Tried to send a %d byte msg to a %d byte queue", msg_len, queue->getSize());
         throw cErrMsg(cErrMsg::errMsgTooLong, getFullName());
      }

      queue->put(getMsg(msg), getMsgLen(msg));
   }

   cMsg receiveMsgFromQueue(cQueueRaw *queue)
   {
      char mem[1024];
      queue->get(mem, sizeof mem);

      cMsg msg = newMsg(mem);
      if ( !msg.isValid() ) {
         DbgError("MSG: Received an invalid memory block");
         throw cErrMsg(cErrMsg::errInvalidMsg, getFullName());
      }

      return msg;
   }

};

cSharedMem cMsgNodeLOCAL::cnt_mem("eclMSGCntMem", cSharedMem::memOpenOrCreate, sizeof(unsigned long));
cMutexSem cMsgNodeLOCAL::cnt_sem("eclMSGCntSem", cMutexSem::semOpenOrCreate);




#if defined __Use_Named_Pipes__

#include "base/eb_npipe.hpp"
#define MAX_NAMEDPIPE_MSG_SIZE 512

// ===========================================================================
// Definition cMsgNodeNPIPE
// ---------------------------------------------------------------------------
//
// cBase
//  +--cMsgNode
//      +--cMsgNodeNPIPE
//
// ===========================================================================

class cMsgNodeNPIPE : public cMsgNode {
   cNpServer *server;
   cNpClient *client;

public:

   cMsgNodeNPIPE(cString name, int send_mode) :
      cMsgNode(name, send_mode)
   {
      server = NULL;
      client = NULL;
   }

   virtual bool ping(int timeout)
   {
      // ???
      return true;
   }

   virtual void createChannel(int msg_count, int msg_size)
   {
      server = new0 cNpServer(getFullName(), MAX_NAMEDPIPE_MSG_SIZE, msg_count);
   }

   virtual void closeChannel()
   {
      delete server; server = NULL;
   }

   virtual void connectToChannel()
   {
      client = new0 cNpClient(getFullName());
   }

   virtual void disconnectFromChannel()
   {
      delete client; client = NULL;
   }

   virtual cString getFullName() const
   {
      return getAddress() + ":" + getName();
   }

   virtual void sendMsg(cMsg msg)
   {
      if ( client == NULL )
         connectToChannel();
      if ( client != NULL )
         client->write(getMsg(msg), getMsgLen(msg));
   }

   virtual cMsg callMsg(cMsg msg, int timeout)
   {
      DbgError("MSG: Warning: Ignoring cMsgRecipient::call() for Named Pipes");
      return cMsg();
   }

   virtual cMsg receiveMsg()
   {
      char buf[MAX_NAMEDPIPE_MSG_SIZE];

      if ( server && server->read(buf, sizeof buf) < 0 )
         return cMsg();

      cMsg msg = newMsg(buf);

      if ( !msg.isValid() ) {
         DbgError("NPipe: Received an invalid memory block");
         throw cErrMsg(cErrMsg::errInvalidMsg, getFullName());
      }

      return msg;
   }

   virtual bool mustReplyMsg(const cMsg& msg_to_reply)
   {
      return false;
   }

   virtual void replyMsg(const cMsg& msg_to_reply, cMsg reply_msg)
   {
      DbgError("MSG: Warning: Ignoring cMsgBox::reply() for Named Pipes");
   }

};

#endif /*__Use_Named_Pipes__*/




#if defined __ECL_OS2__

// ===========================================================================
// Definition cMsgNodeQUEUE
// ---------------------------------------------------------------------------
//
// cBase
//  +--cMsgNode
//      +--cMsgNodeQUEUE
//
// ===========================================================================

class cMsgNodeQUEUE : public cMsgNode {
   unsigned long write_queue;
   unsigned long read_queue;
   unsigned long sync_sema;

public:

   cMsgNodeQUEUE(cString name, int send_mode) :
      cMsgNode(name, send_mode)
   {
      write_queue = read_queue = sync_sema = 0;
   }

   virtual bool ping(int timeout)
   {
      // ???
      return true;
   }

   virtual void createChannel(int msg_count, int msg_size)
   {
      APIRET rc;
      if ( (rc = DosCreateEventSem(NULL, &sync_sema, 0, FALSE)) != NO_ERROR ) {
         DbgError("OS/2: could not create event semaphore, rc = %d", rc);
         throw cErrMsg(cErrMsg::errCreateChannel, getFullName());
      }
      if ( (rc = DosCreateQueue(&read_queue, QUE_FIFO, getFullName())) != NO_ERROR ) {
         DbgError("OS/2: could not create message queue '%s', rc = %d", (const char *)getFullName(), rc);
         DosCloseEventSem(sync_sema);
         throw cErrMsg(cErrMsg::errCreateChannel, getFullName());
      }
   }

   virtual void closeChannel()
   {
      if ( sync_sema ) DosCloseEventSem(sync_sema);
      if ( read_queue ) DosCloseQueue(read_queue);
      sync_sema = read_queue = 0;
   }

   virtual void connectToChannel()
   {
      PID pid = 0;
      APIRET rc;
      if ( write_queue != 0 ) {
         // Testen, ob die Verbindung noch steht
         ULONG dummy;
         if ( 0 != (rc = DosQueryQueue(write_queue, &dummy)) ) {
            /* DosCloseQueue( qd->que ); *???*/
            /* DbgError("OS/2: DosQueryQueue returned %d\n", rc); */
            DbgError("OS/2: Queue '%s' died, retrying\n", (const char *)getFullName());
            write_queue = 0;
         }
      }
      if ( write_queue == 0 && 0 != (rc = DosOpenQueue(&pid, &write_queue, getFullName())) ) {
         DbgError("OS/2: DosOpenQueue returned %d\n", rc);
         throw cErrMsg(cErrMsg::errOpenChannel, getFullName());
      }
   }

   virtual void disconnectFromChannel()
   {
      if ( write_queue != 0 ) {
         DosCloseQueue(write_queue);
         write_queue = 0;
      }
   }

   virtual cString getFullName() const
   {
      return "\\queues\\ecl\\" + getName();
   }

   virtual void sendMsg(cMsg msg)
   {
      void *mem;
      int size = getMsgLen(msg);
      APIRET rc;

      disconnectFromChannel();
      connectToChannel();

      if ( (mem = SharedMem.alloc(size)) == NULL )
         throw cErrMsg(cErrMsg::errSendToChannel, getFullName());
      memcpy(mem, getMsg(msg), size);

      if ( 0 != (rc = DosWriteQueue(write_queue, 0, size, (PVOID)mem, 0)) ) {
         DbgError("OS/2: DosWriteQueue returned %d\n", rc);
         throw cErrMsg(cErrMsg::errSendToChannel, getFullName());
      }
   }

   virtual cMsg callMsg(cMsg msg, int timeout)
   {
      DbgError("OS/2: Warning: Ignoring cMsgRecipient::call() for Queues");
      return cMsg();
   }

   virtual cMsg receiveMsg()
   {
      ULONG size;
      BYTE prio;
      void *mem = NULL;
      REQUESTDATA request = { _getpid(), 0 };
      ULONG wait = getWait() ? DCWW_WAIT : DCWW_NOWAIT;

      APIRET rc = DosReadQueue(read_queue, &request, &size, (PPVOID)&mem, 0, wait, &prio, sync_sema);

      if ( rc != NO_ERROR ) {
         if ( rc == ERROR_QUE_EMPTY ) {
            // Legaler Zustand: Keine Meldung vorhanden
            return cMsg();
         } else {
            DbgError("OS/2: DosReadQueue failed, rc = %d", rc);
            throw cErrMsg(cErrMsg::errReceiveFromChannel, getFullName());
         }
      } else {
         SharedMem.init();
         cMsg msg = newMsg(mem);
         if ( !msg.isValid() ) {
            DbgError("OS/2: Received an invalid memory block");
            throw cErrMsg(cErrMsg::errInvalidMsg, getFullName());
         } else {
            SharedMem.free(mem, size);
            return msg;
         }
      }
   }

   virtual bool mustReplyMsg(const cMsg& msg_to_reply)
   {
      return false;
   }

   virtual void replyMsg(const cMsg& msg_to_reply, cMsg reply_msg)
   {
      DbgError("OS/2: Warning: Ignoring cMsgBox::reply() for Queues");
   }

};

#endif /*__ECL_OS2__*/




#if defined __ECL_W32__

// ===========================================================================
// Definition cMsgNodeMSLOT
// ---------------------------------------------------------------------------
//
// cBase
//  +--cMsgNode
//      +--cMsgNodeMSLOT
//
// ===========================================================================

class cMsgNodeMSLOT : public cMsgNode {
   void *write_mslot;
   void *read_mslot;

public:

   cMsgNodeMSLOT(cString name, int send_mode) :
      cMsgNode(name, send_mode)
   {
      write_mslot = read_mslot = NULL;
   }

   virtual bool ping(int /*timeout*/)
   {
      // ???
      return true;
   }

   virtual void createChannel(int /*msg_count*/, int /*msg_size*/)
   {
      read_mslot = CreateMailslot(getFullName(), MAX_MAILSLOT_MSG_SIZE,
         getWait() ? MAILSLOT_WAIT_FOREVER : 0, NULL);
      if ( read_mslot == INVALID_HANDLE_VALUE ) {
         DbgError("Win32: Could not create mailslot '%s'", (const char *)getFullName());
         throw cErrMsg(cErrMsg::errCreateChannel, getFullName());
      }
   }

   virtual void closeChannel()
   {
      if ( read_mslot ) CloseHandle(read_mslot);
      read_mslot = NULL;
   }

   virtual void connectToChannel()
   {
      HANDLE port = CreateFile(getFullName(),
         GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
         OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      if ( port == INVALID_HANDLE_VALUE ) {
         DbgError("Win32: Could not open mailslot '%s'", (const char *)getFullName());
         throw cErrMsg(cErrMsg::errOpenChannel, getFullName());
      }
      write_mslot = port;
   }

   virtual void disconnectFromChannel()
   {
      if ( write_mslot != NULL ) {
         CloseHandle(write_mslot);
         write_mslot = NULL;
      }
   }

   virtual cString getFullName() const
   {
      return "\\\\" + getAddress() + "\\mailslot\\ecl\\" + getName();
   }

   virtual void sendMsg(cMsg msg)
   {
      int retries = 2;
      BOOL ok = FALSE;
      DWORD bytes_written = 0;

      if ( write_mslot == NULL )
         connectToChannel();

      while ( retries-- > 0 ) {
         ok = WriteFile(write_mslot, getMsg(msg),
            getMsgLen(msg), &bytes_written, NULL);
         if ( ok && bytes_written == (DWORD)getMsgLen(msg) )
            break;
         connectToChannel();
         ok = FALSE;
      }

      if ( !ok ) {
         DbgError("Win32: WriteFile failed (err=%x, written=%d, expected=%d)", GetLastError(), bytes_written, getMsgLen(msg));
         throw cErrMsg(cErrMsg::errSendToChannel, getFullName());
      }
   }

   virtual cMsg callMsg(cMsg msg, int /*timeout*/)
   {
      DbgError("Win32: Warning: Ignoring cMsgRecipient::call() for Mailslots");
      return cMsg();
   }

   virtual cMsg receiveMsg()
   {
      DWORD current_timeout, sizeof_next_msg, number_of_msgs, bytes_read;
      DWORD desired_timeout = getWait() ? MAILSLOT_WAIT_FOREVER : 0;

      BOOL ok = GetMailslotInfo(read_mslot, NULL,
         &sizeof_next_msg, &number_of_msgs, &current_timeout);

      if ( !ok ) {
         DbgError("Win32: GetMailslotInfo failed");
         throw cErrMsg(cErrMsg::errReceiveFromChannel, getFullName());
      }
      if ( current_timeout != desired_timeout
        && !SetMailslotInfo(read_mslot, desired_timeout) )
      {
         DbgError("Win32: SetMailslotInfo failed");
         throw cErrMsg(cErrMsg::errReceiveFromChannel, getFullName());
      }

      if ( number_of_msgs == 0 && desired_timeout == 0 )
         return cMsg();   // Legaler Zustand: Keine Meldung vorhanden

      char mem[MAX_MAILSLOT_MSG_SIZE];
      ok = ReadFile(read_mslot, mem, MAX_MAILSLOT_MSG_SIZE, &bytes_read, NULL);
      cMsg msg = newMsg(mem);

      if ( !ok ) {
         DbgError("Win32: ReadFile failed (read only %d bytes of %d)", bytes_read, sizeof_next_msg);
         throw cErrMsg(cErrMsg::errReceiveFromChannel, getFullName());
      } else if ( !msg.isValid() ) {
         DbgError("Win32: Received an invalid memory block");
         throw cErrMsg(cErrMsg::errInvalidMsg, getFullName());
      }

      return msg;
   }

   virtual bool mustReplyMsg(const cMsg& /*msg_to_reply*/)
   {
      return false;
   }

   virtual void replyMsg(const cMsg& /*msg_to_reply*/, cMsg reply_msg)
   {
      DbgError("Win32: Warning: Ignoring cMsgBox::reply() for Mailslots");
   }

};

#endif /*__ECL_W32__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cErrMsg
// ---------------------------------------------------------------------------
//
// cBase
//  +--cErrBase
//      +--cErrMsg
//
// ===========================================================================

class __ECL_DLLEXPORT__ cErrMsg : public cErrBase {

public:
   cErrMsg(int err, const char *name);

   enum ERR_CODE { errBase = ERR_PREFIX('M','S','G'),

      // Fehler
      errOpenChannel = errBase+errError , // Kann nicht Oeffnen zum Senden
      errCreateChannel                  , // Kann nicht Erzeugen zum Empfangen
      errSendToChannel                  , // Fehler beim Senden
      errReceiveFromChannel             , // Fehler beim Empfangen
      errSendEmptyMsg                   , // Versuch, leere Meldung zu senden
      errInvalidMsg                     , // Ungueltige Meldung empfangen
      errInvalidProtocol                , // Ungueltiges Protokoll angegeben
      errUnsupportedProtocol            , // Protokoll nicht unterstuetzt
      errMsgTooLong                     , // Meldung zu lang
      errNoAnonymousRecipient             // Anonymer Adressat nicht zulaessig

   };

};

#endif /*__INTERFACE__*/


// Implementierung cErrMsg
// ===========================================================================

cErrMsg::cErrMsg(int err, const char *name) :
   cErrBase(err)
{
   setParam(0, name);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cMsg
// ---------------------------------------------------------------------------
//
// Verwaltungs- und Nutzdaten, die als Meldung verschickt werden koennen.
//
// Unterstuetzte Platzhalter im Formatstring (bprintf):
//
//   %    | Bedeutung                      | Auf Stack | In Meldung
//  ------+--------------------------------+-----------+------------
//   %c   | ein Zeichen (oder Byte)        | int       | 1 Byte
//   %i   | ein short (oder USHORT)        | int       | 2 Byte
//   %u   | ein Wort (oder WORD)           | int       | 4 Byte
//   %d   | ein Wort (oder WORD)           | int       | 4 Byte
//   %l   | ein Langwort                   | long      | 4 Byte
//   %f   | eine Realzahl (immer double)   | double    | 8 Byte
//   %s   | Adr. eines nullterm. Strings   | char *s   | *s + '\0'
//   %t   | Adresse einer Struktur mit     | size_t *s | *s
//        | vorangehender Groesse (size_t) |           |
//   %%   | das Zeichen '%'                | -         | '%'
//   #ddd | dez. Angabe eines Zeichens     | -         | '\ddd'
//   #xhh | hex. Angabe eines Zeichens     | -         | '\0xhh'
//   ##   | das Zeichen '#'                | -         | '#'
//
// Beispiel fuer %t:
//
//    struct T {
//       size_t my_size;
//       int a, b, c;
//       // ...
//    } t;
//
//    t.my_size = sizeof t;
//    cMsg msg(MY_ID, "%t", &t);
//
// cBase
//  +--cMsg
//
// ===========================================================================

class __ECL_DLLEXPORT__ cMsg : public cBase {
   friend class cMsgNode;

public:
   // Konstruktor fuer leere Meldung (isEmpty liefert true)
   cMsg();
   // Konstruktor fuer datenfreie Meldung
   cMsg(int msg_id);
   // Konstruktor ueber Zeiger auf Datenbereich
   cMsg(int msg_id, int size, const void *data);
   // Konstruktor ueber cString
   cMsg(int msg_id, cString str);
   // Konstruktor ueber bprintf
   cMsg(int msg_id, const char *fmt, ...);
   // Konstruktor ueber vprintf
   cMsg(int msg_id, const char *fmt, va_list ap);
   // Copy-Konstruktor
   cMsg(const cMsg& other);
   ~cMsg();

   // Zuweisungsoperator
   cMsg& operator=(const cMsg& other);

   // Ist die Meldung gueltig?
   bool isValid() const;
   // Ist die Meldung gueltig, aber leer?
   bool isEmpty() const;

   // Meldungs-ID erfragen
   int getMsgId() const
      { return msg ? msg->id : 0; }

   // Erfragen der Meldungs-Daten
   void *getData() const
      { return msg ? msg->d : NULL; }
   // Erfragen der Laenge der Meldungs-Daten
   int getDataLen() const
      { return msg ? msg->size : 0; }

private:
   struct MSGHDR {
      int magic;     // Identifizierung
      int id;        // Meldungs-ID
      int size;      // Allokierte Groesse
      int refc;      // Referenzzaehler
      int prd1;      // Protokollspezifische Zusatzdaten 1
      int prd2;      // Protokollspezifische Zusatzdaten 2
      char d[1];     // Groesse dynamisch
   } *msg;

   // Konstruktor ueber interne MSGHDR-Struktur
   cMsg(const MSGHDR *foreign_msg);
   // Allokieren und vorinitialisieren der internen Struktur
   MSGHDR *alloc(int len);
   // Referenzzaehler dekrementieren, Struktur evtl. freigeben
   void dealloc(MSGHDR *& msg);
   // Hilfsfunktion zur Initialisieren der internen Struktur
   bool init(int msg_id, const void *data, int size);

   // Transportform der Meldung liefern (const)
   const MSGHDR *getMsg() const
      { return msg; }
   // Transportform der Meldung liefern (non-const)
   MSGHDR *getMsg()
      { return msg; }
   // Laenge (Bytezahl) der Transportform ermitteln
   int getMsgLen() const
      { return sizeof *msg + getDataLen() - 1; }

};

#endif /*__INTERFACE__*/


// Implementierung cMsg
// ===========================================================================

#define MSG_MAGIC    0x42424242
#define MSG_UNMAGIC  0x00000000

cMsg::cMsg()
{
   msg = NULL;
}

cMsg::cMsg(int msg_id)
{
   if ( alloc(0) != NULL )
      msg->id = msg_id;
}

cMsg::cMsg(int msg_id, int size, const void *data)
{
   init(msg_id, data, size);
}

cMsg::cMsg(int msg_id, cString str)
{
   init(msg_id, (const char *)str, str.getLength() + 1);
}

cMsg::cMsg(int msg_id, const char *fmt, ...)
{
   va_list ap;
   char buf[1024];
   va_start(ap, fmt);
   int size = vbprintf(buf, fmt, ap);
   if ( size >= 0 )
      init(msg_id, buf, size);
   va_end(ap);
}

cMsg::cMsg(int msg_id, const char *fmt, va_list ap)
{
   char buf[1024];
   int size = vbprintf(buf, fmt, ap);
   if ( size >= 0 )
      init(msg_id, buf, size);
}

cMsg::cMsg(const cMsg& other)
{
   msg = other.msg;
   if ( msg )
/// PR 11.10.05 changes for thread safety on SMP and hyperthreading enabled machines
///      msg->refc++;
       InterlockedIncrement((long*)&(msg->refc));
/// <
}

cMsg::cMsg(const MSGHDR *foreign_msg)
{
   if ( foreign_msg != NULL ) {
      init(foreign_msg->id, foreign_msg->d, foreign_msg->size);
      msg->magic = foreign_msg->magic;
      msg->prd1 = foreign_msg->prd1;
      msg->prd2 = foreign_msg->prd2;
   }
}

cMsg::~cMsg()
{
   dealloc(msg);
}

cMsg& cMsg::operator=(const cMsg& other)
{
   if ( &other != this ) {
      dealloc(msg);
      msg = other.msg;
      if ( msg )
/// PR 11.10.05 changes for thread safety on SMP and hyperthreading enabled machines
///         msg->refc++;
         InterlockedIncrement((long*)&(msg->refc));
/// <
   }
   return *this;
}

bool cMsg::isValid() const
{
   return msg == NULL || msg->magic == MSG_MAGIC;
}

bool cMsg::isEmpty() const
{
   return msg == NULL;
}

cMsg::MSGHDR * cMsg::alloc(int len)
{
   msg = (MSGHDR *)malloc(sizeof *msg + len - 1);
   msg->magic = MSG_MAGIC;
   msg->size = len;
   msg->refc = 0;
   msg->prd1 = 0;
   msg->prd2 = 0;
   return msg;
}

void cMsg::dealloc(MSGHDR *& data)
{
   if ( data ) {
/// PR 11.10.05 changes for thread safety on SMP and hyperthreading enabled machines
///      if ( data->refc-- == 0 ) {
      if ( InterlockedDecrement((long*)&(data->refc)) == -1 ) {
/// <
         data->magic = MSG_UNMAGIC;
         free(data);
      }
      data = NULL;
   }
}

bool cMsg::init(int msg_id, const void *data, int size)
{
   if ( alloc(size) != NULL && data != NULL ) {
      msg->id = msg_id;
      memcpy(msg->d, data, size);
      return true;
   }
   return false;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cMsgRecipient
// ---------------------------------------------------------------------------
//
// Meldungsadressat.
//
// cBase
//  +--cMsgRecipient
//
// ===========================================================================

class __ECL_DLLEXPORT__ cMsgRecipient : public cBase {

public:
   // Verhalten von 'send', wenn Empfaenger nicht bereit oder Puffer voll
   // Gruppenweise maskierbar, z.B. (modeAliveIgnore | modeFullOverwrite)

   enum SEND_MODE {

                        // Reaktion von 'send', wenn Empfaenger nicht bereit
      modeAliveError    = 0x0000,   //  - Werfen von cErrMsg::errOpenChannel
      modeAliveIgnore   = 0x0001,   //  - Ignorieren des Aufrufs von 'send'
      modeAliveCreate   = 0x0002,   //  - Standardpuffer anlegen (16 x 128 Bytes)
      modeAliveMask     = 0x000f,   //  - ... zum Ausmaskieren der modeAlive-Gruppe

                        // Reaktion von 'send', wenn Puffer zum Empfaenger voll
      modeFullBlock     = 0x0000,   //  - Blockieren des aufrufenden Threads
      modeFullError     = 0x0010,   //  - Werfen von cErrBase::errOverflow
      modeFullIgnore    = 0x0020,   //  - Verwerfen der aktuellen Meldung
      modeFullOverwrite = 0x0030,   //  - Ueberschreiben der aeltesten Meldung im Puffer
      modeFullMask      = 0x00f0    //  - ... zum Ausmaskieren der modeFull-Gruppe

   };

   // Anlegen eines benannten Adressaten
   cMsgRecipient(cString address_name, int send_mode = 0);
   // Loeschen des Adressaten
   ~cMsgRecipient();

   // Pruefen, ob Adressat lebt
   bool ping(int timeout = 0);
   // Meldung abschicken
   void send(cMsg msg);
   // Meldung abschicken und auf Antwort warten
   cMsg call(cMsg msg, int timeout = -1);

   // Name des Adressaten
   cString getName() const;
   // Adresse (Zielrechner) des Adressaten
   cString getAddress() const;
   // Protokollspezifischer Name des Adressaten
   cString getFullName() const;

protected:
   // Anlegen eines anonymen Adressaten (nur zusammen mit MsgBox moeglich!)
   cMsgRecipient(int send_mode);
   // Anlegen eines benannten oder anonymen Adressaten
   cMsgRecipient(cString address_name, bool maybe_anonymous, int send_mode);
   // Initialisierung des Adressaten
   void init(cString address_name, bool maybe_anonymous, int send_mode);
   // Zeiger auf Implementierungsklasse (abhaengig von Meldungs-Protokoll)
   cMsgNode *node;

};

#endif /*__INTERFACE__*/


// Implementierung cMsgRecipient
// ===========================================================================

cMsgRecipient::cMsgRecipient(int send_mode)
{
   node = new0 cMsgNodeLOCAL(send_mode);
}

cMsgRecipient::cMsgRecipient(cString address_name, int send_mode)
{
   init(address_name, false, send_mode);
}

cMsgRecipient::cMsgRecipient(cString address_name, bool maybe_anonymous, int send_mode)
{
   init(address_name, maybe_anonymous, send_mode);
}

cMsgRecipient::~cMsgRecipient()
{
   node->disconnectFromChannel();
   delete node;
}

void cMsgRecipient::init(cString address_name, bool maybe_anonymous, int send_mode)
{
   cString name = cMsgNode::getName(address_name);
   if ( !maybe_anonymous && name.isEmpty() )
      throw cErrMsg(cErrMsg::errNoAnonymousRecipient, address_name);

   cString protocol = cMsgNode::getProtocol(address_name);
   node = NULL;

   if ( protocol == "private" ) {
      protocol = "local";
      address_name += cStringf("@%ld", cThread::getCurrentProcessId());
   }

   if ( protocol == "local" ) {
      node = new0 cMsgNodeLOCAL(address_name, send_mode);
   } else if ( protocol == "npipe" ) {
      #if defined __Use_Named_Pipes__
         node = new0 cMsgNodeNPIPE(address_name, send_mode);
      #else
         throw cErrMsg(cErrMsg::errUnsupportedProtocol, protocol);
      #endif
   } else if ( protocol == "queue" ) {
      #if defined __ECL_OS2__
         node = new0 cMsgNodeQUEUE(address_name, send_mode);
      #else
         throw cErrMsg(cErrMsg::errUnsupportedProtocol, protocol);
      #endif
   } else if ( protocol == "mslot" ) {
      #if defined __ECL_W32__
         node = new0 cMsgNodeMSLOT(address_name, send_mode);
      #else
         throw cErrMsg(cErrMsg::errUnsupportedProtocol, protocol);
      #endif
   } else {
      throw cErrMsg(cErrMsg::errInvalidProtocol, protocol);
   }
}

cString cMsgRecipient::getName() const
{
   return node->getName();
}

cString cMsgRecipient::getAddress() const
{
   return node->getAddress();
}

bool cMsgRecipient::ping(int timeout)
{
   return node->ping(timeout);
}

void cMsgRecipient::send(cMsg msg)
{
   if ( msg.isEmpty() ) {
      DbgError("Tried to send empty message");
      throw cErrMsg(cErrMsg::errSendEmptyMsg, getFullName());
   }

   node->sendMsg(msg);
}

cMsg cMsgRecipient::call(cMsg msg, int timeout)
{
   if ( msg.isEmpty() ) {
      DbgError("Tried to call with empty message");
      throw cErrMsg(cErrMsg::errSendEmptyMsg, getFullName());
   }

   return node->callMsg(msg, timeout);
}

cString cMsgRecipient::getFullName() const
{
   return node->getFullName();
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cMsgBox
// ---------------------------------------------------------------------------
//
// Meldungsempfaenger.
//
// cBase
//  +--cMsgRecipient
//      +--cMsgBox
//
// ===========================================================================

class __ECL_DLLEXPORT__ cMsgBox : public cMsgRecipient {

public:
   // Anlegen einer anonymen MsgBox (nur Intra-Prozess-Kommunikation)
   cMsgBox(int msg_count = 16, int msg_size = 128, int send_mode = 0);
   // Anlegen einer benannten MsgBox (vgl. Modul-Dokumentation)
   cMsgBox(cString name, int msg_count = 16, int msg_size = 128, int send_mode = 0);
   // Loeschen der MsgBox
   ~cMsgBox();

   // Empfangen einer Meldung (Warten abhaengig vom Wait-Flag)
   cMsg receive();
   // Empfangen einer gefilterten Meldnung (NOCH NICHT IMPLEMENTIERT!!!)
   cMsg receiveFiltered(unsigned char msg_low, unsigned char msg_hi);

   // Wird eine Antwort auf die Meldung erwartet?
   bool mustReply(const cMsg& msg_to_reply) const;
   // Beantworten der Meldung msg_to_reply mit der Meldung reply_msg
   void reply(const cMsg& msg_to_reply, cMsg reply_msg);

   // Warte-Flag setzen
   void setWait(bool wait);
   // Warte-Flag erfragen
   bool getWait() const;

};

#endif /*__INTERFACE__*/


// Implementierung cMsgBox
// ===========================================================================

cMsgBox::cMsgBox(int msg_count, int msg_size, int send_mode) :
   cMsgRecipient(send_mode)
{
   node->createChannel(msg_count, msg_size);
}

cMsgBox::cMsgBox(cString name, int msg_count, int msg_size, int send_mode) :
   cMsgRecipient(name, true, send_mode)
{
   node->createChannel(msg_count, msg_size);
}

cMsgBox::~cMsgBox()
{
   node->closeChannel();
}

void cMsgBox::setWait(bool wait)
{
   node->setWait(wait);
}

bool cMsgBox::getWait() const
{
   return node->getWait();
}

cMsg cMsgBox::receive()
{
   return node->receiveMsg();
}

bool cMsgBox::mustReply(const cMsg& msg_to_reply) const
{
   return node->mustReplyMsg(msg_to_reply);
}

void cMsgBox::reply(const cMsg& msg_to_reply, cMsg reply_msg)
{
   node->replyMsg(msg_to_reply, reply_msg);
}




#ifdef __Test_eb_msg__

   #include "base/eb_thread.hpp"
   #include <conio.h>

   // -------------------------------------------------------------------------

   cMsgBox PrivateBox;

   void PrivateSender(char ch)
   {
      cMsg msg(42, "%c", ch);
      while ( 1 ) {
         try {
            PrivateBox.send(msg);
         } catch ( cErrBase& err ) {
            cerr << " * ERROR: " << err << endl;
         }
         cThread::sleep(50);
      }
   }

   void PrivateReceiver()
   {
      while ( 1 ) {
         cMsg msg;
         msg = PrivateBox.receive();
         cerr << *((char *)msg.getData());
      }
   }

   class cPrivateSender : public cThread {
   public:
      cPrivateSender(char ch) { start((void *)ch); }
      int onMain(void *ch) { PrivateSender((char)(long)ch); return 0; }
   };

   class cPrivateReceiver : public cThread {
   public:
      cPrivateReceiver() { start(cThread::teStart); }
      int onMain(void *) { PrivateReceiver(); return 0; }
   };

   // -------------------------------------------------------------------------

   int PublicNum;
   int PublicMaxFound = 0;
   cEventSem PublicReceiverReady;

   void PublicSender(char ch)
   {
      PublicReceiverReady.wait();

      cMsgRecipient *mrecps[100] = { NULL };
      cMsg msg(42, "%c%c", PublicNum, ch);

      while ( 1 ) {
         int rcp = rand() % (PublicMaxFound + 2);
         if ( mrecps[rcp] == NULL )
            mrecps[rcp] = new0 cMsgRecipient("TestBox" + Str(rcp), cMsgRecipient::modeFullOverwrite);
         if ( mrecps[rcp]->ping() ) {
            try {
               mrecps[rcp]->send(msg);
               if ( rcp > PublicMaxFound )
                  PublicMaxFound = rcp;
            } catch ( cErrBase& err ) {
               cerr << " * ERROR: " << err << endl;
            }
         }
         cThread::sleep(50);
      }
   }

   void PublicReceiver()
   {
      cMsgBox *mbox = NULL;

      for ( PublicNum = 0 ; PublicNum <= 100 ; PublicNum++ ) {
         cMsgRecipient check("TestBox" + Str(PublicNum));
         if ( !check.ping() ) {
            try {
               mbox = new0 cMsgBox("TestBox" + Str(PublicNum));
            } catch ( cErrMsg ) {
               mbox = NULL;
            }
            if ( mbox )
               break;
         }
      }

      cout << "Receiving on " << mbox->getFullName() << endl;

      PublicReceiverReady.set();

      while ( 1 ) {
         cMsg msg;
         msg = mbox->receive();
         cerr << "[" << (int)*((char *)msg.getData())
              << ":" << *((char *)msg.getData()+1) << "] ";
      }
   }

   class cPublicSender : public cThread {
   public:
      cPublicSender(char ch) { start((void *)ch); }
      int onMain(void *ch) { PublicSender((char)(long)ch); return 0; }
   };

   class cPublicReceiver : public cThread {
   public:
      cPublicReceiver() { start(cThread::teStart); }
      int onMain(void *) { PublicReceiver(); return 0; }
   };

   // -------------------------------------------------------------------------

   cMsgBox PingPongAnonymousBox;

   void PingPongClient(cString mbox_name)
   {
      cerr << "PingPong Client for '" << mbox_name << "' running - Press ESC to quit" << endl;
      cMsgRecipient *mr = mbox_name.isEmpty() ? &PingPongAnonymousBox : new0 cMsgRecipient(mbox_name);
      char ch;

      while ( (ch = _getch()) != 27 ) {
         cMsg msg = mr->call(cMsg(42, "%c#000", ch));
         cerr << "PONG < " << (const char *)msg.getData() << endl;
         mr->send(cMsg(42, "%c#000", ch));
      }
   }

   void PingPongServer(cString mbox_name)
   {
      cerr << "PingPong Server for '" << mbox_name << "' running" << endl;
      cMsgBox mbox(mbox_name);
      cMsgBox *mb = mbox_name.isEmpty() ? &PingPongAnonymousBox : &mbox;

      while ( 1 ) {
         cMsg msg = mb->receive();
         if ( mb->mustReply(msg) ) {
            cerr << "> PING " << (const char *)msg.getData() << endl;
            mb->reply(msg, cMsg(42, msg.getDataLen(), msg.getData()));
         } else {
            cerr << "Plopp: " << (const char *)msg.getData() << endl;
         }
      }
   }

   class cPingPongServer : public cThread {
      cString mbox_name;
   public:
      cPingPongServer(cString name) { mbox_name = name; start(cThread::teStart); }
      int onMain(void *) { PingPongServer(mbox_name); return 0; }
   };

   // -------------------------------------------------------------------------

   class cSender : public cThread {
   public:
      int onMain(void *extra)
      {
         cString name = cString((const char *)extra) + ":listener";
         cMsgRecipient mbox(name);

         while ( true ) {
            char ch = _getch();
            mbox.send(cMsg(42, "KEY %c#000", ch));
         }
      }
   };

   int main(int argc, char *argv[1])
   {
      try {

         if ( argc < 2 ) {
            cerr << "usage: msg [-l] address"      << endl
                 << "   -l create listener thread" << endl;
            return 1;
         }

         cString option = argv[1];
         cString address = argc > 2 ? argv[2] : argv[1];

         cout << "address = :" << cMsgNode::getProtocol(address)
              <<           ":" << cMsgNode::getAddress(address)
              <<           ":" << cMsgNode::getName(address)
              << endl;

         if ( option == "-priv" ) {

            cPrivateReceiver r;
            for ( int i = 'a' ; i < 'z' ; i++ )
               new0 cPrivateSender(i);
            r.waitFor();

         } else if ( option == "-pub" ) {

            cPublicReceiver r;
            for ( int i = 'a' ; i <= 'z' ; i++ )
               new0 cPublicSender(i);
            r.waitFor();

         } else if ( option == "-pp" ) {

            if ( argc > 2 ) {
               cPingPongServer ppr(address);
               PingPongClient(address);
            } else {
               cPingPongServer ppr(NULL);
               PingPongClient(NULL);
            }

         } else if ( option == "-ppc" ) {

            PingPongClient(address);

         } else if ( option == "-pps" ) {

            PingPongServer(address);

         } else if ( option == "-l" ) {

            cMsgBox mbox(address);
            cout << "Listening on " << mbox.getFullName() << endl;

            while ( true ) {
               cMsg msg = mbox.receive();
               switch ( msg.getMsgId() ) {
               case 42:
                  cout << "You've typed: '" << (const char *)msg.getData() << "'" << endl;
                  break;
               }
            }

         } else {

			cMsgRecipient mbox(address, cMsgRecipient::modeFullOverwrite | cMsgRecipient::modeAliveCreate);
            cout << "Sending to " << mbox.getFullName() << endl;

            while ( true ) {
               char ch = _getch();
               mbox.send(cMsg(42, cStringf("KEY %c", ch)));
            }

         }

      } catch ( const cErrBase& err ) {

         cerr << "EXCEPTION: " << err << endl;

      }

      return 0;
   }

#endif

