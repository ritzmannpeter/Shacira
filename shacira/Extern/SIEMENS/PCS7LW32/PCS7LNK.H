/* Modul       : PCS7LNK.H
  Projekt     : Datenkopplung SIMATIC-S7 300/400 <----> IBM-PC
                mit PC/MPI-Adapter
  for changes and version notes see "changes.txt"
*/  

#ifndef __PCS7LNK_H__

#define __PCS7LNK_H__  

#ifdef __cplusplus
extern "C" {
#endif 
#ifndef __linux__
#pragma pack(1)
#endif

/*------------------------------------------------------------*/
/*---------------------Konstantendefinitionen-----------------*/
/*------------------------------------------------------------*/

#define BST_ART_ANZ     7
#define MAX_MPIADR     126  /* Master + MPI-Adressen 1-126 */

/*--------------------- Bausteinarten ------------------------*/

/* Es gibt unter S7 folgende Bausteinarten */
#define _DB                     0
#define _SDB                    1
#define _SFC                    2
#define _FB                     3
#define _OB                     4
#define _FC                     5
#define _SFB                    6

/*--------------------- Fehlerarten --------------------------*/

#define S7_E_NOERR              0   /* alles OK */
#define S7_E_TIMEOUT            -1  /* ZeitÅberlauf */
#define S7_E_BADBAUD            -2  /* Baudrate ungÅltig */
#define S7_E_BADMPIADR          -3  /* MPI-Adresse ungÅltig */
#define S7_E_NOCOM              -4  /* COM nicht vorhanden  */

#define S7_E_NOBST              2
#define S7_E_BSTLEN             2
#define S7_E_NODATA             2   /* Datenbereich existiert nicht */
                                    
#define S7_E_DEMOEND            0x1234



#define COM1                    0
#define COM2                    1
#define COM3                    2
#define COM4                    3
#define COM5                    4
#define COM6                    5
#define COM7                    6
#define COM8                    7
#define COM9                    8 
#define COM10                   9
#define COM11                   10
#define COM12                   11
#define COM13                   12
#define COM14                   13
#define COM15                   14
#define COM16                   15
/*------------------------------------------------------------*/
/*--------------------- Datentypendefinitionen ---------------*/
/*------------------------------------------------------------*/

#ifdef __linux__
   #define TRUE                1
   #define FALSE               0
   #define far
#endif

#ifndef WINVER
 #define WINFAR  
 #define WINAPI  
#else
 #define WINFAR FAR 
 #ifndef WINAPI
   #define WINAPI FAR PASCAL
 #endif
#endif
 
#ifndef DEFINED_TYPES
  #ifndef WINVER     
    #define TRUE                1
    #define FALSE               0

    typedef unsigned char       BYTE;
    typedef unsigned short int  WORD;
    typedef unsigned long       DWORD;
    typedef long                LONG;
    typedef char                far *_PSTR;
    typedef BYTE                far *_PBYTE;

    typedef void                far *_PVOID;  
    typedef int                 far *_PINT;
    typedef WORD                far *_PWORD;
    typedef long                far *_PLONG;
    typedef DWORD               far *_PDWORD;
    
    typedef BYTE                    *PBYTE;
    typedef BYTE                far *LPBYTE;
    typedef int                 far *LPINT;
    typedef WORD                far *LPWORD;
    typedef long                far *LPLONG;
    typedef DWORD               far *LPDWORD;
    typedef void                far *LPVOID;    

                                           
    #ifndef TPAS
      typedef int                 BOOL;
    #else
      typedef BYTE                BOOL;
    #endif             
    
    #define DEFINED_TYPES
  #else
    typedef LPSTR               _PSTR;
    typedef LPBYTE              _PBYTE;
    typedef LPINT               _PINT;
    typedef LPWORD              _PWORD;
    typedef LPLONG              _PLONG;
    typedef LPDWORD             _PDWORD;
    typedef LPVOID              _PVOID;
  #endif
#endif 
/* ------------------------------------------------------------------ */
        
typedef struct
{
  WORD Com;    
  BOOL bInit;
  int  Err;  
  int  SPSTyp;  /* 0 = S7 400/400 mit MPI-Kabel */
                           /* 1 = S7 200 mit PPI-Kabel */
  BYTE Internal[1536];
} S7, WINFAR *PS7, far *LPS7;

/* ------------------------------------------------------------------ */
/* --------------------- globale Funktionen ------------------------- */
/* ------------------------------------------------------------------ */

extern BOOL WINAPI
S7Init (LPS7 lpS7, WORD Com, WORD SPSMPIAdr, WORD LocalMPIAdr, WORD Baud);
/*
      Zweck:  S7Init initialisiert das in pS7 beschriebene an pS7->Com 
              angeschlossene AG und die dazugehîrige Schnittstelle. 
              pS7->Com mu· COM1, COM2, COM3 ... COM16 sein. 
              pS7->MPINr ist die MPI-Nummer 
  
  Parameter:  Name          Typ      Beschreibung
                            
              pS7           LPS7      Pointer auf den Speicher fÅr das angewÑhlte 
                                     AG 
              SPSMPIAdr     WORD     MPI-Adresse des Partner (SPS)
              LocalMPIAdr   WORD     eigen MPI-Adresse (normal 0)
              Baud          WORD     19200, 38400           
 
     Return:  BOOL          TRUE    wenn erfolgreich, 
                            FALSE   bei Fehler pS7->Err auswerten

*/ 

/* ab V 1.12*/
extern BOOL WINAPI
S7InitFastBaud (LPS7 lpS7, WORD Com, WORD SPSMPIAdr, WORD LocalMPIAdr, DWORD Baud);
/*
      Zweck:  S7InitEx initialisiert das in pS7 beschriebene an pS7->Com 
              angeschlossene AG und die dazugehîrige Schnittstelle. 
              pS7->Com mu· COM1, COM2, COM3 ... COM16 sein. 
              pS7->MPINr ist die MPI-Nummer 
  
  Parameter:  Name          Typ      Beschreibung
                            
              pS7           LPS7      Pointer auf den Speicher fÅr das angewÑhlte 
                                     AG 
              SPSMPIAdr     WORD     MPI-Adresse des Partner (SPS)
              LocalMPIAdr   WORD     eigen MPI-Adresse (normal 0)
              Baud          WORD     19200, 38400, 57600, 115200           
 
     Return:  BOOL          TRUE    wenn erfolgreich, 
                            FALSE   bei Fehler pS7->Err auswerten

*/ 
  
extern BOOL WINAPI
S7InitFastBaudEx (LPS7 lpS7, WORD Com, WORD SPSMPIAdr, WORD LocalMPIAdr, DWORD Baud, DWORD MPIBaud);
/*
  wie S7InitFastBaudEx jedoch mit MPIBaud --> 
  0 = 187,5 kBit/s auf MPI-Bus
  1 = 19,2 kBit/s
  2 = 1,5 MBit/s
           
*/

/*------------------------------------------------------------*/

extern BOOL WINAPI
S7Exit (LPS7 pS7);
/*
      Zweck:  S7xit  mu· fÅr jede mit S7nit mit Return TRUE 
              initialisierte Struktur S7 ausgefÅhrt werden. 
              Die zugehîrigen Schnittstelle wird deaktiviert.
                                                
                        
  Parameter:  Name     Typ      Beschreibung
  
              pS7     LPS7       Pointer auf den Speicher fÅr das angewÑhlte 
                                AG 
 
     Return:  BOOL      TRUE    wenn erfolgreich, 
                        FALSE   bei Fehler 
*/


/* ------------------------------------------------------------------ */
/* ------------------Merker-Operationen------------------------------ */
/* ------------------------------------------------------------------ */


extern BOOL WINAPI 
S7RdMB (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/*
      Zweck:  S7RdMB  liest vom  mit  pS7  initalisierten AG ab dem 
              Merkerbyte <Ab> <Anz> Bytes in den PC-Speicher 
              Buf  ein. Maximale Anzahl = 128 Byte
               
  
  Parameter:  Name     Typ      Beschreibung
              pS7      LPS7      Pointer auf den Speicher fÅr das angewÑhlte 
                                AG
              Ab       WORD     Start-Bytenummer
              Anz      WORD     Anzahl der Worte, die gelesen werden sollen
              Buf      _PVOID   Pointer auf den Zielspeicher im PC
     
     Return:  BOOL     TRUE     wenn erfolgreich 
                       FALSE    bei Fehler pS7->Err auswerten
*/               
/* ------------------------------------------------------------------ */
 
extern BOOL WINAPI 
S7WrMB (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/*
      Zweck:  S7WrMW  schreibt ans das mit  pS7  initalisierte AG ab dem 
              Merkerbyte <Ab> <Anz> Bytes in den Speicher 
              Buf  ein. Maximale Anzahl = 128 Byte
               
  
  Parameter:  Name     Typ      Beschreibung
              pS7      LPS7      Pointer auf den Speicher fÅr das angewÑhlte 
                                AG
              Ab       WORD     Start-Bytenummer
              Anz      WORD     Anzahl der Worte, die gelesen werden sollen
              Buf      _PVOID   Pointer auf den Quellspeicher im PC
     
     Return:  BOOL     TRUE     wenn erfolgreich 
                       FALSE    bei Fehler pS7->Err auswerten
*/               
/* ------------------------------------------------------------------ */

extern BOOL WINAPI
S7RdMW (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/*
      Zweck:  S7RdMW  liest vom  mit  pS7  initalisierten AG ab dem 
              Merkerwort <Ab> <Anz> Bytes in den PC-Speicher 
              Buf ein. Maximale Anzahl = 64 Worte
              !!! Beachte !!!              
              In der SPS gilt fÅr SPS Programmierer
                                         
                   
                   W0 = Byte 0 und Byte 1
                   W2 = Byte 2 und Byte 3 ...
                   
                   W1 = Byte 1 und Byte 2
                   -> bei Verwendung von ungeraden Worten ist eine 
                   Doppelbelegung gegeben. 
                   Der Trebier unterstÅtz deshalb nur gerade Worte->
               d. h. im PC haben sie z.NB:
               WORD Buf[64];                 
               
               nach dem Aufruf S7Rd?W (pS7, 0, 5, Buf) steht
               in Buf[0]  Wort 0 (nach SPS- Adressierung)
                  Buf[1]  Wort 2 (nach SPS- Adressierung)
                  Buf[2]  Wort 4 (nach SPS- Adressierung)
               Sie mÅssen also die StartWortnummer halbieren, um im
               PC richtig zugreifen zu kînnen. Dies gilt auch fÅr 
               Datenbausteine !!
               

              
              
 
  
  Parameter:  Name     Typ      Beschreibung
              pS7      LPS7      Pointer auf den Speicher fÅr das angewÑhlte 
                                AG
              Ab       WORD     Start-Bytenummer
              Anz      WORD     Anzahl der Worte, die gelesen werden sollen
              Buf      _PVOID   Pointer auf den Zielspeicher im PC
     
     Return:  BOOL     TRUE     wenn erfolgreich 
                       FALSE    bei Fehler pS7->Err auswerten
*/               
/* ------------------------------------------------------------------ */


extern BOOL WINAPI 
S7WrMW (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/*
      Wie S7RdMW nur eben schreiben 
*/

/* ------------------------------------------------------------------ */
/* -----------------Eingangs-Operationen----------------------------- */
/* ------------------------------------------------------------------ */

extern BOOL WINAPI 
S7RdEB (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/*
      Zweck:  S7RdEB  liest vom  mit  pS7  initalisierten AG ab dem 
              Eingangsbyte <Ab> <Anz> Bytes in den PC-Speicher 
              Buf  ein. Maximale Anzahl = 128 Byte
               
  
  Parameter:  Name     Typ      Beschreibung
              pS7      LPS7      Pointer auf den Speicher fÅr das angewÑhlte 
                                AG
              Ab       WORD     Start-Bytenummer
              Anz      WORD     Anzahl der Worte, die gelesen werden sollen
              Buf      _PVOID   Pointer auf den Zielspeicher im PC
     
     Return:  BOOL     TRUE     wenn erfolgreich 
                       FALSE    bei Fehler pS7->Err auswerten
*/               
/* ------------------------------------------------------------------ */

extern BOOL WINAPI 
S7RdEW (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/*
      Wie S7RdMW 
*/
/* ------------------------------------------------------------------ */
/* ------------------------------------------------------------------ */
/* -----------------Ausgangs-Operationen----------------------------- */
/* ------------------------------------------------------------------ */

extern BOOL WINAPI 
S7RdAB (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/*
      Zweck:  S7RdAB  liest vom  mit  pS7  initalisierten AG ab dem 
              Ausgangsbyte <Ab> <Anz> Bytes in den PC-Speicher 
              Buf  ein. Maximale Anzahl = 128 Byte
               
  
  Parameter:  Name     Typ      Beschreibung
              pS7      LPS7      Pointer auf den Speicher fÅr das angewÑhlte 
                                AG
              Ab       WORD     Start-Bytenummer
              Anz      WORD     Anzahl der Worte, die gelesen werden sollen
              Buf      _PVOID   Pointer auf den Zielspeicher im PC
     
     Return:  BOOL     TRUE     wenn erfolgreich 
                       FALSE    bei Fehler pS7->Err auswerten
*/               
/* ------------------------------------------------------------------ */

extern BOOL WINAPI 
S7WrAB (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/*
      Zweck:  S7WrAB   schreibt an das mit  pS7  initalisierte AG ab dem 
              Ausgangsbyte <Ab> <Anz> Bytes in den Speicher 
              Buf  ein. Maximale Anzahl = 128 Byte
               
  
  Parameter:  Name     Typ      Beschreibung
              pS7      LPS7      Pointer auf den Speicher fÅr das angewÑhlte 
                                AG
              Ab       WORD     Start-Bytenummer
              Anz      WORD     Anzahl der Worte, die gelesen werden sollen
              Buf      _PVOID   Pointer auf den Quellspeicher im PC
     
     Return:  BOOL     TRUE     wenn erfolgreich 
                       FALSE    bei Fehler pS7->Err auswerten
*/               
/* ------------------------------------------------------------------ */

extern BOOL WINAPI 
S7RdAW (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/*
      Wie S7RdMW 
*/
/* ------------------------------------------------------------------ */

extern BOOL WINAPI 
S7WrAW (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/*
      Wie S7RdMW nur eben schreiben 
*/
/* ------------------------------------------------------------------ */
                                               
/* ------------------------------------------------------------------ */
/* -----------------DB      -Operationen----------------------------- */
/* ------------------------------------------------------------------ */

extern BOOL WINAPI
S7RdDB (LPS7 pS7, WORD  DBNr, WORD Ab, WORD Anz, _PVOID Buf);
/*       
      Zweck:  S7RdDB liest vom mit pS7  initalisierten AG den Datenbaustein
              der Nummer Nr ab Datenwort Ab WortAnz Worte in den 
              PC-Speicher DstBuf  ein. Die Daten werden wortweise mit Drehen 
              der Bytes gelesen. max. 64 Wort
              !!! Beachte !!!              
              In der SPS gilt fÅr SPS Programmierer
                                         
                   
                   W0 = Byte 0 und Byte 1
                   W2 = Byte 2 und Byte 3 ...
                   
                   W1 = Byte 1 und Byte 2
                   -> bei Verwendung von ungeraden Worten ist eine 
                   Doppelbelegung gegeben. 
                   Der Trebier unterstÅtz deshalb nur gerade Worte->
               d. h. im PC haben sie z.NB:
               WORD Buf[64];                 
               
               nach dem Aufruf S7Rd?W (pS7, 0, 5, Buf) steht
               in Buf[0]  Wort 0 (nach SPS- Adressierung)
                  Buf[1]  Wort 2 (nach SPS- Adressierung)
                  Buf[2]  Wort 4 (nach SPS- Adressierung)
               Sie mÅssen also die StartWortnummer halbieren, um im
               PC richtig zugreifen zu kînnen. Dies gilt auch fÅr 
               Datenbausteine !!
  
  Parameter:  Name     Typ      Beschreibung
              pS7      LPS7      Pointer auf den Speicher f¸r das angew‰hlte
                                AG
              Nr       BYTE     Nummer des zu lesenden Datenbausteins
              Ab       WORD     Nummer des Datenwortes, ab welchem gelesen 
                                werden soll
              WortAnz  WORD     Anzahl der Worte, die gelesen werden sollen
              Buf      _PVOID   Pointer auf den Zielspeicher im PC 

     Return:  BOOL     TRUE     wenn erfolgreich 
                       FALSE    bei Fehler 
                                lpS7->Err enth‰lt den Fehler (S7_E_XXX)
                                Soll ein Bausteinbereich gelesen werden, der 
                                im AG nicht exisitiert, so liefert die Funktion 
                                auch FALSE zur¸ck. lpS7->Err = S7_E_NOBST
*/
/*------------------------------------------------------------*/

extern BOOL WINAPI 
S7WrDB (LPS7 pS7, WORD  DBNr, WORD Ab, WORD Anz, _PVOID Buf);
/*
      Zweck:  S7WrDB schreibt vom PC-Speicher DstBuf ins mit pS7 initalisierte
              AG den Datenbaustein der Nummer Nr ab Datenwort Ab WortAnz 
              Worte. Die Daten werden wortweise mit Drehen der Bytes 
              geschrieben.  max. 64 Wort
             
              !!! Beachte !!!              
              In der SPS gilt fÅr SPS Programmierer
                                         
                   
                   W0 = Byte 0 und Byte 1
                   W2 = Byte 2 und Byte 3 ...
                   
                   W1 = Byte 1 und Byte 2
                   -> bei Verwendung von ungeraden Worten ist eine 
                   Doppelbelegung gegeben. 
                   Der Trebier unterstÅtz deshalb nur gerade Worte->
               d. h. im PC haben sie z.NB:
               WORD Buf[64];                 
               
               nach dem Aufruf S7Rd?W (pS7, 0, 5, Buf) steht
               in Buf[0]  Wort 0 (nach SPS- Adressierung)
                  Buf[1]  Wort 2 (nach SPS- Adressierung)
                  Buf[2]  Wort 4 (nach SPS- Adressierung)
               Sie mÅssen also die StartWortnummer halbieren, um im
               PC richtig zugreifen zu kînnen. Dies gilt auch fÅr 
               Datenbausteine !!
  
  Parameter:  Name     Typ      Beschreibung
              pS7      LPS7      Pointer auf den Speicher f¸r das angew‰hlte
                                AG
              Nr       WORD     Nummer des zu schreibenden Datenbausteins
              Ab       WORD     Nummer des Datenwortes, ab welchem geschrieben 
                                werden soll
              WortAnz  WORD     Anzahl der Worte, die geschrieben werden sollen
              Buf      _PVOID    Pointer auf den Quellspeicher im PC

     Return:  BOOL     TRUE     wenn erfolgreich 
                       FALSE    bei Fehler 
                                lpS7->Err enth‰lt den Fehler (S7_E_XXX)
                                Soll ein Bausteinbereich geschrieben werden, der 
                                im AG nicht exisitiert, so liefert die Funktion 
                                auch FALSE zur¸ck. lpS7->Err = S7_E_NOBST
*/
/*------------------------------------------------------------*/


BOOL WINAPI
S7RdDBB (LPS7 pS7, WORD BstNr, WORD Ab, WORD Anz, _PVOID Buf);
/* ------------------------------------------------------------------ */
   
BOOL WINAPI 
S7WrDBB (LPS7 pS7, WORD BstNr, WORD Ab, WORD Anz, _PVOID Buf);

/* nicht fÅr WINDOWS */

extern BOOL WINAPI
DefineCom (WORD Com, int BaseReg, int IRQNr, _PVOID Buffer);
/*------------------------------------------------------------*/

extern BOOL WINAPI
UndefineCom (WORD Com);

/* ------------------------------------------------------------------ */

extern void WINAPI
S7ExitAll (void);

extern BOOL WINAPI
S7PPIInit (LPS7 lpS7, WORD Com, WORD SPSMPIAdr, WORD LocalMPIAdr, WORD Baud);

extern int WINAPI
S7GetDBLen (LPS7 lpS7, WORD BstNr);
/*
Gibt die LÑnge eines DB in Bytes zurÅck
*/

extern long WINAPI 
S7SetTimeout (long NewTimeOut);
/* 
    ab V 1.12 25.10.99 
   Setzt eine neuen Timeout f¸r das Empfangen der Sendebest‰tigung
   NewTimeOut ist in TimerTicks, 1 Tick = 55 ms. Der Alte Wert wird zur¸ck-
   geliefert. Ist NewTimeOut == -1, so wird dieser nicht ¸bernommen.
   Daf¸r wird aber der aktuelle Timeoutwert zur¸ckgegeben.
*/ 

extern BOOL WINAPI
S7GetMPIMembers (LPS7 lpS7, LPWORD pTeiln);

extern BOOL WINAPI
S7RdTimer (LPS7 pS7, WORD Ab, WORD Anz, LPDWORD Buf);
/*
  Liest Anz Timer ab Nr <Ab> aus der SPS. Der Treiber rechnet das SPS-Format in
  Millisekunden um, deshalb wird hier als <Buf> auch als Pointer auf Long

*/

extern BOOL WINAPI
S7WrTimer (LPS7 pS7, WORD Ab, WORD Anz, LPDWORD Buf);
/*
  Schreibt  Anz Timer ab Nr <Ab> in die SPS.
  Der Wert der Timer ist in ms anzugeben. Das SPS-Format wird
  automatisch erzeugt. Dazu kann es zwangslÑufig zu Rundungen kommen!
  Nur fÅr Anwender mit SPS-Kenntnissen geeignet !
  kleinste Auflîsung 10 ms Schritte
*/

extern BOOL WINAPI
S7RdCounter (LPS7 pS7, WORD Ab, WORD Anz, LPWORD Buf);
/*
  Liest Anz ZÑhler ab Nr <Ab> aus der SPS 
  maximaler Wert eines ZÑhlers 999
  Der Treiber konvertiert automatisch vom SPS-Format ins PC-Format

*/

extern BOOL WINAPI
S7WrCounter (LPS7 pS7, WORD Ab, WORD Anz, LPWORD Buf);
/*
  Schreibt Anz ZÑhler ab Nr <Ab> in die SPS 
  maximaler Wert eines ZÑhlers 999     
  Der Treiber konvertiert automatisch ins SPS-Format

*/


extern BOOL WINAPI
S7RdDBDW (LPS7 pS7, WORD BstNr, WORD AbWort, WORD Anz, _PVOID pData);
/*------------------------------------------------------------*/

extern BOOL WINAPI /* 1.23 */
S7WrDBDW (LPS7 pS7, WORD BstNr, WORD AbWort, WORD Anz, _PVOID pData);
/*------------------------------------------------------------*/

extern BOOL WINAPI /* 1.23 */
S7RdMDW (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/* ------------------------------------------------------------------ */
   
extern BOOL WINAPI /* 1.23 */
S7WrMDW (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/* ------------------------------------------------------------------ */
  
extern BOOL WINAPI /* 1.23 */
S7WrADW (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/* ------------------------------------------------------------------ */

extern BOOL WINAPI /* 1.23 */
S7RdADW (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/* ------------------------------------------------------------------ */
   

extern BOOL WINAPI /* 1.23 */
S7WrEDW (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/* ------------------------------------------------------------------ */

extern BOOL WINAPI /* 1.23 */
S7RdEDW (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/* ------------------------------------------------------------------ */

extern BOOL WINAPI
S7RdDBReal (LPS7 pS7, WORD BstNr, WORD AbWort, WORD Anz, float *pData);
/*------------------------------------------------------------*/

extern BOOL WINAPI /* 1.23 */
S7WrDBReal (LPS7 pS7, WORD BstNr, WORD AbWort, WORD Anz, float *pData);
/*------------------------------------------------------------*/

extern BOOL WINAPI /* 1.23 */
S7RdMReal (LPS7 pS7, WORD Ab, WORD Anz, float *Buf);
/* ------------------------------------------------------------------ */
   
extern BOOL WINAPI /* 1.23 */
S7WrMReal (LPS7 pS7, WORD Ab, WORD Anz, float *Buf);
/* ------------------------------------------------------------------ */
  
extern BOOL WINAPI /* 1.23 */
S7WrAReal (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/* ------------------------------------------------------------------ */

extern BOOL WINAPI /* 1.23 */
S7RdAReal (LPS7 pS7, WORD Ab, WORD Anz, float *Buf);
/* ------------------------------------------------------------------ */
   
extern BOOL WINAPI /* 1.23 */
S7WrEReal (LPS7 pS7, WORD Ab, WORD Anz, _PVOID Buf);
/* ------------------------------------------------------------------ */

extern BOOL WINAPI /* 1.23 */
S7RdEReal (LPS7 pS7, WORD Ab, WORD Anz, float *Buf);


#ifndef __linux__
#pragma pack()
#endif

#ifdef __cplusplus
}
#endif


#endif  /* __PCS7LNK_H__ */
