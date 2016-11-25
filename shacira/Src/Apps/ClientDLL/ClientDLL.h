
#ifndef _ClientDLL_h_
#define _ClientDLL_h_

typedef unsigned long CLIENT_HANDLE;
#define INVALID_CLIENT_HANDLE    0

#ifdef __cplusplus
extern "C" {
#endif

long __declspec(dllexport) __stdcall CLIENT_Init(const char * root_name);
void __declspec(dllexport) __stdcall CLIENT_Exit();
CLIENT_HANDLE __declspec(dllexport) __stdcall CLIENT_Connect(const char * name);
long __declspec(dllexport) __stdcall CLIENT_Release(CLIENT_HANDLE hnd);
long __declspec(dllexport) __stdcall CLIENT_GetVarRef(CLIENT_HANDLE hnd, const char * var_spec, char * buf, unsigned long buf_size);
long __declspec(dllexport) __stdcall CLIENT_SetVarRef(CLIENT_HANDLE hnd, const char * var_spec, const char * buf, unsigned long buf_len);
long __declspec(dllexport) __stdcall CLIENT_GetVariable(CLIENT_HANDLE hnd, const char * var_name,
                                       unsigned long i1, unsigned long i2, unsigned long i3, unsigned long i4,
                                       char * buf, unsigned long buf_size);
long __declspec(dllexport) __stdcall CLIENT_SetVariable(CLIENT_HANDLE hnd, const char * var_name,
                                       unsigned long i1, unsigned long i2, unsigned long i3, unsigned long i4,
                                       const char * buf, unsigned long buf_len);
void __declspec(dllexport) __stdcall CLIENT_GetErrorString(CLIENT_HANDLE hnd, char * buf, unsigned long buf_size);

#define ERR_INITIALIZING_CCS_CLIENT_INFRASTRUCTURE          -2
#define ERR_LOADING_CONFIGURATION                           -3
#define ERR_ROOT_NAME_NOT_FOUND                             -4
#define ERR_INVALID_HANDLE                                  -5
#define ERR_GET_VARIABLE                                    -6
#define ERR_SET_VARIABLE                                    -7
#define ERR_CCS_CLIENT_INFRASTRUCTURE_ALREADY_INITIALIZED   -8

#ifdef __cplusplus
}
#endif

#endif

