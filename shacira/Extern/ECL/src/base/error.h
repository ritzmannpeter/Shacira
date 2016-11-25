// ===========================================================================
// base/error.h                                                 ______ /  ECL
// Autoren: Thomas Epting, Markus Wuertz                       /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//     cErrBase   - Basisklasse fuer Exception-Handling.
//
// ===========================================================================

#ifndef __ecl_error__
#define __ecl_error__


// Standard headers
#include <iostream>

// Other ECL headers
#include "base/base.h"


namespace ecl {


// ===========================================================================
// Definition cErrBase
// ---------------------------------------------------------------------------
//
//! Basisklasse fuer Exception-Handling.
//! @ingroup baseclass
//!
//! Nimmt den Fehlercode und eine einfache Fehlermeldung auf und kann diese
//! auf Verlangen auf verschieden Arten ausgeben.
//!
//! Alle Fehlermeldungen werden in einer Datei namens 'ERROR.MSG' oder in
//! den durch die Umgebungsvariable ECL_ERRMSG spezifizierten Dateien gesucht,
//! die einzelnen Dateinamen werden durch ';' getrennt.
//!
//! Diese Dateien werden zeilenweise gelesen, wobei fuer den Zeilenaufbau gilt:
//!
//!    - Zeilen, die mit einem Buchstaben beginnen, werden als Definition einer
//!      Fehlermeldung im folgenden Format interpretiert:
//!      <Fehlercode> Leerstelle <Fehlermeldung>
//!
//!    - Eine Zeile, die mit !include <Dateiname> beginnt, fuegt den Inhalt der
//!      spezifizierten Datei an dieser Stelle ein.
//!
//!    - Alle anderen Zeilen werden ignoriert.
//!
//! Der Fehlercode muss dem Schema PPP-C-EE folgen, die Fehlermeldung kann
//! ueber Jokerzeichen der Form $x parametrisiert werden, wobei x fuer die
//! Parameternummer (1..4) steht.
//!
//! Bedingte Texte: mit $x{Text} wird der Text nur ausgegeben, wenn der
//! Parameter $x belegt ist. Der Text kann $x enthalten, Bedingungen koennen
//! aber nicht geschachtelt werden.
//!
//! Beispiel:
//!
//!   @verbatim
//!    ERR-I-01 Funktion nicht implementiert
//!    ERR-E-01 Ungueltiger Zeiger: $1
//!    ERR-E-02 Ungueltiges Handle: $1
//!    ERR-E-03 Ungueltiger Parameter $1: $2
//!    ERR-E-04 Fehler bei Initialisierung
//!    ERR-E-05 Datei nicht gefunden$1{: $1}
//!    ERR-F-01 Kein freier Speicher mehr
//!    ERR-F-02 Keine freien Handles mehr
//!   @endverbatim
//!
//! Kodierung der Fehlermeldungen in einem 32-Bit Long:
//!
//!   @verbatim
//!    31           24 23           16 15            8 7 6 5         0
//!   +---------------+---------------+---------------+---+-----------+
//!   |P P P P P P P P|P P P P P P P P|P P P P P P P P|C C E E E E E E|
//!   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//!   @endverbatim
//!
//! wobei:
//!
//!    - PPP = der Modulpraefix als 3-Zeichen Eyecatcher
//!    - C   = die Fehlerklasse
//!    - EE  = der Fehlercode - 1
//!
//! Moegliche Fehlerklassen:
//!
//!    - 00 = (I) Informationen
//!    - 01 = (W) Warnungen
//!    - 10 = (E) Fehler
//!    - 11 = (F) Fatale Fehler
//!
//! Die Ausgabe der Fehlermeldung erfolgt in folgender Syntax:
//!
//!    - PPP-C-EE: Fehlermeldung
//
// cBase
//  +--cErrBase
//
// ===========================================================================

class __ECL_DLLEXPORT__ cErrBase {

public:

   //! Lesen der Fehlermeldungsdatei erzwingen
   static void initialize();

   // Allgemeine Fehlercodes
   // ======================

   //! Typ zur Aufnahme des Fehlercodes (32-Bit Integer)
   typedef unsigned long ERR_TYPE; // 32-Bit

   // Bildet den 24-bittigen Fehlerpraefix aus 3 Einzelzeichen
   #define ERR_PREFIX(c1,c2,c3)                 \
      (   (cErrBase::ERR_TYPE)(c1) * 0x01000000L  \
        + (cErrBase::ERR_TYPE)(c2) * 0x00010000L  \
        + (cErrBase::ERR_TYPE)(c3) * 0x00000100L )

   #define errInfo   0L    /*!< Fehlerklasse: Informationen  */
   #define errWarn   64L   /*!< Fehlerklasse: Warnungen      */
   #define errError  128L  /*!< Fehlerklasse: Fehler         */
   #define errFatal  192L  /*!< Fehlerklasse: Fatale Fehler  */

   //! Allgemeine Fehlercodes
   enum ERR_CODE { errBase = ERR_PREFIX('E','R','R'),

      // Kein Fehler
      errNoError     = 0                , //!< Kein Fehler

      // Informationen
      errSorry       = errBase+errInfo  , //!< Noch nicht implementiert
      errMalformed                      , //!< Fehlercode-Textform ungueltig

      // Fehler
      errGeneral     = errBase+errError , //!< Allgemeiner Fehler
      errInvPointer                     , //!< Ungueltiger Zeiger
      errInvHandle                      , //!< Ungueltiges Handle
      errInvParam                       , //!< Ungueltiger Parameter
      errInit                           , //!< Fehler bei Initialisierung
      errTimeout                        , //!< Zeitueberschreitung
      errOverflow                       , //!< Ueberlauf jeglicher Art
      errUnderflow                      , //!< Unterlauf jeglicher Art

      // Fatale Fehler
      errNoMem       = errBase+errFatal , //!< Kein freier Speicher mehr
      errNoHandles                        //!< Keine freien Handles mehr

   };

   //! Defaultkonstruktor fuer errNoError (kein Fehler)
   cErrBase()
      { xerr = 0; }
   //! Konstruktor ueber Fehlercode
   cErrBase(ERR_TYPE err)
      { ealloc(err); }
   //! Konstruktor ueber Fehlercode und bis zu 2 String-Parametern
   cErrBase(ERR_TYPE err, const char *p1, const char *p2 = 0)
      { ealloc(err); setParam(0, p1); setParam(1, p2); }
   //! Konstruktor ueber Fehlercode und bis zu 4 String-Parametern
   cErrBase(ERR_TYPE err, const char *p1, const char *p2, const char *p3, const char *p4 = 0)
      { ealloc(err); setParam(0, p1); setParam(1, p2); setParam(2, p3); setParam(3, p4); }
   //! Copy-Konstruktor
   cErrBase(const cErrBase& other)
      { eclone(other); }
   //! Destruktor
   ~cErrBase()
      { efree(); }

   //! Zuweisungsoperator
   cErrBase& operator= (const cErrBase& right)
      { efree(); eclone(right); return *this; }


   // Umwandlung
   // ==========

private:
   void catMsg(char *& buf, size_t& size, const char *msg, size_t max = 0) const;
   void fmtMsg(char *& buf, size_t& size, const char *msg) const;

public:
   //! Ein Cast des Fehler-Objektes nach ERR_TYPE liefert den urspruenglichen Fehlercode
   operator ERR_TYPE() const { return xerr ? xerr->err_code : errNoError; }
   //! Erzeugt die vollstaendige Fehlermeldung
   const char *getString(char *buffer, size_t size, const char *add_text = 0) const;

   //! Liefert Fehlerklasse "CC" (errInfo, errWarn, errError, errFatal)
   int getClass() const    { return xerr ? (xerr->err_code & 0xC0) : errInfo; }
   //! Liefert Fehlercode "EEEEEE" (ohne Klasse und Prefix)
   int getCode() const     { return xerr ? (xerr->err_code & 0x3F)+1 : errNoError; }
   //! Liefert Modulpraefix (oder 0)
   int getPrefix() const   { return xerr ? (xerr->err_code & 0xFFFFFF00) : 0; }


   // Ausgabe
   // =======

public:
   //! Das Fehlerobjekt kann seine Fehlermeldung auf einem Stream ausgeben
   friend __ECL_OPEXP__ std::ostream& operator<<(std::ostream& os, cErrBase const& err);
   //! Ausgabe der Fehlermeldung auf dem Debug-Kanal
   void DbgOut(const char *add_text = 0) const;


// Fehlerparameter
// ===============

public:
   //! Zahlenformat bei setParam()
   enum NUM_FMT { fmtDec, fmtHex };

   //! Setzt einen optionalen Meldungsparameter (char-Parameter)
   void setParam(int p, char ch);
   //! Setzt einen optionalen Meldungsparameter (Text-Parameter)
   void setParam(int p, const char *txt);
   //! Setzt einen optionalen Meldungsparameter (long-Parameter)
   void setParam(int p, long num, NUM_FMT fmt = fmtDec);
   //! Setzt einen optionalen Meldungsparameter (void*-Parameter)
   void setParam(int p, void *ptr);

   //! Ermittelt einen Fehlerparameter in seiner textuellen Form
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


//__ECL_EXP1__ std::ostream& __ECL_EXP2__ operator<<(std::ostream& os, cErrBase const& err);


}; // namespace ecl


#endif // __ecl_error__


