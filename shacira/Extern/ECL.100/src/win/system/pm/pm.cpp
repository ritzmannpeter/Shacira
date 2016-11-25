// ===========================================================================
// pm.cpp                                        ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    CWnd
//     |
//     +--TWCWnd<CWnd>
//         |
//         +--WCWnd
//
//    CFrameWnd
//     |
//     +--TWCWnd<CFrameWnd>
//         |
//         +--TWCFrameWnd<CFrameWnd>
//             |
//             +--WCFrameWnd
//
// ===========================================================================

#include "win/system/pm.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ---------------------------------------------------------------------------

#define INCL_PM
#define INCL_NLS
#define INCL_BASE
#include <os2.h>

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// cPMWnd
// ---------------------------------------------------------------------------
//
// cPMWnd
//
// ===========================================================================


class cPMWnd {

protected:
   // Installiert das Subclassing
   BOOL InstallHandler(HWND _hwnd, PFNWP func = BaseHandler);
   // Deinstalliert das Subclassing
   BOOL RestoreHandler(void);

public:
   // Registriert die Standard-Fensterklasse
   static BOOL Register(HAB hab);
   // Ermittelt globalen HAB
   static HAB GetGlobalHAB() { return global_hab; }
   // Ermittelt zugehoerigen HAB
   HAB GetHab() const { return WinQueryAnchorBlock(hwnd); }

   // Liefert den ERRORID-Code des letzten PM-Fehlers
   ERRORID GetErrorID();
   // Ermittelt den Fehlercode aus einem ERRORID-Code
   USHORT GetErrorCode(ERRORID id) const { return ERRORIDERROR(id); }
   // Ermittelt die Fehlerklasse aus einem ERRORID-Code
   USHORT GetErrorSev(ERRORID id) const { return ERRORIDSEV(id); }

   // Liefert zu einem HWND den cPMWnd-Zeiger oder NULL
   cPMWnd *GetWindow(HWND hwnd) const;
   // Liefert Windowhandle
   HWND GetHandle() const { return hwnd; }

   // Meldungen senden/posten
   // =======================

   MRESULT SendMsg(ULONG msg, MPARAM mp1 = MPVOID, MPARAM mp2 = MPVOID) const { return WinSendMsg(hwnd, msg, mp1, mp2); }
   MRESULT SendMsg(ULONG msg, ULONG  mp1         , MPARAM mp2 = MPVOID) const { return WinSendMsg(hwnd, msg, MPFROMLONG(mp1), mp2); }
   MRESULT SendMsg(ULONG msg, MPARAM mp1         , ULONG  mp2         ) const { return WinSendMsg(hwnd, msg, mp1, MPFROMLONG(mp2)); }
   MRESULT SendMsg(ULONG msg, ULONG  mp1         , ULONG  mp2         ) const { return WinSendMsg(hwnd, msg, MPFROMLONG(mp1), MPFROMLONG(mp2)); }
   BOOL    PostMsg(ULONG msg, MPARAM mp1 = MPVOID, MPARAM mp2 = MPVOID) const { return WinPostMsg(hwnd, msg, mp1, mp2); }
   BOOL    PostMsg(ULONG msg, ULONG  mp1         , MPARAM mp2 = MPVOID) const { return WinPostMsg(hwnd, msg, MPFROMLONG(mp1), mp2); }
   BOOL    PostMsg(ULONG msg, MPARAM mp1         , ULONG  mp2         ) const { return WinPostMsg(hwnd, msg, mp1, MPFROMLONG(mp2)); }
   BOOL    PostMsg(ULONG msg, ULONG  mp1         , ULONG  mp2         ) const { return WinPostMsg(hwnd, msg, MPFROMLONG(mp1), MPFROMLONG(mp2)); }

   // Handler
   // =======

private:
   // Default-Handler installieren
   void SetDefaultHandler(PFNWP def_handler) { orig_wproc = def_handler; }

protected:
   // Default-Handler f�r alle cWindows
   MRESULT DefaultHandler(const cCmd& cmd);
   // Handler f�r _alle_ Meldungen (auch WM_CONTROL/WM_COMMAND)
   virtual MRESULT MessageHandler(const cCmd& cmd);
   // Spezieller Handler f�r alle WM_CONTROL-Meldungen
   virtual MRESULT ControlHandler(const cCmd& cmd);
   // Spezieller Handler f�r alle WM_COMMAND-Meldungen
   virtual MRESULT CommandHandler(const cCmd& cmd);
   // Spezieller Handler f�r alle WM_HELP-Meldungen
   virtual MRESULT HelpHandler(const cCmd& cmd);

private:
   static HAB global_hab;       // HAB der Applikation
   PFNWP orig_wproc;            // Original-Windowfunktion
   ULONG id;                    // Window-ID und Flags
   HWND hwnd;                   // Window-Handle

};


