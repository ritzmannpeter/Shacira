// ===========================================================================
// ew_lboxctls.cpp                                              ______ /  ECL
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
//           +-cwListCtl   - Basisklasse fuer ECL-Listen-Controls
//
// ===========================================================================

#include "win/ew_lboxctls.hpp"

#if defined __ECL_OS2__
   #include "win/system/pm/pm.hpp"
#elif defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "win/ew_listctls.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwListBox
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwListCtl
//              +--cwListBox
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwListBox : public cwListCtl {
   ELO_DECLARE(cwListBox,cwListCtl)
   friend class ccwListBox;

public:

   // Konstruktor
   inline cwListBox() : cwListCtl(0) { init(); }
   // Destruktor
   virtual ~cwListBox();


   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwListCtl::wsUser,
      wsLbxSingleSel    = wsStart << 0,   // Maximal 1 selektiertes Element
      wsLbxMultipleSel  = wsStart << 1,   // Mehrere selektierte Elemente
      wsLbxExtendedSel  = wsStart << 2,   // Auswahl erweitern mit SHIFT
      wsUser            = wsStart << 3    // Benutzerdefinierte Styles
   };


   // Allgemeines
   // ===========

   // Erzeugen des Controls
   void create(cwWindow *parent, int id, csStorage *store = 0, csQuery *query = 0,
               int style = wsChild | wsVisible | wsBorder, const cdRect& rect = cdRect());


protected:

   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, wenn ein Element selektiert wurde
   void onSelectionChanged(cwListElem *elem);
   // Wird aufgerufen, wenn Enter gedrueckt wurde oder bei Doppelklick
   void onListElemSelected(cwListElem *elem);

   // Wird aufgrufen, um die Anzahl der selektierten Elemente zu ermitteln
   int onGetSelectedElemCount(bool walk) const;
   // Wird aufgerufen, um die selektierten Elemente zu ermitteln
   cwListElem *onGetSelectedElem(cwListElem *elem = 0, bool walk = false) const;
   // Wird aufgerufen, um die Selektion fuer ein einzelnes Element zu aendern
   bool onSelectElem(cwListElem *elem, bool sel);
   // Wird aufgerufen, um die Selektion fuer alle Elemente zu aendern
   bool onSelectAllElems(bool sel, cwListElem *parent, bool walk);

   // Wird aufgerufen, um das Element mit Cursor zu erfragen
   cwListElem *onGetCursoredElem() const;
   // Wird aufgerufen, um den Cursor auf ein Element zu setzen
   bool onSetCursoredElem(cwListElem *elem);

   // Wird aufgerufen, um ein Element an Position 'pos', 'ref_elem' anzuzeigen
   bool onInsertElemAt(int pos, cwListElem *ref_elem, cwListElem *new_elem, cwListElem *parent, bool invd);
   // Wird aufgerufen, um ein Element von der Anzeige zu entfernen
   bool onRemoveElem(cwListElem *elem, bool invd);
   // Wird aufgerufen, um alle Elemente von der Anzeige zu entfernen
   bool onRemoveAllElems(cwListElem *parent, bool invd);

   // Wird aufgerufen, wenn die Abfrage gestartet wurde, um den Listeninhalt zu loeschen
   bool onQueryStarted(csQuery *query);
   // Wird aufgerufen, wenn die Abfrage beendet ist, um die Selektion anzeigen
   bool onQueryEnded(csQuery *query);

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um die OS-spezifischen Styles aus den ECL-Styles zu ermitteln
   void onMakeStyles(int styles, int os_styles[]) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);


protected:

   // Interner Konstruktor
   cwListBox(void *wnd);

private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwListBox
// ===========================================================================

cwListBox::cwListBox(void *wnd) :
   cwListCtl(wnd)
{
}

cwListBox::~cwListBox()
{
}

void cwListBox::init()
{
   #if defined __ECL_W32__
      _wnd = new WCListBox(this);
   #elif defined __ECL_OS2__
      // ...
   #endif
}


// Allgemeines
// ===========

void cwListBox::create(cwWindow *parent, int id, csStorage *store, csQuery *query,
                       int style, const cdRect& rect)
{
   cwListCtl::create(parent, id, store, query);

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);
      int mfc_style[2]; onMakeStyles(style, mfc_style);
      mfc_style[0] |= LBS_NOINTEGRALHEIGHT;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCListBox*)_wnd)->Create(mfc_style[0], mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create list box control"));

   #else
      // ...
   #endif
}


// Ueberschriebene Events
// ======================

void cwListBox::onSelectionChanged(cwListElem *elem)
{
/* TBD: Kann entfallen, wird bereits in Basisklasse gemacht:
   cString key;

   if ( elem && !isStorageReadOnly() && !(key = elem->getKey()).isEmpty() )
      putStorageVal(key);
*/
   cwListCtl::onSelectionChanged(elem);
}

void cwListBox::onListElemSelected(cwListElem *elem)
{
/* TBD: Kann entfallen, wird bereits in Basisklasse gemacht:
   cString key;

   if ( elem && !isStorageReadOnly() && !(key = elem->getKey()).isEmpty() )
      putStorageVal(key);
*/
   cwListCtl::onListElemSelected(elem);
}


// Selektion
// ---------

int cwListBox::onGetSelectedElemCount(bool /*walk*/) const
{
   #if defined __ECL_W32__
      if ( getStyles(wsLbxSingleSel) ) {
         return ((WCListBox*)_wnd)->GetCurSel() != LB_ERR ? 1 : 0;
      } else {
         return ((WCListBox*)_wnd)->GetSelCount();
      }
   #else if defined __ECL_OS2__
      return cwListCtl::onGetSelectedElemCount(walk);
   #endif
}

cwListElem * cwListBox::onGetSelectedElem(cwListElem *elem, bool /*walk*/) const
{
   #if defined __ECL_W32__
      int idx;
      if ( elem == 0 ) {
         elem = getFirstElem();
         idx = 0;
      } else {
         elem = getNextElem(elem);
         idx = getElemCountFromBegin(elem);
      }
      while ( elem != 0 ) {
         if ( ((WCListBox*)_wnd)->GetSel(idx) > 0 )
            return elem;
         elem = getNextElem(elem);
         idx++;
      }
      return 0;
   #else if defined __ECL_OS2__
      int idx = elem ? getElemCountFromBegin(elem) : LIT_FIRST;
      return GetItemHandle(GetLbxSelection(idx));
   #endif
}

bool cwListBox::onSelectElem(cwListElem *elem, bool sel)
{
   #if defined __ECL_W32__
      if ( getStyles(wsLbxSingleSel) ) {
         return __ECL_ASSERT1__(((WCListBox*)_wnd)->SetCurSel(getElemCountFromBegin(elem)) != LB_ERR);
      } else {
         return __ECL_ASSERT1__(((WCListBox*)_wnd)->SetSel(getElemCountFromBegin(elem), sel) != LB_ERR);
      }
   #else if defined __ECL_OS2__
      return SetLbxSelection(getElemCountFromBegin(elem), sel);
   #endif
}

bool cwListBox::onSelectAllElems(bool sel, cwListElem * /*parent*/, bool /*walk*/)
{
   #if defined __ECL_W32__
      if ( __ECL_ASSERT1__(!getStyles(wsLbxSingleSel)) ) {
         return __ECL_ASSERT1__(((WCListBox*)_wnd)->SetSel(-1, sel) != LB_ERR);
      } else {
         return false; // Kein SelectAll moeglich...
      }
   #else if defined __ECL_OS2__
      return cwListCtl::onSelectAllElems(sel, parent, walk);
   #endif
}


// Cursor
// ------

cwListElem * cwListBox::onGetCursoredElem() const
{
   #if defined __ECL_W32__
      int idx = ((WCListBox*)_wnd)->GetCaretIndex();
      if ( __ECL_ASSERT1__(idx >= 0) ) {
         void *ptr = ((WCListBox*)_wnd)->GetItemDataPtr(idx);
         if ( __ECL_ASSERT1__(ptr != (void*)-1) ) {
            return (cwListElem*)ptr;
         } else {
            return 0;
         }
      } else {
         return 0;
      }
   #else if defined __ECL_OS2__
      return GetItemHandle(GetLbxSelection(LIT_CURSOR));
   #endif
}

bool cwListBox::onSetCursoredElem(cwListElem *elem)
{
   if ( !elem )
      return false;

   #if defined __ECL_W32__
      int idx = getElemCountFromBegin(elem);
      if ( getStyles(wsLbxSingleSel) ) {
         return __ECL_ASSERT1__(((WCListBox*)_wnd)->SetCurSel(idx) != LB_ERR);
      } else {
         return __ECL_ASSERT1__(((WCListBox*)_wnd)->SetCaretIndex(idx) != LB_ERR);
      }
   #else if defined __ECL_OS2__
      return Select(elem);
   #endif
}


// Einfuegen/Loeschen
// ------------------

bool cwListBox::onInsertElemAt(int pos, cwListElem *ref_elem, cwListElem *new_elem, cwListElem * /*parent*/, bool /*invd*/)
{
   // pos < 0: Einfuegen VOR ref_elem (Ende der Liste, wenn ref_elem == 0)
   //     > 0: Einfuegen NACH ref_elem (Anfang der Liste, wenn ref_elem == 0)

   #if defined __ECL_W32__

      int idx;

      if ( ref_elem == 0 ) {
         idx = ((WCListBox*)_wnd)->InsertString(pos > 0 ? 0 : -1, new_elem->getName());
      } else if ( pos < 0 ) {
         idx = ((WCListBox*)_wnd)->InsertString(getElemCountFromBegin(ref_elem), new_elem->getName());
      } else {
         idx = ((WCListBox*)_wnd)->InsertString(getElemCountFromBegin(ref_elem)+1, new_elem->getName());
      }

      if ( __ECL_ASSERT1__(idx >= 0) ) {
         return __ECL_ASSERT1__(((WCListBox*)_wnd)->SetItemDataPtr(idx, new_elem) != LB_ERR);
      } else {
         return false;
      }

   #else if defined __ECL_OS2__

      int rc;

      if ( ref_elem == 0 ) {
         rc = InsertItem(new_elem->GetName(), pos > 0 ? 0 : LIT_END);
      } else if ( pos < 0 ) {
         rc = InsertItem(new_elem->GetName(), getElemCountFromBegin(ref_elem));
      } else {
         rc = InsertItem(new_elem->GetName(), getElemCountFromBegin(ref_elem)+1);
      }

      return rc == -1 ? false : SetItemHandle(0, new_elem);

   #endif
}

bool cwListBox::onRemoveElem(cwListElem *elem, bool /*invd*/)
{
   #if defined __ECL_W32__
      return __ECL_ASSERT1__(((WCListBox*)_wnd)->DeleteString(getElemCountFromBegin(elem)) != LB_ERR);
   #else if defined __ECL_OS2__
      return RemoveItem(getElemCountFromBegin(elem));
   #endif
}

bool cwListBox::onRemoveAllElems(cwListElem * /*parent*/, bool /*invd*/)
{
   #if defined __ECL_W32__
      if ( _wnd != 0 && ((WCListBox*)_wnd)->m_hWnd != 0 )
         ((WCListBox*)_wnd)->ResetContent();
      return true;
   #else if defined __ECL_OS2__
      return RemoveAllItems();
   #endif
}


// Abfrage
// -------

bool cwListBox::onQueryStarted(csQuery *query)
{
   bool ok = cwListCtl::onQueryStarted(query);
   csStorage *store = getStorage();
   cString null_text = onGetNullText();

   if ( ok && store && store->isNullable() && !null_text.isNull() ) {
      cwListElem *elem = new1(this) cwListElem("", null_text, null_text, query->getDescription());
      insertElemAtBegin(elem);
   }

   return ok;
}

bool cwListBox::onQueryEnded(csQuery *query)
{
   bool ok = cwListCtl::onQueryEnded(query);
   csStorage *store = getStorage();

   if ( ok && store && store->isNullable() && store->isNull() ) {
      cwListElem *elem = getElemWithKey("", 0, true);
      if ( elem ) {
         // Hier doSelectElem benutzen, nicht selectElem, da letzteres
         // die Storage beschreibt (und das muss hier nicht sein!)
         doSelectElem(elem, true);
      }
   }

   return ok;
}

int cwListBox::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      DWORD style = ((WCWnd*)_wnd)->GetStyle();

      #define LBS_SELMASK ( LBS_MULTIPLESEL | LBS_EXTENDEDSEL )

      if ( (mask & wsLbxSingleSel) && (style & LBS_SELMASK) == 0 )
         rc |= wsLbxSingleSel;
      if ( (mask & wsLbxMultipleSel) && (style & LBS_SELMASK) == LBS_MULTIPLESEL )
         rc |= wsLbxMultipleSel;
      if ( (mask & wsLbxExtendedSel) && (style & LBS_EXTENDEDSEL) )
         rc |= wsLbxExtendedSel;

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc | cwListCtl::onGetStyles(mask);
}

void cwListBox::onMakeStyles(int styles, int os_styles[]) const
{
   #if defined __ECL_W32__

      cwListCtl::onMakeStyles(styles, os_styles);

      if ( styles & wsLbxSingleSel )
         os_styles[0] &= ~(LBS_MULTIPLESEL | LBS_EXTENDEDSEL);
      if ( styles & wsLbxMultipleSel )
         os_styles[0] = (os_styles[0] & ~LBS_EXTENDEDSEL) | LBS_MULTIPLESEL;
      if ( styles & wsLbxExtendedSel )
         os_styles[0] = (os_styles[0] & ~LBS_MULTIPLESEL) | LBS_EXTENDEDSEL;

   #elif defined __ECL_OS2__

      // ...

   #endif
}

void cwListBox::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__

      if ( add & wsLbxSingleSel ) {
         os_remove[0] |= LBS_MULTIPLESEL | LBS_EXTENDEDSEL;
      } else if ( add & wsLbxMultipleSel ) {
         os_add[0] |= LBS_MULTIPLESEL;
         os_remove[0] |= LBS_EXTENDEDSEL;
      } else if ( add & wsLbxExtendedSel ) {
         os_add[0] |= LBS_EXTENDEDSEL;
         os_remove[0] |= LBS_MULTIPLESEL;
      }

      // Remove von wsLbxXxxxSel wird ignoriert, da nur einer der drei
      // Styles gueltig sein kann.

      cwListCtl::onModifyStyles(add, remove, os_add, os_remove);

   #elif defined __ECL_OS2__

      // ...

   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwSetBox
// ---------------------------------------------------------------------------
//
// Die Set-Box dient der Darstellung einer Menge von Elementen, von denen
// jedes ueber einen Ein-Zeichen-Schluessel identifiziert wird. Der Benutzer
// kann keines, eines oder mehrere der Elemente auswaehlen. Die Auswahl wird
// in einer String-Storage abgelegt, wobei die Key-Zeichen aller vorkommenden
// Elemente in den String aufgenommen werden. Beispiel:
//
//   Key | Element         Set-String | Bedeutung
//   ----+---------        -----------+------------------
//    L  | Lenkrad          ""        | Leere Menge
//    H  | Hupe             "H"       | Ein Element: Hupe
//    S  | Sitz             "LSH"     | Alle Elemente
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwListCtl
//              +--cwListBox
//                  +--cwSetBox
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwSetBox : public cwListBox {
   ELO_DECLARE(cwSetBox,cwListBox)

public:

   // Konstruktor
   inline cwSetBox() : cwListBox(0) { init(); }
   // Destruktor
   virtual ~cwSetBox();


   // Allgemeines
   // ===========

   // Erzeugen des Controls
   void create(cwWindow *parent, int id, csStorage *store = 0, csQuery *query = 0,
               int style = wsChild | wsVisible | wsBorder, const cdRect& rect = cdRect());


protected:

   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, wenn Fenster den Focus verliert
   void onLoseFocus();

   // Wird aufgerufen, wenn ein Element selektiert wurde
   void onSelectionChanged(cwListElem *elem);
   // Wird aufgerufen, wenn Enter gedrueckt wurde oder bei Doppelklick
   void onListElemSelected(cwListElem *elem);

   // Wird aufgerufen, wenn sich das gebundene Datenobjekt geaendert hat
   void onEventModified();
   // Wird aufgerufen, wenn die Abfrage beendet ist, um die Selektion anzeigen
   bool onQueryEnded(csQuery *query);

   // Daten des Controls pruefen
   DATAERR onCheckCtl(csStorage *store);
   // Daten des Controls speichern
   DATAERR onStoreCtl(csStorage *store);


protected:

   // Interner Konstruktor
   cwSetBox(void *wnd);


private:

   // Initialisierung
   void init();

   // Intern: Menge (String) in Markierung wandeln
   void transferToControl(cString value);
   // Intern: Markierung in Menge (String) wandeln
   cString transferToString();

};

#endif /*__INTERFACE__*/


// Implementierung cwSetBox
// ===========================================================================

cwSetBox::cwSetBox(void *wnd) :
   cwListBox(wnd)
{
}

cwSetBox::~cwSetBox()
{
   #if defined __ECL_W32__
      // Inhalt loeschen muss hier (und nicht im Destruktor von WCCheckListBox)
      // gemacht werden, damit virtuelle Methode DeleteItem aufgerufen wird!
      if ( _wnd != 0 && isCreated() )
         ((WCCheckListBox*)_wnd)->ResetContent();
   #elif defined __ECL_OS2__
      // ...
   #endif
}

void cwSetBox::init()
{
   #if defined __ECL_W32__
      _wnd = new WCCheckListBox(this);
   #elif defined __ECL_OS2__
      // ...
   #endif
}


// Allgemeines
// ===========

void cwSetBox::create(cwWindow *parent, int id, csStorage *store, csQuery *query,
                      int style, const cdRect& rect)
{
   cwListCtl::create(parent, id, store, query);

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);
      int mfc_style[2]; onMakeStyles(style, mfc_style);
      mfc_style[0] |= LBS_OWNERDRAWFIXED;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCCheckListBox*)_wnd)->Create(mfc_style[0], mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create check list box control"));

   #else
      // ...
   #endif
}


// Ueberschriebene Events
// ======================

void cwSetBox::onLoseFocus()
{
   if ( !isStorageReadOnly() )
      putStorageVal(transferToString());

   // Methoden der Basisklassen cwListBox und cwListCtl ueberspringen
   cwControl::onLoseFocus();
}

void cwSetBox::onSelectionChanged(cwListElem *elem)
{
   if ( elem && !isStorageReadOnly() )
      putStorageVal(transferToString());

   // Methoden der Basisklassen ueberspringen, daher:
   callEvent(evtSelectionChanged, elem);
   setFlags(wflHasChanged);
}

void cwSetBox::onListElemSelected(cwListElem *elem)
{
   if ( elem && !isStorageReadOnly() )
      putStorageVal(transferToString());

   // Methoden der Basisklassen ueberspringen, daher:
   callEvent(evtListElemSelected, elem);
   setFlags(wflHasChanged);
}

void cwSetBox::onEventModified()
{
   // Die Basismethode aufzurufen macht hier keinen Sinn...

   cString key; getStorageVal(key);
   transferToControl(key);

   // Der evtStorageModified-Event soll aber trotzdem ausgeloest
   // werden, daher:

   if ( hasStorage() )
      callEvent(evtStorageModified, getStorage());
}

bool cwSetBox::onQueryEnded(csQuery *query)
{
   if ( !cwListBox::onQueryEnded(query) )
      return false;

   cString buf;
   if ( !getStorageVal(buf) )
      buf.clear();

   transferToControl(buf);
   return true;
}

cwControl::DATAERR cwSetBox::onCheckCtl(csStorage *store)
{
   DATAERR derr = cwListBox::onCheckCtl(store);

   if ( derr == derrNone && hasStorage() ) {
      // ??? int count = getSelectedElemCount(true);
      // ??? if ( count >= own_store->getBufferSize() )
      // ???    derr = derrFormat;
   }

   return derr;
}

cwControl::DATAERR cwSetBox::onStoreCtl(csStorage *store)
{
   if ( !putStorageVal(transferToString()) )
      return derrWrite;

   // Die onStoreCtl-Variante aus cwListCtl ueberspringen, da
   // uns diese den muehsam aufgebauten Wert wieder kaputt macht!
   return cwControl::onStoreCtl(store);
}

void cwSetBox::transferToControl(cString value)
{
   cwListElem *elem;

   #if defined __ECL_W32__

      elem = getFirstElem();

      for ( int i = 0 ; elem != 0 ; i++ ) {
         if ( value.getPos(elem->getKey()) < 0 ) {
            ((CCheckListBox*)_wnd)->SetCheck(i, 0);
         } else {
            ((CCheckListBox*)_wnd)->SetCheck(i, 1);
         }
         elem = getNextElem(elem);
      }

   #else

      for ( int i = 0 ; i < value.getLength() ; i++ ) {
         if ( (elem = getElemWithKey(Str(value[i]), 0, true)) != 0 ) {
            // Hier doSelectElem benutzen, nicht selectElem, da letzteres
            // die Storage beschreibt (und das muss hier nicht sein!)
            doSelectElem(elem);
         }
      }

   #endif
}

cString cwSetBox::transferToString()
{
   cString value;
   cwListElem *elem;

   #if defined __ECL_W32__

      elem = getFirstElem();

      for ( int i = 0 ; elem != NULL ; i++ ) {
         if ( ((CCheckListBox*)_wnd)->GetCheck(i) == 1 )
            value += elem->getKey();
         elem = getNextElem(elem);
      }

   #else

      for ( elem = getSelectedElem(0, true) ; elem != NULL ; ) {
         value += elem->getKey();
         elem = getSelectedElem(elem, true);
      }

   #endif

   return value;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwComboBox
// ---------------------------------------------------------------------------
//
// Eine Combobox wird technisch als 2 verschiedene Fenster behandelt:
//
//  +----------+--+   +==========+--+   +----------+--+
//  |          |  |   |          |  |   |          |  |
//  +----------+--+   +==========+--+   +=============+
//  |             |   |             |   |             |
//  |             | = |             | + |             |
//  |             |   |             |   |             |
//  |             |   |             |   |             |
//  |             |   |             |   |             |
//  +-------------+   +-------------+   +=============+
//                       EditField          ListBox
//
// Das ListBox-Fenster wird nur bei Bedarf geoeffnet. Die cwComboBox-Klasse
// wird intern analog zu einer cwListBox mit wsLbxSingleSel verwaltet. Das
// EditField-"Anhaengsel" stellt die wichtigsten Funktionen der cwEditField-
// Klasse zur Verfuegung.
//
// Dieses Control unterstuetzt die Anzeige eines "ererbten Werten", der ueber
// die SetInheritedValue()-Methode gesetzt werden kann.
//
// Der Inhalt der Listbox wird beim ersten Anzeigen derselben geladen, solange
// der Style 'wsLoadOnInit' nicht gesetzt ist.
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwListCtl
//              +--cwComboBox
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwComboBox : public cwListCtl {
   ELO_DECLARE(cwComboBox,cwListCtl)
   friend class ccwComboBox;

public:

   // Konstruktor
   inline cwComboBox() : cwListCtl(0) { init(); }
   // Destruktor
   virtual ~cwComboBox();


   // Events
   // ======

   // Event-IDs dieser Klasse
   enum EVENTS { evtFirst = cwListCtl::evtUser,
     evtDropDown,                      // (EVFUNC)    Vor Aufklappen der Listbox
     evtCloseUp,                       // (EVFUNC)    Nach Zuklappen der Listbox
     evtUser                           // Benutzerdefinierte Events
   };


   // window-Flags
   // ============

   enum FLAGS { wflStart = cwListCtl::wflUser,
      wflDelayRequery   = wflStart << 0,  // Verzoegertes Nachladen?
      wflDelayActive    = wflStart << 1,  // Verzoegertes Requery aktiv?
      wflUser           = wflStart << 2   // Benutzerdefinierte Flags
   };


   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwListCtl::wsUser,
      wsCbxStaticField  = wsStart << 0,   // Combobox mit statischem Feld
      wsCbxEditField    = wsStart << 1,   // Combobox mit Eingabefeld
      wsDelayRequery    = wsStart << 2,   // Verzoegertes Nachladen (Default bei DB-Queries)
      wsUser            = wsStart << 3    // Benutzerdefinierte Styles
   };


   // Allgemeines
   // ===========

   // Erzeugen des Controls
   void create(cwWindow *parent, int id, csStorage *store = 0, csQuery *query = 0,
               int style = wsChild | wsVisible | wsBorder,
               const cdRect& rect = cdRect());


   // ListBox
   // =======

   // Anzahl darzustellender Element in der ListBox
   int getListElemCount() const
      { return onGetListElemCount(); }
   // ListBox anzeigen bzw. wegnehmen
   void showList(bool show = true);
   // Wird ListBox gerade angezeigt?
   bool isListShowing() const;


protected:

   // Zusaetzliche Events
   // ===================

   // Wird aufgerufen, bevor die Drop-Down-Liste aufgeklappt wird
   virtual void onDropDown();
   // Wird aufgerufen, nachdem die Drop-Down-Liste wieder zugeklappt wurde
   virtual void onCloseUp();
   // Anzahl darzustellender Zeilen in der ListBox
   virtual int onGetListElemCount() const;


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, wenn ein Element selektiert wurde
   void onSelectionChanged(cwListElem *elem);
   // Wird aufgerufen, wenn Enter gedrueckt wurde oder bei Doppelklick
   void onListElemSelected(cwListElem *elem);

   // Wird aufgerufen, um den Default-Text bei NULL-Werten zu ermitteln
   cString onGetNullText();

   // Wird aufgrufen, um die Anzahl der selektierten Elemente zu ermitteln
   int onGetSelectedElemCount(bool walk) const;
   // Wird aufgerufen, um die selektierten Elemente zu ermitteln
   cwListElem *onGetSelectedElem(cwListElem *elem = 0, bool walk = false) const;

   // Wird aufgerufen, um die Selektion fuer ein einzelnes Element zu aendern
   bool onSelectElem(cwListElem *elem, bool sel);
   // Wird aufgerufen, um die Selektion fuer alle Elemente zu aendern
   bool onSelectAllElems(bool sel, cwListElem *parent, bool walk);

   // Wird aufgerufen, um das Element mit Cursor zu erfragen
   cwListElem *onGetCursoredElem() const;
   // Wird aufgerufen, um den Cursor auf ein Element zu setzen
   bool onSetCursoredElem(cwListElem *elem);

   // Wird aufgerufen, um ein Element an Position 'pos', 'ref_elem' anzuzeigen
   bool onInsertElemAt(int pos, cwListElem *ref_elem, cwListElem *new_elem, cwListElem *parent, bool invd);
   // Wird aufgerufen, um ein Element von der Anzeige zu entfernen
   bool onRemoveElem(cwListElem *elem, bool invd);
   // Wird aufgerufen, um alle Elemente von der Anzeige zu entfernen
   bool onRemoveAllElems(cwListElem *parent, bool invd);

   // Wird aufgerufen, um den aktuellen ererbten Wert anzuzeigen
   void onShowInheritedVal();
   // Wird aufgerufen, um die Anzeige des ererbten Wertes zu beenden
   void onHideInheritedVal();

   // Wird aufgerufen, nachdem das Query-Objekt gesetzt wurde
   void onSetQuery(csQuery *query);
   // Abfrage des Controls erneut durchfuehren
   bool onRequeryCtl(csQuery *query);

   // Wird aufgerufen, wenn die Abfrage gestartet wurde, um den Listeninhalt zu loeschen
   bool onQueryStarted(csQuery *query);
   // Wird aufgerufen, wenn die Abfrage beendet ist, um die Selektion anzeigen
   bool onQueryEnded(csQuery *query);

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um die OS-spezifischen Styles aus den ECL-Styles zu ermitteln
   void onMakeStyles(int styles, int os_styles[]) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);


protected:

   // Interner Konstruktor
   cwComboBox(void *wnd);

private:

   // Initialisierung
   void init();

   // Intern: Wird fuer die Erstinitialisierung der ComboBox aufgerufen
   int onRefreshRequery(void *p1, int p2);

};

#endif /*__INTERFACE__*/


// Implementierung cwComboBox
// ===========================================================================

cwComboBox::cwComboBox(void *wnd) :
   cwListCtl(wnd)
{
}

cwComboBox::~cwComboBox()
{
}

void cwComboBox::init()
{
   #if defined __ECL_W32__
      _wnd = new WCComboBox(this);
   #elif defined __ECL_OS2__
   #endif
}


// Allgemeines
// ===========

void cwComboBox::create(cwWindow *parent, int id, csStorage *store, csQuery *query,
                        int style, const cdRect& rect)
{
   cwListCtl::create(parent, id, store, query);
   setFlags(wflDelayRequery, !!(style & wsDelayRequery));

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);
      int mfc_style[2]; onMakeStyles(style, mfc_style);

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCComboBox*)_wnd)->Create(mfc_style[0], mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create combo box control"));

   #else
      // ...
   #endif
}


// ListBox
// =======

void cwComboBox::showList(bool show)
{
   #if defined __ECL_W32__
      ((WCComboBox*)_wnd)->ShowDropDown(show);
   #elif defined __ECL_OS2__
      SendMsg(CBM_SHOWLIST, MPFROMSHORT(show));
   #endif
}

bool cwComboBox::isListShowing() const
{
   #if defined __ECL_W32__
      return !!((WCComboBox*)_wnd)->GetDroppedState();
   #elif defined __ECL_OS2__
      return (bool)SendMsg(CBM_ISLISTSHOWING);
   #endif
}


// Zusaetzliche Events
// ===================

void cwComboBox::onDropDown()
{
   csQuery *query = getQuery();

   if ( getFlags(wflDelayActive) && query ) {
      if ( query->open() ) {
         setFlags(wflQueryStarted, true);
         if ( onQueryStarted(query) ) {
            while ( query->fetch() ) {
               if ( !onQueryData(query) )
                  break;
            }
         }
         query->close();
         onQueryEnded(query);
         setFlags(wflInQuery|wflQueryStarted, false);
         setFlags(wflDelayActive, false);
      }
   }

   callEvent(evtDropDown);
}

void cwComboBox::onCloseUp()
{
   callEvent(evtCloseUp);
}

int cwComboBox::onGetListElemCount() const
{
   int count = 8; //getElementCount();
   if ( count > 8 )
      count = 8;
   return count;
}


// Ueberschriebene Events
// ======================

void cwComboBox::onSelectionChanged(cwListElem *elem)
{
   cwListCtl::onSelectionChanged(elem);
}

void cwComboBox::onListElemSelected(cwListElem *elem)
{
   cwListCtl::onListElemSelected(elem);
}

cString cwComboBox::onGetNullText()
{
   // TBD: Text aus Resourcen holen
   return "<Keine Auswahl>";
}


// Selektion
// ---------

int cwComboBox::onGetSelectedElemCount(bool /*walk*/) const
{
   #if defined __ECL_W32__
      return ((WCComboBox*)_wnd)->GetCurSel() != CB_ERR ? 1 : 0;
   #else if defined __ECL_OS2__
      return cwListCtl::onGetSelectedElemCount(walk);
   #endif
}

cwListElem * cwComboBox::onGetSelectedElem(cwListElem *elem, bool /*walk*/) const
{
   #if defined __ECL_W32__
      return elem == 0 ? getCursoredElem() : 0;
   #else if defined __ECL_OS2__
      int idx = elem ? getElemCountFromBegin(elem) : LIT_FIRST;
      return GetItemHandle(GetLbxSelection(idx));
   #endif
}

bool cwComboBox::onSelectElem(cwListElem *elem, bool sel)
{
   #if defined __ECL_W32__
      if ( !sel && elem != 0 || elem == 0 ) {
         return __ECL_ASSERT1__(((WCComboBox*)_wnd)->SetCurSel(-1) == CB_ERR);
      } else {
         return __ECL_ASSERT1__(((WCComboBox*)_wnd)->SetCurSel(getElemCountFromBegin(elem)) != CB_ERR);
      }
   #else if defined __ECL_OS2__
      return SetLbxSelection(getElemCountFromBegin(elem), sel);
   #endif
}

bool cwComboBox::onSelectAllElems(bool sel, cwListElem * /*parent*/, bool /*walk*/)
{
   if ( sel )
      return false; // SelectAll unsinnig in Combobox

   #if defined __ECL_W32__
      return __ECL_ASSERT1__(((WCComboBox*)_wnd)->SetCurSel(-1) != CB_ERR);
   #else if defined __ECL_OS2__
      return cwListCtl::onSelectAllElems(sel, parent, walk);
   #endif
}


// Cursor
// ------

cwListElem * cwComboBox::onGetCursoredElem() const
{
   #if defined __ECL_W32__
      int idx = ((WCComboBox*)_wnd)->GetCurSel();
      if ( idx >= 0 ) {
         void *ptr = (void *)((WCComboBox*)_wnd)->GetItemData(idx);
         if ( __ECL_ASSERT1__(ptr != (void*)-1) )
            return (cwListElem*)ptr;
      }
      // Keine Selektion (normaler Zustand, kein Fehler!)
      return 0;
   #else if defined __ECL_OS2__
      return GetItemHandle(GetLbxSelection(LIT_CURSOR));
   #endif
}

bool cwComboBox::onSetCursoredElem(cwListElem *elem)
{
   if ( !elem )
      return false;

   #if defined __ECL_W32__
      return __ECL_ASSERT1__(((WCComboBox*)_wnd)->SetCurSel(getElemCountFromBegin(elem)) != CB_ERR);
   #else if defined __ECL_OS2__
      return Select(elem);
   #endif
}


// Einfuegen/Loeschen
// ------------------

bool cwComboBox::onInsertElemAt(int pos, cwListElem *ref_elem, cwListElem *new_elem, cwListElem * /*parent*/, bool /*invd*/)
{
   // pos < 0: Einfuegen VOR ref_elem (Ende der Liste, wenn ref_elem == 0)
   //     > 0: Einfuegen NACH ref_elem (Anfang der Liste, wenn ref_elem == 0)

   #if defined __ECL_W32__

      int idx;

      if ( ref_elem == 0 ) {
         idx = ((WCComboBox*)_wnd)->InsertString(pos > 0 ? 0 : -1, new_elem->getName());
      } else if ( pos < 0 ) {
         idx = ((WCComboBox*)_wnd)->InsertString(getElemCountFromBegin(ref_elem), new_elem->getName());
      } else {
         idx = ((WCComboBox*)_wnd)->InsertString(getElemCountFromBegin(ref_elem)+1, new_elem->getName());
      }

      if ( __ECL_ASSERT1__(idx >= 0) ) {
         return __ECL_ASSERT1__(((WCComboBox*)_wnd)->SetItemData(idx, (DWORD)new_elem) != LB_ERR);
      } else {
         return false;
      }

   #else if defined __ECL_OS2__

      int rc;

      if ( ref_elem == 0 ) {
         rc = InsertItem(new_elem->GetName(), pos > 0 ? 0 : LIT_END);
      } else if ( pos < 0 ) {
         rc = InsertItem(new_elem->GetName(), getElemCountFromBegin(ref_elem));
      } else {
         rc = InsertItem(new_elem->GetName(), getElemCountFromBegin(ref_elem)+1);
      }

      return rc == -1 ? false : SetItemHandle(0, new_elem);

   #endif
}

bool cwComboBox::onRemoveElem(cwListElem *elem, bool /*invd*/)
{
   #if defined __ECL_W32__
      return __ECL_ASSERT1__(((WCComboBox*)_wnd)->DeleteString(getElemCountFromBegin(elem)) != CB_ERR);
   #else if defined __ECL_OS2__
      return RemoveItem(getElemCountFromBegin(elem));
   #endif
}

bool cwComboBox::onRemoveAllElems(cwListElem * /*parent*/, bool /*invd*/)
{
   #if defined __ECL_W32__
      if ( _wnd != 0 && ((WCComboBox*)_wnd)->m_hWnd != 0 )
         ((WCComboBox*)_wnd)->ResetContent();
      return true;
   #else if defined __ECL_OS2__
      return RemoveAllItems();
   #endif
}


// Ererbte Werte
// -------------

void cwComboBox::onShowInheritedVal()
{
   cString value = getInheritedValue();
   if ( value.isEmpty() )
      value = "";
   cwListElem *elem = getElemWithKey(value);
   doSelectElem(elem, true);
}

void cwComboBox::onHideInheritedVal()
{
   cString value;
   cwListElem *elem = 0;
   if ( getStorageVal(value) )
      elem = getElemWithKey(value);
   if ( elem == 0 )
      elem = getElemWithKey("");
   doSelectElem(elem, true);
}


// Abfrage
// -------

void cwComboBox::onSetQuery(csQuery *query)
{
   // Bei cdbQuery-Abfragen automatisch das wsDelayRequery-Flag setzen,
   // damit nicht unnoetig grosse Datenmengen uebertragen werden.

   if ( query != 0 && query->ECL_ISKINDOF(cdbQuery) )
      modifyStyles(wsDelayRequery, 0);

   cwListCtl::onSetQuery(query);
}

bool cwComboBox::onRequeryCtl(csQuery *query)
{
   cString key;

   if ( inQuery() )
      return false;

   if ( !getFlags(wflDelayRequery) )
      return cwListCtl::onRequeryCtl(query);

   // wflDelayActive bedeutet fuer die ComboBox, dass sie beim
   // Aufklappen auf jeden Fall alle bislang vorhandenen Elemente
   // Loeschen und die Liste neu fuellen muss.
   setFlags(wflDelayActive);

   // Alle bisherigen Elemente loeschen und wenigstens das dem
   // Inhalt der aktuellen Storage entsprechende Element neu laden

   if ( isCreated() ) {
#define __Assume_Empty_Key_As_Null_Value__
#ifdef __Assume_Empty_Key_As_Null_Value__
      if ( !getStorageVal(key) )
         key.clear();
      setFlags(wflInQuery, true);
      if ( !query->start1(EVENT(this, (EVFUNC_RPI)onRefreshRequery), key) ) {
         setFlags(wflInQuery|wflQueryStarted, false);
         return false;
      }
#else
      if ( getStorageVal(key) ) {
         setFlags(wflInQuery, true);
         if ( !query->start1(EVENT(this, (EVFUNC_RPI)onRefreshRequery), key) ) {
            setFlags(wflInQuery|wflQueryStarted, false);
            return false;
         }
      } else {
         setFlags(wflInQuery|wflQueryStarted, true);
         onQueryStarted(query);
         onQueryEnded(query);
         setFlags(wflInQuery|wflQueryStarted, false);
         return true;
      }
#endif
   }

   return true;
}

int cwComboBox::onRefreshRequery(void *p1, int p2)
{
   csQuery *query = (csQuery *)p1;
   csQuery::STATE state = (csQuery::STATE)p2;
   int rc = 0;

   switch ( state ) {
   case csQuery::qsStart:
      setFlags(wflQueryStarted, true);
      return (int)onQueryStarted(query);
   case csQuery::qsData:
      return (int)onQueryData(query);
   case csQuery::qsEnd:
   default:
      rc = (int)onQueryEnded(query);
      setFlags(wflInQuery|wflQueryStarted, false);
   }

   return (int)false;
}

bool cwComboBox::onQueryStarted(csQuery *query)
{
   bool ok = cwListCtl::onQueryStarted(query);
   csStorage *store = getStorage();
   cString null_text = onGetNullText();

   if ( ok && store && store->isNullable() && !null_text.isNull() ) {
      cwListElem *elem = new1(this) cwListElem("", null_text);
      insertElemAtBegin(elem);
   }

   return ok;
}

bool cwComboBox::onQueryEnded(csQuery *query)
{
   bool ok = cwListCtl::onQueryEnded(query);
   csStorage *store = getStorage();

   if ( ok && store && store->isNullable() && store->isNull() ) {
      cwListElem *elem = getElemWithKey("", 0, true);
      if ( elem ) {
         // Hier doSelectElem benutzen, nicht selectElem, da letzteres
         // die Storage beschreibt (und das muss hier nicht sein!)
         doSelectElem(elem, true);
      }
   }

   refreshInheritedValue(true);
   return ok;
}

int cwComboBox::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      DWORD style = ((WCWnd*)_wnd)->GetStyle();

      if ( (mask & wsCbxStaticField) && (style & CBS_DROPDOWNLIST) )
         rc |= wsCbxStaticField;
      if ( (mask & wsCbxEditField) && (style & CBS_DROPDOWN) )
         rc |= wsCbxEditField;
      if ( (mask & wsDelayRequery) && getFlags(wflDelayRequery) )
         rc |= wsDelayRequery;

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc | cwListCtl::onGetStyles(mask);
}

void cwComboBox::onMakeStyles(int styles, int os_styles[]) const
{
   #if defined __ECL_W32__

      cwListCtl::onMakeStyles(styles, os_styles);

      if ( styles & wsCbxStaticField )
         os_styles[0] &= (os_styles[0] & ~(CBS_DROPDOWN | CBS_SIMPLE)) | CBS_DROPDOWNLIST;
      if ( styles & wsCbxEditField )
         os_styles[0] &= (os_styles[0] & ~(CBS_DROPDOWNLIST | CBS_SIMPLE)) | CBS_DROPDOWN;

   #elif defined __ECL_OS2__

      // ...

   #endif
}

void cwComboBox::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__

      if ( add & wsCbxStaticField ) {
         os_add[0] |= CBS_DROPDOWNLIST;
         os_remove[0] |= CBS_DROPDOWN | CBS_SIMPLE;
      } else if ( add & wsCbxEditField ) {
         os_add[0] |= CBS_DROPDOWN;
         os_remove[0] |= CBS_DROPDOWNLIST | CBS_SIMPLE;
      }

      // Remove von wsCbxXxxxField wird ignoriert, da nur einer der zwei
      // Styles gueltig sein kann.

      if ( add & wsDelayRequery )
         setFlags(wflDelayRequery, true);
      if ( remove & wsDelayRequery )
         setFlags(wflDelayRequery, false);

      cwListCtl::onModifyStyles(add, remove, os_add, os_remove);

   #elif defined __ECL_OS2__

      // ...

   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwMultiComboBox
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwListCtl
//              +--cwComboBox
//                  +--cwMultiComboBox
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwMultiComboBox : public cwComboBox {
   ELO_DECLARE(cwMultiComboBox,cwComboBox)

public:

   // Konstruktor
   inline cwMultiComboBox() : cwComboBox(0) { init(); }
   // Destruktor
   virtual ~cwMultiComboBox();

   // Hauptspalte setzen (diese wird im Edit-Field angezeigt)
   inline void setMasterColumn(int col)
      { master_column = col; }
   // Hauptspalte erfragen
   inline int getMasterColumn() const
      { return master_column; }


protected:

   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um ein Element an Position 'pos', 'ref_elem' anzuzeigen
   bool onInsertElemAt(int pos, cwListElem *ref_elem, cwListElem *new_elem, cwListElem *parent, bool invd);
   // Wird aufgerufen, wenn sich die Spalten- oder Zeilenzahl (pro DS) geaendert hat
   void onSetupRowCol(const SETUP_ROWCOL_INFO& info);
   // Wird aufgerufen, um in Spalte das Feld 'fld' zur Anzeige vorzubereiten
   void onSetupField(int fld, const SETUP_FIELD_INFO& info);


protected:

   // Interner Konstruktor
   cwMultiComboBox(void *wnd);

private:

   // Hauptspalte
   int master_column;

   // Zusaetzliche Daten
   struct ADD_INFO;
   ADD_INFO *add_info;

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwMultiComboBox
// ===========================================================================

struct cwMultiComboBox::ADD_INFO {
   #if defined __ECL_W32__
      ADD_INFO() { column_count = 0; }
      cArray<cString, const cString&> cs_array;
      cArray<const char *, const char *> cp_array;
      int column_count;
   #else
   #endif
};

cwMultiComboBox::cwMultiComboBox(void *wnd) :
   cwComboBox(wnd)
{
   master_column = -1;
   add_info = new0 ADD_INFO;
}

cwMultiComboBox::~cwMultiComboBox()
{
   #if defined __ECL_W32__
      // Inhalt loeschen muss hier (und nicht im Destruktor von WCMultiComboBox)
      // gemacht werden, damit virtuelle Methode DeleteItem aufgerufen wird!
      if ( _wnd != 0 && ((WCMultiComboBox*)_wnd)->m_hWnd != 0 )
         ((WCMultiComboBox*)_wnd)->ResetContent();
   #elif defined __ECL_OS2__
      // ...
   #endif

   delete add_info;
}

void cwMultiComboBox::init()
{
   #if defined __ECL_W32__
      _wnd = new WCMultiComboBox(this);
      add_info = new0 ADD_INFO;
   #elif defined __ECL_OS2__
      // ...
   #endif
}


// Einfuegen/Loeschen
// ------------------

bool cwMultiComboBox::onInsertElemAt(int pos, cwListElem *ref_elem, cwListElem *new_elem, cwListElem * /*parent*/, bool /*invd*/)
{
   // pos < 0: Einfuegen VOR ref_elem (Ende der Liste, wenn ref_elem == 0)
   //     > 0: Einfuegen NACH ref_elem (Anfang der Liste, wenn ref_elem == 0)

   #if defined __ECL_W32__

      int idx;
      int column_count = add_info->column_count;

      for ( int col = 0 ; col < column_count ; col++ ) {
         new_elem->get(getFieldFromColumn(col), add_info->cs_array[col]);
         const char *cp = add_info->cs_array[col];
         add_info->cp_array[col] = cp ? cp : "";
      }

      const char **array = add_info->cp_array.getData();

      if ( ref_elem == 0 ) {
         idx = ((WCMultiComboBox*)_wnd)->InsertString(pos > 0 ? 0 : -1, array, column_count);
      } else if ( pos < 0 ) {
         idx = ((WCMultiComboBox*)_wnd)->InsertString(getElemCountFromBegin(ref_elem), array, column_count);
      } else {
         idx = ((WCMultiComboBox*)_wnd)->InsertString(getElemCountFromBegin(ref_elem)+1, array, column_count);
      }

      if ( __ECL_ASSERT1__(idx >= 0) ) {
         return __ECL_ASSERT1__(((WCMultiComboBox*)_wnd)->SetItemData(idx, (DWORD)new_elem) != LB_ERR);
      } else {
         return false;
      }

   #else if defined __ECL_OS2__
      // ???
   #endif
}

void cwMultiComboBox::onSetupRowCol(const SETUP_ROWCOL_INFO& info)
{
   int master_col = master_column;

   if ( master_col < 0 ) {
      // Die Berechnung der "Hauptspalte" geht davon aus, dass die Standard-
      // Abfrage fuer MultiComboBoxen mindestens ein Schluessel- und ein
      // Namensfeld an Position 0 und 1 liefern:
      master_col = getColumnFromField(1);
      if ( master_col < 0 ) master_col = getColumnFromField(0);
   }

   #if defined __ECL_W32__

      WCMultiComboBox *cbx = (WCMultiComboBox*)_wnd;

      add_info->column_count = info.new_column_count;
      add_info->cs_array.setSize(info.new_column_count);
      add_info->cp_array.setSize(info.new_column_count);

      cbx->SetColumnCount(info.new_column_count);
      cbx->SetMasterColumn(master_col);
      cbx->SetFitToSize(TRUE);

   #else if defined __ECL_OS2__
      // ???
   #endif
}

void cwMultiComboBox::onSetupField(int /*fld*/, const SETUP_FIELD_INFO& info)
{
   #if defined __ECL_W32__

      WCMultiComboBox *cbx = (WCMultiComboBox*)_wnd;
      int pix_width = 75;
      TEXTMETRIC tm;
      CClientDC cdc(cbx);

      if ( cdc.GetOutputTextMetrics(&tm) )
         pix_width = info.descr->disp_width * tm.tmAveCharWidth;

      #define __Add_Pix_Border__
      #ifdef __Add_Pix_Border__
         pix_width += 10;
      #endif

      cbx->SetColumnWidth(info.disp_col, min_max(pix_width, 35, 375));

   #else if defined __ECL_OS2__
      // ???
   #endif
}

