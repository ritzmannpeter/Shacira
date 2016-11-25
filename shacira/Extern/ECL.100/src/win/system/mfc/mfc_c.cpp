// ===========================================================================
// mfc_c.cpp                                                    ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cwCmd
//     |
//     +-ccwCmd                  - Kompagnon-Klasse zu "cwCmd"
//
//    ccwWindow                  - Kompagnon-Klasse zu "cwWindow"
//
// ===========================================================================

#include "win/system/mfc/mfc_c.hpp"
#include "win/system/mfc/mfc.hpp"

#include "win/ew_application.hpp"
#include "win/ew_context.hpp"
#include "win/ew_windows.hpp"
#include "win/ew_frames.hpp"
#include "win/ew_views.hpp"
#include "win/ew_menus.hpp"
#include "win/ew_dragdrop.hpp"
#include "win/ew_toolbars.hpp"
#include "win/ew_dialogs.hpp"
#include "win/ew_statctls.hpp"
#include "win/ew_buttonctls.hpp"
#include "win/ew_editctls.hpp"
#include "win/ew_nbctls.hpp"
#include "win/ew_listctls.hpp"
#include "win/ew_lboxctls.hpp"
#include "win/ew_cnrctls.hpp"
#include "win/ew_treectls.hpp"
#include "win/ew_gridctls.hpp"

#include "stdafx.h"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "win/ew_commands.hpp"


// Forward-Deklarationen
// ===========================================================================

// von ECL/base:
class cCmdOptions;

// von ECL/win:
class cwApplication;
class cwIconList;
class cwButtonCtl;
class cwContainer;
class cwControl;
class cwDialog;
class cwDragDrop;
class cwDragSource;
class cwDropTarget;
class cwEditCtl;
class cwGrid;
class cwListCtl;
class cwListBox;
class cwLogWin;
class cwComboBox;
class cwListElem;
class cwToolWin;
class cwToolBar;
class cwTree;
class cwMenu;
class cwNotebookCtl;
class cwNotebookDlg;
class cwNotebookPage;
class cwWindow;
class cwFrame;
class cwMiniFrame;
class cwView;

// von MFC:
struct CRuntimeClass;

// von UGRID:
class CUGCell;

#endif /*__INTERFACE__*/




// Lokale Daten
// ===========================================================================

#if defined __ECL_DEBUG__
   static const char *DebugVirtKeys[] = {
      "0x00 ",             "0x01 VK_LBUTTON",   "0x02 VK_RBUTTON",   "0x03 VK_CANCEL",
      "0x04 VK_MBUTTON",   "0x05 ",             "0x06 ",             "0x07 ",
      "0x08 VK_BACK",      "0x09 VK_TAB",       "0x0A ",             "0x0B ",
      "0x0C VK_CLEAR",     "0x0D VK_RETURN",    "0x0E ",             "0x0F ",
      "0x10 VK_SHIFT",     "0x11 VK_CONTROL",   "0x12 VK_MENU",      "0x13 VK_PAUSE",
      "0x14 VK_CAPITAL",   "0x15 VK_KANA",      "0x16 ",             "0x17 VK_JUNJA",
      "0x18 VK_FINAL",     "0x19 VK_HANJA",     "0x1A ",             "0x1B VK_ESCAPE",
      "0x1C VK_CONVERT",   "0x1D VK_NONCONVERT","0x1E VK_ACCEPT",    "0x1F VK_MODECHANGE",
      "0x20 VK_SPACE",     "0x21 VK_PRIOR",     "0x22 VK_NEXT",      "0x23 VK_END",
      "0x24 VK_HOME",      "0x25 VK_LEFT",      "0x26 VK_UP",        "0x27 VK_RIGHT",
      "0x28 VK_DOWN",      "0x29 VK_SELECT",    "0x2A VK_PRINT",     "0x2B VK_EXECUTE",
      "0x2C VK_SNAPSHOT",  "0x2D VK_INSERT",    "0x2E VK_DELETE",    "0x2F VK_HELP",
      "0x30 ",             "0x31 ",             "0x32 ",             "0x33 ",
      "0x34 ",             "0x35 ",             "0x36 ",             "0x37 ",
      "0x38 ",             "0x39 ",             "0x3A ",             "0x3B ",
      "0x3C ",             "0x3D ",             "0x3E ",             "0x3F ",
      "0x40 ",             "0x41 ",             "0x42 ",             "0x43 ",
      "0x44 ",             "0x45 ",             "0x46 ",             "0x47 ",
      "0x48 ",             "0x49 ",             "0x4A ",             "0x4B ",
      "0x4C ",             "0x4D ",             "0x4E ",             "0x4F ",
      "0x50 ",             "0x51 ",             "0x52 ",             "0x53 ",
      "0x54 ",             "0x55 ",             "0x56 ",             "0x57 ",
      "0x58 ",             "0x59 ",             "0x5A ",             "0x5B VK_LWIN",
      "0x5C VK_RWIN",      "0x5D VK_APPS",      "0x5E ",             "0x5F ",
      "0x60 VK_NUMPAD0",   "0x61 VK_NUMPAD1",   "0x62 VK_NUMPAD2",   "0x63 VK_NUMPAD3",
      "0x64 VK_NUMPAD4",   "0x65 VK_NUMPAD5",   "0x66 VK_NUMPAD6",   "0x67 VK_NUMPAD7",
      "0x68 VK_NUMPAD8",   "0x69 VK_NUMPAD9",   "0x6A VK_MULTIPLY",  "0x6B VK_ADD",
      "0x6C VK_SEPARATOR", "0x6D VK_SUBTRACT",  "0x6E VK_DECIMAL",   "0x6F VK_DIVIDE",
      "0x70 VK_F1",        "0x71 VK_F2",        "0x72 VK_F3",        "0x73 VK_F4",
      "0x74 VK_F5",        "0x75 VK_F6",        "0x76 VK_F7",        "0x77 VK_F8",
      "0x78 VK_F9",        "0x79 VK_F10",       "0x7A VK_F11",       "0x7B VK_F12",
      "0x7C VK_F13",       "0x7D VK_F14",       "0x7E VK_F15",       "0x7F VK_F16",
      "0x80 VK_F17",       "0x81 VK_F18",       "0x82 VK_F19",       "0x83 VK_F20",
      "0x84 VK_F21",       "0x85 VK_F22",       "0x86 VK_F23",       "0x87 VK_F24",
      "0x88 ",             "0x89 ",             "0x8A ",             "0x8B ",
      "0x8C ",             "0x8D ",             "0x8E ",             "0x8F ",
      "0x90 VK_NUMLOCK",   "0x91 VK_SCROLL"
   };
#endif




#ifdef __INTERFACE__

// ===========================================================================
// ccwHandle
// ---------------------------------------------------------------------------
//
// ccwHandle
//
// ===========================================================================

class ccwHandle : public cOsBase {

public:

   // Handle aus cOsBase-Objekt erfragen
   static void *getHandle(const cOsBase& other);
   // Handle des cOsBase-Objektes setzen (Vorsicht! Obacht! Gefaehrlich!!!)
   static void setHandle(cOsBase& other, void *handle);

};

#endif /*__INTERFACE__*/


// Implementierung ccwHandle
// ===========================================================================

void *ccwHandle::getHandle(const cOsBase& other)
   { return (void*)getHandleFrom(other); }
void ccwHandle::setHandle(cOsBase& other, void *handle)
   { setHandleOf(other, cOsHandle(handle)); }




#ifdef __INTERFACE__

// ===========================================================================
// ccwCmd
// ---------------------------------------------------------------------------
//
// cwCmd
//  +--ccwCmd
//
// ===========================================================================

class ccwCmd : public cwCmd {

public:

   // Konstruktor aus wParam und lParam
   ccwCmd(unsigned int wParam, long lParam)
      { msg = 0; ul1 = wParam; ul2 = lParam; }
   // Konstruktor aus message, wParam und lParam
   ccwCmd(unsigned int message, unsigned int wParam, long lParam)
      { msg = message; ul1 = wParam; ul2 = lParam; }
   // Konstruktor aus herkoemmlichem cwCmd
   ccwCmd(const cwCmd& cmd)
      { msg = cmd.msg; ul1 = cmd.ul1; ul2 = cmd.ul2; }

   // Meldungs-ID erfragen
   unsigned int getMsg() const
      { return msg; }
   // wParam erfragen
   unsigned int getParam1() const
      { return ul1; }
   // lParam erfragen
   unsigned long getParam2() const
      { return ul2; }

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// ccwApplication
// ---------------------------------------------------------------------------
//
// ccwApplication
//
// ===========================================================================

class ccwApplication {

public:

   // Applikation initialisieren
   static void initApplication(int show_cmd);
   // Trennen vom Wrapper
   static void __disconnect(cwApplication *app);
   // Standard-Kommandos des Main-Frames auswerten
   static bool __onFrameCommand(cwApplication *app, cwWindow *win, const cwCmdEvt& cmd);

   // Wird aufgerufen, um die Applikationsinstanz zu initialisieren
   static bool onInit(cwApplication *app);
   // Wird aufgerufen, um die Hauptschleife der Applikation auszufuehren
   static int onRun(cwApplication *app);
   // Wird aufgerufen, um die Applikationsinstanz zu deinitialisieren
   static int onExit(cwApplication *app);

   // Resource-Handle setzen
   static void *setResourceHandle(void *hInstResource);
   // Original-Resource-Handle setzen
   static void *setOrigResourceHandle();
   // Original-Resource-Handle erfragen
   static void *getOrigResourceHandle();

   // CmdOptions-Objekt der Applikation setzen
   static void setCmdOptions(cwApplication *app, cCmdOptions *options);
   // Erfragen des nShowCmd-Parameters von WinMain
   static int getInitialShowCmd();

private:
   static void *orig_resource_handle;
   static int initial_show_cmd;

};

#endif /*__INTERFACE__*/


// Implementierung ccwApplication
// ===========================================================================

void * ccwApplication::orig_resource_handle = 0;
int ccwApplication::initial_show_cmd = 0;
extern HINSTANCE __declspec(dllimport) EclDefaultInstance;

void ccwApplication::initApplication(int show_cmd)
{
   InitCommonControls();
   orig_resource_handle = AfxGetResourceHandle();
   initial_show_cmd = show_cmd;
}

void * ccwApplication::setResourceHandle(void *hInstResource)
{
   HINSTANCE prev = AfxGetResourceHandle();
   AfxSetResourceHandle((HINSTANCE)hInstResource);
   EclDefaultInstance = (HINSTANCE)hInstResource;
   return (void*)prev;
}

bool ccwApplication::onInit(cwApplication *app)
   { app->__onPreInit();
     return app->onInit(); }
int ccwApplication::onRun(cwApplication *app)
   { return app->onRun(); }
int ccwApplication::onExit(cwApplication *app)
   { int rc = app->onExit();
     app->__onPostExit();
     return rc; }

void ccwApplication::__disconnect(cwApplication *app)
   { app->__disconnect(); }
bool ccwApplication::__onFrameCommand(cwApplication *app, cwWindow *win, const cwCmdEvt& cmd)
   { return app->__onFrameCommand(win, cmd); }
void * ccwApplication::setOrigResourceHandle()
   { return setResourceHandle(orig_resource_handle); }
void * ccwApplication::getOrigResourceHandle()
   { return orig_resource_handle; }

void ccwApplication::setCmdOptions(cwApplication *app, cCmdOptions *options)
   { app->options = options; }
int ccwApplication::getInitialShowCmd()
   { return initial_show_cmd; }




#ifdef __INTERFACE__

// ===========================================================================
// ccwMenu
// ---------------------------------------------------------------------------
//
// ccwMenu
//
// ===========================================================================

class ccwMenu {

public:

   // Trennen vom Wrapper
   static void __disconnect(cwMenu *mnu);

};

#endif /*__INTERFACE__*/


// Implementierung ccwMenu
// ===========================================================================

void ccwMenu::__disconnect(cwMenu *mnu)
   { mnu->__disconnect(); }




#ifdef __INTERFACE__

// ===========================================================================
// ccwDragDrop
// ---------------------------------------------------------------------------
//
// ccwDragDrop
//
// ===========================================================================

class ccwDragDrop {

public:

   // Trennen vom Wrapper
   static void __disconnect(cwDragDrop *dd);

};

#endif /*__INTERFACE__*/


// Implementierung ccwDragDrop
// ===========================================================================

void ccwDragDrop::__disconnect(cwDragDrop *dd)
   { dd->__disconnect(); }




#ifdef __INTERFACE__

// ===========================================================================
// ccwDragSource
// ---------------------------------------------------------------------------
//
// ccwDragDrop
//  +--ccwDragSource
//
// ===========================================================================

class ccwDragSource : public ccwDragDrop {

public:

};

#endif /*__INTERFACE__*/


// Implementierung ccwDragSource
// ===========================================================================





#ifdef __INTERFACE__

// ===========================================================================
// ccwDropTarget
// ---------------------------------------------------------------------------
//
// ccwDragDrop
//  +--ccwDropTarget
//
// ===========================================================================

class ccwDropTarget : public ccwDragDrop {

public:

   // Anmerkung: Die folgenden Routinen liefern 'false', wenn die
   // Standardbehandlung fuer Drag&Drop durchgefuehrt werden soll

   // Wird aufgerufen, wenn eine Drag-Operation das Fenster 'mfc_win' erreicht
   static bool onDragEnter(cwDropTarget *dd, void *mfc_win, cwCmdDrag& cmd);
   // Wird aufgerufen, wenn eine Drag-Operation ueber 'mfc_win' ablaeuft
   static bool onDragOver(cwDropTarget *dd, void *mfc_win, cwCmdDrag& cmd);
   // Wird aufgerufen, wenn eine Drag-Scroll-Operation ueber 'mfc_win' ablaeuft
   static bool onDragScroll(cwDropTarget *dd, void *mfc_win, cwCmdDrag& cmd);
   // Wird aufgerufen, wenn eine Drag-Operation das Fenster 'mfc_win' verlaesst
   static bool onDragLeave(cwDropTarget *dd, void *mfc_win);
   // Wird aufgerufen, wenn ein Drop ueber dem Fenster 'mfc_win' veranlasst wurde
   static bool onDrop(cwDropTarget *dd, void *mfc_win, cwCmdDrop& cmd);

};

#endif /*__INTERFACE__*/


// Implementierung ccwDropTarget
// ===========================================================================

bool ccwDropTarget::onDragEnter(cwDropTarget *dd, void *mfc_win, cwCmdDrag& cmd)
{
   return !dd->onDragEnter(cmd) ?
      (((CWnd*)mfc_win)->SendMessage(WM_ECL_DRAG_ENTER, 0, (LPARAM)&cmd) != 0)
    : true;
}

bool ccwDropTarget::onDragOver(cwDropTarget *dd, void *mfc_win, cwCmdDrag& cmd)
{
   return !dd->onDragOver(cmd) ?
      (((CWnd*)mfc_win)->SendMessage(WM_ECL_DRAG_OVER, 0, (LPARAM)&cmd) != 0)
    : true;
}

bool ccwDropTarget::onDragScroll(cwDropTarget *dd, void *mfc_win, cwCmdDrag& cmd)
{
   return !dd->onDragScroll(cmd) ?
      (((CWnd*)mfc_win)->SendMessage(WM_ECL_DRAG_SCROLL, 0, (LPARAM)&cmd) != 0)
    : true;
}

bool ccwDropTarget::onDragLeave(cwDropTarget *dd, void *mfc_win)
{
   return !dd->onDragLeave() ?
      (((CWnd*)mfc_win)->SendMessage(WM_ECL_DRAG_LEAVE, 0, 0) != 0)
    : true;
}

bool ccwDropTarget::onDrop(cwDropTarget *dd, void *mfc_win, cwCmdDrop& cmd)
{
   return !dd->onDrop(cmd) ?
      (((CWnd*)mfc_win)->SendMessage(WM_ECL_DROP, 0, (LPARAM)&cmd) != 0)
    : true;
}




#ifdef __INTERFACE__

// ===========================================================================
// ccwIconList
// ---------------------------------------------------------------------------
//
// ccwIconList
//
// ===========================================================================

class ccwIconList {

public:

   // Zeiger auf Wrapper-Objekt erfragen
   static void *__getIList(const cwIconList *ilist);
   // Trennen vom Wrapper
   static void __disconnect(cwIconList *ilist);

};

#endif /*__INTERFACE__*/


// Implementierung ccwIconList
// ===========================================================================

void * ccwIconList::__getIList(const cwIconList *ilist)
   { return ilist->__getIList(); }
void ccwIconList::__disconnect(cwIconList *ilist)
   { ilist->__disconnect(); }




#ifdef __INTERFACE__

// ===========================================================================
// ccwWindow
// ---------------------------------------------------------------------------
//
// ccwWindow
//
// ===========================================================================

class ccwWindow {

public:

   struct PP {
      int mask;
      unsigned long fg_col;
      unsigned long bg_col;
   };

   // Moeglicher Eingriff ins Windows-Message-Dispatching
   static bool onDispatchMsg(cwWindow *win, void *msg);

   // Fenster wird erzeugt
   static bool onCreate(cwWindow *win);
   // Fenstererzeugung wird vorbereitet
   static bool onPreCreate(cwWindow *win, void *cs);
   // Subclassing wird vorbereitet
   static void onPreSubclass(cwWindow *win);
   // Fenster wird zerstoert
   static void onDestroy(cwWindow *win);
   // Farben einstellen
   static void *onCtlColor(cwWindow *win, void *dc, long col, void *brush);
   // Hintergrund loeschen
   static int onEraseBkgnd(cwWindow *win, void *dc, void *brush);
   // Groesse geaendert
   static void onSize(cwWindow *win, int cx, int cy);
   // Taste gedrueckt
   static void onChar(cwWindow *win, cwCmdChar& cmd);
   // Mausklick ausgefuehrt
   static bool onMouseClick(cwWindow *win, const cwCmdMouse& cmd);
   // Mausbewegung durchgefuehrt
   static bool onMouseMove(cwWindow *win, const cwCmdMouse& cmd);
   // Befehl ausfuehren (von Menu, Control oder Accelerator)
   static bool onCommand(cwWindow *win, const cwCmdEvt& cmd);
   // Benutzerschnittstelle updaten
   static bool onCommandUI(cwWindow *win, cwCmdUI& cmd);
   // Befehl weiter routen
   static bool onCommandRoute(cwWindow *win, const cwCmdEvt& cmd);
   // Kontextmenu anzeigen
   static bool onContextMenu(cwWindow *win, const cwCmdPosition& cmd);
   // Wird aufgerufen, wenn eine Aktion an einem Scrollbar ausgeloest wurde
   static void onScroll(cwWindow *win, const cwCmdScroll& cmd);

   // Wird aufgerufen, wenn Fenster den Focus erhaelt
   static void onGainFocus(cwWindow *win);
   // Wird aufgerufen, wenn Fenster den Focus verliert
   static void onLoseFocus(cwWindow *win);

   // Inhalt refreshen (false -> Abbruch)
   static bool onRefresh(cwWindow *win);
   // Inhalt speichern (false -> Abbruch)
   static bool onStore(cwWindow *win);
   // Inhalt verwerfen (false -> Abbruch)
   static bool onDiscard(cwWindow *win);
   // Beenden eines unterbrochenen "Schliessen"-Vorgangs
   static void onResumeClose(cwWindow *win);
   // Verzoegertes Ausfuehren einer Operation
   static void onExecDelayed(cwWindow *win, int id, void *data);

   // Blaettern zu Sibling erlauben?
   static bool onAllowTurn(cwWindow *win);
   // Abbruch mit Speichern erlauben?
   static bool onAllowStore(cwWindow *win);
   // Abbruch ohne Speichern erlauben?
   static bool onAllowDiscard(cwWindow *win);
   // Schliessen des Fensters erlauben?
   static bool onAllowClose(cwWindow *win, cwWindow *notify);

   // Timer 'id' abgelaufen
   static bool onTimer(cwWindow *win, int id);

   // Anmerkung: Die folgenden Routinen liefern 'false', wenn die
   // Standardbehandlung fuer Drag&Drop durchgefuehrt werden soll

   // Wird aufgerufen, wenn eine Drag-Operation das Fenster erreicht
   static bool onDragEnter(cwWindow *win, cwCmdDrag& cmd);
   // Wird aufgerufen, wenn eine Drag-Operation ueber dem Fenster ablaeuft
   static bool onDragOver(cwWindow *win, cwCmdDrag& cmd);
   // Wird aufgerufen, wenn eine Drag-Scroll-Operation ueber dem Fenster ablaeuft
   static bool onDragScroll(cwWindow *win, cwCmdDrag& cmd);
   // Wird aufgerufen, wenn eine Drag-Operation das Fenster verlaesst
   static bool onDragLeave(cwWindow *win);
   // Wird aufgerufen, wenn ein Drop ueber dem Fenster veranlasst wurde
   static bool onDrop(cwWindow *win, cwCmdDrop& cmd);

   // Ermitteln der _wnd-Komponente
   static void * __getWnd(cwWindow *win);
   // Ermitteln des Window-Handles
   static void * __getHandle(cwWindow *win);
   // Trennen vom Wrapper
   static void __disconnect(cwWindow *win);

};

#endif /*__INTERFACE__*/


// Implementierung ccwWindow
// ===========================================================================

bool ccwWindow::onDispatchMsg(cwWindow *win, void *msg)
{
   MSG *m = (MSG*)msg;

   switch ( m->message ) {
   case WM_KEYDOWN:
   case WM_KEYUP:
   case WM_CHAR:
      return win->onDispatchChar(ccwCmd(m->message, m->wParam, m->lParam));
   case WM_LBUTTONDOWN:
   case WM_LBUTTONUP:
   case WM_LBUTTONDBLCLK:
   case WM_RBUTTONDOWN:
   case WM_RBUTTONUP:
   case WM_RBUTTONDBLCLK:
   case WM_MBUTTONDOWN:
   case WM_MBUTTONUP:
   case WM_MBUTTONDBLCLK:
      return win->onDispatchMouseClick(ccwCmd(m->message, m->wParam, m->lParam));
   }

   // Der Rueckgabewert gibt an, ob die Weiterverteilung der Meldung 'msg'
   // erfolgen soll (true) oder nicht (false). Standardmaessig natuerlich 'true'.
   return true;
}

bool ccwWindow::onCreate(cwWindow *win)
   { return win->onCreate(); };
bool ccwWindow::onPreCreate(cwWindow *win, void *cs)
   { return win->onPreCreate(cs); }
void ccwWindow::onPreSubclass(cwWindow * /*win*/)
   { /* nothing to do */ }
void ccwWindow::onDestroy(cwWindow *win)
   { win->onDestroy(); };
void ccwWindow::onSize(cwWindow *win, int cx, int cy)
   { win->onSize(cx, cy); }
void ccwWindow::onChar(cwWindow *win, cwCmdChar& cmd)
   { win->onChar(cmd); };
bool ccwWindow::onMouseClick(cwWindow *win, const cwCmdMouse& cmd)
   { return win->onMouseClick(cmd); };
bool ccwWindow::onMouseMove(cwWindow *win, const cwCmdMouse& cmd)
   { return win->onMouseMove(cmd); };
bool ccwWindow::onCommand(cwWindow *win, const cwCmdEvt& cmd)
   { return win->onCommand(cmd); }
bool ccwWindow::onCommandUI(cwWindow *win, cwCmdUI& cmd)
   { return win->onCommandUI(cmd); }
bool ccwWindow::onCommandRoute(cwWindow *win, const cwCmdEvt& cmd)
   { cwWindow *mw = cwApplication::getTheApp()->getMainWindow();
     return win == mw ? false : mw->onCommand(cmd); }
bool ccwWindow::onContextMenu(cwWindow *win, const cwCmdPosition& cmd)
   { win->callEvent(cwWindow::evtContextMenu, cmd.getPosX(), cmd.getPosY());
     return win->onContextMenu(cmd); }
void ccwWindow::onScroll(cwWindow *win, const cwCmdScroll& cmd)
   { win->onScroll(cmd); }

void ccwWindow::onGainFocus(cwWindow *win)
   { win->callEvent(cwWindow::evtFocusGained);
     win->onGainFocus();
     win->setFlags(cwWindow::wflHasFocus);
     win->__setActive(0);
     if ( win->getParent() ) win->getParent()->onChildActivated(win); }
void ccwWindow::onLoseFocus(cwWindow *win)
   { win->setFlags(cwWindow::wflHasFocus, false);
     win->callEvent(cwWindow::evtFocusLost);
     win->onLoseFocus(); }

bool ccwWindow::onStore(cwWindow *win)
   { return win->onStore(); }
bool ccwWindow::onDiscard(cwWindow *win)
   { return win->onDiscard(); }
void ccwWindow::onResumeClose(cwWindow *win)
   { win->onResumeClose(); }
void ccwWindow::onExecDelayed(cwWindow *win, int id, void *data)
   { win->onExecDelayed(id, data); }

bool ccwWindow::onAllowTurn(cwWindow *win)
   { return win->onAllowTurn(); }
bool ccwWindow::onAllowStore(cwWindow *win)
   { return win->onAllowStore(); }
bool ccwWindow::onAllowDiscard(cwWindow *win)
   { return win->onAllowDiscard(); }
bool ccwWindow::onAllowClose(cwWindow *win, cwWindow *notify)
   { return win->onAllowClose(notify); }

bool ccwWindow::onTimer(cwWindow *win, int id)
{
   if ( id >= 10000 && id < 20000 ) {
      // Timer-Event von "execDelayed"
      win->onExecDelayed(id - 10000, 0);
      return true; // Kill Timer
   } else {
      // "Herkoemmlicher" Timer-Event
      return win->onTimer(id);
   }
}

bool ccwWindow::onDragEnter(cwWindow *win, cwCmdDrag& cmd)
   { return win->onDragEnter(cmd); }
bool ccwWindow::onDragOver(cwWindow *win, cwCmdDrag& cmd)
   { return win->onDragOver(cmd); }
bool ccwWindow::onDragScroll(cwWindow *win, cwCmdDrag& cmd)
   { return win->onDragScroll(cmd); }
bool ccwWindow::onDragLeave(cwWindow *win)
   { return win->onDragLeave(); }
bool ccwWindow::onDrop(cwWindow *win, cwCmdDrop& cmd)
   { return win->onDrop(cmd); }

void * ccwWindow::__getWnd(cwWindow *win)
   { return win->__getWnd(); }
void * ccwWindow::__getHandle(cwWindow *win)
   { return win != 0 && win->_wnd != 0 ? ((WCWnd*)win->_wnd)->m_hWnd : 0; }
void ccwWindow::__disconnect(cwWindow *win)
   { win->__disconnect(); }

void * ccwWindow::onCtlColor(cwWindow *win, void *dc, long ctl, void *brush)
{
   PP *pp = (PP*)win->__getPresParam();

   if ( pp->mask == 0 )
      return HBRUSH(0);

   CDC *pDC = (CDC*)dc;
   CBrush *pBrush = (CBrush*)brush;

   if ( pp->mask & (1 << cwWindow::ppFgndColor) )
      pDC->SetTextColor(pp->fg_col);

   if ( pp->mask & (1 << cwWindow::ppBkgndColor) ) {
      pBrush->DeleteObject();
      pBrush->CreateSolidBrush(pp->bg_col);
   } else {
      switch ( ctl ) {
      case CTLCOLOR_BTN:
      case CTLCOLOR_DLG:
      case CTLCOLOR_STATIC:
         pDC->SetBkColor(::GetSysColor(COLOR_BTNFACE));
         return ::GetSysColorBrush(COLOR_BTNFACE);
         //pBrush->DeleteObject();
         //pBrush->CreateStockObject(NULL_BRUSH);
         break;
      case CTLCOLOR_EDIT:
         pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
         return ::GetSysColorBrush(COLOR_WINDOW);
         //pBrush->DeleteObject();
         //pBrush->CreateSolidBrush(RGB(255,255,201));
         break;
      default:
         pDC->SetBkColor(::GetSysColor(COLOR_INFOBK));
         return ::GetSysColorBrush(COLOR_INFOBK);
         //pBrush->DeleteObject();
         //pBrush->CreateSolidBrush(RGB(201,201,201));
         break;
      }
   }

   return HBRUSH(*pBrush);
}

int ccwWindow::onEraseBkgnd(cwWindow *win, void *dc, void *brush)
{
   PP *pp = (PP*)win->__getPresParam();

   if ( (pp->mask & (1 << cwWindow::ppBkgndColor))
     && !win->ECL_ISKINDOF(cwControl) )
   {
      CDC *pDC = (CDC*)dc;
      CBrush *pBrush = (CBrush*)brush;
      pBrush->DeleteObject();
      pBrush->CreateSolidBrush(pp->bg_col);
      pBrush->UnrealizeObject();
      CRect client_rect;
      ((CWnd*)win->__getWnd())->GetClientRect(client_rect);
      pDC->DPtoLP(client_rect);
      pDC->FillRect(&client_rect, pBrush);
      return 1;
   }

   return -1;
}

bool ccwWindow::onRefresh(cwWindow *win)
{
   if ( win->onRefresh() ) {
      ((WCWnd*)win->_wnd)->SendMessageToDescendants(WM_ECL_REFRESH, 0, 0, FALSE);
      win->setFlags(cwWindow::wflWasRefreshed);
      return true;
   } else {
      return false;
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// ccwFrame
// ---------------------------------------------------------------------------
//
// ccwFrame
//
// ===========================================================================

class ccwFrame {

public:

   // Wird zum Erzeugen der Views aufgerufen
   static bool onCreateViews(cwFrame *win, void *info);
   // Wird aufgerufen, um den Wechsel des aktuellen Views anzukuendigen (true = prevent)
   static bool onViewChanging(cwFrame *win);
   // Wird aufgerufen, um den Wechsel des aktuellen Views bekanntzugeben
   static void onViewChanged(cwFrame *win);

};

#endif /*__INTERFACE__*/


// Implementierung ccwFrame
// ===========================================================================

bool ccwFrame::onCreateViews(cwFrame *win, void *info)
   { return win->onCreateViews(info); }
bool ccwFrame::onViewChanging(cwFrame *win)
   { return win->onViewChanging(); }
void ccwFrame::onViewChanged(cwFrame *win)
   { win->onViewChanged(); }




#ifdef __INTERFACE__

// ===========================================================================
// ccwMiniFrame
// ---------------------------------------------------------------------------
//
// ccwMiniFrame
//
// ===========================================================================

class ccwMiniFrame {

public:

   // Wird aufgerufen, wenn Groesse oder Dockstatus veraendert
   static void onSizedOrDocked(cwMiniFrame *win, int cx, int cy, bool floating, bool transition);

};

#endif /*__INTERFACE__*/


// Implementierung ccwMiniFrame
// ===========================================================================

void ccwMiniFrame::onSizedOrDocked(cwMiniFrame *win, int /*cx*/, int /*cy*/, bool floating, bool /*transiton*/)
{
   win->onSizeOrStateChange(floating);
   //TRACE2("onSizedOrDocked %d %d\n", floating, transiton);
}




#ifdef __INTERFACE__

// ===========================================================================
// ccwView
// ---------------------------------------------------------------------------
//
// ccwView
//
// ===========================================================================

class ccwView {

public:

   // cwView-Zeiger waehrend Initialisierung
   // (Kann nicht im Konstruktor uebergeben werden!)
   static cwView *srv_beeing_created;

   // Wird beim Initialisieren des Views aufgerufen
   static void onInit(cwView *win);
   // Wird zum Zeichnen des Views aufgerufen
   static void onDraw(cwView *win, void *ctxt);
   // Wird aufgerufen, wenn der View angezeigt wird
   static void onShowView(cwView *win);
   // Wird aufgerufen, wenn der View verborgen wird
   static void onHideView(cwView *win);

   // Setzen der _wnd-Komponente (nur Intern!)
   static void __setWnd(cwView *win, void *_wnd);
   // Runtime-Class des Views ermitteln (nur Intern!)
   static CRuntimeClass *__getRuntimeClass(cwView *win);

};

#endif /*__INTERFACE__*/


// Implementierung ccwView
// ===========================================================================

cwView *ccwView::srv_beeing_created = 0;
CRuntimeClass* pClass = RUNTIME_CLASS( CObject );

void ccwView::onInit(cwView *win)
   { if ( win->_wnd ) win->onInit(); }
void ccwView::onShowView(cwView *win)
   { win->onShowView(); }
void ccwView::onHideView(cwView *win)
   { win->onHideView(); }
void ccwView::__setWnd(cwView *win, void *_wnd)
   { win->_wnd = _wnd; }

void ccwView::onDraw(cwView *win, void *ctxt)
{
   if ( win->_wnd ) {
      cwContext context(ctxt);
      win->onDraw(&context);
   }
}

CRuntimeClass * ccwView::__getRuntimeClass(cwView *win)
{
   if ( win->getFlags(cwView::wflViewIsTabbed) ) {
      switch ( win->onGetViewType() ) {
      case 1:  return RUNTIME_CLASS(WCTabZoomView);
      default: return RUNTIME_CLASS(WCTabView);
      }
   } else {
      switch ( win->onGetViewType() ) {
      case 1:  return RUNTIME_CLASS(WCZoomView);
      default: return RUNTIME_CLASS(WCView);
      }
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// ccwDialog
// ---------------------------------------------------------------------------
//
// ccwDialog
//
// ===========================================================================

class ccwDialog {

public:

   // Wird beim Initialisieren des Dialogs aufgerufen
   static bool onInit(cwDialog *win);
   // Wird beim Druecken von OK aufgerufen
   static void onOk(cwDialog *win);
   // Wird beim Druecken von CANCEL aufgerufen
   static void onCancel(cwDialog *win);

   // Notebook-Dialog automatisch loeschen?
   static bool isAutoDelete(cwDialog *win);

};

#endif /*__INTERFACE__*/


// Implementierung ccwDialog
// ===========================================================================

bool ccwDialog::onInit(cwDialog *win)
   { win->__attachDelayed();
     return win->onInit(); }
void ccwDialog::onOk(cwDialog *win)
   { win->onOk(); }
void ccwDialog::onCancel(cwDialog *win)
   { win->onCancel(); }
bool ccwDialog::isAutoDelete(cwDialog *win)
   { return win && win->getFlags(cwWindow::wflAutoDelete); }




#ifdef __INTERFACE__

// ===========================================================================
// ccwNotebookPage
// ---------------------------------------------------------------------------
//
// ccwNotebookPage
//
// ===========================================================================

class ccwNotebookPage {

public:

   // Wird beim Druecken von OK aufgerufen
   static void onOk(cwNotebookPage *win);
   // Wird beim Druecken von CANCEL aufgerufen
   static void onCancel(cwNotebookPage *win);
   // Wird beim Druecken von APPLY aufgerufen
   static bool onApply(cwNotebookPage *win);
   // Wird beim Druecken von EDIT aufgerufen
   static void onEdit(cwNotebookPage *win);

   // Wird beim "Betreten" der Seite aufgerufen
   static bool onEnter(cwNotebookPage *win);
   // Wird beim "Verlassen" der Seite aufgerufen
   static bool onLeave(cwNotebookPage *win);

};

#endif /*__INTERFACE__*/


// Implementierung ccwNotebookPage
// ===========================================================================

void ccwNotebookPage::onOk(cwNotebookPage *win)
   { win->onOk(); }
void ccwNotebookPage::onCancel(cwNotebookPage *win)
   { win->onCancel(); }
bool ccwNotebookPage::onApply(cwNotebookPage *win)
   { return win->onApply(); }
void ccwNotebookPage::onEdit(cwNotebookPage *win)
   { win->onEdit(); }
bool ccwNotebookPage::onEnter(cwNotebookPage *win)
   { return win->onEnter(); }
bool ccwNotebookPage::onLeave(cwNotebookPage *win)
   { return win->onLeave(); }




#ifdef __INTERFACE__

// ===========================================================================
// ccwNotebookDlg
// ---------------------------------------------------------------------------
//
// ccwNotebookDlg
//
// ===========================================================================

class ccwNotebookDlg {

public:

   // Wird beim Initialisieren des Dialogs aufgerufen
   static bool onInit(cwNotebookDlg *win);
   // Wird beim Druecken von OK aufgerufen
   static void onOk(cwNotebookDlg *win);
   // Wird beim Druecken von CANCEL aufgerufen
   static void onCancel(cwNotebookDlg *win);
   // Wird beim Druecken von APPLY aufgerufen
   static void onApply(cwNotebookDlg *win);
   // Wird beim Druecken von EDIT aufgerufen
   static void onEdit(cwNotebookDlg *win);

   // Notebook-Dialog automatisch loeschen?
   static bool isAutoDelete(cwNotebookDlg *win);

   // Hat der Notebook-Dialog Standardknoepfe?
   static bool hasAnyButtons(cwNotebookDlg *win);
   // Hat der Notebook-Dialog den Standardknopf 'id'?
   static bool hasButton(cwNotebookDlg *win, int id);

};

#endif /*__INTERFACE__*/


// Implementierung ccwNotebookDlg
// ===========================================================================

bool ccwNotebookDlg::onInit(cwNotebookDlg *win)
   { win->__attachDelayed();
     return win->onInit(); }
void ccwNotebookDlg::onOk(cwNotebookDlg *win)
   { win->onOk(); }
void ccwNotebookDlg::onCancel(cwNotebookDlg *win)
   { win->onCancel(); }
void ccwNotebookDlg::onApply(cwNotebookDlg *win)
   { win->onApply(); }
void ccwNotebookDlg::onEdit(cwNotebookDlg *win)
   { win->onEdit(); }
bool ccwNotebookDlg::isAutoDelete(cwNotebookDlg *win)
   { return win && win->getFlags(cwWindow::wflAutoDelete); }
bool ccwNotebookDlg::hasAnyButtons(cwNotebookDlg *win)
   { return win && win->getStyle(cwNotebookDlg::nbsAllBtns) != 0; }

bool ccwNotebookDlg::hasButton(cwNotebookDlg *win, int id)
{
   switch ( id ) {
   case IDOK:           return !!win->getStyle(cwNotebookDlg::nbsOkBtn);
   case IDCANCEL:       return !!win->getStyle(cwNotebookDlg::nbsCancelBtn);
   case ID_APPLY_NOW:   return !!win->getStyle(cwNotebookDlg::nbsApplyBtn);
   case IDHELP:         return !!win->getStyle(cwNotebookDlg::nbsHelpBtn);
   }
   return false;
}




#ifdef __INTERFACE__

// ===========================================================================
// ccwToolWin
// ---------------------------------------------------------------------------
//
// ccwToolWin
//
// ===========================================================================

class ccwToolWin {

public:

   // Wird aufgerufen, wenn ein DropDown-Knopf gedrueckt wird
   static int onDropDown(cwToolWin *win, void *tbar);

};

#endif /*__INTERFACE__*/


// Implementierung ccwToolWin
// ===========================================================================

int ccwToolWin::onDropDown(cwToolWin *win, void *tbar)
{
   NMTOOLBAR *nmtb = (NMTOOLBAR*)tbar;
   int btn_id = nmtb->iItem;

   switch ( win->onDropDown(btn_id) ) {
   case cwToolWin::ddrNotHandled:   return TBDDRET_NODEFAULT;
   case cwToolWin::ddrHandled:      return TBDDRET_DEFAULT;
   case cwToolWin::ddrNormalBtn:    return TBDDRET_TREATPRESSED;
   }

   return TBDDRET_NODEFAULT;
}




#ifdef __INTERFACE__

// ===========================================================================
// ccwToolBar
// ---------------------------------------------------------------------------
//
// ccwToolBar
//
// ===========================================================================

class ccwToolBar {

public:

   // TBD: Events verfuegbar machen...

};

#endif /*__INTERFACE__*/


// Implementierung ccwToolBar
// ===========================================================================




#ifdef __INTERFACE__

// ===========================================================================
// ccwDialogBar
// ---------------------------------------------------------------------------
//
// ccwDialogBar
//
// ===========================================================================

class ccwDialogBar {

public:

   // TBD: Events verfuegbar machen...

};

#endif /*__INTERFACE__*/


// Implementierung ccwDialogBar
// ===========================================================================




#ifdef __INTERFACE__

// ===========================================================================
// ccwStatusBar
// ---------------------------------------------------------------------------
//
// ccwStatusBar
//
// ===========================================================================

class ccwStatusBar {

public:

   // TBD: Events verfuegbar machen...

};

#endif /*__INTERFACE__*/


// Implementierung ccwStatusBar
// ===========================================================================




#ifdef __INTERFACE__

// ===========================================================================
// ccwButtonCtl
// ---------------------------------------------------------------------------
//
// ccwButtonCtl
//
// ===========================================================================

class ccwButtonCtl {

public:

   // Wird bei einfachem Klick aufgerufen
   static void onClick(cwButtonCtl *win);
   // Wird bei Doppelklick aufgerufen
   static void onDblClick(cwButtonCtl *win);

};

#endif /*__INTERFACE__*/


// Implementierung ccwButtonCtl
// ===========================================================================

void ccwButtonCtl::onClick(cwButtonCtl *win)
   { win->onClick(); }
void ccwButtonCtl::onDblClick(cwButtonCtl *win)
   { win->onDblClick(); }




#ifdef __INTERFACE__

// ===========================================================================
// ccwListCtl
// ---------------------------------------------------------------------------
//
// ccwListCtl
//
// ===========================================================================

class ccwListCtl {

public:

   // Wird bei Doppelklick aufgerufen
   static void onListElemSelected(cwListCtl *win, cwListElem *elem);
   // Wird bei Aenderung der Selektion aufgerufen
   static void onSelectionChanged(cwListCtl *win, cwListElem *elem);

};

#endif /*__INTERFACE__*/


// Implementierung ccwListCtl
// ===========================================================================

void ccwListCtl::onListElemSelected(cwListCtl *win, cwListElem *elem)
   { win->onListElemSelected(elem); }
void ccwListCtl::onSelectionChanged(cwListCtl *win, cwListElem *elem)
   { win->onSelectionChanged(elem); }




#ifdef __INTERFACE__

// ===========================================================================
// ccwListBox
// ---------------------------------------------------------------------------
//
// ccwListBox
//
// ===========================================================================

class ccwListBox {

};

#endif /*__INTERFACE__*/


// Implementierung ccwListBox
// ===========================================================================




#ifdef __INTERFACE__

// ===========================================================================
// ccwComboBox
// ---------------------------------------------------------------------------
//
// ccwComboBox
//
// ===========================================================================

class ccwComboBox {

public:

   // Wird beim Aufklappen der Listbox aufgerufen
   static void onDropDown(cwComboBox *win);
   // Wird beim Zuklappen der Listbox aufgerufen
   static void onCloseUp(cwComboBox *win);

};

#endif /*__INTERFACE__*/


// Implementierung ccwComboBox
// ===========================================================================

void ccwComboBox::onDropDown(cwComboBox *win)
   { win->onDropDown(); }
void ccwComboBox::onCloseUp(cwComboBox *win)
   { win->onCloseUp(); }




#ifdef __INTERFACE__

// ===========================================================================
// ccwNotebookCtl
// ---------------------------------------------------------------------------
//
// ccwNotebookCtl
//
// ===========================================================================

class ccwNotebookCtl {

public:

   // Wird aufgerufen, um den Wechsel der aktuellen Seite anzukuendigen (true = prevent)
   static bool onPageChanging(cwNotebookCtl *win);
   // Wird aufgerufen, um den Wechsel der aktuellen Seite bekanntzugeben
   static void onPageChanged(cwNotebookCtl *win);

};

#endif /*__INTERFACE__*/


// Implementierung ccwNotebookCtl
// ===========================================================================

bool ccwNotebookCtl::onPageChanging(cwNotebookCtl *win)
   { return win->onPageChanging(); }
void ccwNotebookCtl::onPageChanged(cwNotebookCtl *win)
   { win->onPageChanged(); }




#ifdef __INTERFACE__

// ===========================================================================
// ccwContainer
// ---------------------------------------------------------------------------
//
// ccwContainer
//
// ===========================================================================

class ccwContainer {

public:

   // Wird aufgerufen, um den Inhalt der Container-Elemente zu erfragen
   static void onGetDispInfo(cwContainer *win, void *disp_info);
   // Wird aufgerufen, um Aenderungen am Inhalt der Container-Elemente bekanntzugeben
   static void onSetDispInfo(cwContainer *win, void *disp_info);

   // Wird aufgerufen, um die Aktivierung eines Items bekanntzugeben
   static void onItemActivated(cwContainer *win, void *item_activate);
   // Wird aufgerufen, um die Aenderung eines Items anzukuendigen (true = prevent)
   static bool onItemChanging(cwContainer *win, void *list_view);
   // Wird aufgerufen, um die Aenderung eines Items bekanntzugeben
   static void onItemChanged(cwContainer *win, void *list_view);
   // Wird aufgerufen, um die Aenderung von Item-Stati bekanntzugeben
   static void onItemStateChanged(cwContainer *win, void *state_chg);

   // Wird aufgerufen, um ein Einfach-Klick bekanntzugeben
   static void onClick(cwContainer *win, void *item_activate);
   // Wird aufgerufen, um ein Doppel-Klick bekanntzugeben
   static void onDblClick(cwContainer *win, void *item_activate);
   // Wird aufgerufen, um den Klick auf einen Spaltentitel bekanntzugeben
   static void onColumnClick(cwContainer *win, void *item);
   // Wird aufgerufen, um ein Einfach-Klick bekanntzugeben
   static void onReturn(cwContainer *win);
   // Wird aufgerufen, um die Container-Elemente zu zeichnen
   static long onDraw(cwContainer *win, void *cust_draw);

   // Wird aufgerufen, um den Beginn einer Drag-Operation bekanntzugeben
   static void onBeginDrag(cwContainer *win, void *item, int mouse_button);
   // Wird aufgerufen, um den Beginn einer Edit-Operation bekanntzugeben
   static bool onBeginEdit(cwContainer *win, void *item);
   // Wird aufgerufen, um das Ende einer Edit-Operation bekanntzugeben
   static bool onEndEdit(cwContainer *win, void *item);

};

#endif /*__INTERFACE__*/


// Implementierung ccwContainer
// ===========================================================================

void ccwContainer::onGetDispInfo(cwContainer *win, void *disp_info)
{
   LV_DISPINFO *info = (LV_DISPINFO*)disp_info;
   LV_ITEM *item = &info->item;

   if ( item->iSubItem >= 0 ) {

      int fld = win->getFieldFromColumn(item->iSubItem);
      cwListElem *elem = ((WCListCtrl*)win->_wnd)->elems[item->iItem];

      if ( item->mask & LVIF_TEXT ) {
         // ALT: cwListElem *elem = win->getElemWithIndex(item->iItem);
         elem->get(fld, item->pszText, item->cchTextMax);
      }

      if ( item->mask & LVIF_IMAGE ) {
         if ( item->iSubItem == 0 ) {
            item->iImage = elem->getBitmapId();
         } else {
            item->iImage = /*DUMMY:*/0;
         }
      }

   } else {

      if ( item->mask & LVIF_TEXT )
         item->pszText[0] = '\0';
      if ( item->mask & LVIF_IMAGE )
         item->iImage = /*DUMMY:*/0;

   }
}

void ccwContainer::onSetDispInfo(cwContainer *win, void *disp_info)
{
   LV_DISPINFO *info = (LV_DISPINFO*)disp_info;
   LV_ITEM *item = &info->item;

   if ( item->mask & LVIF_STATE ) {
      if ( item->state & LVIS_FOCUSED ) {
         cwListElem *elem = ((WCListCtrl*)win->_wnd)->elems[item->iItem];
         win->onSelectionChanged(elem);
      }
   }
}

void ccwContainer::onItemActivated(cwContainer *win, void *item_activate)
{
   NMITEMACTIVATE *ia = (NMITEMACTIVATE*)item_activate;
   if ( ia->iItem >= 0 ) {
      cwListElem *elem = ((WCListCtrl*)win->_wnd)->elems[ia->iItem];
      win->onListElemSelected(elem);
   }
}

bool ccwContainer::onItemChanging(cwContainer *win, void *list_view)
{
   NMLISTVIEW *lv = (NMLISTVIEW*)list_view;

   if ( lv->iItem >= 0 ) {
      if ( (lv->uNewState & LVIS_FOCUSED) && !(lv->uOldState & LVIS_FOCUSED) ) {
         cwListElem *elem = ((WCListCtrl*)win->_wnd)->elems[lv->iItem];
         return win->onSelectionChanging(elem);
      }
   }

   return false;
}

void ccwContainer::onItemChanged(cwContainer *win, void *list_view)
{
   NMLISTVIEW *lv = (NMLISTVIEW*)list_view;
   if ( lv->iItem >= 0 ) {
      if ( (lv->uNewState & LVIS_FOCUSED) && !(lv->uOldState & LVIS_FOCUSED) ) {
         cwListElem *elem = ((WCListCtrl*)win->_wnd)->elems[lv->iItem];
         if ( !elem->getFlags(cwListElem::eflPreventSelect) )
            win->onSelectionChanged(elem);
      }
   }
}

void ccwContainer::onItemStateChanged(cwContainer * /*win*/, void * /*state_chg*/)
{
}

void ccwContainer::onClick(cwContainer *win, void *item_activate)
{
   // Moeglicherweise laufendes EDIT beenden
   win->endEdit();

   NMITEMACTIVATE *nmi = (NMITEMACTIVATE*)item_activate;
   //cBase::DbgOut(0, "ccwContainer::onClick(item=%d, subitem=%d)", nmi->iItem, nmi->iSubItem);

   // Zuletzt angeklickte Spalte fuer eventuelles EDIT merken
   ((WCListCtrl*)win->_wnd)->last_column_clicked = nmi->iSubItem;

   if ( nmi->iItem < 0 )
      win->onSelectionChanged(0);
}

void ccwContainer::onDblClick(cwContainer *win, void * /*item_activate*/)
{
   // Moeglicherweise laufendes EDIT beenden
   win->endEdit();

   // TBD: Ueberhaupt auswerten??? win->onSelectionChanged(win->getSelectedElem());
}

void ccwContainer::onColumnClick(cwContainer *win, void *item)
{
   // Moeglicherweise laufendes EDIT beenden
   win->endEdit();

   NMLISTVIEW *lv = (NMLISTVIEW*)item;
   win->onColumnClick(lv->iSubItem);
}

void ccwContainer::onReturn(cwContainer *win)
{
   // Moeglicherweise laufendes EDIT beenden
   win->endEdit();

   // 10.04.2002 -TE- Doppelte Aufrufe von onListElemSelected
   // nach Druecken von RETURN, daher folgendes auskommentiert:
   // win->onListElemSelected(win->getSelectedElem());
}

long ccwContainer::onDraw(cwContainer *win, void *cust_draw)
{
   NMLVCUSTOMDRAW *lvcd = (NMLVCUSTOMDRAW*)cust_draw;
   long rc = CDRF_DODEFAULT;

   switch ( lvcd->nmcd.dwDrawStage ) {

   case CDDS_PREPAINT:
      rc = CDRF_NOTIFYITEMDRAW;
      break;

   case CDDS_ITEMPREPAINT:
      {
         cwListElem *elem = ((WCListCtrl*)win->_wnd)->elems[lvcd->nmcd.dwItemSpec];
         if ( elem->getFlags(cwListElem::eflDisplayBold) ) {
            SelectObject(lvcd->nmcd.hdc, ((WCListCtrl*)win->_wnd)->GetFontHandle());
            rc = CDRF_NEWFONT;
         }
         if ( elem->getFlags(cwListElem::eflDisplayFgColor) ) {
            lvcd->clrText = elem->getFgColor().getOsVal();
            rc = CDRF_NEWFONT;
         }
         if ( elem->getFlags(cwListElem::eflDisplayBgColor) ) {
            lvcd->clrTextBk = elem->getBgColor().getOsVal();
            rc = CDRF_NEWFONT;
         }
      }
      break;
   }

   return rc;
}

void ccwContainer::onBeginDrag(cwContainer *win, void *item, int mouse_button)
{
   NMLISTVIEW *lv = (NMLISTVIEW*)item;

   if ( lv->iItem >= 0 ) {
      cwListElem *elem = ((WCListCtrl*)win->_wnd)->elems[lv->iItem];
      win->onBeginDrag(elem, mouse_button);
   }
}

bool ccwContainer::onBeginEdit(cwContainer *win, void *edit_item)
{
   LV_DISPINFO *info = (LV_DISPINFO*)edit_item;
   LV_ITEM *item = &info->item;
   cwListElem *elem = ((WCListCtrl*)win->_wnd)->elems[item->iItem];
   int column_index = ((WCListCtrl*)win->_wnd)->last_column_clicked;
   //cBase::DbgOut(0, "ccwContainer::onBeginEdit(item=%d, subitem=%d)", item->iItem, ((WCListCtrl*)win->_wnd)->last_column_clicked);

   // rc: false = Edit verbieten; true = Edit erlauben
   return item->iItem >= 0 ? win->beginEdit(elem, win->getFieldFromColumn(column_index)) : false;
}

bool ccwContainer::onEndEdit(cwContainer *win, void *edit_item)
{
   LV_DISPINFO *info = (LV_DISPINFO*)edit_item;
   LV_ITEM *item = &info->item;
   cwListElem *elem = ((WCListCtrl*)win->_wnd)->elems[item->iItem];

   // rc: false = Speichern verbieten; true = Speichern erlauben
   return item->iItem >= 0 ? win->onEndEdit(elem, win->getEditField(), item->pszText) : false;
}




#ifdef __INTERFACE__

// ===========================================================================
// ccwTree
// ---------------------------------------------------------------------------
//
// ccwTree
//
// ===========================================================================

class ccwTree {

public:

   // Wird aufgerufen, um den Inhalt der Tree-Elemente zu erfragen
   static void onGetDispInfo(cwTree *win, void *disp_info);
   // Wird aufgerufen, um Aenderungen am Inhalt der Tree-Elemente bekanntzugeben
   static void onSetDispInfo(cwTree *win, void *disp_info);

   // Wird aufgerufen, um den Selektionswechsel anzukuendigen (true = prevent)
   static bool onSelChanging(cwTree *win, void *tree_view);
   // Wird aufgerufen, um den Selektionswechsel bekanntzugeben
   static void onSelChanged(cwTree *win, void *tree_view);
   // Wird aufgerufen, um ein Expand/Collapse anzukuendigen (true = prevent)
   static bool onItemExpanding(cwTree *win, void *tree_view);
   // Wird aufgerufen, um den Expand/Collapse bekanntzugeben
   static void onItemExpanded(cwTree *win, void *tree_view);

   // Wird aufgerufen, um den Beginn einer Drag-Operation bekanntzugeben
   static void onBeginDrag(cwTree *win, void *item, int mouse_button);
   // Wird aufgerufen, um den Beginn einer Edit-Operation bekanntzugeben
   static bool onBeginEdit(cwTree *win, void *item);
   // Wird aufgerufen, um das Ende einer Edit-Operation bekanntzugeben
   static bool onEndEdit(cwTree *win, void *item);

   // Wird bei einfachem Klick aufgerufen (0=None, 1=Left, 2=Right, 3=Middle)
   static bool onClick(cwTree *win, int button_no, long pos);
   // Wird bei Doppelklick aufgerufen (0=RETURN, 1=Left, 2=Right, 3=Middle)
   static bool onDblClick(cwTree *win, int button_no, long pos);

};

#endif /*__INTERFACE__*/


// Implementierung ccwTree
// ===========================================================================

void ccwTree::onGetDispInfo(cwTree * /*win*/, void *disp_info)
{
   TV_DISPINFO *info = (TV_DISPINFO*)disp_info;
   TV_ITEM& item = info->item;

   cwListElem *elem = (cwListElem*)item.lParam;

   if ( elem != 0 ) {

      if ( item.mask & TVIF_TEXT ) {
         elem->get(csQuery::fldName, item.pszText, item.cchTextMax);
      }

      if ( item.mask & TVIF_IMAGE ) {
         item.iImage = /*DUMMY:*/0;
      }

      if ( item.mask & TVIF_SELECTEDIMAGE ) {
         item.iSelectedImage = /*DUMMY:*/0;
      }

      if ( item.mask & TVIF_CHILDREN ) {
         if ( elem->getFlags(cwListElem::eflChildsLoaded) ) {
            item.cChildren = elem->hasChilds();
         } else {
            item.cChildren = 1;
         }
      }

   }
}

void ccwTree::onSetDispInfo(cwTree * /*win*/, void * /*disp_info*/)
{
   /*
   TV_DISPINFO *info = (TV_DISPINFO*)disp_info;
   TV_ITEM *item = &info->item;
   */
}

bool ccwTree::onSelChanging(cwTree *win, void *tree_view)
{
   NMTREEVIEW *tvw = (NMTREEVIEW*)tree_view;
   TV_ITEM& item_new = tvw->itemNew;
   return win->onSelectionChanging((cwListElem*)item_new.lParam);
}

void ccwTree::onSelChanged(cwTree *win, void *tree_view)
{
   NMTREEVIEW *tvw = (NMTREEVIEW*)tree_view;
   TV_ITEM& item_new = tvw->itemNew;
   win->onSelectionChanged((cwListElem*)item_new.lParam);
}

bool ccwTree::onItemExpanding(cwTree *win, void *tree_view)
{
   NMTREEVIEW *tvw = (NMTREEVIEW*)tree_view;
   TV_ITEM& item_new = tvw->itemNew;

   // cBase::DbgOut(0, "Expanding: %04x %08x mask=%08x state=%08x", tvw->action, item_new.hItem, item_new.mask, item_new.state);
   return (tvw->action & TVE_EXPAND) ?
      win->onTreeExpanding((cwListElem*)item_new.lParam)
    : win->onTreeCollapsing((cwListElem*)item_new.lParam);
}

void ccwTree::onItemExpanded(cwTree *win, void *tree_view)
{
   NMTREEVIEW *tvw = (NMTREEVIEW*)tree_view;
   TV_ITEM& item_new = tvw->itemNew;

   // cBase::DbgOut(0, "Expanded:  %04x %08x mask=%08x state=%08x", tvw->action, item_new.hItem, item_new.mask, item_new.state);
   if ( tvw->action & TVE_EXPAND ) {
      win->onTreeExpanded((cwListElem*)item_new.lParam);
   } else {
      win->onTreeCollapsed((cwListElem*)item_new.lParam);
   }
}

void ccwTree::onBeginDrag(cwTree *win, void *item, int mouse_button)
{
   NMTREEVIEW *tvw = (NMTREEVIEW*)item;
   TV_ITEM& item_new = tvw->itemNew;
   win->onBeginDrag((cwListElem*)item_new.lParam, mouse_button);
}

bool ccwTree::onBeginEdit(cwTree *win, void *disp_info)
{
   TV_DISPINFO *info = (TV_DISPINFO*)disp_info;
   TV_ITEM& item = info->item;

   // rc: false = Edit verbieten; true = Edit erlauben
   return win->onBeginEdit((cwListElem*)item.lParam, 0);
}

bool ccwTree::onEndEdit(cwTree *win, void *disp_info)
{
   TV_DISPINFO *info = (TV_DISPINFO*)disp_info;
   TV_ITEM& item = info->item;

   // rc: false = Speichern verbieten; true = Speichern erlauben
   return win->onEndEdit((cwListElem*)item.lParam, win->getEditField(), item.pszText);
}

bool ccwTree::onClick(cwTree *win, int button_no, long pos)
{
   if ( button_no == 2 ) {
      WCTreeCtrl *mfc_tree = (WCTreeCtrl*)win->_wnd;
      mfc_tree->SendMessage(WM_CONTEXTMENU, (WPARAM)mfc_tree->m_hWnd, pos);
      return true;
   }

   return false;
}

bool ccwTree::onDblClick(cwTree *win, int button_no, long /*pos*/)
{
   if ( button_no == 0 || button_no == 1 ) {
      win->onListElemSelected(win->getCursoredElem());
      return true;
   }
   return false;
}




#ifdef __INTERFACE__

// ===========================================================================
// ccwGrid
// ---------------------------------------------------------------------------
//
// ccwGrid
//
// ===========================================================================

class ccwGrid {

public:

   // Darf die Groesse von Spalte 'col' veraendert werden?
   static bool onCanSizeColumn(cwGrid *win, int col);
   // Darf die Groesse von Zeile 'row' veraendert werden?
   static bool onCanSizeRow(cwGrid *win, int row);
   // Darf die Groesse der Spaltenkoepfe veraendert werden?
   static bool onCanSizeColumnHead(cwGrid *win);
   // Darf die Groesse der Zeilenkoepfe veraendert werden?
   static bool onCanSizeRowHead(cwGrid *win);

   // Wird aufgerufen, wenn sich die aktuelle Spalte geaendert hat
   static void onChangedColumn(cwGrid *win, int old_col, int new_col);
   // Wird aufgerufen, wenn sich die aktuelle Zeile geaendert hat
   static void onChangedRow(cwGrid *win, int old_row, int new_row);
   // Wird aufgerufen, wenn sich die aktuelle Zelle geaendert hat
   static void onChangedCell(cwGrid *win, int old_col, int new_col, int old_row, int new_row);

   // Wird aufgerufen, wenn eine Zelle angeklickt wurde
   static void onClickCell(cwGrid *win, int col, int row, const cwCmdMouse& cmd);
   // Wird aufgerufen, wenn ein Spaltenkopf angeklickt wurde
   static void onClickColumnHead(cwGrid *win, int col, int row, const cwCmdMouse& cmd);
   // Wird aufgerufen, wenn ein Zeilenkopf angeklickt wurde
   static void onClickRowHead(cwGrid *win, int col, int row, const cwCmdMouse& cmd);
   // Wird aufgerufen, wenn die linke obere Ecke angeklickt wurde
   static void onClickCorner(cwGrid *win, const cwCmdMouse& cmd);

   // Wird aufgerufen, um den Wert einer Zelle zu ermitteln
   static void onGetCell(cwGrid *win, int col, int row, void *cell);
   // Wird aufgerufen, um den Wert einer Zelle zu setzen
   static void onSetCell(cwGrid *win, int col, int row, void *cell);
   // Wird bei einer Zellen-Notification aufgerufen
   static bool onCellNotify(cwGrid *win, int col, int row, long id, long msg, long param);

};

#endif /*__INTERFACE__*/


// Implementierung ccwGrid
// ===========================================================================

bool ccwGrid::onCanSizeColumn(cwGrid *win, int col)
   { return win->onCanSizeColumn(col); }
bool ccwGrid::onCanSizeRow(cwGrid *win, int row)
   { return win->onCanSizeRow(row); }
bool ccwGrid::onCanSizeColumnHead(cwGrid *win)
   { return win->onCanSizeColumnHead(); }
bool ccwGrid::onCanSizeRowHead(cwGrid *win)
   { return win->onCanSizeRowHead(); }
void ccwGrid::onChangedColumn(cwGrid *win, int old_col, int new_col)
   { win->onChangedColumn(old_col, new_col); }
void ccwGrid::onChangedRow(cwGrid *win, int old_row, int new_row)
   { win->onChangedRow(old_row, new_row); }
void ccwGrid::onChangedCell(cwGrid *win, int old_col, int new_col, int old_row, int new_row)
   { win->onChangedCell(old_col, new_col, old_row, new_row); }
void ccwGrid::onClickCell(cwGrid *win, int col, int row, const cwCmdMouse& cmd)
   { win->onClickCell(col, row, cmd); }
void ccwGrid::onClickColumnHead(cwGrid *win, int col, int row, const cwCmdMouse& cmd)
   { win->onClickColumnHead(col, row, cmd); }
void ccwGrid::onClickRowHead(cwGrid *win, int col, int row, const cwCmdMouse& cmd)
   { win->onClickRowHead(col, row, cmd); }
void ccwGrid::onClickCorner(cwGrid *win, const cwCmdMouse& cmd)
   { win->onClickCorner(cmd); }

void ccwGrid::onGetCell(cwGrid *win, int col, int row, void *cell_p)
{
   if ( win == 0 || cell_p == 0 )
      return;

   int row_count = win->getRowCount();
   //int col_count = win->getColumnCount();

   if ( col >= 0 && row >= 0 ) {
      int fld = win->getFieldFromColumn(col, row % row_count);
      if ( fld >= 0 ) {
         CUGCell *cell = (CUGCell*)cell_p;
         cwListElem *elem = win->getElemWithIndex(row / row_count);
         if ( elem != 0 ) {
            cString text;
            if ( elem->get(fld, text) )
               cell->SetText(text);
            csFilter *flt = win->getQuery() ? win->getQuery()->getFilter(fld) : 0;
            if ( flt != 0 && flt->getValueCount() > 0 )
               cell->SetCellType(UGCT_DROPLIST);
         }
      }
   }
}

void ccwGrid::onSetCell(cwGrid * /*win*/, int /*col*/, int /*row*/, void * /*cell*/)
{
}

bool ccwGrid::onCellNotify(cwGrid *win, int col, int row, long /*id*/, long msg, long param)
{
   if ( win == 0 )
      return false;

   int row_count = win->getRowCount();
   //int col_count = win->getColumnCount();

   if ( col >= 0 && row >= 0 ) {
      int fld = win->getFieldFromColumn(col, row % row_count);
      if ( fld >= 0 ) {
         csFilter *flt = win->getQuery() ? win->getQuery()->getFilter(fld) : 0;
         cwListElem *elem = win->getElemWithIndex(row / row_count);
         if ( elem != 0 ) {

            switch ( msg ) {

            case UGCT_DROPLISTSTART:
               if ( flt != 0 && flt->getValueCount() > 0 ) {
                  CStringList *list = (CStringList*)param;
                  int count = flt->getValueCount();
                  for ( int i = 0 ; i < count ; i++ ) {
                     cString key, name;
                     if ( flt->getValue(i, key, name) )
                        list->AddTail((const char *)name);
                  }
               }
               return true;

            case UGCT_DROPLISTSELECT:
               if ( flt != 0 && flt->getValueCount() > 0 ) {
                  CString *str = (CString*)param;
                  int count = flt->getValueCount();
                  for ( int i = 0 ; i < count ; i++ ) {
                     cString key, name;
                     if ( flt->getValue(i, key, name) && name.compareNoCase(*str) == 0 ) {
                        TRACE1("Selected %s\n", (const char *)key);
                        return true;
                     }
                  }
               }
               // Beep!
               return false;

            }

         }
      }
   }

   return false;
}




#ifdef __INTERFACE__

// ===========================================================================
// ccwEditCtl
// ---------------------------------------------------------------------------
//
// ccwEditCtl
//
// ===========================================================================

class ccwEditCtl {

public:

   // Wird bei Aenderung des Eingabefeldes VOR Schirmupdate aufgerufen
   static void onEditChanged(cwEditCtl *win);
   // Wird bei Aenderung des Eingabefeldes NACH Schirmupdate aufgerufen
   static void onEditUpdated(cwEditCtl *win);
   // Detailauswahl zum Control wurde angefordert
   static void onDetailRequest(cwEditCtl *win);

};

#endif /*__INTERFACE__*/


// Implementierung ccwEditCtl
// ===========================================================================

void ccwEditCtl::onEditChanged(cwEditCtl *win)
   { win->onEditChanged(); }
void ccwEditCtl::onEditUpdated(cwEditCtl *win)
   { win->onEditUpdated(); }
void ccwEditCtl::onDetailRequest(cwEditCtl *win)
   { win->onDetailRequest();
     win->callEvent(cwEditCtl::evtDetailRequested); }


