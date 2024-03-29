/*.SH.*/

/*
 *  Headerfile for module edb_dml
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  edb_dml.cpp on Thursday January 17 2002  13:12:43
 */

#ifndef __edb_dml__
#define __edb_dml__


// Headerfiles
// ===========================================================================

#include "dbi/edb_cursor.hpp"
#include "dbi/edb_transaction.hpp"


// ===========================================================================
// cdbDML
// ---------------------------------------------------------------------------
//
// Ausfuehren eines Befehls zur Datenmanipulation (DML-Befehl). Dies sind
// insbesondere die SQL-Befehle SELECT, INSERT, DELETE und UPDATE, koennen
// jedoch auch spezielle Anweisungen wie Aufrufe von Stored Procedures o.ae.
// sein. Die Abarbeitung der DML-Befehle erfolgt in einem Hintergrund-Thread
// durch Benutzung eines cdbTransaction-Objektes.
//
// cBase
//  +--csBaseStorage
//      +--cdbDML
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbDML : public csBaseStorage, public cdbTAObject {
   ECL_DECLARE(cdbDML,csBaseStorage)

public:

   // Konstruktor ueber TA-Zeiger
   cdbDML(cdbTransaction *ta, SQL::STMT stmt = SQL::STMT(), int flags = 0);
   // Konstruktor ueber TA-Referenz
   cdbDML(cdbTransaction& ta, SQL::STMT stmt = SQL::STMT(), int flags = 0);
   // Destruktor
   ~cdbDML();


   // Parameter- und Ergebnisvariablen
   // ================================

   // Binden einer Ergebnisvariablen
   void define(int n, csStorage *store);
   // Binden einer Parametervariablen
   void bind(int n, csStorage *store);


   // Ausfuehrungskontrolle
   // =====================

   // Asynchrones Starten der Datenmanipulation
   void start(const cEventTarget::EVENT& event = cEventTarget::EVENT());
   // Synchrones Starten der Datenmanipulation
   bool call(const cEventTarget::EVENT& event = cEventTarget::EVENT());


   // Sonstiges
   // =========

   // Auszufuehrendes SQL-Statement erfragen
   inline SQL::STMT getSQL() const
      { return stmt; }

   // Anzahl gebundener Ergebnisvariablen erfragen
   int getDefineCount() const;
   // Anzahl gebundener Parametervariablen erfragen
   int getBindCount() const;


protected:

   // Hinzugefuegte Events
   // ====================

   // Waehrend der Bearbeitung des DML-Befehls werden die folgenden
   // Event-Methoden aufgerufen:
   //
   //  - onEnter: Nach Kompilation des SQL-Statements besteht hier die
   //    Moeglichkeit, Variablenbindungen vorzunehmen oder andere Aktionen
   //    mit dem cdbCursor-Objekt durchzufuehren. Die onEnter()-Methode
   //    der Basisklasse fuehrt die Bindung der ueber die define()- bzw.
   //    bind()-Methoden angegebenen Variablen durch.
   //
   //  - onExec: Diese Methode wird aufgerufen, um die Bearbeitung des
   //    DML-Befehls durchzufuehren. Die onExec()-Methode der Basisklasse
   //    fuehrt ein cdbCursor-Exec aus sowie, sofern mindestens eine
   //    Ergebnisvariable gebunden wurde, einen einmaligen cdbCursor-Fetch.
   //    Diese Verarbeitung duerfte fuer die meisten Anwendungsfaelle aus-
   //    reichen, bei denen lediglich ein einzelner Datensatz abgefragt
   //    werden oder ein INSERT, DELETE und UPDATE ausgefuehrt werden soll.
   //
   //  - onLeave: Hier besteht die Moeglichkeit, Aktionen nach Beendigung
   //    des DML-Befehls auszufuehren. Die onLeave()-Methode der Basisklasse
   //    liefert einfach nur true zurueck.

   // Wird aufgerufen, um Parameter- oder Ergebnisvariablen zu binden
   virtual bool onEnter(cdbCursor& cu);
   // Wird aufgerufen, um das SQL-Statement auszufuehren
   virtual bool onExec(cdbCursor& cu);
   // Wird aufgerufen, um die Verarbeitung abzuschliessen
   virtual bool onLeave(cdbCursor& cu);


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um die Aktion 'func' auszufuehren
   void onExecAction(cdbDatabase *db, int func);
   // Wird aufgerufen, um den Abbruch der aktuellen Aktion anzufordern
   void onStopAction();
   // Wird aufgerufen, um eine textuelle Signatur der Aktion zu ermitteln
   cString onGetSignature();


private:

   SQL::STMT stmt;            // Auszufuehrendes SQL-Statement
   cdbCursor *current_cu;     // Zeiger auf aktuellen Cursor (oder 0)
   cErrBase last_error;       // Zuletzt aufgetretener Fehler
   bool last_rc;              // Letzter Rueckgabestatus

   struct VARS;
   VARS *define_vars;         // Zeiger auf Feld mit Ergebnisvariablen
   VARS *bind_vars;           // Zeiger auf Feld mit Parametervariablen

};


#endif

/*.EH.*/
