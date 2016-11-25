/* 
   Modul         : ES7DEMO.C
   
*/


#ifdef WIN32

  #include <WINDOWS.H>
  #include <conio.h>
#endif

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <unistd.h>
#endif


#include "pcs7easy.h"

#define COM1    0
#define COM2    1
#define COM3    2

#if !defined (_WINDOWS) && !defined (__linux__)
WORD WordBuffer[1024];
BYTE ByteBuffer[1024];
DWORD DWordBuffer[256];
double DoubleBuffer[256];
#else
WORD WordBuffer[1024];
BYTE ByteBuffer[1024];
DWORD DWordBuffer[1024];
double DoubleBuffer[1024];
#endif

WORD EigeneMPIAdr;

static   DWORD Com = COM1;
static   WORD MPIAdr;
static DWORD Baud = 19200;   
static DWORD SPSTyp = 300;



#ifdef __linux__
#define stricmp(s1,s2) strcasecmp((s1),(s2))
#endif

int  
GetKey (void)
{
  char C;

  fflush (stdin);
  fread (&C, 1, 1, stdin);
  return (C);
}
/* ------------------------------------------------------------------ */

void
GoOn (void)
{
  printf ("Weiter mit EINGABE-Taste / to continue press ENTER key\r");
  GetKey ();
#ifdef __linux__
  GetKey ();
#endif
}

/* ------------------------------------------------------------------ */

void      
DoErr (long Res)
{     
  char *Err;
   
  switch (Res)
  {
    case -1:
      Err = "Zeitueberlauf / Timeout";
      break;
    
    case 2:                 
      Err = "DB oder Datenbereich exisitiert nicht / data area in PLC not available";
      break;
    
    case -5:
      Err = "allgemeiner Fehler / general error";
      break;
      
    case -10:
      Err = "Typ-Kennung falsch / invalid typ";
      break; 
    
    case -99: 
      Err = "Referenznummer ist ungueltig / invalid reference no.";
      break;
      
    case 0x1234:
      Err = "Demozeit ist abgelaufen / demo time is over";
      break;
    
    default:   
      Err = "Unerwarteter Fehler / unknown error";
  }                               
  printf ("\n*************************\n"
          "\aFehler / error  %ld\n %s\n"
          "\n**************************\n" , Res, Err);
  GoOn ();
} 
/* ------------------------------------------------------------------ */

void 
WrDB (long Ref)
{
  WORD DBNr,
       i,      
       Len, Wert;
  long Res;
         
  printf ("Schreibe/writting  DB ab/from DW 0\n");
  printf ("\nSchreibe/writting DB-Nummer/DB-No.:");
  scanf ("%u",&DBNr);

  printf ("\nAnzahl der Worte: / Count of words:");
  scanf ("%u",&Len);                    
  
  printf ("\nSchreibwert: / value to write: ");
  scanf ("%u",&Wert);                    
  
  for (i = 0; i < Len; i++)         
    WordBuffer[i] = Wert;

  Res = ES7WrW (Ref, 'D', DBNr, 0, Len, WordBuffer);
  if (Res == 0) // alles OK
  {       
    for (i=0; i < Len;i++)
    {
      printf ("DW %03u = %04x               \n",i*2,WordBuffer[i]);
      if (i % 11 == 10)
        GoOn ();
    }
    GoOn ();
  }
  else   
  {  
    DoErr (Res);
  }
}
/*------------------------------------------------------------*/

void 
RdDB (long Ref)
{
  WORD DBNr, 
          i,      
        Len, AbWort;
  
  long Res;      
           
  
  printf ("Lese / reading DB\n");
  printf ("Lese /reading DB-Nummer: / DB-No:");
  scanf ("%u",&DBNr);


  printf ("\nStart ab Wort: / start from word:");
  scanf ("%u",&AbWort);                    
  
  printf ("\nAnzahl der Worte: / count of words:");
  scanf ("%u",&Len);                    
  
  
  Res = ES7RdW (Ref, 'D', DBNr, AbWort, Len, WordBuffer);
  if (Res == 0)
  {
    for (i=0; i < Len;i++)
    {
      printf ("DW %03u = %04x               \n",AbWort + i*2,WordBuffer[i]);
      if (i % 11 == 10)
        GoOn ();
    }   
    GoOn ();
  }
  else
  {
    DoErr (Res);
  }
}
/*------------------------------------------------------------*/

void
RdEB (long Ref)
{
  WORD  EBNr,
           i,      
           Len;
  long Res;
  
  printf ("Lese Eingangsbyte / reading input bytes\n ");
  printf ("Start byte:");
  scanf ("%u",&EBNr);

  printf ("Anzahl der Bytes / count of bytes to read\n");
  scanf ("%u",&Len);                    

  Res =  ES7RdB (Ref, 'E', 0, EBNr, Len, ByteBuffer);
                                                       
  if (Res == 0)
  {
    for (i=0; i < Len;i++)
    {
      printf ("EB %03u = %04x \n",i, (WORD) ByteBuffer[i]);
      if (i % 11 == 10)
        GoOn ();
    }
    GoOn ();
  }   
  else
  {
    DoErr (Res);
  }
}
/*------------------------------------------------------------*/
    
void 
RdMB (long Ref)
{
  WORD  MBNr,
           i,
           Len;
  long  Res;

  printf ("Lese Merker Byte / reading flag bytes\n ");
  printf ("Start byte: ");
  scanf ("%u",&MBNr);

  printf ("Anzahl der Bytes / count of bytes to read: ");
  scanf ("%u",&Len);
   

  Res = ES7RdB (Ref, 'M', 0,  MBNr, Len, ByteBuffer);
  if (Res == 0)
  {
    for (i=0; i < Len;i++)
    {
      printf ("MB %03u = %04x \n",i, (WORD) ByteBuffer[i]);
      if (i % 11 == 10)
        GoOn ();
    }
    GoOn ();
  }
  else
  {
    DoErr (Res);
  }

}
/*------------------------------------------------------------*/


void 
xForEverRdMB (long Ref)
{
  WORD  MBNr,
           i,
           Len;
  long  Res;

  printf ("Lese Merker Byte / reading flag bytes\n ");
  printf ("Start byte: ");
  scanf ("%u",&MBNr);

  printf ("Anzahl der Bytes / count of bytes to read: ");
  scanf ("%u",&Len);
   
  for (;;)
  {
    Res = ES7RdB (Ref, 'M', 0,  MBNr, Len, ByteBuffer);
    if (Res == 0)
    {
      for (i=0; i < Len;i++)
      {
        printf ("MB %03u = %04x \n",i, (WORD) ByteBuffer[i]);
      }
    } 
    else
    {
      DoErr (Res);
      GoOn ();
    }
  }
}
/*------------------------------------------------------------*/



void 
WrAB (long Ref)
{
  WORD  Nr,
        i,      
        Len,
        Wert;
  long Res;
  
  printf ("\nSchreibe Ausgangsbyte: / writting output bytes\n");
  
  printf ("Start byte: ");
  scanf ("%u",&Nr);
               
  printf ("Schreibwert: / value for writting: ");
  scanf ("%u",&Wert);                    
  
  printf ("Anzahl: ");
  scanf ("%u",&Len);                    
  
  for (i = 0; i < Len; i++)
    ByteBuffer[i] = (BYTE) Wert;        
  
  Res = ES7WrB (Ref, 'A', 0, Nr, Len, ByteBuffer);
  if (Res == 0)
  {
    printf ("ab/from AB/OB %d , %d Bytes geschrieben/written\n", Nr, Len);
  }
  else
  {
    DoErr (Res);
  }
}
/*------------------------------------------------------------*/
void
ShowTeiln (long Ref)
{
  long Res;
  static WORD Teiln[127];

  Res = ES7GetMPIMembers (Ref, Teiln);
  if (Res == 0)
  { 
    int i;
    printf ("Erreichbare Teilnehmer: / available MPI-members:\n");


    for (i = 0; i < 127; i++)
    {
      if (Teiln[i] && i != EigeneMPIAdr)
        printf ("%d, ", i);
    }
    GoOn ();
  }
  else
  {
    DoErr (Res);
  }     
  printf ("\n");
}

void 
RdTimer (long Ref)
{
  WORD  TimerNr,
           i,      
           Cnt;
  long  Res;
  
  printf ("Lese Timer / read Timer\n ");
  printf ("Start Timer Nr: / start number of timer: ");
  scanf ("%u",&TimerNr);

  printf ("Anzahl der Timer / count of timer\n");  
  scanf ("%u",&Cnt);                    
   
  
  Res = ES7RdDW (Ref, 'T', 0,  TimerNr, Cnt, DWordBuffer);
  
  if (Res == 0)
  {
    for (i=0; i < Cnt;i++)
    {
      printf ("T %3u = %ld \n",i+TimerNr, DWordBuffer[i]);
      if (i % 11 == 10)
        GoOn ();
    }
    GoOn ();
  }
  else
  {
    DoErr (Res);
  }
}
/*------------------------------------------------------------*/

void 
RdCounter (long Ref)
{
  WORD  Nr,
           i,      
           Cnt;
  long  Res;
  
  printf ("Lese Zaehler / read counter\n ");
  printf ("Start Zaehler Nr: / start number of counter:");
  scanf ("%u",&Nr);

  printf ("Anzahl der Zaehler / count of counter\n");  
  scanf ("%u",&Cnt);                    
   
  
  Res = ES7RdW (Ref, 'Z', 0,  Nr, Cnt, WordBuffer);
  
  if (Res == 0)
  {
    for (i=0; i < Cnt;i++)
    {
      printf ("Z %3u = %d \n",i+Nr, WordBuffer[i]);
      if (i % 11 == 10)
        GoOn ();
    }
    GoOn ();
  }
  else
  {
    DoErr (Res);
  }
}
/*------------------------------------------------------------*/

void 
WrTimer (long Ref)
{
  WORD i,TimerNr,      
       Len;
  DWORD  Wert;
  long Res;
         
  printf ("Schreibe Timer ab / write Timer\n");
  
  printf ("StartNr / start no. of timer: ");
  scanf ("%u",&TimerNr);

  printf ("\nAnzahl der Timer: / count of Timer:  ");  
  scanf ("%u",&Len);                    
  
  printf ("\nSchreibwert: / write value:");
  scanf ("%lu",&Wert);                    
  
  for (i = 0; i < Len; i++)         
    DWordBuffer[i] = Wert;
                           
  Res = ES7WrDW (Ref, 'T', 0, TimerNr, Len, DWordBuffer);
  if (Res == 0) // alles OK
  {       
    for (i=0; i < Len;i++)
    {
      printf ("T %03u = %ld               \n",i + TimerNr,DWordBuffer[i]);
      if (i % 11 == 10)
        GoOn ();
    }
    GoOn ();
  }
  else   
  {  
    DoErr (Res);
  }
}

void 
WrCounter (long Ref)
{
  WORD i,Nr,      
       Len;
  WORD  Wert;
  long Res;
         
  printf ("Schreibe Zaehler / write counter\n");
  
  printf ("StartNr: / start no. of counter:");
  scanf ("%u",&Nr);

  printf ("\nAnzahl der Zaehler: / count of counter: ");
  scanf ("%u",&Len);                    
  
  printf ("\nSchreibwert: / write value: ");
  scanf ("%u",&Wert);                    
  
  for (i = 0; i < Len; i++)         
    WordBuffer[i] = Wert;
                           
  Res = ES7WrW (Ref, 'Z', 0, Nr, Len, WordBuffer);
  if (Res == 0) // alles OK
  {       
    for (i=0; i < Len;i++)
    {
      printf ("Z %03u = %d\n",i + Nr,WordBuffer[i]);
      if (i % 11 == 10)
       GoOn ();
    }
    GoOn ();
  }
  else   
  {  
    DoErr (Res);
  }
}
/*------------------------------------------------------------*/

void 
RdMBit (long Ref)
{
  WORD  MBNr, BitNr;      
  long  Res;
  
  printf ("Lese Merker Bit / reading bit of flag\n ");
  printf ("ByteNr: / Byte no.:");
  scanf ("%u",&MBNr);
  for (;;)
  {
    printf ("BitNr: / Bit no: ");
    scanf ("%u",&BitNr);
    if (BitNr > 7 || BitNr < 0)
      printf ("BitNr muss zwischen 0 und 7 liegen. / Bit must be between 0 and 7.");
    else
      break;
  }
     
  Res = ES7RdBit (Ref, 'M', 0,  MBNr, BitNr, ByteBuffer);
  
  if (Res == 0)
  {
    printf ("MB %d.%d = %d \n", MBNr, BitNr, (WORD) ByteBuffer[0]);
    GoOn ();
  }
  else
  {
    DoErr (Res);
  }
}
/*------------------------------------------------------------*/

void 
SetMBit (long Ref, BOOL Mode)
{
  WORD  MBNr, BitNr;      
  long  Res;
  
  if (Mode)
  {
    printf ("Setze Merker Bit / Set bit of flag\n");
  }
  else
    printf ("Ruecksetze Merker Bit / Reset bit of flag\n");

  printf ("ByteNr: ");
  scanf ("%u",&MBNr);
  for (;;)
  {
    printf ("BitNr: ");
    scanf ("%u",&BitNr);
    if (BitNr > 7 || BitNr < 0)
      printf ("BitNr muss zwischen 0 und 7 liegen. / Bit must be between 0 and 7.");
    else
      break;
  }
     
  if (Mode)
    Res = ES7SetBit (Ref, 'M', 0, MBNr, BitNr);
  else
    Res = ES7ResetBit (Ref, 'M', 0, MBNr, BitNr);
  
  if (Res == 0)
  {
    if (Mode)
      printf ("Bit gesetzt. / bit is set.");
    else
      printf ("Bit zurueckgesetzt. / bit reseted ");
    GoOn ();
  }
  else
  {
    DoErr (Res);
  }
}
/*------------------------------------------------------------*/

void
RdFloat (long Ref)
{
  WORD DBNr,
       Ab,
       i,      
       Len;
  long Res;
         
  printf ("Lese floating point von DB / reading floating point from DB\n");
  printf ("\nLese von DB mit Nummer: / reading from DB with no.: ");
  scanf ("%u",&DBNr);

  printf ("\nStartbyte: / start byte: ");
  scanf ("%u",&Ab);                    
  
  printf ("\nAnzahl der Werte: / count of values: ");
  scanf ("%u",&Len);                    
                        
  
  Res = ES7RdReal (Ref, 'D', DBNr, Ab, Len, DoubleBuffer);
  if (Res == 0)
  {
    for (i=0; i < Len;i++)
    {
      printf ("Float an Byte float at byte %d = %f\n",i*4 + Ab,DoubleBuffer[i]);
      if (i % 11 == 10)
        GoOn ();
    }
    GoOn ();
  }    
  if (Res != 0)  
  {  
    DoErr (Res);
  }
}
/*------------------------------------------------------------*/
void
WrFloat (long Ref)
{
  WORD DBNr,
       Ab,
       i,      
       Len;
  double Wert;
  long Res;
         
  printf ("Schreibe floating Point in DB / writing floating \n");
  printf ("\nSchreibe in DB mit Nummer: / writing to DB with no.: ");
  scanf ("%u",&DBNr);

  printf ("\nStartbyte: / start byte: ");
  scanf ("%u",&Ab);                    
  
  printf ("\nAnzahl der Werte: / count of values: ");
  scanf ("%u",&Len);                    

  printf ("\nSchreibwert: / value to be written: ");
  scanf ("%lf",&Wert);                    
  
  for (i = 0; i < Len; i++)         
    DoubleBuffer[i] = Wert;
                           
  Res = ES7WrReal (Ref, 'D', DBNr, Ab, Len, DoubleBuffer);
  if (Res == 0) // alles OK
  {       
    Res = ES7RdReal (Ref, 'D', DBNr, Ab, Len, DoubleBuffer);
    if (Res == 0)
    {
      for (i=0; i < Len;i++)
      {
        printf ("Float an Byte / float at byte %d = %f\n",i*4 + Ab,DoubleBuffer[i]);
        if (i % 11 == 10)
          GoOn ();
      }
      GoOn ();
    }    
             
  }
  if (Res != 0)  
  {  
    DoErr (Res);
  }
}

void
WrDWord (long Ref)
{
  WORD DBNr,
       Ab,
       i,      
       Len;
  DWORD Wert;
  long Res;
         
  printf ("Schreibe Doppelwort in DB writing double words of DB\n");
  printf ("\nSchreibe in DB mit Nummer: / writing to DB of no.:");
  scanf ("%u",&DBNr);

  printf ("\nStartbyte: / start byte: ");
  scanf ("%u",&Ab);                    
  
  printf ("\nAnzahl der Werte: / count of value: ");
  scanf ("%u",&Len);                    

  printf ("\nSchreibwert: / value to be written: ");
  scanf ("%ld",&Wert);                    
  
  for (i = 0; i < Len; i++)         
    DWordBuffer[i] = Wert;
                           
  Res = ES7WrDW (Ref, 'D', DBNr, Ab, Len, DWordBuffer);
  if (Res == 0) // alles OK
  {       
    Res = ES7RdDW (Ref, 'D', DBNr, Ab, Len, DWordBuffer);
    if (Res == 0)
    {
      for (i=0; i < Len; i++)
      {
        printf ("DWord an Byte / dword at byte%d = %08lx (hex) = %ld (dec)\n",i*4 + Ab, DWordBuffer[i], DWordBuffer[i]);
        if (i % 11 == 10)
          GoOn ();
      }
      GoOn ();
    }    
  }
  if (Res != 0)  
  {  
    DoErr (Res);
  }
}
/*------------------------------------------------------------*/

void
RdDWord (long Ref)
{
  WORD DBNr,
       Ab,
       i,      
       Len;
  long Res;
         
  printf ("Lese Doppelwort von DB / reading double word from DB\n");
  printf ("\nLese von DB mit Nummer:");
  scanf ("%u",&DBNr);

  printf ("\nStartbyte: / start byte: ");
  scanf ("%u",&Ab);                    
  
  printf ("\nAnzahl der Werte: / count of values: ");
  scanf ("%u",&Len);                    
  
  Res = ES7RdDW (Ref, 'D', DBNr, Ab, Len, DWordBuffer);
  if (Res == 0)
  {
    for (i=0; i < Len; i++)
    {
      printf ("DWord an Byte / dword at byte %d = %08lx (hex) = %ld (dec)\n",i*4 + Ab, DWordBuffer[i], DWordBuffer[i]);
      if (i % 11 == 10)
        GoOn ();
    }
    GoOn ();
  }    
  if (Res != 0)  
  {  
    DoErr (Res);
  }
}
/*------------------------------------------------------------*/

void 
TestForEver (long Ref) // Test Victory
{
  int ErrCnt = 0;
  int CntOKAY = 0;
  WORD DBNr, 
          i,      
        Len, AbWort;
  
  long Res;      
           
  
  for (;;)
  {
    Sleep (25);
    Res = ES7RdW (Ref, 'M', 0, 0, 100, WordBuffer);
    if (Res != 0)
    {
      printf ("\nDurchlaeufe OKAY: %d Fehleranzahl:%d,  Lese Merkerwort Fehlernummer:%d\n", CntOKAY, ErrCnt, Res);
      ++ErrCnt;
      if (Res < 0)
      { 
//        Sleep (1000);
        ES7Close (Ref);
        //Ref = ES7OpenEx (Com, MPIAdr, EigeneMPIAdr, Baud, SPSTyp, 0);  
        Ref = ES7OpenMPILan ("192.168.0.56", 5000, 5000, 5000, MPIAdr, EigeneMPIAdr, SPSTyp, 0);  
        printf ("ReOpen: Ref = %d\n", Ref);
      }
    }
    else
    {
       ++CntOKAY;
       printf ("Durchlaeufe OKAY: %d Fehleranzahl:%d\r", CntOKAY, ErrCnt);
    }
  }
}




int
main  (int ArgAnz, char **Args)
{     
  int i;
/*
  DWORD Com = COM1;
  WORD MPIAdr;
  DWORD Baud = 19200;   
  DWORD SPSTyp = 300;
*/
    
  long Ref;
  for (i = 1; i < ArgAnz; i++)
  {  
    if (stricmp (Args[i], "COM1") == 0)
      Com = COM1;
    if (stricmp (Args[i], "COM2") == 0)
      Com = COM2;
    if (stricmp (Args[i], "COM3") == 0)
      Com = COM3;

    if (stricmp (Args[i], "200") == 0)
    {  
      SPSTyp = 200;
      Baud = 9600;
    }
    
    if (stricmp (Args[i], "19") == 0)
      Baud = 19200;
    
    if (stricmp (Args[i], "38") == 0)
      Baud = 38400; 
    
    if (stricmp (Args[i], "57") == 0)
      Baud = 57600;
  }                     
  
  printf ("PC-S7-EASY-LINK Demo Version 1.03  COM%ld, Baudrate: %ld\n", Com +1, Baud);
  printf ("wollen Sie andere COM dann rufen sie : 'ESDEMO COMx' \n");
  printf ("if you want other COM please start: 'ES7DEMO COMx' \n");

  MPIAdr       = 2;
  EigeneMPIAdr = 0;
  
  printf ("SPS-MPI-Adr / PLC-MPI-Addr %u: \n", MPIAdr);
  scanf ("%u",&MPIAdr);            
  
  printf ("PC-MPI-Addr %u: \n", EigeneMPIAdr);
  scanf ("%u",&EigeneMPIAdr);            
  
  printf ("COM%ld wird geoeffnet / is opened.........\n", Com + 1);

  //Ref = ES7Open (Com, MPIAdr, EigeneMPIAdr, Baud, SPSTyp);
  
  Ref = ES7OpenEx (Com, MPIAdr, EigeneMPIAdr, Baud, SPSTyp, 0);  

  //Ref = ES7OpenMPILan ("192.168.0.56", 5000, 5000, 5000, MPIAdr, EigeneMPIAdr, SPSTyp, 0);  

   
  if (Ref >= 0)
  {       
    BOOL bDo = TRUE;
    
    //TestForEver (Ref);
    for (;bDo;)
    { 
      printf ("\n**************************************************************\n"
              "1 = lese Merker                 | read Flags\n"
              "2 = lese Eingang                | read input\n"
              "3 = schreibe Ausgang            | write output\n"
              "4 = lese DB                     | read DB\n"
              "5 = schreibe DB                 | write DB\n"
              "6 = erreichbare Teilnehmer      | available MPI-members\n"
              "7 = lese Timer                  | read Timer\n"
              "8 = schreibe Timer              | write Timer\n"
              "9 = lese Zaehler                | read Counter\n"
              "A = schreibe Zaehler            | write counter\n"
              "B = lese Merker Bit             | read bit of flag\n"
              "C = setze Merker Bit            | set bit of flag\n"
              "D = ruecksetze Merker Bit       | reset bit of flag\n"
              "E = lese Floatingpointwerte     | reading floating point values\n"
              "F = schreibe Floatingpointwerte | writing floating point values\n"
              "G = lese Doppelworte            | reading double words\n"
              "H = schreibe Doppelworte        | writing double words\n"

              "0 = Ende                        | exit\n"
              "    Bitte waehlen .....         | please select\n\n"
              );
      
      switch (i = GetKey ())
      {
        case '1':
          RdMB (Ref);
          break;
        
        case '2':
          RdEB (Ref);
          break;
        
        case '3':
          WrAB (Ref);
          break;
             
        case '4':
          RdDB (Ref);
          break;
               
        case '5':
          WrDB (Ref);
          break;

        case  '6':
          ShowTeiln (Ref);
          break;

        case '7':
          RdTimer (Ref);
          break;

        case '8':
          WrTimer (Ref);
          break;

        case '9':
          RdCounter (Ref);
          break;
     
        case 'A':
        case 'a':
          WrCounter (Ref);
          break;

        case 'B':
        case 'b':
          RdMBit (Ref);
          break;
       
        case 'C':
        case 'c':
          SetMBit (Ref, 1);
          break;

        case 'D':
        case 'd':
          SetMBit (Ref, 0);
          break;

        case 'E':
        case 'e':
          RdFloat (Ref);
          break;
      
        case 'F':
        case 'f':
          WrFloat (Ref);
          break;

        case 'G':
        case 'g':
          RdDWord (Ref);
          break;
      
        case 'H':
        case 'h':
          WrDWord (Ref);
          break;


        case '0':
          bDo = FALSE;
          break;

        case 'x':
          TestForEver (Ref);
      }
    }
  }
  else
  {
    printf ("Fehler / error 'ES7Open:' %ld\n", Ref);
    GoOn ();
  }
  return (1);
}
/*------------------------------------------------------------*/
