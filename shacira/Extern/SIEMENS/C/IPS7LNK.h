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

/* IPS7LNK.H
   Version 1.32
*/

#ifndef _IPS7LNK_H_45632
#define _IPS7LNK_H_45632

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __linux__

#ifndef WINTYPES_DEFINED
#define WINAPI
  typedef unsigned char BYTE;
  typedef unsigned char *LPBYTE;
  typedef unsigned char *PBYTE;
  typedef char *PSTR;
  typedef char *LPSTR;
  typedef const char *LPCSTR;
  typedef const char *PCSTR;
  typedef unsigned short int  WORD;
  typedef unsigned short int  *LPWORD;
  typedef short int INT;
  typedef short int  *LPINT;
  typedef unsigned short int  *PWORD;
  typedef unsigned long  DWORD;
  typedef unsigned long  *PDWORD;
  typedef unsigned long  *LPDWORD;
  typedef void  VOID;
  typedef void *PVOID;
  typedef void *LPVOID;
  typedef int BOOL;
  typedef short int BOOL16;
#endif

void
IPS7CloseAll (void);
/*
  nur für LINUX, gibt reserviertne Speicher frei uns schliesst Sockets!
*/

#endif // __linux__



long WINAPI // S7-200 1.21
IPS7OpenS7200 (LPCSTR IPAdr, DWORD Rack, DWORD Slot, DWORD RxTimeout, DWORD TxTimeout, DWORD ConnectTimeout);      

long WINAPI
IPS7Open (LPCSTR IPAdr, DWORD Rack, DWORD Slot, DWORD RxTimeout, DWORD TxTimeout, DWORD ConnectTimeout);      

long WINAPI
IPS7OpenPG (LPCSTR IPAdr, DWORD Rack, DWORD Slot, DWORD RxTimeout, DWORD TxTimeout, DWORD ConnectTimeout);  // 1.17
    
extern long WINAPI
IPS7Close (long Ref);

extern long WINAPI
IPS7RdW (long Ref, DWORD Typ, DWORD DBNr, DWORD AbWort, DWORD WortAnz, LPWORD Buffer) ;

extern long WINAPI
IPS7WrW (long Ref, DWORD Typ, DWORD DBNr, DWORD Ab, DWORD Anz, LPWORD Buffer);

extern long WINAPI // 1.17
IPS7RdPlcW (long Ref, DWORD Typ, DWORD DBNr, DWORD AbWort, DWORD WortAnz, LPWORD Buffer) ;

extern long WINAPI // 1.17
IPS7WrPlcW (long Ref, DWORD Typ, DWORD DBNr, DWORD Ab, DWORD Anz, LPWORD Buffer);


extern long WINAPI
IPS7WrB (long Ref, DWORD Typ,
         DWORD DBNr, DWORD Ab, DWORD Anz, LPBYTE Buffer);

extern long WINAPI
IPS7RdB (long Ref, DWORD Typ,
         DWORD DBNr, DWORD Ab, DWORD Anz, LPBYTE Buffer);


extern long WINAPI
IPS7GetSockErr (long Ref);

/*
Aufrufe der BitFunktionen wie gewöhnlich
Beispiel Setzte / Rücksetze Bit DB10.DDB5.1
IPS7SetBit (Ref, 'D', 10, 5, 1);
IPS7ResetBit (Ref, 'D', 10, 5, 1);
Lesen:
BYTE Wert;
IPS7RdBit (Ref, 'D', 10, 5, 1, Wert);
Wert = 1 -> Bit = 1
Wert = 0 -> Bit = 0;
*/

long WINAPI
IPS7RdBit (long Ref, DWORD Typ, DWORD DBNr, DWORD Byte, DWORD Bit, LPBYTE Buffer);

long WINAPI
IPS7SetBit (long Ref, DWORD Typ, DWORD DBNr, DWORD Byte, DWORD Bit);

long WINAPI
IPS7ResetBit (long Ref, DWORD Typ, DWORD DBNr, DWORD Byte, DWORD Bit); 

long WINAPI
IPS7RdReal (long Ref, DWORD Typ, DWORD DBNr, DWORD Ab, DWORD Anz, double *Buffer);

long WINAPI
IPS7WrReal (long Ref, DWORD Typ, DWORD DBNr, DWORD Ab, DWORD Anz, double *Buffer);

long WINAPI
IPS7RdDW (long Ref, DWORD Typ, DWORD DBNr, DWORD Ab, DWORD Anz, LPDWORD Buffer);

long WINAPI
IPS7WrDW (long Ref, DWORD Typ, DWORD DBNr, DWORD Ab, DWORD Anz, LPDWORD Buffer);

long WINAPI
IPS7OpenEx (LPCSTR IPAdr, DWORD Rack, DWORD Slot, DWORD SubNetId, DWORD DstMPIAdr, DWORD AccessMode, DWORD RxTimeout, DWORD TxTimeout, DWORD ConnectTimeout);      // 1.23


long WINAPI
IPS7OpenS7LanEx (LPCSTR IPAdr, DWORD Rack, DWORD Slot, DWORD SubNetId, DWORD DstMPIAdr, DWORD AccessMode, DWORD RxTimeout, DWORD TxTimeout, DWORD ConnectTimeout);

long WINAPI
IPS7OpenS7LanPG (LPCSTR IPAdr, DWORD Rack, DWORD Slot, DWORD RxTimeout, DWORD TxTimeout, DWORD ConnectTimeout);      

long WINAPI
IPS7OpenS7LanOP (LPCSTR IPAdr, DWORD Rack, DWORD Slot, DWORD RxTimeout, DWORD TxTimeout, DWORD ConnectTimeout);

#ifdef __cplusplus
}
#endif 
#endif // _IPS7LNK_H_45632
