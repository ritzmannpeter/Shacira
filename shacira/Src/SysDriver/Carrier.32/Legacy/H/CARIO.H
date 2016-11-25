/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
#ifndef _platform
#include <platform.h>
#define _platform
#endif
#ifndef _basicio
#include <basicio.h>
#define _basicio
#endif
/*.EI.***********************************************************************/

#ifndef __cario__
#define __cario__

#define     DCAR_OK            0
/* error codes
#define     DCAR_BAD_TYP      -1
#define     DCAR_NOT_FOUND    -2
#define     DCAR_VERIFY_ERROR -3
#define     DCAR_NO_EEPROM    -4
#define     DCAR_NOT_READY    -5
#define     DCAR_ADR_ERROR    -6
#define     DCAR_NULL_SIZE    -7
#define     DCAR_DELAY_SIZE   -8
*/

#define     DCAR_0K        0
#define     DCAR_2K        2
#define     DCAR_4K        4
#define     DCAR_8K        8
#define     DCAR_32K       32
#define     DCAR_64K       64

GLOBAL const IO_MODULE * CAR_Module();

#endif   /* cario */

