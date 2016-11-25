/*.SH.*/

/*
 *  Headerfile for module ew_editctls
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  ew_editctls.cpp on Thursday April 11 2002  00:00:56
 */

#ifndef __ew_editctls__
#define __ew_editctls__


// Headerfiles
// ===========================================================================

#include "store/es_query.hpp"
#include "win/ew_controls.hpp"


// ===========================================================================
// Definition cwEditCtl
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwEditCtl
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwEditCtl : public cwControl {
   ELO_DECLARE(cwEditCtl,cwControl)
   friend class ccwEditCtl;

public:

   // window-Flags
   // ============

   // Flags
   enum FLAGS { wflStart = cwControl::wflUser,
      wflHasDropButton  = wflStart << 0,  // Edit-Ctl hat Drop-Button (-> onDetailRequest)
      wflUser           = wflStart << 1   // Benutzerdefinierte Flags
   };


   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwControl::wsUser,
      wsAutoScrollHorz  = wsStart << 0,   // Automatisch horizontal Scrollen
      wsAutoScrollVert  = wsStart << 1,   // Automatisch vertikal Scrollen
      wsAlignLeft       = wsStart << 2,   // Textausrichtung Linksbuendig
      wsAlignCenter     = wsStart << 3,   // Textausrichtung mittig
      wsAlignRight      = wsStart << 4,   // Textausrichtung rechtsbuendig
      wsAlwaysShowSel   = wsStart << 5,   // Selektion stets anzeigen
      wsUser            = wsStart << 6    // Benutzerdefinierte Styles
   };


   // Events
   // ======

   // Event-IDs dieser Klasse
   enum EVENTS { evtFirst = cwControl::evtUser,
      evtEditChanged,         // (EVFUNC) Eingabefeld geaendert (vor Schirm-Update)
      evtEditUpdated,         // (EVFUNC) Eingabefeld geaendert (nach Schirm-Update)
      evtUser                 // Ab hier benutzerdefinierte Events
   };


   // Laenge/Position
   // ===============

   // Maximale Laenge des Eingabefeldes setzen
   inline void setLength(int max_len)
      { onSetLength(max_len); }
   // Maximale Laenge des Eingabefeldes erfragen
   inline int getLength() const
      { return onGetLength(); }
   // Aktuelle Position der Schreibmarke erfragen
   inline int getCurrentPos() const
      { return onGetCurrentPos(); }



   // Selektion
   // =========

   // Selektion setzen von Position 'start' bis 'end'
   inline void setSelection(int start = 0, int end = -1, bool no_scroll = false)
      { onSetSelection(start, end, no_scroll); }
   // Selektion komplett entfernen
   inline void removeSelection()
      { onSetSelection(-1, -1, false); }
   // Aktuelle Selektion erfragen
   inline void getSelection(int& start, int& end) const
      { onGetSelection(start, end); }
   // Aktuelle Startposition der Selektion erfragen
   inline int getSelStart() const
      { int start, end; getSelection(start, end); return start; }
   // Aktuelle Endposition der Selektion erfragen
   inline int getSelEnd() const
      { int start, end; getSelection(start, end); return end; }


/* TBD:
   void DropEmphasisEvt(HPS hps, bool on);
   bool VirtualKeyEvt(const cCmd& cmd, USHORT flags, USHORT& vk);
*/


protected:

   // Zusaetzliche Events
   // ===================

   // Eingabefeld geaendert, Bildschirm-Update steht bevor
   virtual void onEditChanged();
   // Eingabefeld geaendert, Bildschirm-Update ist ausgefuehrt
   virtual void onEditUpdated();

   // Wird aufgerufen, um die maximale Laenge des Eingabefeldes zu setzen
   virtual void onSetLength(int max_len) = 0;
   // Wird aufgerufen, um die maximale Laenge des Eingabefeldes zu erfragen
   virtual int onGetLength() const = 0;
   // Wird aufgerufen, um die aktuelle Position der Schreibmarke erfragen
   virtual int onGetCurrentPos() const;

   // Wird aufgerufen, um die Selektion zu setzen oder zu entfernen
   virtual void onSetSelection(int start, int end, bool no_scroll) = 0;
   // Aktuelle Selektion erfragen
   virtual void onGetSelection(int& start, int& end) const = 0;


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um bestimmte Window-Flags zu setzen
   void onSetFlags(int mask, bool set);
   // Wird aufgerufen, wenn Fenster den Focus erhaelt
   void onGainFocus();
   // Wird aufgerufen, wenn Fenster den Focus verliert
   void onLoseFocus();
   // Taste gedrueckt
   void onChar(cwCmdChar& cmd);

   // Daten des Controls refreshen
   bool onRefreshCtl(csStorage *store);
   // Daten des Controls pruefen
   DATAERR onCheckCtl(csStorage *store);
   // Daten des Controls speichern
   DATAERR onStoreCtl(csStorage *store);

   // Wird aufgerufen, nachdem das Storage-Objekt gesetzt wurde
   void onSetStorage(csStorage *store);
   // Wird aufgerufen, bevor das Storage-Objekt entfernt wird
   void onRemoveStorage(csStorage *store);

   // Wird aufgerufen, um den aktuellen ererbten Wert anzuzeigen
   void onShowInheritedVal();
   // Wird aufgerufen, um die Anzeige des ererbten Wertes zu beenden
   void onHideInheritedVal();

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);


protected:

   // Interner Konstruktor
   cwEditCtl(void *wnd);

};


// ===========================================================================
// Definition cwEditField
// ---------------------------------------------------------------------------
//
// Dieses Control unterstuetzt die Anzeige eines "ererbten Werten", der ueber
// die SetInheritedValue()-Methode gesetzt werden kann.
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwEditCtl
//              +--cwEditField
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwEditField : public cwEditCtl {
   ELO_DECLARE(cwEditField,cwEditCtl)

public:

   // Konstruktor
   cwEditField() : cwEditCtl(0) { init(); }
   // Destruktor
   ~cwEditField();


   // Allgemeines
   // ===========

   // Erzeugen des Eingabefeldes
   void create(cwWindow *parent, int id, csStorage *store = 0,
               int style = wsAutoScrollHorz, const cdRect& rect = cdRect());
   // Mit bestehendem Eingabefeld verknuepfen
   void attach(cwWindow *parent, int id, csStorage *store);


/*
   bool SetFirstChar(SHORT offset) { return (bool)SendMsg(EM_SETFIRSTCHAR, MPFROMSHORT(offset)); }
   SHORT GetFirstChar() const { return (bool)SendMsg(EM_QUERYFIRSTCHAR); }
   bool AdaptPosEvt(cPos& pos);
*/


protected:

   // Ueberschriebene Events
   // ======================

   // Eingabefeld geaendert, Bildschirm-Update steht bevor
   void onEditChanged();
   // Detailauswahl zum Control wurde angefordert
   void onDetailRequest();

   // Wird aufgerufen, um die maximale Laenge des Eingabefeldes zu setzen
   void onSetLength(int max_len);
   // Wird aufgerufen, um die maximale Laenge des Eingabefeldes zu erfragen
   int onGetLength() const;

   // Wird aufgerufen, um die Selektion zu setzen oder zu entfernen
   void onSetSelection(int start, int end, bool no_scroll);
   // Aktuelle Selektion erfragen
   void onGetSelection(int& start, int& end) const;

   // Changed-Flag loeschen (Control als unveraendert markieren)
   void onClearChanged();
   // Zustand des Changed-Flags erfragen
   bool onGetChanged() const;

   // ReadOnly-Zustand setzen
   void onSetReadOnly(bool ro_state);
   // ReadOnly-Zustand erfragen
   bool onGetReadOnly() const;

   // Entscheiden, ob das cwCmdChar-Kommando weiterverteilt werden soll
   bool onDispatchChar(const cwCmdChar& cmd);


protected:

   // Interner Konstruktor
   cwEditField(void *wnd);


private:

   int last_pos;

   // Initialisierung
   void init();

};


// ===========================================================================
// Definition cwEditBox
// ---------------------------------------------------------------------------
//
// Dieses Control unterstuetzt die Anzeige eines "ererbten Werten", der ueber
// die SetInheritedValue()-Methode gesetzt werden kann.
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwEditCtl
//              +--cwEditBox
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwEditBox : public cwEditCtl {
   ELO_DECLARE(cwEditBox,cwEditCtl)

public:

   // Konstruktor
   cwEditBox() : cwEditCtl(0) { init(); }
   // Destruktor
   ~cwEditBox();


   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwEditCtl::wsUser,
      wsInsertReturn    = wsStart << 0,   // Return als Eingabe akzeptieren
      wsUser            = wsStart << 1    // Benutzerdefinierte Styles
   };


   // Allgemeines
   // ===========

   // Erzeugen des Eingabefeldes
   void create(cwWindow *parent, int id, csStorage *store = 0,
               int style = wsAutoScrollVert, const cdRect& rect = cdRect());
   // Mit bestehendem Eingabefeld verknuepfen
   void attach(cwWindow *parent, int id, csStorage *store);


   // Zeilenumbruch
   // =============

   // Zeilenumbruch aktivieren/deaktivieren
   void setWrap(bool wrap);
   // Status des Zeilenumbruchs erfragen
   bool getWrap() const;


protected:

   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um die maximale Laenge des Eingabefeldes zu setzen
   void onSetLength(int max_len);
   // Wird aufgerufen, um die maximale Laenge des Eingabefeldes zu erfragen
   int onGetLength() const;

   // Wird aufgerufen, um die Selektion zu setzen oder zu entfernen
   void onSetSelection(int start, int end, bool no_scroll);
   // Aktuelle Selektion erfragen
   void onGetSelection(int& start, int& end) const;

   // Changed-Flag loeschen (Control als unveraendert markieren)
   void onClearChanged();
   // Zustand des Changed-Flags erfragen
   bool onGetChanged() const;

   // ReadOnly-Zustand setzen
   void onSetReadOnly(bool ro_state);
   // ReadOnly-Zustand erfragen
   bool onGetReadOnly() const;

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);


protected:

   // Interner Konstruktor
   cwEditBox(void *wnd);


private:

   // Initialisierung
   void init();

};


#endif

/*.EH.*/
