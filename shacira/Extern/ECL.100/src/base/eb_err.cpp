// ===========================================================================
// eb_err.cpp                                                   ______ /  ECL
// Autoren: Thomas Epting, Markus Wuertz                       /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cErrBase   - Basisklasse fuer Exception-Handling. Nimmt den Fehler-
//                     code und eine einfache Fehlermeldung auf und kann diese
//                     auf Verlangen auf verschieden Arten ausgeben.
//
// Alle Fehlermeldungen werden in einer Datei namens 'ERROR.MSG' oder in
// den durch die Umgebungsvariable ECL_ERRMSG spezifizierten Dateien gesucht,
// die einzelnen Dateinamen werden durch ';' getrennt.
//
// Diese Dateien werden zeilenweise gelesen, wobei fuer den Zeilenaufbau gilt:
//
//    - Zeilen, die mit einem Buchstaben beginnen, werden als Definition einer
//      Fehlermeldung im folgenden Format interpretiert:
//
//         <Fehlercode> Leerstelle <Fehlermeldung>
//
//    - Eine Zeile, die !include <Dateiname> beginnt, fuegt den Inhalt der
//      spezifizierten Datei an dieser Stelle ein.
//
//    - Alle anderen Zeilen werden ignoriert.
//
// Der Fehlercode muss dem Schema PPP-C-EE folgen, die Fehlermeldung kann
// ueber Jokerzeichen der Form $x parametrisiert werden, wobei x fuer die
// Parameternummer (1..4) steht.
//
// Bedingte Texte: mit $x{Text} wird der Text nur ausgegeben, wenn der Para-
// meter $x belegt ist. Der Text kann $x enthalten, Bedingungen koennen aber
// nicht geschachtelt werden.
//
// Beispiel:
//
//    ERR-I-01 Funktion nicht implementiert
//    ERR-E-01 Ungueltiger Zeiger: $1
//    ERR-E-02 Ungueltiges Handle: $1
//    ERR-E-03 Ungueltiger Parameter $1: $2
//    ERR-E-04 Fehler bei Initialisierung
//    ERR-E-05 Datei nicht gefunden$1{: $1}
//    ERR-F-01 Kein freier Speicher mehr
//    ERR-F-02 Keine freien Handles mehr
//
// ===========================================================================

#include "base/eb_err.hpp"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_base.hpp"

#endif /*__INTERFACE__*/




// ===========================================================================
// Lokale Klasse cMessage
// ---------------------------------------------------------------------------
//
// cBase
//  +--cMessage
//
// ===========================================================================

class cMessage : public cBase {

public:
   cMessage(cErrBase::ERR_TYPE code, const char *msg);
   cMessage(const char *code, const char *msg);
  ~cMessage();


// Konvertierung Fehlercode
// ========================
// Str2Code() - Ermittelt die numerische Form des Codes aus der Textform
// Code2Str() - Erzeugt die Textform des Codes

   static cErrBase::ERR_TYPE convStr2Code(const char *str);
   static size_t convCode2Str(char *str, cErrBase::ERR_TYPE code, size_t len);


// Verzeigerung
// ============

private:
   cMessage *next;
   static cMessage *first, *last;
   static bool initialized;
   static int file_not_found;
   void add(cErrBase::ERR_TYPE code, const char *msg);

public:
   static void initialize();
   static void cleanup();
   static bool readFile(const char *fname);
   static bool includeFile(const char *from_fname, const char *incl_fname);
   static cMessage *find(cErrBase::ERR_TYPE code);
   static int getFileNotFound() { return file_not_found; }

// Meldungsdaten
// =============

   cErrBase::ERR_TYPE getCode() const { return code; }
   const char *getMsg() const { return msg; }

private:
   cErrBase::ERR_TYPE code;
   char *msg;

};


// Implementierung cMessage
// ===========================================================================

cMessage * cMessage::first = NULL;
cMessage * cMessage::last = NULL;
bool cMessage::initialized = false;
int cMessage::file_not_found = 0;

cMessage::cMessage(cErrBase::ERR_TYPE code, const char *msg)
{
   add(code, msg);
}

cMessage::cMessage(const char *code, const char *msg)
{
   cErrBase::ERR_TYPE num_code = convStr2Code(code);

// if ( num_code == cErrBase::errMalformed ) {
//    fprintf(stderr, "<invalid error code %s>\n", code);
// } else {
      add(num_code, msg);
// }
}

cMessage::~cMessage()
{
   delete[] msg; // -TE- 02.03.2001 delete -> delete[]
}


// Konvertierung Fehlercode
// ========================

cErrBase::ERR_TYPE cMessage::convStr2Code(const char *str)
{
   cErrBase::ERR_TYPE code = 0;

   while ( *str && *str != '-' )
      code = 256 * code + *str++;

   if ( *str++ ) {
      switch ( toupper(*str++) ) {
       case 'I':  code = 256*code; break;
       case 'W':  code = 256*code + 64; break;
       case 'E':  code = 256*code + 128; break;
       case 'F':  code = 256*code + 192; break;
       default:   return cErrBase::errMalformed;
      }

      if ( *str++ == '-' ) {
         cErrBase::ERR_TYPE sub_code = atoi(str);
         if ( sub_code < 1 || sub_code > 64 )
            return cErrBase::errMalformed;
         code += sub_code - 1;
      }
   }

   return code;
}

size_t cMessage::convCode2Str(char *str, cErrBase::ERR_TYPE code, size_t len)
{
   char buf[16];

   sprintf(buf, "%c%c%c-%c-%02d",
      (char)((code & 0xff000000) >> 24),
      (char)((code & 0x00ff0000) >> 16),
      (char)((code & 0x0000ff00) >> 8),
      "IWEF"[(code & 0x000000c0) >> 6],
      (int)(code & 0x3f) + 1);

   strxcpy(str, buf, len);
   return strlen(buf);
}


// Verzeigerung
// ============

void cMessage::initialize()
{
   // Fuer das automatische Aufrufen von cMessage::cleanup() Sorge tragen...
   class cAutoCleanup { public: ~cAutoCleanup() { cMessage::cleanup(); } };
   static cAutoCleanup auto_cleanup;

   if ( !initialized ) {

      // Das Oeffnen der Meldungsdatei wird aus Performancegruenden
      // nur ein einziges Mal versucht.

      initialized = true;

      const char *fname = getenv("ECL_ERRMSG");
      if ( !fname )
         fname = "ERROR.MSG";

      char buf[512];
      const char *fend;

      while (*fname) {
         // naechsten Dateinamen in buf kopieren
         if ( (fend = strchr(fname,';')) == NULL ) {
            fend = fname+strlen(fname);
         }
         if (fend-fname >= sizeof(buf)) {
            strncpy(buf,fname,sizeof(buf)-1);
            buf[sizeof(buf)-1] = '\0';
         } else {
            strncpy(buf,fname,fend-fname);
            buf[fend-fname] = '\0';
         }

         readFile(buf);

         fname = *fend ? fend+1 : fend;
      } /*while (*fname)*/

   }
}

void cMessage::cleanup()
{
   cMessage *msg = first;

   while ( msg ) {
      cMessage *to_del = msg;
      msg = msg->next;
      delete to_del;
   }
}

bool cMessage::readFile(const char *fname)
{
   FILE *fp;
   char buf[512];

   if ( (fp = fopen(fname, "r")) != NULL ) {
      while ( fgets(buf, sizeof buf, fp) > 0 ) {
         char *newln = strchr(buf, '\n');
         if ( *newln )
            *newln = '\0';
         if ( strnicmp(buf, "!include", 8) == 0 ) {
            includeFile(fname, buf + 9);
         } else if ( isalpha(*buf) ) {
            char *msg = strchr(buf, ' ');
            if ( msg ) {
               *msg++ = '\0';
               while ( msg && *msg == ' ' )
                  msg++;
            }
            new0 cMessage(buf, msg);
         }
      }
      return true;
   }

   file_not_found++;
   return false;
}

bool cMessage::includeFile(const char *from_fname, const char *incl_fname)
{
   while ( *incl_fname == ' ' )
      incl_fname++;

   if ( readFile(incl_fname) )
      return true;

   bool rc = false;

   #if defined __ECL_VCPP__
      char drive[_MAX_DRIVE], dir[_MAX_DIR];
      _splitpath(from_fname, drive, dir, NULL, NULL);
      char inc_dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
      _splitpath(incl_fname, NULL, inc_dir, fname, ext);
      char incl_fname2[_MAX_PATH]; strcat(dir, inc_dir);
      _makepath(incl_fname2, drive, dir, fname, ext);
      file_not_found--;
      rc = readFile(incl_fname2);
   #endif

   return rc;
}

void cMessage::add(cErrBase::ERR_TYPE code, const char *msg)
{
   cMessage::code = code;

   if ( msg && (cMessage::msg = new0 (char[strlen(msg)+1])) != NULL ) {
      strcpy(cMessage::msg, msg);
   } else {
      cMessage::msg = NULL;
   }

   next = NULL;

   if ( !first )
      first = this;

   if ( !last ) {
      last = this;
   } else {
      last->next = this;
      last = this;
   }
}

cMessage * cMessage::find(cErrBase::ERR_TYPE code)
{
   for ( cMessage *m = first ; m ; m = m->next ) {
      if ( m->code == code )
         return m;
   }

   return NULL;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cErrBase
// ---------------------------------------------------------------------------
//
// Kodierung der Fehlermeldungen in einem 32-Bit Long:
//
//    31           24 23           16 15            8 7 6 5         0
//   +---------------+---------------+---------------+---+-----------+
//   |P P P P P P P P|P P P P P P P P|P P P P P P P P|C C E E E E E E|
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// wobei:
//
//    PPP = der Modulpraefix als 3-Zeichen Eyecatcher
//    C   = die Fehlerklasse
//    EE  = der Fehlercode - 1
//
// Moegliche Fehlerklassen:
//
//    00 = (I) Informationen
//    01 = (W) Warnungen
//    10 = (E) Fehler
//    11 = (F) Fatale Fehler
//
// Die Ausgabe der Fehlermeldung erfolgt in folgender Syntax:
//
//    PPP-C-EE: Fehlermeldung
//
// cBase
//  +--cErrBase
//
// ===========================================================================

class __ECL_DLLEXPORT__ cErrBase : public cBase {

// Allgemeine Fehlercodes
// ======================

public:

   // Lesen der Fehlermeldungsdatei erzwingen
   static void initialize();

   typedef unsigned long ERR_TYPE; // 32-Bit

   #define ERR_PREFIX(c1,c2,c3)                 \
      (   (cErrBase::ERR_TYPE)(c1) * 0x01000000L  \
        + (cErrBase::ERR_TYPE)(c2) * 0x00010000L  \
        + (cErrBase::ERR_TYPE)(c3) * 0x00000100L )

   #define errInfo   0L    /* Informationen  */
   #define errWarn   64L   /* Warnungen      */
   #define errError  128L  /* Fehler         */
   #define errFatal  192L  /* Fatale Fehler  */

   enum ERR_CODE { errBase = ERR_PREFIX('E','R','R'),

      // Kein Fehler
      errNoError     = 0                , // Kein Fehler

      // Informationen
      errSorry       = errBase+errInfo  , // Noch nicht implementiert
      errMalformed                      , // Fehlercode-Textform ungueltig

      // Fehler
      errGeneral     = errBase+errError , // Allgemeiner Fehler
      errInvPointer                     , // Ungueltiger Zeiger
      errInvHandle                      , // Ungueltiges Handle
      errInvParam                       , // Ungueltiger Parameter
      errInit                           , // Fehler bei Initialisierung
      errTimeout                        , // Zeitueberschreitung
      errOverflow                       , // Ueberlauf jeglicher Art
      errUnderflow                      , // Unterlauf jeglicher Art

      // Fatale Fehler
      errNoMem       = errBase+errFatal , // Kein freier Speicher mehr
      errNoHandles                        // Keine freien Handles mehr

   };


// Konstruktor/Destruktor
// ======================

public:
   cErrBase(ERR_TYPE err)
      { ealloc(err); }
   cErrBase(ERR_TYPE err, const char *p1, const char *p2 = NULL)
      { ealloc(err); setParam(0, p1); setParam(1, p2); }
   cErrBase(ERR_TYPE err, const char *p1, const char *p2, const char *p3, const char *p4 = NULL)
      { ealloc(err); setParam(0, p1); setParam(1, p2); setParam(2, p3); setParam(3, p4); }
   cErrBase(const cErrBase& other)
      { eclone(other); }
   ~cErrBase()
      { efree(); }

   cErrBase& operator= (const cErrBase& right)
      { efree(); eclone(right); return *this; }



// Umwandlung
// ==========
// operator ERR_TYPE() - Ein Cast des Fehler-Objektes nach ERR_TYPE
//    liefert den urspruenglichen Fehlercode
//
// String() - Erzeugt die vollstaendige Fehlermeldung
//
// getCode() - liefert Fehlercode "EEEEEE" (ohne Klasse und Prefix)
// getClass() - liefert Fehlerklasse "CC" (errInfo, errWarn, errError, errFatal)
// getPrefix() - liefert Modulpraefix (oder 0)

private:
   void catMsg(char *& buf, size_t& size, const char *msg, size_t max = 0) const;
   void fmtMsg(char *& buf, size_t& size, const char *msg) const;

public:
   operator ERR_TYPE() const { return xerr ? xerr->err_code : errNoError; }
   const char *getString(char *buffer, size_t size, const char *add_text = NULL) const;

   int getClass() const    { return xerr ? (xerr->err_code & 0xC0) : errInfo; }
   int getCode() const     { return xerr ? (xerr->err_code & 0x3F)+1 : errNoError; }
   int getPrefix() const   { return xerr ? (xerr->err_code & 0xFFFFFF00) : 0; }


// Ausgabe
// =======
// operator<< - Das Fehlerobjekt kann seine Fehlermeldung auf einem Stream
//    ausgeben
//
// DbgOut() - Ausgabe der Fehlermeldung auf dem Debug-Kanal

public:
   friend __ECL_EXP1__ ostream& __ECL_EXP2__ operator<<(ostream& os, cErrBase const& err);
   void DbgOut(const char *add_text = NULL) const;


// Fehlerparameter
// ===============
// setParam() - Setzt einen optionalen Meldungsparameter. Es kann zwischen
//    verschiedenen Parametertypen gewaehlt werden.
// getParam() - Ermittelt einen Fehlerparameter in seiner textuellen Form

public:
   enum NUM_FMT { fmtDec, fmtHex };

   void setParam(int p, char ch);
   void setParam(int p, const char *txt);
   void setParam(int p, long num, NUM_FMT fmt = fmtDec);
   void setParam(int p, void *ptr);

   const char *getParam(int p) const;


// Daten
// =====
// err_code - [private] - Fehlercode
// param - Meldungsparameter

private:
   struct XERR {
      ERR_TYPE err_code;
      char *param[4];
      int refc;
   } *xerr;
   void ealloc(ERR_TYPE err);
   void eclone(const cErrBase &other);
   void efree();

};

__ECL_EXP1__ ostream& __ECL_EXP2__ operator<<(ostream& os, cErrBase const& err);

#endif /*__INTERFACE__*/


// Implementierung cErrBase
// ===========================================================================

void cErrBase::initialize()
{
   // Normalerweise wird die Fehlermeldungsdatei beim ersten Formatieren
   // einer Fehlermeldung gelesen. Durch Aufruf dieser statischen Funktion
   // kann das Lesen der Fehlermeldungsdatei zu einem definierten Zeitpunkt
   // erzwungen werden.

   cMessage::initialize();
}

void cErrBase::ealloc(ERR_TYPE err)
{
   if ( (xerr = new0 XERR) != NULL ) {
      xerr->err_code = err;
      xerr->refc = 1;
      for ( int i = 0 ; i < sizeof xerr->param / sizeof xerr->param[0] ; i++ )
         xerr->param[i] = NULL;
   }
}

void cErrBase::eclone(const cErrBase &other)
{
   xerr = other.xerr;
   if (xerr != NULL) {
      xerr->refc++;
   }
}

void cErrBase::efree()
{
   if ( xerr != NULL && --xerr->refc == 0 ) {
      for ( int i = 0 ; i < sizeof xerr->param / sizeof xerr->param[0] ; i++ ) {
         delete[] xerr->param[i];
      }
      delete xerr;
   }
}


// Ausgabe
// =======

__ECL_EXP1__ ostream& __ECL_EXP2__ operator<<(ostream& os, cErrBase const& err)
{
   char buf[1024] = "";
   return os << err.getString(buf, sizeof buf);
}

void cErrBase::DbgOut(const char *add_text) const
{
   char buf[1024] = "";
   getString(buf, sizeof buf, add_text);
   DbgError(buf);
}


// Umwandlung
// ==========

void cErrBase::catMsg(char *& buf, size_t& size, const char *msg, size_t max) const
{
   if ( buf && size && msg ) {
      if ( max == 0 )
         max = strlen(msg);
      size_t len = size-1 < max ? size-1 : max;
      strxcpy(buf, msg, len+1); size -= len; buf += len;
   }
}

void cErrBase::fmtMsg(char *& buf, size_t& size, const char *msg) const
{
   const char *msg2;

   while ( size && (msg2 = strchr(msg, '$')) != NULL ) {
      if ( msg2 > msg )
         catMsg(buf, size, msg, msg2 - msg); msg = msg2 + 1;
      if ( *msg == '$' ) {
         catMsg(buf, size, "$"); msg++;
      } else if ( *msg == '\0' ) {
         catMsg(buf, size, "$");
      } else if ( isdigit(*msg) ) {
         int p = *msg++ - '1';
         if ( xerr != NULL && p >= 0 && p < sizeof xerr->param / sizeof xerr->param[0] ) {
            if ( *msg == '{' && strchr(msg, '}') ) {
               size_t len = strchr(msg, '}') - msg; msg++;
               if ( xerr->param[p] ) {
                  char cond[512]; strxcpy(cond, msg, len);
                  fmtMsg(buf, size, cond);
               }
               msg += len;
            } else if ( xerr->param[p] ) {
               catMsg(buf, size, xerr->param[p]);
            }
         }
      }
   }

   if ( size && *msg )
      catMsg(buf, size, msg);
}

const char *cErrBase::getString(char *buffer, size_t size, const char *add_text) const
{
   char *buf = buffer;

   cMessage::initialize();

   size_t len = cMessage::convCode2Str(buf, xerr?xerr->err_code:errNoError, size);
   size -= len; buf += len;

   if ( add_text && size > 4 ) {
      catMsg(buf, size, ": ");
      catMsg(buf, size, add_text);
   }

   if ( size > 4 ) {
      cMessage *msg = cMessage::find(xerr?xerr->err_code:errNoError);
      const char *text;

      if ( msg && msg->getMsg() ) {
         text = msg->getMsg();
      } else if (cMessage::getFileNotFound()) {
         text = "<message file not found>$1{ P1=$1}$2{ P2=$2}$3{ P3=$3}$4{ P4=$4}";
      } else {
         text = "<no message text found>$1{ P1=$1}$2{ P2=$2}$3{ P3=$3}$4{ P4=$4}";
      };
      catMsg(buf, size, ": ");
      fmtMsg(buf, size, text);
   }

   return buffer;
}


// Setzen und erfragen von Fehlerparametern
// ========================================

void cErrBase::setParam(int p, char ch)
{
   if ( xerr != NULL && p >= 0 && p < sizeof xerr->param / sizeof xerr->param[0] ) {
      if ( xerr->param[p] )
         delete[] xerr->param[p]; // -TE- 02.03.2001 delete -> delete[]
      if ( (xerr->param[p] = new0 (char[2])) != NULL ) {
         xerr->param[p][0] = ch;
         xerr->param[p][1] = '\0';
      }
   }
}

void cErrBase::setParam(int p, const char *txt)
{
   if ( xerr != NULL && p >= 0 && p < sizeof xerr->param / sizeof xerr->param[0] ) {
      if ( xerr->param[p] )
         delete[] xerr->param[p]; // -TE- 02.03.2001 delete -> delete[]
      if ( txt && (xerr->param[p] = new0 (char[strlen(txt)+1])) != NULL ) {
         strcpy(xerr->param[p], txt);
      } else {
         xerr->param[p] = NULL;
      }
   }
}

void cErrBase::setParam(int p, long num, NUM_FMT fmt)
{
   if ( xerr != NULL && p >= 0 && p < sizeof xerr->param / sizeof xerr->param[0] ) {
      if ( xerr->param[p] )
         delete[] xerr->param[p]; // -TE- 02.03.2001 delete -> delete[]
      char buf[64];
      switch ( fmt ) {
       case fmtDec:  sprintf(buf, "%ld", num); break;
       case fmtHex:  sprintf(buf, "%lx", num); break;
       default:      strcpy(buf, "0?"); break;
      }
      if ( (xerr->param[p] = new0 (char[strlen(buf)+1])) != NULL )
         strcpy(xerr->param[p], buf);
   }
}

void cErrBase::setParam(int p, void *ptr)
{
   if ( xerr != NULL && p >= 0 && p < sizeof xerr->param / sizeof xerr->param[0] ) {
      if ( xerr->param[p] )
         delete[] xerr->param[p]; // -TE- 02.03.2001 delete -> delete[]
      char buf[64];
      sprintf(buf, "%p", ptr);
      if ( (xerr->param[p] = new0 (char[strlen(buf)+1])) != NULL )
         strcpy(xerr->param[p], buf);
   }
}

const char *cErrBase::getParam(int p) const
{
   if ( xerr != NULL && p >= 0 && p < sizeof xerr->param / sizeof xerr->param[0] ) {
      return xerr->param[p];
   } else {
      return NULL;
   }
}

