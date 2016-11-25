
#ifndef _service_h_
#define _service_h_

/*.SI.***********************************************************************/
#ifndef __syntax__
#include <syntax.h>
#define __syntax__
#endif
#ifndef __platform__
#include <platform.h>
#define __platform__
#endif
/*.EI.***********************************************************************/

typedef unsigned char unsigned_8;
typedef unsigned short unsigned_16;
typedef unsigned long unsigned_32;
typedef char signed_8;
typedef short signed_16;
typedef long signed_32;

/* Formate
 */
#define UNKNOWN_FORMAT     0
#define FMFAT              1
#define ARBURG_C_FAT       2
#define FMT2               3
#define FX25               4
#define SHEET_FMT          5
#define FMT1               6
#define DEMAG_NC4_FORMAT   7

#define FM_1               50
#define FM_1_5             51
#define FM_2               52
#define FM_3               53
#define DEMAG_NC3_PROT     54

/* Quellen
 */
#define SRC_EEPROM         1
#define EEPROM_PREFIX      "//CARRIER/"
#define SRC_DISK           2
#define DISK_PREFIX        "//DISK/"
#define SRC_NET            3
#define NET_PREFIX         "//NET/"
#define SRC_DUMP           4
#define DUMP_PREFIX        "//DUMP/"

/* Versionen
 */
#define UNKNOWN_VERSION    0
#define FMFAT_KS           50
#define FMFAT_KE           51
#define FMFAT_KDS          53
#define FMFAT_KDE          54
#define FMFAT_ELEKTRA      55
#define FMFAT_FM           56
#define FMFAT_FXR          57
#define FMFAT_FXA          58
#define FMFAT_K0           59
#define FMFAT_K1           60
#define FMFAT_K2           61
#define FMFAT_E0           62
#define FMFAT_E1           63
#define FMFAT_E2           64

#define FMT2_FM           100    /* Id = 1 ProcNr = 1001 */
#define FMT2_FXP          101    /* Id = 1 ProcNr = 1020 */
#define FMT2_FXA          102    /* Id = 1 ProcNr = 1030 */
#define FMT2_FM_2F        103    /* Id = 1 ProcNr = 2001 */
#define FMT2_FM_3F        104    /* Id = 1 ProcNr = 3001 */
#define FMT2_FXP_2F       105    /* Id = 1 ProcNr = 2020 */
#define FMT2_FXA_2F       106    /* Id = 1 ProcNr = 2030 */
#define FMT2_GRAPHIC      107    /* Id = 2 */
#define FMT2_FXP_3F       108    /* Id = 1 ProcNr = 3020 */
#define FMT2_FXA_3F       109    /* Id = 1 ProcNr = 3030 */

#define FX25_FX           150    /*  */
#define FMT1_FM           170    /*  */

#define ARBURG_C          200

#define DEMAG_NC4         210

#endif /* _service_h_ */
