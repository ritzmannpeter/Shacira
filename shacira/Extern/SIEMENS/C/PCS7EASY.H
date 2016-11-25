/* 
     Author : 
     Dipl.-Ing. A. Traeger
     Traeger Industy Components
     WWW.TRAEGER.DE
     Am Steigacker 26
     D - 92694 Etzenricht
     Tel 0961/482300
     Fax 0961/48230 20
*/           

/* PCS7-EASY.H
   
*/

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__linux__) || !defined (WINAPI)
#ifndef DEFINED_TYPES
		#define DEFINED_TYPES
    #define WINAPI
    #define far
    #define TRUE                1
    #define FALSE               0

    typedef unsigned char       BYTE;
    typedef unsigned int        WORD;
    typedef unsigned long       DWORD;
    typedef long                LONG;
    typedef BYTE                *_PBYTE;
    typedef void                *_PVOID;
    typedef int                 *_PINT;
    typedef WORD                *_PWORD;
    typedef long                *_PLONG;
    typedef DWORD               *_PDWORD;

    typedef BYTE                *PBYTE;
    typedef BYTE                *LPBYTE;
    typedef int                 *LPINT;
    typedef WORD                *LPWORD;
    typedef long                *LPLONG;
    typedef DWORD               *LPDWORD;
    typedef void                *LPVOID;

    typedef int                 BOOL;
#endif
#endif

#ifdef __linux__
int
ES7SetDevName (DWORD Com, const char *DevName);
#endif

long WINAPI
ES7Open (DWORD Com, DWORD SPSMPIAdr, DWORD LocalMPIAdr, DWORD Baud, DWORD SPSTyp);

/* 
     
Declare Function ES7Open& Lib "PCS7EASY.dll" (DWORD Com, DWORD SPSMPIAdr, DWORD LocalMPIAdr, DWORD Baud, DWORD SPSTyp);
 
      
        
      Zweck:  S7EOpen îffnet Schnittstelle <Com>, prÅft, ob die Parameter,   
              mit einer bereits geîffneten Com Åbereinstimmen. 
              Baudrate, sowie lokale MPI-Adresse mÅssen Åbereinstimmen
  
  Parameter:  Name          Typ           Beschreibung
              Com           DWORD         0 = COM1
                                          1 = COM2
                                          ...
              
              SPSMPIAdr     DWORD         MPI-Adresse des Partner (SPS)
              LocalMPIAdr   DWORD         eigen MPI-Adresse (normal 0)
              Baud          DWORD         19200, 38400        
              SPSTyp        DWORD          200 = S7200,
                                           ungleich 200 = automatisch S7 300/400
    
    return : >= 0 alles OK, dies ist die Referenz fÅr alle folgenden
                  Kommunikationen 
            
            -1  = keine Resourcen frei, die maximale Anzahl der
                  geîffneten KanÑle ist erreicht
            
            -2  = die Schnittstelle ist bereits geîffnet, jedoch wird 
                  eine andere Baudrate gefordert als beim vorigen Open
                   S7_E_BADBAUD           -2  
                  
            -3  = die Schnittstelle ist bereits geîffnet, jedoch wird 
                  eine andere lokale MPI-Adresse gefordert als beim 
                   S7_E_BADMPIADR         -3  

            -4  = die gewÅnschte Com-Schnittstelle ist nicht vorhanden
                  oder bereits belegt
                  S7_E_NOCOM             -4  
            -5  = allgemeiner Fehler      
*/
/* ------------------------------------------------------------------ */
long WINAPI
ES7OpenEx (DWORD Com, DWORD SPSMPIAdr, DWORD LocalMPIAdr, DWORD Baud, DWORD SPSTyp, DWORD MPIBaud);
/*
  wie ES7Open jedoch mit MPIBaud -->
  0 = 187,5 kBit/s auf MPI-Bus
  1 = 19,2 kBit/s
  2 = 1,5 MBit/s

*/

long WINAPI
ES7Close (long Ref);
/*
    Ref  Referenznummer, die man mit E7Open erhÑlt

    return: 
    0   alles OK
    -1  Schnittstelle war gar nicht geîffnet
    
    -99;
    Fehler, die Referenznummer ist ungÅltig, oder nicht mit Open geîffnet
*/

/* ------------------------------------------------------------------ */

long WINAPI
ES7RdW (long Ref, DWORD Typ, DWORD DBNr, DWORD AbWort, DWORD WortAnz, LPWORD Buffer) ;
/*
      Zweck:  Liest <WortAnz> Worte ab Datenwort <AbWort> vom 
              Daten Typ <Typ> der SPS. Die Worte werden mit Drehen
              der Bytes gelesen.
  
  Parameter:  Name    Typ      Beschreibung
              Ref     long     Referenz, die bei ES7Open zurÅckgegeben wird.
              Typ     DWORD    'M', 'm'          = Merker  (DBNr wird ignoriert)
                               
                               'E', 'e','I','i'  = Eingang (DBNr wird ignoriert)
                               'A', 'a', 'O','o' = Ausgang (DBNr wird ignoriert)
                               'D', 'd',         = Datenbaustein, DBNr wird verwendet
              
              DBNr    DWORD     Datenbausteinnummer, die gelesen werden soll
              
              AbWort  DWORD    Startwort, ab dem gelesen werden soll unbedingt
                               folgendes beachten !
              *********************************************
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
               
               nach dem Aufruf ES7RdW (Ref, Typ, DBNr, 0, 5, Buf) steht
               in Buf[0]  Wort 0 (nach SPS- Adressierung)
                  Buf[1]  Wort 2 (nach SPS- Adressierung)
                  Buf[2]  Wort 4 (nach SPS- Adressierung)
               Sie mÅssen also die StartWortnummer halbieren, um im
               PC richtig zugreifen zu kînnen. Dies gilt auch fÅr 
               Datenbausteine !! --> Ungerade Wortadressen der SPS kînnen also
               nicht gelesen werden.
              ********************************************
              WortAnz   DWORD   Anzahl der zulesenden Worte
              Buffer    LPWORD  ist Pointer auf Zieladresse
    
    return: 
              S7_E_NOERR             0   alles OK 
              S7_E_TIMEOUT           -1  ZeitÅberlauf 
                                                                                  
              S7_E_NODATA            2   Baustein oder Datenbereich exisitiert    
                                         nicht                                    
                                                                    
              S7_E_DEMOEND           0x1234  (Hex) = 4660
              -5                    allgemeiner Fehler  
              -10                    Typ ist nicht erlaubt
              -99                   Refernznummer ist ungÅltig
*/
/* ------------------------------------------------------------------ */
long WINAPI
ES7RdDW (long Ref, DWORD Typ, 
         DWORD DBNr, DWORD Ab, DWORD Anz, LPDWORD Buffer);
/*
      Zweck:  Liest <Anz> Doppelworte ab Doppelwort/ Timerwort <Ab> vom 
              Daten Typ <Typ> der SPS. 
  
  Parameter:  Name    Typ      Beschreibung
              Ref     long     Referenz, die bei ES7Open zurÅckgegeben wird.
              Typ     DWORD    'M', 'm'          = Merker  (DBNr wird ignoriert)
                               
                               'E', 'e','I','i'  = Eingang (DBNr wird ignoriert)
                               'A', 'a', 'O','o' = Ausgang (DBNr wird ignoriert)
                                 'T', 't'          = Timer, die Angabe ist in Millisekunden,
                                                   der Wert wird automatisch in das Format der
                                                   SPS konvertiert.
              
              DBNr    DWORD     Datenbausteinnummer
              
              Ab      DWORD     Startadresse, ab der geschrieben werden soll unbedingt
                                folgendes beachten:
                                Im Gegensatz zu den Wortfunktionen wird hier die Byteadresse im
                                DB, Merker, Eingang oder Ausgangsbereich verwendet 
                                Bei Timer ist dies die Timernummer
                                So kann jederzeit auch auf ungerade Adressen zugegriffen werden                             'D', 'd',         = Datenbaustein, DBNr wird verwendet
              
              Anz       DWORD   Anzahl der zulesenden Worte
              Buffer    LPWORD  ist Pointer auf Zieladresse  
    
    return: 
              S7_E_NOERR             0   alles OK 
              S7_E_TIMEOUT           -1  ZeitÅberlauf 
                                                                                  
              S7_E_NODATA            2   Baustein oder Datenbereich exisitiert    
                                         nicht                                    
                                                                    
              S7_E_DEMOEND           0x1234  (Hex) = 4660
              -5                    allgemeiner Fehler  
              -10                    Typ ist nicht erlaubt
              -99                   Refernznummer ist ungÅltig
*/
long WINAPI
ES7RdB (long Ref, DWORD Typ, DWORD DBNr, DWORD Ab, DWORD Anz, LPBYTE Buffer);
/*
      Zweck:  Liest <Anz> Bytes ab Datenbyte <Ab> vom 
              Daten Typ <Typ> der SPS. 
  
  Parameter:  Name    Typ      Beschreibung
              Ref     long     Referenz, die bei ES7Open zurÅckgegeben wird.
              Typ     DWORD    'M', 'm'          = Merker  (DBNr wird ignoriert)
                               
                               'E', 'e','I','i'  = Eingang (DBNr wird ignoriert)

                               'A', 'a', 'O','o' = Ausgang (DBNr wird ignoriert)
                               'D', 'd',         = Datenbaustein, DBNr wird verwendet
              
              DBNr    DWORD     Datenbausteinnummer
              
              Ab      DWORD    Startbyte ab dem gelesen werden soll unbedingt
                               folgendes beachten !
              Buffer  LPBYTE   Zeiger auf Daten des PC
    
    return: 
              S7_E_NOERR             0   alles OK 
              S7_E_TIMEOUT           -1  ZeitÅberlauf 
                                                                                  
              S7_E_NODATA            2   Baustein oder Datenbereich exisitiert    
                                         nicht                                    
                                                                    
              S7_E_DEMOEND           0x1234  (Hex) = 4660
              -5                     allgemeiner Fehler  
              -10                    Typ ist nicht erlaubt
              -99                    Refernznummer ist ungÅltig
*/
/* ------------------------------------------------------------------ */

long WINAPI
ES7WrW (long Ref, DWORD Typ, DWORD DBNr, DWORD Ab, DWORD Anz, LPWORD Buffer);
/*
      Zweck:  Schreibt <Anz> Worte ab Datenwort <Ab> vom 
              Daten Typ <Typ> der SPS. Die Worte werden mit Drehen
              der Bytes geschrieben.
  
  Parameter:  Name    Typ      Beschreibung
              Ref     long     Referenz, die bei ES7Open zurueckgegeben wird.
              Typ     DWORD    'M', 'm'          = Merker  (DBNr wird ignoriert)
                               
                               'E', 'e','I','i'  = Eingang (DBNr wird ignoriert)
                               'A', 'a', 'O','o' = Ausgang (DBNr wird ignoriert)
                               'D', 'd',         = Datenbaustein, DBNr wird verwendet
              
              DBNr    DWORD     Datenbausteinnummer
              
              Ab      DWORD     Startwort, ab dem geschrieben werden soll unbedingt
                                folgendes beachten !
              *********************************************
              !!! Beachte !!!              
              In der SPS gilt f¸r SPS Programmierer
                                         
                   
                   W0 = Byte 0 und Byte 1
                   W2 = Byte 2 und Byte 3 ...
                   
                   W1 = Byte 1 und Byte 2
                   -> bei Verwendung von ungeraden Worten ist eine 
                   Doppelbelegung gegeben. 
                   Der Trebier unterstÅtz deshalb nur gerade Worte->
               d. h. im PC haben sie z.NB:
               WORD Buf[64];                 
               
               nach dem Aufruf ES7WrW (Ref, Typ, DBNr, 0, 5, Buf) steht
               in Wort 0 Buf[0](nach SPS- Adressierung)
                  Wort 2 Buf[1](nach SPS- Adressierung)
                  Wort 4 Buf[2](nach SPS- Adressierung)
               Sie m¸ssen also die StartWortnummer halbieren, um im
               PC richtig zugreifen zu kˆnnen. Dies gilt auch f¸r 
               Datenbausteine !! --> Ungerade Wortadressen der SPS kˆnnen also
               nicht geschrieben werden.
              ********************************************
              Anz       DWORD   Anzahl der zu schreibenden Worte
              Buffer    LPWORD  ist Pointer auf PC-Adresse
    
    return: 
              S7_E_NOERR             0   alles OK 
              S7_E_TIMEOUT           -1  Zeit¸berlauf 
                                                                                  
              S7_E_NODATA            2   Baustein oder Datenbereich exisitiert    
                                         nicht                                    
                                                                    
              S7_E_DEMOEND           0x1234  (Hex) = 4660
              -5                    allgemeiner Fehler  
              -10                    Typ ist nicht erlaubt
              -99                   Refernznummer ist ungÅltig
*/
/* ------------------------------------------------------------------ */


long WINAPI
ES7WrDW (long Ref, DWORD Typ, DWORD DBNr, DWORD Ab, DWORD Anz, LPDWORD Buffer);
/*
      Zweck:  Schreibt <Anz> Doppelworte ab Doppelwort<Ab> vom 
              Daten Typ <Typ> der SPS. Die Worte werden mit Drehen
              der Bytes geschrieben.
  
  Parameter:  Name    Typ      Beschreibung
              Ref     long     Referenz, die bei ES7Open zurueckgegeben wird.
              Typ     DWORD    'M', 'm'          = Merker  (DBNr wird ignoriert)
                               
                               'E', 'e','I','i'  = Eingang (DBNr wird ignoriert)
                               'A', 'a', 'O','o' = Ausgang (DBNr wird ignoriert)
                               'D', 'd',         = Datenbaustein, DBNr wird verwendet
                               'T', 't'          = Timer, die Angabe ist in Millisekunden,
                                                   der Wert wird automatisch in das Format der
                                                   SPS konvertiert.
              
              DBNr    DWORD     Datenbausteinnummer
              
              Ab      DWORD     Startadresse, ab der geschrieben werden soll unbedingt
                                folgendes beachten:
                                Im Gegensatz zu den Wortfunktionen wird hier die Byteadresse im
                                DB, Merker, Eingang oder Ausgangsbereich verwendet 
                                Bei Timer ist dies die Timernummer
                                So kann jederzeit auch auf ungerade Adressen zugegriffen werden
              Anz       DWORD   Anzahl der zu schreibenden Worte
              Buffer    LPDWORD  ist Pointer auf PC-Adresse
    
    return: 
              S7_E_NOERR             0   alles OK 
              S7_E_TIMEOUT           -1  Zeit¸berlauf 
                                                                                  
              S7_E_NODATA            2   Baustein oder Datenbereich exisitiert    
                                         nicht                                    
                                                                    
              S7_E_DEMOEND           0x1234  (Hex) = 4660
              -5                    allgemeiner Fehler  
              -10                    Typ ist nicht erlaubt
              -99                   Refernznummer ist ungÅltig
*/
/* ------------------------------------------------------------------ */

long WINAPI
ES7WrB (long Ref, DWORD Typ, 
         DWORD DBNr, DWORD Ab, DWORD Anz, LPBYTE Buffer);
/*
      Zweck:  Schreibt <Anz> Bytes ab Datenbyte <Ab> vom 
              Daten Typ <Typ> der SPS. 
  
  Parameter:  Name    Typ      Beschreibung
              Ref     long     Referenz, die bei ES7Open zurÅckgegeben wird.
              Typ     DWORD    'M', 'm'          = Merker  (DBNr wird ignoriert)
                               
                               'E', 'e','I','i'  = Eingang (DBNr wird ignoriert)
                               'A', 'a', 'O','o' = Ausgang (DBNr wird ignoriert)
                               'D', 'd',         = Datenbaustein, DBNr wird verwendet
              
              DBNr    DWORD     Datenbausteinnummer
              
              Ab      DWORD    Startbyte, ab dem geschrieben werden soll 
                               
              Anz     DWORD    Anzahl der zu schreibenden Bytes
              Buffer  LPBYTE   ist Pointer auf PC-Adresse


    
    return: 
              S7_E_NOERR             0   alles OK 
              S7_E_TIMEOUT           -1  ZeitÅberlauf 
                                                                                  
              S7_E_NODATA            2   Baustein oder Datenbereich exisitiert    
                                         nicht                                    
                                                                    
              S7_E_DEMOEND           0x1234  (Hex) = 4660
              -5                    allgemeiner Fehler  
              -10                    Typ ist nicht erlaubt
              -99                   Refernznummer ist ungÅltig
*/
/* ------------------------------------------------------------------ */
long WINAPI
ES7GetMPIMembers (long Ref, LPWORD Teiln) ;
/*
      Zweck:  Ermittelt die erreichbaren Teilnehmer am MPI-Bus
              Es ist Zeiger auf ein Array von min. 128 (Worten 16 BIT)
              zu ¸bergeben.
              Ist der Wert in Teiln[x] ungleich "0", so ist der Teilnehmer vorhanden
              z.B. Teiln[0] != 0 -> Teilnehmer 0 ist erreichbar
               oder Teiln[3] = 1 -> Teilnehmer vorhanden!

              
  
  Parameter:  Name    Typ      Beschreibung
              Ref     long     Referenz, die bei ES7Open zurÅckgegeben wird.
              
              Buffer  LPWORD   Es ist Zeiger auf ein Array von min. 128 (Worten 16 BIT)
                               zu ¸bergeben. 
    
    return: 
              S7_E_NOERR             0   alles OK 
              S7_E_TIMEOUT           -1  ZeitÅberlauf 
                                                                                  
              S7_E_NODATA            2   Baustein oder Datenbereich exisitiert    
                                         nicht                                    
                                                                    
              S7_E_DEMOEND           0x1234  (Hex) = 4660
              -5                    allgemeiner Fehler  
              -10                    Typ ist nicht erlaubt
              -99                   Refernznummer ist ungÅltig
*/

long WINAPI
ES7RdBit (long Ref,  DWORD Typ, DWORD DBNr, DWORD Byte, DWORD Bit, LPBYTE Buffer);

long WINAPI
ES7SetBit (long Ref, DWORD Typ, DWORD DBNr, DWORD Byte, DWORD Bit); 

long WINAPI
ES7ResetBit (long Ref, DWORD Typ, DWORD DBNr, DWORD Byte, DWORD Bit);

long WINAPI
ES7RdReal (long Ref, DWORD Typ, DWORD DBNr, DWORD Ab, DWORD Anz, double *Buffer);

long WINAPI
ES7WrReal (long Ref, DWORD Typ, DWORD DBNr, DWORD Ab, DWORD Anz, double *Buffer);

long WINAPI
ES7RdDW (long Ref, DWORD Typ, DWORD DBNr, DWORD Ab, DWORD Anz, LPDWORD Buffer);

long WINAPI
ES7WrDW (long Ref, DWORD Typ, DWORD DBNr, DWORD Ab, DWORD Anz, LPDWORD Buffer);

long WINAPI
ES7OpenMPILan (LPCSTR IPAdr, DWORD RxTimeout, DWORD TxTimeout, DWORD ConnectTimeout,
               DWORD SPSMPIAdr, DWORD LocalMPIAdr, DWORD SPSTyp, DWORD MPIBaud);




#ifdef __cplusplus
}
#endif 
