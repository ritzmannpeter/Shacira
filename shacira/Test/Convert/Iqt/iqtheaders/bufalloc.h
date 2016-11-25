/*********************************************************************
*
*  BUFALLOC.H
*
*  *** HISTORY ***
*  07.01.92 -TSchw-  Implementierung
*  09.01.92 -TSchw-  Um BufUsed und BUF_BLOCK erweitert
*  14.01.92 -TSchw-  OvErrLastTask, OvErrLastLen eingefuegt
*  27.07.98 -PR-     In nicht segmentierte Umgebung uebernommen,
*                    hardwarespezifische Teile entfernt und zu
*                    system-unabhaengigem ADT umfunktioniert.
*
*********************************************************************/

#ifndef _bufalloc
#define _bufalloc

/*********************************************************************
X  Konstanten
*********************************************************************/

#define MAXTASK   28       /* Anzahl Eintraege in der Tabelle TaskCount      */
#define FIRSTTASK  9       /* Offset in der Tabelle TaskCount                */
#define MAX_MEMERR 5       /* Anzahl Eintraege in MemErrorBuf                */

/*********************************************************************
X  Typen
*********************************************************************/

typedef struct bufblock {
   void *base;       /* Basisadresse des Freispeicherplatzes                 */
   long len;         /* Gesamte Laenge des Freispeicherplatzes in Byte       */
   int  chunklen;    /* Laenge eines Frei-Blockes in Byte                    */
   long maxfree;     /* Laenge des groessten freien Speicherblocks in Byte   */
   long totalfree;   /* Groesse aller freien Speicherbloecke in Byte         */
   int  nr;          /* Anzahl der Freispeicherbloecke                       */
} BUF_BLOCK;

/*********************************************************************
X  Variablen
*********************************************************************/

/* Die folgenden beiden Tabellen sind im BBRAM definiert:                    */
extern long TaskCount [MAXTASK]; /* Zaehler allocierte Byte/Task, Zaehlung   */
                          /* beginnt bei Task 9: Index 0 = Task FIRSTTASK.   */
                          /* Nr der Task, die Fehler im BufFree produzieren: */
extern WORD OvErrLastTask;    /* Tasknummer des vorhergehenden Blocks */
extern WORD OvErrLastLen;     /* L„nge des vorhergehenden Blocks      */
extern BYTE MemErrorBuf[MAX_MEMERR]; /* Free Error 0: Buffer already free    */
                                     /* Free Error 1: Buffer not found       */
                                     /* Free Error 2: Overwrite Error,Task>37*/
                                     /* AllocError 3: No Buffer found        */
                                     /* AllocError 4: Loop in Free List      */

/*********************************************************************
X  Funktionsprototypen
*********************************************************************/

int  MyBufCheck ();
void BufUsed( BUF_BLOCK * p );

#endif
