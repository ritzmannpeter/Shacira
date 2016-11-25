(* 
  Author : 
  Dipl.-Ing. A. Traeger
  Traeger Industy Components
  WWW.TRAEGER.DE
  Am Steigacker 26
  D - 92694 Etzenricht
  Tel 0961/482300
  Fax 0961/48230 20
*)           
(*
   Version       : 1.00
   Modul         : PCS7EASY.PAS
   Projekt       : Datenkopplung SIMATIC-S7 per PC-MPI-Adapter

   Versionsinfo siehe "version.htm"

*)

unit PCS7EASY;

interface
TYPE PDWORD =  ^LongWord;
TYPE PWORD =  ^WORD;
TYPE PBYTE =  ^BYTE;
TYPE PDOUBLE = ^Double;

FUNCTION
ES7OpenMPILan (IPAdr : PChar; RxTimeout : LongWord; TxTimeout : LongWord ; ConnectTimeout : LongWord;
               SPSMPIAdr : LongWord; LocalMPIAdr : LongWord; SPSTyp : LongWord; MPIBaud : LongWord ) : LongInt; stdcall; external 'PCS7EASY.DLL';      

FUNCTION
ES7OpenEx (Com : LongWord; SPSMPIAdr : LongWord; LocalMPIAdr : LongWord; Baud : LongWord; SPSTyp : LongWord; MPIBaud : LongWord) : LongInt; stdcall; external 'PCS7EASY.DLL';      


FUNCTION
ES7Open (Com : LongWord; SPSMPIAdr : LongWord; LocalMPIAdr : LongWord; Baud : LongWord; SPSTyp : LongWord) : LongInt; stdcall; external 'PCS7EASY.DLL';      

FUNCTION
ES7OpenEx (Com : LongWord; SPSMPIAdr : LongWord; LocalMPIAdr : LongWord; Baud : LongWord; SPSTyp : LongWord; MPIBaud : LongWord) : LongInt; stdcall; external 'PCS7EASY.DLL';      
    
FUNCTION
ES7Close (Ref : LongInt) : LongInt; stdcall; external 'PCS7EASY.DLL';      


FUNCTION
ES7RdW (Ref : LongInt; Typ : Longword; DBNr : Longword; AbWort : Longword; WortAnz : Longword;  Buffer : PWORD)  : LongInt; stdcall; external 'PCS7EASY.DLL';

FUNCTION
ES7RdDW (Ref : LongInt; Typ : Longword; DBNr : Longword; AbWort : Longword; WortAnz : Longword;  Buffer : PDWORD)  : LongInt; stdcall; external 'PCS7EASY.DLL';

FUNCTION
ES7RdB (Ref : LongInt; Typ : Longword;  DBNr: Longword;
          Ab : Longword;  Anz : Longword; Buffer: PBYTE) : LongInt; stdcall; external 'PCS7EASY.DLL';

FUNCTION
ES7WrW (Ref : LongInt; Typ : Longword; DBNr : Longword; AbWort : Longword; WortAnz : Longword; Buffer : PWORD)  : LongInt; stdcall; external 'PCS7EASY.DLL';

FUNCTION
ES7WrDW (Ref : LongInt; Typ : Longword; DBNr : Longword; AbWort : Longword; WortAnz : Longword; Buffer : PDWORD)  : LongInt; stdcall; external 'PCS7EASY.DLL';

FUNCTION
ES7WrB (Ref : LongInt; Typ : Longword;  DBNr: Longword;
         Ab : Longword;  Anz : Longword; Buffer: PBYTE) : LongInt; stdcall; external 'PCS7EASY.DLL';

FUNCTION
ES7RdBit (Ref : LongInt; Typ : Longword;  DBNr: Longword;
           ByteNr : Longword;  BitNr : Longword; Buffer: PBYTE) : LongInt; stdcall; external 'PCS7EASY.DLL';

FUNCTION
ES7SetBit (Ref : LongInt; Typ : Longword;  DBNr: Longword;
            ByteNr : Longword;  BitNr : Longword) : LongInt; stdcall; external 'PCS7EASY.DLL';

FUNCTION
ES7ResetBit (Ref : LongInt; Typ : Longword;  DBNr: Longword;
            ByteNr : Longword;  BitNr : Longword) : LongInt; stdcall; external 'PCS7EASY.DLL';

FUNCTION
ES7RdReal (Ref : LongInt; Typ : Longword; DBNr : Longword; AbWort : Longword; WortAnz : Longword;  Buffer : PDOUBLE)  : LongInt; stdcall; external 'PCS7EASY.DLL';

FUNCTION
ES7WrReal (Ref : LongInt; Typ : Longword; DBNr : Longword; AbWort : Longword; WortAnz : Longword;  Buffer : PDOUBLE)  : LongInt; stdcall; external 'PCS7EASY.DLL';


implementation

begin
end.
