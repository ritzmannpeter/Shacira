// ErrBuf.h

#ifndef _errbuf_
#define _errbuf_

#define ERRBUF_TYPE_STARTBIT     1  /* Bitfehler tritt auf                 */
#define ERRBUF_TYPE_STOPBIT      2  /* Bitfehler verschwindet              */
#define ERRBUF_TYPE_STARTHEAT    3  /* Heizungsfehler tritt auf            */
#define ERRBUF_TYPE_STOPHEAT     4  /* Heizungsfehler verschwindet         */

#define ERRBUF_USER1             0x01
#define ERRBUF_USER2             0x02
#define ERRBUF_USER3             0x03
#define ERRBUF_USER4             0x08
#define ERRBUF_USER_NONE         0x00

typedef struct  {
   BYTE        Flag;                /* Gelesen-Markierung je User          */
   BYTE        Id;                  /* Identifikation des Typs             */
   PARAMETER   Date;                /* Datum                               */
   PARAMETER   Time;                /* Uhrzeit                             */
   long        AddCount;            /* Addierender Schusszaehler           */
   UWORD       ErrInd;              /* Index in Fehlermeldungstabelle      */
   int         HeatGroup;           /* Heizungsgruppe (Zylinder, Wkz, ...) */
   int         HeatZone;            /* Zone innerhalb der Gruppe           */
   int         HeatFunc;            /* Funktionseinheit (Spritzeinheit)    */
} ERRBUF_ENTRY;


GLOBAL int  ErrBuf_Init( BOOL init_bbram );
GLOBAL void ErrBuf_StartBitError( UWORD Index );
GLOBAL void ErrBuf_StopBitError( UWORD Index );
GLOBAL void ErrBuf_HeatError( BOOL StartFlag, UWORD ErrIndex,
                              int Group, int Zone, int Func );
GLOBAL int ErrBuf_GetEntry (ERRBUF_ENTRY *Param , int Nr, 
                            UWORD user, UWORD mark);
GLOBAL int ErrBuf_GetLastEntry (ERRBUF_ENTRY *Param , UWORD user, UWORD mark);
GLOBAL int ErrBuf_Count (UWORD user);
                            

#endif // _errbuf_

