
#ifndef target_def_h
#define target_def_h 1

#if defined(__linux__)

#include "System/Sys/cLinuxPort.h"
//#define NOT_PORTED_TO_LINUX
#define PORT_LEVEL_1
#define PORT_LEVEL_2
#define PORT_LEVEL_3
#define PORT_LEVEL_4
#define PORT_LEVEL_5

#elif defined(_WIN32)

#include <winsock2.h>
#define _WINSOCKAPI_            // Prevent winsock.h #include's.
#include <windows.h>

#if defined(__MINGW32__)
//#define NOT_PORTED_TO_MINGW
#define PORT_LEVEL_1
#define PORT_LEVEL_2
#define PORT_LEVEL_3
#define PORT_LEVEL_4
#define PORT_LEVEL_5
#endif

#else

#pragma error("this platform is not supported")

#endif

#endif

