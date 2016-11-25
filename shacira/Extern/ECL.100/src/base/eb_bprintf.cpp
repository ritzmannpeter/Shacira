// ===========================================================================
// eb_bprintf.cpp                                ECL (ET's tiny Class Library)
//                                                         Autor: Norman Bring
// ---------------------------------------------------------------------------
//
// Dieses kleine, aber feine Modul stellt die folgenden FUNKTIONEN
// zur Verfuegung:
//
//    bprintf  - Binary Print Formatted
//    vbprintf - Variable Binary Print Formatted
//
// Diese arbeiten aehnlich wie sprintf und vsprintf aus der Standard-"C"-
// Bibliothek, erzeugen aber aus den angegebenen Argumenten keinen String
// sondern Binaerdaten.
//
// ===========================================================================

#include "base/eb_bprintf.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>




#ifdef __INTERFACE__

#include <stddef.h>
#include <stdarg.h>

#include "base/eb_base.hpp"

int __ECL_DLLEXPORT__ vbprintf( void *buf, const char *fmt, va_list ap );
int __ECL_DLLEXPORT__ bprintf( void *buf, const char *fmt, ... );

#endif  /* __INTERFACE__ */




/*.Sf.***********************************************************************
*
*  FUNKTION:
*     GetArg - Liest ein durch einen Platzhalter beschriebenes Argument
*
*  AUFRUF:
*     result = GetArg( desc, p, ap_ptr );
*
*  PARAMETER:
*     result RESULT [int] - Anzahl aus dem Formatstring gelesener Zeichen
*     desc IN [char] - Platzhalter
*     p IN [unsigned char **] - Adresse eines Zeigers auf den Zielpuffer
*     ap_ptr IN [va_list *] - Aktueller Argumentzeiger
*
*  FEHLER:
*     Liefert 0, falls ein falscher Platzhalter oder ein ungueltiges Argument
*     gefunden wurde
*
*  REFERENZEN:
*
**.Ef.***********************************************************************/

#define GET_ARG( type )\
    { *(type *) buf = va_arg( *ap, type );   \
      memcpy( *p, buf, sizeof(type) );        \
      *p += sizeof(type);                     \
    }

static int GetArg( char desc, unsigned char **p, va_list *ap )
{
   unsigned char buf[10];

   switch ( desc ) {
    case '%': *(*p)++ = '%'; break;
    case 'c': GET_ARG( unsigned char ); break;
    case 'i': GET_ARG( short ); break;
    case 'd':
    case 'u': GET_ARG( int ); break;
    case 'l': GET_ARG( long ); break;
    case 'f': GET_ARG( double ); break;
    case 't': {
      size_t len = va_arg( *ap, size_t );
      void * adr = va_arg( *ap, void * );

      if( len ) {
         if( adr == NULL ) return 0;
         memcpy( *p, adr, len );
         *p += len;
      }
      break;
    }
    case 's': {
      char *str = va_arg( *ap, char * );
      strcpy( (char *) *p, str );
      *p += strlen( str ) + 1;
      break;
    }
    default :
      /* Unbekannter Platzhalter */
      return 0;
   }

   return 1;
}


/*.Sf.***********************************************************************
*
*  FUNKTION:
*     GetEscape - Liest eine Escapesequenz aus dem Formatstring
*
*  BESCHREIBUNG:
*     Im Moment wird nur die Angabe einer dreistelligen Dezimal- oder einer
*     zweistelligen Hexadezimalzahl akzeptiert. Das entsprechende ASCII-Zeichen
*     wird in den Zielpuffer uebertragen.
*     Das Escapezeichen '#' kann durch '##' erreicht werden.
*
*  AUFRUF:
*     result = GetEscape( s, p );
*
*  PARAMETER:
*     result RESULT [int] - Anzahl der aus dem Formatstring gelesenen Zeichen
*     s IN [char *] - Zeiger auf Position hinter Backslash
*     p IN [unsigned char **] - Adresse eines Zeigers auf den Zielpuffer
*
*  FEHLER:
*     Liefert 0, falls keine gueltige Zahl erkannt wurde
*
*  REFERENZEN:
*
**.Ef.***********************************************************************/

static int GetEscape( char *s, unsigned char **p )
{
   char buf[4];
   int base = 10;
   unsigned long l;

   if( *s == '#' ) {
      *(*p)++ = '#';
      return 1;
   }

   buf[0] = '\0';
   strncat( buf, s, 3 );
   s = buf;
   if( *s == 'x' ) {
      s++; base = 16;
   }

   l = strtoul( s, &s, base );
   if( l == ULONG_MAX || l > 255 || *s != '\0' /*|| *s != '0'*/ ) {
      return 0;
   }

   *(*p)++ = (unsigned char) l;

   return 3;
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     vbprintf - Variable Binary Printf
*
*  BESCHREIBUNG:
*     Schreibt die ueber den Formatstring beschriebenen Daten der Argument-
*     liste in den angegebenen Puffer.
*
*  AUFRUF:
*     result = vbprintf( buf, fmt, ap );
*
*  PARAMETER:
*     result RESULT [int] - Anzahl der geschriebenen Zeichen (EOF bei Fehler)
*     buf IN [void *] - Adresse eines ausreichend dimensionierten Puffers
*     fmt IN [const char *] - Formatstring (s. bprintf)
*     ap IN [va_list] - Argumentliste
*
*  REFERENZEN:
*     GetArg [GLOBAL]
*     GetEscape [GLOBAL]
*
**.EF.***********************************************************************/

int vbprintf( void *buf, const char *fmt, va_list ap )
{
   unsigned char *ptr;
   int len;

   /* Argumente pruefen */
   if( buf == NULL || fmt == NULL ) return EOF;

   ptr = (unsigned char *) buf;

   while( *fmt != '\0' ) {
      len = 0;
      switch ( *fmt ) {
       case '%' : len = GetArg( *(++fmt), &ptr, &ap ); break;
       case '#' : len = GetEscape( (char *) ++fmt, &ptr ); break;
       default  : *ptr++ = (unsigned char) *fmt; len = 1;
      }
      if( len == 0 ) {
         /* Err_Collect( ??? , ??? ); */
         return EOF;
      }
      fmt += len;
   }

   return (int) (ptr - (unsigned char *) buf);
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     bprintf - Binary Printf
*
*  BESCHREIBUNG:
*     Schreibt die ueber den Formatstring beschriebenen Argumente
*     in den angegebenen Puffer.
*
*     Unterstuetzte Platzhalter im Formatstring:
*        %c    : ein Zeichen (oder Byte)                    1 Byte
*        %i    : ein short (oder USHORT)                    2 Byte
*        %u, %d: ein Wort (oder WORD)                       4 Byte
*        %l    : ein Langwort                               4 Byte
*        %f    : eine Realzahl (immer double)               8 Byte
*        %s    : Adresse eines nullterminierten Strings
*        %t    : Adresse einer Struktur mit vorangehender Groessenangabe (size_t)
*        %%    : das Zeichen '%'
*        #ddd  : dezimale Angabe eines Zeichens
*        #xhh  : hexadezimale Angabe eines Zeichens
*        ##    : das Zeichen '#'
*
*     Beispiel:
*        len = bprintf( buf,
*                 "%cText geht auch#000%t%l",
*                 'X', sizeof(test_struct), &test_struct, 42L );
*
*  AUFRUF:
*     result = bprintf( buf, fmt, usw. usw.  );
*
*  PARAMETER:
*     result RESULT [int] - Anzahl der geschriebenen Zeichen (EOF bei Fehler)
*     buf IN [void *] - Adresse eines ausreichend dimensionierten Puffers
*     fmt IN [const char *] - Formatstring (s. bprintf)
*     usw. usw. IN [bel.] - Parameter (wenn's geht) passend zum Formatstring
*
*  REFERENZEN:
*
**.EF.***********************************************************************/

int bprintf( void *buf, const char *fmt, ... )
{
   va_list ap;
   int res;

   va_start( ap, fmt );
   res = vbprintf( buf, fmt, ap );
   va_end( ap );

   return res;
}


/*.SL.*/
#ifdef TEST
typedef struct {
   int i;
   long l;
   char s[12];
   double wutz;
} TEST_STRUCT;


int main( void )
{
   static unsigned char buf[500];
   int result;
   TEST_STRUCT t = { 1, 2, "Hoppla", 0.0 };

   result = bprintf( buf,
		     "%u Du des %s#x20jetzt ein Tescht#032%tEnde#000",
		     0x42, "isch", sizeof(t), &t );
   result = bprintf( buf, "%u", 0x1234 );
   result = bprintf( buf, "" );
   result = bprintf( buf, "%f", 42.42 );

   printf( "Result is %d\n", result );

   return 0;
}
#endif
/*.EL.*/
