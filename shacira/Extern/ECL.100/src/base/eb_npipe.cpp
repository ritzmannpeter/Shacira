// ===========================================================================
// eb_npipe.cpp                                  ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cErrBase
//     |  |
//     |  +-cErrNp            - Named Pipes Fehlerklasse.
//     |
//     +-cNamedPipe           - Verwalten einer Named Pipe im Message-Mode.
//     |
//     +-cNpClient            - Einfacher Named Pipe Client.
//     |
//     +-cNpServer            - Multithreaded Named Pipe Server.
//
// ===========================================================================

#include "base/eb_thread.hpp"
#include "base/eb_list.hpp"
#include "base/eb_npipe.hpp"

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
#elif defined __ECL_W32__
   #include <windows.h>
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_err.hpp"
#include "base/eb_str.hpp"
#include "base/eb_queue.hpp"

class cNpSrvConnectThread;

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cErrNp
// ---------------------------------------------------------------------------
//
// cBase
//  +--cErrBase
//      +--cErrNp
//
// ===========================================================================

class __ECL_DLLEXPORT__ cErrNp : public cErrBase {

public:
   cErrNp(int err, const char *name);

   enum ERR_CODE { errBase = ERR_PREFIX('N','M','P'),

      // Fehler
      errCreate      = errBase+errError , // Kann Pipe-Instanz nicht erzeugen
      errConnect                        , // Fehler beim Connect zum Server
      errConnectTimeout                 , // Pipe-Server nicht verfuegbar
      errRead                           , // Fehler beim Lesen von Pipe
      errWrite                          , // Fehler beim Schreiben auf Pipe
      errConnectWithClient              , // Fehler beim Connect mit Client
      errDisconnectFromClient             // Fehler beim Disconnect vom Client

   };

};

#endif /*__INTERFACE__*/


// Implementierung cErrNp
// ===========================================================================

cErrNp::cErrNp(int err, const char *name) :
   cErrBase(err)
{
   setParam(0, name);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cNamedPipe
// ---------------------------------------------------------------------------
//
// Verwalten einer Named Pipe im Message-Mode.
//
// cBase
//  +--cOsBase
//      +--cNamedPipe
//
// ===========================================================================

class __ECL_DLLEXPORT__ cNamedPipe : public cOsBase {

public:
   enum MODE { mRead = 0x01, mWrite = 0x02, mDuplex = 0x03 };

   // Oeffnen einer Named Pipe im Client-Mode
   cNamedPipe(cString address_name, MODE mode, int ms_timeout = -1);
   // Erzeugen einer Named Pipe im Server-Mode (auf lokalem Rechner)
   cNamedPipe(cString name, int in_buf_size, int out_buf_size);
   // Schliessen der Named Pipe
   ~cNamedPipe();

   // Name der Pipe erfragen
   cString getName() const
      { return name; }
   // Adresse (Rechnername) der Pipe erfragen
   cString getAddress() const
      { return address; }
   // Systemspezifischen Namen ermitteln
   cString getFullName() const;

   // Modus erfragen
   MODE getPipeMode(MODE mode_mask = mDuplex) const
      { return (MODE)(pipe_mode & mode_mask); }
   // Kann von der Pipe gelesen werden?
   bool canReadFrom() const
      { return getPipeMode(mRead) == mRead; }
   // Kann auf die Pipe geschrieben werden?
   bool canWriteTo() const
      { return getPipeMode(mWrite) == mWrite; }

   // Warten auf Connect eines Pipe Clients (true wenn erfolgreich)
   bool waitForClient() const;
   // Client abhaengen
   void disconnectFromClient() const;
   // Ausgabepuffer vollends ausschreiben
   void flushBuffers() const;

   // Momentane Einstellung des Blocking/Nonblocking-Modus erfragen
   bool getWaitMode() const;
   // Einstellen des Blocking/Nonblocking-Modus (liefert false bei Fehler)
   bool setWaitMode(bool wait = true);

   // Lesen von der Pipe. Liefert Anzahl gelesener Bytes
   // oder -1, falls Pipe-Verbindung unterbrochen
   int read(void *buf, int buf_size);
   // Schreiben auf die Pipe. Liefert Anzahl geschriebener Bytes
   // oder -1, falls Pipe-Verbindung unterbrochen
   int write(const void *buf, int buf_size);

private:
   cString name, address;
   MODE pipe_mode;

};

#endif /*__INTERFACE__*/


// Implementierung cNamedPipe
// ===========================================================================

cNamedPipe::cNamedPipe(cString address_name, MODE mode, int ms_timeout)
{
   int pos = address_name.getPos(":");
   name = address_name.getMid(pos + 1);

   if ( pos > 0 ) {
      address = address_name.getLeft(pos);
   } else {
      address = ".";
   }

   pipe_mode = mode;

   #if defined __ECL_OS2__

      ULONG tmo = ms_timeout < 0 ? -1 : ms_timeout;
      APIRET rc = DosWaitNPipe(getFullName(), tmo);
      __ECL_ASSERT2__(!rc, ("OS/2: No pipe server to connect, err = %d", rc));
      if ( rc ) throw cErrNp(cErrNp::errConnectTimeout, getFullName());

      ULONG action = 0;
      ULONG open_mode = OPEN_SHARE_DENYNONE;
      switch ( getPipeMode() ) {
         case mRead:    open_mode |= OPEN_ACCESS_READONLY; break;
         case mWrite:   open_mode |= OPEN_ACCESS_WRITEONLY; break;
         case mDuplex:  open_mode |= OPEN_ACCESS_READWRITE; break;
      }

      rc = DosOpen(
         getFullName(),    // pipe name
         &handle,          // result handle
         &action,          // action taken by DosOpen
         0,                // logical file size
         FILE_NORMAL,      // file attribute
         FILE_OPEN,        // file open flags
         open_mode,        // file open mode
         NULL              // no extended attributes
      );

      __ECL_ASSERT2__(!rc, ("OS/2: Could not open pipe, err = %d", rc));
      if ( rc ) throw cErrNp(cErrNp::errConnect, getFullName());

   #elif defined __ECL_W32__

      DWORD tmo = ms_timeout < 0 ? NMPWAIT_WAIT_FOREVER : ms_timeout;
      BOOL ok = WaitNamedPipe(getFullName(), tmo);
      __ECL_ASSERT2__(ok, ("Win32: No pipe server to connect, err = %d", GetLastError()));
      if ( !ok ) throw cErrNp(cErrNp::errConnectTimeout, getFullName());

      DWORD access_mode = GENERIC_READ | GENERIC_WRITE;
      if ( mode == mRead ) access_mode &= ~GENERIC_WRITE;
      if ( mode == mWrite ) access_mode &= ~GENERIC_READ;

      handle = CreateFile(
         getFullName(),    // pipe name
         access_mode,      // access mode
         0,                // no sharing
         NULL,             // no security attributes
         OPEN_EXISTING,    // opens existing pipe
         0,                // default attributes
         NULL              // no template file
      );

      if ( handle == INVALID_HANDLE_VALUE ) {
         DbgError("Win32: Could not open pipe %s, err = %d", (const char *)getFullName(), GetLastError());
         throw cErrNp(cErrNp::errConnect, getFullName());
      }

   #endif

   if ( !setWaitMode() )
      throw cErrNp(cErrNp::errConnect, getFullName());
}

cNamedPipe::cNamedPipe(cString name, int in_buf_size, int out_buf_size)
{
   int pos = name.getPos(":");
   cNamedPipe::name = pos > 0 ? name.getMid(pos + 1) : name;
   cNamedPipe::address = ".";

   if ( in_buf_size && out_buf_size ) {
      pipe_mode = mDuplex;
   } else if ( in_buf_size ) {
      pipe_mode = mRead;
   } else if ( out_buf_size ) {
      pipe_mode = mWrite;
   } else {
      throw cErrNp(cErrNp::errCreate, getFullName());
   }

   #if defined __ECL_OS2__

      ULONG open_mode = 0;
      switch ( getPipeMode() ) {
         case mRead:    open_mode = NP_ACCESS_INBOUND; break;
         case mWrite:   open_mode = NP_ACCESS_OUTBOUND; break;
         case mDuplex:  open_mode = NP_ACCESS_DUPLEX; break;
      }

      APIRET rc = DosCreateNPipe(
         getFullName(),             // pipe name
         &handle,                   // result handle
         open_mode,                 // read/write access
         NP_TYPE_MESSAGE |          // message type pipe
         NP_READMODE_MESSAGE |      // message-read mode
         NP_WAIT |                  // blocking mode
         NP_UNLIMITED_INSTANCES,    // max. instances
         out_buf_size,              // output buffer size
         in_buf_size,               // input buffer size
         -1                         // client time-out
      );

      __ECL_ASSERT2__(!rc, ("OS/2: Could not create pipe, err = %d", rc));
      if ( rc ) throw cErrNp(cErrNp::errCreate, getFullName());

   #elif defined __ECL_W32__

      DWORD open_mode = 0;
      if ( canReadFrom() ) open_mode |= PIPE_ACCESS_INBOUND;
      if ( canWriteTo() ) open_mode |= PIPE_ACCESS_OUTBOUND;

      handle = CreateNamedPipe(
         getFullName(),             // pipe name
         open_mode,                 // read/write access
         PIPE_TYPE_MESSAGE |        // message type pipe
         PIPE_READMODE_MESSAGE |    // message-read mode
         PIPE_WAIT,                 // blocking mode
         PIPE_UNLIMITED_INSTANCES,  // max. instances
         out_buf_size,              // output buffer size
         in_buf_size,               // input buffer size
         INFINITE,                  // client time-out
         NULL                       // no security attribute
      );

      if ( handle == INVALID_HANDLE_VALUE ) {
         DbgError("Win32: Could not create pipe, err = %d", GetLastError());
         throw cErrNp(cErrNp::errCreate, getFullName());
      }

   #endif
}

cNamedPipe::~cNamedPipe()
{
   #if defined __ECL_OS2__
      DosClose(handle);
   #elif defined __ECL_W32__
      CloseHandle(handle);
   #endif
}

cString cNamedPipe::getFullName() const
{
   #if defined __ECL_OS2__
      cString prefix = (address == ".") ? cString("") : "\\\\" + address;
      return prefix + "\\pipe\\" + name;
   #elif defined __ECL_W32__
      return "\\\\" + address + "\\pipe\\" + name;
   #endif
}

bool cNamedPipe::waitForClient() const
{
   #if defined __ECL_OS2__
      APIRET rc = DosConnectNPipe(handle);
      __ECL_ASSERT2__(!rc, ("OS/2: Waiting for pipe client connect failed, err = %d", rc));
      return !rc;
   #elif defined __ECL_W32__
      BOOL ok = ConnectNamedPipe(handle, NULL);
      DWORD err = GetLastError();
      if ( !ok && err == ERROR_PIPE_CONNECTED ) return true;
      __ECL_ASSERT2__(ok, ("Win32: Waiting for pipe client connect failed, err = %d", err));
      return !!ok;
   #endif
}

void cNamedPipe::disconnectFromClient() const
{
   #if defined __ECL_OS2__
      APIRET rc = DosDisConnectNPipe(handle);
      __ECL_ASSERT2__(!rc, ("OS/2: Could not disconnect pipe, err = %d", rc));
      if ( rc ) throw cErrNp(cErrNp::errDisconnectFromClient, getFullName());
   #elif defined __ECL_W32__
      BOOL ok = DisconnectNamedPipe(handle);
      __ECL_ASSERT2__(ok, ("Win32: Could not disconnect pipe, err = %d", GetLastError()));
      if ( !ok ) throw cErrNp(cErrNp::errDisconnectFromClient, getFullName());
   #endif
}

void cNamedPipe::flushBuffers() const
{
   if ( !canWriteTo() )
      return;

   #if defined __ECL_OS2__
      APIRET rc = DosResetBuffer(handle);
      __ECL_ASSERT2__(!rc, ("OS/2: Could not flush buffers, err = %d", rc));
   #elif defined __ECL_W32__
      BOOL ok = FlushFileBuffers(handle);
      __ECL_ASSERT2__(ok, ("Win32: Could not flush buffers, err = %d", GetLastError()));
   #endif
}

bool cNamedPipe::getWaitMode() const
{
   #if defined __ECL_OS2__
      // ???
      return false;
   #elif defined __ECL_W32__
      DWORD state = 0;
      BOOL ok = GetNamedPipeHandleState(handle, &state, NULL, NULL, NULL, NULL, 0);
      __ECL_ASSERT2__(ok, ("Win32: Could not get wait mode, err = %d", GetLastError()));
      return !(state & PIPE_NOWAIT);
   #endif
}

bool cNamedPipe::setWaitMode(bool wait)
{
   #if defined __ECL_OS2__
      APIRET rc = DosSetNPHState(handle, NP_READMODE_MESSAGE | (wait ? NP_WAIT : NP_NOWAIT));
      __ECL_ASSERT2__(!rc, ("OS/2: Could not set wait mode, err = %d", rc));
      return !rc;
   #elif defined __ECL_W32__
      DWORD mode = PIPE_READMODE_MESSAGE | (wait ? PIPE_WAIT : PIPE_NOWAIT);
      BOOL ok = SetNamedPipeHandleState(handle, &mode, NULL, NULL);
      __ECL_ASSERT2__(ok, ("Win32: Could not set wait mode, err = %d", GetLastError()));
      return !!ok;
   #endif
}

int cNamedPipe::read(void *buf, int buf_size)
{
   #if defined __ECL_OS2__
      ULONG read_count = 0;
      APIRET rc = DosRead(handle, buf, buf_size, &read_count);
      if ( rc == ERROR_NO_DATA || read_count == 0 ) return -1;
      __ECL_ASSERT2__(!rc, ("OS/2: Could not read from pipe, err = %d", rc));
      if ( rc ) throw cErrNp(cErrNp::errRead, getFullName());
      return (int)read_count;
   #elif defined __ECL_W32__
      DWORD read_count = 0;
      BOOL ok = ReadFile(handle, buf, buf_size, &read_count, NULL);
      DWORD err = GetLastError();
      if ( !ok && err == ERROR_BROKEN_PIPE ) return -1;
      __ECL_ASSERT2__(ok, ("Win32: Could not read from pipe, err = %d", err));
      if ( !ok ) throw cErrNp(cErrNp::errRead, getFullName());
      return (int)read_count;
   #endif
}

int cNamedPipe::write(const void *buf, int buf_size)
{
   #if defined __ECL_OS2__
      ULONG write_count = 0;
      APIRET rc = DosWrite(handle, (void *)buf, buf_size, &write_count);
      if ( rc == ERROR_BROKEN_PIPE ) return -1;
      __ECL_ASSERT2__(!rc, ("OS/2: Could not write to pipe, err = %d", rc));
      if ( rc ) throw cErrNp(cErrNp::errWrite, getFullName());
      return (int)write_count;
   #elif defined __ECL_W32__
      DWORD write_count = 0;
      BOOL ok = WriteFile(handle, buf, buf_size, &write_count, NULL);
      DWORD err = GetLastError();
      if ( !ok && err == ERROR_BROKEN_PIPE ) return -1;
      __ECL_ASSERT2__(ok, ("Win32: Could not write to pipe, err = %d", GetLastError()));
      if ( !ok ) throw cErrNp(cErrNp::errWrite, getFullName());
      return (int)write_count;
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cNpClient
// ---------------------------------------------------------------------------
//
// cBase
//  +--cNpClient
//
// ===========================================================================

class __ECL_DLLEXPORT__ cNpClient : public cBase {

public:
   // Named-Pipe-Client anlegen
   cNpClient(cString address_name, cNamedPipe::MODE mode = cNamedPipe::mWrite, int ms_timeout = -1);

   // Lesen vom Pipe-Server. Liefert Anzahl gelesener Bytes
   // oder -1, falls Pipe-Verbindung unterbrochen
   int read(void *buf, int size);
   // Schreiben auf Pipe-Server. Liefert Anzahl geschriebener Bytes
   // oder -1, falls Pipe-Verbindung unterbrochen
   int write(const void *buf, int size);

private:
   cNamedPipe pipe;   // Named-Pipe, auf die zugegriffen wird

};

#endif /*__INTERFACE__*/


// Implementierung cNpClient
// ===========================================================================

cNpClient::cNpClient(cString address_name, cNamedPipe::MODE mode, int ms_timeout) :
   pipe(address_name, mode, ms_timeout)
{
   // ...
}

int cNpClient::read(void *buf, int size)
{
   return pipe.read(buf, size);
}

int cNpClient::write(const void *buf, int size)
{
   return pipe.write(buf, size);
}



#ifdef __INTERFACE__

// ===========================================================================
// Definition cNpServer
// ---------------------------------------------------------------------------
//
// cBase
//  +--cNpServer
//
// ===========================================================================

class __ECL_DLLEXPORT__ cNpServer : public cBase {

public:
   // Named-Pipe-Server anlegen
   cNpServer(cString name, int max_msg_size, int queue_size = 10, int in_buf_size = 2048);
   ~cNpServer();

   // Lesen von den Pipe-Clients. Liefert Anzahl gelesener Bytes
   int read(void *buf, int size);

   // ?????????????????????
   void block();

   typedef class /*__ECL_DLLEXPORT__*/ cQueue<void*> SRV_QUEUE;

private:
   #if defined __ECL_VCPP__
      #pragma warning(disable:4251)  /* Dummer Compiler, Saudummer */
   #endif

   SRV_QUEUE srv_queue;
   cNpSrvConnectThread *connect_thread;

   #if defined __ECL_VCPP__
      #pragma warning(default:4251)
   #endif

};

#endif /*__INTERFACE__*/


// Implementierung cNpServer
// ===========================================================================


   // cNpSrvReadThread
   // ----------------

   class cNpSrvReadThread : public cThread {

   public:

      cNpSrvReadThread(cNamedPipe *pipe, cNpServer::SRV_QUEUE *srv_queue, int max_msg_size) :
         cThread(tdAutoDel)
      {
         cNpSrvReadThread::pipe = pipe;
         cNpSrvReadThread::srv_queue = srv_queue;
         cNpSrvReadThread::max_msg_size = max_msg_size;
         start(teStart);
      }

      ~cNpSrvReadThread()
      {
         cerr << "SERVER: read thread self-terminated" << endl;
      }

      int onMain(void * /*extra*/)
      {
         char *buf = new0 char[sizeof(int) + max_msg_size];
         int bytes_read;

         while ( (bytes_read = pipe->read(buf + sizeof(int), max_msg_size)) >= 0 ) {
            *((int *)buf) = bytes_read;
            srv_queue->put((void *)buf);
            buf = new0 char[sizeof(int) + max_msg_size];
         }

         delete[] buf; // -TE- 02.03.2001 delete -> delete[]
         return 0;
      }

      void onLeave(int /*rc*/)
      {
         pipe->flushBuffers();
         pipe->disconnectFromClient();
         delete pipe;
      }

   private:
      cNamedPipe *pipe;
      cNpServer::SRV_QUEUE *srv_queue;
      int max_msg_size;

   };


   // cNpSrvConnectThread
   // -------------------

   #if defined __ECL_ICC__
      inline void EclDestructElements(cNamedPipe **elements, int count)
         { /* no destructor call needed */ }
   #endif

   class cNpSrvConnectThread : public cThread {

   public:
      cNpSrvConnectThread(cString name, cNpServer::SRV_QUEUE *srv_queue,
                          int max_msg_size, int in_buf_size, int out_buf_size) :
         cThread(tdNoAutoDel)
      {
         terminate = false;
         cNpSrvConnectThread::name = name;
         cNpSrvConnectThread::srv_queue = srv_queue;
         cNpSrvConnectThread::max_msg_size = max_msg_size;
         cNpSrvConnectThread::in_buf_size = in_buf_size;
         cNpSrvConnectThread::out_buf_size = out_buf_size;
         start(teStart);
      }

      ~cNpSrvConnectThread()
      {
         cerr << "SERVER: connection thread terminated" << endl;
      }

      int onMain(void * /*extra*/)
      {
         cList<cNamedPipe*, cNamedPipe*> open_pipes;

         while ( !terminate ) {
            cerr << "SERVER: Creating pipe " << name << endl;
            cNamedPipe *pipe = new0 cNamedPipe(name, in_buf_size, out_buf_size);
            pipe_created.set();
            cerr << "SERVER: Waiting for client to connect..." << endl;
            if ( pipe->waitForClient() && !terminate ) {
               cerr << "SERVER: Starting handler thread..." << endl;
               open_pipes.addTail(pipe);
               new0 cNpSrvReadThread(pipe, srv_queue, max_msg_size);
            } else {
               delete pipe;
            }
         }

         IPOSITION it = open_pipes.getHeadPosition();
         while ( it != NULL ) {
            cNamedPipe *pipe = open_pipes.getNext(it);
            pipe->setWaitMode(false);
         }

         return 0;
      }

      void waitUntilReady()
      {
         pipe_created.wait();
      }

      void terminateThread()
      {
         cNamedPipe::MODE pipe_mode = cNamedPipe::mDuplex;
         if ( in_buf_size && !out_buf_size ) pipe_mode = cNamedPipe::mWrite;
         if ( !in_buf_size && out_buf_size ) pipe_mode = cNamedPipe::mRead;

         terminate = true;
         cNamedPipe shutdown_pipe(name, pipe_mode, 1000);
      }

   private:
      cString name;
      bool terminate;
      int max_msg_size;
      int in_buf_size, out_buf_size;
      cNpServer::SRV_QUEUE *srv_queue;
      cEventSem pipe_created;

   };


cNpServer::cNpServer(cString name, int max_msg_size, int queue_size, int in_buf_size) :
   srv_queue(queue_size)
{
   connect_thread = new0 cNpSrvConnectThread(name, &srv_queue, max_msg_size, in_buf_size, 0);
   connect_thread->waitUntilReady();
}

cNpServer::~cNpServer()
{
   connect_thread->terminateThread();
   connect_thread->waitFor(cThread::teEnd);
   delete connect_thread;
   cerr << "SERVER: pipe server terminated" << endl;
}

int cNpServer::read(void *buf, int size)
{
   char *ptr = (char *)srv_queue.get();
   int bytes_read = -1;

   if ( ptr != NULL ) {
      bytes_read = *((int *)ptr);
      memcpy(buf, ptr + sizeof(int), min(size, bytes_read));
   }

   return bytes_read;
}

void cNpServer::block()
{
   connect_thread->waitFor(cThread::teEnd);
}




#ifdef __Test_eb_npipe__

   #include <conio.h>

   typedef struct { char c[2]; int getSize() const { return 2; } } CMSG;

   static void PipeClient(cString name_address)
   {
      cerr << "Waiting for server to come up..." << endl;
      cEventSem("NPipeServer", cEventSem::semOpenOrCreate).wait();

      cerr << "PIPE CLIENT for " << name_address << " RUNNING" << endl;

      while ( 1 ) {
         cNpClient pipe_client(name_address);
         CMSG cmsg = { "?" };
         while ( 1 ) {
            cmsg.c[0] = _getch();
            if ( pipe_client.write(&cmsg, sizeof cmsg) < 0 )
               break;
         }
         cerr << "Pipe broken, trying to reconnect..." << endl;
      }
   }

   static void PipeServer(cString srv_name)
   {
      cEventSem client_sync("NPipeServer", cSema::semOpenOrCreate);
      client_sync.set();

      cerr << "PIPE SERVER for " << srv_name << " RUNNING" << endl;
      cNpServer pipe_server(srv_name, sizeof(CMSG));

      CMSG cmsg;
      while ( pipe_server.read(&cmsg, sizeof cmsg) >= 0 ) {
         cerr << "got: " <<  cmsg.c[0] << endl;
         if ( cmsg.c[0] == '*' )
            return;
      }

      cerr << "Server pipe broken, terminating..." << endl;
   }

   int main(int argc, char *argv[])
   {
      cout << "Named Pipe Example" << endl;

      cString name = "pfeife";
      if ( argc > 1 )
         name = argv[1];

      try {
         if ( name.getPos(":") > 0 ) {
            PipeClient(name);
         } else {
            PipeServer(name);
         }
      } catch ( const cErrBase& err ) {
         cerr << "Error " << err << endl;
      }

      return 0;
   }

#endif

