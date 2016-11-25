/*.SH.*/

/*
 *  Headerfile for module et_conser
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  et_conser.cpp on Thursday February 15 2001  13:12:36
 */

#ifndef __et_conser__
#define __et_conser__


#include "base/eb_base.hpp"
#include "base/eb_msg.hpp"
#include "base/eb_str.hpp"
#include "base/eb_shmem.hpp"
#include "time.h"


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


#endif

/*.EH.*/
