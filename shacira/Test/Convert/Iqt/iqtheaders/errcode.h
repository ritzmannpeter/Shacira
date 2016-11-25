/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     ERRCODE.H 
*
*  BESCHREIBUNG:
*     ...
*
*  UMGEBUNG:
*     ZIELRECHNER:           IQT-450
*     ENTWICKLUNGSRECHNER:   PC-AT/QNX v3.15
*     UEBERSETZER:           c86 v3.3
*     OPTIONEN:              ...
*
*  VERSION:
*     VERSION:    4.0                       DATUM:   14.07.92
*     AUTOR(EN):  -TS-   T. Schoenig        TELEFON: (0761) 42257
*
*  HISTORY:
*     14.07.92 -TS-    Erstellung
*     08.10.92 -SF-    Fehler des Bildschirmtreibers eingebaut (ERR_DEVCRT)
*     14.10.92 -MBa-   DEVHOST u. HOSTSRV Fehlermeldungen eingefuehrt 
*     29.12.92 -PR-    Fehlermeldungen Prozessgrafik eingefuehrt
*     08.11.00 -TSchw- Fehlermeldungen für Kartenleser eingefügt (siehe MEMCARD)
*     13.03.01 -TSchw- Fehlermeldungen für Euromap 17 Device eingefügt
*                      (siehe DEVEM17).
*     09.04.01 -TSchw- ERR_DEVCARD_BUFFER_TOO_SMALL neu eingefügt
*
*
*
*  BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  PROTOTYPEN:
*     Keine
*
*  DATENTYPEN:
*     Keine
*
*.EH.***********************************************************************/

#ifndef _errcode
#define _errcode


/****************************************************************************
* Vordefinierte Diagnosemeldungen allgemeiner Art
****************************************************************************/
#define ERR_NOT_AVAILABLE      -5001
#define ERR_BAD_ID             -5002
#define ERR_READ_ONLY_ID       -5003
#define ERR_BAD_PARAMETERS     -5004
#define ERR_ILLEGAL_DEVICE     -5005
#define ERR_IDLE               -5006
#define ERR_INTERNAL           -5007
#define ERR_MEMORY_FULL        -5008
#define ERR_TIMEOUT            -5009
#define ERR_GET_ATTR           -5010    
#define ERR_GET_STTY           -5011     
#define ERR_DRAM_ALLOC         -5012 /* Fehler bei MemAlloc() */
#define ERR_DRAM_FREE          -5013 /* Fehler bei MemFree() */
#define ERR_BBRAM_ALLOC        -5014 /* Fehler bei BbrAlloc() */
#define ERR_SEM_INIT           -5015 /* Semaphore nicht initialisiert */
/* #define ERR_LAST_BUFALLOC      -5016 */ /* Post mortem dump von BufAlloc beim Aufstart */
#define ERR_BUFALLOC           -5017 /* Fehler im Modul BUFALLOC */
#define ERR_ILLEGAL_HANDLE     -5018 
#define ERR_INVALID_TIME_BASE  -5019

/****************************************************************************
* Diagnosemeldungen Programmkomplex IQTTSK
****************************************************************************/
#define ERR_IQTTSK_NAME_LOCATE_TSKSTART   -100
#define ERR_IQTTSK_SET_TIMER              -101
#define ERR_IQTTSK_NAME_LOCATE_TSKSRV     -102
#define ERR_IQTTSK_NOTID_TSKPROTO                  -103
#define ERR_IQTTSK_NOTID_TSKSTART                  -104
#define ERR_IQTTSK_NOTID_TSKSRV               -105
#define ERR_IQTTSK_CREATEQ                -106
#define ERR_IQTTSK_NAME_LOCATE_TSKPROTO   -107
#define ERR_IQTTSK_FIFO_FULL              -108
#define ERR_IQTTSK_FIFO_SIZING            -109
#define ERR_IQTTSK_FIFO_INIT_STRUCT       -110
#define ERR_IQTTSK_DEFAULT                -111
#define ERR_IQTTSK_SEM_P                  -112
#define ERR_IQTTSK_SEM_V                  -113
#define ERR_IQTTSK_SEM_PCOUNT             -114
#define ERR_IQTTSK_SEM_VCOUNT             -115
#define ERR_IQTTSK_SEM_INIT               -116
#define ERR_IQTTSK_START_TASK                   -117
#define ERR_IQTTSK_STOP_TASK                    -118
#define ERR_IQTTSK_INVALID_TIND                 -119

/****************************************************************************
* Diagnosemeldungen Programmkomplex IQTMEM
****************************************************************************/
#define ERR_IQTMEM_MEM_INIT                      -150
#define ERR_IQTMEM_BBRAM_ALLOC                -151
#define ERR_IQTMEM_INIT_DIAG                  -152
#define ERR_IQTMEM_NO_PTR_SPACE               -153

/****************************************************************************
* Diagnosemeldungen Programmkomplex TSKSTART
****************************************************************************/
#define ERR_TSKSTART_TASK_NOT_FOUND       -200
#define ERR_TSKSTART_NAME_ATTACH          -201
#define ERR_TSKSTART_CREATEV              -202
#define ERR_TSKSTART_MALLOC               -203
#define ERR_TSKSTART_NO_PORT              -204
#define ERR_TSKSTART_NO_TIMER             -205
#define ERR_TSKSTART_CYCL_STATE_NOTASK    -206
#define ERR_TSKSTART_MEMORY_LINK          -207
#define ERR_TSKSTART_CREATEQ              -208

/****************************************************************************
* Diagnosemeldungen Programmkomplex TSKSRV
****************************************************************************/
#define ERR_TSKSRV_NAME_ATTACH            -251

/****************************************************************************
* Diagnosemeldungen Programmkomplex COMSRV
****************************************************************************/
#define ERR_COMSRV_NAME_ATTACH            -300
#define ERR_COMSRV_GET_STTY               -301
#define ERR_COMSRV_GET_ATTR               -302
#define ERR_COMSRV_BAD_HARDWARE           -303
#define ERR_COMSRV_PRINTER_NOT_AVAIL      -304
#define ERR_COM_OPEN_READ_STREAM          -305
#define ERR_COM_OPEN_WRITE_STREAM         -306
#define ERR_COMSRV_SET_ATTR               -307
#define ERR_COM_TIMEOUT                   -308
#define ERR_COM_INVALID_BASE              -309

/****************************************************************************
* Diagnosemeldungen Programmkomplex DISKSRV
****************************************************************************/
#define ERR_DISKSRV_NAME_ATTACH           -350

/****************************************************************************
* Diagnosemeldungen Programmkomplex TSKPROTO
****************************************************************************/
#define ERR_TSKPROTO_NAME_ATTACH          -351
#define ERR_TSKPROTO_FILE_NAME            -352 

/****************************************************************************
* Diagnosemeldungen Programmkomplex TSKPROST
****************************************************************************/
#define ERR_TSKPROST_NAME_LOCATE_TSKPROTO -400 

/****************************************************************************
* Diagnosemeldungen Programmkomplex DEVCOM
****************************************************************************/
#define ERR_DEVCOM_BAD_ID                             -450
#define ERR_DEVCOM_BAD_HARDWARE           -451
#define ERR_DEVCOM_BAD_BAUD_RATE              -452
#define ERR_DEVCOM_BAD_STOP_NUM               -453
#define ERR_DEVCOM_BAD_PARITY                 -454
#define ERR_DEVCOM_BAD_CHAR_LEN               -455
#define ERR_DEVCOM_GET_ATTR                   -456
#define ERR_DEVCOM_GET_STTY                   -457
#define ERR_DEVCOM_BAD_DATA_PROTOCOL      -458
#define ERR_DEVCOM_BAD_CHECKSUM           -459
#define ERR_DEVCOM_TIME_OUT               -460
#define ERR_DEVCOM_EOS_DETECTED           -461
#define ERR_DEVCOM_EOF_DETECTED           -462
#define ERR_DEVCOM_WHILE_TRANSMISSION     -463
#define ERR_DEVCOM_MEMORY_FULL            -465
#define ERR_DEVCOM_NAME_LOCATE_COMSRV     -466

/****************************************************************************
* Diagnosemeldungen Programmkomplex DEVKBD
****************************************************************************/
#define ERR_DEVKBD_SENDSHOWBUF            -501
#define ERR_DEVKBD_INITFILTER             -502
#define ERR_DEVKBD_MEM_MSGPORT_KBD        -503
#define ERR_DEVKBD_MEM_MSGPORT_KBDAT      -504
#define ERR_DEVKBD_OPEN_MEM               -505
#define ERR_DEVKBD_OPEN_MSGSEND           -506
#define ERR_DEVKBD_CLOSE_MSGSEND          -507
#define ERR_DEVKBD_READ_MSGSEND           -508
#define ERR_DEVKBD_EXAMINE_MSGSEND        -510
#define ERR_DEVKBD_BAD_ID                 -511
#define ERR_DEVKBD_TIMEOUT                -512
                                                         
/****************************************************************************
* Diagnosemeldungen Programmkomplex DEVKBDMA
****************************************************************************/
#define ERR_DEVKBDMA_MEM_MSGPORT_KBD      -551
#define ERR_DEVKBDMA_MEM_MSGPORT_KBDAT    -552
                                      
/****************************************************************************
* Diagnosemeldungen Programmkomplex DEVKBDAT
****************************************************************************/
#define ERR_DEVKBDAT_MEM_MSGPORT_KBD      -601
#define ERR_DEVKBDAT_MEM_MSGPORT_KBDAT    -602
#define ERR_DEVKBDAT_GET_ATTR             -603
#define ERR_DEVKBDAT_SET_ATTR             -604
                                                         
/****************************************************************************
* Diagnosemeldungen Programmkomplex DEVPRN
****************************************************************************/
#define ERR_DEVPRN_PRN_PRGRID             -651
#define ERR_DEVPRN_BAD_PARAMETERS         -653
#define ERR_DEVPRN_MEMORY_FULL            -654 
#define ERR_DEVPRN_COMMUNICATION          -655 
#define ERR_DEVPRN_USER                   -656
#define ERR_DEVPRN_INVALID_BUFFER         -657
#define ERR_DEVPRN_BAD_OPENBLOCK          -658
#define ERR_DEVPRN_BAD_COMHANDLE          -659
#define ERR_DEVPRN_INVALID_FONT           -660
#define ERR_DEVPRN_INVALID_MODE           -661

/****************************************************************************
* Diagnosemeldungen Programmkomplex DEVCEN
****************************************************************************/
#define ERR_DEVCEN_NUM_DEVICES            -701
#define ERR_DEVCEN_MEMORY_FULL            -702
#define ERR_DEVCEN_BAD_HW                 -703
#define ERR_DEVCEN_FPUTC                  -704
#define ERR_DEVCEN_NAME_LOCATE_COMSRV     -705
#define ERR_DEVCEN_INVALID_DEVICE         -706

/****************************************************************************
* Diagnosemeldungen Programmkomplex PRINT
****************************************************************************/
#define ERR_PRNPAGE_HARDCOPY                -750
#define ERR_PRNPAGE_DEV_OPEN                -751
#define ERR_PRNPAGE_PAGE_NO                 -752
#define ERR_PRNPAGE_BUFFER_CLEARED          -753
#define ERR_PRNPAGE_SOLL_FORMAT             -754

/****************************************************************************
* Diagnosemeldungen Programmkomplex DEVDISK
****************************************************************************/

#define ERR_DISK_FORMAT         -850
#define ERR_DISK_OPEN           -851
#define ERR_DISK_EXPAND         -852
#define ERR_DISK_READ           -853
#define ERR_DISK_WRITE          -854
#define ERR_DISK_DEL            -855
#define ERR_WRITE_PROTECT       -856

#define ERR_CAR_NOT_READY       -870
#define ERR_CAR_WRONG_FORMAT    -871
#define ERR_CAR_NO_DIR_ENTRY    -872
#define ERR_CAR_FILE_EXISTS     -873
#define ERR_CAR_NO_EEPROM       -874
#define ERR_CAR_ADDRESS         -875
#define ERR_INVALID_DISKID      -876
#define ERR_INVALID_SPINFO      -877

#define ERR_NO_DEVICE           -910
#define ERR_DEVICE_FULL         -911
#define ERR_PAST_END            -912
#define ERR_FILE_NOT_FOUND      -913
#define ERR_MULTIPLE_FILE       -914
#define ERR_DIR_FULL            -915
#define ERR_UNKNOWN             -916
#define ERR_HARDWARE            -917
#define ERR_BAD_MODE            -918
#define ERR_READ                -919
#define ERR_WRITE               -920
#define ERR_NO_FILESYSTEM       -921
#define ERR_DIR_OPEN            -923

/****************************************************************************
* Diagnosemeldungen Programmkomplex IQTREGIM
****************************************************************************/
#define ERR_IQTREGIM                            -950

/* Fehlerkonstanten Kundenprom */
#define KPROM_ERR_OPEN_CONFIG   -960
#define KPROM_ERR_ALLOC_BBRAM   -961
#define KPROM_ERR_GET_FILEPOS   -962
#define KPROM_ERR_SET_FILEPOS   -963

/****************************************************************************
* Diagnosemeldungen Programmkomplex DEVHOST
****************************************************************************/

#define HOST_ERR_NO_LINE  -980   /* no open line for host-connection */
#define HOST_ERR_NO_DATA  -981   /* no data-block available (get from host) */
#define HOST_ERR_RETRY    -982   /* too many retries (put to host) */
#define HOST_ERR_TIMEOUT  -983   /* timeout error */
#define HOST_ERR_EOT      -984   /* EOT received */
#define HOST_ERR_ENQ      -985   /* ENQ received */
#define HOST_ERR_ETB      -986   /* ETB received */
#define HOST_ERR_MASK     -987   /* Blendet alle "unechten" Fehler aus */
#define HOST_ERR_NAME_LOCATE -988 /* name_locate versagte */
#define ERR_HSTTSK_NAME_ATTACH -989

/****************************************************************************
* Diagnosemeldungen Programmkomplex HOSTSRV
****************************************************************************/

#define ERR_HSTSRV_NAME_ATTACH            -990


/****************************************************************************
* Diagnosemeldungen Programmkomplex DEVCRT
****************************************************************************/
#define ERR_DEVCRT_NO_OBJECT       -1000
#define ERR_DEVCRT_NO_PARENT       -1001
#define ERR_DEVCRT_BAD_PARENT      -1002
#define ERR_DEVCRT_BAD_FONTNAME    -1003
#define ERR_DEVCRT_BAD_FONT        -1004
#define ERR_DEVCRT_BAD_MODE        -1005
#define ERR_DEVCRT_BAD_STATE       -1006
#define ERR_DEVCRT_BAD_GRAPHCMD    -1007
#define ERR_DEVCRT_BAD_BKGND       -1008
#define ERR_DEVCRT_OUT_OF_SCREEN   -1009
#define ERR_DEVCRT_OUT_OF_WINDOW   -1010
#define ERR_DEVCRT_OUT_OF_RANGE    -1011
#define ERR_DEVCRT_WINDOW_TOO_BIG  -1012
#define ERR_DEVCRT_NOT_CHILDLESS   -1013
#define ERR_DEVCRT_TXTREAD         -1014
#define ERR_DEVCRT_TXTREADCOL      -1015
#define ERR_DEVCRT_GRFREAD         -1016

/****************************************************************************
* Diagnosemeldungen Programmkomplex CRTGRF
****************************************************************************/
#define ERR_CRTGRF_OBJECT_EXIST           -1050
#define ERR_CRTGRF_NO_INIT_GRAPH          -1051
#define ERR_CRTGRF_FILE_NOT_FOUND         -1052
#define ERR_CRTGRF_INVALID_DRIVER         -1053
#define ERR_CRTGRF_NO_LOAD_MEM            -1054
#define ERR_CRTGRF_INVALID_MODE           -1055
#define ERR_CRTGRF_NO_VIEWPORT_SELECT     -1056
#define ERR_CRTGRF_INVALID_FONT_NUM       -1057
#define ERR_CRTGRF_NO_FREE_MEMORY         -1058
#define ERR_CRTGRF_BAD_COORDINATES        -1059
#define ERR_CRTGRF_TO_MUCH_VIEWPORTS      -1060
#define ERR_CRTGRF_VIEWPORT_NOT_OPENED    -1061
#define ERR_CRTGRF_VIEWPORT_TO_DEPTH      -1062
#define ERR_CRTGRF_NO_VIEWPORT_INIT       -1063
#define ERR_CRTGRF_OUT_OF_SCREEN          -1064
#define ERR_CRTGRF_VIEWPORT_ALREADY_INIT  -1065
#define ERR_CRTGRF_BAD_PARAMETER          -1066
#define ERR_CRTGRF_IMAGE_ERROR            -1067
#define ERR_CRTGRF_VIEWPORT_PROTECTED     -1068
#define ERR_CRTGRF_NOT_SUPPORTED          -1069
#define ERR_CRTGRF_UNKNOWN                -1070


/****************************************************************************
* Diagnosemeldungen Modul NAMEDBUF
****************************************************************************/
#define ERR_NAMED_NO_MEMORY       -1100
#define ERR_NAMED_NO_BUF          -1101
#define ERR_NAMED_BUF_FULL        -1102
#define ERR_NAMED_INVALID_POS     -1103

/****************************************************************************
* Diagnosemeldungen Modul IFK
****************************************************************************/
#define ERR_IFK_OPEN_PPCCOM       -1110
#define ERR_IFK_OPEN_CENTRONICS   -1111
#define ERR_IFK_OPEN_SERCOMLINE   -1112
#define ERR_IFK_OPEN_MEMCARD      -1113 /* MEMCARD */


/****************************************************************************
* Diagnosemeldungen Modul IFK
****************************************************************************/
#define ERR_PG_NO_ENDMARK           -1120
#define ERR_PG_INVALID_CLIPBOARDID  -1121
#define ERR_PG_NO_ACTIVE_CLIPBOARD  -1122
#define ERR_PG_INVALID_PARAM        -1123
#define ERR_PG_READING_YSCALE_END   -1124
#define ERR_PG_READING_XSCALE_END   -1125
#define ERR_PG_INVALID_CURSORID     -1126
#define ERR_PG_TRANSFER_DATA        -1127
#define ERR_PG_INVALID_CLIPBOARD    -1128
#define ERR_PG_MEASURE              -1129


/* START MEMCARD */
/****************************************************************************
* Diagnosemeldungen Modul DEVCARD
****************************************************************************/
#define ERR_DEVCARD_INIT               -1150
#define ERR_DEVCARD_NOINIT             -1151
#define ERR_DEVCARD_INV_RW_DEST        -1152
#define ERR_DEVCARD_READWRITE          -1153
#define ERR_DEVCARD_INV_CARD           -1154
#define ERR_DEVCARD_INV_SUBFILE        -1155
#define ERR_DEVCARD_SUBFILE_NOT_FOUND  -1156
#define ERR_DEVCARD_NOT_ENOUGH_SPACE   -1157
#define ERR_DEVCARD_CHECKSUM_ERROR     -1158
#define ERR_DEVCARD_BUFFER_TOO_SMALL   -1159
/* END MEMCARD */

/****************************************************************************
* Diagnosemeldungen Modul DEVEM17
****************************************************************************/
#define ERR_DEVEM17_INIT               -1200
#define ERR_DEVEM17_INV_PROGNAME       -1201
#define ERR_DEVEM17_INV_CHECKSUM       -1202
#define ERR_DEVEM17_BUF_TOO_LOW        -1203
#define ERR_DEVEM17_ROBOT_WORKING      -1204
#define ERR_DEVEM17_WRITE_ERROR        -1205
#define ERR_DEVEM17_TIMEOUT            -1206
#define ERR_DEVEM17_NAK                -1207
#define ERR_DEVEM17_INV_ANSWER         -1208
#define ERR_DEVEM17_CHECKSUM_ERROR     -1209
#define ERR_DEVEM17_BLOCK_TOO_LONG     -1210
#define ERR_DEVEM17_INTERNAL           -1211
#define ERR_DEVEM17_BUFLEN_TOO_LONG    -1212

#endif /* _errcode */
