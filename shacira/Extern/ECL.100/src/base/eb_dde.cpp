// ===========================================================================
// eb_dde.cpp                                                   ______ /  ECL
// Autor: Markus Wuertz                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
// cBase
//    |
//    +--cDde
//
// ===========================================================================

#include "base/eb_dde.hpp"

//#include <stdio.h>
//#include <ostream.h>
//#include "base/eb_file.hpp"
//#include "base/eb_thread.hpp"
//#include "base/eb_time.hpp"
//#include "tom/et_tomate.hpp"
//#include "azr_com.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_base.hpp"
#include "base/eb_str.hpp"
#include "base/eb_err.hpp"

#include <windows.h>
#include <ddeml.h>

#endif /*__INTERFACE__*/




// ===========================================================================
// Deklaration cDde
// ===========================================================================

#ifdef __INTERFACE__

class __ECL_DLLEXPORT__ cDde : public cBase {
   //
   // Fehlerbehandlung
   //
public:
   enum ERR_CODE { errBase = ERR_PREFIX('D','D','E'),
      // Information
      // err??? = errBase + errInfo,

      // Warnungen
      // err??? = errBase + errWarn,

      // Fehler
      errDdeFailed = errBase + errError,
      errDdeTimeout,

      // Fatale Fehler
      errDdeInit = errBase+errFatal,
   };

public:
   // Initialize and Connect
   cDde(cString _service, cString _topic);
   // Uninitialize
   ~cDde();

   void poke(cString _item, cString _Value);
   void poke(cString _item, const char *_buffer, int _size);
   cString request(cString _item);
   void execute(cString _cmd);

   static HDDEDATA CALLBACK callback(UINT uType,UINT uFmt,HCONV hconv,
      HSZ hsz1, HSZ hsz2, HDDEDATA hdata, DWORD dwData1, DWORD dwData2);

private:
   DWORD idInst;     // instance identifier
   HCONV hConv;      // handle to conversation

   cErrBase::ERR_TYPE cvtDdeError(UINT _api_err);
};

#endif /*__INTERFACE__*/


// ---------------------------------------------------------------------------
// Implementierung cDde
// ---------------------------------------------------------------------------

cDde::cDde(cString _service, cString _topic)
{
   UINT err;

   /*
   UINT DdeInitialize(
      LPDWORD pidInst,          // pointer to instance identifier
      PFNCALLBACK pfnCallback,  // pointer to callback function
      DWORD afCmd,              // set of command and filter flags
      DWORD ulRes               // reserved
   );
   */
   idInst = 0;
   err = DdeInitialize(&idInst, callback, /*APPCLASS_STANDARD*/
                                          APPCMD_CLIENTONLY , 0);
   if (err) {
      throw cErrBase( errDdeInit,"Initialize",cStringf("0x%04x",err) );
   }

   /*
   HCONV DdeConnect(
      DWORD idInst,      // instance identifier
      HSZ hszService,    // handle to service name string
      HSZ hszTopic,      // handle to topic name string
      PCONVCONTEXT pCC   // pointer to structure with context data
   );
   */
   HSZ szService = DdeCreateStringHandle (idInst, (const char *)_service, CP_WINANSI);
   HSZ szTopic = DdeCreateStringHandle (idInst, (const char *)_topic, CP_WINANSI);

   hConv = DdeConnect( idInst, szService, szTopic, NULL );

   DdeFreeStringHandle(idInst, szService);
   DdeFreeStringHandle(idInst, szTopic);

   if (hConv == 0) {
      err = DdeGetLastError(idInst);
      throw cErrBase( errDdeInit,"Connect",cStringf("0x%04x",err),
                      (const char *)_service,(const char *)_topic );
   }

}

cDde::~cDde()
{
   if (!DdeDisconnect( hConv ))
      throw cErrBase(errDdeInit,"Disconnect");
   if (!DdeUninitialize( idInst ))
      throw cErrBase(errDdeInit,"Uninitialize");
}

HDDEDATA CALLBACK cDde::callback(UINT uType,UINT uFmt,HCONV hconv, HSZ hsz1, HSZ hsz2,
                                 HDDEDATA hdata, DWORD dwData1, DWORD dwData2)
{
#define __CALLBACK_TEST__
#ifdef __CALLBACK_TEST__

   DbgTrcBase("Callback(T=%d,F=%d,H=%d,S1=%d,S2=%d,D=%d,D1=%d,D2=%d)",
      uType,uFmt,hconv,hsz1,hsz2,hdata,dwData1, dwData2);
#endif

   return (HDDEDATA) NULL;
}


cErrBase::ERR_TYPE cDde::cvtDdeError(UINT _api_err) {
   switch (_api_err) {
   case DMLERR_ADVACKTIMEOUT:
   case DMLERR_EXECACKTIMEOUT:
   case DMLERR_DATAACKTIMEOUT:
      return errDdeTimeout;
   case DMLERR_SYS_ERROR:
   case DMLERR_INVALIDPARAMETER:
   case DMLERR_BUSY:
   case DMLERR_DLL_NOT_INITIALIZED:
   case DMLERR_DLL_USAGE:
   case DMLERR_LOW_MEMORY:
   case DMLERR_MEMORY_ERROR:
   case DMLERR_NOTPROCESSED:
   case DMLERR_NO_CONV_ESTABLISHED:
   case DMLERR_POKEACKTIMEOUT:
   case DMLERR_POSTMSG_FAILED:
   case DMLERR_REENTRANCY:
   case DMLERR_SERVER_DIED:
   case DMLERR_UNADVACKTIMEOUT:
   case DMLERR_UNFOUND_QUEUE_ID:
   default:
      return errDdeFailed;
   }
}


void cDde::poke(cString _item, cString _value)
{
   poke(_item, (const char *)_value, _value.getLength());
}

void cDde::poke(cString _item, const char *_buffer, int _size)
{
   int err = 0;
   HSZ szItem = DdeCreateStringHandle (idInst, (const char *)_item, CP_WINANSI);

   //if (!szItem) {
   //   err = DdeGetLastError(idInst);
   //   throw cErrBase(cvtDdeError(err),"Request",cStringf("0x%04x",err),(const char *)_item);
   //}

   /*
   HDDEDATA DdeClientTransaction(
      LPBYTE pData,       // pointer to data to pass to server
      DWORD cbData,       // length of data
      HCONV hConv,        // handle to conversation
      HSZ hszItem,        // handle to item name string
      UINT wFmt,          // clipboard data format
      UINT wType,         // transaction type
      DWORD dwTimeout,    // time-out duration
      LPDWORD pdwResult   // pointer to transaction result
   );
   */
   HDDEDATA hData = DdeClientTransaction((LPBYTE)_buffer, _size,
                                         hConv, szItem, CF_TEXT, XTYP_POKE, 1000, NULL);

   DdeFreeStringHandle(idInst, szItem);

   if (hData) {
      DdeFreeDataHandle( hData );
   } else {
      err = DdeGetLastError(idInst);
      throw cErrBase(cvtDdeError(err),"Poke",cStringf("0x%04x",err),(const char *)_item,
                     (const char *)(cString(_buffer).getLeft(16)));
   }
}


cString cDde::request(cString _item)
{
   int err = 0;
   char buf[256];

   char *buf_ptr = buf;
   int buf_len = sizeof(buf);

   HSZ szItem = DdeCreateStringHandle (idInst, (const char *)_item, CP_WINANSI);

   //if (!szItem) {
   //   err = DdeGetLastError(idInst);
   //   throw cErrBase(cvtDdeError(err),"Request",cStringf("0x%04x",err),(const char *)_item);
   //   DbgError("Fehler bei request ...!");
   //}

   HDDEDATA hData = DdeClientTransaction(NULL, 0, hConv, szItem, CF_TEXT, XTYP_REQUEST, 5000, NULL);

   if (hData) {
      /*
      DWORD DdeGetData(
         HDDEDATA hData,  // handle to DDE  object
         LPBYTE pDst,     // pointer to destination buffer
         DWORD cbMax,     // amount of data to copy
         DWORD cbOff      // offset to beginning of data
      );
      */
      int len;
      len = DdeGetData(hData, NULL, sizeof(buf), 0); // wie gross muss Puffer sein?
      if (len > sizeof(buf)-1) {
         buf_len = len+1;
         buf_ptr = new0 char[len+1];
      }

      len = DdeGetData(hData, (LPBYTE)buf_ptr, buf_len, 0); // Daten lesen
      if (len == 0) {
         err = DdeGetLastError(idInst);
      }
      DdeFreeDataHandle( hData );
   } else {
      err = DdeGetLastError(idInst);
   }

   DdeFreeStringHandle(idInst, szItem);

   if (err) {
      throw cErrBase(cvtDdeError(err),"Request",cStringf("0x%04x",err),(const char *)_item);
   }

   cString result(buf_ptr); // dynamischen Puffer ggf. freigeben
   if (buf_ptr != buf) { delete buf_ptr; }
   return result;
}


void cDde::execute(cString _cmd)
{
   int err = 0;

   HDDEDATA hData = DdeClientTransaction((LPBYTE)(const char *)_cmd, _cmd.getLength()+1,
                                      hConv, 0, CF_TEXT, XTYP_EXECUTE, 1000, NULL);

   if (hData) {
      DdeFreeDataHandle( hData );
   } else {
      err = DdeGetLastError(idInst);
      throw cErrBase(cvtDdeError(err),"Execute",cStringf("0x%04x",err),(const char *)_cmd);
   }
}


