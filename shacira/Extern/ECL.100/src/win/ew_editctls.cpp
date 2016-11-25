// ===========================================================================
// ew_editctls.cpp                                              ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cwWindow
//        |
//        +-cwControl
//           |
//           +-cwEditCtl         - Basisklasse fuer ECL-Eingabefelder
//              |
//              +--cwEditField   - Eingabefeld fuer Texte, Zahlen und Datum
//              |
//              +--cwEditBox     - Eingabebereich fuer mehrzeilige Texte
//
// ===========================================================================

#include "win/ew_editctls.hpp"

#if defined __ECL_OS2__
   #include "win/system/pm/pm.hpp"
#elif defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
   #ifdef _DEBUG
      #define new DEBUG_NEW
      #undef THIS_FILE
      static char THIS_FILE[] = __FILE__;
   #endif
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "store/es_query.hpp"
#include "win/ew_controls.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

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

#endif /*__INTERFACE__*/


// Implementierung cwEditCtl
// ===========================================================================

cwEditCtl::cwEditCtl(void *wnd) :
   cwControl(wnd)
{
}


// Zusaetzliche Events
// ===================

void cwEditCtl::onEditChanged()
{
}

void cwEditCtl::onEditUpdated()
{
}

int cwEditCtl::onGetCurrentPos() const
{
   return getSelStart();
}


// Ueberschriebene Events
// ======================

/*
bool cwEditCtl::VirtualKeyEvt(const cCmd& cmd, USHORT flags, USHORT& vk)
{
   if ( vk == VK_F2 ) {
      cwWindow *next = GetWindow(rtNext);
      if ( next )
         next->SendMsg(BM_CLICK, MPFROMSHORT(true));
      return true;
   }

   return false;
}

void cwEditCtl::DropEmphasisEvt(HPS hps, bool on)
{
// DbgInfo("cwEditCtl::DropEmphasisEvt(%d)", on);

// GpiSetMix(hps, FM_XOR);
// GpiSetBackMix(hps, BM_LEAVEALONE);
   GpiSetColor(hps, on ? CLR_NEUTRAL : CLR_BACKGROUND);

   GpiMove(hps, cPoint(3,3));
   GpiBox(hps, DRO_OUTLINE, cPoint(GetWidth()-3, GetHeight()-3), 0, 0);
}
*/

void cwEditCtl::onSetFlags(int mask, bool set)
{
   if ( mask & wflHasDropButton ) {
      #if defined __ECL_W32__
         ((WCEdit*)_wnd)->ShowButton(set);
      #elif defined __ECL_OS2__
         // ???
      #endif
   }

   cwControl::onSetFlags(mask, set);
}

void cwEditCtl::onGainFocus()
{
   cwControl::onGainFocus();

   #ifdef SELECT_ALL_ONLY_IF_OVERWRITE
      if ( hasStorage() && getStorage()->forceOverwrite() )
         setSelection(0, -1, true);
   #else
      setSelection(0, -1, true);
   #endif
}

void cwEditCtl::onLoseFocus()
{
   if ( !isStorageReadOnly() && getChanged() )
      putStorageVal(getText());
   cwControl::onLoseFocus();
}

void cwEditCtl::onChar(cwCmdChar& cmd)
{
   int ch = 0;
   int curpos = getCurrentPos();

   if ( cmd.isChar() && cmd.isKeyDown() && (ch = cmd.getChar()) >= ' ' ) {
      if ( hasStorage() ) {
         csStorage *store = getStorage();
         if ( store->forceUppercase() )
            #if defined __ECL_W32__
               if ( islower(ch) )
                  cmd.setChar(ch = toupper(ch));
            #elif defined __ECL_OS2__
               cmd.setChar(ch = WinUpperChar(GetHab(), 0, 0, ch);
            #endif
         if ( store->forceLowercase() && isupper(ch) )
            cmd.setChar(ch = tolower(ch));
         if ( !store->isAllowedChar(curpos, char(ch)) )
            cmd.killChar();
      }
   }

   cwControl::onChar(cmd);
}

bool cwEditCtl::onRefreshCtl(csStorage *store)
{
   int len = store->getMaskLength();

   if ( len <= 0 ) {
      setEnable(false);
   } else {
      setEnable(true);
      setLength(len);
      if ( store->getType() == csStorage::tDate )
         setFlags(wflHasDropButton, true);
   }

   // Aufrufen der Parent-Methode _vor_ Setzen des Textes,
   // damit die Beschraenkung der EF-Laenge bereits wirksam ist.

   if ( !cwControl::onRefreshCtl(store) )
      return false;

   refreshInheritedValue(true);

   cString buf;
   if ( !store->get(buf) || store->isNull() )
      buf.clear();

   if ( !buf.isEmpty() ) {
      setText(buf);
   } else if ( !isMarkedAsInheritedValue() ) {
      setText(cString());
   }

   setSelection(0, -1, true);
   return true;
}

cwControl::DATAERR cwEditCtl::onCheckCtl(csStorage *store)
{
   if ( !isStorageReadOnly() && !store->isNullable() ) {
      if ( isMarkedAsInheritedValue() )
         return derrNotNull;
      if ( getText().isEmpty() )
         return derrNotNull;
   }

   return cwControl::onCheckCtl(store);
}

cwControl::DATAERR cwEditCtl::onStoreCtl(csStorage *store)
{
   refreshInheritedValue();

   if ( !isStorageReadOnly() ) {
      if ( !store->put(getText()) )
         return store->isNull() && !store->isNullable() ? derrNotNull : derrFormat;
   }

   return cwControl::onStoreCtl(store);
}

void cwEditCtl::onSetStorage(csStorage *store)
{
   if ( store->getType() == csStorage::tDate )
      setFlags(wflHasDropButton, true);
   cwControl::onSetStorage(store);
}

void cwEditCtl::onRemoveStorage(csStorage *store)
{
   if ( store->getType() == csStorage::tDate )
      setFlags(wflHasDropButton, false);
   cwControl::onRemoveStorage(store);
}

void cwEditCtl::onShowInheritedVal()
{
   setText(getInheritedValue());
}

void cwEditCtl::onHideInheritedVal()
{
   cString value;
   getStorageVal(value);
   setText(value);
}

int cwEditCtl::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      DWORD style = ((WCEdit*)_wnd)->GetStyle();

      if ( (mask & wsAutoScrollHorz) && (style & ES_AUTOHSCROLL) )
         rc |= wsAutoScrollHorz;
      if ( (mask & wsAutoScrollVert) && (style & ES_AUTOVSCROLL) )
         rc |= wsAutoScrollVert;
      if ( (mask & wsAlignLeft) && (style & ES_LEFT) )
         rc |= wsAlignLeft;
      if ( (mask & wsAlignCenter) && (style & ES_CENTER) )
         rc |= wsAlignCenter;
      if ( (mask & wsAlignRight) && (style & ES_RIGHT) )
         rc |= wsAlignRight;
      if ( (mask & wsAlwaysShowSel) && (style & ES_NOHIDESEL) )
         rc |= wsAlwaysShowSel;

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc | cwControl::onGetStyles(mask);
}

void cwEditCtl::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__

      if ( add & wsAutoScrollHorz )
         os_add[0] |= ES_AUTOHSCROLL;
      if ( add & wsAutoScrollVert )
         os_add[0] |= ES_AUTOVSCROLL;
      if ( add & wsAlignLeft )
         os_add[0] |= ES_LEFT;
      if ( add & wsAlignCenter )
         os_add[0] |= ES_CENTER;
      if ( add & wsAlignRight )
         os_add[0] |= ES_RIGHT;
      if ( add & wsAlwaysShowSel )
         os_add[0] |= ES_NOHIDESEL;

      if ( remove & wsAutoScrollHorz )
         os_remove[0] |= ES_AUTOHSCROLL;
      if ( remove & wsAutoScrollVert )
         os_remove[0] |= ES_AUTOVSCROLL;
      if ( remove & wsAlignLeft )
         os_remove[0] |= ES_LEFT;
      if ( remove & wsAlignCenter )
         os_remove[0] |= ES_CENTER;
      if ( remove & wsAlignRight )
         os_remove[0] |= ES_RIGHT;
      if ( remove & wsAlwaysShowSel )
         os_remove[0] |= ES_NOHIDESEL;

      cwControl::onModifyStyles(add, remove, os_add, os_remove);

   #elif defined __ECL_OS2__

      // ...

   #endif
}




#ifdef __INTERFACE__

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

#endif /*__INTERFACE__*/


// Implementierung cwEditField
// ===========================================================================

cwEditField::cwEditField(void *wnd) :
   cwEditCtl(wnd)
{
   last_pos = 0;
}

cwEditField::~cwEditField()
{
}

void cwEditField::init()
{
   last_pos = 0;

   #if defined __ECL_W32__
      _wnd = new WCEdit(this);
   #elif defined __ECL_OS2__
      // ...
   #endif
}


// Allgemeines
// ===========

void cwEditField::create(cwWindow *parent, int id, csStorage *store,
                         int style, const cdRect& rect)
{
   cwEditCtl::create(parent, id, store);

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);

      int mfc_style = WS_CHILD | WS_VISIBLE | WS_BORDER;
      if ( style & wsAutoScrollHorz )  mfc_style |= ES_AUTOHSCROLL;
      if ( style & wsAutoScrollVert )  mfc_style |= ES_AUTOVSCROLL;
      if ( style & wsAlignLeft )       mfc_style |= ES_LEFT;
      if ( style & wsAlignCenter )     mfc_style |= ES_CENTER;
      if ( style & wsAlignRight )      mfc_style |= ES_RIGHT;
      if ( style & wsAlwaysShowSel )   mfc_style |= ES_NOHIDESEL;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCEdit*)_wnd)->Create(mfc_style, mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create edit control"));

   #else
      // ...
   #endif
}

void cwEditField::attach(cwWindow *parent, int id, csStorage *store)
{
   cwEditCtl::attach(parent, id, store);
}


// Ueberschriebene Events
// ======================

void cwEditField::onEditChanged()
{
   cwEditCtl::onEditChanged();

   if ( hasStorage() && last_pos >= 0 ) {
      int pos = getCurrentPos();
      int last_pos = cwEditField::last_pos;
      cwEditField::last_pos = -1; // Mark as "in use"
      cString buf = getText();
      if ( pos == buf.getLength() ) {
         while ( pos >= last_pos ) {
            char auto_char = getStorage()->getAutomaticChar(pos);
            if ( auto_char == '\0' )
               break;
            buf += Str(auto_char);
            setText(buf);
            #if defined __ECL_W32__
               ((WCEdit*)_wnd)->SetModify(true);
            #endif
            pos++;
         }
         setSelection(pos+1);
      }
      cwEditField::last_pos = pos;
   }
}

void cwEditField::onDetailRequest()
{
   cwEditCtl::onDetailRequest();

   if ( getStorageType() == csStorage::tDate ) {
      #if defined __ECL_W32__
         bool orig_null = isStorageNull();
         cDate orig_date; getStorageVal(orig_date);
         WCMonthCalCtrl mcc((cwEditField*)this);
         if ( mcc.DoModal() == 0 ) {
            if ( orig_null ) {
               setStorageNull();
            } else {
               putStorageVal(orig_date);
            }
         }
      #endif
   }
}

void cwEditField::onSetLength(int max_len)
{
   #if defined __ECL_W32__
      ((WCEdit*)_wnd)->SetLimitText(max_len);
   #elif defined __ECL_OS2__
      SendMsg(EM_SETTEXTLIMIT, (SHORT)max_len, MPVOID);
   #endif
}

int cwEditField::onGetLength() const
{
   #if defined __ECL_W32__
      return ((WCEdit*)_wnd)->GetLimitText();
   #elif defined __ECL_OS2__
      // ...
   #endif
}

void cwEditField::onSetSelection(int start, int end, bool no_scroll)
{
   #if defined __ECL_W32__
      ((WCEdit*)_wnd)->SetSel(start, end, no_scroll);
   #elif defined __ECL_OS2__
      if ( start < 0 ) {
         SendMsg(EM_SETSEL, MPFROM2SHORT(0,0));
      } else {
         SendMsg(EM_SETSEL, MPFROM2SHORT(start,end));
      }
   #endif
}

void cwEditField::onGetSelection(int& start, int& end) const
{
   #if defined __ECL_W32__
      ((WCEdit*)_wnd)->GetSel(start, end);
   #elif defined __ECL_OS2__
      MRESULT sel = SendMsg(EM_QUERYSEL);
      start = SHORT1FROMMR(mr);
      end = SHORT2FROMMR(mr);
   #endif
}

void cwEditField::onClearChanged()
{
   #if defined __ECL_W32__
      ((WCEdit*)_wnd)->SetModify(false);
   #elif defined __ECL_OS2__
      SendMsg(EM_QUERYCHANGED);
   #endif
}

bool cwEditField::onGetChanged() const
{
   #if defined __ECL_W32__
      return !!((WCEdit*)_wnd)->GetModify();
   #elif defined __ECL_OS2__
      return (bool)SendMsg(EM_QUERYCHANGED);
   #endif
}

void cwEditField::onSetReadOnly(bool ro_state)
{
   #if defined __ECL_W32__
      ((WCEdit*)_wnd)->SetReadOnly(ro_state);
   #elif defined __ECL_OS2__
      SendMsg(EM_SETREADONLY, MPFROMSHORT(ro_state));
   #endif

   cwControl::onSetReadOnly(ro_state);
}

bool cwEditField::onGetReadOnly() const
{
   #if defined __ECL_W32__
      return !!(((WCEdit*)_wnd)->GetStyle() & ES_READONLY);
   #elif defined __ECL_OS2__
      return (bool)SendMsg(EM_QUERYREADONLY);
   #endif
}

bool cwEditField::onDispatchChar(const cwCmdChar& cmd)
{
   if ( cmd.isVirt() && cmd.isKeyDown()  ) {
      switch ( cmd.getVirt() ) {
      case cwCmdChar::vkUp:
      case cwCmdChar::vkDown:
         onNavKey(cmd.getVirt());
         callEvent(evtNavKeyPressed, cmd.getVirt());
         if ( getFlags(wflEatNavKeys) )
            return false;
         break;
      default: break;
      }
   }

   return cwEditCtl::onDispatchChar(cmd);
}




#ifdef __INTERFACE__

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

#endif /*__INTERFACE__*/


// Implementierung cwEditBox
// ===========================================================================

cwEditBox::cwEditBox(void *wnd) :
   cwEditCtl(wnd)
{
}

cwEditBox::~cwEditBox()
{
}

void cwEditBox::init()
{
   #if defined __ECL_W32__
      _wnd = new WCEdit(this);
   #elif defined __ECL_OS2__
      // ...
   #endif
}


// Allgemeines
// ===========

void cwEditBox::create(cwWindow *parent, int id, csStorage *store,
                         int style, const cdRect& rect)
{
   cwEditCtl::create(parent, id, store);

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);

      int mfc_style = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE;
      if ( style & wsAutoScrollHorz )  mfc_style |= ES_AUTOHSCROLL;
      if ( style & wsAutoScrollVert )  mfc_style |= ES_AUTOVSCROLL;
      if ( style & wsAlignLeft )       mfc_style |= ES_LEFT;
      if ( style & wsAlignCenter )     mfc_style |= ES_CENTER;
      if ( style & wsAlignRight )      mfc_style |= ES_RIGHT;
      if ( style & wsAlwaysShowSel )   mfc_style |= ES_NOHIDESEL;
      if ( style & wsInsertReturn )    mfc_style |= ES_WANTRETURN;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCEdit*)_wnd)->Create(mfc_style, mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create edit control"));

   #else
      // ...
   #endif
}

void cwEditBox::attach(cwWindow *parent, int id, csStorage *store)
{
   cwEditCtl::attach(parent, id, store);
}


// Zeilenumbruch
// =============

void cwEditBox::setWrap(bool wrap)
{
   #if defined __ECL_W32__
      // ???
   #elif defined __ECL_OS2__
      SendMsg(MLM_SETWRAP, wrap);
   #endif
}

bool cwEditBox::getWrap() const
{
   #if defined __ECL_W32__
      return true; // ???
   #elif defined __ECL_OS2__
      return (bool)SendMsg(MLM_QUERYWRAP);
   #endif
}


// Ueberschriebene Events
// ======================

void cwEditBox::onSetLength(int max_len)
{
   #if defined __ECL_W32__
      ((WCEdit*)_wnd)->SetLimitText(max_len);
   #elif defined __ECL_OS2__
      SendMsg(MLM_SETTEXTLIMIT, max);
   #endif
}

int cwEditBox::onGetLength() const
{
   #if defined __ECL_W32__
      return ((WCEdit*)_wnd)->GetLimitText();
   #elif defined __ECL_OS2__
      return (int)SendMsg(MLM_QUERYTEXTLENGTH);
   #endif
}

void cwEditBox::onSetSelection(int start, int end, bool no_scroll)
{
   #if defined __ECL_W32__
      ((WCEdit*)_wnd)->SetSel(start, end, no_scroll);
   #elif defined __ECL_OS2__
      // ???
   #endif
}

void cwEditBox::onGetSelection(int& start, int& end) const
{
   #if defined __ECL_W32__
      ((WCEdit*)_wnd)->GetSel(start, end);
   #elif defined __ECL_OS2__
      start = end = 0; // ???
   #endif
}

void cwEditBox::onClearChanged()
{
   #if defined __ECL_W32__
      ((WCEdit*)_wnd)->SetModify(false);
   #elif defined __ECL_OS2__
      SendMsg(MLM_SETCHANGED, MPFROMSHORT(false));
   #endif
}

bool cwEditBox::onGetChanged() const
{
   #if defined __ECL_W32__
      return !!((WCEdit*)_wnd)->GetModify();
   #elif defined __ECL_OS2__
      return (bool)SendMsg(MLM_QUERYCHANGED);
   #endif
}

void cwEditBox::onSetReadOnly(bool ro_state)
{
   #if defined __ECL_W32__
      ((WCEdit*)_wnd)->SetReadOnly(ro_state);
   #elif defined __ECL_OS2__
      SendMsg(MLM_SETREADONLY, MPFROMSHORT(ro_state));
   #endif
}

bool cwEditBox::onGetReadOnly() const
{
   #if defined __ECL_W32__
      return !!(((WCEdit*)_wnd)->GetStyle() & ES_READONLY);
   #elif defined __ECL_OS2__
      return (bool)SendMsg(MLM_QUERYREADONLY);
   #endif
}

int cwEditBox::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      DWORD style = ((WCEdit*)_wnd)->GetStyle();

      if ( (mask & wsInsertReturn) && (style & ES_WANTRETURN) )
         rc |= wsInsertReturn;

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc | cwControl::onGetStyles(mask);
}

void cwEditBox::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__

      if ( add & wsInsertReturn )
         os_add[0] |= ES_WANTRETURN;

      if ( remove & wsInsertReturn )
         os_remove[0] |= ES_WANTRETURN;

      cwControl::onModifyStyles(add, remove, os_add, os_remove);

   #elif defined __ECL_OS2__

      // ...

   #endif
}







/*
cwEditBox::cwEditBox(cwWindow *_parent, ULONG _id, csStorage *_store,
      ULONG _style, const char *_text, cwWindow *_owner) :
   cwEditCtl(WC_MLE, _parent, _id, _style, _store, _text, _owner)
{
   SetFormat(MLFIE_NOTRANS);
   ClearChanged();
}

MRESULT cwEditBox::ControlHandler(const cCmd& cmd)
{
   switch ( cmd.notify.code ) {
    case MLN_CHANGE:    ChangeEvt(); return NULL;
    case MLN_SETFOCUS:  break;
    case MLN_KILLFOCUS: break;
   }

   return cwEditCtl::ControlHandler(cmd);
}

cString cwEditBox::GetText()
{
   LONG ipt = 0;
   ULONG text_len = GetFormatLength(0, GetLength()), act_len = text_len;
   char *text = (char *)malloc(text_len+1);

   if ( !text || !SetBuffer(text, text_len) )
      return cString(NULL);

   ExportText(&ipt, &act_len);
   text[text_len] = '\0';

   cString new_text(text, text_len);
   free(text);

   return new_text;
}

void cwEditBox::GainFocusEvt()
{
   cwEditCtl::GainFocusEvt();
   PostMsg(MLM_SETSEL, (ULONG)0, (ULONG)4096); // Selektion setzen
}

void cwEditBox::LoseFocusEvt()
{
   if ( HasStorage() && !GetStorage()->ReadOnly() && GetChanged() )
      GetStorage()->Put(GetText());
   cwEditCtl::LoseFocusEvt();
}

*/




