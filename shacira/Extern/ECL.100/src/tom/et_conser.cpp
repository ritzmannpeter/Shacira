// ===========================================================================
// et_conser.cpp                                         Remote Console Server
//                                                        Autor: Markus Wuertz
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
// cBase
//    |
//    +--cConServer
//    |
//    +--cConDirectory
//
// ===========================================================================


#include "tom/et_conser.hpp"
#include "tom/et_concli.hpp"


// Voreingestellter Servername
//
#define ENV_SERVER      "CON_SERVER"
#define DEFAULT_SERVER  "ConServer"

#define MAX_MESSAGE_LEN    256
// Anzahl erlaubter Zwillings-Server (Name + lfd.Nummer)
#define MAX_SERVER_TWINS   16


// Name des Verzeichnisses im Shared Memory
#define SHMEM_NAME         "RemoteConsole"

#ifdef __INTERFACE__

#include "base/eb_base.hpp"
#include "base/eb_msg.hpp"
#include "base/eb_str.hpp"
#include "base/eb_shmem.hpp"
#include "time.h"

#endif /*__INTERFACE__*/


// ---------------------------------------------------------------------------
// Deklaration cConDirectory

#ifdef __INTERFACE__

// Anzahl der Eintraege im Serververzeichnis
#define MAX_DIR_SIZE       32
// Signifikante Stellen in einem Namen (incl. \0)
#define MAX_NAME_LEN       32

class __ECL_DLLEXPORT__ cConDirectory : public cBase {
#if defined __ECL_ICC__
public:
#endif
   struct ENTRY {
      char name[MAX_NAME_LEN];
      time_t timestamp;
   };
   struct DIRECTORY {
      int size;
      ENTRY entry[MAX_DIR_SIZE];
   };
   typedef int POSITION;

   cSharedMem shmem; // Shared Memory mit Verzeichnis
   DIRECTORY *dir;   // Zeiger auf den Shared Memory

public:
   cConDirectory();

   // Eintrag in Verzeichnis vornehmen
   bool newEntry( cString name, time_t timestamp );
   // Eintrag aus Verzeichnis loeschen
   bool delEntry( cString name );

   // Ersten Eintrag auswaehlen (0=kein Eintrag)
   int rewind() { return findNext(1); }
   // Naechsten Eintrag lesen (0=kein Eintrag mehr)
   cString getNext( int& pos, time_t& timestamp );

private:
   // nach Name suchen, liefert Index oder -1
   int Lookup( cString name );
   // Index des naechsten verwendeten Eintrags oder -1
   int findNext( int pos );

};

#endif /*__INTERFACE__*/


cConDirectory::cConDirectory() :
   shmem( SHMEM_NAME, cSharedMem::memOpenOrCreate, sizeof(DIRECTORY) )
{
   dir = (DIRECTORY*)shmem.getAdr();
   // Erstinitialisierung
   if (shmem.getCreationMode()==cSharedMem::cmSharedCreated) {
      dir->size = MAX_DIR_SIZE;
      for (int i=0; i<dir->size; i++) {
         dir->entry[i].name[0] = '\0';
      }
   }
}

int cConDirectory::Lookup(cString name)
{
   for (int i=0; i < dir->size; i++) {
      if (cString(dir->entry[i].name) == name) {
         return i;
      }
   }
   return -1;
}

int cConDirectory::findNext( int pos )
{
   while ( pos <= dir->size ) {
      if (dir->entry[pos-1].name[0] != '\0') return pos;
      pos++;
   }
   return 0;
}

cString cConDirectory::getNext(int& pos, time_t &timestamp)
{
   if (!pos) return pos;

   cString name = dir->entry[pos-1].name;
   timestamp = dir->entry[pos-1].timestamp;

   pos = findNext(pos+1);
   return name;
}

// false falls name bereits vergeben oder Verzeichnis voll ist
bool cConDirectory::newEntry(cString name, time_t timestamp)
{
   int pos;
   name = name.getLeft(MAX_NAME_LEN-1);

   if (Lookup(name) != -1) return false;     // schon drin
   if ((pos=Lookup("")) == -1) return false; // kein freier Eintrag mehr

   strcpy(dir->entry[pos].name, (const char *)name);
   dir->entry[pos].timestamp = timestamp;
   return true;
}

// false falls name nicht gefunden
bool cConDirectory::delEntry(cString name)
{
   int pos;
   name = name.getLeft(MAX_NAME_LEN-1);

   if ((pos=Lookup(name)) == -1) return false;  // nicht drin

   dir->entry[pos].name[0] = '\0';
   return true;
}


// ---------------------------------------------------------------------------
// Deklaration cConServer

#ifdef __INTERFACE__

class __ECL_DLLEXPORT__ cConServer : public cBase {
   cMsgBox        *inbox;
   cMsgRecipient  *outbox;

   cString server_name;
   cString client_name;

   cConDirectory condir;

   char last_line[256];

   typedef const char * CCP;  // fuer tippfreundlichen cast

public:
   enum {
      // 10..19 - Meldungen vom Client an den Server
      msgLogin=10,   // <clientname>\0    - Client meldet sich an
      msgLogout,     //                   - Client meldet sich ab
      msgGetsReply   // <string>\0        - Antwort auf ein gets-Anforderung
   };

   cConServer( cString name = NULL );
   virtual ~cConServer();

   char *cgets( char *str );
   int cputs( const char *str );

private:
   // Empfangsfunktion
   bool /*ok*/ Receive( cMsg &msg );

   // sichere Sendefunktion(en)
   bool /*ok*/ safeSend( cMsg msg );
   // ... mit Messagekonstruktion
   bool /*ok*/ safeSend( int msg_id )
   { return safeSend( cMsg(msg_id) ); }
   bool /*ok*/ safeSend( int msg_id , const char *string )
   { return safeSend( cMsg(msg_id,strlen(string)+1,string) ); }
   bool /*ok*/ safeSend( int msg_id , const char *buffer, int size )
   { return safeSend( cMsg(msg_id,size,buffer) ); }

   void onlineLoop( char *str );
   void offlineLoop();

   //
   // DEBUG-Schalter
   //
private:
   unsigned long dbg_error;
   unsigned long dbg_info;
   unsigned long dbg_status;
public:
   // - mit dbgBase gesetzt wird ueber mask=0 IMMER etwas ausgegeben (status)
   // - sonst werden nur dbgInfo und dbgError bestimmungsgemaess verwendet
   // - das dbgUser ist wegen der Sonderabfrage in cBase auf mask==0 drin !!!
   void setDebug(unsigned long mask) {
      dbg_error  = cBase::dbgUser | (mask & cBase::dbgError);
      dbg_info   = cBase::dbgUser | (mask & cBase::dbgInfo);
      dbg_status = (mask & cBase::dbgBase) ? 0 : cBase::dbgUser;
   }
};

#endif /*__INTERFACE__*/


// ---------------------------------------------------------------------------
// Implementierung cConServer

cConServer::cConServer( cString in )
{
   setDebug( cBase::dbgError | cBase::dbgBase );

   //cBase::setDebugMask( cBase::getDebugMask() | cBase::dbgInfo );

   if ( in.getLength() ) {
      server_name = in;
   } else if ( getenv(ENV_SERVER) ) {
      server_name = getenv(ENV_SERVER);
   } else {
      server_name = DEFAULT_SERVER;
   }

   cString base_name(server_name);
   int try_counter = 0;

   inbox = NULL;
   do {
      try {
         inbox = new cMsgBox( (CCP)server_name,16,MAX_MESSAGE_LEN );
      } catch (cErrBase& err) {
         if ( err == cErrMsg::errCreateChannel /*WinNT*/ ) {
            //err == cErrMsg::errSendToChannel /*Win95*/ ||
            if ( ++try_counter >= MAX_SERVER_TWINS ) {
               // FEHLER AUSGEBEN
               throw;
            }
            inbox = NULL;
            server_name = base_name + Str(try_counter);
         } else {
            cerr << "Error: " << err << endl;
            throw;
         }
      }

   } while ( inbox==NULL );

   //## Server traegt sich im Shared-Memory mit Zeitstempel ein
   condir.newEntry(server_name, time(NULL));

   outbox = NULL;
   last_line[0] = '\0';
}


cConServer::~cConServer()
{
   safeSend( cConClient::msgServerLost );

   //## Server loescht seinen Eintrag im Shared Memory
   condir.delEntry(server_name);

   delete inbox;
   delete outbox;
}


// ---------------------------------------------------------------------------
// ... Meldungen senden und empfangen (Low-Level)

bool cConServer::safeSend( cMsg msg )
{
   if ( outbox ) {
      try {
         DbgOut(dbg_info, "%s: send Msg(id=%d, %p, %d)", (CCP)server_name,
                  msg.getMsgId(), msg.getData(), msg.getDataLen() );
         outbox->send( msg );
      } catch (cErrBase& err) {
         if ( err == cErrMsg::errSendToChannel /*Win95*/ ||
              err == cErrMsg::errOpenChannel /*WinNT*/ ) {
            DbgOut(dbg_error,"%s: client %s lost", (CCP)server_name, (CCP)client_name);
            delete outbox;
            outbox = NULL;
            return false;
         } else {
            cerr << "Error: " << err << endl;
            throw;
         }
      }
   }
   return true;
}


bool cConServer::Receive( cMsg &msg )
{
   msg = inbox->receive();

   if ( msg.isEmpty () ) {
      DbgOut(dbg_info, "%s: receive Msg(emtpy)", (CCP)server_name );
   } else {
      DbgOut(dbg_info, "%s: receive Msg(id=%d, %p, %d)", (CCP)server_name,
               msg.getMsgId(), msg.getData(), msg.getDataLen() );
   }

   return !msg.isEmpty();
}


// ---------------------------------------------------------------------------
// ... Serverfunktioen

void cConServer::onlineLoop( char *str )
{
   cMsg msg;
   static char lfd_id;  // Debug

   while ( outbox != NULL ) {
      str[1] = lfd_id++;
      DbgOut(dbg_info,"%s: gets request %d",(CCP)server_name,str[1]); // Debug
      safeSend( cConClient::msgGetsReq, str, 2 ); // Debug
      //safeSend( cConClient::msgGetsReq, str, 1 );
      Receive( msg );
      switch (msg.getMsgId()) {
      case msgGetsReply:
         str[1] = char(msg.getDataLen()-1);
         strcpy(str+2, (char*)msg.getData());
         return;
      case msgLogin:
         if ( client_name == (CCP)msg.getData() ) {
            DbgOut(dbg_info, "%s: additional login %s confirmed", (CCP)server_name,
                      (CCP)client_name );
            safeSend( cConClient::msgLoginAck );
            safeSend( cConClient::msgPuts, last_line );
         } else {
            DbgOut(dbg_status, "%s: LOGIN %s (%s lost)", (CCP)server_name,
                      msg.getData(), (CCP)client_name );
            // alten Client benachrichtigen und entsorgen
            safeSend( cConClient::msgServerLost );
            delete outbox;
            // neuen Client bestaetigen
            outbox = new cMsgRecipient( (char*)msg.getData() );
            client_name = (char*)msg.getData();
            safeSend( cMsg(cConClient::msgLoginAck) );
            safeSend( cConClient::msgPuts, last_line );
         }
         break;
      case msgLogout:
         DbgOut(dbg_status,"%s: LOGOUT %s", (CCP)server_name,(CCP)client_name);
         safeSend( cConClient::msgLogoutAck );
         delete outbox;
         outbox = NULL;
         break;
      default:
         DbgOut(dbg_error,"%s: unknown message id=%d", (CCP)server_name, msg.getMsgId() );
         break;
      }
   }
}


void cConServer::offlineLoop()
{
   cMsg msg;

   DbgOut(dbg_status,"%s: waiting for client", (CCP)server_name );
   while ( outbox == NULL ) {
      Receive( msg );
      switch (msg.getMsgId()) {
      case msgLogin:
         DbgOut(dbg_status, "%s: LOGIN %s", (CCP)server_name, msg.getData() );
         outbox = new cMsgRecipient( (char*)msg.getData() );
         client_name = (char*)msg.getData();
         safeSend( cMsg(cConClient::msgLoginAck) );
         safeSend( cConClient::msgPuts, last_line );
         break;
      case msgLogout:
      case msgGetsReply:
         DbgOut(dbg_error, "%: message ignored id=%d", (CCP)server_name, msg.getMsgId() );
         break;
      default:
         DbgOut(dbg_error, "%s: unknown message id=%d", (CCP)server_name, msg.getMsgId() );
         break;
      }
   }
}


int cConServer::cputs( const char *str )
{
   char *nl_pos = strrchr(str,'\n');
   int max_chars = sizeof(last_line) - strlen(last_line) - 1;

   if (nl_pos) {
      int dbg = min( max_chars,  strlen(str) + str - nl_pos );
      strncpy( last_line, nl_pos+1, dbg  );
   } else {
      strncat( last_line, str, min( max_chars, (int)strlen(str) ) );
   }

   if (strlen(str) < MAX_MESSAGE_LEN) {
      safeSend( cConClient::msgPuts, str );
   } else {
      const char *ptr = str;
      char temp_buf[MAX_MESSAGE_LEN];
      temp_buf[MAX_MESSAGE_LEN-1]='\0';
      do {
         memcpy(temp_buf,ptr,MAX_MESSAGE_LEN-1);
         safeSend( cConClient::msgPuts, temp_buf );
         ptr += MAX_MESSAGE_LEN-1;
      } while (strlen(ptr) >= MAX_MESSAGE_LEN);
      safeSend( cConClient::msgPuts, ptr );
   }
   return strlen(str);
}


char *cConServer::cgets( char *str )
{
   do {
      if ( outbox ) {
         onlineLoop( str );
      } else {
         offlineLoop();
      }
   } while ( !outbox );

   return str+2;
}



