// ===========================================================================
// ew_menus.cpp                                                 ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cwMenuItem        -
//     |
//     +--cwMID         -
//     |
//     +--cwMPos        -
//     |
//     +--cwMEndPos     -
//
//    cwMenu            -
//     |
//     +-cwSubMenu      -
//     |
//     +-cwFrameMenu    -
//     |
//     +-cwPopupMenu    -
//
// ===========================================================================

#include "win/ew_menus.hpp"
#include "win/ew_frames.hpp"
#include "win/ew_application.hpp"
#include "base/eb_osver.hpp"

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
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

#include "base/eb_elo.hpp"
#include "base/eb_event.hpp"
#include "win/ew_base.hpp"
#include "win/ew_commands.hpp"


// Forward-Deklarationen
// ===========================================================================

class cwMenu;
class cwSubMenu;
class cwFrameMenu;
class cwPopupMenu;
class cwWindow;

#endif /*__INTERFACE__*/




/*
// ===========================================================================
// Lokale Klasse cwMenuDefaultActionDescription
// ---------------------------------------------------------------------------
//
// cEloBase
//  +--cEloDescription
//      +--cEloActionDescription
//          +--cwMenuDefaultActionDescription
//
// ===========================================================================

static class cwMenuDefaultActionDescription : public cEloActionDescription {
   ELO_DECLARE(cwMenuDefaultActionDescription,cEloActionDescription)

   void onInitialize()
      { }

   cString onGetSignature() const
      { return "cwMenuDefaultActionDescription"; }

} MenuDefaultActionDescription;
*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwMenuItem
// ---------------------------------------------------------------------------
//
// Spezifikation eines Menu-Eintrags wahlweise ueber dessen ID (cwMID) oder
// ueber dessen relative Position (cwMPos).
//
// cwMenuItem
//   +--cwMID
//   +--cwMPos
//   +--cwMEndPos
//
// ===========================================================================

class cwMenuItem {

public:

   // Ist der Menu-Eintrag ueber dessen ID gegeben?
   inline bool isID() const
      { return !!(item_id & 0x80000000); }
   // Ist der Menu-Eintrag ueber dessen relative Position gegeben?
   inline bool isPos() const
      { return !(item_id & 0x80000000); }
   // Spezialfall: Ist der Eintrag NACH dem letzten Eintrag gemeint?
   inline bool isEndPos() const
      { return (item_id & 0xc0000000) == 0x40000000; }

   // ID oder Position des Menu-Eintrags erfragen
   inline int getItem() const
      { return isEndPos() ? -1 : int(item_id & 0x0000ffff); }


protected:

   // Konstruktor
   inline cwMenuItem(unsigned long id)
      { item_id = id; }


private:

   // ID (Bit 31 gesetzt) oder Position (Bit 31 rueckgesetzt)
   unsigned long item_id;

};


class cwMID : public cwMenuItem {
public:
   // Konstruktor
   inline cwMID(int id) :
      cwMenuItem((id & 0x0000ffff) | 0x80000000) { }
};

class cwMPos : public cwMenuItem {
public:
   // Konstruktor
   inline cwMPos(int pos) :
      cwMenuItem(pos & 0x0000ffff) { }
};

class cwMEndPos : public cwMenuItem {
public:
   // Konstruktor
   inline cwMEndPos() :
      cwMenuItem(0x40000000) { }
};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwMenu
// ---------------------------------------------------------------------------
//
// Dies ist eine abstrakte Basisklasse zur Verwendung in cwFrameMenu und
// cwPopupMenu. Es werden Funktionalitaeten zur Erstellung, Modifikation und
// Verwaltung von Menues zur Verfuegung gestellt.
//
// cwMenu
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwMenu : public cEventSource {
   friend class ccwMenu;

public:

   // Destruktor
   ~cwMenu();


   // Allgemeines
   // ===========

   // Erzeugen eines Menus
   bool create();
   // Erzeugen eines Menus aus einer Resource
   bool create(cResource res);
   // Loeschen des Menus (Freigeben der Resourcen)
   void destroy();


   // Menu-Eintraege
   // ==============

   enum MENU_STATES {
      msEnabled   = (1 << 0),
      msChecked   = (1 << 1)
   };

   // Menu-Eintrag aktivieren oder deaktivieren (grau)
   bool setEnable(const cwMenuItem& mi, bool enabled = true);
   // Menu-Eintrag mit Checkmark versehen
   bool setCheck(const cwMenuItem& mi, bool checked = true);
   // Menu-Eintrag als Default-Eintrag markieren
   bool setDefault(const cwMenuItem& mi);

   // Menu-Eintrag am Ende des Menus hinzufuegen
   void addItem(cString text, int item_id, cwSubMenu *sub_menu = 0, int state = msEnabled);
   // Separator am Ende des Menus hinzufuegen
   void addSeparator();

   // Menu-Eintrag vor 'mi' einfuegen
   void insertItem(const cwMenuItem& mi, cString text, int item_id, cwSubMenu *sub_menu = 0, int state = msEnabled);
   // Separator vor 'mi' einfuegen
   void insertSeparator(const cwMenuItem& mi);

   // Menu-Eintrag entfernen
   void removeItem(const cwMenuItem& mi);


protected:

   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, wenn sich die aktuelle Selektion geaendert hat
   void onSelectionChanged(cEloSelection *selection);


protected:

   // Events
   // ======

   // Wird aufgerufen, um das Menu zu erzeugen
   virtual bool onCreate(cResource res);


protected:

   void *_mnu;       // Zeiger auf Wrapper-Objekt


   // ECL/win Internas
   // ================

   // Interner Konstruktor
   cwMenu(void *mnu);

   // Trennen vom Wrapper
   void __disconnect();
   // Eigenen Zeiger auf Wrapper-Objekt ermitteln
   void *__getMnu();
   const void *__getMnu() const;
   // Zeiger auf Wrapper-Objekt ermitteln (statische Variante)
   static void *__getMnu(cwMenu *menu);
   static const void *__getMnu(const cwMenu *menu);

};

#endif /*__INTERFACE__*/


// Implementierung cwMenu
// ===========================================================================

cwMenu::cwMenu(void *mnu)
{
   _mnu = mnu;
}

cwMenu::~cwMenu()
{
   #if defined __ECL_W32__
      delete (WCMenu*)_mnu;
   #elif defined __ECL_OS2__
      // ...
   #endif
}


// Allgemeines
// ===========

bool cwMenu::create()
{
   if ( __ECL_ASSERT1__(_mnu != 0) ) {
      destroy();
      return onCreate(cResource(-1));
   }

   return false;
}

bool cwMenu::create(cResource res)
{
   if ( __ECL_ASSERT1__(_mnu != 0) ) {
      destroy();
      return onCreate(res);
   }

   return false;
}

void cwMenu::destroy()
{
   if ( __ECL_ASSERT1__(_mnu != 0) ) {
      #if defined __ECL_W32__
         if ( ((WCMenu*)_mnu)->m_hMenu != 0 )
            ((WCMenu*)_mnu)->DestroyMenu();
      #elif defined __ECL_OS2__
         // ...
      #endif
   }
}


// Menu-Eintraege
// ==============

bool cwMenu::setEnable(const cwMenuItem& mi, bool enabled)
{
   if ( __ECL_ASSERT1__(_mnu != 0) ) {
      #if defined __ECL_W32__
         int mfc_enable =
            (enabled ? MF_ENABLED : MF_GRAYED)
          | (mi.isID() ? MF_BYCOMMAND : MF_BYPOSITION);
         return !!(((WCMenu*)_mnu)->EnableMenuItem(mi.getItem(), mfc_enable) & MF_ENABLED);
      #elif defined __ECL_OS2__
         return WinEnableMenuItem(GetHandle(), mi.getItem(), enabled);
      #endif
   }

   return false;
}

bool cwMenu::setCheck(const cwMenuItem& mi, bool checked)
{
   if ( __ECL_ASSERT1__(_mnu != 0) ) {
      #if defined __ECL_W32__
         int mfc_enable =
            (checked ? MF_CHECKED : MF_UNCHECKED)
          | (mi.isID() ? MF_BYCOMMAND : MF_BYPOSITION);
         return !!(((WCMenu*)_mnu)->CheckMenuItem(mi.getItem(), mfc_enable) & MF_CHECKED);
      #elif defined __ECL_OS2__
         return WinCheckMenuItem(GetHandle(), mi.getItem(), checked);
      #endif
   }

   return false;
}

bool cwMenu::setDefault(const cwMenuItem& mi)
{
   if ( __ECL_ASSERT1__(_mnu != 0) ) {
      #if defined __ECL_W32__
         return !!((WCMenu*)_mnu)->SetDefaultItem(mi.getItem(), mi.isPos());
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   return false;
}

void cwMenu::addItem(cString text, int item_id, cwSubMenu *sub_menu, int state)
{
   insertItem(cwMEndPos(), text, item_id, sub_menu, state);
/*
   if ( __ECL_ASSERT1__(_mnu != 0) ) {
      #if defined __ECL_W32__
         int mfc_state =
            MF_STRING
          | ((state & msEnabled) ? MF_ENABLED : MF_GRAYED)
          | ((state & msChecked) ? MF_CHECKED : MF_UNCHECKED);
         ((WCMenu*)_mnu)->AppendMenu(mfc_state, item_id, (const char *)text);
      #elif defined __ECL_OS2__
      #endif
   }
*/
}

void cwMenu::addSeparator()
{
   if ( __ECL_ASSERT1__(_mnu != 0) ) {
      #if defined __ECL_W32__
         ((WCMenu*)_mnu)->AppendMenu(MF_SEPARATOR);
      #elif defined __ECL_OS2__
      #endif
   }
}

void cwMenu::insertItem(const cwMenuItem& mi, cString text, int item_id, cwSubMenu *sub_menu, int state)
{
   if ( __ECL_ASSERT1__(_mnu != 0) ) {
      #if defined __ECL_W32__

            HMENU w32_hmenu = 0;
            WCMenu *mfc_submenu = 0;

            if ( sub_menu != 0 ) {
               if ( (mfc_submenu = (WCMenu*)sub_menu->__getMnu()) == 0 ) {
                  __ECL_ASSERT2__(0, ("cwMenu::insertItem: Invalid submenu given"));
               } else if ( mfc_submenu->m_hMenu == 0 ) {
                  __ECL_ASSERT2__(0, ("cwMenu::insertItem: Detached submenu given"));
               } else {
                  w32_hmenu = mfc_submenu->Detach();
               }
            }

            char w32_text[128];
            strxcpy(w32_text, text, sizeof w32_text);

            int w32_flags =
               ((state & msEnabled) ? MFS_ENABLED : MFS_GRAYED)
             | ((state & msChecked) ? MFS_CHECKED : MFS_UNCHECKED);

            int w32_mask =
               MIIM_TYPE | MIIM_STATE | MIIM_ID
             | (sub_menu != 0 ? MIIM_SUBMENU : 0);

            MENUITEMINFO mii;
            // 21.03.2002 -TE- Windows95 tillt 'rum, wenn hier was anderes als 0x2c steht
            mii.cbSize = cOsVersion::getVersion() == 95 ? 0x2c : sizeof mii;
            mii.fMask = w32_mask;
            mii.fType = MFT_STRING;
            mii.fState = w32_flags;
            mii.wID = item_id;
            mii.hSubMenu = w32_hmenu;
            mii.dwTypeData = w32_text;

            ::InsertMenuItem(((WCMenu*)_mnu)->m_hMenu, mi.getItem(), mi.isPos(), &mii);

      #elif defined __ECL_OS2__
         // ...
      #endif
   }
}

void cwMenu::insertSeparator(const cwMenuItem& mi)
{
}

void cwMenu::removeItem(const cwMenuItem& mi)
{
   if ( __ECL_ASSERT1__(_mnu != 0) ) {
      #if defined __ECL_W32__
         int mfc_flags = mi.isID() ? MF_BYCOMMAND : MF_BYPOSITION;
         ((WCMenu*)_mnu)->DeleteMenu(mi.getItem(), mfc_flags);
      #elif defined __ECL_OS2__
         // ...
      #endif
   }
}


// Events
// ======

bool cwMenu::onCreate(cResource res)
{
   if ( __ECL_ASSERT1__(_mnu != 0) ) {
      #if defined __ECL_W32__
         if ( res.getID() >= 0 ) {
            return !!((WCMenu*)_mnu)->LoadMenu(res.getID());
         } else {
            return !!((WCMenu*)_mnu)->CreateMenu();
         }
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   return false;
}


// Ueberschriebene Events
// ======================

void cwMenu::onSelectionChanged(cEloSelection * /*selection*/)
{
}


// ECL/win Internas
// ================

void cwMenu::__disconnect()
{
   _mnu = 0;
/*
   if ( getFlags(wflAutoDelete) ) {
      DbgTrcWin("Auto deleting this = %08x", this);
      delete this;
   }
*/
}

void * cwMenu::__getMnu()
{
   return _mnu;
}

const void * cwMenu::__getMnu() const
{
   return _mnu;
}

void * cwMenu::__getMnu(cwMenu *menu)
{
   return menu ? menu->_mnu : 0;
}

const void * cwMenu::__getMnu(const cwMenu *menu)
{
   return menu ? menu->_mnu : 0;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwSubMenu
// ---------------------------------------------------------------------------
//
// cwMenu
//  +--cwSubMenu
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwSubMenu : public cwMenu {

public:

   // Konstruktor
   inline cwSubMenu() : cwMenu(0) { init(); }
   // Destruktor
   ~cwSubMenu();


protected:

   // Interner Konstruktor
   cwSubMenu(void *mnu);


private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwSubMenu
// ===========================================================================

cwSubMenu::cwSubMenu(void *mnu) :
   cwMenu(mnu)
{
}

cwSubMenu::~cwSubMenu()
{
}

void cwSubMenu::init()
{
   #if defined __ECL_W32__
      _mnu = new WCMenu(this);
   #elif defined __ECL_OS2__
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwFrameMenu
// ---------------------------------------------------------------------------
//
// cwMenu
//  +--cwFrameMenu
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwFrameMenu : public cwMenu {

public:

   // Konstruktor
   inline cwFrameMenu() : cwMenu(0) { init(); }
   // Destruktor
   ~cwFrameMenu();


   // Allgemeines
   // ===========

   // Mit bestehendem Menu verbinden
   bool attach(cwWindow *parent);
   // Bestehende Verbindung loesen
   void detach();


protected:

   // Interner Konstruktor
   cwFrameMenu(void *mnu);


private:

   // Zeiger auf Parent-Window
   cwWindow *parent;

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwFrameMenu
// ===========================================================================

cwFrameMenu::cwFrameMenu(void *mnu) :
   cwMenu(mnu)
{
   parent = 0;
}

cwFrameMenu::~cwFrameMenu()
{
}

void cwFrameMenu::init()
{
   parent = 0;

   #if defined __ECL_W32__
      _mnu = new WCMenu(this);
   #elif defined __ECL_OS2__
   #endif
}


// Allgemeines
// ===========

bool cwFrameMenu::attach(cwWindow *parent)
{
   #if defined __ECL_W32__
      HWND w32_hwnd = (HWND)ccwWindow::__getHandle(parent);
      if ( w32_hwnd != 0 ) {
         HMENU w32_hmenu = ::GetMenu(w32_hwnd);
         return w32_hmenu != NULL && !!((WCMenu*)_mnu)->Attach(w32_hmenu);
      }
   #elif defined __ECL_OS2__
   #endif

   return false;
}

void cwFrameMenu::detach()
{
   #if defined __ECL_W32__
      ((WCMenu*)_mnu)->Detach();
   #elif defined __ECL_OS2__
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwPopupMenu
// ---------------------------------------------------------------------------
//
// cwMenu
//  +--cwPopupMenu
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwPopupMenu : public cwMenu {

public:

   // Konstruktor
   inline cwPopupMenu() : cwMenu(0) { init(); }
   // Destruktor
   ~cwPopupMenu();

   enum MENU_ALIGN {    // Orientierung des Kontextmenues zu 'screen_pos':
      maDefault,        //  - Betriebssystem-Default
      maTopLeft,        //  - 'screen_pos' ist oberer linker Eckpunkt
      maCenter,         //  - 'screen_pos' ist Mittelpunkt
      maBottomLeft      //  - 'screen_pos' ist unterer linker Eckpunkt
   };

   // Kontextmenu anzeigen, Position und Alignment aus cwCmdPosition
   bool showMenu(cwWindow *wnd, const cwCmdPosition &cmd);
   // Kontextmenu anzeigen, Position und Alignment uebergeben
   bool showMenu(cwWindow *wnd, const cdPoint& screen_pos, MENU_ALIGN align = maDefault);

   // Kontextmenu anzeigen und Ergebnis ermitteln, Position und Alignment aus cwCmdPosition
   // Liefert die MID des selektierten Eintrags; 0, falls keine Selektion erfolgt; -1 bei Fehler
   int queryMenu(const cwCmdPosition &cmd, cwWindow *wnd = 0);
   // Kontextmenu anzeigen und Ergebnis ermitteln, Position und Alignment uebergeben
   // Liefert die MID des selektierten Eintrags; 0, falls keine Selektion erfolgt; -1 bei Fehler
   int queryMenu(const cdPoint& screen_pos, MENU_ALIGN align = maDefault, cwWindow *wnd = 0);


protected:

   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um das Menu zu erzeugen
   bool onCreate(cResource res);


protected:

   // Interner Konstruktor
   cwPopupMenu(void *mnu);


private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwPopupMenu
// ===========================================================================

cwPopupMenu::cwPopupMenu(void *mnu) :
   cwMenu(mnu)
{
}

cwPopupMenu::~cwPopupMenu()
{
}

void cwPopupMenu::init()
{
   #if defined __ECL_W32__
      _mnu = new WCMenu(this);
   #elif defined __ECL_OS2__
   #endif
}

bool cwPopupMenu::showMenu(cwWindow *wnd, const cwCmdPosition &cmd)
{
   cdPoint pos = cmd.getPos();
   cwPopupMenu::MENU_ALIGN ma = cwPopupMenu::maDefault;

   if ( cmd.fromKeyboard() ) {
      pos = cdPoint(wnd->getClientSize() / 2);
      wnd->convWin2Screen(pos);
      ma = cwPopupMenu::maCenter;
   } else if ( cmd.isRelativeToWindow() ) {
      wnd->convWin2Screen(pos);
   }

   return showMenu(wnd, pos, ma);
}

bool cwPopupMenu::showMenu(cwWindow *win, const cdPoint& screen_pos, MENU_ALIGN align)
{
   if ( __ECL_ASSERT1__(_mnu != 0 && win != 0) ) {
      #if defined __ECL_W32__
         int mfc_flags = TPM_RIGHTBUTTON;
         switch ( align ) {
         case maCenter:       mfc_flags |= TPM_CENTERALIGN; break;
         case maBottomLeft:   mfc_flags |= TPM_BOTTOMALIGN; break;
         default:             mfc_flags |= TPM_LEFTALIGN; break;
         }
         return !!((WCMenu*)_mnu)->TrackPopupMenu(
            mfc_flags,
            screen_pos.x, screen_pos.y,
            (CWnd*)ccwWindow::__getWnd(win));
      #elif defined __ECL_OS2__
      #endif
   }

   return false;
}

int cwPopupMenu::queryMenu(const cwCmdPosition &cmd, cwWindow *wnd)
{
   cdPoint pos = cmd.getPos();
   cwPopupMenu::MENU_ALIGN ma = cwPopupMenu::maDefault;

   if ( wnd != 0 ) {
      if ( cmd.fromKeyboard() ) {
         pos = cdPoint(wnd->getClientSize() / 2);
         wnd->convWin2Screen(pos);
         ma = cwPopupMenu::maCenter;
      } else if ( cmd.isRelativeToWindow() ) {
         wnd->convWin2Screen(pos);
      }
   }

   return queryMenu(pos, ma, wnd);
}

int cwPopupMenu::queryMenu(const cdPoint& screen_pos, MENU_ALIGN align, cwWindow *wnd)
{
   if ( __ECL_ASSERT1__(_mnu != 0) ) {
      #if defined __ECL_W32__
         cwWindow *win = wnd == 0 ? cwApplication::getMainWindow() : wnd;
         if ( __ECL_ASSERT1__(win != 0) ) {
            HMENU w32_hmenu = ((WCMenu*)_mnu)->m_hMenu;
            HWND w32_hwnd = ((CWnd*)ccwWindow::__getWnd(win))->m_hWnd;
            int w32_flags = TPM_RIGHTBUTTON | TPM_RETURNCMD;
            if ( wnd == 0 ) w32_flags |= TPM_NONOTIFY;
            switch ( align ) {
            case maCenter:       w32_flags |= TPM_CENTERALIGN; break;
            case maBottomLeft:   w32_flags |= TPM_BOTTOMALIGN; break;
            default:             w32_flags |= TPM_LEFTALIGN; break;
            }
            return ::TrackPopupMenuEx(
               w32_hmenu,
               w32_flags,
               screen_pos.x, screen_pos.y,
               w32_hwnd,
               NULL);
         }
      #elif defined __ECL_OS2__
      #endif
   }

   return -1;
}


// Ueberschriebene Events
// ======================

bool cwPopupMenu::onCreate(cResource res)
{
   if ( __ECL_ASSERT1__(_mnu != 0) ) {
      #if defined __ECL_W32__
         if ( res.getID() >= 0 ) {
            return !!((WCMenu*)_mnu)->LoadMenu(res.getID());
         } else {
            return !!((WCMenu*)_mnu)->CreatePopupMenu();
         }
      #elif defined __ECL_OS2__
      #endif
   }

   return false;
}


