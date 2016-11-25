// ===========================================================================
// et_concli.cpp                                         Remote Console Client
//                                                        Autor: Markus Wuertz
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
// cBase
// |
// +--cConClient
// |
// +--cThread
//    |
//    +--cWatchDog
//
// ===========================================================================


#include "tom/et_concli.hpp"
#include "tom/et_conser.hpp"

#include "base/eb_err.hpp"

#include <conio.h>


// Voreingestellte Namen
//
#define ENV_SERVER     "CON_SERVER"
#define DEFAULT_SERVER "ConServer"
#define ENV_CLIENT     "CON_CLIENT"
#define DEFAULT_CLIENT "ConClient"

#define MAX_MESSAGE_LEN    256
// Anzahl erlaubter Zwillings-Clients (Name + lfd.Nummer)
#define MAX_CLIENT_TWINS   16


#ifdef __INTERFACE__

#include "base/eb_base.hpp"
#include "base/eb_str.hpp"
#include "base/eb_msg.hpp"
#include "base/eb_thread.hpp"

// ---------------------------------------------------------------------------
// Deklaration cWatchDog

class __ECL_DLLEXPORT__ cWatchDog : public cThread {
   cMsgRecipient alarm_box;   // Alarmempfaenger mit garantierter Existenz
   int alarm_msg_id;          // Alarmmeldung (nur Id)

   long sleep_ms;             // Zeit zwischen zwei Kontrollen
   long counter;              // Zaehler der beiFuss-Aufrufe
   bool ignore;               // Alarm unterbinden

   bool is_alive;             // Flag zum Beenden des Thread

public:
   cWatchDog( cString msg_box, int msg_id, long intervall_ms=1000 );
   ~cWatchDog();

   int onMain( void *extra );

   void beiFuss() { counter++; }
   void sitz() { ignore = true; }
   void fass() { ignore = false; }
};

#endif /*__INTERFACE__*/


// ---------------------------------------------------------------------------
// Implementierung cWatchDog

cWatchDog::cWatchDog( cString box, int msg_id, long intervall_ms ) :
   alarm_box( box )
{
   alarm_msg_id = msg_id;
   sleep_ms = intervall_ms;
   counter = 0;
   ignore = false;

   is_alive = true;
   start();
}

cWatchDog::~cWatchDog()
{
   is_alive = false;
   waitFor();
}

int cWatchDog::onMain( void * /*extra*/ )
{
   long old_counter;

   while ( is_alive ) {
      //cerr << ".";
      old_counter = counter;
      sleep( sleep_ms );
      if ( !ignore && counter == old_counter ) {
         alarm_box.send( cMsg(alarm_msg_id) );
      }
   }

   return 0;
}


// ---------------------------------------------------------------------------
// Deklaration cConClient

#ifdef __INTERFACE__

class __ECL_DLLEXPORT__ cConClient : public cBase {
   cWatchDog      *lassie;    // Wachhund

   cMsgBox        *inbox;     // Client
   cMsgRecipient  *outbox;    // Server

   cString server_name;
   cString client_name;

   typedef const char * CCP;  // fuer tippfreundlichen cast

   enum WAIT { DONT_WAIT, PLEASE_WAIT };

public:
   // Zustand des Clients
   enum STATE {
      stLogout=0,          // normaler Betrieb
      stLogin=1,         // warten auf Login
      stEnd=99             // Programmende
   } state;

   // Meldungen, die der Client vom Server empfangen kann
   enum MESSAGES {
      msgPuts=20,       // <string>\0     - Ausgabe
      msgGetsReq,       // [buffersize]   - Eingabe (cgets-style)
      msgLoginAck,      //                - Bestaetigung fuer msgLogin
      msgLogoutAck,     //                - Bestaetigung fuer msgLogout
      msgServerLost,    //                - Server hat jetzt anderen Client :-(
      msgWauWau         //                - Alarm vom Wachhund
   };

   cConClient( cString in, cString out );
   virtual ~cConClient();

   // Meldungsschleife
   void onlineLoop();
   // Eingabeschleife
   void offlineLoop();
   // Zustand des Client abfragen
   STATE getState() { return state; }

private:
   // Empfangsfunktion
   bool /*ok*/ Receive( cMsg &msg, WAIT wait );

   // sichere Sendefunktion(en)
   bool /*ok*/ safeSend( cMsg msg, bool use_as_ping = false );
   // ... mit Messagekonstruktion (aber ohne Ping-Flag)
   bool /*ok*/ safeSend( int msg_id )
   { return safeSend( cMsg(msg_id) ); }
   bool /*ok*/ safeSend( int msg_id , const char *string )
   { return safeSend( cMsg(msg_id,strlen(string)+1,string) ); }
   bool /*ok*/ safeSend( int msg_id , const char *buffer, int size )
   { return safeSend( cMsg(msg_id,size,buffer) ); }

   int OS_PutS( const char *str);
   char *OS_GetS( char *str );

   // vorhandene Meldungen verwerfen
   void clearBox();
   // auf Antwort vom Server warten
   bool /*ok*/ waitForReply( int msg_id );

   // an Server anmelden
   void loginServer( cString server );
   // von Server abmelden
   void logoutServer();

   // Befehle an den Client auswerten
   void localCommand( const char *cmd );
};
#endif /*__INTERFACE__*/


// ---------------------------------------------------------------------------
// Implementierung cConClient

cConClient::cConClient( cString in, cString out)
{
   //cBase::setDebugMask( cBase::getDebugMask() | cBase::dbgInfo );
   if ( out.getLength() ) {
      server_name = out;
   } else if ( getenv(ENV_SERVER) ) {
      server_name = getenv(ENV_SERVER);
   } else {
      server_name = DEFAULT_SERVER;
   }

   if ( in.getLength() ) {
      client_name = in;
   } else if ( getenv(ENV_CLIENT) ) {
      client_name = getenv(ENV_CLIENT);
   } else {
      client_name = DEFAULT_CLIENT;
   }

   cString base_name(client_name);
   int try_counter = 0;

   inbox = NULL;
   do {
      try {
         inbox = new cMsgBox( (CCP)client_name,16,MAX_MESSAGE_LEN );
      } catch (cErrBase& err) {
         if ( err == cErrMsg::errCreateChannel /*WinNT*/ ) {
            //err == cErrMsg::errSendToChannel /*Win95*/ ||
            if ( ++try_counter >= MAX_CLIENT_TWINS ) {
               // FEHLER AUSGEBEN
               throw;
            }
            inbox = NULL;
            client_name = base_name + Str(try_counter);
         } else {
            cerr << "Error: " << err << endl;
            throw;
         }
      }

   } while ( inbox==NULL );

   outbox = NULL;
   loginServer( server_name );

   lassie = new cWatchDog( client_name, msgWauWau );
}


cConClient::~cConClient()
{
   logoutServer();
   delete lassie;
   delete inbox;
}


// ---------------------------------------------------------------------------
// Systemabhaenigige Ein/Ausgabe

int cConClient::OS_PutS(const char *str)
{
   #if defined(__ECL_OS2__)

      return fputs( str , stdout ); /* Haeh? */

   #elif defined(__ECL_W32__)

      return cputs(str);

   #else

      return cputs( str );

   #endif
}


char *cConClient::OS_GetS(char *str)
{
   #if defined(__ECL_OS2__)

      fflush( stdout );
      return _cgets( str );

   #elif defined(__ECL_W32__)

      return _cgets( str );

   #else

      return cgets( str );

   #endif
}


// ---------------------------------------------------------------------------
// ... Meldungen senden und empfangen (Low-Level)

bool cConClient::safeSend( cMsg msg, bool use_as_ping )
{
   //if ( outbox == NULL ) {
   //   DbgError("%s: no server", (CCP)client_name);
   //}

   try {
      DbgInfo( "%s: send Msg(id=%d, %p, %d)", (CCP)client_name,
               msg.getMsgId(), msg.getData(), msg.getDataLen() );
      outbox->send( msg );
   } catch (cErrBase& err) {
      if ( err == cErrMsg::errSendToChannel /*Win95*/ ||
           err == cErrMsg::errOpenChannel /*WinNT*/ ) {
         if ( use_as_ping ) {
            DbgError("%s: server %s not found", (CCP)client_name, (CCP)server_name );
         } else {
            DbgError("%s: server %s lost", (CCP)client_name, (CCP)server_name );
         }
         delete outbox;
         outbox = NULL;
         state = stLogout;
         return false;
      } else {
         cerr << "Error: " << err << endl;
         throw;
      }
   }
   return true;
}


bool cConClient::Receive( cMsg &msg, WAIT wait )
{
   inbox->setWait( wait == PLEASE_WAIT );
   msg = inbox->receive();

   if ( msg.isEmpty () ) {
      DbgInfo( "%s: receive Msg(emtpy)", (CCP)client_name );
   } else {
      DbgInfo( "%s: receive Msg(id=%d, %p, %d)", (CCP)client_name,
               msg.getMsgId(), msg.getData(), msg.getDataLen() );
   }

   return !msg.isEmpty();
}


// ---------------------------------------------------------------------------
// ... Hicks-Level-Kommunikation

void cConClient::clearBox()
{
   cMsg trash;

   while ( Receive(trash, DONT_WAIT) ) {
      DbgInfo("... removed");
   }
}


bool cConClient::waitForReply( int msg_id )
{
   cMsg msg;

   for ( int retry = 1; retry <= 5; retry++ ) {

      if ( Receive(msg, DONT_WAIT) ) {
         if ( msg.getMsgId() == msg_id ) {
            return true;
         } else {
            retry--;
            DbgError( "%s: message %d ignored (%d expected)",
                      (CCP)client_name, msg.getMsgId(), msg_id );
         }
      } else {
         cThread::sleep(200);
      }
   }
   DbgError( "%s: timeout (%d expected)", (CCP)client_name, msg_id );
   return false;
}


void cConClient::loginServer( cString server )
{
   state = stLogout;
   server_name = server;
   delete outbox;
   outbox = new cMsgRecipient( server_name );

   clearBox();

   if ( safeSend( cMsg(cConServer::msgLogin, client_name.getLength()+1, (CCP)client_name), true ) &&
        waitForReply( cConClient::msgLoginAck ) ) {
      cout << client_name << ": connection to " << server_name << endl;
      state = stLogin;
   } else {
      DbgError("%s: login to %s failed", (CCP)client_name, (CCP)server_name );
      delete outbox;
      outbox = NULL;
   }
}


void cConClient::logoutServer()
{
   if (outbox) {
      safeSend( cConServer::msgLogout );
      waitForReply( cConClient::msgLogoutAck );
      delete outbox;
      outbox = NULL;
   };
   state = stLogout;
}


void cConClient::localCommand( const char *cmd )
{
   if ( !stricmp(cmd,"exit") ) {
      logoutServer();
      state = stEnd;
   } else if ( !stricmp(cmd,"logout") ) {
      logoutServer();
   } else if ( !strnicmp(cmd,"login",5) ) {
      logoutServer();
      if (cmd[5] == ' ') {
         loginServer( cString(cmd+6) );
      } else {
         loginServer( server_name );
      }
   } else if ( !stricmp(cmd,"status") ) {
      cConDirectory condir;
      cString name;
      time_t timedate;

      cout << "this client:    " << client_name << endl
           << "current server: " << server_name << endl
           << "available server:" << endl;

      int pos = condir.rewind();
      while (pos) {
         name = condir.getNext(pos, timedate);
         cout << "   " << name << " --- " << ctime(&timedate) << endl;
      }
   } else {
      cout << "console client local commands:" << endl
           << "  (+++ is the escape sequence to local commands)" << endl
           << "  login [<servername>]" << endl
           << "  logout" << endl
           << "  dir" << endl
           << "  status" << endl
           << "  exit" << endl
           << "  help / ? / -h / rumpelstilzchen" << endl;
   }
}


void cConClient::offlineLoop()
{
   char buffer[80];

   while ( state == stLogout ) {
      cerr << "[CONSOLE CLIENT LOCAL COMMAND MODE] ";
      buffer[0] = sizeof(buffer)-3;
      OS_GetS( buffer );
      if ( buffer[2] != '\0' ) localCommand( buffer+2 );
   }
}


void cConClient::onlineLoop()
{
   cMsg msg;
   char buffer[260];
   bool message_ready = false;

   while ( state == stLogin ) {
      lassie->beiFuss();
      if ( !message_ready ) Receive( msg, PLEASE_WAIT );
      message_ready = false;
      switch ( msg.getMsgId() ) {
      case msgPuts: OS_PutS( (char *)msg.getData() );
         break;
      case msgGetsReq:
         buffer[0] = *(char *)msg.getData();
         DbgInfo("{%d%}",((char *)msg.getData())[1]);

         do {
            lassie->sitz();
            OS_GetS( buffer );
            lassie->fass();
            // gab es Meldungen, waehrend auf Eingaben gewartet wurde?
            message_ready = Receive(msg, DONT_WAIT);
            if ( !strncmp(buffer+2,"+++",3) ) {
               localCommand( buffer+5 );
            }
         } while ( !message_ready && !strncmp(buffer+2,"+++",3) && state == stLogin );
         if ( (!message_ready || msg.getMsgId() != msgServerLost) && state == stLogin ) {
            // nur senden, wenn sich der Server nicht abgemeldet hat!
            safeSend( cConServer::msgGetsReply, buffer+2 );
         }
         break;
      case msgWauWau:
         DbgError("%s: Watchdog ...", (CCP)client_name );
         if ( outbox->ping() ) break;
         DbgError("%s: WauWau !!!", (CCP)client_name );
         // msgWauWau faellt in msgServerLost rein ...
      case msgServerLost:
         DbgError("%s: server %s gone to hell", (CCP)client_name, (CCP)server_name );
         delete outbox;
         outbox = NULL;
         state = stLogout;
         break;
      case msgLoginAck:
      case msgLogoutAck:
         DbgError("%s: unexpected message id=%d", (CCP)client_name,msg.getMsgId() );
         break;
      default:
         DbgError("%s: unknown message id=%d", (CCP)client_name,msg.getMsgId() );
         break;
      }
   }
}



