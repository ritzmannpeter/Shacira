
#ifndef __stypes__
#define __stypes__

#ifdef __QNXNTO__
typedef int CID_T;
typedef int SIZE_T;
typedef int NID_T;
typedef int PID_T;
typedef int TID_T;
typedef int TIND_T;
#elif defined __LINUX__
typedef int CID_T;
typedef int SIZE_T;
typedef int NID_T;
typedef int PID_T;
typedef int TID_T;
typedef int TIND_T;
#elif defined __QNX4__
typedef int CID_T;
typedef int SIZE_T;
typedef int NID_T;
typedef int PID_T;
typedef int TID_T;
typedef int TIND_T;
#elif defined __WIN32__
#include <windows.h>
typedef int CID_T;
typedef DWORD SIZE_T;
typedef int NID_T;
typedef int PID_T;
typedef int TID_T;
typedef int TIND_T;
#elif defined __QNX2__
typedef int CID_T;
typedef int SIZE_T;
typedef int NID_T;
typedef int PID_T;
typedef int TID_T;
typedef int TIND_T;
#endif

#endif /* __stypes__ */
