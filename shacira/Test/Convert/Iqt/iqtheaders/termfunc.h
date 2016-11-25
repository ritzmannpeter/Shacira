
#ifndef _termfunc
#define _termfunc

/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
#ifndef _iqtdev
#include <iqtdev.h>
#define _iqtdev
#endif
/*.EI.***********************************************************************/

GLOBAL int CreateTerminal(IQT_HANDLE hnd, long baudrate, BYTE charlength,
                                                                  BYTE stopbits, BYTE parity);
GLOBAL int LoginTerminal(IQT_HANDLE hnd, long baudrate, BYTE charlength,
                                                                 BYTE stopbits, BYTE parity);

#endif   /*ifndef _termfunc*/
