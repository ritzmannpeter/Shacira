// ===========================================================================
// base/namedpipe.cpp                                           ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================


// Interface header
#include "base/namedpipe.h"

// Other ECL headers
#include "base/thread.h"
#include "base/list.h"

// Platform dependant headers
#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
#elif defined __ECL_W32__
   #include <windows.h>
#endif


/**
 * @defgroup namedpipe Named Pipes
 * @ingroup ipc
 */




namespace ecl {




// Konstanten der Masken fuer __ECL_ASSERT__ (identifizieren Pipe-Modul)
const unsigned long IPC_ERROR = cBase::dbgIpc | cBase::dbgError | cBase::dbgAssert;
const unsigned long IPC_WARN  = cBase::dbgIpc | cBase::dbgWarn;
const unsigned long IPC_INFO  = cBase::dbgIpc | cBase::dbgInfo;

// Implementierung cErrNp
// ===========================================================================

cErrNp::cErrNp(int err, const char *name) :
   cErrBase(err)
{
   setParam(0, name);
}




// Implementierung cNamedPipe
// ===========================================================================

cNamedPipe::cNamedPipe(cString address_name, MODE mode, int ms_timeout)
{
   __ECL_STATISTIC__("cNamedPipe")

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
         0                 // no extended attributes
      );

      __ECL_ASSERT2__(!rc, ("OS/2: Could not open pipe, err = %d", rc));
      if ( rc ) throw cErrNp(cErrNp::errConnect, getFullName());

   #elif defined __ECL_W32__

      DWORD tmo = ms_timeout < 0 ? NMPWAIT_WAIT_FOREVER : ms_timeout;
      BOOL ok = WaitNamedPipe(getFullName(), tmo);
      __ECL_ASSERT_PRINTF__(ok, IPC_ERROR, ("Win32: No pipe server to connect, err = %d", GetLastError()));
      if ( !ok ) throw cErrNp(cErrNp::errConnectTimeout, getFullName());

      DWORD access_mode = GENERIC_READ | GENERIC_WRITE;
      if ( mode == mRead ) access_mode &= ~GENERIC_WRITE;
      if ( mode == mWrite ) access_mode &= ~GENERIC_READ;

      handle = CreateFile(
         getFullName(),    // pipe name
         access_mode,      // access mode
         0,                // no sharing
         0,                // no security attributes
         OPEN_EXISTING,    // opens existing pipe
         0,                // default attributes
         0                 // no template file
      );

      if ( handle == INVALID_HANDLE_VALUE ) {
         __ECL_RELEASE_PRINTF__(IPC_ERROR, ("Win32: Could not open pipe %s, err = %d", (const char *)getFullName(), GetLastError()));
         throw cErrNp(cErrNp::errConnect, getFullName());
      }

   #endif

   if ( !setWaitMode() )
      throw cErrNp(cErrNp::errConnect, getFullName());
}

cNamedPipe::cNamedPipe(cString name, int in_buf_size, int out_buf_size)
{
   __ECL_STATISTIC__("cNamedPipe")

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
         0                          // no security attribute
      );

      if ( handle == INVALID_HANDLE_VALUE ) {
         __ECL_RELEASE_PRINTF__(IPC_ERROR, ("Win32: Could not create pipe, err = %d", GetLastError()));
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
      BOOL ok = ConnectNamedPipe(handle, 0);
      DWORD err = GetLastError();
      if ( !ok && err == ERROR_PIPE_CONNECTED ) return true;
      __ECL_ASSERT_PRINTF__(ok, IPC_ERROR, ("Win32: Waiting for pipe client connect failed, err = %d", err));
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
      __ECL_ASSERT_PRINTF__(ok, IPC_ERROR, ("Win32: Could not disconnect pipe, err = %d", GetLastError()));
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
      __ECL_ASSERT_PRINTF__(ok, IPC_ERROR, ("Win32: Could not flush buffers, err = %d", GetLastError()));
   #endif
}

bool cNamedPipe::getWaitMode() const
{
   #if defined __ECL_OS2__
      // ???
      return false;
   #elif defined __ECL_W32__
      DWORD state = 0;
      BOOL ok = GetNamedPipeHandleState(handle, &state, 0, 0, 0, 0, 0);
      __ECL_ASSERT_PRINTF__(ok, IPC_ERROR, ("Win32: Could not get wait mode, err = %d", GetLastError()));
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
      BOOL ok = SetNamedPipeHandleState(handle, &mode, 0, 0);
      __ECL_ASSERT_PRINTF__(ok, IPC_ERROR, ("Win32: Could not set wait mode, err = %d", GetLastError()));
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
      BOOL ok = ReadFile(handle, buf, buf_size, &read_count, 0);
      DWORD err = GetLastError();
      if ( !ok && err == ERROR_BROKEN_PIPE ) return -1;
      __ECL_ASSERT_PRINTF__(ok, IPC_ERROR, ("Win32: Could not read from pipe, err = %d", err));
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
      BOOL ok = WriteFile(handle, buf, buf_size, &write_count, 0);
      DWORD err = GetLastError();
      if ( !ok && err == ERROR_BROKEN_PIPE ) return -1;
      __ECL_ASSERT_PRINTF__(ok, IPC_ERROR, ("Win32: Could not write to pipe, err = %d", GetLastError()));
      if ( !ok ) throw cErrNp(cErrNp::errWrite, getFullName());
      return (int)write_count;
   #endif
}




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
         __ECL_RELEASE_TEXT__(IPC_INFO, "cNpSrvReadThread: read thread self-terminated");
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
         __ECL_RELEASE_TEXT__(IPC_INFO, "cNpSrvConnectThread: connection thread terminated");
      }

      int onMain(void * /*extra*/)
      {
         cList<cNamedPipe*, cNamedPipe*> open_pipes;

         while ( !terminate ) {
            __ECL_RELEASE_PRINTF__(IPC_INFO, ("cNpSrvConnectThread: Creating pipe %s", (const char *)name));
            cNamedPipe *pipe = new0 cNamedPipe(name, in_buf_size, out_buf_size);
            pipe_created.set();
            __ECL_RELEASE_TEXT__(IPC_INFO, "cNpSrvConnectThread: Waiting for client to connect...");
            if ( pipe->waitForClient() && !terminate ) {
               __ECL_RELEASE_TEXT__(IPC_INFO, "cNpSrvConnectThread: Starting handler thread...");
               open_pipes.addTail(pipe);
               new0 cNpSrvReadThread(pipe, srv_queue, max_msg_size);
            } else {
               delete pipe;
            }
         }

         IPOSITION it = open_pipes.getHeadPosition();
         while ( it != 0 ) {
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
   __ECL_RELEASE_TEXT__(IPC_INFO, "cNpSrvConnectThread: pipe server terminated");
}

int cNpServer::read(void *buf, int size)
{
   char *ptr = (char *)srv_queue.get();
   int bytes_read = -1;

   if ( ptr != 0 ) {
      bytes_read = *((int *)ptr);
      memcpy(buf, ptr + sizeof(int), min(size, bytes_read));
   }

   return bytes_read;
}

void cNpServer::block()
{
   connect_thread->waitFor(cThread::teEnd);
}



/*
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
*/


}; // namespace ecl


