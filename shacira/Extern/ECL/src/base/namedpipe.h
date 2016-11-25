// ===========================================================================
// base/namedpipe.h                                             ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
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

#ifndef __ecl_namedpipe__
#define __ecl_namedpipe__


// Base class header
#include "base/base.h"

// Other ECL headers
#include "base/error.h"
#include "base/string.h"
#include "base/queue.h"

          
namespace ecl {


// Forward-Deklarationen
// ===========================================================================

class cNpSrvConnectThread;


// ===========================================================================
// Definition cErrNp
// ---------------------------------------------------------------------------
//
//! Named Pipes Fehlerklasse.
//! @ingroup namedpipe
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

      //! Fehler
      errCreate      = errBase+errError , //!< Kann Pipe-Instanz nicht erzeugen
      errConnect                        , //!< Fehler beim Connect zum Server
      errConnectTimeout                 , //!< Pipe-Server nicht verfuegbar
      errRead                           , //!< Fehler beim Lesen von Pipe
      errWrite                          , //!< Fehler beim Schreiben auf Pipe
      errConnectWithClient              , //!< Fehler beim Connect mit Client
      errDisconnectFromClient             //!< Fehler beim Disconnect vom Client

   };

};


// ===========================================================================
// Definition cNamedPipe
// ---------------------------------------------------------------------------
//
//! Verwalten einer Named Pipe im Message-Mode.
//! @ingroup namedpipe
//
// cBase
//  +--cOsBase
//      +--cNamedPipe
//
// ===========================================================================

class __ECL_DLLEXPORT__ cNamedPipe : public cOsBase {

public:
   enum MODE { mRead = 0x01, mWrite = 0x02, mDuplex = 0x03 };

   //! Oeffnen einer Named Pipe im Client-Mode
   cNamedPipe(cString address_name, MODE mode, int ms_timeout = -1);
   //! Erzeugen einer Named Pipe im Server-Mode (auf lokalem Rechner)
   cNamedPipe(cString name, int in_buf_size, int out_buf_size);
   //! Schliessen der Named Pipe
   ~cNamedPipe();

   //! Name der Pipe erfragen
   cString getName() const
      { return name; }
   //! Adresse (Rechnername) der Pipe erfragen
   cString getAddress() const
      { return address; }
   //! Systemspezifischen Namen ermitteln
   cString getFullName() const;

   //! Modus erfragen
   MODE getPipeMode(MODE mode_mask = mDuplex) const
      { return (MODE)(pipe_mode & mode_mask); }
   //! Kann von der Pipe gelesen werden?
   bool canReadFrom() const
      { return getPipeMode(mRead) == mRead; }
   //! Kann auf die Pipe geschrieben werden?
   bool canWriteTo() const
      { return getPipeMode(mWrite) == mWrite; }

   //! Warten auf Connect eines Pipe Clients (true wenn erfolgreich)
   bool waitForClient() const;
   //! Client abhaengen
   void disconnectFromClient() const;
   //! Ausgabepuffer vollends ausschreiben
   void flushBuffers() const;

   //! Momentane Einstellung des Blocking/Nonblocking-Modus erfragen
   bool getWaitMode() const;
   //! Einstellen des Blocking/Nonblocking-Modus (liefert false bei Fehler)
   bool setWaitMode(bool wait = true);

   //! Lesen von der Pipe. Liefert Anzahl gelesener Bytes
   //! oder -1, falls Pipe-Verbindung unterbrochen
   int read(void *buf, int buf_size);
   //! Schreiben auf die Pipe. Liefert Anzahl geschriebener Bytes
   //! oder -1, falls Pipe-Verbindung unterbrochen
   int write(const void *buf, int buf_size);

private:
   cString name, address;
   MODE pipe_mode;

};


// ===========================================================================
// Definition cNpClient
// ---------------------------------------------------------------------------
//
//! Einfacher Named Pipe Client.
//! @ingroup namedpipe
//
// cBase
//  +--cNpClient
//
// ===========================================================================

class __ECL_DLLEXPORT__ cNpClient {

public:
   //! Named-Pipe-Client anlegen
   cNpClient(cString address_name, cNamedPipe::MODE mode = cNamedPipe::mWrite, int ms_timeout = -1);

   //! Lesen vom Pipe-Server. Liefert Anzahl gelesener Bytes
   //! oder -1, falls Pipe-Verbindung unterbrochen
   int read(void *buf, int size);
   //! Schreiben auf Pipe-Server. Liefert Anzahl geschriebener Bytes
   //! oder -1, falls Pipe-Verbindung unterbrochen
   int write(const void *buf, int size);

private:
   cNamedPipe pipe;   //!< Named-Pipe, auf die zugegriffen wird

};


// ===========================================================================
// Definition cNpServer
// ---------------------------------------------------------------------------
//
//! Multithreaded Named Pipe Server.
//! @ingroup namedpipe
//
// cBase
//  +--cNpServer
//
// ===========================================================================

class __ECL_DLLEXPORT__ cNpServer {

public:
   //! Named-Pipe-Server anlegen
   cNpServer(cString name, int max_msg_size, int queue_size = 10, int in_buf_size = 2048);
   ~cNpServer();

   //! Lesen von den Pipe-Clients. Liefert Anzahl gelesener Bytes
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


}; // namespace ecl


#endif // __ecl_namedpipe__

