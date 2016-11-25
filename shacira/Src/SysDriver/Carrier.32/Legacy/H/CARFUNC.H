
#ifndef _carfunc
#define _carfunc

/***************************************************************************/
#ifndef __cstdio__
#include <cstdio.h>
#define __cstdio__
#endif
/***************************************************************************/

#define INPUT_SIZE      1024
#define OUTPUT_SIZE     1024

#ifdef __cplusplus
extern "C" {
#endif

GLOBAL int _Carrier(char * input, char * output);
GLOBAL int _CARRIER_FileInfo(char * path, FILE_INFO * file_info);
GLOBAL int _CARRIER_FileRepair(char * path);
GLOBAL int _CARRIER_SetTime(char * path);
GLOBAL int _CARRIER_SetRegVal(char * path, long regid, int index, long value);
GLOBAL int _CARRIER_GetRegVal(char * path, long regid, int index, long * value);
GLOBAL int _CARRIER_SetData(char * path, char * artno, char * matno, char * toolno);

#ifdef __cplusplus
}
#endif

#endif /* ifndef _carfunc */

