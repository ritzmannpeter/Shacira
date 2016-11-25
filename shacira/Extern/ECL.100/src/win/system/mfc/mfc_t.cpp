// ===========================================================================
// mfc_t.cpp                                     ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    MFC
//     |
//     +-TWCWinApp<MFC>          - Wrapper-Template fuer "CWinApp"
//     |
//     +-TWCWnd<MFC>             - Wrapper-Template fuer "CWnd"
//        |
//        +-TWCFrameWnd<MFC>     - Wrapper-Template fuer "CFrameWnd"
//        |
//        +-TWCDialog<MFC>       - Wrapper-Template fuer "CDialog"
//        |
//        +-TWCButton<MFC>       - Wrapper-Template fuer "CButton"
//        |
//        +-TWCListBox<MFC>      - Wrapper-Template fuer "CListBox"
//        |
//        +-TWCComboBox<MFC>     - Wrapper-Template fuer "CComboBox"
//        |
//        +-TWCEdit<MFC>         - Wrapper-Template fuer "CEdit"
//
// ===========================================================================




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "win/system/mfc/stdafx.h"
#include "win/system/mfc/mfc_c.hpp"
#include "win/system/mfc/utool/OXLayoutManager.h"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCWinApp<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWinApp<MFC>
//
// ===========================================================================

template<class MFC>
class TWCWinApp : public MFC {
   friend class cwApplication;
public:
   TWCWinApp(cwApplication *srv, LPCTSTR lpszAppName);
   virtual ~TWCWinApp();
   // Set _srv when cwApplication object ready
   void SetSrv(cwApplication *srv);
   // Overrides
	BOOL InitInstance();
   int ExitInstance();
protected:
   cwApplication *_srv;
};

   template<class MFC>
   TWCWinApp<MFC>::TWCWinApp(cwApplication *srv, LPCTSTR lpszAppName) : MFC(lpszAppName)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCWinApp<MFC>::~TWCWinApp()
   {
      if ( _srv )
         ccwApplication::__disconnect(_srv);
   }

   template<class MFC>
   void TWCWinApp<MFC>::SetSrv(cwApplication *srv)
   {
      _srv = srv;
   }

   template<class MFC>
   BOOL TWCWinApp<MFC>::InitInstance()
   {
      MFC::InitInstance();
      // onInit() wird normalerweise nie aufgerufen, da _srv vor WinMain immer == 0
      // Statt dessen wird onInit() aus WinMain nochmal aufgerufen!!!
      return _srv ? (BOOL)ccwApplication::onInit(_srv) : TRUE;
   }

   template<class MFC>
   int TWCWinApp<MFC>::ExitInstance()
   {
      // Eigener RC hat Prioritaet vor System-RC
      int my_rc = _srv ? ccwApplication::onExit(_srv) : 0;
      int sys_rc = MFC::ExitInstance();
      return my_rc == 0 ? sys_rc : my_rc;
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCMenu<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCMenu<MFC>
//
// ===========================================================================

template<class MFC>
class TWCMenu : public MFC {
   friend class cwMenu;
public:
   TWCMenu(cwMenu *srv);
   virtual ~TWCMenu();
protected:
   cwMenu *_srv;
};

   template<class MFC>
   TWCMenu<MFC>::TWCMenu(cwMenu *srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCMenu<MFC>::~TWCMenu()
   {
      if ( _srv )
         ccwMenu::__disconnect(_srv);
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCOleDataSource<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCOleDataSource<MFC>
//
// ===========================================================================

template<class MFC>
class TWCOleDataSource : public MFC {
   friend class cwDragSource;
public:
   TWCOleDataSource(cwDragSource *srv);
   virtual ~TWCOleDataSource();
protected:
   cwDragSource *_srv;
};

   template<class MFC>
   TWCOleDataSource<MFC>::TWCOleDataSource(cwDragSource *srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCOleDataSource<MFC>::~TWCOleDataSource()
   {
      if ( _srv )
         ccwDragSource::__disconnect((cwDragDrop*)_srv);
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCOleDropTarget<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCOleDropTarget<MFC>
//
// ===========================================================================

template<class MFC>
class TWCOleDropTarget : public MFC {
   friend class cwDropTarget;
public:
   TWCOleDropTarget(cwDropTarget *srv);
   virtual ~TWCOleDropTarget();
protected:
   cwDropTarget *_srv;
   DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
   DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
   DROPEFFECT OnDragScroll(CWnd* pWnd, DWORD dwKeyState, CPoint point);
   void OnDragLeave(CWnd* pWnd);
   DROPEFFECT OnDropEx(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point);
};

   template<class MFC>
   TWCOleDropTarget<MFC>::TWCOleDropTarget(cwDropTarget *srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCOleDropTarget<MFC>::~TWCOleDropTarget()
   {
      if ( _srv )
         ccwDropTarget::__disconnect((cwDragDrop*)_srv);
   }

   template<class MFC>
   DROPEFFECT TWCOleDropTarget<MFC>::OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
   {
      cwCmdDrag cmd = ccwCmd((dwKeyState&0xffff)|0xf0000000, (unsigned int)pDataObject, MAKELPARAM(point.x,point.y));
      if ( ccwDropTarget::onDragEnter(_srv, pWnd, cmd) )
         return cwCmdDrag::convAllowedOpsToSys(cmd.getAllowedOps());
      return MFC::OnDragEnter(pWnd, pDataObject, dwKeyState, point);
   }

   template<class MFC>
   DROPEFFECT TWCOleDropTarget<MFC>::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
   {
      cwCmdDrag cmd = ccwCmd((dwKeyState&0xffff)|0xf0000000, (unsigned int)pDataObject, MAKELPARAM(point.x,point.y));
      if ( ccwDropTarget::onDragOver(_srv, pWnd, cmd) )
         return cwCmdDrag::convAllowedOpsToSys(cmd.getAllowedOps());
      return MFC::OnDragOver(pWnd, pDataObject, dwKeyState, point);
   }

   template<class MFC>
   DROPEFFECT TWCOleDropTarget<MFC>::OnDragScroll(CWnd* pWnd, DWORD dwKeyState, CPoint point)
   {
      cwCmdDrag cmd = ccwCmd((dwKeyState&0xffff)|0xf0000000, 0, MAKELPARAM(point.x,point.y));
      if ( ccwDropTarget::onDragScroll(_srv, pWnd, cmd) )
         return cwCmdDrag::convAllowedOpsToSys(cmd.getAllowedOps());
      return MFC::OnDragScroll(pWnd, dwKeyState, point);
   }

   template<class MFC>
   void TWCOleDropTarget<MFC>::OnDragLeave(CWnd* pWnd)
   {
      if ( !ccwDropTarget::onDragLeave(_srv, pWnd) )
         MFC::OnDragLeave(pWnd);
   }

   template<class MFC>
   DROPEFFECT TWCOleDropTarget<MFC>::OnDropEx(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point)
   {
      cwCmdDrop cmd = ccwCmd(0xf000ffff, (unsigned int)pDataObject, MAKELPARAM(point.x,point.y));
      cmd.setDropOp(cwCmdDrop::convSysToDropOp(dropDefault));
      cmd.setSourceOps(cwCmdDrop::convSysToSourceOps(dropList));
      if ( ccwDropTarget::onDrop(_srv, pWnd, cmd) )
         return cwCmdDrop::convDropOpToSys(cmd.getDropOp());
      return MFC::OnDropEx(pWnd, pDataObject, dropDefault, dropList, point);
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCImageList<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCImageList<MFC>
//
// ===========================================================================

template<class MFC>
class TWCImageList : public MFC {
   friend class cwIconList;
public:
   TWCImageList(cwIconList *srv);
   virtual ~TWCImageList();
protected:
   cwIconList *_srv;
};

   template<class MFC>
   TWCImageList<MFC>::TWCImageList(cwIconList *srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCImageList<MFC>::~TWCImageList()
   {
      if ( _srv )
         ccwIconList::__disconnect(_srv);
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCWnd<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//
// ===========================================================================

template<class MFC>
class TWCWnd : public MFC {
   CBrush brush_bkgnd;
public:
   TWCWnd(cwWindow *srv);
   TWCWnd(cwWindow *srv, UINT id, CWnd *parent); // needed by CDialog
   virtual ~TWCWnd();
protected:
   cwWindow *_srv;
   // Window procedure override
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
   // Overrides from the MFC framework
   afx_msg BOOL PreTranslateMessage(MSG *pMsg);
   afx_msg BOOL PreCreateWindow(CREATESTRUCT& cs);
   afx_msg void PreSubclassWindow( );
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnDestroy();
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg BOOL OnCommand(WPARAM wParam, LPARAM lParam);
   afx_msg void OnSysCommand(UINT nId, LPARAM lParam);
   afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
   afx_msg void OnUpdateUI(CCmdUI* pCmdUI);
   // ECL specific commands
   afx_msg LRESULT OnEclRefresh(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnEclStore(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnEclDiscard(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnEclAllowTurn(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnEclAllowStore(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnEclAllowDiscard(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnEclAllowClose(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnEclExecDelayed(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnEclDragEnter(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnEclDragOver(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnEclDragScroll(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnEclDragLeave(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnEclDrop(WPARAM wParam, LPARAM lParam);
};

   template<class MFC>
   TWCWnd<MFC>::TWCWnd(cwWindow *srv)
   {
      _srv = srv;
      brush_bkgnd.CreateSolidBrush(RGB(255,255,255));
   }

   template<class MFC>
   TWCWnd<MFC>::TWCWnd(cwWindow *srv, UINT id, CWnd *parent) : MFC(id, parent)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCWnd<MFC>::~TWCWnd()
   {
      ccwWindow::__disconnect(_srv);
   }

   // Window procedure override

   template<class MFC>
   LRESULT TWCWnd<MFC>::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
   {
      switch ( message ) {
      case WM_KILLFOCUS:
         ccwWindow::onLoseFocus(_srv);
         break;
      case WM_SETFOCUS:
         ccwWindow::onGainFocus(_srv);
         break;
      case WM_TIMER:
         if ( ccwWindow::onTimer(_srv, int(wParam)) )
            KillTimer(int(wParam));
         break;
      case WM_KEYDOWN:
      case WM_KEYUP:
         {
            cwCmdChar cmd = ccwCmd(message, wParam, lParam);
            if ( cmd.getVirt() != cwCmdChar::vkUndef ) {
               ccwWindow::onChar(_srv, cmd);
               if ( ccwCmd(cmd).getMsg() == 0 && cmd.getChar() == 0 )
                  return 0;
            }
      		break;
         }
         break;
      case WM_CHAR:
         {
            cwCmdChar cmd = ccwCmd(message, wParam, lParam);
            ccwWindow::onChar(_srv, cmd);
            if ( ccwCmd(cmd).getMsg() == 0 ) {
               wParam = cmd.getChar();
               if ( wParam == 0 ) return 0;
            }
         }
         break;
      case WM_LBUTTONDOWN:
      case WM_LBUTTONUP:
      case WM_LBUTTONDBLCLK:
      case WM_RBUTTONDOWN:
      case WM_RBUTTONUP:
      case WM_RBUTTONDBLCLK:
      case WM_MBUTTONDOWN:
      case WM_MBUTTONUP:
      case WM_MBUTTONDBLCLK:
         if ( ccwWindow::onMouseClick(_srv, ccwCmd(message, wParam, lParam)) )
            return 0;
         break;
      case WM_MOUSEMOVE:
         if ( ccwWindow::onMouseMove(_srv, ccwCmd(message, wParam, lParam)) )
            return 0;
         break;
      case WM_CONTEXTMENU:
         if ( ccwWindow::onContextMenu(_srv, ccwCmd(message, wParam, lParam)) )
            return 0;
         break;
      case WM_HSCROLL:
      case WM_VSCROLL:
         ccwWindow::onScroll(_srv, ccwCmd(message, wParam, lParam));
         break;
      }

   	return MFC::WindowProc(message, wParam, lParam);
   }

   // Overrides from the MFC framework

   template<class MFC>
   afx_msg BOOL TWCWnd<MFC>::PreTranslateMessage(MSG *pMsg)
   {
      return ccwWindow::onDispatchMsg(_srv, (void*)pMsg) ?
         MFC::PreTranslateMessage(pMsg) : TRUE;
   }

   template<class MFC>
   afx_msg BOOL TWCWnd<MFC>::PreCreateWindow(CREATESTRUCT& cs)
   {
      return MFC::PreCreateWindow(cs) && ccwWindow::onPreCreate(_srv, (void*)&cs);
   }

   template<class MFC>
   afx_msg void TWCWnd<MFC>::PreSubclassWindow()
   {
      MFC::PreSubclassWindow();
      ccwWindow::onPreSubclass(_srv);
   }

   template<class MFC>
   afx_msg int TWCWnd<MFC>::OnCreate(LPCREATESTRUCT lpCreateStruct)
   {
	   if (MFC::OnCreate(lpCreateStruct) == -1)
		   return -1;
      return ccwWindow::onCreate(_srv) ? 0 : -1;
   }

   template<class MFC>
   afx_msg void TWCWnd<MFC>::OnDestroy()
   {
      ccwWindow::onDestroy(_srv);
      MFC::OnDestroy();
   }

   template<class MFC>
   afx_msg void TWCWnd<MFC>::OnSize(UINT nType, int cx, int cy)
   {
      MFC::OnSize(nType, cx, cy);
      ccwWindow::onSize(_srv, cx, cy);
   }

   template<class MFC>
   afx_msg void TWCWnd<MFC>::OnChar(UINT /*nChar*/, UINT /*nRepCnt*/, UINT /*nFlags*/)
   {
      //ccwWindow::onChar(_srv, nChar);
   }

   template<class MFC>
   afx_msg BOOL TWCWnd<MFC>::OnCommand(WPARAM wParam, LPARAM lParam)
   {
      // Erste Chance: Das ECL-Fenster selbst darf das Kommando bearbeiten
      if ( ccwWindow::onCommand(_srv, cwCmdEvt(ccwCmd(WM_COMMAND, wParam, lParam))) )
         return TRUE;
      // Zweite Chance: Die MFC (oder Windows) darf das Kommando bearbeiten
      return MFC::OnCommand(wParam, lParam);
   }

   template<class MFC>
   afx_msg void TWCWnd<MFC>::OnSysCommand(UINT nId, LPARAM lParam)
   {
      if ( ccwWindow::onCommand(_srv, cwCmdEvt(ccwCmd(WM_SYSCOMMAND, nId, lParam))) )
         return;
      MFC::OnSysCommand(nId, lParam);
   }

   template<class MFC>
   afx_msg HBRUSH TWCWnd<MFC>::CtlColor(CDC* pDC, UINT nCtlColor)
   {
      return HBRUSH(ccwWindow::onCtlColor(_srv, pDC, nCtlColor, &brush_bkgnd));
   }

   template<class MFC>
   afx_msg BOOL TWCWnd<MFC>::OnEraseBkgnd(CDC* pDC)
   {
      switch ( ccwWindow::onEraseBkgnd(_srv, pDC, &brush_bkgnd) ) {
      case 0:  return FALSE;
      case 1:  return TRUE;
      default: return MFC::OnEraseBkgnd(pDC);
      }
   }

   template<class MFC>
   afx_msg void TWCWnd<MFC>::OnUpdateUI(CCmdUI* pCmdUI)
   {
      cwCmdUI cmd(ccwCmd(WM_COMMAND, CN_UPDATE_COMMAND_UI, (long)pCmdUI));
      if ( !ccwWindow::onCommandUI(_srv, cmd) )
         pCmdUI->ContinueRouting();
   }

   // ECL specific commands

   template<class MFC>
   afx_msg LRESULT TWCWnd<MFC>::OnEclRefresh(WPARAM /*wParam*/, LPARAM /*lParam*/)
   {
      ccwWindow::onRefresh(_srv);
      return 0;
   }

   template<class MFC>
   afx_msg LRESULT TWCWnd<MFC>::OnEclStore(WPARAM /*wParam*/, LPARAM lParam)
   {
      if ( !ccwWindow::onStore(_srv) )
         *((bool*)lParam) = false;
      return 0;
   }

   template<class MFC>
   afx_msg LRESULT TWCWnd<MFC>::OnEclDiscard(WPARAM /*wParam*/, LPARAM lParam)
   {
      if ( !ccwWindow::onDiscard(_srv) )
         *((bool*)lParam) = false;
      return 0;
   }

   template<class MFC>
   afx_msg LRESULT TWCWnd<MFC>::OnEclAllowTurn(WPARAM /*wParam*/, LPARAM lParam)
   {
      if ( !ccwWindow::onAllowTurn(_srv) )
         *((bool*)lParam) = false;
      return 0;
   }

   template<class MFC>
   afx_msg LRESULT TWCWnd<MFC>::OnEclAllowStore(WPARAM /*wParam*/, LPARAM lParam)
   {
      if ( !ccwWindow::onAllowStore(_srv) )
         *((bool*)lParam) = false;
      return 0;
   }

   template<class MFC>
   afx_msg LRESULT TWCWnd<MFC>::OnEclAllowDiscard(WPARAM /*wParam*/, LPARAM lParam)
   {
      if ( !ccwWindow::onAllowDiscard(_srv) )
         *((bool*)lParam) = false;
      return 0;
   }

   template<class MFC>
   afx_msg LRESULT TWCWnd<MFC>::OnEclAllowClose(WPARAM /*wParam*/, LPARAM lParam)
   {
      if ( !ccwWindow::onAllowClose(_srv, 0 /* TBD: ....... */) )
         *((bool*)lParam) = false;
      return 0;
   }

   template<class MFC>
   afx_msg LRESULT TWCWnd<MFC>::OnEclExecDelayed(WPARAM wParam, LPARAM lParam)
   {
      ccwWindow::onExecDelayed(_srv, (int)wParam, (void*)lParam);
      return 0;
   }

   template<class MFC>
   afx_msg LRESULT TWCWnd<MFC>::OnEclDragEnter(WPARAM /*wParam*/, LPARAM lParam)
   {
      return ccwWindow::onDragEnter(_srv, *((cwCmdDrag*)lParam));
   }

   template<class MFC>
   afx_msg LRESULT TWCWnd<MFC>::OnEclDragOver(WPARAM /*wParam*/, LPARAM lParam)
   {
      return ccwWindow::onDragOver(_srv, *((cwCmdDrag*)lParam));
   }

   template<class MFC>
   afx_msg LRESULT TWCWnd<MFC>::OnEclDragScroll(WPARAM /*wParam*/, LPARAM lParam)
   {
      return ccwWindow::onDragScroll(_srv, *((cwCmdDrag*)lParam));
   }

   template<class MFC>
   afx_msg LRESULT TWCWnd<MFC>::OnEclDragLeave(WPARAM /*wParam*/, LPARAM /*lParam*/)
   {
      return ccwWindow::onDragLeave(_srv);
   }

   template<class MFC>
   afx_msg LRESULT TWCWnd<MFC>::OnEclDrop(WPARAM /*wParam*/, LPARAM lParam)
   {
      return ccwWindow::onDrop(_srv, *((cwCmdDrop*)lParam));
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCHistoryCtrl<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCHistoryCtrl<MFC>
//
// ===========================================================================

template<class MFC>
class TWCHistoryCtrl : public TWCWnd<MFC> {
   friend class cwLogWin;
public:
   TWCHistoryCtrl(cwLogWin *srv);
   virtual ~TWCHistoryCtrl();
protected:
   cwLogWin *_srv;
};

   template<class MFC>
   TWCHistoryCtrl<MFC>::TWCHistoryCtrl(cwLogWin *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCHistoryCtrl<MFC>::~TWCHistoryCtrl()
   {
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCFrameWnd<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCFrameWnd<MFC>
//
// ===========================================================================

template<class MFC>
class TWCFrameWnd : public TWCWnd<MFC> {
   friend class cwFrame;
public:
   TWCFrameWnd(cwFrame *srv);
   virtual ~TWCFrameWnd();
   afx_msg BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
protected:
   cwFrame *_srv;
};

   template<class MFC>
   TWCFrameWnd<MFC>::TWCFrameWnd(cwFrame *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCFrameWnd<MFC>::~TWCFrameWnd()
   {
   }

   template<class MFC>
   BOOL TWCFrameWnd<MFC>::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
   {
      if ( !ccwFrame::onCreateViews(_srv, pContext) )
         return MFC::OnCreateClient(lpcs, pContext);
      return TRUE;
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCToolBarCtrl<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCToolBarCtrl<MFC>
//
// ===========================================================================

template<class MFC>
class TWCToolBarCtrl : public TWCWnd<MFC> {
   friend class cwToolWin;
public:
   TWCToolBarCtrl(cwToolWin *srv);
   virtual ~TWCToolBarCtrl();
protected:
   cwToolWin *_srv;
   // Window procedure override
	BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
};

   template<class MFC>
   TWCToolBarCtrl<MFC>::TWCToolBarCtrl(cwToolWin *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCToolBarCtrl<MFC>::~TWCToolBarCtrl()
   {
   }

   // Window procedure override

   template<class MFC>
   BOOL TWCToolBarCtrl<MFC>::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
   {
      switch ( message ) {
      case WM_NOTIFY:
         switch ( ((NMHDR*)lParam)->code ) {
         case TBN_DROPDOWN:
            return ccwToolWin::onDropDown(_srv, (void*)lParam);
         }
         break;
      }
	   return MFC::OnChildNotify(message, wParam, lParam, pLResult);
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCControlBar<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCControlBar<MFC>
//
// ===========================================================================

template<class MFC>
class TWCControlBar : public TWCWnd<MFC> {
   friend class cwMiniFrame;
public:
   TWCControlBar(cwMiniFrame *srv);
   virtual ~TWCControlBar();
protected:
   void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
   cwMiniFrame *_srv;
};

   template<class MFC>
   TWCControlBar<MFC>::TWCControlBar(cwMiniFrame *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCControlBar<MFC>::~TWCControlBar()
   {
   }

   template<class MFC>
   void TWCControlBar<MFC>::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int /*flags*/)
   {
      ccwMiniFrame::onSizedOrDocked(_srv, cx, cy, !!bFloating, !!IsProbablyFloating());
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCDialogBar<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCDialogBar<MFC>
//
// ===========================================================================

template<class MFC>
class TWCDialogBar : public TWCWnd<MFC> {
   friend class cwDialogBar;
public:
   TWCDialogBar(cwDialogBar *srv);
   virtual ~TWCDialogBar();
protected:
   cwDialogBar *_srv;
};

   template<class MFC>
   TWCDialogBar<MFC>::TWCDialogBar(cwDialogBar *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCDialogBar<MFC>::~TWCDialogBar()
   {
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCDialogBar2<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCDialogBar2<MFC>
//
// ===========================================================================

template<class MFC>
class TWCDialogBar2 : public TWCWnd<MFC> {
   friend class cwMiniFrame;
public:
   TWCDialogBar2(cwMiniFrame *srv);
   virtual ~TWCDialogBar2();
protected:
   void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
   cwMiniFrame *_srv;
};

   template<class MFC>
   TWCDialogBar2<MFC>::TWCDialogBar2(cwMiniFrame *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCDialogBar2<MFC>::~TWCDialogBar2()
   {
   }

   template<class MFC>
   void TWCDialogBar2<MFC>::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int /*flags*/)
   {
      ccwMiniFrame::onSizedOrDocked(_srv, cx, cy, !!bFloating, !!IsProbablyFloating());
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCToolBar<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCToolBar<MFC>
//
// ===========================================================================

template<class MFC>
class TWCToolBar : public TWCWnd<MFC> {
   friend class cwToolBar;
public:
   TWCToolBar(cwToolBar *srv);
   virtual ~TWCToolBar();
protected:
   cwToolBar *_srv;
};

   template<class MFC>
   TWCToolBar<MFC>::TWCToolBar(cwToolBar *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCToolBar<MFC>::~TWCToolBar()
   {
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCStatusBar<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCStatusBar<MFC>
//
// ===========================================================================

template<class MFC>
class TWCStatusBar : public TWCWnd<MFC> {
   friend class cwStatusBar;
public:
   TWCStatusBar(cwStatusBar *srv);
   virtual ~TWCStatusBar();
protected:
   cwStatusBar *_srv;
};

   template<class MFC>
   TWCStatusBar<MFC>::TWCStatusBar(cwStatusBar *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCStatusBar<MFC>::~TWCStatusBar()
   {
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCView<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCView<MFC>
//
// ===========================================================================

template<class MFC>
class TWCView : public TWCWnd<MFC> {
   friend class cwView;
public:
   TWCView(cwView *srv);
   virtual ~TWCView();
protected:
   cwView *_srv;
   BOOL PreCreateWindow(CREATESTRUCT& cs);
   void OnInitialUpdate();
   afx_msg void OnDraw(CDC* pDC);
};

   template<class MFC>
   TWCView<MFC>::TWCView(cwView *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCView<MFC>::~TWCView()
   {
   }

   template<class MFC>
   BOOL TWCView<MFC>::PreCreateWindow(CREATESTRUCT& cs)
   {
      if ( ccwView::srv_beeing_created != 0 ) {
         TWCView<MFC>::_srv = ccwView::srv_beeing_created;
         TWCWnd<MFC>::_srv = (cwWindow*)ccwView::srv_beeing_created;
         ccwView::__setWnd(ccwView::srv_beeing_created, this);
      }
      return MFC::PreCreateWindow(cs);
   }

   template<class MFC>
   void TWCView<MFC>::OnInitialUpdate()
   {
      if ( _srv != 0 )
         ccwView::onInit(_srv);
      MFC::OnInitialUpdate();
   }

   template<class MFC>
   void TWCView<MFC>::OnDraw(CDC* pDC)
   {
      ccwView::onDraw(_srv, pDC);
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCDialog<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCDialog<MFC>
//
// ===========================================================================

template<class MFC>
class TWCDialog : public TWCWnd<MFC> {
   friend class cwDialog;
public:
   TWCDialog(cwDialog *srv);
   TWCDialog(cwDialog *srv, UINT id, CWnd *parent);
   virtual ~TWCDialog();
   COXLayoutManager lm;
protected:
   cwDialog *_srv;
   afx_msg BOOL OnInitDialog();
   afx_msg void OnOK();
   afx_msg void OnCancel();
   void PostNcDestroy();
};

   template<class MFC>
   TWCDialog<MFC>::TWCDialog(cwDialog *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCDialog<MFC>::TWCDialog(cwDialog *srv, UINT id, CWnd *parent) :
      TWCWnd<MFC>((cwWindow*)srv, id, parent)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCDialog<MFC>::~TWCDialog()
   {
      // Wird doch schon in Basisklasse aufgerufen?!?
      //ccwWindow::__disconnect((cwWindow*)_srv);
   }

   template<class MFC>
   afx_msg BOOL TWCDialog<MFC>::OnInitDialog()
   {
      return (BOOL)ccwDialog::onInit(_srv);
   }

   template<class MFC>
   afx_msg void TWCDialog<MFC>::OnOK()
   {
      ccwDialog::onOk(_srv);
   }

   template<class MFC>
   afx_msg void TWCDialog<MFC>::OnCancel()
   {
      ccwDialog::onCancel(_srv);
   }

   template<class MFC>
   void TWCDialog<MFC>::PostNcDestroy()
   {
      if ( ccwDialog::isAutoDelete(_srv) ) {
         CWnd::PostNcDestroy();
         delete this;
      } else {
         MFC::PostNcDestroy();
      }
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCPropertyPage<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCDialog<MFC>
//          +--TWCPropertyPage<MFC>
//
// ===========================================================================

template<class MFC>
class TWCPropertyPage : public TWCDialog<MFC> {
   friend class cwNotebookPage;
public:
   TWCPropertyPage(cwNotebookPage *srv);
   virtual ~TWCPropertyPage();
protected:
   cwNotebookPage *_srv;
   afx_msg void OnOK();
   afx_msg void OnCancel();
   afx_msg BOOL OnApply();
   afx_msg BOOL OnSetActive();
   afx_msg BOOL OnKillActive();
};

   template<class MFC>
   TWCPropertyPage<MFC>::TWCPropertyPage(cwNotebookPage *srv) :
      TWCDialog<MFC>((cwDialog*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCPropertyPage<MFC>::~TWCPropertyPage()
   {
   }

   template<class MFC>
   afx_msg void TWCPropertyPage<MFC>::OnOK()
   {
      ccwNotebookPage::onOk(_srv);
   }

   template<class MFC>
   afx_msg void TWCPropertyPage<MFC>::OnCancel()
   {
      ccwNotebookPage::onCancel(_srv);
   }

   template<class MFC>
   afx_msg BOOL TWCPropertyPage<MFC>::OnApply()
   {
      return (BOOL)ccwNotebookPage::onApply(_srv);
   }

   template<class MFC>
   afx_msg BOOL TWCPropertyPage<MFC>::OnSetActive()
   {
      return (BOOL)ccwNotebookPage::onEnter(_srv);
   }

   template<class MFC>
   afx_msg BOOL TWCPropertyPage<MFC>::OnKillActive()
   {
      return (BOOL)ccwNotebookPage::onLeave(_srv);
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCPropertySheet<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCPropertySheet<MFC>
//
// ===========================================================================

template<class MFC>
class TWCPropertySheet : public TWCWnd<MFC> {
   friend class cwNotebookDlg;
public:
   TWCPropertySheet(cwNotebookDlg *srv);
   virtual ~TWCPropertySheet();
protected:
   cwNotebookDlg *_srv;
	afx_msg BOOL OnInitDialog();
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
   void PostNcDestroy();
private:
   void EnableDefButton(UINT id);
};

   template<class MFC>
   TWCPropertySheet<MFC>::TWCPropertySheet(cwNotebookDlg *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCPropertySheet<MFC>::~TWCPropertySheet()
   {
      // Wird doch schon in Basisklasse aufgerufen?!?
      // ccwWindow::__disconnect((cwWindow*)_srv);
   }

   template<class MFC>
	afx_msg BOOL TWCPropertySheet<MFC>::OnInitDialog()
   {
      BOOL rc = (BOOL)ccwNotebookDlg::onInit(_srv);
      if ( ccwNotebookDlg::hasAnyButtons(_srv) ) {
         rc = MFC::OnInitDialog() || rc;
         if ( ccwNotebookDlg::hasButton(_srv, IDOK) ) EnableDefButton(IDOK);
         if ( ccwNotebookDlg::hasButton(_srv, IDCANCEL) ) EnableDefButton(IDCANCEL);
         if ( ccwNotebookDlg::hasButton(_srv, ID_APPLY_NOW) ) EnableDefButton(ID_APPLY_NOW);
         if ( ccwNotebookDlg::hasButton(_srv, IDHELP) ) EnableDefButton(IDHELP);
      } else {
         rc = MFC::OnInitDialog() || rc;
      }
      return rc;
   }

   template<class MFC>
   void TWCPropertySheet<MFC>::EnableDefButton(UINT id)
   {
      HWND hWnd = ::GetDlgItem(m_hWnd, id);
      if ( hWnd != NULL ) {
         ::ShowWindow(hWnd, SW_SHOW);
         ::EnableWindow(hWnd, id != ID_APPLY_NOW);
      }
   }

   template<class MFC>
   LRESULT TWCPropertySheet<MFC>::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
   {
      RECT rect;
      int cur_cx, cur_cy;
      int new_cx, new_cy;

      switch ( message ) {
      case WM_SIZE:
         GetWindowRect(&rect);
         cur_cx = rect.right - rect.left;
         cur_cy = rect.bottom - rect.top;
         new_cx = LOWORD(lParam);
         new_cy = HIWORD(lParam);
         break;
      }

      return MFC::WindowProc(message, wParam, lParam);
   }

   template<class MFC>
   void TWCPropertySheet<MFC>::PostNcDestroy()
   {
      if ( ccwNotebookDlg::isAutoDelete(_srv) ) {
         CWnd::PostNcDestroy();
         delete this;
      } else {
         MFC::PostNcDestroy();
      }
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCButton<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCButton<MFC>
//
// ===========================================================================

template<class MFC>
class TWCButton : public TWCWnd<MFC> {
   friend class cwButtonCtl;
public:
   TWCButton(cwButtonCtl *srv);
   virtual ~TWCButton();
protected:
   cwButtonCtl *_srv;
   // Window procedure override
	BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
};

   template<class MFC>
   TWCButton<MFC>::TWCButton(cwButtonCtl *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCButton<MFC>::~TWCButton()
   {
   }

   // Window procedure override

   template<class MFC>
   BOOL TWCButton<MFC>::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
   {
      switch ( message ) {
      case WM_COMMAND:
         switch ( HIWORD(wParam) ) {
         case BN_CLICKED:
            ccwButtonCtl::onClick(_srv);
            return TRUE;
         #ifdef BN_DBLCLICK
         case BN_DBLCLICK:
         #endif
         case BN_DOUBLECLICKED:
            ccwButtonCtl::onDblClick(_srv);
            return TRUE;
         }
         break;
      }

	   return MFC::OnChildNotify(message, wParam, lParam, pLResult);
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCStatic<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCStatic<MFC>
//
// ===========================================================================

template<class MFC>
class TWCStatic : public TWCWnd<MFC> {
   friend class cwStaticCtl;
public:
   TWCStatic(cwStaticCtl *srv);
   virtual ~TWCStatic();
protected:
   cwStaticCtl *_srv;
};

   template<class MFC>
   TWCStatic<MFC>::TWCStatic(cwStaticCtl *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCStatic<MFC>::~TWCStatic()
   {
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCTabCtrl<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCTabCtrl<MFC>
//
// ===========================================================================

template<class MFC>
class TWCTabCtrl : public TWCWnd<MFC> {
   friend class cwNotebookCtl;
public:
   TWCTabCtrl(cwNotebookCtl *srv);
   virtual ~TWCTabCtrl();
protected:
   cwNotebookCtl *_srv;
   // Window procedure override
	BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
};

   template<class MFC>
   TWCTabCtrl<MFC>::TWCTabCtrl(cwNotebookCtl *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCTabCtrl<MFC>::~TWCTabCtrl()
   {
   }

   // Window procedure override

   template<class MFC>
   BOOL TWCTabCtrl<MFC>::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
   {
      switch ( message ) {
      case WM_NOTIFY:
         switch ( ((NMHDR*)lParam)->code ) {
         case TCN_SELCHANGING:
            if ( ccwNotebookCtl::onPageChanging(_srv) )
               return TRUE;
            break;
         case TCN_SELCHANGE:
            ccwNotebookCtl::onPageChanged(_srv);
            break;
         }
         break;
      }
	   return MFC::OnChildNotify(message, wParam, lParam, pLResult);
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCListCtrl<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCListCtrl<MFC>
//
// ===========================================================================

template<class MFC>
class TWCListCtrl : public TWCWnd<MFC> {
   friend class cwContainer;
public:
   TWCListCtrl(cwContainer *srv);
   virtual ~TWCListCtrl();
   cArray<cwListElem*,cwListElem*> elems;
   int last_column_clicked;
protected:
   cwContainer *_srv;
   // Window procedure override
	BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
};

   template<class MFC>
   TWCListCtrl<MFC>::TWCListCtrl(cwContainer *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
      last_column_clicked = -1;
   }

   template<class MFC>
   TWCListCtrl<MFC>::~TWCListCtrl()
   {
   }

   // Window procedure override

   template<class MFC>
   BOOL TWCListCtrl<MFC>::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
   {
      switch ( message ) {
      case WM_NOTIFY:
         switch ( ((NMHDR*)lParam)->code ) {
         case LVN_GETDISPINFO:
            ccwContainer::onGetDispInfo(_srv, (void*)lParam);
            break;
         case LVN_SETDISPINFO:
            ccwContainer::onSetDispInfo(_srv, (void*)lParam);
            break;
         case LVN_ITEMACTIVATE:
            ccwContainer::onItemActivated(_srv, (void*)lParam);
            break;
         case LVN_ITEMCHANGING:
            if ( ccwContainer::onItemChanging(_srv, (void*)lParam) )
               return TRUE;
            break;
         case LVN_ITEMCHANGED:
            ccwContainer::onItemChanged(_srv, (void*)lParam);
            break;
         case LVN_ODSTATECHANGED:
            ccwContainer::onItemStateChanged(_srv, (void*)lParam);
            break;
         case LVN_BEGINDRAG:
            ccwContainer::onBeginDrag(_srv, (void*)lParam, 1); // 1 = Left
            break;
         case LVN_BEGINRDRAG:
            ccwContainer::onBeginDrag(_srv, (void*)lParam, 2); // 2 = Right
            break;
         case LVN_BEGINLABELEDIT:
            *pLResult = !ccwContainer::onBeginEdit(_srv, (void*)lParam);
            return TRUE;
         case LVN_ENDLABELEDIT:
            *pLResult = ccwContainer::onEndEdit(_srv, (void*)lParam);
            return TRUE;
         case LVN_COLUMNCLICK:
            ccwContainer::onColumnClick(_srv, (void*)lParam);
            break;
         case NM_CLICK:
            ccwContainer::onClick(_srv, (void*)lParam);
            break;
         case NM_DBLCLK:
            ccwContainer::onDblClick(_srv, (void*)lParam);
            break;
         case NM_RETURN:
            ccwContainer::onReturn(_srv);
            break;
         case NM_CUSTOMDRAW:
            *pLResult = (LRESULT)ccwContainer::onDraw(_srv, (void*)lParam);
            return TRUE;
         }
         break;
      }
	   return MFC::OnChildNotify(message, wParam, lParam, pLResult);
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCTreeCtrl<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCTreeCtrl<MFC>
//
// ===========================================================================

template<class MFC>
class TWCTreeCtrl : public TWCWnd<MFC> {
   friend class cwTree;
public:
   TWCTreeCtrl(cwTree *srv);
   virtual ~TWCTreeCtrl();
protected:
   cwTree *_srv;
   // Window procedure override
	BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
};

   template<class MFC>
   TWCTreeCtrl<MFC>::TWCTreeCtrl(cwTree *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCTreeCtrl<MFC>::~TWCTreeCtrl()
   {
   }

   // Window procedure override

   template<class MFC>
   BOOL TWCTreeCtrl<MFC>::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
   {
      switch ( message ) {
      case WM_NOTIFY:
         switch ( ((NMHDR*)lParam)->code ) {
         case TVN_GETDISPINFO:
            ccwTree::onGetDispInfo(_srv, (void*)lParam);
            break;
         case TVN_SETDISPINFO:
            ccwTree::onSetDispInfo(_srv, (void*)lParam);
            break;
         case TVN_SELCHANGING:
            if ( ccwTree::onSelChanging(_srv, (void*)lParam) )
               return TRUE;
            break;
         case TVN_SELCHANGED:
            ccwTree::onSelChanged(_srv, (void*)lParam);
            return TRUE;
         case TVN_ITEMEXPANDING:
            if ( ccwTree::onItemExpanding(_srv, (void*)lParam) )
               return TRUE;
            break;
         case TVN_ITEMEXPANDED:
            ccwTree::onItemExpanded(_srv, (void*)lParam);
            break;
         case TVN_BEGINDRAG:
            ccwTree::onBeginDrag(_srv, (void*)lParam, 1); // 1 = Left
            break;
         case TVN_BEGINRDRAG:
            ccwTree::onBeginDrag(_srv, (void*)lParam, 2); // 2 = Right
            break;
         case TVN_BEGINLABELEDIT:
            return !ccwTree::onBeginEdit(_srv, (void*)lParam);
         case TVN_ENDLABELEDIT:
            return ccwTree::onEndEdit(_srv, (void*)lParam);
         case NM_CLICK:
            if ( ccwTree::onClick(_srv, 1, GetMessagePos()) )
               return TRUE;
            break;
         case NM_RCLICK:
            if ( ccwTree::onClick(_srv, 2, GetMessagePos()) )
               return TRUE;
            break;
         case NM_DBLCLK:
            if ( ccwTree::onDblClick(_srv, 1, GetMessagePos()) )
               return TRUE;
            break;
         case NM_RDBLCLK:
            if ( ccwTree::onDblClick(_srv, 2, GetMessagePos()) )
               return TRUE;
            break;
         case NM_RETURN:
            if ( ccwTree::onDblClick(_srv, 0, GetMessagePos()) )
               return TRUE;
            break;
         }
         break;
      }
	   return MFC::OnChildNotify(message, wParam, lParam, pLResult);
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCGridCtrl<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCGridCtrl<MFC>
//
// ===========================================================================

template<class MFC>
class TWCGridCtrl : public TWCWnd<MFC> {
   friend class cwGrid;
public:
   TWCGridCtrl(cwGrid *srv);
   virtual ~TWCGridCtrl();
   cArray<cwListElem*,cwListElem*> elems;
protected:
   cwGrid *_srv;
   // Window procedure override
	BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
   // Grid procedure override
   int OnCanSizeCol(int col);
   int OnCanSizeRow(long row);
   int OnCanSizeSideHdg();
   int OnCanSizeTopHdg();
   void OnColChange(int oldcol, int newcol);
   void OnRowChange(long oldrow, long newrow);
   void OnCellChange(int oldcol, int newcol, long oldrow, long newrow);
   void OnLClicked(int col, long row, int updn, RECT *rect, POINT *point, int processed);
   void OnRClicked(int col, long row, int updn, RECT *rect, POINT *point, int processed);
   void OnDClicked(int col, long row, RECT *rect, POINT *point, BOOL processed);
   void OnSH_LClicked(int col, long row, int updn, RECT *rect, POINT *point, BOOL processed);
   void OnSH_RClicked(int col, long row, int updn, RECT *rect, POINT *point, BOOL processed);
   void OnSH_DClicked(int col, long row, RECT *rect, POINT *point, BOOL processed);
   void OnTH_LClicked(int col, long row, int updn, RECT *rect, POINT *point, BOOL processed);
   void OnTH_RClicked(int col, long row, int updn, RECT *rect, POINT *point, BOOL processed);
   void OnTH_DClicked(int col, long row, RECT *rect, POINT *point, BOOL processed);
   void OnCB_LClicked(int updn, RECT *rect, POINT *point, BOOL processed);
   void OnCB_RClicked(int updn, RECT *rect, POINT *point, BOOL processed);
   void OnCB_DClicked(RECT *rect, POINT *point, BOOL processed);
   void OnGetCell(int col, long row, CUGCell *cell);
   void OnSetCell(int col, long row, CUGCell *cell);
   int OnCellTypeNotify(long ID, int col, long row, long msg, long param);
};

   template<class MFC>
   TWCGridCtrl<MFC>::TWCGridCtrl(cwGrid *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCGridCtrl<MFC>::~TWCGridCtrl()
   {
   }

   // Window procedure override

   template<class MFC>
   BOOL TWCGridCtrl<MFC>::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
   {
      /*
      switch ( message ) {
      case WM_NOTIFY:
         switch ( ((NMHDR*)lParam)->code ) {
         case NM_CLICK:
            ccwContainer::onClick(_srv, (void*)lParam);
            break;
         }
         break;
      }
      */
	   return MFC::OnChildNotify(message, wParam, lParam, pLResult);
   }

   // Window procedure override

   template<class MFC>
   int TWCGridCtrl<MFC>::OnCanSizeCol(int col)
   {
      return ccwGrid::onCanSizeColumn(_srv, col);
   }

   template<class MFC>
   int TWCGridCtrl<MFC>::OnCanSizeRow(long row)
   {
      return ccwGrid::onCanSizeRow(_srv, row);
   }

   template<class MFC>
   int TWCGridCtrl<MFC>::OnCanSizeSideHdg()
   {
      return ccwGrid::onCanSizeRowHead(_srv);
   }

   template<class MFC>
   int TWCGridCtrl<MFC>::OnCanSizeTopHdg()
   {
      return ccwGrid::onCanSizeColumnHead(_srv);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnColChange(int oldcol, int newcol)
   {
      ccwGrid::onChangedColumn(_srv, oldcol, newcol);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnRowChange(long oldrow, long newrow)
   {
      ccwGrid::onChangedRow(_srv, oldrow, newrow);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnCellChange(int oldcol, int newcol, long oldrow, long newrow)
   {
      ccwGrid::onChangedCell(_srv, oldcol, newcol, oldrow, newrow);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnLClicked(int col, long row, int updn, RECT *, POINT *point, int)
   {
      cwCmdMouse cmd = ccwCmd(updn ? WM_LBUTTONDOWN : WM_LBUTTONUP,
         updn ? MK_LBUTTON : 0, MAKELPARAM(point->x,point->y));
      ccwGrid::onClickCell(_srv, col, row, cmd);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnRClicked(int col, long row, int updn, RECT *, POINT *point, int)
   {
      cwCmdMouse cmd = ccwCmd(updn ? WM_RBUTTONDOWN : WM_RBUTTONUP,
         updn ? MK_RBUTTON : 0, MAKELPARAM(point->x,point->y));
      ccwGrid::onClickCell(_srv, col, row, cmd);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnDClicked(int col, long row, RECT *, POINT *point, BOOL)
   {
      cwCmdMouse cmd = ccwCmd(WM_LBUTTONDBLCLK,
         MK_LBUTTON, MAKELPARAM(point->x,point->y));
      ccwGrid::onClickCell(_srv, col, row, cmd);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnSH_LClicked(int col, long row, int updn, RECT *, POINT *point, BOOL)
   {
      cwCmdMouse cmd = ccwCmd(updn ? WM_LBUTTONDOWN : WM_LBUTTONUP,
         updn ? MK_LBUTTON : 0, MAKELPARAM(point->x,point->y));
      ccwGrid::onClickRowHead(_srv, col, row, cmd);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnSH_RClicked(int col, long row, int updn, RECT *, POINT *point, BOOL)
   {
      cwCmdMouse cmd = ccwCmd(updn ? WM_RBUTTONDOWN : WM_RBUTTONUP,
         updn ? MK_RBUTTON : 0, MAKELPARAM(point->x,point->y));
      ccwGrid::onClickRowHead(_srv, col, row, cmd);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnSH_DClicked(int col, long row, RECT *, POINT *point, BOOL)
   {
      cwCmdMouse cmd = ccwCmd(WM_LBUTTONDBLCLK,
         MK_LBUTTON, MAKELPARAM(point->x,point->y));
      ccwGrid::onClickRowHead(_srv, col, row, cmd);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnTH_LClicked(int col, long row, int updn, RECT *, POINT *point, BOOL)
   {
      cwCmdMouse cmd = ccwCmd(updn ? WM_LBUTTONDOWN : WM_LBUTTONUP,
         updn ? MK_LBUTTON : 0, MAKELPARAM(point->x,point->y));
      ccwGrid::onClickColumnHead(_srv, col, row, cmd);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnTH_RClicked(int col, long row, int updn, RECT *, POINT *point, BOOL)
   {
      cwCmdMouse cmd = ccwCmd(updn ? WM_RBUTTONDOWN : WM_RBUTTONUP,
         updn ? MK_RBUTTON : 0, MAKELPARAM(point->x,point->y));
      ccwGrid::onClickColumnHead(_srv, col, row, cmd);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnTH_DClicked(int col, long row, RECT *, POINT *point, BOOL)
   {
      cwCmdMouse cmd = ccwCmd(WM_LBUTTONDBLCLK,
         MK_LBUTTON, MAKELPARAM(point->x,point->y));
      ccwGrid::onClickColumnHead(_srv, col, row, cmd);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnCB_LClicked(int updn, RECT *, POINT *point, BOOL)
   {
      cwCmdMouse cmd = ccwCmd(updn ? WM_LBUTTONDOWN : WM_LBUTTONUP,
         updn ? MK_LBUTTON : 0, MAKELPARAM(point->x,point->y));
      ccwGrid::onClickCorner(_srv, cmd);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnCB_RClicked(int updn, RECT *, POINT *point, BOOL)
   {
      cwCmdMouse cmd = ccwCmd(updn ? WM_RBUTTONDOWN : WM_RBUTTONUP,
         updn ? MK_RBUTTON : 0, MAKELPARAM(point->x,point->y));
      ccwGrid::onClickCorner(_srv, cmd);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnCB_DClicked(RECT *, POINT *point, BOOL)
   {
      cwCmdMouse cmd = ccwCmd(WM_LBUTTONDBLCLK,
         MK_LBUTTON, MAKELPARAM(point->x,point->y));
      ccwGrid::onClickCorner(_srv, cmd);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnGetCell(int col, long row, CUGCell *cell)
   {
      ccwGrid::onGetCell(_srv, col, row, cell);
   }

   template<class MFC>
   void TWCGridCtrl<MFC>::OnSetCell(int col, long row, CUGCell *cell)
   {
      ccwGrid::onGetCell(_srv, col, row, cell);
   }

   template<class MFC>
   int TWCGridCtrl<MFC>::OnCellTypeNotify(long ID, int col, long row, long msg, long param)
   {
      return ccwGrid::onCellNotify(_srv, col, row, ID, msg, param);
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCListBox<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCListBox<MFC>
//
// ===========================================================================

template<class MFC>
class TWCListBox : public TWCWnd<MFC> {
   friend class cwListBox;
public:
   TWCListBox(cwListBox *srv);
   virtual ~TWCListBox();
protected:
   cwListBox *_srv;
   // Window procedure override
	BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
};

   template<class MFC>
   TWCListBox<MFC>::TWCListBox(cwListBox *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCListBox<MFC>::~TWCListBox()
   {
   }

   // Window procedure override

   template<class MFC>
   BOOL TWCListBox<MFC>::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
   {
      int idx;

      switch ( message ) {
      case WM_COMMAND:
         switch ( HIWORD(wParam) ) {
         case LBN_SELCHANGE:
            if ( (idx = GetCaretIndex()) >= 0 ) {
               ccwListCtl::onSelectionChanged((cwListCtl*)_srv, (cwListElem*)GetItemDataPtr(idx));
            } else {
               ccwListCtl::onSelectionChanged((cwListCtl*)_srv, 0);
            }
            break;
         case LBN_DBLCLK:
            if ( (idx = GetCaretIndex()) >= 0 ) {
               ccwListCtl::onListElemSelected((cwListCtl*)_srv, (cwListElem*)GetItemDataPtr(idx));
            } else {
               ccwListCtl::onListElemSelected((cwListCtl*)_srv, 0);
            }
            break;
         }
         break;
      }

	   return MFC::OnChildNotify(message, wParam, lParam, pLResult);
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCCheckListBox<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCListBox<MFC>
//          +--TWCCheckListBox<MFC>
//
// ===========================================================================

template<class MFC>
class TWCCheckListBox : public TWCListBox<MFC> {
   friend class cwSetBox;
public:
   TWCCheckListBox(cwSetBox *srv);
   virtual ~TWCCheckListBox();
protected:
   cwSetBox *_srv;
};

   template<class MFC>
   TWCCheckListBox<MFC>::TWCCheckListBox(cwSetBox *srv) :
      TWCListBox<MFC>((cwListBox*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCCheckListBox<MFC>::~TWCCheckListBox()
   {
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCComboBox<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCComboBox<MFC>
//
// ===========================================================================

template<class MFC>
class TWCComboBox : public TWCWnd<MFC> {
   friend class cwComboBox;
public:
   TWCComboBox(cwComboBox *srv);
   virtual ~TWCComboBox();
protected:
   cwComboBox *_srv;
   // Window procedure override
	BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
};

   template<class MFC>
   TWCComboBox<MFC>::TWCComboBox(cwComboBox *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCComboBox<MFC>::~TWCComboBox()
   {
   }

   // Window procedure override

   template<class MFC>
   BOOL TWCComboBox<MFC>::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
   {
      int idx;

      switch ( message ) {
      case WM_COMMAND:
         switch ( HIWORD(wParam) ) {
         case CBN_SELCHANGE:
            if ( (idx = GetCurSel()) >= 0 ) {
               ccwListCtl::onSelectionChanged((cwListCtl*)_srv, (cwListElem*)GetItemDataPtr(idx));
            } else {
               ccwListCtl::onSelectionChanged((cwListCtl*)_srv, 0);
            }
            break;
         case CBN_SELENDOK:
            if ( (idx = GetCurSel()) >= 0 ) {
               ccwListCtl::onListElemSelected((cwListCtl*)_srv, (cwListElem*)GetItemDataPtr(idx));
            } else {
               ccwListCtl::onListElemSelected((cwListCtl*)_srv, 0);
            }
            break;
         case CBN_DROPDOWN:
            ccwComboBox::onDropDown(_srv);
            break;
         case CBN_CLOSEUP:
            ccwComboBox::onCloseUp(_srv);
            break;
         }
         break;
      }

	   return MFC::OnChildNotify(message, wParam, lParam, pLResult);
   }

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// TWCEdit<MFC>
// ---------------------------------------------------------------------------
//
// MFC
//  +--TWCWnd<MFC>
//      +--TWCEdit<MFC>
//
// ===========================================================================

template<class MFC>
class TWCEdit : public TWCWnd<MFC> {
   friend class cwEditCtl;
public:
   TWCEdit(cwEditCtl *srv);
   virtual ~TWCEdit();
protected:
   cwEditCtl *_srv;
   // Window procedure override
	BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
};

   template<class MFC>
   TWCEdit<MFC>::TWCEdit(cwEditCtl *srv) :
      TWCWnd<MFC>((cwWindow*)srv)
   {
      _srv = srv;
   }

   template<class MFC>
   TWCEdit<MFC>::~TWCEdit()
   {
   }

   // Window procedure override

   template<class MFC>
   BOOL TWCEdit<MFC>::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
   {
      switch ( message ) {
      case WM_COMMAND:
         switch ( HIWORD(wParam) ) {
         case EN_UPDATE:   ccwEditCtl::onEditChanged(_srv); break;
         case EN_CHANGE:   ccwEditCtl::onEditUpdated(_srv); break;
         }
         break;
      }
	   return MFC::OnChildNotify(message, wParam, lParam, pLResult);
   }

#endif /*__INTERFACE__*/



