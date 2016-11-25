#ifndef _DEVCTL_H_INCLUDED
#define _DEVCTL_H_INCLUDED

#if __WATCOMC__ > 1000
#pragma pack(push,1);
#else
#pragma pack(1);
#endif

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef _IOCTL_H_INCLUDED
 #include <ioctl.h>
#endif

#ifndef _LIMITS_H_INCLUDED
 #include <limits.h>
#endif

#ifndef __NEUTRINO_H_INCLUDED
#ifdef __QNXNTO__
 #include <sys/neutrino.h>
#endif
#endif

/*
 * Flag bits applied to dcmd parameter of devctl()
 * Note that we limit the cmd portion to the low order 16 bits for
 * compatibility with UNIX ioctl's.
 */

#define _POSIX_DEVDIR_NONE		0
#define _POSIX_DEVDIR_TO		0x80000000
#define _POSIX_DEVDIR_FROM		0x40000000
#define _POSIX_DEVDIR_TOFROM	(_POSIX_DEVDIR_TO | _POSIX_DEVDIR_FROM)
#define _POSIX_DEVDIR_CMD_MASK	0x0000FFFF

#define DEVDIR_NONE				_POSIX_DEVDIR_NONE
#define DEVDIR_TO				_POSIX_DEVDIR_TO
#define DEVDIR_FROM				_POSIX_DEVDIR_FROM
#define DEVDIR_TOFROM			_POSIX_DEVDIR_TOFROM
#define DEVDIR_CMD_MASK			_POSIX_DEVDIR_CMD_MASK


#ifdef __cplusplus
extern "C" {
#endif
extern int devctl(int fd, int dcmd, void *dev_data_ptr, size_t nbytes, int *dev_info_ptr);
//extern int devctlv(int fd, int dcmd, int sparts, int rparts, const iov_t *sv, const iov_t *rv, int *dev_info_ptr);

extern int set_device_direction(int command, int direction);
#define set_device_direction(_cmd, _dir)	((_cmd)|(_dir))

extern int get_device_direction(int command);
#define get_device_direction(_cmd)			((_cmd)&_POSIX_DEVDIR_TOFROM)

extern int get_device_command(int command);
#define get_device_command(_cmd)			((_cmd)&~DEVDIR_CMD_MASK)
#ifdef __cplusplus
};
#endif


/*
 * ioctl is built() on top of devctl().
 * Both devcmd() and ioctl() encode the direction in the command using
 * the same 2 high order bits.
 *
 * All QNX devctl's are defined in this file. Other codes may exist for
 * 3rd party products in files provided by the 3rd party.
 *
 *
 * The dcmd codes are subdivided into the following classes:
 *
 *      QNX reserved            0x000 - 0x0ff
 *      common (all io servers) 0x100 - 0x1ff
 *      Block                   0x200 - 0x2ff
 *      Character               0x300 - 0x3ff
 *      Network                 0x400 - 0x4ff
 *      Misc                    0x500 - 0x5ff
 *      IP                  	0x600 - 0x6ff
 *      Mixer					0x700 - 0x7ff
 *		Proc					0x800 - 0x8ff
 *      Flash filesystems		0x900 - 0x9ff
 *      Input devices           0xA00 - 0xAff
 *
 * Add new ranges here and create a header file in <sys/dcmd_???.h>
 * which you include at the bottom of this file.
 *
 *      QNX reserved            0x000 - 0xfff
 */
#define _DCMD_ALL		0x01
#define _DCMD_BLK		0x02
#define _DCMD_CHR		0x03
#define _DCMD_NET		0x04
#define _DCMD_MISC		0x05
#define _DCMD_IP		0x06
#define _DCMD_MIXER		0x07
#define _DCMD_PROC		0x08
#define _DCMD_FFS		0x09
#define _DCMD_INPUT		0x0A

#define __DIOF(class, cmd, data)	(((class)<<8) + (cmd) + _POSIX_DEVDIR_FROM)
#define __DIOT(class, cmd, data)	(((class)<<8) + (cmd) + _POSIX_DEVDIR_TO)
#define __DIOTF(class, cmd, data)	(((class)<<8) + (cmd) + _POSIX_DEVDIR_TOFROM)
#define __DION(class, cmd)			(((class)<<8) + (cmd) + _POSIX_DEVDIR_NONE)

#define _DEVCTL_DATA(msg)			((void *)(sizeof(msg) + (char *)(&msg)))

#if __WATCOMC__ > 1000
#pragma pack(pop);
#else
#pragma pack();
#endif
#endif

