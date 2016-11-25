/*
 *  dcmd_name.h   Non-portable low-level devctl definitions
 *
 * 13.08.99 -TSchw-  info_msg in name_info_msg geaendert in __DIOT (auf
 *                   Verdacht, bisher wurde dieser Parameter im Makro
 *                   nicht benutzt).
 * 18.04.00 -TSchw-  DCMD_NAME von 0x0B auf 0x0E geaendert, weil 0x0B
 *                   ab Neutrino 2.0 offenbar fuer Photon reserviert ist,
 *                   und daher das devctl schief geht.
 *
 */

#ifndef _dcmd_name
#define _dcmd_name

/*.SI.***********************************************************************/
#ifdef __QNXNTO__
#include <devctl.h>
#elif defined __QNX4__
#include <posix/devctl.h>
#endif
#include <namesrv.h>
/*.EI.***********************************************************************/

#define MAX_NAME_LEN		128

typedef struct name_info_msg
{	char name[MAX_NAME_LEN];
	INFO info;
} NAME_INFO_MSG;

#ifdef __QNXNTO__

#define _DCMD_NAME		0x0E

#define DCMD_NAME_GETNAMEINFO	__DIOTF(_DCMD_NAME, 1, struct name_info_msg)
#define DCMD_NAME_SETNAMEINFO	__DIOT(_DCMD_NAME, 2, struct name_info_msg)

#endif

#endif
