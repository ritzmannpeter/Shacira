// ===========================================================================
// es_query.cpp                                                 ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-csBaseStorage
//        |
//        +-csQuery            - Abfragen von Datenbestaenden
//           |
//           +-csQuery         - Abfragen von Aufzaehlwerten
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */

#include "store/es_query.hpp"
#include "base/eb_elo.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_event.hpp"
#include "store/es_store.hpp"
#include "store/es_filter.hpp"


// Forward-Deklarationen
// ===========================================================================

class cEloElementDescription;

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition csQuery
// ---------------------------------------------------------------------------
//
// Realisiert eine abstrakte Abfrage von Datenbestaenden, die u.a. zum Fuellen
// von listenartigen Dialogelemente verwendet werden kann. Um eine konkrete
// Abfrage zu realisieren, muss diese Klasse entsprechend abgeleitet werden.
// Um den Verwaltungsaufwand moeglichst gering zu halten, wurden alle die
// Abfrage betreffenden Informationen (Datensaetze, Feld- und Gesamtbeschrei-
// bung) in eine Klasse "gepackt". Dies hat den Vorteil, dass ein die Abfrage
// benutzendes Objekt lediglich einen Zeiger auf ein csQuery-Objekt benoetigt,
// um alle benoetigten Informationen zu erhalten. Allerdings duerfen manche
// Methoden nur zu bestimmten Zeitpunkten aufgerufen werden (vgl. Kommentare
// in Klassendefinition).
//
//    Bezeichnung | Index | Art      | Beschreibung
//   -------------+-------+----------+----------------------------------
//    fldIconID   |  -4   | Default  | ID des dem Datensatz zugeord. Icons
//    fldDescr    |  -3   | Default  | Kurzbeschreibung des Datensatzes
//    fldName     |  -2   | Default  | Name des Datensatzes
//    fldKey      |  -1   | Default  | Schluesselwert des Datensatzes
//    fldField    |   0   | Optional | Erstes Feld der Abfrage
//    fldField+1  |   1   | Optional | Zweites Feld der Abfrage
//     :          |   :   |  :       |  :
//    fldField+n  |   n   | Optional | (n+1)-tes Feld der Abfrage
//
// Eine csQuery-Ableitung muss mindestens die Methoden onRewind(), onFetch()
// und onGetString() implementieren.
//
// cBase
//  +--csBaseStorage
//      +--csQuery
//
// ===========================================================================

class csFilter;

class __ECL_DLLEXPORT__ csQuery : public csBaseStorage, public cEventSource {
   ECL_DECLARE(csQuery,csBaseStorage)
   friend class csRow;

public:
   csQuery();
   csQuery(int flags);
   csQuery(const csQuery& other);
   ~csQuery();


   // Flags
   // =====

   enum FLAGS { fStart = csBaseStorage::fUser,
      fStopReq     = fStart << 0,  // Abfrage vorzeitig beenden
      fUnfiltered  = fStart << 1,  // Moegliche Query-Filter deaktivieren
      fUser        = fStart << 2   // Benutzerdefinierte Flags
   };


   // Ereignisgesteuertes Durchfuehren der Abfrage
   // ============================================
   // Beispiel fuer ereignisgesteuerte Abfrage:
   //
   //    main()
   //    {
   //       csMyListbox lb(...);
   //       csQuery q(...);
   //       if ( q.start(EVENT(&lb, (EVFUNC_RPI)lb.QueryFunc)) )
   //          print("Abfrage gestartet");
   //    }
   //
   //    int csMyListbox::QueryFunc(void *p1, int p2)
   //    {
   //       csQuery *query = (csQuery*)p1;
   //       csQuery::STATE state = (csQuery::STATE)p2;
   //       switch ( state ) {
   //        case csQuery::qsStart:   PrepareListbox(...); break;
   //        case csQuery::qsData:    AddDataToListbox(...); break;
   //        case csQuery::qsEnd:     CloseListbox(...); break;
   //       }
   //       return (int)true;  // false fuer Abbruch
   //    }

   enum STATE {
      qsInit,           // Vor dem ersten Start
      qsStart,          // Abfrage hat begonnen (vor erstem Datensatz)
      qsData,           // Naechster Datensatz bereit
      qsEnd             // Abfrage beendet (nach letztem Datensatz)
   };

   // Ereignisgesteuerte Abfrage starten
   bool start(const EVENT& event);
   // Ereignisgesteuerte Einzelabfrage starten
   bool start1(const EVENT& event, cString key);
   // Vorzeitiges Beenden der Abfrage vor dem naechsten Datensatz
   bool stop();


   // Sequentielles Durchfuehren der Abfrage
   // ======================================
   // Beispiel fuer sequentielle Abfrage:
   //
   //    main()
   //    {
   //       csMyListbox lb(...);
   //       csQuery q(...);
   //       q.open();
   //       PrepareListbox(...);
   //       while ( !q.next() ) {
   //          AddDataToListbox(...);
   //       }
   //       CloseListbox(...);
   //       q.close();
   //    }

   // Sequentielle Abfrage starten (Startposition: Vor dem ersten Datensatz)
   bool open();
   // Sequentielle Abfrage beenden
   void close();
   // An die Position vor den ersten Datensatz springen (wie close & open)
   bool rewind();
   // Zum naechsten Datensatz gehen und diesen laden
   bool fetch();

   // TBD: Support fuer scrolling cursors
   // bool move(int rel_pos);


   // Hierarchische Abfragen
   // ======================

   // Query-Modus: Erfragen der obersten Hierarchiestufe (Default)
   inline void setQueryFromTopLevel()
      { onSetParentKey(cString()); }
   // Query-Modus: Erfragen der Elemente, die sich auf 'parent_key' beziehen
   inline void setQueryFromKey(cString parent_key)
      { onSetParentKey(parent_key); }

   // Liefert true bei "echten" hierarchischen Abfragen (keine Subqueries)
   inline bool isStructured() const
      { return !!(onGetQueryStyle() & qstIsStructured); }
   // Liefert den Schluesselwert des Parent-Elementes (Leerstring fuer Top-Level)
   inline cString getParentKey() const
      { return onGetParentKey(); }


   // Filter
   // ======

   // Filter fuer eine Spalte erfragen
   csFilter *getFilter(int fld) const;
   // Filter fuer eine Spalte setzen
   bool setFilter(int fld, csFilter *filter);
   // Filter fuer eine Spalte wieder zuruecknehmen
   bool removeFilter(int fld);


   // Sortierung
   // ==========

   // Abfrage nach Spalte 'fld' sortieren (dir > 0: Aufsteigend, < 0: Absteigend)
   inline void orderBy(int fld, int dir = 1)
      { onSetOrder(&fld, &dir, 1); }
   // Sortierreihenfolge der Abfrage festlegen
   inline void setOrder(int fld[], int dir[], int count)
      { onSetOrder(fld, dir, count); }


   // Verfuegbarkeit von Informationen
   // ================================
   // Nicht alle Informationen der Query sind zu jeder Zeit verfuegbar.
   // Die folgenden Funktionen geben an, welche Information momentan
   // verfuegbar ist.

   // Ist die Gesamtbeschreibung der Query momentan verfuegbar?
   inline bool hasQueryInfos() const
      { return onCheckAvailability(qciQuery); }
   // Sind die Feldbeschreibungen momentan verfuegbar?
   inline bool hasFieldInfos() const
      { return onCheckAvailability(qciField); }
   // Sind momentan aktuelle Daten eines Datensatzes verfuegbar?
   inline bool hasData() const
      { return onCheckAvailability(qciData); }


   // Gesamtbeschreibung
   // ==================

   // Gesamttitel sichtbar?
   inline bool isTitleVisible() const
      { return !!(onGetQueryStyle() & qstTitleVisible); }
   // Spaltentitel sichtbar?
   inline bool isColumnTitleVisible() const
      { return !!(onGetQueryStyle() & qstColumnTitleVisible); }

   // Name der Abfrage ermitteln
   inline cString getName() const
      { return onGetQueryName(); }
   // ID des Default-Icons fuer Elemente ermitteln
   inline int getDefIconID() const
      { return onGetQueryDefIconID(); }
   // ELO-Elementbeschreibung der Query ermitteln
   inline const cEloElementDescription * getBaseDescription() const
      { return onGetQueryDescription(); }

   // Versucht den Wert des Schluesselfeldes 'key_name' zu ermitteln, ohne
   // dass ein Datensatz geladen sein muss (oder 0 falls nicht ermittelbar)
   inline cString getKeyValue(cString key_name) const
      { return onGetKeyValue(key_name); }


   // Feld- (=Spalten-) beschreibung
   // ==============================
   // Die folgenden Methoden duerfen nur aufgerufen werden, waehrend
   // eine Abfrage laeuft, d.h. zwischen den Events qsStart und qsEnd
   // bzw. zwischen open() und close()

   // Feld-Indizes
   // ------------

   enum FIELD_INDEX {
      fldField  =  0,   // (optional) Felder der Abfrage (n >= 0)
      fldKey    = -1,   // (default)  Schluesselwert des Datensatzes
      fldName   = -2,   // (default)  Name des Datensatzes
      fldDescr  = -3,   // (default)  Kurzbeschreibung des Datensatzes
      fldIconID = -4    // (default)  Dem Datensatz zugeordnetes Icon
   };

   // Eigenschaften der Felder
   // ------------------------

   // Ermittelt die Anzahl der Felder im Datensatz (excl. Default-Felder)
   inline int getFieldCount() const
      { return onGetQueryFieldCount(); }

   // Ermittelt den Typ eines Feldes
   inline TYPE getFieldType(int fld) const
      { return onGetFieldType(fld); }
   // Ermittelt die maximale Groesse eines Feldes
   inline int getFieldBufferSize(int fld) const
      { return onGetFieldBufferSize(fld); }
   // Ermittelt den Namen eines Feldes
   inline cString getFieldName(int fld) const
      { return onGetFieldName(fld); }
   // Darf das Feld einen NULL-Wert enthalten?
   inline bool isFieldNullable(int fld) const
      { return !(onGetFieldStyle(fld) & fstNotNull); }


   // Element-Anzeige
   // ---------------

   enum HALIGN { haLeft, haCenter, haRight };
   enum VALIGN { vaTop, vaCenter, vaBottom };

   // Guenstigste Anzeigebreite [Zeichen] (0=soviel wie noetig)
   inline int getFieldViewSize(int fld) const
      { return onGetFieldViewSize(fld); }
   // Horizontale Ausrichtung
   inline HALIGN getFieldHAlign(int fld) const
      { return onGetFieldHAlign(fld); }
   // Vertikale Ausrichtung
   inline VALIGN getFieldVAlign(int fld) const
      { return onGetFieldVAlign(fld); }
   // Spalte schreibgeschuetzt (nicht editierbar)?
   inline bool isFieldReadOnly(int fld) const
      { return !!(onGetFieldStyle(fld) & fstReadOnly); }
   // Spalte angezeigt?
   inline bool isFieldVisible(int fld) const
      { return !!(onGetFieldStyle(fld) & fstVisible); }
   // Spalte rechts durch vertikalen Separator abgegrenzt?
   inline bool hasFieldSeparator(int fld) const
      { return !!(onGetFieldStyle(fld) & fstSeparator); }
   // Maximale Feldbreite [Zeichen]
   inline int getFieldWidth(int fld) const
      { return onGetFieldWidth(fld); }
   // Anzahl Nachkommastellen [Zeichen]
   inline int getFieldPrec(int fld) const
      { return onGetFieldPrec(fld); }
   // Anzeigeposition: Zeile (-1 falls gleiche Zeile wie voriges Feld)

   inline int getFieldRow(int fld) const
      { return onGetFieldPos(fld, fpiDispRow); }
   // Anzeigeposition: Spalte (-1 falls naechste Spalte)
   inline int getFieldCol(int fld) const
      { return onGetFieldPos(fld, fpiDispCol); }
   // Zellenverbindung senkrecht: Anzahl weiterer Felder (0 = Default)
   inline int getFieldJoinRows(int fld) const
      { return onGetFieldPos(fld, fpiJoinRows); }
   // Zellenverbindung waagrecht: Anzahl weiterer Felder (0 = Default)
   inline int getFieldJoinCols(int fld) const
      { return onGetFieldPos(fld, fpiJoinCols); }

   // Titel-Anzeige
   // -------------

   // Titel der Spalte
   inline cString getTitleText(int fld) const
      { return onGetTitleText(fld); }
   // Horizontale Ausrichtung des Titels
   inline HALIGN getTitleHAlign(int fld) const
      { return onGetTitleHAlign(fld); }
   // Vertikale Ausrichtung des Titels
   inline VALIGN getTitleVAlign(int fld) const
      { return onGetTitleVAlign(fld); }
   // Titel schreibgeschuetzt (nicht editierbar)?
   inline bool isTitleReadOnly(int fld) const
      { return !!(onGetFieldStyle(fld) & fstTitleReadOnly); }
   // Titel durch horizontalen Separator abgegrenzt?
   inline bool hasTitleSeparator(int fld) const
      { return !!(onGetFieldStyle(fld) & fstTitleSeparator); }


   // Erfragefunktionen fuer aktuellen Datensatz
   // ==========================================
   // Die folgenden Methoden duerfen nur aufgerufen werden, wenn ein
   // Datensatz zur Verfuegung steht, d.h. nur beim Event qsData!

   // Datensatz
   // ---------

   // Kann der Datensatz Kind-Elemente haben (strukturierte Abfrage)?
   inline bool mayHaveChilds() const
      { return !!(onGetRecordStyle() & (rstMayHaveChilds | rstHasSubquery)); }
   // Hat der Datensatz eine Subquery zugeordnet?
   inline bool hasSubquery() const
      { return !!(onGetRecordStyle() & rstHasSubquery); }
   // Sollen die Kind-Elemente des Datensatzes automatisch angezeigt werden?
   inline bool mustAutoViewChilds() const
      { return !!(onGetRecordStyle() & rstAutoViewChilds); }
   // Subquery des Datensatzes erzeugen
   inline csQuery *newSubquery() const
      { return onNewRecordSubquery(); }
   // ELO-Elementbeschreibung des Datensatzes ermitteln
   inline const cEloElementDescription * getDescription() const
      { return onGetRecordDescription(); }

   // Laenge (Bytes) der benutzerspezifischen Zusatzinformationen erfragen
   inline int getUserDataLen() const
      { return onGetUserDataLen(); }
   // Benutzerspezifische Zusatzinformation ermitteln
   inline void *getUserData(void *buf, int buf_size) const
      { return onGetUserData(buf, buf_size); }
   // Icon-ID des Datensatzes ermitteln
   inline bool getIconID(int& buf) const
      { return onGetIconID(buf); }

   // Ermittelt den Basisnamen der einem Feld zugrundeliegenden Daten-
   // struktur (z.B. der Datenbank-Tabellenname). Dieser kann sich fuer
   // jeden Datensatz unterscheiden (z.B. bei SQL-UNION-Abfragen)
   inline cString getBaseName(int fld) const
      { return onGetRecordBaseName(fld); }
   // Ermittelt den Basisnamen eines Feldes in der zugrundeliegenden
   // Datenstruktur (z.B. der Datenbank-Feldname). Dieser kann sich fuer
   // jeden Datensatz unterscheiden (z.B. bei SQL-UNION-Abfragen)
   inline cString getBaseFieldName(int fld) const
      { return onGetRecordBaseFieldName(fld); }


   // Feldwerte
   // ---------

   // Hat das Feld einen NULL-Wert?
   inline bool isNull(int fld) const
      { return onGetNull(fld); }

   // Ermittelt den int-Wert eines Feldes
   bool get(int fld, int& buf) const;
   // Ermittelt den double-Wert eines Feldes
   bool get(int fld, double& buf) const;
   // Ermittelt den cTime-Wert eines Feldes
   bool get(int fld, cTime& buf) const;
   // Ermittelt den cDate-Wert eines Feldes
   bool get(int fld, cDate& buf) const;
   // Ermittelt den cDateTime-Wert eines Feldes
   bool get(int fld, cDateTime& buf) const;
   // Ermittelt den char-Wert eines Feldes
   bool get(int fld, char& buf) const;
   // Ermittelt den cString-Wert eines Feldes
   bool get(int fld, cString& buf) const;
   // Ermittelt die String-Repraesentation eines Feldes
   bool get(int fld, char *buf, int size) const;
   // Ermittelt den cIcon-Wert eines Feldes
   bool get(int fld, cIcon& buf) const;
   // Ermittelt den cBitmap-Wert eines Feldes
   bool get(int fld, cBitmap& buf) const;


   // Freigabesperre
   // ==============

   // Abfrage wird benutzt und darf bis auf weiteres nicht freigegeben werden
   void requestLock();
   // Abfrage wird nicht laenger benutzt und kann freigegeben werden
   void releaseLock(bool delete_now = false);


protected:

   // Zusaetzliche Events
   // ===================

   // Ereignisgesteuerte Abfragesteuerung
   // -----------------------------------

   // Wird aufgerufen, um ereignisgesteuerte Abfrage zu starten
   virtual bool onStart(const EVENT& event);
   // Wird aufgerufen, um ereignisgesteuerte Einzelabfrage zu starten
   virtual bool onStart1(const EVENT& event, cString key);
   // Wird aufgerufen zum vorzeitigen Beenden der Abfrage
   virtual bool onStop();

   // Wird aufgerufen, bevor Abfrage beginnt (vor erstem DS)
   virtual void onQueryStart(const EVENT& event);
   // Wird aufgerufen, wenn naechster Datensatz bereit
   virtual bool onQueryData(const EVENT& event);
   // Wird aufgerufen, wenn Abfrage beendet (nach letztem DS)
   virtual void onQueryEnd(const EVENT& event);


   // Sequentielle Abfragesteuerung
   // -----------------------------

   // Wird aufgerufen, um sequentielle Abfrage zu starten
   virtual bool onOpen();
   // Wird aufgerufen, um sequentielle Abfrage zu beenden
   virtual void onClose();
   // Wird aufgerufen, um an die Position vor dem ersten Datensatz zu springen
   virtual bool onRewind() = 0;
   // Wird aufgerufen, um zum naechsten Datensatz zu gehen und diesen laden
   virtual bool onFetch() = 0;


   // Hierarchische Abfragen
   // ----------------------

   // Wird aufgerufen, um den Schluessel des Parent-Elementes zu setzen
   void onSetParentKey(cString parent_key);
   // Wird aufgerufen, um den Schluessel des Parent-Elementes zu erfragen
   cString onGetParentKey() const;


   // Verfuegbarkeit von Informationen
   // --------------------------------

   // Moegliche Informationen
   enum QUERY_INFOS {
      qciQuery                = 0x0001,   // Gesamtbeschreibung verfuegbar?
      qciField                = 0x0002,   // Feldbeschreibungen verfuegbar?
      qciData                 = 0x0004    // Aktuelle Daten verfuegbar?
   };

   // Wird aufgerufen, um die aktuelle Verfuegbarkeit zu pruefen
   virtual bool onCheckAvailability(QUERY_INFOS qci) const;


   // Manipulation von Datensaetzen
   // -----------------------------

   // Wird aufgerufen, um den Schluesselwert eines neuen Datensatzes zu ermitteln
   virtual cString onGetNewRowKey() const;
   // Wird aufgerufen, wenn ein Datensatz hinzugefuegt wurde
   virtual void onRowAdded(csRow *row);
   // Wird aufgerufen, wenn sich ein Datensatz geaendert hat
   virtual void onRowChanged(csRow *row);
   // Wird aufgerufen, wenn ein Datensatz entfernt wurde
   virtual void onRowRemoved(csRow *row);


   // Sortierung
   // ----------

   // Wird aufgerufen, um die Sortierreihenfolge der Abfrage festzulegen
   virtual void onSetOrder(int *fld, int *dir, int count);


   // Beschreibung
   // ------------

   // Gesamtbeschreibung der Abfrage
   enum QUERY_STYLE {
      qstTitleVisible         = 0x0001,   // Gesamttitel sichtbar?
      qstColumnTitleVisible   = 0x0002,   // Spaltentitel sichtbar?
      qstIsStructured         = 0x0004    // Hierarchische Abfrage?
   };

   // Wird aufgerufen, um die Anzahl Felder im Datensatz zu ermitteln
   virtual int onGetQueryFieldCount() const;
   // Wird aufgerufen, um die Gesamtbeschreibung der Abfrage zu ermitteln (QUERY_STYLE)
   virtual int onGetQueryStyle() const;
   // Wird aufgerufen, um das Default-Icon fuer die Elemente der Abfrage zu ermitteln
   virtual cString onGetQueryName() const;
   // Wird aufgerufen, um die ID des Default-Icons fuer die Elemente der Abfrage zu ermitteln
   virtual int onGetQueryDefIconID() const;
   // Wird aufgerufen, um die ELO-Elementbeschreibung der Query zu ermitteln
   virtual const cEloElementDescription * onGetQueryDescription() const;
   // Wird aufgerufen, um den Wert des Schluesselfeldes 'key_name' zu ermitteln
   virtual cString onGetKeyValue(cString key_name) const;


   // Beschreibung des Datensatzes
   enum RECORD_STYLE {
      rstMayHaveChilds     = 0x0001,   // Kann der Datensatz Child-Elemente haben?
      rstHasSubquery       = 0x0002,   // Hat der Datensatz eine Subquery?
      rstAutoViewChilds    = 0x0004    // Child-Element automatisch anzeigen?
   };

   // Wird aufgerufen, um die Beschreibung des Datensatzs zu ermitteln (RECORD_STYLE)
   virtual int onGetRecordStyle() const;
   // Wird aufgerufen, um eine (neue) Subquery des Datensatzes zu erzeugen
   virtual csQuery *onNewRecordSubquery() const;
   // Wird aufgerufen, um die ELO-Elementbeschreibung des Datensatzes zu ermitteln
   virtual const cEloElementDescription * onGetRecordDescription() const;

   // Wird aufgerufen, um die Laenge (Bytes) der benutzerspezifischen Zusatzinformationen erfragen
   virtual int onGetUserDataLen() const;
   // Wird aufgerufen, um die benutzerspezifischen Zusatzinformation zu ermitteln
   virtual void *onGetUserData(void *buf, int buf_size) const;
   // Wird aufgerufen, um die Icon-ID des Datensatzes zu lesen
   virtual bool onGetIconID(int& buf) const;

   // Beschreibung eines Feldes
   enum FIELD_STYLE {
      fstReadOnly          = 0x0001,   // Spalte schreibgeschuetzt (nicht editierbar)?
      fstVisible           = 0x0002,   // Spalte angezeigt?
      fstSeparator         = 0x0004,   // Spalte durch vertikalen Separator abgegrenzt?
      fstTitleReadOnly     = 0x0008,   // Titel schreibgeschuetzt (nicht editierbar)?
      fstTitleSeparator    = 0x0010,   // Titel durch horizontalen Separator abgegrenzt?
      fstNotNull           = 0x0020    // Darf das Feld keine NULL-Wert enthalten?
   };

   // Wird aufgerufen, um die Beschreibung einer Spalte zu ermitteln (FIELD_STYLE)
   virtual int onGetFieldStyle(int fld) const;
   // Wird aufgerufen, um den Typ eines Feldes zu ermitteln
   virtual TYPE onGetFieldType(int fld) const;

   // Wird aufgerufen, um die horizontale Ausrichtung zu ermitteln
   virtual HALIGN onGetFieldHAlign(int fld) const;
   // Wird aufgerufen, um die vertikale Ausrichtung zu ermitteln
   virtual VALIGN onGetFieldVAlign(int fld) const;

   // Wird aufgerufen, um den Namen eines Feldes zu ermitteln
   virtual cString onGetFieldName(int fld) const;
   // Wird aufgerufen, um den Titel der Spalte zu ermitteln
   virtual cString onGetTitleText(int fld) const;
   // Wird aufgerufen, um die horizontale Ausrichtung des Titels zu ermitteln
   virtual HALIGN onGetTitleHAlign(int fld) const;
   // Wird aufgerufen, um die vertikale Ausrichtung des Titels zu ermitteln
   virtual VALIGN onGetTitleVAlign(int fld) const;

   // Wird aufgerufen, um den Tabellennamen eines Feldes zu ermitteln
   virtual cString onGetRecordBaseName(int fld) const;
   // Wird aufgerufen, um den Basisnamen eines Feldes zu ermitteln
   virtual cString onGetRecordBaseFieldName(int fld) const;

   // Wird aufgerufen, um die maximale Groesse eines Feldes zu ermitteln
   virtual int onGetFieldBufferSize(int fld) const;
   // Wird aufgerufen, um die guenstigste Anzeigebreite zu ermitteln
   virtual int onGetFieldViewSize(int fld) const;
   // Wird aufgerufen, um die maximale Feldbreite zu ermitteln
   virtual int onGetFieldWidth(int fld) const;
   // Wird aufgerufen, um die Anzahl Nachkommastellen zu ermitteln
   virtual int onGetFieldPrec(int fld) const;


   // Positionsinformation
   enum FIELD_POSINFO {
      fpiDispRow     = 1,  // Anzeigezeile des Feldes (-1 = Default)
      fpiDispCol     = 2,  // Anzeigespalte des Feldes (-1 = Default)
      fpiJoinRows    = 3,  // Anzahl zu verbindender Zellen senkrecht
      fpiJoinCols    = 4   // Anzahl zu verbindender Zellen waagrecht
   };

   // Wird aufgerufen, um Positionsinformationen ueber das Feld zu ermitteln
   virtual int onGetFieldPos(int fld, FIELD_POSINFO fpi) const;


   // Werte erfragen
   // --------------

   // Wird aufgerufen, um den NULL-Zustand des Feldes zu ermitteln
   virtual bool onGetNull(int fld) const;

   // Wird aufgerufen, um einen int-Wert aus Feld 'fld' zu lesen
   virtual bool onGetInt(int fld, int& buf) const;
   // Wird aufgerufen, um einen double-Wert aus Feld 'fld' zu lesen
   virtual bool onGetDouble(int fld, double& buf) const;
   // Wird aufgerufen, um einen cTime-Wert aus Feld 'fld' zu lesen
   virtual bool onGetTime(int fld, cTime& buf) const;
   // Wird aufgerufen, um einen cDate-Wert aus Feld 'fld' zu lesen
   virtual bool onGetDate(int fld, cDate& buf) const;
   // Wird aufgerufen, um einen cDateTime-Wert aus Feld 'fld' zu lesen
   virtual bool onGetDateTime(int fld, cDateTime& buf) const;
   // Wird aufgerufen, um einen char-Wert aus Feld 'fld' zu lesen
   virtual bool onGetChar(int fld, char& buf) const;
   // Wird aufgerufen, um einen cString-Wert aus Feld 'fld' zu lesen
   virtual bool onGetString(int fld, cString& buf) const = 0;
   // Wird aufgerufen, um einen cIcon-Wert aus Feld 'fld' zu lesen
   virtual bool onGetIcon(int fld, cIcon& buf) const;
   // Wird aufgerufen, um einen cBitmap-Wert aus Feld 'fld' zu lesen
   virtual bool onGetBitmap(int fld, cBitmap& buf) const;


   // Vereinfachte Query-Implementierung
   // ==================================
   // Zur leichteren Realisierung von einfachen Abfragen kann die Default-
   // Implementierung von onStart() herangezogen werden. Dazu muss die
   // Methode onLoop() ueberschrieben werden und immer, wenn eine neuer
   // Datensatz bereit steht, die Methode signalDataReady() aufgerufen
   // werden.
   //
   // class csMyQuery : csQuery {
   //    int actual;
   //    ...
   //    bool onLoop(const EVENT& event)
   //    {
   //       for ( actual = 0 ; actual < MAX  ; actual++ ) {
   //          if ( getFlags(fStopReq) )
   //             break;
   //          if ( !signalDataReady(event) )
   //             return false;
   //       }
   //       return true;
   //    }
   //    ...
   //    bool onGetString(int fld, cString& buf) const
   //    {
   //       buf = my_buffer[actual];
   //       return true;
   //    }
   // };

   // Wird aufgerufen, um die Hauptschleife der Abfrage zu realisieren
   virtual bool onLoop(const EVENT& event);
   // Muss von onLoop aufgerufen werden, um einen neuen Datensatz zu signalisieren
   bool signalDataReady(const EVENT& event);


protected:

   // Filterverwaltung
   // ================

   // Filtertabelle generieren
   bool installFilter(int field_count);
   // Filtertabelle verwerfen
   bool deinstallFilter();
   // Filterfunktion fuer Textfeld ausfuehren
   void callFilter(int fld, cString& text) const;
   // Filterfunktion fuer Icon-Feld ausfuehren
   void callFilter(int fld, cString key, cIcon& icon) const;
   // Filterfunktion fuer Bitmap-Feld ausfuehren
   void callFilter(int fld, cString key, cBitmap& bmp) const;
   // Maximale Feldgroesse nach Filterung berechnen
   int getFilteredBufferSize(int fld, int size) const;


private:

   struct FILTER_LIST {
      int fld;
      csFilter *filter;
      FILTER_LIST *next;
   };

   FILTER_LIST *flist_anchor;
   csFilter **filter_tab;
   cString parent_key;           // Parent-Key fuer hierarchische Abfragen

   STATE state;                  // Aktueller Zustand der Abfrage
   int lock_count;               // Zaehler fuer Freigabesperre

};

#endif /*__INTERFACE__*/


// Implementierung csQuery
// ===========================================================================

csQuery::csQuery() :
   csBaseStorage()
{
   state = qsInit;
   flist_anchor = NULL;
   filter_tab = NULL;
   lock_count = 0;
}

csQuery::csQuery(int _flags) :
   csBaseStorage(_flags)
{
   state = qsInit;
   flist_anchor = NULL;
   filter_tab = NULL;
   lock_count = 0;
}

csQuery::csQuery(const csQuery& other) :
   csBaseStorage(other)
{
   // Hinfällig???? -TE- 26.01.2001 query_func = other.query_func;

   state = qsInit;
   flist_anchor = NULL;
   filter_tab = NULL;
   lock_count = 0;

   // Kopie der Filter-Liste von 'other' erstellen
   FILTER_LIST **fl_ptr = &flist_anchor;
   for ( FILTER_LIST *fl = other.flist_anchor ; fl ; fl = fl->next ) {
      *fl_ptr = new0 FILTER_LIST;
      (*fl_ptr)->filter = fl->filter;
      (*fl_ptr)->fld = fl->fld;
      (*fl_ptr)->next = NULL;
      fl_ptr = &(*fl_ptr)->next;
   }
}

csQuery::~csQuery()
{
   __ECL_ASSERT2__(lock_count == 0, ("Trying to delete csQuery with lock_count = %d", lock_count));

   deinstallFilter();

   while ( flist_anchor ) {
      FILTER_LIST *fl = flist_anchor;
      flist_anchor = flist_anchor->next;
      if ( fl->filter && !fl->filter->isPermanent() )
         delete fl->filter;
      delete fl;
   }
}


// Ereignisgesteuertes Durchfuehren der Abfrage
// ============================================

bool csQuery::start(const EVENT& event)
{
   return onStart(event);
}

bool csQuery::start1(const EVENT& event, cString key)
{
   return onStart1(event, key);
}

bool csQuery::stop()
{
   return onStop();
}


// Sequentielles Durchfuehren der Abfrage
// ======================================

bool csQuery::open()
{
   return onOpen();
}

void csQuery::close()
{
   onClose();
}

bool csQuery::rewind()
{
   return onRewind();
}

bool csQuery::fetch()
{
   return onFetch();
}


// Query-Filter
// ============

#define FLD_OFFSET csQuery::fldIconID

bool csQuery::installFilter(int field_count)
{
   deinstallFilter();

   field_count -= FLD_OFFSET;

   if ( field_count > 0 && flist_anchor != NULL ) {
      if ( (filter_tab = new0 (csFilter *[field_count])) == NULL )
         return false;

      memset(filter_tab, 0, field_count * sizeof(csFilter *));

      for ( FILTER_LIST *fl = flist_anchor ; fl ; fl = fl->next )
         if ( fl->fld - FLD_OFFSET < field_count )
            filter_tab[fl->fld - FLD_OFFSET] = fl->filter;
   }

   return true;
}

bool csQuery::deinstallFilter()
{
   delete[] filter_tab;
   filter_tab = NULL;
   return true;
}

void csQuery::callFilter(int fld, cString& text) const
{
   if ( filter_tab && !getFlags(fUnfiltered) ) {
      csFilter *filter;
      if ( (filter = filter_tab[fld - FLD_OFFSET]) != NULL )
         filter->filter(this, text);
   }
}

void csQuery::callFilter(int fld, cString key, cIcon& icon) const
{
   if ( filter_tab && !getFlags(fUnfiltered) ) {
      csFilter *filter;
      if ( (filter = filter_tab[fld - FLD_OFFSET]) != NULL )
         filter->filter(this, key, icon);
   }
}

void csQuery::callFilter(int fld, cString key, cBitmap& bmp) const
{
   if ( filter_tab && !getFlags(fUnfiltered) ) {
      csFilter *filter;
      if ( (filter = filter_tab[fld - FLD_OFFSET]) != NULL )
         filter->filter(this, key, bmp);
   }
}

int csQuery::getFilteredBufferSize(int fld, int size) const
{
   if ( filter_tab && !getFlags(fUnfiltered) ) {
      csFilter *filter;
      if ( (filter = filter_tab[fld - FLD_OFFSET]) != NULL )
         return filter->calcSize(this, size);
   }

   return size;
}

csFilter * csQuery::getFilter(int fld) const
{
   FILTER_LIST *fl = flist_anchor;

   while ( fl && fl->fld != fld )
      fl = fl->next;

   return fl ?
      fl->filter
    : 0;
}

bool csQuery::setFilter(int fld, csFilter *filter)
{
   FILTER_LIST *fl = flist_anchor;

   while ( fl && fl->fld != fld )
      fl = fl->next;

   if ( !fl && (fl = new0 FILTER_LIST) != NULL) {
      fl->fld = fld;
      fl->next = flist_anchor;
      flist_anchor = fl;
   }

   if ( fl )
      fl->filter = filter;

   return fl != NULL;
}

bool csQuery::removeFilter(int fld)
{
   FILTER_LIST *fl = flist_anchor, *fl_prev = NULL;

   while ( fl && fl->fld != fld ) {
      fl_prev = fl;
      fl = fl->next;
   }

   if ( !fl )
      return false;

   if ( fl_prev == NULL ) {
      flist_anchor = fl->next;
   } else {
      fl_prev = fl->next;
   }

   if ( fl->filter && !fl->filter->isPermanent() )
      delete fl->filter;

   delete fl;
   return true;
}


// Feldwerte
// ---------

bool csQuery::get(int fld, int& buf) const
{
   return onGetInt(fld, buf);
}

bool csQuery::get(int fld, double& buf) const
{
   return onGetDouble(fld, buf);
}

bool csQuery::get(int fld, cTime& buf) const
{
   return onGetTime(fld, buf);
}

bool csQuery::get(int fld, cDate& buf) const
{
   return onGetDate(fld, buf);
}

bool csQuery::get(int fld, cDateTime& buf) const
{
   return onGetDateTime(fld, buf);
}

bool csQuery::get(int fld, char& buf) const
{
   return onGetChar(fld, buf);
}

bool csQuery::get(int fld, cString& buf) const
{
   if ( onGetString(fld, buf) ) {
      callFilter(fld, buf);
      return true;
   }

   return false;
}

bool csQuery::get(int fld, char *buf, int size) const
{
   cString str;

   if ( onGetString(fld, str) ) {
      callFilter(fld, str);
      strxcpy(buf, str.isEmpty() ? "" : str, size);
      return true;
   }

   return false;
}

bool csQuery::get(int fld, cIcon& buf) const
{
   if ( !onGetIcon(fld, buf) ) {
      cString key;
      bool rc = onGetString(fld, key);
      callFilter(fld, key, buf);
      return rc;
   }

   return true;
}

bool csQuery::get(int fld, cBitmap& buf) const
{
   if ( !onGetBitmap(fld, buf) ) {
      cString key;
      bool rc = onGetString(fld, key);
      callFilter(fld, key, buf);
      return rc;
   }

   return true;
}


// Anforderung/Freigabe
// ====================

// Anm.: Die Funktionen requestLock() und releaseLock() sind "sicher",
// d.h. sie koennen auch ueber einen 0-Zeiger aufgerufen werden.

void csQuery::requestLock()
{
   if ( this != 0 ) {
      lock_count++;
   }
}

void csQuery::releaseLock(bool delete_now)
{
   if ( this != 0 ) {
      // Wichtig: Nur loeschen, wenn delete_now gesetzt UND
      // die Query nicht als fPermanent markiert ist!
      if ( --lock_count <= 0 && delete_now && !getFlags(fPermanent) )
         delete this;
   }
}


// Zusaetzliche Events
// ===================

// Ereignisgesteuerte Abfragesteuerung
// -----------------------------------

// Die Default-Implementierung der ereignisgesteuerten Abfrage
// benutzt die Methoden der sequentiellen Abfrage.

bool csQuery::onStart(const EVENT& event)
{
   setFlags(fStopReq, false);
   onQueryStart(event);
   installFilter(getFieldCount());
   bool rc = onLoop(event);
   deinstallFilter();
   onQueryEnd(event);

   return rc;
}

bool csQuery::onStart1(const EVENT& event, cString key)
{
   bool rc = false;
   cString cur_key;

   setFlags(fStopReq, false);
   onQueryStart(event);
   installFilter(getFieldCount());

   if ( open() ) {
      while ( fetch() ) {
         if ( getFlags(fStopReq) )
            break;
         if ( get(fldKey, cur_key) && key == cur_key ) {
            rc = signalDataReady(event);
            break;
         }
      }
      close();
   }

   deinstallFilter();
   onQueryEnd(event);
   return false;
}

bool csQuery::onStop()
{
   setFlags(fStopReq);
   return true;
}

void csQuery::onQueryStart(const EVENT& event)
{
   state = qsStart;
   callEventR(event, this, qsStart);
}

bool csQuery::onQueryData(const EVENT& event)
{
   state = qsData;
   return !!callEventR(event, this, qsData);
}

void csQuery::onQueryEnd(const EVENT& event)
{
   state = qsEnd;
   callEventR(event, this, qsEnd);
}

bool csQuery::onLoop(const EVENT& event)
{
   if ( open() ) {
      while ( fetch() ) {
         if ( getFlags(fStopReq) )
            break;
         if ( !signalDataReady(event) )
            return false;
      }
      close();
   }

   return true;
}

bool csQuery::signalDataReady(const EVENT& event)
{
   return onQueryData(event);
}


// Sequentielle Abfragesteuerung
// -----------------------------

// Eine ableitende Klasse muss die Methoden onRewind()
// und onFetch() implementieren

bool csQuery::onOpen()
{
   // TBD: Filter installieren
   return rewind();
}

void csQuery::onClose()
{
   // TBD: Filter deinstallieren
}


// Hierarchische Abfragen
// ----------------------

void csQuery::onSetParentKey(cString parent_key)
{
   csQuery::parent_key = parent_key;
}

cString csQuery::onGetParentKey() const
{
   return parent_key;
}


// Verfuegbarkeit von Informationen
// --------------------------------

bool csQuery::onCheckAvailability(QUERY_INFOS qci) const
{
   switch ( qci ) {
   case qciQuery:
      return state >= qsStart;
   case qciField:
      return state >= qsStart;
   case qciData:
      return state == qsData;
   }

   return false;
}


// Manipulation von Datensaetzen
// -----------------------------

cString csQuery::onGetNewRowKey() const
{
   return cString();
}

void csQuery::onRowAdded(csRow * /*row*/)
{
}

void csQuery::onRowChanged(csRow * /*row*/)
{
}

void csQuery::onRowRemoved(csRow * /*row*/)
{
}


// Sortierung
// ----------

void csQuery::onSetOrder(int * /*fld*/, int * /*dir*/, int /*count*/)
{
   // Keine Default-Sortierung moeglich
}


// Beschreibung
// ------------

int csQuery::onGetQueryFieldCount() const
{
   // Defaultwert fuer einfache Abfragen, die nur aus den 4
   // Standardspalten (fldIconID..fldKey) bestehen

   return 0;
}

int csQuery::onGetQueryStyle() const
{
   // Defaultwert: Spaltentitel anzeigen

   return qstColumnTitleVisible;
}

cString csQuery::onGetQueryName() const
{
   // Defaultwert: Kein Name

   return cString();
}

int csQuery::onGetQueryDefIconID() const
{
   // Defaultwert: Kein Icon

   return 0;
}

const cEloElementDescription * csQuery::onGetQueryDescription() const
{
   // Defaultwert: Keine Query-Elementbeschreibung

   return 0;
}

cString csQuery::onGetKeyValue(cString key_name) const
{
   // Default: Leerstring (kein Namenskonzept fuer Schluessel auf dieser Ebene)

   return 0;
}

int csQuery::onGetRecordStyle() const
{
   // Defaultwert abhaengig von Strukturiert/nicht strukturiert

   return isStructured() ?
      rstMayHaveChilds
    : 0;
}

csQuery * csQuery::onNewRecordSubquery() const
{
   // Defaultwert: Datensatz hat keine Subquery

   return 0;
}

const cEloElementDescription * csQuery::onGetRecordDescription() const
{
   // Defaultwert: Keine Elementbeschreibung

   return 0;
}

int csQuery::onGetUserDataLen() const
{
   // Defaultwert: 0

   return 0;
}

void * csQuery::onGetUserData(void * /*buf*/, int /*buf_size*/) const
{
   // Defaultwert: void

   return 0;
}

bool csQuery::onGetIconID(int& buf) const
{
   const cEloElementDescription *descr = getDescription();

   if ( descr != 0 ) {
      buf = descr->getBitmapId(cEloBase::bsDefault);
      if ( buf < 0 ) buf = getDefIconID();
   } else {
      buf = getDefIconID();
   }

   return buf >= 0;
}

int csQuery::onGetFieldStyle(int fld) const
{
   // Defaultwerte fuer die 4 Standardspalten (fldIconID..fldKey)

   switch ( fld ) {
   case fldIconID:   return fstVisible | fstReadOnly;
   case fldDescr:    return 0;
   case fldName:     return 0;
   case fldKey:      return fstReadOnly;
   }

   return fstVisible;
}

csBaseStorage::TYPE csQuery::onGetFieldType(int fld) const
{
   // Defaultwerte fuer die 4 Standardspalten (fldIconID..fldKey)

   switch ( fld ) {
   case fldIconID:   return tInt;
   case fldDescr:    return tString;
   case fldName:     return tString;
   case fldKey:      return tString;
   }

   __ECL_ASSERT2__(true, ("csQuery::onGetFieldType: field %d: no field type", fld));
   return tNone;
}

csQuery::HALIGN csQuery::onGetFieldHAlign(int fld) const
{
   switch ( getFieldType(fld) ) {
    case tInt:    return haRight;
    case tDouble: return haRight;
   }

   return haLeft;
}

csQuery::VALIGN csQuery::onGetFieldVAlign(int /*fld*/) const
{
   return vaCenter;
}

cString csQuery::onGetFieldName(int /*fld*/) const
{
   return cString();
}

cString csQuery::onGetTitleText(int /*fld*/) const
{
   return cString();
}

csQuery::HALIGN csQuery::onGetTitleHAlign(int /*fld*/) const
{
   return haCenter;
}

csQuery::VALIGN csQuery::onGetTitleVAlign(int /*fld*/) const
{
   return vaCenter;
}

cString csQuery::onGetRecordBaseName(int /*fld*/) const
{
   return cString();
}

cString csQuery::onGetRecordBaseFieldName(int /*fld*/) const
{
   return cString();
}

int csQuery::onGetFieldBufferSize(int fld) const
{
   // Defaultwerte fuer die 4 Standardspalten (fldIconID..fldKey)

   switch ( fld ) {
   case fldIconID:   return getFilteredBufferSize(fld, sizeof(int));
   case fldDescr:    return getFilteredBufferSize(fld, onGetFieldBufferSize(fldName));
   case fldName:     return getFilteredBufferSize(fld, 32);
   case fldKey:      return getFilteredBufferSize(fld, 8);
   }

   __ECL_ASSERT2__(true, ("csQuery::onGetFieldBufferSize: field %d: no field buffer size", fld));
   return 0;
}

int csQuery::onGetFieldViewSize(int /*fld*/) const
{
   // Bestmoegliche Breite = 0
   return 0;
}

int csQuery::onGetFieldWidth(int fld) const
{
   switch ( (fld) ) {
    case tInt:    return 11;
    case tDouble: return 21;
   }

   return onGetFieldBufferSize(fld);
}

int csQuery::onGetFieldPrec(int fld) const
{
   switch ( getFieldType(fld) ) {
    case tDouble: return 3;
   }

   return 0;
}

int csQuery::onGetFieldPos(int /*fld*/, FIELD_POSINFO fpi) const
{
   switch ( fpi ) {

   case fpiDispRow:
      // Default: Ein Feld wird in der gleichen Zeile ausgegeben,
      // in der auch das vorige Feld ausgegeben wurde. Das erste
      // Feld wird in Zeile 0 ausgegeben.
      return -1;

   case fpiDispCol:
      // Default: Ein Feld wird in der naechsten freien Spalte
      // ausgegeben. Das erste Feld wird in Spalte 0 ausgegeben.
      return -1;

   case fpiJoinRows:
      // Default: Es werden keine Zellen senkrecht verbunden
      return 0;

   case fpiJoinCols:
      // Default: Es werden keine Zellen waagrecht verbunden
      return 0;

   }

   return 0;
}


// Werte erfragen
// --------------

bool csQuery::onGetNull(int /*fld*/) const
{
   return false;
}

bool csQuery::onGetInt(int fld, int& buf) const
{
   if ( fld == fldIconID ) {
      return onGetIconID(buf);
   } else {
      cString str;
      if ( onGetString(fld, str) ) {
         buf = atoi(str);
         return true;
      }
      return false;
   }
}

bool csQuery::onGetDouble(int fld, double& buf) const
{
   cString str;
   if ( onGetString(fld, str) ) {
      buf = atof(str);
      return true;
   }
   return false;
}

bool csQuery::onGetTime(int /*fld*/, cTime& /*buf*/) const
{
   // ???
   return false;
}

bool csQuery::onGetDate(int /*fld*/, cDate& /*buf*/) const
{
   // ???
   return false;
}

bool csQuery::onGetDateTime(int /*fld*/, cDateTime& /*buf*/) const
{
   // ???
   return false;
}

bool csQuery::onGetChar(int fld, char& buf) const
{
   cString str;
   if ( onGetString(fld, str) ) {
      buf = str[0];
      return true;
   }
   return false;
}

bool csQuery::onGetIcon(int /*fld*/, cIcon& /*buf*/) const
{
   return false;
}

bool csQuery::onGetBitmap(int /*fld*/, cBitmap& /*buf*/) const
{
   return false;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition csEnumQuery
// ---------------------------------------------------------------------------
//
// Einfache Abfrage, deren Elemente leicht ueber den Konstruktor definiert
// werden koennen. So kann z.B. eine Abfrage, welche die Namen der Wochentage
// "Montag".."Sonntag" liefert und als zugehoerige Schluessel die Werte 0..6
// erzeugt werden durch:
//
//    csEnumQuery *query = new csEnumQuery("Montag", "Dienstag", "Mittwoch",
//       "Donnerstag", "Freitag", "Samstag", "Sonntag", NULL);
//
// Die Schluesselelemente werden numerisch und in aufsteigender Reihenfolge ver-
// geben, beginnend mit 0. Sollen von dieser Vorschrift abweichende Schluessel
// benutzt werden, kann dies ueber "kodierte" Namen folgendermassen erfolgen:
//
//    csEnumQuery *query = new csEnumQuery("MON$Montag", "TUE$Dienstag",
//       "WED$Mittwoch", "THU$Donnerstag", "FRI$Freitag",
//       "SAT$Samstag", "SUN$Sonntag", NULL);
//
// cBase
//  +--csBaseStorage
//      +--csQuery
//          +--csEnumQuery
//
// ===========================================================================

class __ECL_DLLEXPORT__ csEnumQuery : public csQuery {
   ECL_DECLARE(csEnumQuery,csQuery)

public:

   // Konstruktor aus variabler Anzahl Strings
   csEnumQuery(const char *_str1, ...);
   // Konstruktor aus Flag und variabler Anzahl Strings
   csEnumQuery(int _flags, const char *_str1, ...);
   // Konstruktor aus Flag, Maximalgroessen und variabler Anzahl Strings
   csEnumQuery(int _flags, int max_key, int max_name, int max_descr, const char *_str1, ...);
   // Copy-Konstruktor
   csEnumQuery(const csEnumQuery& other);
   // Destruktor
   ~csEnumQuery();


   // Flags
   // =====

   enum FLAGS { fStart = csQuery::fUser,
      fEncodedKeys = fStart << 0,  // Schluessel in Enums kodiert: "key$name"
      fInclDescr   = fStart << 1,  // Jeder zweite Parameter enthaelt Beschr.
      fUser        = fStart << 2   // Benutzerdefinierte Flags
   };


protected:

   // Wird aufgerufen, um an die Position vor dem ersten Datensatz zu springen
   bool onRewind();
   // Wird aufgerufen, um zum naechsten Datensatz zu gehen und diesen laden
   bool onFetch();
   // Wird aufgerufen, um die maximale Groesse eines Feldes zu ermitteln
   int onGetFieldBufferSize(int fld) const;
   // Wird aufgerufen, um einen cString-Wert aus Feld 'fld' zu lesen
   bool onGetString(int fld, cString& buf) const;


protected:

   // Konstruktor ueber Flags (nur fuer Ableitungen)
   csEnumQuery(int flags);
   // Initialisierung ueber variable Argumentliste (nur fuer Ableitungen)
   void init(const char *str1, va_list arg_ptr);

   // Wert fuer maixmale Schluesselgroesse vorbelegen
   void setMaxKeySize(int max)
      { max_key_size = max; }
   // Wert fuer maixmale Namensgroesse vorbelegen
   void setMaxNameSize(int max)
      { max_name_size = max; }
   // Wert fuer maixmale Beschreibungsgroesse vorbelegen
   void setMaxDescrSize(int max)
      { max_descr_size = max; }


private:

   struct NODE {
      NODE() { }
      NODE(int _key, const char *_name, const char *_descr, bool _encoded_keys);
      char key[12];
      cString name, descr;
      NODE *next;
   };
   NODE *anchor, *actual;
   int max_key_size, max_name_size, max_descr_size;

};

#endif /*__INTERFACE__*/


// Implementierung csEnumQuery
// ===========================================================================

csEnumQuery::csEnumQuery(int flags) :
   csQuery(flags)
{
   max_key_size = 0;
   max_name_size = 0;
   max_descr_size = 0;
}

csEnumQuery::csEnumQuery(const char *_str1, ...) :
   csQuery(fEncodedKeys)
{
   va_list arg_ptr;

   max_key_size = 0;
   max_name_size = 0;
   max_descr_size = 0;

   va_start(arg_ptr, _str1);
   init(_str1, arg_ptr);
   va_end(arg_ptr);
}

csEnumQuery::csEnumQuery(int _flags, const char *_str1, ...) :
   csQuery(_flags)
{
   va_list arg_ptr;

   max_key_size = 0;
   max_name_size = 0;
   max_descr_size = 0;

   va_start(arg_ptr, _str1);
   init(_str1, arg_ptr);
   va_end(arg_ptr);
}

csEnumQuery::csEnumQuery(int _flags, int max_key, int max_name, int max_descr, const char *_str1, ...) :
   csQuery(_flags)
{
   va_list arg_ptr;

   max_key_size = max_key;
   max_name_size = max_name;
   max_descr_size = max_descr;

   va_start(arg_ptr, _str1);
   init(_str1, arg_ptr);
   va_end(arg_ptr);
}

csEnumQuery::csEnumQuery(const csEnumQuery& other) :
   csQuery(other)
{
   max_key_size = other.max_key_size;
   max_name_size = other.max_name_size;
   max_descr_size = other.max_descr_size;

   anchor = actual = NULL;

   // Kopie der Knoten-Liste von 'other' erstellen
   NODE **node_ptr = &anchor;
   for ( NODE *node = other.anchor ; node ; node = node->next ) {
      *node_ptr = new0 NODE;
      strcpy((*node_ptr)->key, node->key);
      (*node_ptr)->name = node->name;
      (*node_ptr)->descr = node->descr;
      (*node_ptr)->next = NULL;
      node_ptr = &(*node_ptr)->next;
   }
}

csEnumQuery::~csEnumQuery()
{
   NODE *next, *node = anchor;

   while ( node ) {
      next = node->next;
      delete node;
      node = next;
   }
}


void csEnumQuery::init(const char *str1, va_list arg_ptr)
{
   const char *str = str1;
   NODE *act, *last = NULL;
   int count = 0;

   anchor = actual = NULL;

   do {
      const char *descr = getFlags(fInclDescr) ?
         va_arg(arg_ptr, const char *) : NULL;

      act = new0 NODE(count++, str, descr, !!getFlags(fEncodedKeys));

      if ( (int)strlen(act->key) + 1 > max_key_size )
         max_key_size = strlen(act->key) + 1;
      if ( act->name.getLength() + 1 > max_name_size )
         max_name_size = act->name.getLength() + 1;
      if ( act->descr.getLength() + 1 > max_descr_size )
         max_descr_size = act->descr.getLength() + 1;

      if ( !anchor )
         anchor = act;
      if ( last )
         last->next = act;
      last = act;

      if ( getFlags(fInclDescr) && descr == NULL )
         break;
   } while ( (str = va_arg(arg_ptr, const char *)) != NULL );
}

csEnumQuery::NODE::NODE(int _key, const char *_name, const char *_descr,
   bool _encoded_keys)
{
   char *pname;

   if ( _encoded_keys && (pname = strchr(_name, '$')) != NULL ) {
      name = pname + 1;
      strxcpy(key, _name, sizeof key);
      if ( (pname = strchr(key, '$')) != NULL )
         *pname = '\0';
   } else {
      sprintf(key, "%d", _key);
      name = _name;
   }

   descr = _descr;
   next = NULL;
}

bool csEnumQuery::onRewind()
{
   actual = 0;
   return anchor != 0;
}

bool csEnumQuery::onFetch()
{
   actual = actual == 0 ? anchor : actual->next;
   return actual != 0;
}

int csEnumQuery::onGetFieldBufferSize(int fld) const
{
   int size = 0;

   switch ( fld ) {
   case fldDescr:    if ( !getFlags(fInclDescr) ) size = max_descr_size; break;
   case fldName:     size = max_name_size; break;
   case fldKey:      size = max_key_size; break;
   default:          return csQuery::onGetFieldBufferSize(fld);
   }

   return getFilteredBufferSize(fld, size);
}

bool csEnumQuery::onGetString(int fld, cString& buf) const
{
   if ( actual ) {
      switch ( fld ) {
      case fldDescr:    buf = actual->descr; return true;
      case fldName:     buf = actual->name; return true;
      case fldKey:      buf = actual->key; return true;
      }
   }

   return false;
}

