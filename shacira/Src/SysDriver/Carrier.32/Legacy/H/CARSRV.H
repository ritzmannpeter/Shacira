/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
#ifndef _platform
#include <platform.h>
#define _platform
#endif
/*.EI.***********************************************************************/

#ifndef _carsrv_
#define _carsrv_

/* Dienste bzw. Kommandos
 */
#define QUERY_SRV_VERSION   0
#define QUERY_FORMAT        1

#define DIR_CARRIER        10
#define FORMAT_CARRIER     11
#define READ_FILE          12
#define WRITE_FILE         13
#define DELETE_FILE        14

/* Formate
 */
#define FMFAT              1
#define ARBURG_C_FAT       2
#define FMT2               3
#define FX25               4
#define FMT1               6

#define FM_1               50
#define FM_1_5             51
#define FM_2               52
#define FM_3               53
#define DEMAG              54

/* Quellen
 */
#define SRC_EEPROM         1
#define EEPROM_PREFIX      "//carrier/"
#define SRC_DISK           2
#define DISK_PREFIX        "//disk/"
#define SRC_NET            3
#define NET_PREFIX         "//net/"
#define SRC_FILE           4
#define FILE_PREFIX        "//file/"

/* Versionen
 */
#define UNKNOWN_VERSION    49
#define FMFAT_KS           50
#define FMFAT_KE           51
#define FMFAT_KDS          53
#define FMFAT_KDE          54
#define FMFAT_ELEKTRA      55
#define FMFAT_FM           56
#define FMFAT_FXR          57
#define FMFAT_FXA          58

#define FMT2_FM           100    /* 1001 */
#define FMT2_FXP          101    /* 1020 */
#define FMT2_FXA          102    /* 1030 */
#define FMT2_FM_2F        103    /* 2001 */
#define FMT2_FM_3F        104    /* 3001 */
#define FMT2_FXP_2F       105    /* 2020 */
#define FMT2_FXA_2F       106    /* 2030 */

#define FX25_FX           150    /*  */
#define FMT1_FM           151

#define ARBURG_C          200


#define MAX_SRC_LEN       256

typedef struct service_header
{  short server;
   short service;
   char src[MAX_SRC_LEN];
   short status;
   short format;
}  SERVICE_HEADER;

#define SRV_NAME_LEN       128
#define DATE_LEN           18
#define VERS_LEN           10

typedef struct srv_version
{  char name[SRV_NAME_LEN];
   char date[DATE_LEN];
   char version[VERS_LEN];
}  SRV_VERSION;

typedef struct dir_header
{  short files;
}  DIR_HEADER;

typedef struct format_entry
{  short format;
}  FORMAT_ENTRY;

#define FILE_NAME_LENGTH   20
#define TOOLNO_LENGTH      20
#define MATNO_LENGTH       20
#define ARTNO_LENGTH       20

GLOBAL int DeviceError();

/* Geraete-Fehlercodes
 */
#define DEV_WRITE_PROTECTED           -100
#define DEV_UNKNOWN_UNIT              -101
#define DEV_NOT_READY                 -102
#define DEV_UNKNOWN_COMMAND           -103
#define DEV_CRC_ERROR                 -104
#define DEV_BAD_DRIVE_REQUEST         -105
#define DEV_SEEK_ERROR                -106
#define DEV_SECTOR_NOT_FOUND          -107
#define DEV_OUT_OF_PAPER              -108
#define DEV_WRITE_FAULT               -109
#define DEV_READ_FAULT                -110
#define DEV_GENERAL_FAILURE           -111
#define DEV_UNKNOWN_ERROR             -112

/* Fehlercodes
 */
#define SRV_SERVICE_NOT_AVAILABLE      -300
#define SRV_INVALID_SERVICE            -301
#define SRV_UNKNOWN_SOURCE             -302
#define SRV_FUNC_NOT_IMP               -303
#define SRV_FORMAT_NOT_DETECTED        -304
#define SRV_NO_FORMAT_DETECT           -305
#define SRV_INVALID_SRC_SPEC           -306
#define SRV_DEVICE_UNAVAILABLE         -307

#endif /* _carsrv_ */
