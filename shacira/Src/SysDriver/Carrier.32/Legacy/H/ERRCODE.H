
#ifndef _errcode
#define _errcode

/* zusaetzliche Systemfehler
 */
#define ENOTOP  40            /* file not open  */
#define ENOF    41            /* no files found */

/* vorerst, da bei FMT2 nicht abgebildet
 */
#define DCAR_OK                    0
#define DCAR_NO_MEMORY             -49
#define DCAR_INIT                  -50
#define DCAR_BAD_TYP               -51
#define DCAR_NOT_FOUND             -52
#define DCAR_VERIFY_ERROR          -53
#define DCAR_NO_EEPROM             -54
#define DCAR_NOT_READY             -55
#define DCAR_ADR_ERROR             -56
#define DCAR_NULL_SIZE             -57
#define DCAR_DELAY_SIZE            -58
#define DCAR_READ_ERROR            -59
#define DCAR_INVALID_MODE          -60
#define DCAR_READ_FAILED           -61
#define DCAR_NO_SIZE_DETECTED      -62
#define DCAR_HW                    -63

#define BASIC_INVALID_IO_TYPE      -70

#define FILES_FILEMAP_FULL             -100

#define CSTDIO_SIZE_NOT_SUPPORTED      -200
#define CSTDIO_NO_FORMAT_INFO          -201
#define CSTDIO_NO_FILE_FORMAT_DETECTED -202

#define FMT2_INVALID_FILENO            -300
#define FMT2_INVALID_FILENAME          -301
#define FMT2_NO_MEMORY                 -302
#define FMT2_INVALID_HANDLE            -303
#define FMT2_FILE_ALROP                -304
#define FMT2_FILE_NOTOP                -305
#define FMT2_INVALID_PROGLEN           -306
#define FMT2_CHECKSUM                  -307
#define FMT2_CHECKSUM1                 -308
#define FMT2_CHECKSUM2                 -309
#define FMT2_CHECKSUM3                 -310
#define FMT2_INVALID_SEEKPOS           -311
#define FMT2_INVALID_MODE              -312
#define FMT2_INVALID_PROCNO            -313
#define FMT2_INVALID_VERSION           -314
#define FMT2_FILE_OPEN_FAILURE         -315
#define FMT2_FILE_READ_FAILURE         -316
#define FMT2_FILE_WRITE_FAILURE        -317
#define FMT2_INVALID_CARRIER_ID        -318
#define FMT2_FILE_SEEK_ERROR           -319
#define FMT2_INVALID_REGID             -320
#define FMT2_REG_NOT_ALLOWED           -321
#define FMT2_GRAPHIC_NOT_SUPPORTED     -322
#define FMT2_2F_CHECKSUM               -323
#define FMT2_3F_CHECKSUM               -324
#define FMT2_FORMAT_NOT_SUPPORTED      -325

#define FX25_INVALID_FILENO            -400
#define FX25_INVALID_FILENAME          -401
#define FX25_NO_MEMORY                 -402
#define FX25_INVALID_HANDLE            -403
#define FX25_FILE_ALROP                -404
#define FX25_FILE_NOTOP                -405
#define FX25_INVALID_PROGLEN           -406
#define FX25_CHECKSUM                  -407
#define FX25_CHECKSUM1                 -408
#define FX25_CHECKSUM2                 -409
#define FX25_CHECKSUM3                 -410
#define FX25_INVALID_SEEKPOS           -411
#define FX25_INVALID_MODE              -412
#define FX25_INVALID_HEADERLEN         -413
#define FX25_FILE_OPEN_FAILURE         -414
#define FX25_FILE_READ_FAILURE         -415
#define FX25_FILE_NOT_CLEARED          -416
#define FX25_USER_CHECK_ERR            -417
#define FX25_FILE_WRITE_FAILURE        -418
#define FX25_FILE_SEEK_ERROR           -419
#define FX25_INVALID_REGID             -420

#define FMT1_INVALID_FILENO            -600
#define FMT1_INVALID_FILENAME          -601
#define FMT1_NO_MEMORY                 -602
#define FMT1_INVALID_HANDLE            -603
#define FMT1_FILE_ALROP                -604
#define FMT1_FILE_NOTOP                -605
#define FMT1_INVALID_PROGLEN           -606
#define FMT1_CHECKSUM                  -607
#define FMT1_CHECKSUM1                 -608
#define FMT1_CHECKSUM2                 -609
#define FMT1_CHECKSUM3                 -610
#define FMT1_INVALID_SEEKPOS           -611
#define FMT1_INVALID_MODE              -612
#define FMT1_INVALID_HEADERLEN         -613
#define FMT1_FILE_OPEN_FAILURE         -614
#define FMT1_FILE_READ_FAILURE         -615
#define FMT1_FILE_NOT_CLEARED          -616
#define FMT1_USER_CHECK_ERR            -617
#define FMT1_FILE_WRITE_FAILURE        -618
#define FMT1_FILE_SEEK_ERROR           -619
#define FMT1_INVALID_REGID             -620

#define RAW_INVALID_FILENO            -300
#define RAW_INVALID_FILENAME          -301
#define RAW_NO_MEMORY                 -302
#define RAW_INVALID_HANDLE            -303
#define RAW_FILE_ALROP                -304
#define RAW_FILE_NOTOP                -305
#define RAW_INVALID_PROGLEN           -306
#define RAW_CHECKSUM                  -307
#define RAW_CHECKSUM1                 -308
#define RAW_CHECKSUM2                 -309
#define RAW_CHECKSUM3                 -310
#define RAW_INVALID_SEEKPOS           -311
#define RAW_INVALID_MODE              -312
#define RAW_INVALID_PROCNO            -313
#define RAW_INVALID_VERSION           -314
#define RAW_FILE_OPEN_FAILURE         -315
#define RAW_FILE_READ_FAILURE         -316
#define RAW_FILE_WRITE_FAILURE        -317
#define RAW_INVALID_CARRIER_ID        -318
#define RAW_FILE_SEEK_ERROR           -319
#define RAW_INVALID_REGID             -320
#define RAW_REG_NOT_ALLOWED           -321

#define FMFAT_INVALID_HEADERLEN        -500
#define FMFAT_UNKNOWN_MACHTYPE         -501
#define FMFAT_INVALID_DATE             -502
#define FMFAT_UNKNOWN_HEADER           -503
#define FMFAT_FILE_OPEN_FAILURE        -504
#define FMFAT_FILE_READ_FAILURE        -505
#define FMFAT_SUBFILETAB_MISSING       -506
#define FMFAT_TEXTVAR_NOT_FOUND        -507
#define FMFAT_INVALID_TEXT_SIZE        -508
#define FMFAT_INCONSISTENT_SUBFILE_ID  -509
#define FMFAT_INVALID_SUBFILE_POSITION -510
#define FMFAT_SUBFILETAB_READ_FAILED   -511
#define FMFAT_FILE_SEEK_ERROR          -512
#define FMFAT_FILE_READ_ERROR          -513
#define FMFAT_FILE_WRITE_ERROR         -514
#define FMFAT_OFFSET_INVALID           -515
#define FMFAT_FILE_WRITE_FAILURE       -516
#define FMFAT_TEXT_COMPRESSED          -517
#define FMFAT_SUBFILETAB_CORRUPTED     -518
#define FMFAT_REG_NOT_FOUND            -519
#define FMFAT_INVALID_REG_VALUESIZE    -520
#define FMFAT_INVALID_INDEX            -521
#define FMFAT_CORRUPTED_REG_SUBFILE    -522
#define FMFAT_REG_NOT_ALLOWED          -523

#define ERR_DISK_FORMAT                -850
#define ERR_DISK_OPEN                  -851
#define ERR_DISK_EXPAND                -852
#define ERR_DISK_READ                  -853
#define ERR_DISK_WRITE                 -854
#define ERR_DISK_DEL                   -855
#define ERR_WRITE_PROTECT              -856

#define ERR_CAR_NOT_READY              -870
#define ERR_CAR_WRONG_FORMAT           -871
#define ERR_CAR_NO_DIR_ENTRY           -872
#define ERR_CAR_FILE_EXISTS            -873
#define ERR_CAR_NO_EEPROM              -874
#define ERR_CAR_ADDRESS                -875
#define ERR_INVALID_DISKID             -876
#define ERR_INVALID_SPINFO             -877

#define ERR_NO_DEVICE                  -910
#define ERR_DEVICE_FULL                -911
#define ERR_PAST_END                   -912
#define ERR_FILE_NOT_FOUND             -913
#define ERR_MULTIPLE_FILE              -914
#define ERR_DIR_FULL                   -915
#define ERR_UNKNOWN                    -916
#define ERR_HARDWARE                   -917
#define ERR_BAD_MODE                   -918
#define ERR_READ                       -919
#define ERR_WRITE                      -920
#define ERR_NO_FILESYSTEM              -921

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


#endif /* _errcode */
