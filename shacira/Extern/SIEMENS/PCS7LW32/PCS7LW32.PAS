(*
  Modul       : PCS7LW32.PAS interface for delphi
  Version     : 1.11
  Projekt     : Datenkopplung SIMATIC-S7 300/400 <----> IBM-PC
                mit PC/MPI-Adapter

  for changes and version notes see "version.txt"
*)  

{$A- $O-}

(* Recordausrichtung ausschalten Code Optimierung auch ausschalten *)
(* siehe Projekt - Optionen Compiler *)


unit PCS7LW32;

interface
         
{--------------------------------------------------------------}
{----------------------Konstantendefinitionen------------------}
{--------------------------------------------------------------}

CONST
{ Schnittstellennummern }
  COM1             = 0;
  COM2             = 1;
  COM3             = 2;
  COM4             = 3;
  COM5             = 4;
  COM6             = 5;
  COM7             = 6;
  COM8             = 7;
  COM9             = 8;
  COM10            = 9;
  COM11            = 10;
  COM12            = 11;
  COM13            = 12;
  COM14            = 13;
  COM15            = 14;
  COM16            = 15;

  BST_ART_ANZ      = 7;

{---------------------- Fehlerarten ---------------------------}


S7_E_NOERR      =         0   (* alles OK *)                        
S7_E_TIMEOUT    =         -1  (* ZeitÅberlauf *)                    
S7_E_BADBAUD    =         -2  (* Baudrate ungÅltig *)               
S7_E_BADMPIADR  =         -3  (* MPI-Adresse ungÅltig *)    
S7_E_NOCOM      =         -4  (* COM nicht vorhanden  *)    
                                  
S7_E_NOBST      =        2                                         
S7_E_BSTLEN     =        2   (* Baustein ist zu kurz *)            
S7_E_NODATA     =        2   (* Datenbereich existiert nicht *)    
S7_E_BADADDRESS =        3   
S7_E_BADCMD     =        4  
                            
S7_E_TOMANY     =        7  
S7_E_SLAVEOUT   =        8  
S7_E_CMDLOCKED  =        9  
S7_E_DEMOEND    =        $1234     



TYPE DWORD = LongInt;

TYPE PDWORD = ^DWORD;

TYPE PWORD = ^WORD;
TYPE PNIL  = ^WORD;
{-----------------------  Datentypen ----------------------------}

Type
  S7 = record
  Com    : WORD;
  bInit  : LongBool;
  Err    : Integer;         
  SPSTyp : Integer;         

  Internal : ARRAY of BYTE [1..1536];
end;



(* ------------------------------------------------------------------ *)

FUNCTION
S7Init (var pS7 : S7; Com : WORD; SPSMPIAdr : WORD; LocalMPIAdr : WORD; Baud : WORD) : LongBool; stdcall;
(*
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

*)   
FUNCTION
S7PPIInit (var pS7 : S7; Com : WORD; SPSMPIAdr : WORD; LocalMPIAdr : WORD; Baud : WORD) : LongBool; stdcall;
(*
      Zweck:  S7PPIInit initialisiert das in pS7 beschriebene an pS7->Com 
              angeschlossene AG und die dazugehîrige Schnittstelle. 
              Zum Betrieb an einer S7 200
              pS7->Com mu· COM1, COM2, COM3 ... COM16 sein. 
              pS7->MPINr ist die MPI-Nummer 
  
  Parameter:  Name          Typ      Beschreibung
                            
              pS7           LPS7     Pointer auf den Speicher fÅr das angewÑhlte 
                                     AG 
              SPSMPIAdr     WORD     MPI-Adresse des Partner (SPS)
              LocalMPIAdr   WORD     eigen MPI-Adresse (normal 0)
              Baud          WORD     9600, 19200
 
     Return:  BOOL          TRUE    wenn erfolgreich, 
                            FALSE   bei Fehler pS7->Err auswerten

*)   

  


(*------------------------------------------------------------*)

FUNCTION
S7Exit ( var pS7 : LPS7) : LongBool; stdcall;
(*
      Zweck:  S7xit  mu· fÅr jede mit S7nit mit Return TRUE 
              initialisierte Struktur S7 ausgefÅhrt werden. 
              Die zugehîrigen Schnittstelle wird deaktiviert.
                                                
                        
  Parameter:  Name     Typ      Beschreibung
  
              pS7     LPS7       Pointer auf den Speicher fÅr das angewÑhlte 
                                AG 
 
     Return:  BOOL      TRUE    wenn erfolgreich, 
                        FALSE   bei Fehler 
*)


(* ------------------------------------------------------------------ *)
(* ------------------Merker-Operationen------------------------------ *)
(* ------------------------------------------------------------------ *)


FUNCTION 
S7RdMB (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall;
(*
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
*)               
(* ------------------------------------------------------------------ *)
 
FUNCTION 
S7WrMB (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall;
(*
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
*)               
(* ------------------------------------------------------------------ *)

FUNCTION
S7RdMW (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall;
(*
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
*)               
(* ------------------------------------------------------------------ *)


FUNCTION 
S7WrMW (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall;
(*
      Wie S7RdMW nur eben schreiben 
*)

(* ------------------------------------------------------------------ *)
(* -----------------Eingangs-Operationen----------------------------- *)
(* ------------------------------------------------------------------ *)

FUNCTION 
S7RdEB (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall;
(*
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
*)               
(* ------------------------------------------------------------------ *)

FUNCTION 
S7RdEW (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall;
(*
      Wie S7RdMW 
*)
(* ------------------------------------------------------------------ *)
(* ------------------------------------------------------------------ *)
(* -----------------Ausgangs-Operationen----------------------------- *)
(* ------------------------------------------------------------------ *)

FUNCTION 
S7RdAB (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall;
(*
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
*)               
(* ------------------------------------------------------------------ *)

FUNCTION 
S7WrAB (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall;
(*
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
*)               
(* ------------------------------------------------------------------ *)

FUNCTION 
S7RdAW (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall;
(*
      Wie S7RdMW 
*)
(* ------------------------------------------------------------------ *)

FUNCTION 
S7WrAW (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall;
(*
      Wie S7RdMW nur eben schreiben 
*)
(* ------------------------------------------------------------------ *)
                                               
(* ------------------------------------------------------------------ *)
(* -----------------Timer   -Operationen----------------------------- *)
(* ------------------------------------------------------------------ *)


FUNCTION 
S7RdTimer (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PDWORD) : LongBool; stdcall;
(*
  Liest Anz Timer ab Nr <Ab> aus der SPS. Der Treiber rechnet das SPS-Format in
  Millisekunden um, deshalb wird hier als <Buf> auch als Pointer auf Long
              
  
  Parameter:  Name     Typ      Beschreibung
              pS7      LPS7      Pointer auf den Speicher fÅr das angewÑhlte 
                                AG
              Ab       WORD     Start-Bytenummer
              Anz      WORD     Anzahl der Worte, die gelesen werden sollen
              Buf      PDWORD   Pointer auf den Zielspeicher im PC
     
     Return:  BOOL     TRUE     wenn erfolgreich 
                       FALSE    bei Fehler pS7->Err auswerten


*)               
(* ------------------------------------------------------------------ *)

FUNCTION 
S7WrTimer (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PDWORD) : LongBool; stdcall;
(*      
  Schreibt  Anz Timer ab Nr <Ab> in die SPS.
  Der Wert der Timer ist in ms anzugeben. Das SPS-Format wird
  automatisch erzeugt. Dazu kann es zwangslÑufig zu Rundungen kommen!
  Nur fÅr Anwender mit SPS-Kenntnissen geeignet !
  kleinste Auflîsung 10 ms Schritte
*)
(* ------------------------------------------------------------------ *)
(* -----------------ZÑhler  -Operationen----------------------------- *)
(* ------------------------------------------------------------------ *)


FUNCTION 
S7RdCounter (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall;
(*      
  Liest Anz ZÑhler ab Nr <Ab> aus der SPS 
  maximaler Wert eines ZÑhlers 999
  Der Treiber konvertiert automatisch vom SPS-Format ins PC-Format
*)
(* ------------------------------------------------------------------ *)


FUNCTION 
S7WrCounter (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall;
(*         
  Schreibt Anz ZÑhler ab Nr <Ab> in die SPS 
  maximaler Wert eines ZÑhlers 999     
  Der Treiber konvertiert automatisch ins SPS-Format

*)
(* ------------------------------------------------------------------ *)
(* -----------------DB      -Operationen----------------------------- *)
(* ------------------------------------------------------------------ *)

FUNCTION
S7RdDB (var pS7 : S7; DBNr : WORD; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall;
(*       
      Zweck:  S7RdDB liest vom mit pS7	initalisierten AG den Datenbaustein
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
*)
(*------------------------------------------------------------*)

FUNCTION 
S7WrDB (var pS7 : S7; DBNr : WORD; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall;
(*
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
*)
(*------------------------------------------------------------*)


PROCEDURE
S7ExitAll :  stdcall;

implementation


FUNCTION
S7Init (var pS7 : S7; Com : WORD; SPSMPIAdr : WORD; LocalMPIAdr : WORD; Baud : WORD) : LongBool; stdcall; external 'PCS7LW32.DLL';   
  
FUNCTION
S7PPIInit (var pS7 : S7; Com : WORD; SPSMPIAdr : WORD; LocalMPIAdr : WORD; Baud : WORD) : LongBool; stdcall; external 'PCS7LW32.DLL';           

FUNCTION
S7Exit (var pS7 : LPS7) : LongBool; stdcall; external 'PCS7LW32.DLL';

FUNCTION 
S7RdMB (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall; external 'PCS7LW32.DLL';
 
FUNCTION 
S7WrMB (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall; external 'PCS7LW32.DLL';

FUNCTION
S7RdMW (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall; external 'PCS7LW32.DLL';

FUNCTION 
S7WrMW (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall; external 'PCS7LW32.DLL';

FUNCTION 
S7RdEB (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall; external 'PCS7LW32.DLL';

FUNCTION 
S7RdEW (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall; external 'PCS7LW32.DLL';

FUNCTION 
S7RdAB (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall; external 'PCS7LW32.DLL';

FUNCTION 
S7WrAB (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall; external 'PCS7LW32.DLL';

FUNCTION 
S7RdAW (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall; external 'PCS7LW32.DLL';

FUNCTION 
S7WrAW (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall; external 'PCS7LW32.DLL';

FUNCTION 
S7RdTimer (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PDWORD) : LongBool; stdcall; external 'PCS7LW32.DLL';

FUNCTION 
S7WrTimer (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PDWORD) : LongBool; stdcall; external 'PCS7LW32.DLL';

FUNCTION 
S7RdCounter (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall; external 'PCS7LW32.DLL';

FUNCTION 
S7WrCounter (var pS7 : S7; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall; external 'PCS7LW32.DLL';

FUNCTION
S7RdDB (var pS7 : S7; DBNr : WORD; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall; external 'PCS7LW32.DLL';

FUNCTION 
S7WrDB (var pS7 : S7; DBNr : WORD; Ab : WORD; Anz : WORD; Buf : PNIL) : LongBool; stdcall; external 'PCS7LW32.DLL';

PROCEDURE
S7ExitAll :  stdcall; external 'PCS7LW32.DLL';


begin
end.

{$A+}
