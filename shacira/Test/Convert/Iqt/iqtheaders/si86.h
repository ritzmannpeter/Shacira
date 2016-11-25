
#ifndef __si86__
#define __si86__

#include <syntax.h>

#if defined(__QNXNTO__) || defined(__QNX4__)

//#include <i86.h>
#define Disable() _disable()
#define Enable()  _enable()
#define POINTER_VALID(ptr) TRUE

#elif defined(__LINUX__)

#define POINTER_VALID(ptr) TRUE

#elif defined(__QNX2__)

#include <qnx.h>
#define Disable() cli()
#define Enable()  sti()
#define POINTER_VALID(ptr) _ispermitr((ptr))

#elif defined(__WIN32__)

#include <windows.h>
#define Disable()
#define Enable()
#define POINTER_VALID(ptr) TRUE

#endif

GLOBAL void Reset(void);
GLOBAL void Reboot(void);
GLOBAL void ExitProgram (int retcode); /* Nur das Programm beenden */

#endif /* __si86__ */
