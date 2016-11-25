/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
/* name     : BTRIEVEW.H  for Windows                                      */
/* version  : 1.8.3 / 16.12.1991                                             */
/* function : descriptions for the Btrieve function calls                  */
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
/* date/sign : changes                                                     */
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
/*------------- only for version 5.1, Btrieve for Windows --------------

#define BTRIEVE5_1
-------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FAR
#define FAR far
#endif

#define BTRVDEBUG
#define FILE_DDF         "FILE.DDF"              /* names of Xtrieve files */
#define FIELD_DDF        "FIELD.DDF"
#define INDEX_DDF        "INDEX.DDF"
#define DBEXTENSION      ".DBF"            /* extension for database files */
#define MAXFILES          120        /* maximum number of Btrieve databases */
#define MAXPOSBLOCKSIZE  128             /* maximum size of Position Block */
#define MAXNAMESIZE       20
#define MAXPATHSIZE       64
#define MAXPATHNAMESIZE   84
#define DDFBUFFERSIZE     10

typedef char   STRING[256];
typedef HANDLE HBTR;

/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
//HBTR checkDatabase      (LPSTR, LPSTR, unsigned *);
HBTR checkDatabase      (int);

int  b_begin           (LPSTR);
int  b_end             (void);

//HBTR b_open            (LPSTR, LPSTR, int FAR *);
//HBTR b_open_read_only  (LPSTR, LPSTR, int FAR *);

HBTR b_open            (LPSTR, LPSTR, int FAR *, int);
HBTR b_open_read_only  (LPSTR, LPSTR, int FAR *, int);

int  b_close        (HBTR);
int  b_insert       (HBTR, int, LPSTR, void FAR *, BOOL);
int b_update        (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_delete       (HBTR, int, LPSTR, void FAR *, BOOL);
int b_delete_notest (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_create       (HBTR, int, LPSTR, void FAR *, BOOL);
//int  b_stat       (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_stat         (HBTR, int, LPSTR, void FAR *);
int  b_extend       (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_stop         (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_version      (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_unlock       (HBTR, int, LPSTR, void FAR *, BOOL);
int b_reset         (HBTR, int, LPSTR, void FAR *, BOOL);

int  b_setOwner        (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_clearOwner      (HBTR, int, LPSTR, void FAR *, BOOL);

int  b_createSuppIndex (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_dropSuppIndex   (HBTR, int, LPSTR, void FAR *, BOOL);

int  b_stepFirst       (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_stepLast        (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_stepNext        (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_stepPrev        (HBTR, int, LPSTR, void FAR *, BOOL);

int  b_setDirectory    (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_getDirectory    (HBTR, int, LPSTR, void FAR *, BOOL);

int  b_abortTransaction(HBTR, int, LPSTR, void FAR *, BOOL);
int  b_beginTransaction(HBTR, int, LPSTR, void FAR *, BOOL);
int  b_endTransaction  (HBTR, int, LPSTR, void FAR *, BOOL);

int  b_getDirect       (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_getEqual        (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_getFirst        (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_getGreater      (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_getGreaterEqual (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_getLast         (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_getLess         (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_getLessEqual    (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_getNext         (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_getPosition     (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_getPrev         (HBTR, int, LPSTR, void FAR *, BOOL);
#ifdef BTRIEVE5_1
int  b_getNextExtend   (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_getPrevExtend   (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_StepNextExtend  (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_StepPrevExtend  (HBTR, int, LPSTR, void FAR *, BOOL);
int  b_InsertExtend    (HBTR, int, LPSTR, void FAR *, BOOL);
#endif

int  b_getKey          (int, HBTR, int, LPSTR);

/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
/*   definitions to the Microsoft Btrieve interface                        */
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
#define BOPEN                       0                  /* basic operations */
#define BCLOSE                      1
#define BINSERT                     2
#define BUPDATE                     3
#define BDELETE                     4
#define BGETEQUAL                   5
#define BGETNEXT                    6
#define BGETPREV                    7
#define BGETGREATER                 8
#define BGETGREATEREQUAL            9
#define BGETLESS                   10
#define BGETLESSEQUAL              11
#define BGETFIRST                  12
#define BGETLAST                   13
#define BCREATE                    14
#define BSTAT                      15
#define BEXTEND                    16
#define BSETDIRECTORY              17
#define BGETDIRECTORY              18
#define BBEGINTRANSACTION          19
#define BENDTRANSACTION            20
#define BABORTTRANSACTION          21
#define BGETPOSITION               22
#define BGETDIRECT                 23
#define BSTEPNEXT                  24
#define BSTOP                      25
#define BVERSION                   26
#define BUNLOCK                    27
#define BRESET                     28
#define BSETOWNER                  29
#define BCLEAROWNER                30
#define BCREATESUPPINDEX  	        31
#define BDROPSUPPINDEX             32
#define BSTEPFIRST                 33
#define BSTEPLAST                  34
#define BSTEPPREV             	   35
#ifdef BTRIEVE5_1                             /* since Btrieve version 5.1 */
#define BNEXTEX                    36
#define BGETPREVEX                 37
#define STEPNEXTEX                 38
#define STEPPREVEX                 39
#define INSERTEX                   40
#endif

#define BGETKEY                    50               /* extended operations */
#define BSINGLEWAITLOCK           100
#define BSINGLENOWAITLOCK         200
#define BMULTIPLEWAITLOCK         300
#define BMULTIPLENOWAITLOCK       400

   /* File Flag Values            Code */

#define BVARIABLELENGTH             1
#define BBLANKTRUNCATION            2
#define BPREALLOCATION              4
#define BDATACOMPRESSION            8
#define BKEYONLY                   16
#define BFREESPACE10PERCENT        64
#define BFREESPACE20PERCENT       128
#define BFREESPACE30PERCENT       192

   /* Key-Attribute               Code */

#define BDUPLICATE                  1
#define BMODIFIABLE                 2
#define BBINARY                     4
#define BNULL                       8
#define BSEGMENTED                 16
#define BALTCOLSEQ                 32
#define BDESCENDING                64
#define BSUPPLEMENTAL             128
#define BEXTENDEDTYPE             256
#define BMANUAL                   512

   /*   extended key types       Value */

#define BSTRING                     0
#define BINTEGER                    1
#define BFLOAT                      2
#define BDATE                       3
#define BTIME                       4
#define BDECIMAL                    5
#define BMONEY                      6
#define BLOGICAL                    7
#define BNUMERIC                    8
#define BBFLOAT                     9
#define BLSTRING                   10
#define BZSTRING                   11
#define BUNSIGNEDBINARY            14
#define BAUTOINCREMENT             15

/* attributs for opening database */
#define BOPEN_NORMAL                0
#define BOPEN_ACCELERATED          -1
#define BOPEN_READ_ONLY            -2
#define BOPEN_VERIFY               -3
#define BOPEN_EXCLUSIVE            -4

#define MAXKEYLEN                 255       /* maximum length of key value */

/* Typen-Definition of Btrieve.h */

typedef struct
	{
	  unsigned short recordlength;
	  unsigned short pagesize;
	  unsigned short indexes;
	  long 		 NumberOfRecords;
	  unsigned short fileflags;
	  unsigned short reservedword;
	  unsigned short allocation;
	} FILESPECS;

typedef struct
	{
	  unsigned short keyposition;
	  unsigned short keylength;
	  unsigned short keyflags;
	  long 		 NumberOfKeys;
	  unsigned char  extendedKeyType;
	  unsigned char  nullvalue;
	  long		 reserved;
	} KEYSPECS;

/***************************************************************************/
/*                                                                         */
/* Novell, Inc.                                                            */
/* Devleopment Products Division                                           */
/* Btrieve Record Manager                                                  */
/*                                                                         */
/* WBTRV.H                                                                 */
/*                                                                         */
/* - Function prototypes for the MS-Windows DLL version of Btrieve         */
/*                                                                         */
/***************************************************************************/

#if defined(__NT__)
#define BCALL __far16 PASCAL
#elif defined(APPL_ETCL)
#define BCALL PASCAL
#else
#define BCALL FAR PASCAL
#endif

/* -------------------------------------------------------------------------
   Btrieve initialization - returns 0 if successful
---------------------------------------------------------------------------*/
extern int BCALL WBTRVINIT (char FAR *);

/* -------------------------------------------------------------------------
   Btrieve requester initialization - returns 0 if successful
---------------------------------------------------------------------------*/
extern int BCALL WBRQSHELLINIT (char FAR *);

/* -------------------------------------------------------------------------
 Btrieve function execution - returns 0 if successful
---------------------------------------------------------------------------*/
extern int BCALL BTRCALL (int,
                               char FAR *,
                               char FAR *,
                               unsigned FAR *,
                               char FAR *,
                               unsigned char,
                               char);

/* ------------------------------------------------------------------------
   Termination processing - MUST be called prior to terminating application.
   Place this call in the application's WM_CLOSE or equivalent message case.
   Returns 0 if successful;  if a non-zero status is returned, files have
   been left open or a transaction active. Perform a Reset operation and
   call the function again, or close files properly and exit again.
---------------------------------------------------------------------------*/
extern int BCALL WBTRVSTOP (void);

int BTRV (int           operation,
          LPSTR         posblk,
          LPSTR         databuf,
          unsigned FAR *datalen,
          LPSTR         keyP,
          int           keyNumber);

/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
#ifdef BTRVDEBUG                         /* for debugging the applications */
int OpenInfo(LPSTR lpName);
void Info(int hfile, LPSTR lpStr1, LPSTR lpStr2, int nValue, int nStr2Len);
#endif


VOID DBCounter(HANDLE hDlg, LPSTR lpszCaption); // WW:12.12.91

BOOL myGlobalUnlock(HGLOBAL hglb);
void FAR * myGlobalLock(HGLOBAL hglb);

#ifdef __cplusplus
};
#endif

