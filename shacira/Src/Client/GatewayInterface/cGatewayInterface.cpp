
#include "FirstHeader.h"

#include "Client/GatewayInterface/cGatewayInterface.h"
#include "Client/GatewayInterface/cGatewayClient.h"

#ifdef __cplusplus
extern "C" {
#endif

#define REQUEST_TIMEOUT    1000

static cGatewayClient * _Client = NULL;

static int StartSockets()
{
#ifdef _WIN32
   WORD req_version = MAKEWORD(2, 2);
   WSADATA wsa_data;
   int err = WSAStartup(req_version, &wsa_data);
   if (err != 0) {
      /* Tell the user that we could not find a usable */
      /* WinSock DLL.                                  */
       return GATEWAY_FAILED_TO_LOAD_WINSOCK_DLL;
   }
   /* Confirm that the WinSock DLL supports 2.2.*/
   /* Note that if the DLL supports versions greater    */
   /* than 2.2 in addition to 2.2, it will still return */
   /* 2.2 in wVersion since that is the version we      */
   /* requested.                                        */
   if (LOBYTE(wsa_data.wVersion) != 2 ||
       HIBYTE(wsa_data.wVersion) != 2) {
      /* Tell the user that we could not find a usable */
      /* WinSock DLL.                                  */
      WSACleanup();
      return GATEWAY_INVALID_WINSOCK_VERSION;
   }
   return 0;
#else
   return 0;
#endif
}

int GIInit(unsigned long client_id, unsigned short server_port, const char * server_host)
{
   try {
      if (_Client == NULL) {
         int rc = StartSockets();
         if (rc != 0) {
            return rc;
         }
         _Client = new cGatewayClient(client_id, server_port, server_host);
         return 0;
      } else {
         return GATEWAY_INTERFACE_ALREADY_INITIALIZED;
      }
   } catch (...) {
      return GATEWAY_INIT_FAILED;
   }
}

int GIGetValue(const char * cell_name, const char * var_spec,
               char * buf, unsigned long buf_size)
{
   try {
      if (_Client != NULL) {
         int rc = _Client->GetValue(cell_name, var_spec, buf, buf_size);
         if (rc == 0) {
            return 0;
         } else {
            return rc;
         }
      } else {
         return GATEWAY_INTERFACE_NOT_INITIALIZED;
      }
   } catch (...) {
      return GATEWAY_GETVALUE_FAILED;
   }
}

int GISetValue(const char * cell_name, const char * var_spec,
               const char * value)
{
   try {
      if (_Client != NULL) {
         int rc = _Client->SetValue(cell_name, var_spec, value);
         if (rc == 0) {
            return 0;
         } else {
            return rc;
         }
      } else {
         return GATEWAY_INTERFACE_NOT_INITIALIZED;
      }
   } catch (...) {
      return GATEWAY_SETVALUE_FAILED;
   }
}

int GIGetContextList(char * buf, unsigned long buf_size)
{
   try {
      if (_Client != NULL) {
         int rc = _Client->GetContextList(buf, buf_size);
         if (rc == 0) {
            return 0;
         } else {
            return rc;
         }
      } else {
         return GATEWAY_INTERFACE_NOT_INITIALIZED;
      }
   } catch (...) {
      return GATEWAY_CONTEXTLIST_FAILED;
   }
}

int GIGetPage(const char * cell_name, const char * page, char * buf, unsigned long buf_size)
{
   try {
      if (_Client != NULL) {
         int rc = _Client->GetPage(cell_name, page, buf, buf_size);
         if (rc == 0) {
            return 0;
         } else {
            return rc;
         }
      } else {
         return GATEWAY_INTERFACE_NOT_INITIALIZED;
      }
   } catch (...) {
      return GATEWAY_GETPAGE_FAILED;
   }
}

int GIRequest(const char * cell_name, const char * request, char * buf, unsigned long buf_size)
{
   try {
      if (_Client != NULL) {
         int rc = _Client->Request(cell_name, request, buf, buf_size);
         if (rc == 0) {
            return 0;
         } else {
            return rc;
         }
      } else {
         return GATEWAY_INTERFACE_NOT_INITIALIZED;
      }
   } catch (...) {
      return GATEWAY_GETPAGE_FAILED;
   }
}

#ifdef __cplusplus
}
#endif

