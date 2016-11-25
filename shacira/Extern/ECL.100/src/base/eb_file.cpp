// ===========================================================================
// eb_file.cpp                                                  ______ /  ECL
// Autor: Norman Bring                                         /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cFile   - Diese Klasse bildet eine einheitliche Schnittstelle fuer
//     |            Dateizugriffe und macht die auf sie zugreifenden Module
//     |            unabhaengig von dem verwendeten Compiler. Zusaetzlich wer-
//     |            den alle Dateizugriffe durch Handles ueberwacht und die
//     |            errno-Fehler auf Fehlermeldungen dieses Moduls abgebildet
//     |            (in Textform in error.msg nachzulesen)
//     |
//     +--cDir    - Ermoeglicht einheitlichen Zugriff auf Verzeichnisse (nur
//     |            bei Compilern mit entsprechenden Routinen wie z.B. GNU-C)
//     |
//     +--cFileFind - Verzeichnisse mit Wildcards durchsuchen
//     |
//     +--cErrFile - Fehlerobjekte bei cFile.
//
// ===========================================================================

/*#pragma strings (readonly)*/

#include "base/eb_file.hpp"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#if defined __ECL_OS2__
   #include <os2.h>
#elif defined __ECL_W32__
   #include <windows.h>
   #include <direct.h>
#endif




// Lokale Daten
// ===========================================================================

// Abhaengigkeiten von Compilern und Systemen

#if defined __ECL_ICC__
#  define __ICC__ 1
#endif

#ifdef __ICC__    // der kennt das tatsaechlich nicht
#  define HAS_VFSCANF   0
#  define HAS_OPENDIR   1
#  define read _read
#  define write _write
#  define isatty _isatty
#elif defined __ECL_VCPP__
#  define HAS_VFSCANF   0
#  define HAS_OPENDIR   0
#  define read _read
#  define write _write
#  define isatty _isatty
#elif defined __ECL_GNUC__
#  define HAS_VFSCANF   1
#  define HAS_OPENDIR   1
#else
#  define HAS_VFSCANF   1
#  define HAS_OPENDIR   0
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include <stdio.h>
#include <stdarg.h>

#if defined __ECL_GNUC__
   #include <io.h>
   #include <sys/types.h>
   #include <sys/stat.h>
#else
   #include <io.h>
   #include <sys/stat.h>
#endif

#include "base/eb_err.hpp"
#include "base/eb_str.hpp"

class cFile;
class cDir;

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cErrFile
// ---------------------------------------------------------------------------
//
// cBase
//  +--cErrBase
//      +--cErrFile
//
// ===========================================================================

class __ECL_DLLEXPORT__ cErrFile : public cErrBase {

public:
   cErrFile(ERR_TYPE err);
   cErrFile(ERR_TYPE err, const char *filespec);
   cErrFile(ERR_TYPE err, cFile& file);
   cErrFile(ERR_TYPE err, cDir& dir);

   enum ERR_CODE { errBase = ERR_PREFIX('F','I','L'),

      // Informationen
      errEOF         = errBase+errInfo  , //
      errNoMatch                        , //

      // Fehler
      errIllSpec     = errBase+errError , //
      errIllDevice                      , //
      errIllParam                       , //
      errIllAccess                      , //
      errFileNotFound                   , //
      errPathNotFound                   , //
      errExists                         , //
      errPermDenied                     , //
      errGeneralIO                      , //
      errDeviceFull                     , //
      errWriteProt                      , //
      errSeek                           , //
      errUnget                          , //
      errShare                          , //
      errDeviceInUse                    , //
      errDeviceLocked                   , //
      errPipeBusy                       , //
      errDeviceNotReady                 , //
      errSorry                          , //

      // Fatale Fehler
      errIllHandle   = errBase+errFatal , //
      errTableOverflow                  , //
      errTooManyFiles                   , //
      errLib                              //

   };

};

#endif /*__INTERFACE__*/


// Implementierung cErrFile
// ===========================================================================

cErrFile::cErrFile(ERR_TYPE err) :
   cErrBase(err)
{
   // ...
}

cErrFile::cErrFile(ERR_TYPE err, const char *filespec) :
   cErrBase(err)
{
   if ( filespec ) {
      setParam(0, filespec);
   }
}

cErrFile::cErrFile(ERR_TYPE err, cFile& file) :
   cErrBase(err)
{
   setParam(0, file.GetName());
}

cErrFile::cErrFile(ERR_TYPE err, cDir& /*dir*/) :
   cErrBase(err)
{
   // ...
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cFile
// ---------------------------------------------------------------------------
//
// cBase
//  +--cFile
//
// ===========================================================================

class __ECL_DLLEXPORT__ cFile : public cBase {

// Konstanten
public:
   #if defined __ECL_OS2__
      enum {
         PATH_MAX = 260,               // CCHMAXPATH aus BSEDOS.H
         PATH_COMP_MAX = 256           // CCHMAXPATHCOMP aus BSEDOS.H
      };
      #define File_SEPARATOR  "\\"
      #define File_CONSOLE  "con"
   #elif defined __ECL_W32__
      enum {
         PATH_MAX = _MAX_PATH,
         PATH_COMP_MAX = _MAX_DIR
      };
      #define File_SEPARATOR  "\\"
      #define File_CONSOLE  "con"
   #endif

// Typen
public:
   typedef char NAME[ PATH_MAX ];          // Dateiname
   typedef const char *MODE;               // Zugriffsmodus auf Dateien
   typedef struct stat STAT;               // Statusdaten einer Datei
   typedef fpos_t POS;                     // Positionsangabe

   enum BUF_MODE {  // Puffertypen
      BUF_MODE_FULL  = _IOFBF,
      BUF_MODE_LINE  = _IOLBF,
      BUF_MODE_NONE  = _IONBF
   };

   enum SEEK_MODE {  // Modus fuer Seek()
      SEEK_MODE_SET  = SEEK_SET,
      SEEK_MODE_CUR  = SEEK_CUR,
      SEEK_MODE_END  = SEEK_END
   };

// Variablen
private:
   FILE        *File;      // Filehandle
   cString     Name;       // Dateiname
   bool        Text;       // Textmodus?
   bool        IsTTY;      // Zeichenorientiertes Geraet?

   static unsigned long EclMode;  // ECL-spezifische Betriebsarten
public:
   enum {
      ECL_MODE_NOEOFERR = 0x0001    // eof wirft keinen Fehler
   };
   static cBase::MASK_NAME EclMode_mask_name[];

   // Hier sollten mal alle File_...-Typen stehen

// ------ METHODEN ---------------------------------------------------

private:
   void OpenFile( const char *fname, MODE mode );
   void RaiseError( int err_code );

public:
   cFile( const char *fname=NULL, MODE mode="r" );    // Datei oeffnen
   cFile( FILE *f_handle, MODE mode="r" );            // Existierendes Handle einbinden
   ~cFile();                                          // Datei schliessen
   void Open( const char *fname, MODE mode="r" );     // Datei oeffnen (falls nicht durch Konstruktor)
   void Assign( FILE *f_handle, MODE mode="r" );      // Existierendes Handle einbinden
   void Close();                                      // Datei schliessen (Objekt bleibt erhalten)
   bool Eof();                                        // EOF erreicht?
   int GetNo();                                       // DOS-Handle erfragen
   void SetBuf( void *buf );                          // Dateipuffer setzen
   void SetVBuf( void *buf, BUF_MODE type, size_t size );
   void GetPos( POS *pos );                           // Dateiposition ermitteln?
   void SetPos( POS *pos );                           // Dateiposition setzen
   void Rewind();                                     // Dateizeiger zuruecksetzen
   void Seek( long offset, SEEK_MODE mode );          // Dateiposition suchen
   long Tell();                                       // Dateiposition ermitteln
   void FStat( STAT *stat_buf );                      // Dateizustand abfragen
   void Reopen( const char *fname, MODE mode );       // Andere Datei mit Objekt verbinden
   void Flush();                                      // Dateipuffer schreiben
   void Write( void *ptr, size_t elem_size, size_t count );   // In Datei schreiben
   void Putc( int ch );                               // Zeichen in Datei schreiben
   void Puts( const char *s );                        // String in Datei schreiben
   int Printf( const char *fmt, ... );                // printf in Datei
   int VPrintf( const char *fmt, va_list args );      // vprintf in Datei
   size_t cFile::Read( void *ptr, size_t elem_size, size_t count );  // Aus Datei lesen
   int Getc();                                        // Zeichen aus Datei lesen
   char *Gets( char str[], int max_len, bool strip_nl=false ); // String aus Datei lesen
   int Scanf( const char *fmt, ... );                 // Scanf aus Datei
   int VScanf( const char *fmt, va_list args );       // VScanf aus Datei
   void Ungetc( int c );                              // Eingelesenes Zeichen zurueckstellen
   size_t RawRead( void *ptr, size_t count );         // Low-Level Lesen
   size_t RawWrite( void *ptr, size_t count );        // Low-Level Schreiben
   bool Isatty();                                     // Ist Datei zeichenorientiert?
   cString GetName();                                 // Liefert Dateinamen
   void ClearError();                                 // Fehlerzustand zuruecksetzen

   // Auch direkt aufzurufende Funktionen
   static bool Exists( const char *fname );           // Vorhandensein abpruefen
   static void MakeDirName( char path_name[] );       // Backslash an Pfad haengen (falls noetig)
   static void Stat( char *path, STAT *stat_buf );    // Statusdaten ermitteln
   static void Rename( const char *old_name, const char *new_name );
   static void Copy( const char *from_fspec, const char *to_fspec );
   static void Remove( const char *fpattern );
   static cString ExpandFileName(cString path, cString name, cString ext);
   static cString SplitFileName(cString fspec, cString &path, cString &ext);
   static cString GetPath(cString fspec);             // Pfad ermitteln (mit '\' am Ende)
   static cString GetName(cString fspec);             // Dateiname (ohne Ext) ermitteln
   static cString GetFullName(cString fspec);         // Dateiname mit Ext ermitteln
   static cString GetExt(cString fspec);              // Erweiterung ermitteln (mit '.')

   static void SetMode(unsigned long mode);           // Betriebsart einstellen
   static void SetMode(const char *mode);             // Betriebsart in Klartext einstellen
   static unsigned long GetMode();                    // Betriebsart ermitteln
};


#endif /*__INTERFACE__*/


// Implementierung cFile
// ===========================================================================


// Konstanten und Makros
// ---------------------------------------------------------------------------

#define VERSION         100
#define IS_TEXT(mode)   (!strchr( mode, 'b' ))

unsigned long cFile::EclMode = 0;
cBase::MASK_NAME cFile::EclMode_mask_name[] = {
   cFile::ECL_MODE_NOEOFERR, "noeoferr"
};


// lokale Funktionen
// ---------------------------------------------------------------------------

#ifdef __ECL_OS2__

// GetOSErr - Ermittelt den Fehlercode aus den tieferen Schichten des OS

static cErrBase::ERR_TYPE GetOSErr( void )
{
   cErrBase::ERR_TYPE err;

   switch ( _doserrno ) {
      case   0 : err = cErrFile::errGeneralIO;        break;
      case   1 : err = cErrFile::errIllParam;         break;
      case   2 : err = cErrFile::errFileNotFound;     break;
      case   3 : err = cErrFile::errPathNotFound;     break;
      case   4 : err = cErrFile::errTooManyFiles;     break;
      case   5 : err = cErrFile::errIllAccess;        break;
      case   6 : err = cErrFile::errIllParam;         break;
      case   8 : err = cErrBase::errNoMem;            break;
      case  12 : err = cErrFile::errIllAccess;        break;
      case  15 : err = cErrFile::errIllDevice;        break;
      case  18 : err = cErrFile::errNoMatch;          break;
      case  19 : err = cErrFile::errWriteProt;        break;
      case  21 : err = cErrFile::errDeviceNotReady;   break;
      case  25 : err = cErrFile::errSeek;             break;
      case  32 : err = cErrFile::errShare;            break;
      case  38 : err = cErrFile::errEOF;              break;
      case  39 : err = cErrFile::errDeviceFull;       break;
      case  87 : err = cErrFile::errIllParam;         break;
      case  99 : err = cErrFile::errDeviceInUse;      break;
      case 108 : err = cErrFile::errDeviceLocked;     break;
      case 112 : err = cErrFile::errDeviceFull;       break;
      case 206 : err = cErrFile::errIllSpec;          break;
      case 231 : err = cErrFile::errPipeBusy;         break;
      default  : err = cErrFile::errGeneralIO;        break;
   }

   return err;
}

#endif

// ConvError - Konvertiert einen ERRNO-Fehler in einen ERR_TYPE
//
// Der uebergebene Fehlercode wird mit den E...-Konstanten des verwendeten
// Compilers verglichen und auf Fehlermeldungen dieses Moduls abgebildet.
// Wird ein Zeiger auf eine aktive Dateistruktur uebergeben, so wird der
// ermittelte Fehlercode in dieser hinterlegt und kann mit File_Error()
// abgefragt werden.

static cErrBase::ERR_TYPE ConvError( int err_code )
{
    cErrBase::ERR_TYPE err = cErrFile::errLib;

    switch ( err_code ) {
     case 0         : err = cErrFile::errEOF;            break;
     case ENOENT    : err = cErrFile::errFileNotFound;   break;
     case EBADF     : err = cErrFile::errIllHandle;      break;
     case EACCES    : err = cErrFile::errIllAccess;      break;
     case EEXIST    : err = cErrFile::errExists;         break;
     case EINVAL    : err = cErrFile::errIllParam;       break;
     case EMFILE    : err = cErrFile::errTooManyFiles;   break;
     case ENOSPC    : err = cErrFile::errDeviceFull;     break;
#ifdef __ECL_ICC__
     case EISOPEN   : err = cErrFile::errIllAccess;      break;
     case ENOTEXIST : err = cErrFile::errFileNotFound;   break;
     case EBADMODE  : err = cErrFile::errIllParam;       break;
     case EBADNAME  : err = cErrFile::errIllSpec;        break;
     case ENOMEM    : err = cErrBase::errNoMem;          break;
     case ENOTWRITE : err = cErrFile::errWriteProt;      break;
     case ENOSEEK   : err = cErrFile::errSeek;           break;
     case EPASTEOF  : err = cErrFile::errEOF;            break;
     case EOS2ERR   : err = GetOSErr();                  break;
     default        : err = cErrFile::errGeneralIO;      break;
#endif
    }

    return err;
}


// isstd - Stellt fest, ob es sich um einen Standardkanal handelt

static bool isstd( FILE *f )
{
    return (f == stderr || f == stdin  || f == stdout);
}


// strichr - String "case"-unabhaengig nach Zeichen absuchen

static char *strichr( const char *string, int ch )
{
        ch = toupper(ch);

        while( *string && (toupper( *string ) != ch) )
                string++;

        return (ch == toupper(*string) ? (char *) string : NULL);
}


// stristr - Sucht String in String ohne "case" zu beachten

static char *stristr( const char *string, const char *pattern )
{
        size_t plen;
        char *s;

        plen = strlen(pattern);

        do {
                if( NULL == (s = strichr( string, *pattern )) )
                        break;
                else if( strnicmp(s, pattern, plen) == 0 )
                        return s;
                else
                        string = s+1;
        } while( *string );

        return NULL;
}


// ispipe - Ist Dateiname eine Pipe?

static bool ispipe( const char * fname )
{
#if defined __ECL_OS2__
   return (stristr( fname, "\\pipe\\" ) != NULL);
#elif defined __ECL_W32__
   return stristr( fname, "\\pipe\\" ) != NULL;
#else
   return false;
#endif
}


// globale Funktionen (nicht nur ueber Objekt)
// ---------------------------------------------------------------------------


// File_Exists - Prueft das Vorhandensein einer Datei

bool cFile::Exists( const char *fname )
{
   FILE *f;

   if( !fname || NULL == (f = fopen( fname, "r" )) ) {
      return false;
   } else {
      fclose( f );
      return true;
   }
}


// Stat - Ermittelt Statusdaten einer Datei   -> stat

void cFile::Stat( char *path, STAT *stat_buf )
{
   if( !stat_buf || !path || !*path ) {
      throw cErrFile(cErrFile::errIllParam, path);
   } else if( EOF == stat( path, stat_buf ) ) {
      throw cErrFile(ConvError( errno ));
   }
}


// MakeDirName - Ergaenzt Pfad um einen Backslash (wenn noetig)
//
// !!! Da in path_name geschrieben wird, darf es auf gar keinen Fall auf
// !!! statische Daten zeigen, sonst -> Protection Fault

void cFile::MakeDirName( char path_name[] )
{
   if( !*path_name || strcmp( path_name + strlen(path_name) - strlen(File_SEPARATOR) , File_SEPARATOR ) != 0 ) {
      strcat( path_name, File_SEPARATOR );
   }
}


// ExpandFileName - sofern nicht im Dateinamen enthalten, diesen um Default-Pfad
//                  und -Extension erweitern

cString cFile::ExpandFileName(cString path, cString name, cString ext)
{
   cString file_name(name);

   if ( !path.isEmpty() && file_name.getPos(File_SEPARATOR) == -1 ) {
      if( path.getRight(strlen(File_SEPARATOR)) != cString(File_SEPARATOR) ) {
         file_name = path + File_SEPARATOR + file_name;
      } else {
         file_name = path + file_name;
      }
   }

   int last_fs=-1, look=-1;
   while ((look = file_name.getPos(File_SEPARATOR, look+1)) != -1) last_fs = look;
   if (!ext.isEmpty() && file_name.getPos(".",last_fs+1) == -1) {
      file_name = file_name + "." + ext;
   };

   return file_name;
}


// SplitFileName - Dateibezeichnung in Pfad, Dateiname und Extension zerlegen

cString cFile::SplitFileName( cString fspec, cString &path, cString &ext )
{
   cString name;

   int last=-1, look=-1;
   while ((look = fspec.getPos(File_SEPARATOR, look+1)) != -1) last = look;

   if (last != -1) {
      path = fspec.getLeft(last+1);
      fspec = fspec.getMid(last+1);
   } else {
      path = "";
   }

   last=-1, look=-1;
   while ((look = fspec.getPos(".", look+1)) != -1) last = look;
   if (last != -1) {
      name = fspec.getLeft(last);
      ext = fspec.getMid(last);
   } else {
      name = fspec;
      ext = "";
   }

   return name;
}

cString cFile::GetPath(cString fspec)
{
   cString path,ext,name = SplitFileName(fspec, path, ext);
   return path;
}

cString cFile::GetName(cString fspec)
{
   cString path,ext,name = SplitFileName(fspec, path, ext);
   return name;
}

cString cFile::GetFullName(cString fspec)
{
   cString path,ext,name = SplitFileName(fspec, path, ext);
   return name+ext;
}

cString cFile::GetExt(cString fspec)
{
   cString path,ext,name = SplitFileName(fspec, path, ext);
   return ext;
}


// Rename - Benennt Datei 'old_name' um in 'new_name'

void cFile::Rename( const char *old_name, const char *new_name )
{
   if( !old_name || !new_name ) {
      throw cErrFile(cErrFile::errIllParam );
   } else if( rename(old_name, new_name) ) {
      throw cErrFile(ConvError( errno ));
   }
}


// Copy - Kopiert Datei 'from_fspec' nach 'to_fspec'

void cFile::Copy( const char *from_fspec, const char *to_fspec )
{
   char buf[33333];
   size_t buf_len = sizeof(buf);

   size_t rd_len;

   cFile from(from_fspec,"rb");
   from.SetMode("noeoferr");
   cFile to(to_fspec,"wb");

   do {
      rd_len = from.RawRead(buf, buf_len);
      to.RawWrite(buf, rd_len);
   } while (rd_len == buf_len);
}


// Remove - Loescht alle Dateien, die auf 'fpattern' passen

void cFile::Remove( const char *fpattern )
{
   if( !fpattern ) {
      throw cErrFile(cErrFile::errIllParam );
   } else if( remove(fpattern) ) {
      cErrBase::ERR_TYPE err = ConvError( errno );
      if (err != cErrFile::errFileNotFound) throw cErrFile( err, fpattern );
   }
}


// Betriebsart einstellen & ermitteln
void cFile::SetMode(unsigned long mode)
{
   EclMode = mode;
}

void cFile::SetMode(const char *mode)
{
   EclMode = cBase::getMask(mode, cFile::EclMode_mask_name, 0);
}

unsigned long cFile::GetMode()
{
   return EclMode;
}


// Implementierung cFile
// ---------------------------------------------------------------------------


// cFile - Konstruktor

cFile::cFile( const char *fname, MODE mode )
{
   File = NULL;
   Name = "";

   if( fname ) {  // Dateiname angegeben
      if( !mode ) {
         throw cErrFile(cErrFile::errIllParam, fname);
      } else {
         Open( fname, mode );
      }
   } else {  // Kein Name angegeben
      File = NULL;
   }
}

cFile::cFile( FILE *f_handle, MODE mode )
{
   if( !f_handle ) {
      throw cErrFile(cErrFile::errIllParam);
   } else {
      Name  = "<assigned>";
      Text  = IS_TEXT( mode );
      File  = f_handle;
      IsTTY = !!isatty( fileno(f_handle) );
   }
}


// ~cFile - Destruktor

cFile::~cFile()
{
   // Datei schliessen
   Close();
}


// RaiseError - Fehler auswerten (ruft ConvError() auf)

void cFile::RaiseError( int err_code )
{
   cErrBase::ERR_TYPE err = ConvError( err_code );

   if( err ) {
      throw cErrFile( err, *this );
   }
}


// OpenFile - Oeffnet eine Datei und initialisiert den FCB
//
// Diese Funktion uebernimmt die Drecksarbeit und oeffnet die Datei
// mit dem angegebenen Namen. Ist in dem FCB bereits ein Filehandle
// eingetragen, so wird freopen aufgerufen.
// Da eine Pipe unter OS/2 nicht geschlossen und wieder geoeffnet werden
// kann (???), muss in diesem Fall auf ein freopen verzichtet werden.

void cFile::OpenFile( const char *fname, MODE mode )
{
   FILE *new_file = NULL;
   bool fail = false;

   // Namen eintragen
   Name  = fname;

   // Ist ein reopen gefordert?
   if( File ) {
      if( ispipe(fname) ) {
         // Eine Pipe kann nicht testweise geoeffnet werden, sie ist nach
         // einem fclose() nicht wieder verfuegbar (warum auch immer???)
         if( NULL != (new_file = fopen( fname, mode )) ) {
            if( !isstd(File) ) fclose( File );
            File = NULL;
         } else {
            fail = true;
         }
      } else if( isstd(File) ) {
         // Standardkanal darf nicht durch freopen geschlossen werden,
         // wenn die neue Datei nicht geoeffnet werden kann.

         if( NULL != (new_file = fopen( fname, mode )) ) {
            fclose( new_file ); new_file = NULL;
         } else {
            fail = true;
         }
      }
   }

   if( !fail ) {
      if( new_file != NULL ) {
         File = new_file;
      } else {
         File = ( File != NULL
                     ? freopen( fname, mode, File )
                     : fopen( fname, mode ) );
      }
   }

   if( fail || !File ) {
      RaiseError( errno );
   } else {
      Text  = IS_TEXT( mode );
      IsTTY = !!isatty( fileno(File) );
   }
}


// Oeffentliche Methoden
// ---------------------------------------------------------------------------


// Eof - Liefert true, falls das Dateiende erreicht ist   -> feof

bool cFile::Eof()
{
   return !!feof( File );
}


// GetNo - Liefert das DOS-Handle   -> fileno

int cFile::GetNo()
{
   return fileno( File );
}


// ClearError - Loescht den Fehlerspeicher der Datei   -> clearerr

void cFile::ClearError()
{
   clearerr( File );
}


// SetBuf - Setzt den Puffer der Datei auf die angegebene Adresse
//
// Die Groesse des Puffers muss zumindest der Defaultpuffergroesse BUFSIZE
// (aus stdio.h) entsprechen, sonst knallt's   -> setbuf

void cFile::SetBuf( void *buf )
{
   setbuf( File, (char *) buf );
}


// SetVBuf - Puffer einer Datei zuordnen   -> setvbuf

void cFile::SetVBuf( void *buf, BUF_MODE type, size_t size )
{
   switch ( type ) {
    case BUF_MODE_LINE :
    case BUF_MODE_FULL :
      if( !size ) {
         throw cErrFile(cErrFile::errIllParam, *this);
      }
      // und weiter im Takt
    case BUF_MODE_NONE :
      if( setvbuf( File, (char *) buf, (int) type, size ) ) {
         throw cErrFile(cErrFile::errLib, *this);
      }
      break;
    default :
      throw cErrFile(cErrFile::errIllParam, *this);
   }
}


// GetPos - Aktuelle Dateiposition ermitteln
//
// Traegt die aktuelle Dateiposition in <pos> ein. Diese kann
// ueber einen Aufruf von File_SetPos wieder angesteuert werden -> fgetpos

void cFile::GetPos( POS *pos )
{
   if( !pos ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else if( fgetpos( File, pos ) ) {
      RaiseError( errno );
   }
}


// SetPos - Dateiposition setzen
//
// Setzt die ueber File_GetPos ermittelte Dateiposition wieder
// als aktuelle Dateiposition   -> fsetpos

void cFile::SetPos( POS *pos )
{
   if( !pos ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else if( fsetpos( File, pos ) ) {
      RaiseError( errno );
   }
}


// Rewind - Schreib/Lesezeiger zuruecksetzen   -> rewind

void cFile::Rewind()
{
   rewind( File );
}


// Seek - Dateiposition setzen   -> fseek

void cFile::Seek( long offset, SEEK_MODE mode )
{
   switch ( mode ) {
    case SEEK_MODE_SET :
    case SEEK_MODE_CUR :
    case SEEK_MODE_END :
      if( fseek( File, offset, mode ) ) {
         throw cErrFile(cErrFile::errSeek, *this);
         // RaiseError( errno );
      }
      break;
    default :
      throw cErrFile(cErrFile::errIllParam, *this);
   }
}


// Tell - Dateiposition abfragen   -> ftell

long cFile::Tell()
{
   long result;

   if( -1 == (result = ftell( File )) ) {
      RaiseError( errno );
   }

   return result;
}


// FStat - Ermittelt Status einer geoeffneten Datei  -> fstat

void cFile::FStat( STAT *stat_buf )
{
   if( !stat_buf ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else if( EOF == fstat( fileno( File ), stat_buf ) ) {
      RaiseError( errno );
   }
}


// GetName - Dateinamen ermitteln

cString cFile::GetName()
{
   return Name;
}


// Open - Datei oeffnen

void cFile::Open( const char *fname, MODE mode )
{
   if( File ) Close();
   OpenFile( fname, mode );
}


// Reopen - Ordnet einem Handle eine neue Datei zu   -> freopen

void cFile::Reopen( const char *fname, MODE mode )
{
   if( !fname || !mode ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else {
      OpenFile( fname, mode );
   }
}


// Close - Schliesst eine mit (Re)Open geoeffnete Datei  -> fclose

void cFile::Close()
{
   if( File && !isstd(File ) ) {
      if( fclose( File ) ) RaiseError( errno );
   }

   Name = "";
   File = NULL;
}


// Flush - Dateipuffer schreiben bzw. loeschen   -> fflush
//
// Schreibt den aktuellen Schreibpuffer in die Datei oder
// loescht den aktuelle Lesepuffer

void cFile::Flush()
{
   if( fflush( File ) ) {
      RaiseError( errno );
   }
}


// Assign - Ordnet einem bestehenden Filepointer ein Handle zu
//
// Erzeugt fuer einen existierenden Filepointer ein Filehandle
// (so kann man z.B. stdin, stdout und stderr auch ueber diese
// Schicht benutzen).

void cFile::Assign( FILE *f_handle, MODE mode )
{
   if( !f_handle ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else {
      Close();
      Text  = IS_TEXT( mode );
      File  = f_handle;
      IsTTY = !!isatty( fileno(f_handle) );
   }
}


// Write - Daten in eine Datei schreiben   -> fwrite

void cFile::Write( void *ptr, size_t elem_size, size_t count )
{
   if( !ptr || !elem_size || !count ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else if( count != fwrite( ptr, elem_size, count, File ) ) {
      RaiseError( errno );
   }
}


// Putc - Schreibt das angegebene Zeichen in die Datei   -> fputc

void cFile::Putc( int ch )
{
   if( EOF == fputc( ch, File ) ) {
      RaiseError( errno );
   }
}


// Puts - Schreibt den angegebenen String in die Datei   -> fputs

void cFile::Puts( const char *s )
{
   if( !s ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else if( *s && EOF == fputs( s, File ) ) {
      RaiseError( errno );
   }
}


// Printf - Printf in eine Datei   -> fprintf

int cFile::Printf( const char *fmt, ... )
{
   int result = -1;
   va_list args;

   if( !fmt ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else {
      va_start( args, fmt );
      result = vfprintf( File, fmt, args );
      va_end( args );
      if( result == EOF ) RaiseError( errno );
   }

   return result;
}


// VPrintf - Variable Printf in eine Datei  -> vfprintf

int cFile::VPrintf( const char *fmt, va_list args )
{
   int result = -1;

   if( !fmt ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else {
      result = vfprintf( File, fmt, args );
      if( result == EOF ) RaiseError( errno );
   }

   return result;
}


// Read - Daten aus einer Datei lesen   -> fread

size_t cFile::Read( void *ptr, size_t elem_size, size_t count )
{
   size_t result = (size_t) -1;

   if( !ptr || !elem_size || !count ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else {
      result = fread( ptr, elem_size, count, File );
      if( result != count ) {
         cErrBase::ERR_TYPE err = ConvError( errno );
         if (err && (err != cErrFile::errEOF || (EclMode & ECL_MODE_NOEOFERR) == 0)) {
            throw cErrFile( err, *this );
         }
         //RaiseError( errno );
      }
   }

   return result;
}


// File_Getc - Lesen eines Zeichens aus einer Datei   -> fgetc

int cFile::Getc()
{
   int result = fgetc( File );
   if( result == EOF) {
      cErrBase::ERR_TYPE err = ConvError( errno );
      if (err && (err != cErrFile::errEOF || (EclMode & ECL_MODE_NOEOFERR) == 0)) {
         throw cErrFile( err, *this );
      }
      // throw cErrFile(cErrFile::errEOF, *this);
   }
   return result;
}


// File_Gets - Einlesen eines Strings aus einer Datei  -> fgets
//
// Liest maximal <max_len> Zeichen aus der angegebenen Datei (einschliess-
// lich Null-Zeichen).
// Ist <strip_nl> true, so wird ein eventuell vorhandenes '\n' entfernt.

char *cFile::Gets( char str[], int max_len, bool strip_nl )
{
   char *result = NULL;

   if( !str || max_len <= 0 ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else {
      result = fgets( str, max_len, File );
      if( !result && (!feof(File) || (EclMode & ECL_MODE_NOEOFERR) == 0)) {
         cErrBase::ERR_TYPE err = ConvError( errno );
         throw cErrFile( err, *this );
         //throw cErrFile(cErrFile::errEOF, *this);
      }
      if( strip_nl ) {
         char *p = strchr( str, '\n' );
         if( p ) *p = '\0';
      }
   }

   return result;
}


// Scanf - Liest formatiert aus der angegebenen Datei   -> fscanf

int cFile::Scanf( const char *fmt, ... )
{
   int result = -1;
   va_list args;

   if( !fmt ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else {
      va_start( args, fmt );
      result = VScanf( fmt, args );
      va_end( args );
   }

   return result;
}


// VScanf - Liest formatiert ueber Argumentliste aus einer Datei

#if (HAS_VSCANF == 1)
int cFile::VScanf( const char *fmt, va_list args )
{
   int result = EOF;

   if( !fmt ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else {
      result = vfscanf( File, fmt, args );
      if( result == EOF ) {
         cErrBase::ERR_TYPE err = ConvError( errno );
         if (err && (err != cErrFile::errEOF || (EclMode & ECL_MODE_NOEOFERR) == 0)) {
            throw cErrFile( err, *this );
         }
         // RaiseError( errno );
      }
   }

   return result;
}
#else
int cFile::VScanf( const char * /*fmt*/, va_list /*args*/ )
{
   throw cErrFile(cErrFile::errSorry, *this);
   return EOF;
}
#endif


// Ungetc - Schiebt ein Zeichen in eine Datei zurueck   -> ungetc

void cFile::Ungetc( int c )
{
   if( EOF == ungetc( c, File ) ) {
      throw cErrFile(cErrFile::errUnget, *this);
   }
}


// RawRead - Low-Level-Lesen aus einer Datei   -> read
//
// Liest <count> Bytes aus der angegebenen Datei
// Weder Modus noch Puffer werden beachtet, diese Routine
// ist Low-Level

size_t cFile::RawRead( void *ptr, size_t count )
{
   size_t result = (size_t) -1;

   if( !ptr || !count ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else {
      result = read( fileno(File), ptr, count );
      // Auszug aus der MSDN-Doku zu read():
      // If the function tries to read at end of file, it returns 0. If the
      // handle is invalid, or the file is not open for reading, or the file
      // is locked, the function returns -1 and sets errno to EBADF.
      // ALT: if( result != count && errno ) RaiseError( errno );
      if (result == (size_t) -1) {
         RaiseError(errno);
      } else if (result != count && (EclMode & ECL_MODE_NOEOFERR) == 0) {
         throw cErrFile( cErrFile::errEOF, *this );
      }
   }

   return result;
}


// RawWrite - Low-Level-Schreiben in eine Datei  -> write
//
// Schreibt <count> Bytes in die angegebenen Datei
// Weder Modus noch Puffer werden beachtet, diese Routine
// ist Low-Level

size_t cFile::RawWrite( void *ptr, size_t count )
{
   size_t result = (size_t) -1;

   if( !ptr || !count ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else {
      result = write( fileno(File), ptr, count );
      if( result != count ) RaiseError( errno );
   }

   return result;
}


// Isatty - Ist Handle ein zeichenorientiertes Geraet?  -> isatty

bool cFile::Isatty()
{
   return IsTTY;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cDir
// ---------------------------------------------------------------------------
//
// cBase
//  +--cDir
//
// ===========================================================================

#if defined  __ECL_GNUC__

   #include <io.h>
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <dirent.h>

#elif defined  __ECL_ICC__

   #include <io.h>
   #include <sys/stat.h>

   #define MAXNAMLEN  cFile::PATH_COMP_MAX
   #define MAXPATHLEN cFile::PATH_COMP_MAX
   #define A_RONLY   0x01
   #define A_HIDDEN  0x02
   #define A_SYSTEM  0x04
   #define A_LABEL   0x08
   #define A_DIR     0x10
   #define A_ARCHIVE 0x20

   struct ftime {
      unsigned int twosecs : 5;
      unsigned int minutes : 6;
      unsigned int hours   : 5;
   };

   struct fdate {
      unsigned int day     : 5;
      unsigned int month   : 4;
      unsigned int year    : 7;
   };

   struct dirent {
      int            d_ino;                 /* Almost not used           */
      int            d_reclen;              /* Almost not used           */
      int            d_namlen;              /* Length of d_name          */
      char           d_name[MAXNAMLEN + 1]; /* File name, 0 terminated   */
      unsigned long  d_size;                /* File size (bytes)         */
      unsigned long  d_attr;                /* OS file attributes        */
      struct ftime   d_time;                /* OS file modification time */
      struct fdate   d_date;                /* OS file modification date */
   };

#elif defined  __ECL_VCPP__

   #include <io.h>
   #include <sys\stat.h>

   #define MAXNAMLEN  cFile::PATH_COMP_MAX
   #define MAXPATHLEN cFile::PATH_COMP_MAX
   #define A_RONLY   0x01
   #define A_HIDDEN  0x02
   #define A_SYSTEM  0x04
   #define A_LABEL   0x08
   #define A_DIR     0x10
   #define A_ARCHIVE 0x20

   struct ftime {
      unsigned int twosecs : 5;
      unsigned int minutes : 6;
      unsigned int hours   : 5;
   };

   struct fdate {
      unsigned int day     : 5;
      unsigned int month   : 4;
      unsigned int year    : 7;
   };

   struct dirent {
      int            d_ino;                 /* Almost not used           */
      int            d_reclen;              /* Almost not used           */
      int            d_namlen;              /* Length of d_name          */
      char           d_name[MAXNAMLEN + 1]; /* File name, 0 terminated   */
      unsigned long  d_size;                /* File size (bytes)         */
      unsigned long  d_attr;                /* OS file attributes        */
      struct ftime   d_time;                /* OS file modification time */
      struct fdate   d_date;                /* OS file modification date */
   };

#else

   #error "Your compiler is not supported"

#endif

class __ECL_DLLEXPORT__ cDir : public cBase {

public:

   // Verzeichnis oeffnen
   cDir(const char *name);
   // Verzeichnis schliessen
   ~cDir();

   // Verzeichniseintrag (DirRead)
   typedef struct dirent DIR_ENTRY;


   // Funktionen auf Verzeichnis
   // ==========================

   // Eintrag lesen
   DIR_ENTRY *cDir::read();
   // Eintrag ansteuern
   void seek(long offset);
   // Nummer des aktuellen Eintrags
   long tell();
   // Zu erstem Eintrag zurueck
   void rewind();


   // Statische Funktionen
   // ====================

   // Aktuelles Arbeitsverzeichnis erfragen
   static cString getWorkingDir();
   // Aktuelles Arbeitsverzeichnis setzen
   static void setWorkingDir(cString dir);


private:

   void *Dir;        // Directory-Struktur
   cString Name;     // Directory-Name

   // Fehler generieren, Fehlercode aus errno
   void raiseError(int err_code);
   // Fehler generieren, Fehlercode aus errno (statische Version)
   static void raiseError(int err_code, const char *dirname);

};

#endif /*__INTERFACE__*/


// Implementierung cDir
// ===========================================================================


//
// Directory routines for IBM Compiler
//

#if __ICC__ && HAS_OPENDIR

// Attributes to search for
#ifndef DIR_ATTRIBUTES
   #define DIR_ATTRIBUTES  A_DIR | A_HIDDEN | A_SYSTEM
#endif

// Level of file information to retrieve (see DosFindFirst documentation)
#ifndef DIR_INFO_LEVEL
   #define DIR_INFO_LEVEL FIL_STANDARD
#endif

#if DIR_INFO_LEVEL == FIL_STANDARD
   #define FINDBUF FILEFINDBUF3
#elif DIR_INFO_LEVEL == FIL_QUERYEASIZE
   #define FINDBUF FILEFINDBUF4
   #error "Not yet implemented"
#elif DIR_INFO_LEVEL == FIL_QUERYEASFROMLIST
   #define FINDBUF FILEFINDBUF5
   #error "Not yet implemented"
#else
   #error "DIR_INFO_LEVEL incorrect"
#endif

struct _find {
   HDIR     handle;
   FINDBUF  buf;
};

struct _dircontents {
   char *         _d_entry;
   unsigned long  _d_size;
   unsigned long  _d_attr;
   struct ftime   _d_time;
   struct fdate   _d_date;
   struct _dircontents * _d_next;
};

struct _dirdesc {
   int                   dd_id;
   long                  dd_loc;
   struct _dircontents * dd_contents;
   struct _dircontents * dd_cp;
   struct dirent         dd_dirent;
   struct _find          dd_find;
};

typedef struct _dirdesc DIR;

// Unix compatibility
static int _readdir_ino = 31415926;

static char *getdirent (const char *dir, struct _find *pfind)
{
   APIRET rc;
   ULONG count = 1;

   if(dir != NULL) {
      pfind->handle = HDIR_CREATE;
      rc = DosFindFirst( dir, &pfind->handle, DIR_ATTRIBUTES,
                         (PVOID) &pfind->buf, sizeof(FINDBUF), &count, DIR_INFO_LEVEL );
   }
   else {
      rc = DosFindNext( pfind->handle, (PVOID) &pfind->buf, sizeof(FINDBUF), &count );
   }

   if(rc != 0) {
      DosFindClose( pfind->handle );
      return NULL;
   }

   return pfind->buf.achName;
}

static void free_dircontents (struct _dircontents *dp)
{
   struct _dircontents *odp;

   while(dp != NULL) {
      if(dp->_d_entry != NULL)
         free(dp->_d_entry);
      odp = dp;
      dp = dp->_d_next;
      free (odp);
   }
}

static int closedir (DIR *dirp)
{
   free_dircontents (dirp->dd_contents);
   free (dirp);
   return 0;
}

static struct dirent *readdir (DIR *dirp) {
   if(dirp->dd_cp == NULL)
      return NULL;
   strcpy (dirp->dd_dirent.d_name, dirp->dd_cp->_d_entry);
   dirp->dd_dirent.d_namlen = strlen (dirp->dd_dirent.d_name);
   dirp->dd_dirent.d_reclen = dirp->dd_dirent.d_namlen;
   dirp->dd_dirent.d_ino = _readdir_ino++;
   if(_readdir_ino == 0)
      _readdir_ino = 1;
   dirp->dd_dirent.d_size = dirp->dd_cp->_d_size;
   dirp->dd_dirent.d_attr = dirp->dd_cp->_d_attr;
   dirp->dd_dirent.d_time = dirp->dd_cp->_d_time;
   dirp->dd_dirent.d_date = dirp->dd_cp->_d_date;
   dirp->dd_cp = dirp->dd_cp->_d_next;
   ++dirp->dd_loc;
   return &dirp->dd_dirent;
}

static void seekdir (DIR *dirp, long off)
{
   long i;
   struct _dircontents *dp;

   if(off >= 0) {
      i = 0;
      for(dp = dirp->dd_contents; i < off && dp != NULL; dp = dp->_d_next)
         ++i;
      dirp->dd_loc = i;
      dirp->dd_cp = dp;
   }
   else
      errno = EINVAL;
}

static void rewinddir (DIR *dirp)
{
   seekdir (dirp, 0L);
}

static long telldir (DIR *dirp)
{
   return dirp->dd_loc;
}

static DIR *opendir(const char *name)
{
   struct stat statb;
   struct _find find;
   // FINDBUF *fbuf;
   DIR *dirp;
   char c;
   char *s;
   struct _dircontents *dp;
   char nbuf[MAXPATHLEN+1];
   int len;

   strcpy (nbuf, name);
   len = strlen (nbuf);
   s = nbuf + len;
   if(len > 0) {
      c = nbuf[len-1];
      if(c == '\\' || c == '/' || c == ':') {
         nbuf[len++] = '.';      /* s now points to '.' */
         nbuf[len] = 0;
      }
   }
   if(_stat (nbuf, &statb) < 0)
      return NULL;
   if(!(statb.st_mode & S_IFDIR)) {
      errno = EINVAL;
      return NULL;
   }
   dirp = (DIR *) malloc (sizeof (DIR));
   if(dirp == NULL) {
      errno = ENOMEM;
      return NULL;
   }
   if(*s == 0)
      *s++ = '\\';
   strcpy (s, "*.*");
   dirp->dd_loc = 0;
   dirp->dd_contents = NULL;
   dirp->dd_cp = NULL;
   s = getdirent (nbuf, &find);
   if(s == NULL) {
      errno = ENOMEM;
      return dirp;
   }
   do {
      dp = (struct _dircontents *) malloc (sizeof (struct _dircontents));
      if(dp == NULL) {
         free_dircontents (dirp->dd_contents);
         errno = ENOMEM;
         return NULL;
      }
      dp->_d_entry = (char *) malloc (strlen (s) + 1);
      if(dp->_d_entry == NULL) {
         free (dp);
         free_dircontents (dirp->dd_contents);
         errno = ENOMEM;
         return NULL;
      }
      if(dirp->dd_contents != NULL)
         dirp->dd_cp->_d_next = dp;
      else
         dirp->dd_contents = dp;
      dirp->dd_cp = dp;
      strcpy (dp->_d_entry, s);
      dp->_d_next = NULL;
      dp->_d_size = find.buf.cbFile;
      dp->_d_attr = find.buf.attrFile;
      dp->_d_time.twosecs = find.buf.ftimeLastWrite.twosecs;
      dp->_d_time.minutes = find.buf.ftimeLastWrite.minutes;
      dp->_d_time.hours   = find.buf.ftimeLastWrite.hours;
      dp->_d_date.day     = find.buf.fdateLastWrite.day;
      dp->_d_date.month   = find.buf.fdateLastWrite.month;
      dp->_d_date.year    = find.buf.fdateLastWrite.year;
      s = getdirent (NULL, &find);
   } while(s != NULL);
   dirp->dd_cp = dirp->dd_contents;
   return dirp;
}

#endif   // __ICC__ && HAS_OPENDIR


#if HAS_OPENDIR

// Implementierung cDir
// ---------------------------------------------------------------------------


// cDir - Konstruktor

cDir::cDir( const char *name )
{
   Dir = NULL;
   Name = "";

   if( !name || !*name ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else {
      Name = name;
      Dir = (void *) opendir( name );
      if( !Dir ) raiseError( errno );
   }
}


// ~cDir - Destruktor

cDir::~cDir()
{
   if( Dir ) closedir( (DIR *) Dir );
}


// DirRead - Lesen eines Verzeichniseintrags  -> readdir

cDir::DIR_ENTRY *cDir::read()
{
   #ifdef __readdir_throws_out_error__
      DIR_ENTRY *de = NULL;
      if( NULL == (de = readdir( (DIR *) Dir )) ) {
         throw cErrFile(cErrFile::errNoMatch, *this);
      }
      return de;
   #else
      return readdir( (DIR *) Dir );
   #endif
}


// DirSeek - Bestimmten Verzeichniseintrag ansteuern   -> seekdir

void cDir::seek( long offset )
{
   if( offset < 0 ) {
      throw cErrFile(cErrFile::errIllParam, *this);
   } else {
      seekdir( (DIR *) Dir, offset );
   }
}


// DirTell - Liefert die aktuelle Verzeichnisposition  -> telldir

long cDir::tell()
{
   return telldir( (DIR *) Dir );
}


// DirRewind - "Zurueckspulen" eines Verzeichnisses  -> rewinddir

void cDir::rewind()
{
   seek( 0 );
}
#endif // HAS_OPENDIR


void cDir::raiseError(int err_code)
{
   cErrBase::ERR_TYPE err = ConvError(err_code);
   if ( err ) throw cErrFile(err, *this);
}

void cDir::raiseError(int err_code, const char *dirname)
{
   cErrBase::ERR_TYPE err = ConvError(err_code);
   if ( err ) throw cErrFile(err, dirname);
}

cString cDir::getWorkingDir()
{
   char dir[512];

   #if defined __ECL_VCPP__
      if ( _getcwd(dir, sizeof dir) == 0 )
         raiseError(errno, ".");
   #endif

   cFile::MakeDirName(dir);
   return cString(dir);
}

void cDir::setWorkingDir(cString dir)
{
   #if defined __ECL_VCPP__
      if ( _chdir(dir) != 0 )
         raiseError(errno, dir);
   #endif
}




// ===========================================================================
// Deklaration cFileFind
// ---------------------------------------------------------------------------
//
// cBase
//    +--cFileFind
//
// Erweiterungsideen:
//
// -  Mit den vordefinierten Masken koennen bis jetzt nur SICHTBARE Dateien
//    gesucht werden. Man koennte zusaetzliche Bits definieren, die Hidden-
//    und System-Dateien durch Maskenanpassung ebenfalls zugaenglich machen.
//
// -  Diesen und andere zusaetziche Suchparameter koennte man nach der
//    Instanziirung und vor der Suchschliefe mit findNext() durch eine
//    geeignete Methode einstellbar machen.
//
// -  Thomas wuenscht sich eine Variante, mit der "nur" die Verzeichnisstruktur
//    herausgefunden werden kann (Unix: rekursiv nach "." suchen) - knifflig.
//
// -  Man koennte die Suchtiefe beschraenkbar machen.
//
// -  Aufrufvarianten mit der Schleife innerhalb der Klasse, die a) eine
//    Callback-Funktion oder b) eine virtuellen Funktion aufruft.
//

#ifdef __INTERFACE__

class __ECL_DLLEXPORT__ cFileFind : public cBase {
private:
   cString  file_name;
   cString  file_path;
   long     file_size;
   int      file_attr;
   time_t   file_date;

public:
   enum {
      ATTR_READONLY  = 0x01,
      ATTR_HIDDEN    = 0x02,
      ATTR_SYSTEM    = 0x04,
      ATTR_DIRECTORY = 0x10,
      ATTR_ARCHIVE   = 0x20,

      MASK_ALL       = 0x0600,   // sichtbare Verzeichnisse und Dateien
      MASK_FILE      = 0x1600,   // sichtbare Dateien
      MASK_DIR       = 0x1610    // sichtbare Verzeichnisse
   };

   cFileFind(cString _files, int _mask=MASK_FILE);
   cFileFind(cString _files, cString _dirs);
   ~cFileFind();

   // naechste passende Datei suchen, false falls es keine mehr gibt
   bool findNext();
   bool easy_find_next();

   // Name der gefundenen Datei
   cString getFullName() { return ff_tail->file_name; }
   // Pfad der gefundenen Datei
   cString getPath() { return ff_tail->file_path; }
   // Pfad und Name der gefundenen Datei
   cString getFileSpec() { return ff_tail->file_path+ff_tail->file_name; }
   // Laenge der gefundenen Datei
   long getSize()    { return ff_tail->file_size; }
   // Attribute der gefundenen Datei
   int getAttr()     { return ff_tail->file_attr; }
   // Datum der gefundenen Datei
   time_t getDate()  { return ff_tail->file_date; }

   // Attribute gezielt pruefen
   bool isReadOnly() { return (ff_tail->file_attr & ATTR_READONLY) != 0; }
   bool isHidden()   { return (ff_tail->file_attr & ATTR_HIDDEN) != 0; }
   bool isSystem()   { return (ff_tail->file_attr & ATTR_SYSTEM) != 0; }
   bool isDir()      { return (ff_tail->file_attr & ATTR_DIRECTORY) != 0; }
   bool isArchive()  { return (ff_tail->file_attr & ATTR_ARCHIVE) != 0; }

private:
   enum {
      STATE_FIRST,
      STATE_NEXT,
      STATE_DONE
   } find_state;
   int find_mask;

   // --- Parameter fuer die rekursive Durchwanderungsvariante
   //     (walk_mode, ff_last & ff_tail zur Erkennung und Durchfuehrung der
   //     einstufigen Suche)
   enum {
      WALK_OFF,   // Deaktiviert
      WALK_FILES, // Suche nach Dateien
      WALK_DIRS   // Suche nach Verzeichnissen
   } walk_mode;
   cFileFind *ff_tail;  // Aktuelle und tiefste Suchebene
   cFileFind *ff_last;  // vorangegangene Suchebene

   cString walk_path,walk_file_pattern,walk_dir_pattern;
   bool walk_find_next();
public:
   void walk_set_last(cFileFind *ff) { ff_last = ff; }
   // --- Ende der mehrstufigen Erweiterung

private:
   // Fehlercode fuer _first() und _next()
   enum {
      FIND_OK,
      FIND_NO_MATCH,
      FIND_ILL_PARAM
   };
   // Die Funktionen _first(), _next() und _close() stellen (bis jetzt) die
   // Schnittstelle zum verwendeten Betriebssystem/Compiler dar.
   #if defined __ECL_VCPP__
      long _handle;
   #elif defined __ECL_ICC__
      // TBD ...
   #endif

   // find_pattern x find_attr --> _handle x find x error
   int _first(const char *pattern, int mask);
   // find_handle -> find x error
   int _next();
   // find_handle -> %
   void _close();
};

#endif /*__INTERFACE__*/


// Implementierung cFileFind
// ===========================================================================

#if defined __ECL_VCPP__

   int cFileFind::_first(const char *pattern, int /*attr*/)
   {
      _finddata_t find;

      _handle = _findfirst( pattern, &find );
      if (_handle != -1) {
         file_name = find.name;
         file_size = find.size;
         file_attr = find.attrib;
         file_date = find.time_write;
         return FIND_OK;
      } else {
         return errno==ENOENT ? FIND_NO_MATCH : FIND_ILL_PARAM;
      }
   }

   int cFileFind::_next()
   {
      _finddata_t find;

      if (_findnext( _handle, &find ) == 0) {
         file_name = find.name;
         file_size = find.size;
         file_attr = find.attrib;
         file_date = find.time_write;
         return FIND_OK;
      } else {
         return FIND_NO_MATCH;
      }
   }

   void cFileFind::_close()
   {
      if (_handle != -1) {
         _findclose( _handle );
      }

   }

#elif defined __ECL_ICC__


   int cFileFind::_first(const char *pattern, int attr)
   {
      return FIND_ILL_PARAM;
   }

   int cFileFind::_next()
   {
      return FIND_NO_MATCH;
   }

   void cFileFind::_close()
   {
   }

#endif


// Einstufige Suche
// ---------------------------------------------------------------------------

cFileFind::cFileFind(cString _files, int _mask)
{
   ff_tail = this;
   ff_last = NULL;
   walk_mode = WALK_OFF;

   file_path = cFile::GetPath(_files);
   find_mask = _mask;

   switch (_first((const char *)_files, _mask)) {
   case FIND_ILL_PARAM:
      throw cErrFile(cErrFile::errIllParam, (const char *)_files);
   case FIND_NO_MATCH:
      find_state = STATE_DONE;
      break;
   case FIND_OK:
      find_state = STATE_FIRST;
      break;
   }
}


cFileFind::~cFileFind()
{
   while (ff_tail->ff_last) {
      cFileFind *ff = ff_tail->ff_last;
      ff_tail->ff_last = NULL;
      delete ff_tail;
      ff_tail = ff;
   }
}


bool cFileFind::findNext()
{
   if (ff_tail->walk_mode != WALK_OFF) {
      return walk_find_next();
   } else {
      return easy_find_next();
   }
}

bool cFileFind::easy_find_next()
{
   int err;

   if (find_state != STATE_DONE) {
      err = (find_state == STATE_FIRST) ? FIND_OK : _next();
      while (err == FIND_OK) {
         if ( (getAttr() & find_mask>>8) == (find_mask & 0x3F) &&
              (!isDir() || (getFullName() != "." && getFullName() != "..")) ) {
            find_state = STATE_NEXT;
            return true;
         }
         err = _next();
      }
      find_state = STATE_DONE;
   }
   // Resultatparameter loeschen
   file_name = "";
   file_size = 0;
   file_attr = 0;
   return false;
}


// Mehrstufige (rekursive) Suche
// ---------------------------------------------------------------------------

cFileFind::cFileFind(cString _files, cString _dirs)
{
   walk_file_pattern = cFile::GetFullName(_files);
   walk_dir_pattern = cFile::GetFullName(_dirs);
   walk_path = cFile::GetPath(_files);
   walk_mode = WALK_OFF;

   if (walk_path.getLength()) {
      if (cFile::GetPath(_dirs).getLength()) {
         throw cErrFile(cErrFile::errIllParam, (const char *)_dirs);
      }
   } else {
      walk_path = cFile::GetPath(_dirs);
   }

   ff_last = NULL;
   ff_tail = new0 cFileFind(walk_path+walk_dir_pattern, MASK_DIR);
   delete ff_tail;

   ff_tail = new0 cFileFind(walk_path+walk_file_pattern, MASK_FILE);
   ff_tail->walk_mode = WALK_FILES;
   ff_tail->ff_last = this;
}


bool cFileFind::walk_find_next()
{
   cFileFind *ff;
   bool abort = false;

   while ( !abort ) {

      switch (ff_tail->walk_mode) {

      case WALK_FILES:
         if (ff_tail->easy_find_next()) { return true; }
         // alle Dateien durch ...
         ff = ff_tail->ff_last;
         ff_tail->ff_last = NULL;
         delete ff_tail;
         ff_tail = ff;

         // ... jetzt die Verzeichnisse vornehmen
         if (ff_tail == this) {
            ff = new0 cFileFind(walk_path+walk_dir_pattern, MASK_DIR);
         } else {
            ff = new0 cFileFind(ff_tail->getFileSpec()+File_SEPARATOR+walk_dir_pattern, MASK_DIR);
         }
         ff->walk_mode = WALK_DIRS;
         ff->ff_last = ff_tail;
         ff_tail = ff;
         break;

      case WALK_DIRS:
         if (ff_tail->easy_find_next()) {
            // neues Unterverzeichnis gefunden
            try {
               ff = new0 cFileFind(ff_tail->getFileSpec()+File_SEPARATOR+walk_file_pattern, MASK_FILE);
               ff->walk_mode = WALK_FILES;
               ff->ff_last = ff_tail;
               ff_tail = ff;
            } catch (cErrBase err) {

            }
         } else {
            ff = ff_tail->ff_last;
            ff_tail->ff_last = NULL;
            delete ff_tail;
            ff_tail = ff;
         }
         break;

      case WALK_OFF:
         // wieder ganz oben gelandet -> Suche beendet
         abort = true;
      }
   }

   return false; // Aufwandsabschaetzung bis zu dieser Stelle: O(unendlich)
}

