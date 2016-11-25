
#ifndef cGatewayInterface_h
#define cGatewayInterface_h 1

#ifdef __cplusplus
extern "C" {
#endif

#define GATEWAY_INTERFACE_ALREADY_INITIALIZED   -2
#define NO_GATEWAY_REPLY                        -3
#define GATEWAY_INTERFACE_NOT_INITIALIZED       -4
#define GATEWAY_FAILED_TO_LOAD_WINSOCK_DLL      -5
#define GATEWAY_INVALID_WINSOCK_VERSION         -6
#define GATEWAY_GETVALUE_FAILED                 -7
#define GATEWAY_SETVALUE_FAILED                 -8
#define GATEWAY_INIT_FAILED                     -9
#define GATEWAY_CONTEXTLIST_FAILED              -10
#define GATEWAY_GETPAGE_FAILED                  -11

extern int GIInit(unsigned long client_id, unsigned short server_port, const char * server_host);
extern int GIGetValue(const char * cell_name, const char * var_spec,
                      char * buf, unsigned long buf_size);
extern int GISetValue(const char * cell_name, const char * var_spec,
                      const char * value);
extern int GIGetContextList(char * buf, unsigned long buf_size);
extern int GIGetPage(const char * cell_name, const char * page, char * buf, unsigned long buf_size);
extern int GIRequest(const char * cell_name, const char * request, char * buf, unsigned long buf_size);

#ifdef __cplusplus
}
#endif

#endif

