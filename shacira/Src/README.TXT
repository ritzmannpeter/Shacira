
Plattformen:

  - Win32

Entwicklungsumgebungen:

  - Borland C++-Builder
  - MSVC 5.0 mit Service Pack 3
  - MSVC 6.0 mit Service Pack 5

ORBs:

  - Visibroker Version 3.3 unter Borland C++ Builder 4.
  - OmniORB Version 3.0.4 unter Microsft Visual C++ 6.
    Das generieren der Stub Files erfolgt unter OmniOrb ab der Version
    3.04 durch:
       omniidl -bcxx -WbBOA -Wba Control.idl

STL:

  - STL-Implementierung des Borland-Compilers bei Verwendung von
    Borland C++-Builder.
  - STL-Port Version 4.0 von Boris Formichev.
    Diese STL ist im Projektverzeichnis STL verfuegbar.
    Im Gegensatz zur Borland STL koennen die STL-Templatenamen wie
    list, vector usw nicht als Variablennamen verwendet werden.
    Dies fuehrt zu Fehlermeldungen der Art
    "template definition requires template argument list".

ATL:

  - ab Version 2.1. Es muss generell in der Header-Datei atlcom.h das
    Macro "min(a,b) (a<b) ? a : b" definiert werden.
  - Wesentlich besser als in atlcom.h rumzumanschen: #include <minmax.h>
    in OPCInterface\stdafx.h einfuegen

STYX:
  - Die Sprachbeschreibung ist in Shacira.sty
  - Stubs zum parsen werden wie folgt generiert
    styx -makeIMG -makeC Shacira
  - Die Integration von styx in den Source fuehrt zu Problemen
    mit der standard-stl-Klasse list, was sich vornehmlich bei der
    Verwendung mit dem Borland-Compiler 5.4 auswirkt.
    Als Workaround wurde die Datei list.h in STYX/Src/INC in styxlist.h
    umbenannt. Die Dateien innerhalb des Styx-Source-Codes die diese
    Datei benoetigen muessen entsprechend angepasst werden.

Borland 5.4 Compiler und Exceptionbehandlung:
  - Beim Borland Compiler 5.4 werden beim Aufraeumen des Stacks
    im Konstruktor und nur im Konstruktor die Destruktoren von
    Objekten, die nach dem throw erst instantiiert werden,
    zweimal aufgerufen. Dieses Verhalten hat absolut unkontrollierbare
    Auswirkungen.

Beispiel: 

   cAnyClass::cAnyClass()
   {
      cObject object1;      
      throw SomeException();
      cObject object2;
      // Bei object 1 wird korrekt aufgeraeumt,
      // der Destruktor von object1 wird genau einmal
      // aufgerufen.
      // Bei object2 gehts in die Hose.
      // Der Destruktor von object2 wir zweimal aufgerufen.
      // Was dann passiert haengt natuerlich davon ab,
      // was im Destruktor von object2 gemacht wird.
   }
   
   Diese Situation kann nur durch bewusste Vermeidung verhindert werden.
   Falls im Konstruktor eines Objekts ggfs. eine Exception verursacht werden
   kann sollten vor dieser Zeile alle im Konstruktor auf dem Stack liegenden
   Objekte schon instantiiert sein (positionstechnisch).


Integration in GIT
