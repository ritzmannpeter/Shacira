/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [binimg.c]    Portable machine-independant binary format                 */
/*                                                                          */
/* Copyright (c) 1993 by Lars D\olle, Heike Manns                           */
/* ------------------------------------------------------------------------ */

#include "standard.h"
#include "symbols.h"

#include "glo_tab.h"
#include "pathes.h"
#include "hmap.h"
#include "otab.h"
#include "sink.h"

/*!!
  Summary

  [binimg] offers a set of functions to read and write binary files in a portable
  machine-independant format. Within the STYX-system they are used to make data structures
  persistent.

  non-reentrant API:

  For each supported data type exist a read and write function with the following signature.

  |   void put<TYPE>(<CTYPE>  x);
  |   void get<TYPE>(<CTYPE> &x);

  Source and target are implicit in these operations. The functions 'getBgn' and 'getEnd'
  open and close a source. To open and close a target one has to use the functions 'putBgn'
  and 'putEnd'. So it is not possible to read or write more than one file at a time.

  reentrant API:

  For each supported data type exist a read and write function with the following signature.

  |   void fput<TYPE>(BinImg_T img, <CTYPE>  x);
  |   void fget<TYPE>(BinImg_T img, <CTYPE> &x);

  The functions 'fgetBgn' and 'fgetEnd' open and close a source. To open and close a target 
  one has to use the functions 'fputBgn' and 'fputEnd'. So it is possible to read or write 
  more than one file at a time.

  Each binary file within the STYX-system starts with a header block. Creation and reading
  e.g. checking is done by the functions 'putHeader' and 'getHeader' respectively
  'fputHeader' and 'fgetHeader'.

  The binary files are protected against unauthorized reading and writing by an integrated 
  combined encryption and checking method. Further more they will be compressed.
*/

/*!!
  Files and EOF

  With the non-reentrant API it is not possible to read or write more than one file at a time.

  This module doesn't support an explicit EOF-predicate. It is the responsibility of the user
  to check for EOF. Reading behind EOF causes the program to abort with an error message.
*/

/*D 
  Dies ist kein Schikane, sondern eher eine Entlastung im Vergleich zur
  C-Konvention. In letzterer stellen die von 'fgetc' gelieferten Werte
  eine Vereinigung von 'byte' mit dem Sonderwert 'EOF' dar. Mithin wird
  dort nach jeder Leseoperation eine Fallunterscheidung erzwungen, die
  bei unserer Konvention entfaellt - es werden eben nur Datenbytes geliefert.

  Wenn das Dateiende erwartet wird, kann dies durch 'checkEOF' abgesichert
  werden. Dies geschieht automatisch beim Schliessen einer gelesenen Datei.
  (Siehe 'getEnd', weiter unten).
*/


/* ======================== type & macros & globals =========================== */

#define crypt_1       (52845)
#define crypt_2       (22719)

#define MAXBLKLEN     200
#define BLKEOF        (MAXBLKLEN+1)

#define CharSetSize   (1<<8)
#define MaxBitsLen    12
#define HtblSize      (1<<MaxBitsLen)
#define MaxEntries    (HtblSize-CharSetSize)

#define Closed        (0)
#define Open(MODE)    (1+(MODE))
#define Body(MODE)    (3+(MODE))

#define Get           0
#define Put           1

#define Version       2

#define HugeBufferLen ((size_t)(1L<<15))

#define CheckState(img,STATE) assert1((img)->state == (STATE),"state = %d\n",(img)->state)


/**/static void noIncEvent(float lvl);

ExternalType( BinImg_T ) /* Abstract binary image type */
{
  /* identification */
  FILE*    f;   /* file pointer: defined, if 'state != stateClosed' */
  c_string fid; /* binary image path                                */

  /* open & close */
  int state/*=Closed*/; /* state of put / get operation */

  /* header information */
  byte cMinor;   /* current minor version */
  byte cVersion; /* current file  version */

  /* reading */
  long   SrcFileLen; /* length of source file                       */
  long   SrcFileGet; /* number of bytes read                        */
  void   (*IncEvent)(float lvl)/*=noIncEvent*/; /* progress handler */

  /* simulated interface */
  c_bool someHugePut;    /* huge data ?   */
  long   BytesIn/*=0*/;  /* bytes read    */
  long   BytesOut/*=0*/; /* bytes written */

  /* bit I/O */
  unsigned long bit_buffer;    /* binary buffer, 4 byte == 32 bit         */
  int           bits_buffered; /* number of bits buffered in 'bit_buffer' */

  /* put & get */
  MAPTY    puttyp; /* needed by 'putReference' and 'getReference' */
  MAP(_,_) putmap; 
  ROW(_)   getmap;

  /* en/decryption */
  word   crypt_R; /* current en/decryption key */

  /* blocking & validation (1) */
  byte BlockLen /*=0*/;     /* number of bytes written to buffer */
  byte BlockRdr /*=0*/;     /* number of bytes read from buffer  */

  /* compression */
  short topEntry;             /* number of entries in the prefix table */
  short Log2_top;             /* = ceiling(log2(topEntry+CharSetSize)) */
  short Prev, Leng;           /* part of prefix and length             */
  struct
  {
    short prev; /* previous String OR! Character        */
    char  c;    /* appended character                   */
    short next; /* chain in the case of a hash conflict */
  } __FAR hentry[MaxEntries]; /* prefix table                          */
  short __FAR Htbl[HtblSize]; /* hash table. (-1) is a free slot.      */
  byte  __FAR res_buffer[MaxEntries]; /* buffer for 'unpkByt'          */

  /* blocking & validation (2) */
  byte BlockTxt[MAXBLKLEN]; /* temporary byte buffer             */
};

/* static context for non-reentrant interface functions */
static ConcreteImp(BinImg_T) cimg = 
{
  NULL,NULL,Closed,(byte)0,(byte)0,0,0,noIncEvent,
  C_False,0,0,0,0,NULL,NULL,NULL,(word)0,(byte)0,(byte)0,
  (short)0,(short)0,(short)0,(short)0
};
static BinImg_T pcimg = &cimg;


/* ============================== functions =================================== */

static void putbyte(BinImg_T img,byte x)
/* put byte 'x' to 'f' */
{
  fputc(x,img->f);
}

static void noIncEvent(float lvl)
/* noop */
{
}

BinImg_T BIN_getCurImage(void)
/* get current image */
{
  return pcimg;
}

void BIN_setIncEvent(void (*evt)(float lvl))
/* set the get-inc event */
{
  pcimg->IncEvent = evt;
}

void fBIN_setIncEvent(BinImg_T img,void (*evt)(float lvl))
/* set the get-inc event for binary image 'img' */
{
  BUG_NULL(img);
  img->IncEvent = evt;
}

static int getbyte(BinImg_T img,bool eof_ok)
/* get byte 'x' from 'f' */
{ int cc = fgetc(img->f);
  assert1(eof_ok || cc != EOF,"unexpected end of file '%s'",img->fid);
  if (cc != EOF)
  {
    img->SrcFileGet += 1;
    if ((img->SrcFileGet-1)*100/img->SrcFileLen != img->SrcFileGet*100/img->SrcFileLen)
      (*img->IncEvent)(img->SrcFileGet/(float)img->SrcFileLen);
  }
  return cc;
}

static void checkEOF(BinImg_T img)
/* validates 'EOF' reading */
{
  assert1(fgetc(img->f) == EOF,"data after logical end of file '%s'",img->fid);
}

/*D
  Verschluesselungmethode

  Zur Verschluesselung wird ein auf linearer Kongruenz basierendes Verfahren
  verwendete. Beachte, dass sich die Ver- und Entschluesslungsoperation
  subtil darin unterscheiden, dass immer das zuletzt "verschluesselte" Byte
  zur Ermittlung des neuen Schluessels verwendet wird.
*/

static byte Encrypt(BinImg_T img,byte plain)
/* encrypt a byte */
{
  byte cipher = (plain ^ (img->crypt_R >> 8));
  img->crypt_R = (cipher + img->crypt_R) * crypt_1 + crypt_2;
  return cipher;
}

static byte Decrypt(BinImg_T img,byte cipher)
/* decrypt a byte */
{
  byte plain = (cipher ^ (img->crypt_R >> 8));
  img->crypt_R = (cipher + img->crypt_R) * crypt_1 + crypt_2;
  return plain;
}

/*D
  Verschluesselung und Validierung

  Der Verschluesselungalgorithmus wird zugleich zur Validierung des
  Dateiinhalts, besonders auch ihrer unverschluesselten Teile verwendet.
  Unter dieser Konvention durchlaeuft der "gesamte" Dateiinhalt das
  Verschluesselungsverfahren. Falls unverschluesselte Ausgabe erfolgt,
  wird lediglich der Seiteneffekt der Verschluesselung, der nach jedem
  Byte einen neuen Schluessel erzeugt verwendet. Diese Schluessel koennen
  als Pruefbytes gelegentlich ausgegeben und beim Einlesen mit dem
  dann aktuellen Schluessel verglichen werden ('putCheck', 'getCheck').
*/

static void CryptInit(BinImg_T img)
/* initializes transcryption */
{
  img->crypt_R = 55665;
}

static void putPlain(BinImg_T img,byte plain)
{
  Encrypt(img,plain);
  putbyte(img,plain);
}

static int getPlain(BinImg_T img,bool eof_ok)
{ int plain = getbyte(img,eof_ok);
  if (plain == EOF) return EOF;
  Encrypt(img,(byte)plain); /* ! */
  return plain;
}

static void putCrypt(BinImg_T img,byte plain)
{
  putbyte(img,Encrypt(img,plain));
}

static int getCrypt(BinImg_T img,bool eof_ok)
{ int crypt = getbyte(img,eof_ok);
  if (crypt == EOF) return EOF;
  return Decrypt(img,(byte)crypt);
}

static void putCheck(BinImg_T img)
{
  putbyte(img,(byte)(img->crypt_R >> 8));
  putbyte(img,(byte)(img->crypt_R >> 0));
}

static void getCheck(BinImg_T img)
{
  assert1(getbyte(img,False) == ((img->crypt_R >> 8) & 0xff),
          "file '%s' corrupted",img->fid);
  assert1(getbyte(img,False) == ((img->crypt_R >> 0) & 0xff),
          "file '%s' corrupted",img->fid);
}

/*D
  Blockung und Validierung

  Um die Leseoperation abzusichern, ist es erforderlich, schon "vor" dem
  Lesen eines Bytes sicher sein zu koennen, dass diese korrekt ist. Im anderen
  Fall bricht ggfls. das Programm vor dem Lesen der Pruefbytes bereits
  mit einem anderen Fehler ab, was die eigentliche Ursache verschleiert.

  Der Binaertext wird daher beim Schreiben in "Bloecke" eingeteilt. Jeder
  Block wird am Anfang mit der Laenge seines Inhalts und am Ende mit Pruefbytes
  versehen. Beim Lesen wird jeweils ein ganzer Block in den Speicher geladen
  bis er auf seine Korrektheit hinsichtlich der Pruefbytes untersucht werden
  kann. Dies erfordert die Einrichtung eines Pufferungsmechanismus.

  Die maximale Blocklaenge betraegt 'MAXBLKLEN+8' Bytes. Kuerzere Bloecke
  sind moeglicht. Der Aufbau eines Blocks sieht im einzelnen so aus:

  |   1 Byte Blockl\ange
  |   N Bytes Text           -- maximal MAXBLKLEN
  |   2 Pr\ufbytes
*/

static void putBlock(BinImg_T img)
{ int i;
  putCrypt(img,img->BlockLen);
  for (i = 0; i < img->BlockLen; i++)
    putCrypt(img,img->BlockTxt[i]);
  putCheck(img);
  img->BlockLen = 0;
}

static void getBlock(BinImg_T img,bool eof_ok)
{ int n, i;
  img->BlockRdr = 0;
  n = getCrypt(img,eof_ok);
  if (n == EOF)
  {
    img->BlockLen = BLKEOF; return;
  }
  img->BlockLen = (byte)n;
  assert1(img->BlockLen <= MAXBLKLEN,"file '%s' corrupted",img->fid);
  for (i = 0; i < img->BlockLen; i++)
    img->BlockTxt[i] = getCrypt(img,False);
  getCheck(img);
}

static void BlockPutByte(BinImg_T img,byte x)
{
  if (img->BlockLen == MAXBLKLEN)
    putBlock(img);
  img->BlockTxt[img->BlockLen++] = x;
}

static int BlockGetByte(BinImg_T img,bool eof_ok)
{
  if (img->BlockRdr == img->BlockLen)
    getBlock(img,eof_ok);
  if (img->BlockLen == BLKEOF)
  {
    assert1(eof_ok,"unexpected end of file '%s'",img->fid);
    return EOF;
  }
  return img->BlockTxt[img->BlockRdr++];
}

/* ----------------------------- Kompression ------------------------------ */

/*D
  Datenkompression

  Der Inhalt der Datenseiten wird komprimiert. Ausser dass eine
  Speicherersparnis von ca. 50 Prozent ergibt, ist dies auch angezeigt,
  weil umgekehrt die Verschluesselung der Seiten, den unangenehmen
  Nebeneffekt hat, dass die Bibliothek nachtraeglich nicht mehr
  komprimiert werden kann, da sie, statistisch betrachtet, nach
  der Verschluesselung nur noch eine Kette gleichverteilter Bytes ist.
  Sie entlastet im uebrigen auch bei Binaerdateien den Programmieren etwa
  von Platzueberlegungen, so kann etwa ein 'long' mit recht verminderter
  Hemmung als 'bool' verwendet werden, wenn dies nur oft genug geschieht.

  Kompressionsverfahren

  Verwendet wird eine Variante der Lempel-Ziv-Welch Kompression.
  Sie besteht aus einer Tabelle, die als Eintraege Binaerstrings
  enthaelt. Am Anfang enthaelt diese Tabelle nur alle Bytes von 0
  bis 255 als Strings der Laenge 1.

  Vom zu komprimierenden Text wird dann der laengste Praefix, der
  in der Tabelle enthalten ist, gesucht. Dessen Nummer (Index)
  wird dann ausgegeben und dieser Praefix, verlaengert um das
  unmittelbar folgende Zeichen im Text als neuer String in die
  Tabelle eingetragen. Der Praefix wird dann vom Text entfernt
  und der Rest weiterverarbeitet, bis der Text vollstaendig
  komprimiert ist.

  Die Indizies werden als Zahlen mit einer variablen Anzahl an
  Bits ausgegeben. Diese Bitzahl ist die kleinste Zahl, die
  dem aktuellen Fuellungsgrad der Tabelle entspricht.
  Begonnen wird also mit 8 Bits, nach dem 1. Eintrag 9. Bit,
  nach dem 256. Eintrag 10. Bit, usw.

  Die Tabelle hat eine feste, hoechste Groesse von Eintraegen, die
  neu aufgenommen werden k÷nnen ('MaxEntries'). Falls mehr
  Eintraege aufgenommen werden sollen, wird die Tabelle
  wieder auf ihren Ausgangszustand (nur die einzelnen Bytes)
  zurueckgesetzt. Dies ist heuristisch darum angezeigt, da durch
  die Verlaengerung der Tabelle auch immer mehr Bits pro Eintrag
  ausgegeben werden muessen, obwohl (ggfls. schon viele Seiten im
  Text spaeter) inzwischen viele der alten Eintraege gar nicht mehr
  im laufenden Text auftauchen.

  Implementierung

  Das schnelle Auffinden des Praefix ist die Crux des Verfahrens.
  Hierzu wird eine Hash-Tabelle eingesetzt, deren Eintraege Paare
  der Form (Eintrag,Byte) sind. Dies ist nicht nur ein schnelles,
  sondern auch (gemessen an der Groesse) relativ platzsparendes
  Verfahren.

  Dekompression

  Die Dekompression laeuft im wesentlichen umgekehrt dazu. Wenn ein
  Index gelesen wird, wird dessen String aus der Tabelle gesucht,
  und als dekomprimierter Teil ausgegeben. Ferner bilden das erste
  Zeichen dieses Strings angehaengt an den zuletzt vorher ausgegebenen
  String einen neuen Eintrag fuer die Tabelle. Der einzige Kniff ist
  der Fall, dass ein Index auflaufen kann, der noch nicht bekannt ist,
  in diesem Fall ist der zuletzt ausgegebene String verlaengert um
  sein erstes Zeichen gemeint - wie man sich mit einiger Muehe dann
  doch ueberlegen kann. Die Tabelle muss natuerlich auch bei der
  Dekompression immer wieder auf ihren Anfangswert zurueckgesetzt
  werden, wenn sie voll ist. Die Kompression und Dekompression sauber
  zu synchronisieren, war speziell an dieser Stelle am kritischsten.
*/

/* ----------------------------- Kompression ------------------------------ */

static void initEntry(BinImg_T img)
/* ininitalizes 'topEntry' maintaining intergrity of 'Log2_top' */
{
  img->topEntry = 0; img->Log2_top = 8;
}

static void incEntry(BinImg_T img)
/* increments 'topEntry' maintaining intergrity of 'Log2_top' */
{
  img->topEntry += 1;
  if ((img->topEntry+CharSetSize) > (1 << img->Log2_top))
    img->Log2_top += 1;
}

static word HashPair(word prev, char c)
/* hash value needed as 'loc0' for the two following functions */
{
  return (word)((52845 * (prev + c) + 22719) & (HtblSize-1));
}

static short FindPair(BinImg_T img, word loc0, word prev, char c)
/* finds pair or returns (-1) if not found */
{ short loc;
  for(loc = img->Htbl[loc0];
      loc != -1 && !(img->hentry[loc].c == c && img->hentry[loc].prev == prev);
      loc = img->hentry[loc].next
     );
  return loc < 0 ? -1 : loc + (short)CharSetSize;
}

static void AddPair(BinImg_T img, word loc0, word prev, char c)
/* adds pair to table */
{
  assert0(img->topEntry < MaxEntries,"table overflow");
  img->hentry[img->topEntry].c    = c;
  img->hentry[img->topEntry].prev = prev;
  img->hentry[img->topEntry].next = img->Htbl[loc0];
  img->Htbl[loc0]                 = img->topEntry;
  incEntry(img);
}

static void initTable(BinImg_T img)
/* initalizes the hash table */
{ int i;
  for (i = 0; i < HtblSize; i++)
    img->Htbl[i] = -1;
  initEntry(img);
}

/* -- Simulated Interface -- */

static void sim_putByte(BinImg_T img,byte b)
/* */
{
  BlockPutByte(img,b);
  img->BytesOut += 1;
}

static int sim_getByte(BinImg_T img)
{
  int res = BlockGetByte(img,True);
  img->BytesOut += (res != EOF);
  return res;
}

/* --------------------------------- Bit I/O ------------------------------ */

static void initBits(BinImg_T img)
/* clear bit buffer */
{
  img->bits_buffered = 0;
}

static void putBits(BinImg_T img,word bits, int len)
/* put 'len' 'bits' */
{
  img->bit_buffer = (img->bit_buffer << len) | bits;
  for (img->bits_buffered += len; img->bits_buffered > 7; img->bits_buffered -= 8)
    sim_putByte(img,(byte)(img->bit_buffer >> (img->bits_buffered - 8)));
}

static void flushBits(BinImg_T img)
/* flushes bits remaining in buffer */
{
  if (img->bits_buffered > 0)
    sim_putByte(img,(byte)(img->bit_buffer << (8 - img->bits_buffered)));
}

static int getBits(BinImg_T img,int len)
/* get 'len' bits */
{ /* This ist tricky! */
  for(img->bits_buffered -= len; img->bits_buffered < 0; img->bits_buffered += 8)
  { int tmp = sim_getByte(img); if (tmp == EOF) return -1;
    img->bit_buffer = (img->bit_buffer << 8) | tmp;
  }
  return (img->bit_buffer >> img->bits_buffered) & ((1<<len)-1);
}

static void packBgn(BinImg_T img)
/* prepare for packing */
{
  img->BytesIn = 0; img->BytesOut = 0; 
  initTable(img); initBits(img); img->Leng = 0;
}

static void packByt(BinImg_T img,byte c)
/* pack one byte */
{
  img->BytesIn += 1;
  if (img->Leng == 0)                       /* Das erstes Zeichen \uberhaupt ...  */
  {
    img->Leng = 1; img->Prev = c;           /* ... beginnt den ersten Pr\afix.    */
  }
  else                                      /* Alle weiteren Zeichen:             */
  { word  loc0 = HashPair(img->Prev,c);     /* Suche String in Tabelle ...        */
    short temp = FindPair(img,loc0,img->Prev,c);
    if (temp < 0)                           /* Wenn nicht vorhanden, dann ist ... */
    {                                       /* daf\ur aber der Pr\afix gefunden.  */
      putBits(img,img->Prev,img->Log2_top); /* Dessen Index ausgeben              */
      if (img->topEntry < MaxEntries)       /* ... und ...                        */
        AddPair(img,loc0,img->Prev,c);      /* (Pr\afix,c) hinzuf\ugen            */
      else                                  /* ... oder ...                       */
        initTable(img);                     /* Tabelle leeren, wenn voll.         */
      img->Leng = 1; img->Prev = c;         /* Hier beginnt neuen Pr\afix.        */
    }
    else
    {
      img->Leng += 1; img->Prev  = temp;    /* Eintrag bekannt, weiter im Text    */
    }
  }
}

static void packEnd(BinImg_T img)
/* done with packing, flushes all buffered values */
{
  if (img->Leng > 0)
    putBits(img,img->Prev,img->Log2_top);
  flushBits(img);
  if (!img->someHugePut && img->BytesIn > 1024 && 
      img->BytesOut > 3*img->BytesIn/4)
  {
    fprintf(STDERR,"\n");
    fprintf(STDERR,"[Packer Quality Monitor]\n");
    fprintf(STDERR,"!\n");
    fprintf(STDERR,"! The packratio was less than 75%%.\n");
    fprintf(STDERR,"!\n");
    fprintf(STDERR,"! file: %s\n",img->fid);
    fprintf(STDERR,"! in  : %8ld : 100.00 %%\n",img->BytesIn);
    fprintf(STDERR,"! out : %8ld : %3ld.%02ld %%\n",
                   img->BytesOut,
                   100*img->BytesOut/img->BytesIn,
                   (10000*img->BytesOut/img->BytesIn)%100);
    fprintf(STDERR,"\n");
  }
}

static void unpkBgn(BinImg_T img)
/* prepare for unpacking */
{
  img->BytesIn = 0; img->BytesOut = 0; 
  initEntry(img); initBits(img); img->Leng = 0;
}

static int unpkByt(BinImg_T img)
/* get one unpacked byte or EOF */
{ int code0,code;
  img->BytesIn += 1;
  if (img->Leng > 0)                     /* Obwohl die Dekomprimierung         */
    return img->res_buffer[--img->Leng]; /* eigentlich viel einfacher als die  */
  code0 = getBits(img,img->Log2_top);    /* Komprimierung ist (es mu\s weder   */
  if (code0 == EOF)                      /* gesucht noch gehasht werden), hat  */
    return EOF;                          /* auch sie so ihre Haken und \Osen.  */
  if (img->topEntry < MaxEntries)
    img->hentry[img->topEntry].prev = code0;
  for(code = code0; code >= CharSetSize; code = img->hentry[code-CharSetSize].prev)
    img->res_buffer[img->Leng++] = img->hentry[code-CharSetSize].c;
  if (img->topEntry > 0)
  {
    img->hentry[img->topEntry-1].c = code;
    if (code0 == img->topEntry-1+CharSetSize)
      img->res_buffer[0] = code;
  }
  if (img->topEntry == MaxEntries)
    initEntry(img);
  else
    incEntry(img);
  return code;
}

static void unpkEnd(void)
/* dummy */
{
}

static void resync(BinImg_T img)
{
  initEntry(img); initBits(img); img->Leng = 0;
}

static void flushAllBuffers(BinImg_T img)
{
  if (img->Leng > 0) putBits(img,img->Prev,img->Log2_top);
  flushBits(img); 
  if (img->BlockLen > 0) putBlock(img);
  initTable(img); initBits(img); img->Leng = 0;
}

/*I----------------------------- Open & Close --------------------------------- */

/*D
  States

  To support a correct usage of this modul an explicit state variable was 
  introduced and checked before each operation. We distinguish 5 states:

  - closed
  - opened for reading or writing
  - ready to read or write data
*/

static c_bool putBgn_aux
              (
                BinImg_T img, 
                string EnvVar, string FileName, string Ext,
                c_bool force
              )
{
  CheckState(img,Closed);
  img->fid = MkPath(EnvVar,FileName,Ext,'e');
  if( force )
    img->f = OpnFile(img->fid,"wb");
  else
  {
    img->f = TryOpnFile(img->fid,"wb");
    if( img->f == (FILE*)NULL ) 
    {
      FreeMem(img->fid); img->fid = (c_string)NULL;
      return C_False;
    }
  }
  img->state  = Open(Put);
  srand((int)time(NULL)); /* time dependent ("true") random */
  packBgn(img);
  img->puttyp = MAP_newTyp(primCopy,primFree,primEqual,primHash,primCopy,primFree);
  img->putmap = MAP_newMap(img->puttyp);
  img->someHugePut = False;
  return C_True;
}

void putBgn(string EnvVar, string FileName, string Ext)
/* open [$'EnvVar'/'FileName''Ext'] to put binary image */
{
  putBgn_aux(pcimg,EnvVar,FileName,Ext,C_True);
}

BinImg_T fputBgn(string EnvVar, string FileName, string Ext)
/* open [$'EnvVar'/'FileName''Ext'] to put binary image (reentrant) */
{ BinImg_T img = New(BinImg_T);
  img->state = Closed;
  putBgn_aux(img,EnvVar,FileName,Ext,C_True);
  return img;
}

BinImg_T TryfputBgn(string EnvVar, string FileName, string Ext)
/* tries to open [$'EnvVar'/'FileName''Ext'] to put binary image (reentrant);
   returns NULL in the case of an invalid path
*/
{ BinImg_T img = New(BinImg_T);
  img->state = Closed;
  if( ! putBgn_aux(img,EnvVar,FileName,Ext,C_False) )
  {
    FreeMem(img); img = (BinImg_T)NULL;
  }
  return img;
}

static c_bool getBgn_aux
              (
                BinImg_T img, 
                string EnvVar, string FileName, string Ext,
                c_bool force
              )
{ 
  CheckState(img,Closed);
  img->fid        = MkPath(EnvVar,FileName,Ext,'p');
  img->SrcFileLen = Path_FileSize(img->fid);
  img->SrcFileGet = 0;
  img->f          = OpnFile(img->fid,"rb");
  if( force )
    img->f = OpnFile(img->fid,"rb");
  else
  {
    img->f = TryOpnFile(img->fid,"rb");
    if( img->f == (FILE*)NULL ) 
    {
      FreeMem(img->fid); img->fid = (c_string)NULL;
      return C_False;
    }
  }
  img->state      = Open(Get);
  (*img->IncEvent)((float)0);
  unpkBgn(img);
  img->getmap = OT_CREATE_ADT(_);
  return C_True;
}

void getBgn(string EnvVar, string FileName, string Ext)
/* open [$'EnvVar'/'FileName''Ext'] to get binary image */
{ 
  getBgn_aux(pcimg,EnvVar,FileName,Ext,C_True);
}

BinImg_T fgetBgn(string EnvVar, string FileName, string Ext)
/* open [$'EnvVar'/'FileName''Ext'] to get binary image (reentrant) */
{ BinImg_T img = New(BinImg_T);
  img->state    = Closed;
  img->IncEvent = noIncEvent;
  getBgn_aux(img,EnvVar,FileName,Ext,C_True);
  return img;
}

BinImg_T TryfgetBgn(string EnvVar, string FileName, string Ext)
/* tries to open [$'EnvVar'/'FileName''Ext'] to get binary image (reentrant);
   returns NULL in the case of an invalid path
*/
{ BinImg_T img = New(BinImg_T);
  img->state    = Closed;
  img->IncEvent = noIncEvent;
  if( ! getBgn_aux(img,EnvVar,FileName,Ext,C_False) )
  {
    FreeMem(img); img = (BinImg_T)NULL;
  }
  return img;
}

static void putEnd_aux(BinImg_T img)
{
  CheckState(img,Body(Put));
  packEnd(img);
  if (img->BlockLen > 0)
    putBlock(img);
  fclose(img->f);
  img->state = Closed;
  if( img->fid != (c_string)NULL ) 
  {
    FreeMem(img->fid); img->fid = (c_string)NULL;
  }
  MAP_freeMap(img->putmap);
  MAP_freeTyp(img->puttyp);
}

void putEnd(void)
/* completes binary puting */
{
  putEnd_aux(pcimg);
}

void fputEnd(BinImg_T img)
/* completes puting to binary image 'img';
   frees 'img' (reentrant) */
{
  if( img != (BinImg_T)NULL )
  {
    putEnd_aux(img); FreeMem(img);
  }
}

static void getEnd_aux(BinImg_T img)
{
  CheckState(img,Body(Get));
  img->IncEvent = noIncEvent;
  unpkEnd();
  assert1
  (
    (img->BlockLen == BLKEOF || 
     img->BlockLen == img->BlockRdr) && fgetc(img->f) == EOF,
    "text after logical end of file '%s'",img->fid
  );
  fclose(img->f);
  img->state = Closed;
  FreeMem(img->fid);
  OT_DEL_T(img->getmap);
}

void getEnd(void)
/* completes binary geting */
{
  getEnd_aux(pcimg);
}

void fgetEnd(BinImg_T img)
/* completes geting from binary image 'img';
   frees 'img' (reentrant) */
{
  if( img != (BinImg_T)NULL )
  {
    getEnd_aux(img); FreeMem(img);
  }
}

/*I-------------------------------- Header ------------------------------------------ */

/*!!
  There are a lot of reasons to save some informations at the beginning of such a file.

  Beside a short text describing the content of the file, the user want to be sure that
  the file has the expected format. Following an old tradition this will be done by a 
  'Magic'.

  To handle format changes of binary files we introduce a version. The version consists
  of two numbers ('Major', 'Minor'). Binary formats with different major-numbers are
  treated as incompatible. Binary formats with different minor-numbers are treated as
  upward compatible.

  Furthermore this module has an internal version number to track changes of the internal
  format.

  Contrary to the external representation the title will be be saved as null-terminated
  string.

  'getHeader' respectively 'fgetHeader' checks these informations and aborts the operation 
  in the case of an error. During the read or write process the current minor-version is 
  accessable via the function 'MinorVersion' respectively 'fMinorVersion'.
*/

static void putHeader_aux
            (
              BinImg_T img, string Title, string Magic, byte Major, byte Minor
            )
{ int i;
  CheckState(img,Open(Put));
  CryptInit(img);
  while(*Title) putPlain(img,*Title++); putPlain(img,0);
  for (i = 0; i < 3; i++) putPlain(img,(byte)rand());
  putCheck(img);
  img->BlockLen = 0; img->BlockRdr = 0; /* init blocking */
  while(*Magic ) BlockPutByte(img,*Magic++); BlockPutByte(img,0);
  BlockPutByte(img,Major);
  BlockPutByte(img,Minor);
  BlockPutByte(img,Version);
  putBlock(img);
  img->cMinor = Minor;
  img->state = Body(Put);
}

void putHeader(string Title, string Magic, byte Major, byte Minor)
/* put header */
{ 
  putHeader_aux(pcimg,Title,Magic,Major,Minor);
}

void fputHeader
     (
       BinImg_T img, string Title, string Magic, byte Major, byte Minor
     )
/* put header to binary image 'img' (reentrant) */
{ 
  BUG_NULL(img);
  putHeader_aux(img,Title,Magic,Major,Minor);
}

static void getHeaderInfo_aux
            (
              BinImg_T img, string *Com, string *Mag, 
              byte *Ma, byte *Mi, byte *Bv
            )
{ int i; byte cc; Sink tmp;
  CheckState(img,Open(Get));
  CryptInit(img);
  tmp = Sink_open();
  while( (cc = getPlain(img,False)), cc != 0)
    Sink_putc(tmp,cc);
  *Com = Sink_close(tmp);
  for (i = 0; i < 3; i++) getPlain(img,False);
  getCheck(img);
  img->BlockLen = 0; img->BlockRdr = 0; /* init blocking */
  tmp = Sink_open();
  while( (cc = BlockGetByte(img,False)), cc != 0)
    Sink_putc(tmp,cc);
  *Mag = Sink_close(tmp);
  *Ma  = BlockGetByte(img,False);
  *Mi  = BlockGetByte(img,False);
  img->cVersion = BlockGetByte(img,False);
  *Bv  = img->cVersion;
  assert1(img->cVersion == Version,
          "incompatible binary format of file '%s'",img->fid);
  assert1(img->BlockLen == img->BlockRdr,"file '%s' corrupted",img->fid);
  img->state = Body(Get);
}

void getHeaderInfo(string *Com, string *Mag, byte *Ma, byte *Mi, byte *Bv)
/* get header information ( title,magic,major,minor,version ) */
{ 
  getHeaderInfo_aux(pcimg,Com,Mag,Ma,Mi,Bv);
}

void fgetHeaderInfo
     (
       BinImg_T img, string *Com, string *Mag, 
       byte *Ma, byte *Mi, byte *Bv
     )
/* get header information ( title,magic,major,minor,version ) 
   from binary image 'img' (reentrant) */
{ 
  BUG_NULL(img);
  getHeaderInfo_aux(img,Com,Mag,Ma,Mi,Bv);
}

static void getHeader_aux(BinImg_T img, string Magic, byte Major, byte Minor)
{ string Tit, Mag; byte Ma, Mi, Bv;
  getHeaderInfo_aux(img,&Tit, &Mag, &Ma, &Mi, &Bv);
  assert1(strcmp(Magic,Mag)==0,"wrong type of file '%s'",img->fid);
  assert1(Major == Ma,"incompatible major version of file '%s'",img->fid);
  assert1(Minor <= Mi,"incompatible minor version of file '%s'",img->fid);
  img->cMinor = Mi; FreeMem(Tit); FreeMem(Mag);
}

void getHeader(string Magic, byte Major, byte Minor)
/* validates header */
{ 
  getHeader_aux(pcimg,Magic,Major,Minor);
}

void fgetHeader(BinImg_T img, string Magic, byte Major, byte Minor)
/* validates header of binary image 'img' (reentrant) */
{ 
  BUG_NULL(img);
  getHeader_aux(img,Magic,Major,Minor);
}

static void getHeaderTitle_aux
            (
              BinImg_T img, string Magic, 
              byte Major, byte Minor, string* Title
            )
{ string Mag; byte Ma, Mi, Bv;
  getHeaderInfo_aux(img,Title, &Mag, &Ma, &Mi, &Bv);
  assert1(strcmp(Magic,Mag)==0,"wrong type of file '%s'",img->fid);
  assert1(Major == Ma,"incompatible major version of file '%s'",img->fid);
  assert1(Minor <= Mi,"incompatible minor version of file '%s'",img->fid);
  img->cMinor = Mi; FreeMem(Mag);
}

void getHeaderTitle(string Magic, byte Major, byte Minor, string* Title)
/* validates header, returns title */
{ 
  getHeaderTitle_aux(pcimg,Magic,Major,Minor,Title);
}

void fgetHeaderTitle
     (
       BinImg_T img, string Magic, byte Major, byte Minor, string* Title
     )
/* validates header, returns title of binary image 'img' (reentrant) */
{ 
  BUG_NULL(img);
  getHeaderTitle_aux(img,Magic,Major,Minor,Title);
}

short MinorVersion(void)
/* 'Minor' of the file */
{
  return pcimg->cMinor;
}

short fMinorVersion(BinImg_T img)
/* 'Minor' of the file 'img' (reentrant) */
{
  BUG_NULL(img);
  return img->cMinor;
}

/*I============================= Data types =============================== */

/*!!
  Actually the following data types are supported.

  | TYPE      | CTYPE                  |
  +-----------+------------------------+----------------------------
  | Byte      | unsigned char          |
  | Word      | unsigned short int     |   Intrinsic C-data types
  | Long      | signed long int        |
  | ULong     | unsigned long int      |
  | Int64     | signed long long int   | if supported type
  | UInt64    | unsigned long long int | if supported type
  +-----------+------------------------+----------------------------
  | String    | (char *)               |   Strings
  | Binary    | c_bstring              |   binary Strings
  | Symbol    | symbol                 |   Symbols
  | Function  | (? (*)())              |   Functions
  | Abstract  | (?)                    |   "Objects"
  | StdCPtr   | (?*)                   |   References
*/

/*I----------------------------- Plain values ----------------------------- */

void putByte(byte v)
/* put 'v' to file */
{
  CheckState(pcimg,Body(Put));
  packByt(pcimg,v);
}

void fputByte(BinImg_T img, byte v)
/* put 'v' to file 'img' (reentrant) */
{
  BUG_NULL(img);
  CheckState(img,Body(Put));
  packByt(img,v);
}

void getByte(byte *v)
/* get 'v' from file */
{ int val;
  CheckState(pcimg,Body(Get));
  val = unpkByt(pcimg);
  assert1(val != EOF,"unexpected end of file '%s'",pcimg->fid);
  *v = (byte)val;
}

void fgetByte(BinImg_T img, byte *v)
/* get 'v' from file 'img' (reentrant) */
{ int val;
  BUG_NULL(img);
  CheckState(img,Body(Get));
  val = unpkByt(img);
  assert1(val != EOF,"unexpected end of file '%s'",img->fid);
  *v = (byte)val;
}

int getByte_or_EOF(void)
/* get byte or EOF from file */
{ CheckState(pcimg,Body(Get)); return unpkByt(pcimg);
}

int fgetByte_or_EOF(BinImg_T img)
/* get byte or EOF from file 'img' (reentrant) */
{ 
  BUG_NULL(img);
  CheckState(img,Body(Get)); return unpkByt(img);
}

void putWord(short v)
/* put 'v' to file; msb first */
{
  putByte((byte)(v >> 8));
  putByte((byte)(v >> 0));
}

void fputWord(BinImg_T img, short v)
/* put 'v' to file 'img'; msb first (reentrant) */
{
  fputByte(img,(byte)(v >> 8));
  fputByte(img,(byte)(v >> 0));
}

void getWord(short *v)
/* get 'v' from file; msb first */
{ byte msb,lsb;
  getByte(&msb);
  getByte(&lsb);
  *v = ((short)msb << 8) | lsb;
}

void fgetWord(BinImg_T img, short *v)
/* get 'v' from file 'img'; msb first (reentrant) */
{ byte msb,lsb;
  fgetByte(img,&msb);
  fgetByte(img,&lsb);
  *v = ((short)msb << 8) | lsb;
}

void putLong(long v)
/* put 'v' ( <= 32 Bit ) to file; msw first */
{
  putWord((short)(v >> 16));
  putWord((short)(v >>  0));
}

void fputLong(BinImg_T img, long v)
/* put 'v' ( <= 32 Bit ) to file 'img'; msw first (reentrant) */
{
  fputWord(img,(short)(v >> 16));
  fputWord(img,(short)(v >>  0));
}

void getLong(long *v)
/* get 'v' from file; msw first */
{ word msw,lsw;
  getWord((short *)&msw);
  getWord((short *)&lsw);
  *v = ((long)msw << 16) | lsw;
}

void fgetLong(BinImg_T img, long *v)
/* get 'v' from file 'img'; msw first (reentrant) */
{ word msw,lsw;
  fgetWord(img,(short *)&msw);
  fgetWord(img,(short *)&lsw);
  *v = ((long)msw << 16) | lsw;
}

void putULong(unsigned long v)
/* put 'v' ( <= 32 Bit ) to file; msw first */
{ 
  putWord((short)(v >> 16));
  putWord((short)(v >>  0));
}

void fputULong(BinImg_T img, unsigned long v)
/* put 'v' ( <= 32 Bit ) to file 'img'; msw first (reentrant) */
{ 
  fputWord(img,(short)(v >> 16));
  fputWord(img,(short)(v >>  0));
}

void getULong(unsigned long *v)
/* get 'v' from file; msw first */
{ word msw,lsw;
  getWord((short *)&msw);
  getWord((short *)&lsw);
  *v = ((unsigned long)msw << 16) | lsw;
}

void fgetULong(BinImg_T img, unsigned long *v)
/* get 'v' from file 'img'; msw first (reentrant) */
{ word msw,lsw;
  fgetWord(img,(short *)&msw);
  fgetWord(img,(short *)&lsw);
  *v = ((unsigned long)msw << 16) | lsw;
}

void putInt(int v)
/* put 'v' ( <= 16 Bit ) to file */
{
  assert1( ( ((long) v) & 0xffff0000L ) == 0          ||
           ( ((long) v) & 0xffff0000L ) == 0xffff0000L,
          "'%d' needs more than 2 bytes for representation (use 'putLong')",v);
  putWord((short)v);
}

void fputInt(BinImg_T img, int v)
/* put 'v' ( <= 16 Bit ) to file 'img' (reentrant) */
{
  assert1( ( ((long) v) & 0xffff0000L ) == 0          ||
           ( ((long) v) & 0xffff0000L ) == 0xffff0000L,
          "'%d' needs more than 2 bytes for representation (use 'putLong')",v);
  fputWord(img,(short)v);
}

void getInt(int* v)
/* get 'v' from file */
{ short v0;
  getWord(&v0);
  *v = v0;
}

void fgetInt(BinImg_T img, int* v)
/* get 'v' from file 'img' (reentrant) */
{ short v0;
  fgetWord(img,&v0);
  *v = v0;
}

/*DOC_INTERFACE*/
#ifdef STYX_CONFIG_TINT64

void putInt64(c_int64 v)
/* put 'v' ( <= 64 Bit ) to file; msl first */
{
  putLong((long)(v >> 32));
  putLong((long)(v >>  0));
}

void fputInt64(BinImg_T img, c_int64 v)
/* put 'v' ( <= 64 Bit ) to file 'img'; msl first (reentrant) */
{
  fputLong(img,(long)(v >> 32));
  fputLong(img,(long)(v >>  0));
}

void getInt64(c_int64 *v)
/* get 'v' from file; msl first */
{ long msl,lsl;
  getLong((long *)&msl);
  getLong((long *)&lsl);
  *v = ((c_int64)msl << 32) | lsl;
}

void fgetInt64(BinImg_T img, c_int64 *v)
/* get 'v' from file 'img'; msl first (reentrant) */
{ long msl,lsl;
  fgetLong(img,(long *)&msl);
  fgetLong(img,(long *)&lsl);
  *v = ((c_int64)msl << 32) | lsl;
}

void putUInt64(c_uint64 v)
/* put 'v' ( <= 64 Bit ) to file; msl first */
{ 
  putULong((unsigned long)(v >> 32));
  putULong((unsigned long)(v >>  0));
}

void fputUInt64(BinImg_T img, c_uint64 v)
/* put 'v' ( <= 64 Bit ) to file 'img'; msl first (reentrant) */
{ 
  fputULong(img,(unsigned long)(v >> 32));
  fputULong(img,(unsigned long)(v >>  0));
}

void getUInt64(c_uint64 *v)
/* get 'v' from file; msl first */
{ unsigned long msl,lsl;
  getULong((unsigned long *)&msl);
  getULong((unsigned long *)&lsl);
  *v = ((c_uint64)msl << 32) | lsl;
}

void fgetUInt64(BinImg_T img, c_uint64 *v)
/* get 'v' from file 'img'; msl first (reentrant) */
{ unsigned long msl,lsl;
  fgetULong(img,(unsigned long *)&msl);
  fgetULong(img,(unsigned long *)&lsl);
  *v = ((c_uint64)msl << 32) | lsl;
}

/*DOC_INTERFACE*/
#endif

void putString(string v)
/* put 'v' to file; length byte first */
{
  putLong(strlen(v));
  for(; *v; v++)
    putByte(*v);
}

void fputString(BinImg_T img, string v)
/* put 'v' to file 'img'; length byte first (reentrant) */
{
  fputLong(img,strlen(v));
  for(; *v; v++)
    fputByte(img,*v);
}

void getString(string *v)
/* get 'v' from file; length first; allocs memory */
{ long len,i;
  getLong(&len);
  *v = (string) NewMem((len+1) * sizeof(char));
  for(i = 0; i < len; i++)
    getByte((byte*)&(*v)[i]);
  (*v)[len] = '\0';
}

void fgetString(BinImg_T img, string *v)
/* get 'v' from file 'img'; length first; allocs memory (reentrant) */
{ long len,i;
  fgetLong(img,&len);
  *v = (string) NewMem((len+1) * sizeof(char));
  for(i = 0; i < len; i++)
    fgetByte(img,(byte*)&(*v)[i]);
  (*v)[len] = '\0';
}

void putBString(c_bstring v)
/* put 'v' to file */
{ long len, i;
  memcpy(&len,v,sizeof(long));
  putLong(len);
  len += sizeof(long);
  for(i = sizeof(long); i < len; i++)
    putByte(v[i]);
}

void fputBString(BinImg_T img, c_bstring v)
/* put 'v' to file 'img' (reentrant) */
{ long len, i;
  memcpy(&len,v,sizeof(long));
  fputLong(img,len);
  len += sizeof(long);
  for(i = sizeof(long); i < len; i++)
    fputByte(img,v[i]);
}

void getBString(c_bstring *v)
/* get 'v' from file; allocs memory */
{ long len,i;
  getLong(&len); len += sizeof(long);
  *v = (c_bstring) NewMem(len * sizeof(char));
  memcpy(*v,&len,sizeof(long));
  for(i = sizeof(long); i < len; i++)
    getByte((byte*)&(*v)[i]);
}

void fgetBString(BinImg_T img, c_bstring *v)
/* get 'v' from file 'img'; allocs memory (reentrant) */
{ long len,i;
  fgetLong(img,&len); len += sizeof(long);
  *v = (c_bstring) NewMem(len * sizeof(char));
  memcpy(*v,&len,sizeof(long));
  for(i = sizeof(long); i < len; i++)
    fgetByte(img,(byte*)&(*v)[i]);
}

/*I----------------------------- Huge binaries ------------------------------- */

/*!
  To save and load large binary data blocks the following functions can be used.
*/

static void putHuge_aux(BinImg_T img, HugeCPtr v, long len)
{ byte *       buf  = (byte*)NewMem(HugeBufferLen);
  byte __HUGE* himg = (byte __HUGE*)v;
  long         iln;
  fputLong(img,len);
  flushAllBuffers(img); /* flush buffered data */
  img->BytesIn  += len;
  img->BytesOut += len;
  img->someHugePut = True;
  for(iln = len; iln >= HugeBufferLen; iln -= HugeBufferLen)
  { size_t i;
    for (i = 0; i < HugeBufferLen; i++)
      buf[i] = Encrypt(img,*himg++);
    fwrite(buf,HugeBufferLen,1,img->f);
  }
  if (iln > 0)
  { size_t i;
    for (i = 0; i < iln; i++)
      buf[i] = Encrypt(img,*himg++);
    fwrite(buf,(size_t)iln,1,img->f);
  }
  FreeMem(buf);
  putCheck(img);
}

void putHuge(HugeCPtr v, long len)
/* put 'len' bytes to file */
{ 
  putHuge_aux(pcimg,v,len);
}

void fputHuge(BinImg_T img, HugeCPtr v, long len)
/* put 'len' bytes to file 'img' (reentrant) */
{ 
  putHuge_aux(img,v,len);
}

static void getHuge_aux(BinImg_T img, HugeCPtr *v, long *len)
{ byte *       buf = (byte*)NewMem(HugeBufferLen);
  byte __HUGE* himg;
  long         iln;
  fgetLong(img,len);
  resync(img);
  img->BytesIn  += *len;
  img->BytesOut += *len;
  *v   = NewHMem(*len);
  himg = (byte __HUGE*)*v;
  for(iln = *len; iln >= HugeBufferLen; iln -= HugeBufferLen)
  { size_t i;
    fread(buf,HugeBufferLen,1,img->f);
    for (i = 0; i < HugeBufferLen; i++)
      (*himg++) = Decrypt(img,buf[i]);
  }
  if (iln > 0)
  { size_t i;
    fread(buf,(size_t)iln,1,img->f);
    for (i = 0; i < iln; i++)
      (*himg++) = Decrypt(img,buf[i]);
  }
  FreeMem(buf);
  getCheck(img);
}

void getHuge(HugeCPtr *v, long *len)
/* get 'len' bytes from file */
{ 
  getHuge_aux(pcimg,v,len);
}

void fgetHuge(BinImg_T img, HugeCPtr *v, long *len)
/* get 'len' bytes from file 'img' (reentrant) */
{ 
  getHuge_aux(img,v,len);
}

/*I-------------------------------- Symbols ------------------------------- */

/*!
  Symbols are externally represented as ( binary ) strings. 
  <br>The leading byte specifies the symbol type.
*/

void putSymbol(symbol v)
/* put a symbol to file */
{ bool binsym = binarySymbol(v);
  putByte((byte)binsym);
  if( !binsym )
    putString(symbolToString(v));
  else
    putBString(symbolToBString(v));
}

void fputSymbol(BinImg_T img, symbol v)
/* put a symbol to file */
{ bool binsym = binarySymbol(v);
  fputByte(img,(byte)binsym);
  if( !binsym )
    fputString(img,symbolToString(v));
  else
    fputBString(img,symbolToBString(v));
}

static void getSymbol_aux(BinImg_T img, symbol *v)
{ byte binsym;
  fgetByte(img,&binsym);
  if( !binsym )
  { string s;
    fgetString(img,&s);
    *v = stringToSymbol(s);
    FreeMem(s);
  }
  else
  { c_bstring s;
    fgetBString(img,&s);
    *v = bstringToSymbol(s);
    FreeMem(s);
  }
}

void getSymbol(symbol *v)
/* get a symbol from file */
{ 
  getSymbol_aux(pcimg,v);
}

void fgetSymbol(BinImg_T img, symbol *v)
/* get a symbol from file 'img' (reentrant) */
{ 
  getSymbol_aux(img,v);
}

/*I------------------------------- Functions ------------------------------ */

/*!
   For technical reasons the functions must be defined in a global table.<br>
   They are externally represented by a symbolic name representing the key
   to the function table entry. ( see also <a href="glo_tab.htm">[glo_tab]</a> )
*/

void putFunction(StdCPtr v)
/* put a function to file
   raises error if 'v' not 'Glo'bally defined 
*/
{
  putSymbol(Glo_key(v));
}

void fputFunction(BinImg_T img, StdCPtr v)
/* put a function to file 'img' (reentrant)
   raises error if 'v' not 'Glo'bally defined 
*/
{
  fputSymbol(img,Glo_key(v));
}

void getFunction(StdCPtr *v)
/* get a function from file
   raises error if 's' not 'Glo'bally defined 
*/
{ symbol s;
  getSymbol(&s);
  *v = Glo_val(StdCPtr,s);
}

void fgetFunction(BinImg_T img, StdCPtr *v)
/* get a function from file 'img' (reentrant)
   raises error if 's' not 'Glo'bally defined 
*/
{ symbol s;
  fgetSymbol(img,&s);
  *v = Glo_val(StdCPtr,s);
}

/*I---------------------------- Abstract types ---------------------------- */

/*!!
   In the case of a generic data type ( e.g. 'List(Alpha)') a 'put'-function
   typically looks like:

   non-reentrant API:
   |  void putList(List(Alpha) v, void putAlpha(Alpha v))
   |  {
   |    putInt(List_length(v));
   |    for (; !List_null(v); v = List_rest(v))
   |      putAlpha(List_first(Alpha,v));
   |  }

   reentrant API:
   |  void putList(BinImg_T img, List(Alpha) v, void putAlpha(BinImg_T img,Alpha v))
   |  {
   |    fputInt(img,List_length(v));
   |    for (; !List_null(v); v = List_rest(v))
   |      putAlpha(img,List_first(Alpha,v));
   |  }

   In the case of a heterogen parameter type ("Object") the user has to save 
   the corresponding 'get'-function together with the value.
*/

void putAbstract(Abs_T v, void putData(Abs_T v), void getData(Abs_T *v))
/* put abstract data to file */
{
  putFunction((StdCPtr)getData);
  putData(v);
}

void fputAbstract
     (
       BinImg_T img, Abs_T v, 
       void putData(BinImg_T img,Abs_T v), 
       void getData(BinImg_T img,Abs_T *v)
     )
/* put abstract data to file 'img' (reentrant) */
{
  fputFunction(img,(StdCPtr)getData);
  putData(img,v);
}

void getAbstract(Abs_T *v)
/* get abstract data from file */
{ StdCPtr getData;
  getFunction(&getData);
  ((void (*)(Abs_T *v))getData)(v);
}

void fgetAbstract(BinImg_T img, Abs_T *v)
/* get abstract data from file 'img' (reentrant) */
{ StdCPtr getData;
  fgetFunction(img,&getData);
  ((void (*)(BinImg_T img,Abs_T *v))getData)(img,v);
}

/*I-------------------------------- Pointer ------------------------------------------- */

/*!!
   References to multiple or cyclic referenced structures ( except symbols and functions )
   can't be simply expanded if the representation should be unique.
   For cases like this we support the following function.

   non-reentrant API:
   |  void putReference(Abs_T  v, void putData(Abs_T v));

   reentrant API:
   |  void fputReference(BinImg_T img, Abs_T  v, void putData(BinImg_T img,Abs_T v));

   This function outputs a reference number for this structure and only in the case of the 
   first reference the structure values.
*/

void putReference(Abs_T v, void putData(Abs_T v))
/* put a pointer to file */
{
  if (MAP_defined(pcimg->putmap,v))
  {
    putLong(MAP_apply(long,pcimg->putmap,v));
  }
  else
  { long id = MAP_count(pcimg->putmap);
    MAP_dfndom(pcimg->putmap,v,id);
    putLong(id);
    putData(v);
  }
}

void fputReference
     (
       BinImg_T img, Abs_T v, void putData(BinImg_T img,Abs_T v)
     )
/* put a pointer to file 'img' (reentrant) */
{
  if (MAP_defined(img->putmap,v))
  {
    fputLong(img,MAP_apply(long,img->putmap,v));
  }
  else
  { long id = MAP_count(img->putmap);
    MAP_dfndom(img->putmap,v,id);
    fputLong(img,id);
    putData(img,v);
  }
}

void getReference(Abs_T *v, void getData(Abs_T *v))
/* get a pointer from file */
{ long getid;
  getLong(&getid);
  if (getid < OT_CNT(pcimg->getmap))
  {
    *v = OT_GET(Abs_T,pcimg->getmap,getid);
  }
  else
  {
    assert0(getid == OT_CNT(pcimg->getmap),"out of sync");
    OT_PUSH(NULL,pcimg->getmap);
    getData(v);
    OT_UPD(Abs_T,pcimg->getmap,getid,*v);
  }
}

void fgetReference
     (
       BinImg_T img, Abs_T *v, void getData(BinImg_T img,Abs_T *v)
     )
/* get a pointer from file 'img' */
{ long getid;
  fgetLong(img,&getid);
  if (getid < OT_CNT(img->getmap))
  {
    *v = OT_GET(Abs_T,img->getmap,getid);
  }
  else
  {
    assert0(getid == OT_CNT(img->getmap),"out of sync");
    OT_PUSH(NULL,img->getmap);
    getData(img,v);
    OT_UPD(Abs_T,img->getmap,getid,*v);
  }
}
