// ===========================================================================
// base/logfile.h                                               ______ /  ECL
// Autore: Markus Wuertz                                       /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cLogfile    - Verwaltung von Protokolldateien.
//
// ===========================================================================

#ifndef __ecl_logfile__
#define __ecl_logfile__


// Other ECL headers
#include "base/string.h"


namespace ecl {


// ===========================================================================
// Definition cLogfile
// ---------------------------------------------------------------------------
//
//! Verwaltung von Protokolldateien.
//! @ingroup file
//
// cLogfile
//
// ===========================================================================

class __ECL_DLLEXPORT__ cLogfile {

public:
   //! Konstruktor
   cLogfile(const char *fname = 0, bool append = true);
   
   //! Logdatei festlegen und aktivieren, oder deaktivieren
   void setFile(const char *fname = 0, bool append = true);
   //! Protokolldatei ermitteln (0 = deaktiviert)
   const char *getFile();
   
   //! Logdateigenerationen und Dateigroesse (0 = kein Limit) festlegen
   void setLimits(int max_gen, long max_size);
   //! Logdateigenerationen und Dateigroesse ermitteln
   void getLimits(int &max_gen, long &max_size);
   
   //! Zeitstempel aktivieren oder deaktivieren
   void setTimestamp(bool enable);
   //! Zeitstempelflag ermitteln
   bool getTimestamp() const;

   //! Alle Logfile-Parameter ueber einen Parameterstring setzen.
   void setParam(const char *param);

   //! Zeile in Logdatei schreiben ('\n' wird angefügt!)
   void write(const char *text);

private:
   enum {
      DEF_LOGFILE_SIZE = 524288, //!< Standarddateigroesse: 512 KByte
      DEF_LOGFILE_GEN  = 3       //!< Standardgenerationenzahl
   };

   cString _logfile_name;     //!< Name der Logdatei
   long _max_logfile_size;    //!< Groesse einer einzelnen Datei
   int _max_logfile_gen;      //!< Anzahl Generationen
   bool _use_timestamp;       //!< Zeitstempel mit Datum/Uhrzeit ausgeben

   void theNextGeneration();
};

}; // namespace ecl


#endif // __ecl_logfile__

