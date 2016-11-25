/***************************************************************************/

#ifndef __thunkmod__
#define __thunkmod__

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void FreeRessources(void);
extern void Message(const char * fmt, ... );
extern void ErrMessage(const char * fmt, ...);

#ifdef __cplusplus
}
#endif

#endif

