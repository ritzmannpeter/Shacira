#include "trace.h"
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
/* name     : BTRIEVEW.C                                                   */
/* version  : 1.8.3 / 16.12.1991                                           */
/* function : interface for Btrieve function calls includes MSCXBTRV.C     */
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
/* date/sign          : changes                                            */
/* 13.03.91/Linse     : MSCXBTRV.C included                                */
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
#define NOCOMM                /* for Windows */

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include <time.h>
#include <signal.h>
#include "BTRIEVEW.H"
#ifndef APPL_ETCL
#include "debug.h"
#endif
#include <stdio.h>

#define AskLock(bLock) (bLock ? BSINGLENOWAITLOCK : 0)



/******************************************************************/

typedef struct
{                                       /* stores the database description */
  char  szPosBlock[MAXPOSBLOCKSIZE];      /* Positionblock of the Database */
  unsigned nSize;                    /* size of the databuffer from FIELD.DDF */
  unsigned bti_handle;                 /* Btrieve-Handle aus szPosBlock */
} FILELISTTYP;

static FILELISTTYP FAR *pFileList;
static int         nStatus;               /* requeststatus used everywhere */

static int nOpenCloseCounter = 0;

static int nLockCounter = 0;
#define MAX_HNDL 100
static HGLOBAL lock_hndl[MAX_HNDL] = {0};
static int lock_hndl_cnt[MAX_HNDL] = {0};
static int lock_index_cnt = 0;
static unsigned long error_da = 0;
static unsigned long error2_da = 0;
static int loop_cnt = 0;



/* 04.06.96 -TE- BEGIN BTRVc() */

#define PFLTYP(pf)        ( (FILELISTTYP FAR *)(pf) )
#define BTI_POSBLK(pf,i)  ( (unsigned char) (PFLTYP(pf)->szPosBlock[(i)]) )
#define BTI_HANDLE(pf)    ( BTI_POSBLK(pf,126) + (unsigned short)BTI_POSBLK(pf,127)*256 )
#define BTI_OK(pf)        ( BTI_POSBLK(pf,38) == 0xcb && PFLTYP(pf)->bti_handle == BTI_HANDLE(pf) )

#define __BTI_CHECK__
#ifdef __BTI_CHECK__

   int BTRVc(FILELISTTYP FAR *pf, int op, char FAR *pb,
      char FAR *buf, unsigned FAR *len, char FAR *keyp, int key)
   {
      int rc;
      char errmsg[132];

      if ( !BTI_OK(pf) ) {
         sprintf(errmsg, "BTRIEVE CHECK FAILED before (%d, %08x, %08x, %d, %08x, %d)",
            op, pb, buf, len, keyp, key);
         b_err_proto(errmsg);
      }

      rc = BTRV(op, pb, buf, len, keyp, key);

      if ( !BTI_OK(pf) ) {
         sprintf(errmsg, "BTRIEVE CHECK FAILED  after (%d, %08x, %08x, %d, %08x, %d)",
            op, pb, buf, len, keyp, key);
         b_err_proto(errmsg);
      }

      return rc;
   }

#else

   #define BTRVc(pf, op, pb, buf, len, keyp, key)   BTRV(pf, op, pb, buf, len, keyp, key)

#endif

/* 04.06.96 -TE- END BTRVc() */



//**************************************************************************

int b_err_mess(char * Errorbuf, char * Infobuf)
Begin ("b_err_mess")
	MessageBox(NULL,(LPCSTR) Errorbuf,(LPCSTR)Infobuf,MB_ICONSTOP|MB_OK|MB_TASKMODAL);
	Return 0 ;
End

//**************************************************************************

int b_err_proto(char * Errorbuf)
Begin ("b_err_proto")

   #ifdef APPL_ETCL

      extern void PASCAL DbgPrint(const char *fmt, ...);
      DbgPrint(Errorbuf);

   #else

   	struct tm *tmtime;
      time_t lntime;
      char szTime[35];
   	FILE *fp;

      fp = fopen ("hgp_btr.txt","a");
      if (fp)
      {
     		lntime = time(NULL);
         tmtime=localtime(&lntime);
   	  	wsprintf((LPSTR)szTime,"%2d.%2d.%2d %2d:%2d:%2d",
   	      tmtime->tm_mon + 1,
   	      tmtime->tm_mday,
   	      tmtime->tm_year,
   	      tmtime->tm_hour,
   	      tmtime->tm_min,
            tmtime->tm_sec);
      	fprintf(fp, "\n%s %s lock_index_cnt %d",
         		szTime, Errorbuf, lock_index_cnt);
      	fclose(fp);
      }

   #endif

	Return 0 ;

End

#ifndef TraceOn

//**************************************************************************

int b_error(int b_err) // TraceOff
Begin ("b_error")
	char errm[150];

   wsprintf(errm,"error %d btrievew (%ld,%ld)",
   		b_err, error2_da, error_da);
	switch (b_err) {
	case -2:
		error2_da++;
	default:
		error_da++;
	}
#if defined(APPL_HGP)
	// keine MessageBox beim HGP
   // siehe Menu: Optionen-Projekt-Compiler-Definitionen
	DebugAusgabe(errm);
   b_err_proto(errm);
#elif !defined(APPL_ETCL)
	// MessageBox
	b_err_mess(errm,"b_error");
#endif
   Return b_err;
End // b_error() TraceOff

#else // b_error() TraceOn

//**************************************************************************

int b_error(int b_err) // TraceOn
Begin ("b_error")
	char errm[100];
	switch (b_err) {
	case -2:
		error2_da++;
/*
	{
 Obwohl der folgende Code im Debugger die Datei nachprüfbar
beschreibt, landet die Ausgabe nicht in der Datei. Auch nicht wenn mann die Ausgabe
 über raise auf 'Catcher' umleitet. Sehrwohl funktioniert der gleiche Mechanismus
 dort richtig. -BH-22.10.95, Ausgabe blockiert da beim Kunden störend.
	FILE * Error;
	char * Ptr;
	int I;
	int ret;
	   Ptr = TraceStack.BasePtr;
	   Error = fopen ("Error","a");
	   fprintf(Error,"\n");
	   for (I=0;I<TraceStack.Count;I++)
		{
			ret = fprintf(Error,"error %d btrievew (%ld,%ld) Trace: %s\n",b_err,error2_da,error_da,Ptr);
			Ptr += TraceStack.ElementSize;
		}
		fclose(Error);
	}
*/
		Return b_err;
	default:
		error_da++;
/*
	{
	FILE * Error;
	char * Ptr;
	int ret;
	int I;
	   Ptr = TraceStack.BasePtr;
	   Error = fopen ("Error","a");
	   fprintf(Error,"\n");
	   for (I=0;I<TraceStack.Count;I++)
		{
			ret = fprintf(Error,"error %d btrievew (%ld,%ld) Trace: %s\n",b_err,error2_da,error_da,Ptr);
			Ptr += TraceStack.ElementSize;
		}
		fclose(Error);
	}
*/
		Return b_err;
	}
End // b_error() TraceOn

#endif // b_error() TraceOn

//*********************************************************************************

HBTR checkDatabase(int nFileLenght)
Begin ("checkDatabase")

  HANDLE      hFileList;

  nStatus=-2;

  hFileList = GlobalAlloc(GMEM_MOVEABLE|GMEM_DISCARDABLE|GMEM_ZEROINIT, 130);
  pFileList = (FILELISTTYP FAR *)myGlobalLock(hFileList);


  if ((!hFileList) || (!pFileList))
  {
	 myGlobalUnlock(hFileList);
	 GlobalFree(hFileList);
     Return (NULL);
  }
  pFileList->nSize = nFileLenght;
  nStatus = 0;
  if (hFileList)
  {
     myGlobalUnlock(hFileList);
  }
  Return(hFileList);
End

//**************************************************************************

int b_begin (LPSTR opStr)
Begin ("b_begin")
  nStatus = WBRQSHELLINIT(opStr);
  if (nStatus != 0)  /* 25.01.95 -TE- Abfrage auf != -1 geaendert in != 0 */
     nStatus = WBTRVINIT(opStr);
  Return(nStatus);
End

//**************************************************************************

int b_end (void)
Begin ("b_end")
  Return(WBTRVSTOP());
End
//**************************************************************************


HBTR b_open (LPSTR lpPath, LPSTR lpName, int FAR *nResult,int nLenght)
/* Returns a handle for a database and opens it */
Begin ("b_open")
  HBTR     hbtr = 0;
  LPSTR    lpPathName, lpDatBuf;
  unsigned nDatLen = 0;
  HANDLE   hmem[2];
  int      nRecordLenght;

  nRecordLenght = nLenght;

  *nResult = -2;
  hmem[0] = GlobalAlloc(GMEM_MOVEABLE|GMEM_DISCARDABLE|GMEM_ZEROINIT,lstrlen(lpPath)+lstrlen(lpName)+5);
  if (!hmem[0]) {
		MessageBox(0,"1 b_open: kein Speicherplatz frei","OPENFILE:",
					MB_ICONSTOP|MB_OK);
	  Return(NULL);
  }
  lpPathName = myGlobalLock(hmem[0]);
  if (!lpPathName) {
		MessageBox(0,"2 b_open: kein Speicherplatz frei","OPENFILE:",
					MB_ICONSTOP|MB_OK);
	GlobalFree(hmem[0]);
	Return(NULL);
  }
  lstrcpy(lpPathName, lpPath);
  lstrcat(lpPathName, lpName);
  /* 25.01.95 -TE- Extension nur anhaengen, wenn kein '.' im Dateinamen */
  if ( !strchr(lpName, '.') )
      lstrcat(lpPathName, DBEXTENSION);
  lpDatBuf = "\000";                                   /* clear DataBuffer */
  nStatus  = -2;                                 /* no handle for database */

  nOpenCloseCounter++; // WW:12.12.91

  hbtr = checkDatabase(nRecordLenght);


  if ((hbtr) && (!nStatus))
  {
	  hmem[1] = GlobalAlloc(GMEM_MOVEABLE|GMEM_DISCARDABLE|GMEM_ZEROINIT,nDatLen+1);
	  lpDatBuf = myGlobalLock(hmem[1]);
	  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
	  if ((!lpDatBuf) || (!pFileList))
	  {
		 if (hmem[1]) {
			myGlobalUnlock(hmem[1]);
			GlobalFree(hmem[1]);
		 }
		 if (hmem[0]) {
			myGlobalUnlock(hmem[0]);
			GlobalFree(hmem[0]);
		 }
		 if (hbtr) {
			myGlobalUnlock(hbtr);
			GlobalFree(hbtr);
		 }
		   MessageBox(0,"3 b_open: kein Speicherplatz frei","OPENFILE:",
							MB_ICONSTOP|MB_OK);

		 Return(NULL);
	  }

	  *nResult = BTRV(BOPEN, pFileList->szPosBlock, lpDatBuf, &nDatLen, lpPathName, BOPEN_NORMAL);
	  if (*nResult != 0)
	  {
		char szMessage[50];
		wsprintf(szMessage, "%s %s %d",
			"B_Open-Error : "
			,lpPathName
			,*nResult);
		MessageBox(0,(LPSTR)szMessage,"OPENFILE:",
						MB_ICONSTOP|MB_OK);

	  }
     /* 04.06.96 -TE- BTI-Internes Handle merken */
     pFileList->bti_handle = BTI_HANDLE(pFileList);
  }
  else
  {
	 if (nStatus)
	 {
        char szMessage[50];
		wsprintf(szMessage, "%s %d", "Btrieve-Error : " ,nStatus);
		MessageBox(0,(LPSTR)szMessage,"OPENFILE:",
						MB_ICONSTOP|MB_OK);
	 }
	 else
		MessageBox(0,"4 b_open: kein Speicherplatz frei","OPENFILE:",
						MB_ICONSTOP|MB_OK);

	 if (nStatus) *nResult = nStatus;
	 else *nResult = -2;
  }
  myGlobalUnlock(hmem[0]);
  myGlobalUnlock(hmem[1]);
  GlobalFree(hmem[0]);
  GlobalFree(hmem[1]);
  if (*nResult)
  {
     myGlobalUnlock(hbtr);
    if (hbtr) GlobalFree(hbtr);
    hbtr=NULL;
  }
  else
     if (hbtr)
        myGlobalUnlock(hbtr);


  Return(hbtr);
End    /* b_open */
//**************************************************************************



//**************************************************************************
HBTR b_open_read_only(LPSTR lpPath, LPSTR lpName, int FAR *nResult, int nLenght)
/* Returns a handle for a database and opens it */
Begin ("b_open_read_only")
  HBTR     hbtr = 0;
  LPSTR    lpPathName, lpDatBuf;
  unsigned nDatLen = 0;
  HANDLE   hmem[2];
  int      nRecordLenght;

  nRecordLenght = nLenght;
  *nResult = -2;
  hmem[0] = GlobalAlloc(GMEM_MOVEABLE|GMEM_DISCARDABLE|GMEM_ZEROINIT,lstrlen(lpPath)+lstrlen(lpName)+5);
  if (!hmem[0]) {Return(NULL);}
  lpPathName = myGlobalLock(hmem[0]);
  if (!lpPathName) {
	 GlobalFree(hmem[0]);
	 Return(NULL);
  }
  lstrcpy(lpPathName, lpPath);
  lstrcat(lpPathName, lpName);
  /* 25.01.95 -TE- Extension nur anhaengen, wenn kein '.' im Dateinamen */
  if ( !strchr(lpName, '.') )
      lstrcat(lpPathName, DBEXTENSION);
  lpDatBuf = "\000";                                   /* clear DataBuffer */
  nStatus  = -2;                                 /* no handle for database */

  nOpenCloseCounter++; // WW:12.12.91

  hbtr = checkDatabase(nRecordLenght);
  if ((hbtr) && (!nStatus))
  {
	hmem[1] = GlobalAlloc(GMEM_MOVEABLE|GMEM_DISCARDABLE|GMEM_ZEROINIT,nDatLen+1);
    lpDatBuf = myGlobalLock(hmem[1]);
	pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
    if ((!lpDatBuf) || (!pFileList))
    {
      if (hmem[0]) {
         myGlobalUnlock(hmem[0]);
         GlobalFree(hmem[0]);
      }
      if (hmem[1]) {
         myGlobalUnlock(hmem[1]);
         GlobalFree(hmem[1]);
      }
      if (hbtr) {
         myGlobalUnlock(hbtr);
         GlobalFree(hbtr);
      }
      Return(NULL);
    }
    /* open database for reading only (key-number=-2) */
	 *nResult = BTRV(BOPEN, pFileList->szPosBlock, lpDatBuf, &nDatLen, lpPathName, BOPEN_READ_ONLY);
    /* 04.06.96 -TE- BTI-Internes Handle merken */
    pFileList->bti_handle = BTI_HANDLE(pFileList);
  } else
  {
	if (nStatus) *nResult = nStatus;
    else *nResult = -2;
  }
  myGlobalUnlock(hmem[0]);
  myGlobalUnlock(hmem[1]);
  GlobalFree(hmem[0]);
  GlobalFree(hmem[1]);
  if (*nResult)
  {
    if (hbtr) {
       myGlobalUnlock(hbtr);
       GlobalFree(hbtr);
    }
    hbtr=NULL;
  }
  else if (hbtr) myGlobalUnlock(hbtr);


  Return(hbtr);
End    /* b_open_read_only */
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int  b_close (HBTR hbtr)
Begin ("b_close")
  if (!hbtr) {
	Return(-2); //-TS-
  }

  nOpenCloseCounter--; // WW:12.12.91
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
	nStatus=BTRV(BCLOSE, pFileList->szPosBlock, NULL, &pFileList->nSize, NULL, 0);
	myGlobalUnlock(hbtr);
	GlobalFree(hbtr);
  }
  else {
	myGlobalUnlock(hbtr);
	GlobalFree(hbtr);
	Return(-2);
  }
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_insert (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_insert")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    bLock=bLock;
    nStatus=BTRVc(pFileList, BINSERT, pFileList->szPosBlock,
		 data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_update (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_update")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    bLock=bLock;
    nStatus=BTRVc(pFileList, BUPDATE, pFileList->szPosBlock,
		 data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
    if (nStatus == 5) // duplicate key value
    { // loeschen TEST 11.01.96 TS
    	// b_delete( hbtr, nIndex, lpKey, data, bLock);
    }
  } else {
  	Return b_error(-2);
  }
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_delete (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_delete")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    bLock=bLock;

    if (!(lpKey[8] == '_' && lpKey[10] == '_')) {
    	// <==> (Key4[0] == '_' && Key4[2] == '_')
      // wegen MPP eingefuehrt
		nStatus=BTRVc(pFileList, BDELETE, pFileList->szPosBlock, data, &pFileList->nSize, lpKey, nIndex);
    }

    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_delete_notest (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_delete_notest")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    bLock=bLock;
    // bedingungsloses Loeschen
    nStatus=BTRVc(pFileList, BDELETE, pFileList->szPosBlock, data, &pFileList->nSize, lpKey, nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_create (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_create")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    bLock=bLock;
    nStatus=BTRVc(pFileList, BCREATE, pFileList->szPosBlock,
		 data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_stat (HBTR hbtr, int nSize, LPSTR szName, void FAR *sStat)
Begin ("b_stat")

  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus = BTRVc(pFileList, BSTAT, pFileList->szPosBlock,
	      sStat, (unsigned FAR *)&nSize, szName, 0);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);

End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_extend (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_extend")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    bLock=bLock;
    nStatus=BTRVc(pFileList, BEXTEND, pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);

End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_stop (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_stop")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    bLock=bLock;
    nStatus=BTRVc(pFileList, BSTOP, pFileList->szPosBlock, data, &pFileList->nSize, lpKey, nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_version (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_version")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    bLock=bLock;
    nStatus=BTRVc(pFileList, BVERSION, pFileList->szPosBlock, data, &pFileList->nSize, lpKey, nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_unlock (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_unlock") char szData[5];
  unsigned int nSize;

  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nSize = 5;
    bLock=bLock;
    nStatus = BTRVc(pFileList, BUNLOCK, pFileList->szPosBlock, (LPSTR)&szData, &nSize, lpKey, --nIndex);
    lstrcpy(data, (LPSTR)szData);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_reset (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_reset")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    bLock=bLock;
    nStatus=BTRVc(pFileList, BRESET, pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_setOwner (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_setOwner")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    bLock=bLock;
    nStatus=BTRVc(pFileList, BSETOWNER, pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_clearOwner (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_clearOwner")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    bLock=bLock;
    nStatus=BTRVc(pFileList, BCLEAROWNER, pFileList->szPosBlock, data, &pFileList->nSize, lpKey, nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_createSuppIndex (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_createSuppIndex")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    bLock=bLock;
    nStatus=BTRVc(pFileList, BCREATESUPPINDEX, pFileList->szPosBlock, data, &pFileList->nSize, lpKey, nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_dropSuppIndex (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_dropSuppIndex")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    bLock=bLock;
    nStatus=BTRVc(pFileList, BDROPSUPPINDEX, pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_stepFirst (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_stepFirst")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BSTEPFIRST+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_stepLast (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_stepLast")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BSTEPLAST+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_stepNext (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_stepNext")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
	nStatus=BTRVc(pFileList, BSTEPNEXT+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, nIndex);
	myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_stepPrev (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_stepPrev")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
	nStatus=BTRVc(pFileList, BSTEPPREV+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, nIndex);
	myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_setDirectory (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_setDirectory")
  if (!lstrcmp(lpKey, "")) Return(35);
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
	bLock=bLock;
	nStatus=BTRVc(pFileList, BSETDIRECTORY, pFileList->szPosBlock, data, &pFileList->nSize, lpKey, nIndex);
	myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  {Return(nStatus);}
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_getDirectory (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_getDirectory")
  if (lstrlen(lpKey) >= 66) Return(35);
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
	bLock=bLock;
	nStatus=BTRVc(pFileList, BGETDIRECTORY, pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
	myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2); }
  {Return(nStatus);}
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_abortTransaction (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_abortTransaction")
  bLock=bLock;
  hbtr=hbtr;
  Return(BTRVc(pFileList, BABORTTRANSACTION, NULL, data, NULL, lpKey, nIndex));
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_beginTransaction (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_beginTransaction")
  bLock=bLock;
  hbtr=hbtr;
  Return(BTRVc(pFileList, BBEGINTRANSACTION, NULL, data, NULL, lpKey, nIndex));
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_endTransaction (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_endTransaction")
  bLock=bLock;
  hbtr=hbtr;
  Return(BTRVc(pFileList, BENDTRANSACTION, NULL, data, NULL, lpKey, nIndex));
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_getDirect (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_getDirect")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BGETDIRECT+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_getEqual (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_getEqual")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BGETEQUAL+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_getFirst (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_getFirst")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BGETFIRST+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_getGreater (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_getGreater")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BGETGREATER+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_getGreaterEqual (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_getGreaterEqual")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BGETGREATEREQUAL+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_getLast (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_getLast")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BGETLAST+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_getLess (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_getLess")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BGETLESS+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_getLessEqual (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_getLessEqual")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BGETLESSEQUAL+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_getNext (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_getNext")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BGETNEXT+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_getPosition (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_getPosition") char szData[4];
  unsigned nLength=4;

  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus = BTRVc(pFileList, BGETPOSITION+AskLock(bLock), pFileList->szPosBlock, (LPSTR)szData, &nLength, lpKey, --nIndex);
    lstrcpy(data, szData);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_getPrev (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_getPrev")
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BGETPREV+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
#ifdef BTRIEVE5_1
int b_getNextExtend (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_getNextExtend")
  Return(60);
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BGETNEXTEX+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_getPrevExtend (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_getPrevExtend")
  Return(60);
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BGETPREVEX+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_StepNextExtend (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_StepNextExtend")
  Return(60);
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BSTEPNEXTEX+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_StepPrevExtend (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_StepPrevExtend")
  Return(60);
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BSTEPPREVEX+AskLock(bLock), pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
int b_InsertExtend (HBTR hbtr, int nIndex, LPSTR lpKey, void FAR *data, BOOL bLock)
Begin ("b_insertExtend")
  Return(60);
  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
  if (pFileList)
  {
    nStatus=BTRVc(pFileList, BINSERTEX, pFileList->szPosBlock, data, &pFileList->nSize, lpKey, --nIndex);
    myGlobalUnlock(hbtr);
  }
  else {Return b_error(-2);}
  Return(nStatus);
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
#endif
int b_getKey (int nOperation, HBTR hbtr, int nIndex, LPSTR lpKey)
Begin ("b_getKey") char szData[4];
  int  nStatus;

  switch (nOperation)
  {
	case BGETEQUAL:
	case BGETNEXT:
	case BGETPREV:
	case BGETGREATER:
	case BGETGREATEREQUAL:
	case BGETLESS:
	case BGETLESSEQUAL:
	case BGETFIRST:
	case BGETLAST:
	case BGETPOSITION:
	case BGETDIRECT:
	  pFileList=(FILELISTTYP FAR *)myGlobalLock(hbtr);
	  if (pFileList)
	  {
	nOperation += BGETKEY;
	nStatus = BTRVc(pFileList, nOperation, pFileList->szPosBlock, szData, &pFileList->nSize, lpKey, --nIndex);
		myGlobalUnlock(hbtr);
	  }
	  else {Return b_error(-2);}
	break;
	default:
	  nStatus = 41;
	break;
  }
  Return(nStatus);
End
/***************************************************************************/
/*                                                                         */
/*  WBTRINTF.C                                                             */
/*                                                                         */
/*     Interface module for Microsoft Windows applications to the Btrieve  */
/*     Dynamic Link Module WBTRCALL.                                       */
/*                                                                         */
/*     There are five entry points called by the user application.         */
/*                                                                         */
/*     The Btrieve DLL "WBTRCALL" can be either the local Btrieve  DLL     */
/*     or the Btrieve requester.  By having this interchangability,        */
/*     an application can be written so that it can initialize, and use    */
/*     which ever happens to be present.  An application will simply go    */
/*     through which ever of the DLL's  happens to be named "WBTRCALL".    */
/*                                                                         */
/*     Initialization is done through several different functions.         */
/*                                                                         */
/*        Requester     - WBRQSHELLINIT ()                                 */
/*        Local DLL     - WBTRVINIT ()                                     */
/*                                                                         */
/*     If access to local files when using the requester is desired, the   */
/*     local Btrieve DLL must be present and named "WBTRLOCL", and a "l:"  */
/*     option is given in the requester initialization.                    */
/*                                                                         */
/*     Any call to an initialization function must be made prior to any    */
/*     other functional call as the DLL will initialize by default on      */
/*     the first call.                                                     */
/*                                                                         */
/*                                                                         */
/*     RQSHELLINIT (char FAR *) - called with FAR pointer to char string   */
/*             with desired options to initialize the requester.           */
/*                                                                         */
/*     BTRVINIT(char FAR *) - Called with FAR pointer to char string with  */
/*             desired Btrieve option parameters in the form:              */
/*                                                                         */
/*     BTRV (normal Btrieve parameters) - Btrieve function calls.          */
/*                                                                         */
/*     BTRVSTOP (void) - Called with no parameters.  Used by an application*/
/*             prior to termination.  This clears the application's entry  */
/*             in the DLL's internal table of active tasks.  If using the  */
/*             requester, this function MUST be called.                    */
/*                                                                         */
/*                                                                         */
/*     Link application with WBTRCALL.LIB                                  */
/*                                                                         */
/*     Date - 5/14/90                                                      */
/*                                                                         */
/***************************************************************************/

extern int BCALL BTRCALL (int , char FAR *, char FAR *, unsigned FAR *, char FAR *, unsigned char, char);
extern int BCALL WBTRVINIT (char FAR *);
extern int BCALL WBRQSHELLINIT (char FAR *);
extern int BCALL WBTRVSTOP (void);

/*********************  Requester Btrieve Only   **************************/
/********  If using local Btrieve this function Returns a -1    ***********/
/**************************************************************************/
int RQSHELLINIT (char FAR *opStr)
Begin ("RQSHELLINIT")
  Return (WBRQSHELLINIT (opStr));
End


/**************************  Local Btrieve Only  **************************/
/********  If using Btrieve Requester this function passes the  ***********/
/********  options string to the local Btrieve DLL if local     ***********/
/********  access is possible  - specify /l: option in the      ***********/
/********  WBRQSHELLINIT () or [brequest] options.              ***********/
/**************************************************************************/
int BTRVINIT (char FAR *opStr)
Begin ("BTRVINIT")
  Return (WBTRVINIT (opStr));
End


int BTRVSTOP ()
Begin ("BTRVSTOP")
  Return (WBTRVSTOP ());
End


int BTRV (int          operation,
	  char FAR     *posblk,
	  char FAR     *databuf,
	  unsigned FAR *datalen,
		  char FAR     *keyP,
		  int          keyNumber)
Begin ("BTRV")
  unsigned char keylen = 255;
  char ckeynum = (char) keyNumber;
  int ret;
  char preinfo1[200];
#ifdef OHNE_INFO_PRE_POST
  char preinfo2[1000];
  char preinfo3[1000];
  char postinfo1[200];
  char postinfo2[1000];
  char postinfo3[1000];
#endif


	preinfo1[0] = '\0';
#ifdef OHNE_INFO_PRE_POST
	preinfo2[0] = '\0';
	preinfo3[0] = '\0';
	postinfo1[0] = '\0';
	postinfo2[0] = '\0';
	postinfo3[0] = '\0';
#endif

#ifdef MIT_ERR_AUS
{ // Daten retten fuer Error Ausgabe
	int length;

	sprintf(preinfo1,
	"op %d posblk %p databuf %p p_datalen %p keyP %p keylen %d ckeynum %c",
				  (int)  operation,
				  (char FAR *) posblk,
				  (char FAR *) databuf,
				  (unsigned FAR *) datalen,
				  (char FAR *) keyP,
				  (unsigned char) keylen,
				  (char) ckeynum);
#ifdef MIT_DATEN
	sprintf(preinfo2,"data :");
	length = strlen(preinfo2);
	if (databuf) {
		for (i=length;
			(i < (*((unsigned FAR *)datalen)) + length)
					&& (i < 1000-10) ;i++) {
			preinfo2[i] = *(((char FAR *)databuf)+i);
			if (preinfo2[i] < 32)
				preinfo2[i] = '?';
		}
	}else{
		if (*((unsigned FAR *)datalen)) {
			strcat(preinfo2,"keine Daten aber Laengenangabe");
		} else {
			strcat(preinfo2,"keine Daten");
		}
	}
	preinfo2[i+1] = ':'; preinfo2[i+2] = '\0';
#endif
#ifdef MIT_KEY
	sprintf(preinfo3,"key :");
	if (keyP)
		strcat(preinfo3,keyP);
	strcat(preinfo3,":");
#endif
}
#endif
//******************************************
  ret = BTRCALL (
				  (int)  operation,
				  (char FAR *) posblk,
				  (char FAR *) databuf,
				  (unsigned FAR *) datalen,
				  (char FAR *) keyP,
				  (unsigned char) keylen,
				  (char) ckeynum);
//******************************************
#ifdef MIT_ERR_AUS
	{
	int length;
	sprintf(postinfo1,
	"op %d posblk %p databuf %p p_datalen %p keyP %p keylen %d ckeynum %c",
				  (int)  operation,
				  (char FAR *) posblk,
				  (char FAR *) databuf,
				  (unsigned FAR *) datalen,
				  (char FAR *) keyP,
				  (unsigned char) keylen,
				  (char) ckeynum);

#ifdef MIT_DATEN
	sprintf(postinfo2,"data :");
	length = strlen(postinfo2);
	if (databuf) {
		for (i=length;
			(i < (*((unsigned FAR *)datalen)) + length)
					&& (i < 1000-10) ;i++) {
			postinfo2[i] = *(((char FAR *)databuf)+i);
			if (postinfo2[i] < 32)
				postinfo2[i] = '?';
		}
	}else{
		if (*((unsigned FAR *)datalen)) {
			strcat(postinfo2,"keine Daten aber Laengenangabe");
		} else {
			strcat(postinfo2,"keine Daten");
		}
	}
	postinfo2[i+1] = ':'; postinfo2[i+2] = '\0';
#endif

#ifdef MIT_KEY
	sprintf(postinfo3,"key :");
	if (keyP)
		strcat(postinfo3,keyP);
	strcat(postinfo3,":");
#endif
  }

  if ((ret != 0) && (ret != 4) && (ret != 9))
  {
	// Message BOX und LOGFILE
	FILE *fp;

	b_err_mess(preinfo1,"Vorher Befehl");
#ifdef MIT_DATEN
	b_err_mess(preinfo2,"Vorher Daten");
#endif
	b_err_mess(preinfo3,"Vorher Key");
	b_err_mess(postinfo1,"Nachher Befehl");
#ifdef MIT_DATEN
	b_err_mess(postinfo2,"Nachher Daten");
#endif
	b_err_mess(postinfo3,"Nachher Key");

	fp = fopen("btr.log","w");
	if (fp) {
		int i;
		fprintf(fp,"Vorher Befehl\n");
		fprintf(fp,"\n%s\n",preinfo1);
#ifdef MIT_DATEN
		fprintf(fp,"Vorher Daten\n");
#endif
		fprintf(fp,"\n%s\n",preinfo2);
		fprintf(fp,"Vorher Key\n");
		fprintf(fp,"\n%s\n",preinfo3);
		fprintf(fp,"Nacher Befehl\n");
		fprintf(fp,"\n%s\n",postinfo1);
#ifdef MIT_DATEN
		fprintf(fp,"Nachher Daten\n");
		fprintf(fp,"\n%s\n",postinfo2);
#endif
		fprintf(fp,"Nachher Key\n");
		fprintf(fp,"\n%s\n",postinfo3);
		fclose(fp);
	}
  }
#endif

  if ((ret != 0) && (ret != 4) && (ret != 9))
  {
  	  b_error(ret);
  }

  Return ret;
End     /* end of WBTRINTF.C */
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/

/*************************************************************************
#ifdef BTRVDEBUG
int OpenInfo(LPSTR lpName)
{ int   hfile;
  LPSTR lpText;

  hfile = _lopen(lpName, OF_READWRITE);
  if (hfile != -1)
  {
	_llseek(hfile, 0, 2);
	lpText = "\n********************************************************\n";
	_lwrite(hfile, lpText, lstrlen(lpText));
  }
  else hfile = _lcreat(lpName, 0);
  Return(hfile);
}
ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
void Info(int hfile, LPSTR lpStr1, LPSTR lpStr2, int nValue, int nStr2Len)
{ LPSTR  lpInt, lpPoint, lpEnd;
  char   szInt[10];

  lpPoint = " ,";
  lpEnd = "\n";
  lpInt = (LPSTR)szInt;
  itoa(nValue, szInt, 10);
  _lwrite(hfile, lpStr1, lstrlen(lpStr1));
  if (nStr2Len == 0) nStr2Len = lstrlen(lpStr2);
  _lwrite(hfile, lpStr2, nStr2Len);
  _lwrite(hfile, lpPoint, 2);
  _lwrite(hfile, lpInt, lstrlen(lpInt));
  _lwrite(hfile, lpEnd, lstrlen(lpEnd));
}
#endif

************************************************************************/

/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
#include <STDIO.H>           // WW:12.12.91
VOID DBCounter
(
  HANDLE hDlg,               // parent-window-handle
  LPSTR  lpszCaption         // Caption-Text
)  // WW:12.12.91
/*
  Diese Routine zeigt die Variable "nOpenCloseCounter" an. Diese wird bei
  jedem b_open-Aufruf inkrementiert und bei jedem b_close-Aufruf de-
  krementiert.
*/
Begin ("DBCounter")
  char szCounter[81];

  wsprintf(szCounter, "%d", nOpenCloseCounter );
  MessageBox( hDlg, szCounter, lpszCaption, MB_OK );
End
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/

int set_lock_hndl_cnt(HGLOBAL hglb,int val)
Begin ("set_lock_hndl_cnt")
	int i;
	lock_index_cnt += val;
	if (val == 1) {
		;
	} else {
		if (lock_index_cnt >= 5) {
			i=0;
		}
	}
#ifdef spaeter
	if (++loop_cnt == 5000) {
		char xerrbuf[100];
		loop_cnt = 0;
		wsprintf(xerrbuf,"lock_index_cnt = %d", lock_index_cnt);
		DebugAusgabe(xerrbuf);
		wsprintf(xerrbuf,"btrieve error = %ld error2 = %ld",error_da,error2_da);
		DebugAusgabe(xerrbuf);
	}
#endif

	Return 0;

#ifdef WG_OBIGEM_Return_SOWIESO_NICHT_GEBRAUCHT /* 27.07.95 -TE- */
	for (i=0;i<lock_index_cnt;i++) {
		if (hglb == lock_hndl[i]) {
			lock_hndl_cnt[i] += val;
			Return 0;
		}
	}
	if (i < MAX_HNDL-2) {
		i = ++lock_index_cnt;
		lock_hndl[i] = hglb;
		lock_hndl_cnt[i] += val;
		Return 0;
	} else {
		i = MAX_HNDL-1;
		lock_hndl[i] = -99;
		lock_hndl_cnt[i] += val;
		Return 0;
	}
#endif
End

BOOL myGlobalUnlock(HGLOBAL hglb)
Begin ("myGlobalUnlock")
	BOOL ret;
	ret = GlobalUnlock(hglb);
	if (ret != 0) {
		Return ret;
	} else {
		set_lock_hndl_cnt(hglb, -1);
		Return ret;
	}
End

void FAR * myGlobalLock(HGLOBAL hglb)
Begin ("myGlobalLock")
	void FAR * ret;
	ret = GlobalLock(hglb);
	if (ret == NULL) {
		Return ret;
	} else {
		set_lock_hndl_cnt(hglb, 1);
		Return ret;
	}
End


