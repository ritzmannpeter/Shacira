/*
 *  carioctl.h   platform specific low-level ioctl definitions
 *
 *  History:
 *    28.02.00 -TSchw- IOCTL_CARRIER_... inserted
 */

/*.SI.***********************************************************************/
#ifndef _carioctl_
#define _carioctl_

#include <syntax.h>

#ifdef __WIN32__
#include <winioctl.h>
#elif defined __NT_DRIVER__
#include <devioctl.h>
#endif
/*.EI.***********************************************************************/

/****************************************************************************/
/* Data Carrier device                                                      */
/****************************************************************************/


#if defined(__WIN32__) || defined (__NT_DRIVER__)

// Check carrier and return carrier size in KByte
// write buffer:  empty 
// return buffer: one int, containing size in KByte or a (negative)
//                DCAR_... error code
#define IOCTL_CARRIER_CHECK	CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,\
                                       METHOD_BUFFERED,FILE_ANY_ACCESS)

// Set the address in the carrier for subsequent read/write operation
// write buffer:  one unsigned long int, containing address
// return buffer: empty
#define IOCTL_CARRIER_SEEK		CTL_CODE(FILE_DEVICE_UNKNOWN,0x802,\
                                       METHOD_BUFFERED,FILE_ANY_ACCESS)

// Get the last carrier error (DCAR_...)
// write buffer:  empty 
// return buffer: one int, containing the last DCAR_... error code.
//                DCAR_OK means no error with last command.
#define IOCTL_CARRIER_LASTERR	CTL_CODE(FILE_DEVICE_UNKNOWN,0x803,\
                                       METHOD_BUFFERED,FILE_ANY_ACCESS)

#endif


#endif	/* _carioctl_ */

