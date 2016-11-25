/* ----------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>


#define ENUM_ALPHA  11
#define ENUM_BETA   22
#define ENUM_GAMMA  33

#define MASK_CON   0x0001
#define MASK_PRT   0x0002
#define MASK_FILE  0x0004
#define MASK_D1    0x0100
#define MASK_D2    0x0200
#define MASK_D3    0x0300
#define MASK_D7    0x0700

char Char = 111;
unsigned char uChar = 222;
short Short = 12345;
unsigned short uShort = 56789;
int Int = -1;
unsigned int uInt = -1;
long Long = 0x76543210L;
unsigned long uLong = 0xFEDCBA98L;

int  Enum = ENUM_ALPHA;
int Mask = 0x0001;

bool Bool = true;

float Float = 3.4567;
double Double = 2.3456;
long double lDouble = 9.87654321;

double Deg = 90;

int PosX = 0;
int PosY = 0;
int Var = 0x1234;

char Strng[] = "Das ist der Initialisierungstext";
void *Void = NULL;

int Flag = 0;



int IchWerdeGetestet( int x , int y )
{
   printf( "\
Ich bin ein Programm mit folgenden Variablen:\n\
Int = %d, uInt = %u, Long = %ld, uLong = %lu\n\
(X;Y) = (%d;%d), Bool = %d, Enum = %d, Var = %d\n\
Strng = %s\n",
Int,uInt, Long,uLong, PosX,PosY, Bool,Enum,Var, Strng );
   printf( "Funktionsparameter: %d, %d\n",x,y );

   return x*y;
}

/* ----------------------------------------------------------------------- */

#include "tom/et_tomate.hpp"
#include "tom/et_tools.hpp"
#include "tom/et_con.hpp"

int IchWerdeGetestet ( int x, int y );

char *TestIt( char *line , Tom_TYPE *tt )
{
   int result;

   switch (tt->value) {
   case 0:
      Tom_printf( "TestIt(0): Aufruf mit Konstanten\n" );
      result = IchWerdeGetestet( 12 , 34 );
      break;
   case 1:
      Tom_printf( "TestIt(1): Aufruf mit x und y\n" );
      result = IchWerdeGetestet( PosX,PosY );
      break;
/*
   case 2:
      Tom_printf( "TestIt(2): Aufruf mit Parametern der Eingabezeile\n" );
      ...
      result = IchWerdeGetestet( p1,p2 );
      break;
*/
/*
   case 3:
      Tom_printf( "TestIt(3): Test von ConIO\n" );
      While ( (key=getch()) != 3 ) Do
         putch( key );
      Endwhile
      Tom_printf( "Test von cgets\n" );
      {
         char buf[82];
         buf[0] = 79;
         cgets( buf );
         cputs( buf+2 );
      }
      break;
*/
   default:
      Tom_printf( "TestIt(n): Aufruf mit n und var\n" );
      result = IchWerdeGetestet( tt->value,Var );
      break;
   }
   Tom_printf( "Funktionswert = %d\n",result );

   return line;
}

char *Hallo( char *line , Tom_TYPE *tt )
{
   Tom_printf( "Hello, world! - Ich bin eine beliebige Funktion\n" );
   return line;
}


char *LoopFunc( char *line , Tom_TYPE *tt )
{
   long val;
   int i = 0;

   val = strtoul( line , &line , 0 );
   i = 1;

   Tom_printf( "Parameter ist %ld ('%s')\n",val,line );
   do {
      Tom_printf( "Zeile %d: blabla...\n",i++ );
   } while (--val > 0L);
   Tom_printf( "Schleifenende\n" );

   return line;
}


char *GotoFunc( char *line , Tom_TYPE *tt )
{
   long val;
   int level;

   val = strtol( line , &line , 0 );
   level = Tom_Jump( (int)val );
   Tom_printf( "Aktueller Level: %d\n",level );

   return line;
}


char *StartFunc( char *line , Tom_TYPE *tt )
{
   extern Tom_TYPE _haupt[];

   Tom_Start( (Tom_TYPE*)_haupt , NULL );

   return NULL;
}


/*
 * Struktur & Hierarchie
 */

extern Tom_TYPE _sublevel[];

char _text[] = "\
Mit dem Befehl Gag2 kann man sich wunderbar im Kreis bewegen!\n";

Tom_TYPE _subsublevel[] = {
   Tom_LEVEL( _sublevel ,    1,"Gag2 - Vorsicht vor Rekursion!!" )
   Tom_UWPP( Hallo,0,0,0 ,   1,"Hallo - eine Spezialfunktion" )
   Tom_VIEW( _TEXT , _text , 1,"What - Wie bitte?" )
   Tom_PROMPT( "Sub-Sub-Level[%d]" )
};

Tom_TYPE _sub2[] = {
   Tom_LEVEL( _subsublevel , 1,"Tiefer - besonderer Gag, Teil 3" )
   Tom_ENDE()
};

Tom_TYPE _sub2b[] = {
   Tom_COMMENT( "Aetsch, das ist eine Sackgasse ..." )
   Tom_ENDE()
};

Tom_TYPE _sub1[] = {
   Tom_PARAM( _sub2 ,        1,"Noch ... - besonderer Gag, Teil 2" )
   Tom_PARAM( _sub2b ,       1,"Zweig ... -  oder hier ???" )
   Tom_ENDE()
};

Tom_TYPE _sublevel[] = {
   Tom_PARAM( _sub1 ,        1,"Gehe ... - besonderer Gag" )
   Tom_U( StartFunc ,        1,"Start - rekursiver Start-Aufruf" )
   Tom_PROMPT( "Sub-Level[%d]" )
};


/*
 * Beispiele fuer Scripts und Alias:
 */
char *_viewall[] = {
   "VAR",
   "%echo Einfache Variable:",
   "View Short",
   "View UShort",
   "View UInt",
   "View Int",
   "View ULong",
   "View Long",
   "%echo Symbolische Variable:",
   "View Bool",
   "View Enum",
   "View Strng",
   ".",
   NULL
};

char *_silent[] = {
   "%echo off",
   "script view .",
   NULL
};

/* weil die Haupttabelle erst noch folgt ... */
extern Tom_TYPE _xhauptold[];

char _notes[] = "\
Fox und Pos sind Alias-Definitionen. Ersteres kuerzt den Weg in tiefere\n\
Eingabestufen ab, zweiteres gibt mehrere Variablen zusammen aus\n\
\n";

Tom_TYPE _scrlevel[] = {
   /* Beachte: '$' ist in Cherry die Schnellreferenz fuer die Hauptstufe */
   Tom_ALIAS( "$sub gehe noch tiefer", 1,"Fox - jump over lazy Levels" )
   Tom_ALIAS( "$var view x view y .",  1,"Pos - Koordinate ausgeben" )
   Tom_SCRIPT( _viewall,_xhauptold , 1,"View - Alle Variablen anzeigen" )
   Tom_SCRIPT( _silent,_xhauptold ,  2,"SView - dito, aber silent" )
   Tom_VIEW( _TEXT , _notes, 1,"Notes - Anmerkungen" )
   Tom_PROMPT( "Script-Test[%d]" )
};


/*
 * Haupttabelle:
 */
Tom_TYPE _xhauptold[] = {
   Tom_COMMENT( "----- Benutzerdefinierte Funktionen:" )
   Tom_UW( TestIt, 0,     1,"All - eigene Funktion #0" )
   Tom_UW( TestIt, 1,     2,"A1 - dito, Aufrufmodus #1" )
   Tom_UW( TestIt, 2,     2,"A2 - dito, Aufrufmodus #2" )
   Tom_UW( TestIt, 3,     2,"A3 - Konsolen-IO testen" )
   Tom_UW( TestIt, 33,    3,"A33 - dito, Aufrufmodus #33" )
   Tom_COMMENT( "----- Struktur:" )
   Tom_LEVEL( _sublevel,  3,"SUBlevel> - weitere Eingabestufe" )
   Tom_LEVEL( _scrlevel,  3,"SCRipts> - Scripts und Alias" )
   Tom_COMMENT( "----- spezielle Testfunktionen:" )
   Tom_U( LoopFunc,       1,"Loop <rept> - Ausgabeschleife fuer More" )
   Tom_U( GotoFunc,       1,"Goto <level> - Kaenguruh fuer Jump" )
   Tom_ALIAS( "$sub $sub $sub $sub $sub $sub $sub $sub $sub $sub $sub $sub $sub $sub ",1,"U-Boot - " )
   Tom_GATES( NULL , NULL, "Alt[%d]" )
};





/*
 * Definition der "symbolischen" Datentypen:
 */
Tom_TYPE _valmask[] = {              /* Definition eines Masken-Typs */
   Tom_COMMENT(                        "----- Moegliche Masken:" )
   Tom_MASK( _ON       , MASK_CON  , 2,"CONSOLE - Konsolenausgabe" )
   Tom_MASK( _ON       , MASK_PRT  , 2,"PRINTER - Druckerausgabe" )
   Tom_MASK( _ON       , MASK_FILE , 2,"FILE - Dateiausgabe" )
   Tom_MASK( MASK_D1   , 0x0F00    , 2,"DEV1 - Geraet Nr.1" )
   Tom_MASK( MASK_D2   , 0x0F00    , 2,"DEV2 - Geraet Nr.2" )
   Tom_MASK( MASK_D3   , 0x0F00    , 2,"DEV3 - Geraet Nr.3" )
   Tom_MASK( MASK_D7   , 0x0F00    , 2,"DEV7 - Geraet Nr.7" )
   Tom_ENDE()
};

Tom_NAMES _Mask = { &Mask , _valmask };


Tom_TYPE _valenum[] = {              /* Definition eines Enum-Typs */
   Tom_ENUM( ENUM_ALPHA , 1,"Alpha - Enumwert Nr. 1" )
   Tom_ENUM( ENUM_BETA  , 1,"Beta - Enumwert Nr. 2" )
   Tom_ENUM( ENUM_GAMMA , 1,"Gamma - Enumwert Nr. 3" )
   Tom_ENDE()
};

Tom_NAMES _Enum = { &Enum , _valenum };


/*
 * "neue" allgemeine Variablenverwaltung:
 */
Tom_TYPE _maskaction[] = {
   Tom_COMMENT( "----- Operationen auf Masken-Variablen:" )
   Tom_VIEW( 0  , NULL ,  1,"View - anzeigen" )
   ToTo_PUSH( 0 , NULL ,  2,"PUsh - auf den Stack" )
   ToTo_POP( 0  , NULL ,  2,"POp - vom Stack holen" )
   ToTo_ADR( 0  , NULL ,  1,"Adr - Adresse der Variable" )
   Tom_RESET( 0 , NULL ,  1,"- ruecksetzen einer Maske" )
   Tom_SET( 0   , NULL ,  1,"+ setzen einer Maske" )
   Tom_SET( 0   , NULL , -1,"('+' ist optional)" )
   Tom_ENDE()
};

Tom_TYPE _varaction[] = {
   Tom_COMMENT( "----- Operationen auf Variablen:" )
   Tom_VIEW( 0  , NULL ,  1,"View - anzeigen (Variablennamen beachten)" )
   ToTo_PUSH( 0 , NULL ,  2,"PUsh - auf den Stack" )
   ToTo_POP( 0  , NULL ,  2,"POp - vom Stack holen" )
   ToTo_ADR( 0  , NULL ,  1,"Adr - Adresse der Variable" )
   Tom_SET( 0   , NULL ,  1,"Set <int> - setzen eines Wertes" )
   Tom_SET( 0   , NULL , -1,"(Eingabe von 'Set' ist optional)" )
   Tom_ENDE()
};

static  Tom_TYPE _varnewlevel[] = {
   Tom_COMMENT( "----- Die   N E U E N   Aktionsvariablen:" )
   Tom_WITH( _uchar  , &uChar  , _varaction  , 2,"UChar ... - unsigned char" )
   Tom_WITH( _ushort , &uShort , _varaction  , 2,"UShort ... unsigned short" )
   Tom_WITH( _uint   , &uInt   , _varaction  , 2,"UInt ... - unsigned integer" )
   Tom_WITH( _ulong  , &uLong  , _varaction  , 2,"ULong ... - unsigned long integer" )
   Tom_WITH( _char   , &Char   , _varaction  , 1,"Char ... - char" )
   Tom_WITH( _short  , &Short  , _varaction  , 1,"Short ... - short" )
   Tom_WITH( _int    , &Int    , _varaction  , 1,"Int ... - integer" )
   Tom_WITH( _long   , &Long   , _varaction  , 1,"Long ... - long integer" )
   Tom_WITH( _ENUM   , &_Enum  , _varaction  , 1,"Enum ... - Aufzaehltyp" )
   Tom_WITH( _MASK   , &_Mask  , _maskaction , 1,"Mask ... - Bitmaske" )
   Tom_WITH( _bool   , &Bool   , _varaction  , 1,"Bool ... - 2 b | !( 2 b ) ?" )
   Tom_WITH( _STR    ,  Strng  , _varaction  , 1,"$string ... - char[]" )
   Tom_WITH( _TEXT   , "Textvariablen koennen nur angezeigt werden!\n"
                               , _varaction  , 1,"Text ... - char *" )
   Tom_WITH( _ptr    , &Void   , _varaction  , 1,"Void ... - Woidzaiger je nach System" )
   Tom_WITH( _float  , &Float  , _varaction  , 1,"Float ... - float" )
   Tom_WITH( _double , &Double , _varaction  , 1,"Double ... - double" )
   Tom_WITH( _ldouble, &lDouble, _varaction  , 1,"LDouble ... - long double" )
   Tom_COMMENT( "----- ... und Koordinaten:" )
   Tom_WITH( _int    , &PosX   , _varaction  , 1,"X - Horizontal" )
   Tom_WITH( _int    , &PosY   , _varaction  , 1,"Y - Vertikal" )
   Tom_ALIAS( "X VIEW Y VIEW"                , 2,"VIew - Koordinaten anzeigen" )

   Tom_PROMPT( "Neu[%d]" )
};


/*
 * "alte" allgemeine Variablenverwaltung:
 */
static  Tom_TYPE _setit[] = {
   Tom_SET( _uint   , &uInt   , 2,"UInt <int> - unsigned Integer" )
   Tom_SET( _int    , &Int    , 1,"Int <int> - signed Integer" )
   Tom_SET( _ulong   , &uLong  , 2,"ULong <long> - unsigned Long" )
   Tom_SET( _long   , &Long   , 1,"Long <long> - signed Long" )
   Tom_SET( _bool   , &Bool   , 1,"Bool ... - 2 b | !( 2 b ) ?" )
   Tom_SET( _ENUM   , &_Enum  , 1,"Enum ... - Enum-Typ" )
   Tom_SET( _uint   , &Enum   , 2,"IEnum - dieser Enum-Typ als Integer" )
   Tom_SET( _STR    , Strng     , 1,"Strng <string> - Zeichenkette" )
   Tom_SET( _ptr    , &Void   , 1,"Void <int/long> - Woidzaiger je nach System" )
   Tom_SET( _double , &Double , 1,"Double <double> - double" )
   Tom_SET( _float  , &Float  , 1,"Float <float> - float" )

   Tom_ENDE()
};

static  Tom_TYPE _viewit[] = {
   Tom_VIEW( _uint   , &uInt   , 2,"UInt - unsigned Integer" )
   Tom_VIEW( _int    , &Int    , 1,"Int - signed Integer" )
   Tom_VIEW( _ulong   , &uLong  , 2,"ULong - unsigned Long" )
   Tom_VIEW( _long   , &Long   , 1,"Long - signed Long" )
   Tom_VIEW( _bool   , &Bool   , 1,"Bool - wahr oder nicht wahr" )
   Tom_VIEW( _ENUM   , &_Enum  , 1,"Enum - Enum-Typ" )
   Tom_VIEW( _STR    , Strng     , 1,"Strng - Zeichenkette" )
   Tom_VIEW( _ptr    , &Void   , 1,"Void - Woidzaiger" )
   Tom_VIEW( _int    , &PosX   , 1,"X - Koordinate, 1. Teil" )
   Tom_VIEW( _int    , &PosY   , 1,"Y - Koordinate, 2. Teil" )
   Tom_VIEW( _double , &Double , 1,"Double - double" )
   Tom_VIEW( _float  , &Float  , 1,"Float - float" )

   Tom_ENDE()
};

static  Tom_TYPE _pushit[] = {
   ToTo_PUSH( _uint   , &uInt   , 2,"UInt - unsigned Integer" )
   ToTo_PUSH( _int    , &Int    , 1,"Int - signed Integer" )
   ToTo_PUSH( _ushort , &uShort , 2,"UShort - signed short")
   ToTo_PUSH( _short  , &Short  , 1,"Short - signed short")
   ToTo_PUSH( _ulong  , &uLong  , 2,"ULong - unsigned Long" )
   ToTo_PUSH( _long   , &Long   , 1,"Long - signed Long" )
   ToTo_PUSH( _bool   , &Bool   , 1,"Bool - wahr oder nicht wahr" )
   ToTo_PUSH( _ENUM   , &Enum   , 1,"Enum - Enum-Typ" )
   ToTo_PUSH( _ptr    , &Void   , 1,"Void - Woidzaiger" )
   ToTo_PUSH( _double , &Double , 1,"Double - double" )
   ToTo_PUSH( _float  , &Float  , 1,"Float - float" )

   Tom_ENDE()
};

static  Tom_TYPE _popit[] = {
   ToTo_POP( _uint   , &uInt   , 2,"UInt - unsigned Integer" )
   ToTo_POP( _int    , &Int    , 1,"Int - signed Integer" )
   ToTo_POP( _ushort , &uShort , 2,"UShort - signed short")
   ToTo_POP( _short  , &Short  , 1,"Short - signed short")
   ToTo_POP( _ulong  , &uLong  , 2,"ULong - unsigned Long" )
   ToTo_POP( _long   , &Long   , 1,"Long - signed Long" )
   ToTo_POP( _bool   , &Bool   , 1,"Bool - wahr oder nicht wahr" )
   ToTo_POP( _ENUM   , &Enum   , 1,"Enum - Enum-Typ" )
   ToTo_POP( _ptr    , &Void   , 1,"Void - Woidzaiger" )
   ToTo_POP( _double , &Double , 1,"Double - double" )
   ToTo_POP( _float  , &Float  , 1,"Float - float" )

   Tom_ENDE()
};


static  char _tvar[] = "\
Diese Variable enthaelt ein WORD ohne bestimmte Bedeutung\n\
(Textvariablen sind gut fuer Erklaerugen)\n";

static  Tom_TYPE _var[] = {
   Tom_VIEW(  _TEXT , _tvar , 1,"Help - wasissndas" )
   Tom_VIEW(  _uint , &Var  , 1,"View - anzeigen (Variablenname beachten!)" )
   ToTo_PUSH( _uint , &Var  , 2,"PUsh - auf den Stack" )
   ToTo_POP(  _uint , &Var  , 2,"POp - vom Stack holen" )
   Tom_SET(   _uint , &Var  ,-1,"<int> - setzen eines Wertes (default)" )

   Tom_ENDE()
};


static  Tom_TYPE _varoldlevel[] = {
   Tom_COMMENT( "----- Set/View-Zweige mit Variablen-Unterzweigen:" )
   Tom_PARAM( _setit    , 1,"Set ... - Parameter setzen" )
   Tom_PARAM( _viewit   , 1,"View ... - Parameter anzeigen" )
   Tom_PARAM( _pushit   , 2,"PUsh ... - Parameter auf den Stack" )
   Tom_PARAM( _popit    , 2,"POp ... - Parameter vom Stack holen" )
   Tom_COMMENT( "----- Variablenzweig mit Set/View-Unterzweigen:" )
   Tom_PARAM( _var      , 3,"VAR ... - Integer-Variable steuern" )

   Tom_PROMPT( "Alt[%d]" )
};


/*
 * Spezielle Variablenbearbeitung:
 */
static  Tom_TYPE _varlevel[] = {
   Tom_COMMENT( "----- Werte direkt laden:" )
   Tom_SET(   _int , &PosX       , 1,"X <int> - eine Koordinate" )
   Tom_SET(   _int , &PosY       , 1,"Y <int> - andere Koordinate" )
   Tom_COMMENT( "----- Variablen mit Konstanten belegen:" )
   Tom_CONST( _int , &PosX , 0   , 2,"X0 - X loeschen" )
   Tom_CONST( _int , &PosY , 100 , 2,"YMAX - Y mit Maximalwert laden" )
   Tom_COMMENT( "----- Werte direkt anzeigen (Variablenname beachten):" )
   Tom_VIEW(  _int , &PosX       , 2,"VX - View X" )
   Tom_VIEW(  _int , &PosY       , 2,"VY - View Y" )
   Tom_ALIAS( "VX VY"            , 1,"View - Koordinaten anzeigen" )
   Tom_COMMENT( "----- allgemeine Variablenbehandlungen:" )
   Tom_LEVEL( _varnewlevel       , 1,"Neu> - neue Variablen" )
   Tom_LEVEL( _varoldlevel       , 1,"Alt> - alte Variablen" )

   Tom_PROMPT( "Variablen[%d]" )
};


/*
 * Gate-Demo Nr.1: Geschuetzte Eingabestufen:
 */
char *initgate( char *line , Tom_TYPE *tt )
{
   Tom_printf( "*** Init ***\n" );
   if (Flag != 1) {
      Tom_printf( "In diesen Level darf man nur wenn Flag == 1 ist!\n" );   }

   return (Flag == 1) ? line : NULL;
}

char *exitgate( char *line , Tom_TYPE *tt )
{
   Tom_printf( "*** Exit ***\n" );
   if (Flag != 2) {
      Tom_printf( "Hier kommst Du nur mit Flag == 2 raus!\n" );
   }

   return (Flag == 2) ? line : NULL;
}

Tom_TYPE _initexitlevel[] = {
   Tom_COMMENT( "----- Level mit besonderem Zu- und Abgang" )
   Tom_WITH( _int , &Flag , _varaction , 1,"Flag ... - Flagvariable" )

   Tom_GATES( initgate , exitgate , "Init&Exit[%d]" )
};


/*
 * Gate-Demo Nr. 2: Level mit dynamischem Prompt und dynamischem Exit-Gate
 */
char *dynexit( char *line , Tom_TYPE *tt )
{
   Tom_printf( "Ich bin eine dynamisch fesgelegte Exit-Funktion\n" );
   if (Flag != 3) {
      Tom_printf( "Hier kommst Du nur mit Flag == 3 raus!\n" );
   }

   return (Flag == 3) ? line : NULL;
}

char *promptgate( char *line , Tom_TYPE *tt )
{
   static char buf[16];

   if (Tom_GetArg( &line , buf , 16)) {
      tt->token = buf;
   } else {
      line = NULL;
   }

   if (buf[0] == '!') {
      tt->ptr2 = dynexit;
   }

   return line;
}

static char _schweinetext[] = "\
Falls beim Aufruf das erste Zeichen des Prompt `!` ist,\n\
dann wird automatisch eine Exit-Gate-Funktion definiert!\n";

Tom_TYPE _promptlevel[] = {
   Tom_COMMENT( "----- Level mit beim Aufruf festgelegtem Prompt:" )
   Tom_VIEW( _TEXT , _schweinetext , 1,"Mehr - Schweinereien" )
   Tom_WITH( _int , &Flag , _varaction , 1,"Flag ... - Flagvariable" )
   Tom_GATES( promptgate , NULL , "Es ist egal was hier steht!" )
};


/*
 * Gate-Demo Nr. 3: Parameterstufe mit dynamischer Tabellenwahl
 */
Tom_TYPE _secretparam[] = {
   Tom_COMMENT( "----- Geheim-Nachrichten:" )
   Tom_ALIAS( "%echo Thomas ist doof!",1,"Thomas" )
   Tom_ALIAS( "%echo Jehova, Jehova, Jehova!!!",1,"Siggi" )
   Tom_ALIAS( "%echo Wie waer's mit 'ner Runde Tetris?",1,"Norman" )
   Tom_ALIAS( "%echo Held der Tomate ...",1,"Markus" )

   Tom_ENDE()
};


char *paramgate( char *line , Tom_TYPE *tt )
{
   char *oldline = line;

   while (isspace(*line)) { line++; }
   if (strncmp( line,"secret",6 )) {
      Tom_printf( "Hello, world\n" );
      line = oldline;
   } else {
      Tom_printf( "Hello, *SECRET* world!\n" );
      tt->ptr1 = (void*)_secretparam;
      line += 6;
   }

   return line;
}

Tom_TYPE _worldparam[] = {
   Tom_COMMENT( "----- Sprechblasen:" )
   Tom_ALIAS( "%echo Trara trara",1,"Post" )
   Tom_ALIAS( "%echo Holleroedulioeh",1,"Loeffel" )
   Tom_VIEW( _TEXT,"Mit 'GateParam secret ...' gibts mehr!\n",1,"Mehr - Schweinereien" )
   Tom_ENDE()
};


/*
 * Gate-Demo Nr. 4: Protect innerhalb einer Tabelle
 */
static char *ProtFnTrue( char *line , Tom_TYPE *tt )
{
   return Flag == 99 ? line : NULL;
}

static char *ProtFnFalse( char *line , Tom_TYPE *tt )
{
   return Flag == 99 ? NULL : line;
}


static Tom_TYPE _protenumvalues[] = {
   Tom_ENUM( 11 , 1,"Elf - 11" )
   Tom_PROTECT( ProtFnTrue )
      Tom_COMMENT( "----- Nur bei Flag == 99 erlaubt:" )
      Tom_ENUM( 55 , 1,"Fuenfundfuenfzig - 55" )
   Tom_PROTECT( NULL )
   Tom_ENUM( 88 , 1,"Achtundachzig - 88" )
   Tom_ENUM( 99 , 1,"Luftballons - 99" )

   Tom_ENDE()
};

static Tom_NAMES _Flag = { &Flag , _protenumvalues };


static Tom_TYPE _protect[] = {
   Tom_PROMPT( "Protect[%d]" )
};


Tom_TYPE _gatelevel[] = {
   Tom_LEVEL( _initexitlevel , 1,"Init&Exit> - geschuetzte Eingabestufen" )
   Tom_LEVEL( _promptlevel   , 1,"Prompt <arg> > - dynamische Prompts & Exit-Gates" )
   Tom_GPARAM( _worldparam , paramgate , 1,"GateParam ... - Parameter mit Gate" )

   Tom_PROTECT( ProtFnTrue )
      Tom_COMMENT( "----- Nur bei Flag == 99 erlaubt:" )
      Tom_CONST( _ENUM , &Flag, 88 , 2,"88 -> Flag" )
   Tom_PROTECT( ProtFnFalse )
      Tom_COMMENT( "----- Nur bei Flag != 99 erlaubt:" )
      Tom_CONST( _ENUM , &Flag, 99 , 2,"99 -> Flag" )
   Tom_PROTECT( NULL )
   Tom_COMMENT( "----- Immer erlaubt:" )

   Tom_WITH( _ENUM , &_Flag , ToTo_VarOp , 1,"Enum ... - Flag-Variable als Enum" )
   Tom_WITH( _int  , &Flag  , _varaction , 1,"Flag ... - Flagvariable" )

   Tom_PROMPT( "Gates[%d]" )
};


/*
 * Parameterauswertung
 */
static Tom_TYPE _paramenum[] = {

   Tom_ENDE()
};

static char *GetFunc( char *line , Tom_TYPE *tt )
{
   unsigned int W;
   int i;
   long l;
   double d;
   char word[11];

   switch( tt->value) {
   case 0:
      if (Tom_GetLong( &line, &l)) {
         Tom_printf( "Long = %ld\n",l );
      }
      break;
   case 1:
      if (Tom_GetInt( &line, &i)) {
         Tom_printf( "Int = %d\n",i );
      }
      break;
   case 2:
      if (Tom_GetDouble( &line, &d)) {
         Tom_printf( "Double = %.3f\n",d );
      }
      break;
   case 3:
      if (Tom_GetArg( &line, word, 11 )) {
         Tom_printf( "Argument = '%s'\n",word );
      }
      break;
   case 4:
      if (Tom_GetInt( &line , (int*)&W )) {
         Tom_printf( "WORD = %u\n",W );
      }
      break;
   case 5:
      if (Tom_GetArg( &line, word, 1 )) {
         Tom_printf( "Argument = '%s'\n",word );
      }
      break;
   default:
      Tom_printf( "GetFunc: unbekannter Kode %d\n",tt->value );
      break;
   }

   return line;
}

static Tom_TYPE _getlevel[] = {
   Tom_COMMENT(          "----- Befehlszeilenparameter:" )
   Tom_UW( GetFunc, 0, 1,"Long - Long-Parameter (Tom_GetLong)" )
   Tom_UW( GetFunc, 1, 1,"Int - Int-Parameter (Tom_GetInt)" )
   Tom_UW( GetFunc, 4, 1,"Word - WORD-Parameter (Tom_GetInt)" )
   Tom_UW( GetFunc, 2, 1,"Double - Double-Parameter (Tom_GetDouble)" )
   Tom_UW( GetFunc, 3, 1,"Arg - Argument-Wort (10 Zeichen)" )
   Tom_UW( GetFunc, 5, 1,"Char - Argument-'Wort' (1 Zeichen)" )

   Tom_PROMPT( "Parameter[%d]" )
};


/*
 * Informationen ueber das aktuelle System
 */
static char *SystemFunc( char *line , Tom_TYPE *tt )
{
   static char ch[1] = { -1 };

   switch(tt->value) {

   case 0:
      Tom_printf( "sizeof( char )        = %d\n",(int)sizeof(char) );
      Tom_printf( "sizeof( short )       = %d\n",(int)sizeof(short) );
      Tom_printf( "sizeof( int )         = %d\n",(int)sizeof(int) );
      Tom_printf( "sizeof( long )        = %d\n",(int)sizeof(long) );
      Tom_printf( "sizeof( size_t )      = %d\n",(int)sizeof(size_t) );
      Tom_printf( "sizeof( void* )       = %d\n",(int)sizeof(void*) );
      Tom_printf( "sizeof( float )       = %d\n",(int)sizeof(float) );
      Tom_printf( "sizeof( double )      = %d\n",(int)sizeof(double) );
#ifdef __STDC__
      Tom_printf( "sizeof( long double ) = %d\n",(int)sizeof(long double) );
#endif
      break;

   case 1:

#define MINCHAR   ((char)  (1 << (8*sizeof(char)  - 1)))
#define MINSHORT  ((short) (1 << (8*sizeof(short) - 1)))
#define MININT    ((int)   (1 << (8*sizeof(int)   - 1)))
#define MINLONG   ((long)  (1 << (8*sizeof(long)  - 1)))

#define MAXCHAR   ((char)  (~MINCHAR) )
#define MAXSHORT  ((short) (~MINSHORT))
#define MAXINT    ((int)   (~MININT)  )
#define MAXLONG   ((long)  (~MINLONG) )

#define MAXUCHAR  ~((unsigned char)  0)
#define MAXUSHORT ~((unsigned short) 0)
#define MAXUINT   ~((unsigned int)   0)
#define MAXULONG  ~((unsigned long)  0)

      Tom_printf( "CHAR_BIT  %12d (%d)\n",CHAR_BIT,8 );
      Tom_printf( "CHAR_MIN  %12d (%d)\n",CHAR_MIN,(ch[0]<0) ? MINCHAR : 0 );
      Tom_printf( "CHAR_MAX  %12d (%d)\n",CHAR_MAX,(ch[0]<0) ? MAXCHAR : 255);

      Tom_printf( "\nSCHAR_MIN %12d (%d)\n",SCHAR_MIN,MINCHAR );
      Tom_printf( "SCHAR_MAX %12d (%d)\n",SCHAR_MAX,MAXCHAR );
      Tom_printf( "UCHAR_MAX %12u (%u)\n",UCHAR_MAX,MAXUCHAR );

      Tom_printf( "\nSHRT_MIN  %12d (%d)\n",SHRT_MIN,MINSHORT );
      Tom_printf( "SHRT_MAX  %12d (%d)\n",SHRT_MAX,MAXSHORT );
      Tom_printf( "USHRT_MAX %12u (%u)\n",USHRT_MAX,MAXUSHORT );

      Tom_printf( "\nINT_MIN   %12d (%d)\n",INT_MIN,MININT );
      Tom_printf( "INT_MAX   %12d (%d)\n",INT_MAX,MAXINT );
      Tom_printf( "UINT_MAX  %12u (%u)\n",UINT_MAX,MAXUINT );

      Tom_printf( "\nLONG_MIN  %12ld (%ld)\n",LONG_MIN,MINLONG );
      Tom_printf( "LONG_MAX  %12ld (%ld)\n",LONG_MAX,MAXLONG );
      Tom_printf( "ULONG_MAX %12lu (%lu)\n",ULONG_MAX,MAXULONG );
      break;

   default:
      Tom_printf( "SystemFunc: unbekannter Code %d\n",tt->value );
      break;
   }

   return line;
}

static Tom_TYPE _systemlevel[] = {
   Tom_UW( SystemFunc, 0, 1,"Sizeof - Groesse der Datentypen" )
   Tom_UW( SystemFunc, 1, 1,"Limits - Zahlenbereiche" )

   Tom_PROMPT( "System[%d]" )
};


/*
 * Haupt-Tabelle:
 */
Tom_TYPE _haupt[] = {
   Tom_COMMENT( "----- Schwerpunkte:" )
   Tom_LEVEL( _gatelevel   , 1,"Gates - verschiedene Schutzmechanismen" )
   Tom_LEVEL( _getlevel    , 1,"Parameter - Befehlzeilenparameter" )
   Tom_LEVEL( _systemlevel , 1,"System - Maschinenvariablen ermitteln" )
   Tom_LEVEL( _varlevel    , 1,"Variablen - Standard-Typen verwursteln" )

   Tom_COMMENT( "-----" )
   Tom_LEVEL( _xhauptold    , 1,"Alt - Reste der ALTEN Cherry-Struktur" )

   Tom_PROMPT( "Cherry" )
};


/*
 * Immer-und-ueberall-Funktionen:
 */
static Tom_TYPE _escape[] = {
   Tom_PARAM( _haupt ,       1,"# ... - Befehle der Hauptstufe" )
   Tom_PARAM( ToTo_Root ,    1,"$ ... - Tom-Tools" )
   Tom_ENDE()
};



/*
 * So sieht der Aufruf der Tomate aus:
 */
#include "base/eb_str.hpp"
#include "base/eb_cmdarg.hpp"

int main( int argc, char *argv[] )
{
   cCmdArg arg_line( argc, argv );
   const char *arg;
   bool option;

   cString server;

   while ( (arg = arg_line.getNext()) != NULL ) {
      option = *arg == '/' || *arg == '-';
      if ( option && (!stricmp(arg+1,"server") || !stricmp(arg+1,"s")) ) {
         server = arg_line.getNext();
      } else if (!option && server.Length() == 0) {
         server = arg;
      } else {
         cout << "Usage: " << arg_line.getModule() <<
            " [[-S] <servername>]" << endl;
         return 1;
      }
   }
   if ( server.Length() ) {
      _putenv( (const char *)(cString("CON_SERVER=") + server) );
   }

   {
      cTomConServer tcs; //tcs("Cherry-Tomate");

      cTomate tom(&tcs);
      //Tom_Init( ToCo_Init() );
      ToTo_Init();
      tom.Start( (Tom_TYPE*)_haupt , (Tom_TYPE*)_escape );
      ToTo_Exit();
      //Tom_Exit();
   }

   return 0;
}


