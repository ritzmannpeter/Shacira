
#ifndef ToolFiles_h
#define ToolFiles_h 1

// formats

#define FMT_UNDEFINED        -1
#define FMT_FMFAT             1
#define FMT_ARBURG_C_FAT      2
#define FMT_FMT2              3
#define FMT_FX25              4
#define FMT_SHEET             5
#define FMT_FMT1              6
#define FMT_DEMAG_NC4         7
#define FMT_FMT2_2F           8
#define FMT_FMT2_3F           9
#define FMT_FMT2_GRAPHIC      10
#define FMT_FREE              11

#define FMTHST_FM_1            50
#define FMTHST_FM_1_5          51
#define FMTHST_FM_2            52
#define FMTHST_FM_3            53
#define FMTHST_DEMAG_NC3       54

// versions

#define FILE_VERSION_UNKNOWN     -1
#define VERS_FMFAT_KS            50
#define VERS_FMFAT_KE            51
#define VERS_FMFAT_KDS           53
#define VERS_FMFAT_KDE           54
#define VERS_FMFAT_ELEKTRA       55
#define VERS_FMFAT_FM            56
#define VERS_FMFAT_FXR           57
#define VERS_FMFAT_FXA           58
#define VERS_FMFAT_K0            59
#define VERS_FMFAT_K1            60
#define VERS_FMFAT_K2            61
#define VERS_FMFAT_E0            62
#define VERS_FMFAT_E1            63
#define VERS_FMFAT_E2            64

#define VERS_FMT2_FM             100    /* Id = 1 ProcNr = 1001 */
#define VERS_FMT2_FXP            101    /* Id = 1 ProcNr = 1020 */
#define VERS_FMT2_FXA            102    /* Id = 1 ProcNr = 1030 */
#define VERS_FMT2_FM_2F          103    /* Id = 1 ProcNr = 2001 */
#define VERS_FMT2_FM_3F          104    /* Id = 1 ProcNr = 3001 */
#define VERS_FMT2_FXP_2F         105    /* Id = 1 ProcNr = 2020 */
#define VERS_FMT2_FXA_2F         106    /* Id = 1 ProcNr = 2030 */
#define VERS_FMT2_GRAPHIC        107    /* Id = 2 */
#define VERS_FMT2_FXP_3F         108    /* Id = 1 ProcNr = 3020 */
#define VERS_FMT2_FXA_3F         109    /* Id = 1 ProcNr = 3030 */

#define VERS_FX25_FX             150    /*  */
#define VERS_FMT1_FM             170    /*  */

#define VERS_ARBURG_C            200

#define VERS_DEMAG_NC4           210
#define VERS_FREE                220

#define ARTNO_SIZE      64
#define TOOLNO_SIZE     64
#define MATNO_SIZE      64
#define MACHTYPE_SIZE   64
#define MACHNO_SIZE     32
#define DECRIPTION_SIZE 128
#define FILE_NAME_SIZE  128
#define DESCRIPTION_SIZE  256

#define TOOLFILE_MAGIC  0xabcdef

typedef struct _file_info
{  USHORT_T format;
   USHORT_T version;
   ULONG_T size;
   ULONG_T date;
   CHAR_T artno[ARTNO_SIZE];
   CHAR_T toolno[TOOLNO_SIZE];
   CHAR_T matno[MATNO_SIZE];
   CHAR_T machtype[MACHTYPE_SIZE];
   CHAR_T machno[MACHNO_SIZE];
   CHAR_T description[DESCRIPTION_SIZE];
}  FILE_INFO_T;

typedef struct _toolfile_header {
   ULONG_T magic;
   CHAR_T file_name[FILE_NAME_SIZE];
   FILE_INFO_T file_info;
}  TOOLFILE_HEADER_T;





typedef struct _sub_file {
   CHAR_T file_name[FILE_NAME_SIZE];
   ULONG_T offset;
   ULONG_T size;
}  SUB_FILE_T;

#define MAX_SUB_FILES   10
typedef struct _toolfile_subheader {
   ULONG_T file_count;
   SUB_FILE_T files[MAX_SUB_FILES];
}  TOOLFILE_SUBHEADER_T;

typedef struct _toolfile {
   ULONG_T magic;
   CHAR_T file_name[FILE_NAME_SIZE];
   FILE_INFO_T file_info;
   TOOLFILE_SUBHEADER_T subheader;
}  TOOLFILE_T;

#endif
