


#ifdef __INTERFACE__

class cTomTools {

};

/**.SC.***********************************************************************
*
*  MACRONAME:
*     ToTo_PUSH - Variable auf Stack sichern
*     ToTo_POP - Variable von Stack holen
*
*  AUFRUF
*     ToTo_PUSH( type, ptr, minlen, token )
*     ToTo_POP( type, ptr, minlen, token )
*
*  PARAMETER:
*     type IN [int] - Variablentyp
*     ptr IN [void*] - Zeiger auf Variable
*     minlen IN [int] - signifikante Laenge
*     token IN [char*] - Tokenstring
*
*  BEMERKUGEN:
*     Es werden alle Datentypen ausser _TEXT und _STR unterstuetzt.
*
**.EC.***********************************************************************/

#define ToTo_PUSH( type , varptr , min , token ) \
   Tom_UWP( ToTo_Push , (type) , (varptr) , (min) , (token) )

#define ToTo_POP( type , varptr , min , token ) \
   Tom_UWP( ToTo_Pop , (type) , (varptr) , (min) , (token) )


/**.SC.***********************************************************************
*
*  MACRONAME:
*     ToTo_ADR - Variablenadresse ausgeben
*
*  AUFRUF
*     ToTo_ADR( type, ptr, minlen, token )
*
*  PARAMETER:
*     type IN [int] - Variablentyp
*     ptr IN [void*] - Zeiger auf Variable
*     minlen IN [int] - signifikante Laenge
*     token IN [char*] - Tokenstring
*
**.EC.***********************************************************************/

#define ToTo_ADR( type , varptr , min , token ) \
   Tom_UWP( ToTo_Adr , (type) , (varptr) , (min) , (token) )


/* --- Funktionen der offiziellen Schnittstelle --- */
__ECL_EXP1__ void __ECL_EXP2__ ToTo_Init ( void );
__ECL_EXP1__ void __ECL_EXP2__ ToTo_Exit ( void );
__ECL_EXP1__ char * __ECL_EXP2__ ToTo_Push ( char* , Tom_TYPE* );
__ECL_EXP1__ char * __ECL_EXP2__ ToTo_Pop ( char* , Tom_TYPE* );
__ECL_EXP1__ char * __ECL_EXP2__ ToTo_Adr ( char* , Tom_TYPE* );
__ECL_EXP1__ char * __ECL_EXP2__ ToTo_Tree ( char* , Tom_TYPE* );
__ECL_EXP1__ void __ECL_EXP2__ ToTo_View ( char* , int , void* );

__ECL_EXP1__ const Tom_TYPE * __ECL_EXP2__ ToTo_Root ( );
__ECL_EXP1__ const Tom_TYPE * __ECL_EXP2__ ToTo_VarOp ( );
__ECL_EXP1__ const Tom_TYPE * __ECL_EXP2__ ToTo_MaskOp ( );

#endif /*__INTERFACE__*/


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "tom/et_tomate.hpp"
#include "tom/et_tools.hpp"

#define LG_GERMAN    0
#define LG_ENGLISH   1
#define LANGUAGE     LG_GERMAN


/*.SL.*/

/*
 *
 * --- lokale Datentypen ---
 *
 */

/* Union fuer ein einzelnes Stack-Element: */
typedef union {
   char           v_char;
   short          v_short;
   int            v_int;     /* auch fuer _ENUM, _BOOL */
   long           v_long;
   unsigned char  v_uchar;
   unsigned short v_ushort;
   unsigned int   v_uint;
   unsigned long  v_ulong;
   bool           v_bool;
   void          *v_PTR;
   float          v_float;
   double         v_double;
   long double    v_ldouble;
} TT_STACK;



/*
 *
 * --- Konfigurations-Konstanten ---
 *
 */
#define TT_STK_MAX 32          /* maximale Tiefe des ToTo-Stacks */



/*
 *
 * --- lokale Variable ---
 *
 */
static TT_STACK TTStack[TT_STK_MAX];    /* Feld fuer Stack */
static int TTSp = 0;                        /* Stackpointer */



/*
 *
 * --- Prototypen der lokalen Funktionen ---
 *
 */
static void ToToTree ( Tom_TYPE*, int );



/*.SF.***********************************************************************
*
*  FUNKTION:
*     ToTo_Init - Tom-Tools initialisieren
*
*  BESCHREIBUNG:
*     Variablen-Stack initialisieren (ToTo_PUSH/POP)
*
*  AUFRUF:
*     ToTo_Init();
*
*  REFERENZEN:
*     TTSp [GLOBAL]
*
**.EF.***********************************************************************/

void ToTo_Init( void )
{
   //TTSp = 0;
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     ToTo_Exit - Tom-Tools deinitialisieren
*
*  AUFRUF:
*     ToTo_Exit();
*
*  REFERENZEN:
*
**.EF.***********************************************************************/

void ToTo_Exit( void )
{
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     ToTo_Push - Wert auf Stack ablegen
*     ToTo_Pop - Wert von Stack holen
*
*  AUFRUF:
*     result = ToTo_Push( line, tt );
*     result = ToTo_Pop( line, tt );
*
*  PARAMETER:
*     result RESULT [char *] - NULL bei Fehlern, sonst line zurueck.
*     line IN [char *] - Textzeiger fuer result.
*     tt IN [Tom_TYPE *] - Tabelleneintrag mit:
*        tt->value - Konstante mit dem Variablentyp
*        (???)tt->ptr1 - Zeiger auf Variable
*
*  REFERENZEN:
*     TTSp [GLOBAL]
*     TTStack [GLOBAL]
*     TTsizeof [GLOBAL]
*
*  BEMERKUNGEN:
*     Der Benutzer ist dafuer verantwortlich, dass die Datentypen auf dem
*     Stack in der gleichen Reihenfolge ausgelesen werden, wie sie auch
*     eingeschrieben wurden.
*
**.EF.***********************************************************************/

char *ToTo_Push( char *line , Tom_TYPE *tt )
{
   const int *TTsizeof = cTomate::getTomSizes();

   if ((TTSp+1) < TT_STK_MAX) {
      memcpy( &TTStack[TTSp++], tt->ptr1 , TTsizeof[tt->value] );
   } else {
      Tom_printf( "ToTo_Push: Stack overflow\n" );
      line = NULL;
   }

   return line;
}


char *ToTo_Pop( char *line , Tom_TYPE *tt )
{
   const int *TTsizeof = cTomate::getTomSizes();

   if (TTSp) {
      memcpy( tt->ptr1 , &TTStack[--TTSp] , TTsizeof[tt->value] );
   } else {
      Tom_printf( "ToTo_Pop: Stack empty\n" );
      line = NULL;
   }

   return line;
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     ToTo_Adr - Adresse einer Variablen ausgeben
*
*  AUFRUF:
*     result = ToTo_Adr( line, tt );
*
*  PARAMETER:
*     result RESULT [char *] - line zurueck.
*     line IN [char *] - Textzeiger fuer result.
*     tt IN [Tom_TYPE *] - Tabelleneintrag mit:
*        tt->value - Konstante mit dem Variablentyp
*        (???)tt->ptr1 - Zeiger auf Variable
*
*  REFERENZEN:
*     Tom_NAMES [EXTERN TYPE FROM TOMATE]
*
**.EF.***********************************************************************/

char *ToTo_Adr( char *line , Tom_TYPE *tt )
{
   Tom_printf( "Location: %p\n",
               (tt->value == _ENUM || tt->value == _MASK)
               ? ((Tom_NAMES*)tt->ptr1)->var : tt->ptr1 );

   return line;
}


/**.SV.***********************************************************************
*
*  VARIABLENNAME:
*     ToTo_VarOp - Tom-Tabelle Standard-Befehle fuer Variablen
*     ToTo_MaskOp - ... fuer Bitmasken
*
*  BESCHREIBUNG:
*     Benutzt werden diese Tabellen mit dem Tom_WITH-Macro, z.B.:
*     Tom_WITH( _WORD, &Counter, ToToVarOp, 1,"Cnt ... - irgendein Zaehler" )
*
*  VARIABLENTYP:
*     [ARRAY ? OF Tom_TYPE]
*
**.EV.***********************************************************************/

const Tom_TYPE ToToMaskOp[] = {
#if LANGUAGE == LG_GERMAN
   Tom_COMMENT( "----- Standard-Operationen fuer Bitmasken:" )
   Tom_VIEW( 0  , NULL ,  1,"View - anzeigen" )
   ToTo_PUSH( 0 , NULL ,  2,"PUsh - auf dem Stack sichern" )
   ToTo_POP( 0  , NULL ,  2,"POp - vom Stack holen" )
   ToTo_ADR( 0  , NULL ,  1,"Adr - Adresse der Variable" )
   Tom_RESET( 0 , NULL ,  1,"- ruecksetzen einer Maske" )
   Tom_SET( 0   , NULL ,  1,"+ setzen einer Maske" )
   Tom_SET( 0   , NULL ,  0,"('+' ist optional)" )
#endif
#if LANGUAGE == LG_ENGLISH
   Tom_COMMENT( "----- standard functions on bit-masks:" )
   Tom_VIEW( 0  , NULL ,  1,"View - show value" )
   ToTo_PUSH( 0 , NULL ,  2,"PUsh - save to stack" )
   ToTo_POP( 0  , NULL ,  2,"POp - restore from stack" )
   ToTo_ADR( 0  , NULL ,  1,"Adr - show address" )
   Tom_RESET( 0 , NULL ,  1,"- reset mask" )
   Tom_SET( 0   , NULL ,  1,"+ set mask" )
   Tom_SET( 0   , NULL ,  0,"('+' is optional)" )
#endif
   Tom_ENDE()
};

__ECL_EXP1__ const Tom_TYPE * __ECL_EXP2__ ToTo_MaskOp ( )
   { return ToToMaskOp; }

const Tom_TYPE ToToVarOp[] = {
#if LANGUAGE == LG_GERMAN
   Tom_COMMENT( "----- Standard-Operationen auf Variablen:" )
   Tom_VIEW( 0  , NULL ,  1,"View - anzeigen" )
   ToTo_PUSH( 0 , NULL ,  2,"PUsh - auf dem Stack sichern" )
   ToTo_POP( 0  , NULL ,  2,"POp - vom Stack holen" )
   ToTo_ADR( 0  , NULL ,  1,"Adr - Adresse der Variable" )
   Tom_SET( 0   , NULL ,  1,"Set <int> - setzen eines Wertes" )
   Tom_SET( 0   , NULL ,  0,"(Eingabe von 'Set' ist optional)" )
#endif
#if LANGUAGE == LG_ENGLISH
   Tom_COMMENT( "----- standard functions on variables:" )
   Tom_VIEW( 0  , NULL ,  1,"View - show value" )
   ToTo_PUSH( 0 , NULL ,  2,"PUsh - save to stack" )
   ToTo_POP( 0  , NULL ,  2,"POp - restore from stack" )
   ToTo_ADR( 0  , NULL ,  1,"Adr - show address" )
   Tom_SET( 0   , NULL ,  1,"Set <int> - change value" )
   Tom_SET( 0   , NULL ,  0,"('Set' is optional)" )
#endif
   Tom_ENDE()
};

__ECL_EXP1__ const Tom_TYPE * __ECL_EXP2__ ToTo_VarOp ( )
   { return ToToVarOp; }


/*.Sf.***********************************************************************
*
*  FUNKTION:
*     ToToTree - Tomate-Tabelle mit Anhaengseln ausgeben
*
*  AUFRUF:
*     ToToTree( base, level );
*
*  PARAMETER:
*     base IN [Tom_TYPE *] - Zeiger auf die Wurzel der Hauptstruktur
*     level IN [int] - Tiefenzaehler, muss beim Aufrum immer 1 sein!
*
*  BEMERKUNGEN:
*     Die Tree-Funktion war zuletzt als '%tree' in der Tomate verfuegbar.
*
**.Ef.***********************************************************************/

#define TOM_MAX_TREE 50
static Tom_TYPE *TomNodes[TOM_MAX_TREE];

static void ToToTree( Tom_TYPE *base , int level )
{
   int i;
   TomNodes[level] = base;

   for (i=1; i<level; i++) {
      if (TomNodes[i] == base) {
         while (i-- > 1) {
            Tom_printf( "|   " );
         }
         Tom_printf( "|<---- REKURSION !!!\n" );
         return;
      }
   }

   if (base == NULL) {
      for (i=0; i<level; i++) {
         Tom_printf( "|   " );
      }
      Tom_printf( " NULL !!!\n" );
      return;
   }

   while (base->minlen != cTomate::TOM_ENDE) {
      for (i=0; i<level; i++) {
         Tom_printf( "|   " );
      }
      if (base->token) {
         Tom_printf( "%s  ",base->token );
      }
      if (base->func == cTomate::_Param) {
         Tom_printf( "[Param]\n" );
         ToToTree( (Tom_TYPE*)base->ptr1 , level+1 );
      } else if (base->func == cTomate::_Level) {
         Tom_printf( "[Level]\n" );
         ToToTree( (Tom_TYPE*)base->ptr1 , level+1 );
      } else if (base->func == cTomate::_With) {
         /* Der wegen der DLL-Probleme eingeflickete Workaround mit Funktionen fuer die
            ToTo_MaskOp bzw. ToTo_VarOp Tabellen muß extra abgefragt werden */
         if ((Tom_TYPE*)base->ptr2 == ToToVarOp || base->ptr2 == (void*)&ToTo_VarOp) {
            Tom_printf( "[With ToTo_VarOp]\n" );
         } else if ((Tom_TYPE*)base->ptr2 == ToToMaskOp || base->ptr2 == (void*)&ToTo_MaskOp) {
            Tom_printf( "[With ToTo_MaskOp]\n" );
         } else {
            Tom_printf( "[With]\n" );
            ToToTree( (Tom_TYPE*)base->ptr2 , level+1 );
         }
      } else if (base->func == cTomate::_Dummy) {
         if (base->minlen == cTomate::TOM_DUMMY) {
            Tom_printf( "[Comment]\n" );
         } else {
            Tom_printf( "[Dummy]\n" );
         }
      } else if (base->func == cTomate::_Alias) {
         Tom_printf( "[Alias]\n" );
      } else if (base->func == cTomate::_Script) {
         Tom_printf( "[Script]\n" );
         ToToTree( (Tom_TYPE*)base->ptr2 , level+1 );
      } else if (base->func == cTomate::_View) {
         Tom_printf( "[View]\n" );
         if (base->value == _ENUM) {
            ToToTree( (Tom_TYPE*)base->ptr2 , level+1 );
         } else if (base->value == _MASK) {
            ToToTree( (Tom_TYPE*)base->ptr2 , level+1 );
         }
      } else if (base->func == cTomate::_Set) {
         Tom_printf( "[Set]\n" );
         if (base->value == _ENUM) {
            ToToTree( (Tom_TYPE*)base->ptr2 , level+1 );
         } else if (base->value == _MASK) {
            ToToTree( (Tom_TYPE*)base->ptr2 , level+1 );
         }
      } else if (base->func == cTomate::_Const) {
         Tom_printf( "[Const]\n" );
      } else if (base->func == ToTo_Push) {
         Tom_printf( "[ToTo_Push]\n" );
      } else if (base->func == ToTo_Pop) {
         Tom_printf( "[ToTo_Pop]\n" );
      } else if (base->func == ToTo_Adr) {
         Tom_printf( "[ToTo_Adr]\n" );
      } else if (base->token == NULL) {
         Tom_printf( "[Protection]\n" );
      } else {
         Tom_printf( "[User]\n" );
      }
      base++;
   }
}



/*.SF.***********************************************************************
*
*  FUNKTION:
*     ToTo_Tree - Tomatenbaum ausgeben (Wie bitte?!?)
*
*  BESCHREIBUNG:
*     Diese Funktion gibt ab einer bestimmten Wurzel die Struktur einer
*     Tomaten-Tabelle aus. Der Aufruf ist auf zwei Arten gedacht:
*
*        Tom_USER  ( ToTo_Tree,       1,"Baum - ab aktueller Eingabestufe" )
*        Tom_USER_P( ToTo_Tree, Root, 1,"Wurzel - wird explizit angegeben" )
*
*     In der ToTo_Root-Tabelle ist bereits ein Aufruf dieser Funktion
*     enthalten (Variante ab aktueller Eingabestufe).
*
*  AUFRUF:
*     result = ToTo_Tree( line, tt );
*
*  PARAMETER:
*     result RESULT [char *] - Zeilenrest aus 'line'
*     line IN [char *] - Textzeile fuer 'result'
*     tt IN [Tom_TYPE *] - Tabelleneintrag mit:
*        (Tom_TYPE*)tt->ptr1 - Zeiger auf Wurzel, bei NULL wird die Tabelle
*                              der aktuellen Eingabestufe benutzt.
*
*  REFERENZEN:
*     Tom_Env [EXTERN FROM TOMATE]
*     Tom_TYPE [EXTERN TYPE FROM TOMATE]
*     ToToTree [GLOBAL]
*
**.EF.***********************************************************************/

char *ToTo_Tree( char *line , Tom_TYPE *tt )
{
   char *prompt;
   int level;
   Tom_TYPE *root;

   cTomate::getTomEnv( &prompt, &level, &root );

   if (tt->ptr1 == NULL) {
      Tom_printf( prompt,level );
      Tom_printf( "  [Prompt]\n" );
   } else {
      root = (Tom_TYPE *)tt->ptr1;
   }

   ToToTree( root , 1 );

   return line;
}


// ---------------------------------------------------------------------------
// ToTo_cBaseDebug
//
static Tom_TYPE _debugmask[] = {
   Tom_COMMENT(   "----- Debug-Flags:" )
   Tom_MASK( _ON , cBase::dbgError   , 1,"Error - Fehlermeldungen [dbgError]" )
   Tom_MASK( _ON , cBase::dbgInfo    , 1,"Info  - Allgemeine Infos [dbgInfo]" )
   Tom_MASK( _ON , cBase::dbgTrcBase , 2,"TBase - Trace: Methoden der Basisklassen [dbgTrcBase]" )
   Tom_MASK( _ON , cBase::dbgTrcDb   , 2,"TDb   - Trace: Methoden der Datenbankklassen [dbgTrcDb]" )
   Tom_MASK( _ON , cBase::dbgTrcWin  , 2,"TWin  - Trace: Methoden der Windowklassen [dbgTrcWin]" )
   Tom_MASK( _ON , cBase::dbgTrcApp  , 2,"TApp  - Trace: Methoden der Anwendungsklassen [dbgTrcApp]" )
   Tom_MASK( _ON , cBase::dbgBase    , 1,"Base  - Basisklassen-Spezifisches [dbgBase]" )
   Tom_MASK( _ON , cBase::dbgDb      , 1,"Db    - Datenbankklassen-Spezifisches [dbgDb]" )
   Tom_MASK( _ON , cBase::dbgWin     , 1,"Win   - Windowklassen-Spezifisches [dbgWin]" )
   Tom_MASK( _ON , cBase::dbgSql     , 1,"Sql   - Alle SQL-Befehle [dbgSql]" )
   Tom_MASK( _ON , cBase::dbgMsg     , 1,"Msg   - Meldungs-spezifisches [dbgMsg]" )
   Tom_ENDE()
};


char *ToTo_cBaseDebug( char *line , Tom_TYPE *tt )
{
   unsigned long old_debug, debug;
   Tom_NAMES desc = { &debug, _debugmask };
   Tom_TYPE with_tt;

   with_tt.value = _MASK;
   with_tt.ptr1 = (void*)&desc;
   with_tt.ptr2 = (void*)ToToMaskOp;
   with_tt.minlen = tt->minlen;
   with_tt.token = tt->token;

   old_debug = debug = cBase::getDebugMask();
   line = cTomate::_With( line, &with_tt );
   if (old_debug != debug) cBase::setDebugMask( debug );

   return line;
}


// ---------------------------------------------------------------------------
// _environment & ToTo_Env
//

char *ToTo_Env( char *line , Tom_TYPE *tt )
{
   char buf[256];
   char *env;
   int len;

   switch (tt->value) {
   case 1: // getenv
      if (Tom_GetArg(&line,buf,sizeof(buf))) {
         if ( (env = getenv(buf)) != 0 ) {
            Tom_printf("%s=%s\n",buf,env);
         } else {
            Tom_printf("%s not defined\n",buf);
         }
      }
      break;
   case 2: // putenv
      if ( Tom_GetArg(&line, buf, sizeof(buf)-1) ) {
         len = strlen(buf);
         buf[len] = '=';
         if (Tom_GetStr(&line, buf+len+1, sizeof(buf)-len-1) ) {
            if (putenv(buf)) {
               Tom_printf("error\n");
            }
         }
      }
      break;
   case 3: // env
      {
         char **env = _environ;
         while (*env != NULL) {
            Tom_printf("%s\n",*env);
            env++;
         }
      }
      break;
   }
   return line;
}

static Tom_TYPE _environment[] = {
   Tom_UW(ToTo_Env, 1, 1,"Get <var> - Wert anzeigen" )
   Tom_UW(ToTo_Env, 2, 1,"Set <var> <value> - Wert setzen")
   Tom_UW(ToTo_Env, 2, 1,"Put <var> <value> - Wert setzen")
   Tom_UW(ToTo_Env, 3, 1,"View - alle Werte anzeigen" )
   Tom_UW(ToTo_Env, 3, 0,"(Default ist alle Werte anzeigen" )
   Tom_ENDE()
};
/*.SF.***********************************************************************
*
*  FUNKTION:
*     ToTo_View - allgemeine tomatige Variablenausgabe
*
*  BESCHREIBUNG:
*     Was im Tom_VIEW-Macro konstant festgelegt ist, wird dieser
*     Funktion beim Aufruf mitgegeben. Ansonsten aehnlich Tom_View.
*
*  AUFRUF:
*     ToTo_View( name, type, value );
*
*  PARAMETER:
*     name IN [char *] - Variablen-Name (entspricht dem Token)
*     type IN [int] - Variablen-Typ
*     value IN [void *] - Variablen-Zeiger (bei _ENUM und _MASK wie
*                         ueblich auf eine Tom_NAMES-Struktur).
*
**.EF.***********************************************************************/

void ToTo_View( char *name, int type, void *value )
{
   Tom_TYPE tt;

   tt.func = cTomate::_View;
   tt.value = type;
   tt.ptr1 = value;
   tt.ptr2 = NULL;
   tt.minlen = 1;
   tt.token = name;
   cTomate::_View( NULL, &tt );
}


/**.SV.***********************************************************************
*
*  VARIABLENNAME:
*     ToTo_Root - Wurzeltabelle fuer diverse Tom-Tools
*
*  BESCHREIBUNG:
*     Es wird empfohlen, bei Tom_Start den Immer-und-Ueberall-Befehlen die
*     folgende Zeile hinzuzufuegen, um einen einheitlichen Zugriff auf die
*     Tom-Tools zu haben:
*
*        Tom_PARAM( ToTo_Root , 1,"$ ... - Tom-Tools" )
*
*  VARIABLENTYP:
*     [ARRAY ? OF Tom_TYPE]
*
**.EV.***********************************************************************/

const Tom_TYPE ToToRoot[] = {
#if LANGUAGE == LG_GERMAN
   Tom_U( ToTo_Tree,       1,"Tree - erreichbaren Tomatenbaum ausgeben" )
   Tom_U( ToTo_cBaseDebug, 1,"Debug ... - Debug-Maske (aus cBase)" )
   Tom_PARAM( _environment, 1, "Env ... - Umgebungsvariablen" )
#endif
#if LANGUAGE == LG_ENGLISH
   Tom_U( ToTo_Tree, 1,"Tree - display tomato structure" )
   Tom_U( ToTo_cBaseDebug, 1,"Debug ... - Debug-Mask (from cBase)" )
   Tom_PARAM( _environment, 1, "Env ... - environment variable" )
#endif
   Tom_ENDE()
};

__ECL_EXP1__ const Tom_TYPE * __ECL_EXP2__ ToTo_Root ( )
   { return ToToRoot; }

/*.EL.*/

