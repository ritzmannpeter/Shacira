// ===========================================================================
// mfc.cpp                                       ECL (ET's tiny Class Library)
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
//         |   |
//         |   +--WCFrameWnd
//         |
//         +--TWCDialog<CDialog>
//         |   |
//         |   +--WCDialog
//         |
//         +--TWCButton<CButton>
//             |
//             +--WCButton
//
// ===========================================================================

#include "win/system/mfc/mfc.hpp"

#include "win/ew_windows.hpp"
#include "win/ew_controls.hpp"

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
   static char THIS_FILE[] = __FILE__;
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "win/system/mfc/stdafx.h"
#include "win/system/mfc/mfc_t.hpp"

// Ultimate Toolbox
#include "win/system/mfc/utool/OXDropEdit.h"
#include "win/system/mfc/utool/OXHistoryCtrl.h"
#include "win/system/mfc/utool/OXMultiComboBox.h"
#include "win/system/mfc/utool/OXFrameWndDock.h"
#include "win/system/mfc/utool/OXSizeDockBar.h"
//#include "win/system/mfc/utool/OXSizeDlgBar.h"
#include "win/system/mfc/utool/OXMenuBar.h"
#include "win/system/mfc/utool/OXTabView.h"
#include "win/system/mfc/utool/OXZoomVw.h"
#include "win/system/mfc/ugrid/mycug97.h"


// User Defined Messages
// ===========================================================================

#define WM_ECL_REFRESH           (WM_USER + 0x101)
#define WM_ECL_STORE             (WM_USER + 0x102)
#define WM_ECL_DISCARD           (WM_USER + 0x103)
#define WM_ECL_ALLOW_TURN        (WM_USER + 0x104)
#define WM_ECL_ALLOW_STORE       (WM_USER + 0x105)
#define WM_ECL_ALLOW_DISCARD     (WM_USER + 0x106)
#define WM_ECL_ALLOW_CLOSE       (WM_USER + 0x107)
#define WM_ECL_EXEC_DELAYED      (WM_USER + 0x108)
#define WM_ECL_DRAG_ENTER        (WM_USER + 0x110)
#define WM_ECL_DRAG_OVER         (WM_USER + 0x111)
#define WM_ECL_DRAG_SCROLL       (WM_USER + 0x112)
#define WM_ECL_DRAG_LEAVE        (WM_USER + 0x113)
#define WM_ECL_DROP              (WM_USER + 0x114)

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// WCWinApp
// ---------------------------------------------------------------------------
//
// CWinApp
//  +--TWCWinApp<CWinApp>
//      +--WCWinApp
//
// ===========================================================================

class WCWinApp : public TWCWinApp<CWinApp> {
public:
   WCWinApp(cwApplication *srv, LPCTSTR lpszAppName) : TWCWinApp<CWinApp>(srv, lpszAppName) { }
	DECLARE_MESSAGE_MAP()
};

#endif /*__INTERFACE__*/


// Implementierung WCWinApp
// ===========================================================================

BEGIN_MESSAGE_MAP(WCWinApp, CWinApp)
	//{{AFX_MSG_MAP(WCWinApp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCMenu
// ---------------------------------------------------------------------------
//
// CMenu
//  +--TWCMenu<CMenu>
//      +--WCMenu
//
// ===========================================================================

class WCMenu : public TWCMenu<CMenu> {
public:
   WCMenu(cwMenu *srv) : TWCMenu<CMenu>(srv) { }
};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// WCOleDataSource
// ---------------------------------------------------------------------------
//
// COleDataSource
//  +--TWCOleDataSource<COleDataSource>
//      +--WCOleDataSource
//
// ===========================================================================

class WCOleDataSource : public TWCOleDataSource<COleDataSource> {
public:
   WCOleDataSource(cwDragSource *srv) : TWCOleDataSource<COleDataSource>(srv) { }
};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// WCOleDropTarget
// ---------------------------------------------------------------------------
//
// COleDropTarget
//  +--TWCOleDropTarget<COleDropTarget>
//      +--WCOleDropTarget
//
// ===========================================================================

class WCOleDropTarget : public TWCOleDropTarget<COleDropTarget> {
public:
   WCOleDropTarget(cwDropTarget *srv) : TWCOleDropTarget<COleDropTarget>(srv) { }
};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// WCImageList
// ---------------------------------------------------------------------------
//
// CImageList
//  +--TWCImageList<CImageList>
//      +--WCImageList
//
// ===========================================================================

class WCImageList : public TWCImageList<CImageList> {
public:
   WCImageList(cwIconList *srv) : TWCImageList<CImageList>(srv) { }
};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// WCWnd
// ---------------------------------------------------------------------------
//
// CWnd
//  +--TWCWnd<CWnd>
//      +--WCWnd
//
// ===========================================================================

class WCWnd : public TWCWnd<CWnd> {
public:
   WCWnd(cwWindow *srv) : TWCWnd<CWnd>(srv) { }
};

#endif /*__INTERFACE__*/


// Implementierung WCWnd
// ===========================================================================

#define ON_WCWND_MSGS() \
	ON_WM_CREATE() \
   ON_WM_DESTROY() \
	ON_WM_SIZE() \
   ON_WM_SYSCOMMAND() \
   ON_WM_ERASEBKGND() \
   ON_WM_CTLCOLOR_REFLECT() \
   ON_UPDATE_COMMAND_UI_RANGE(0, 0xffff, OnUpdateUI) \
   ON_MESSAGE(WM_ECL_REFRESH, OnEclRefresh) \
   ON_MESSAGE(WM_ECL_STORE, OnEclStore) \
   ON_MESSAGE(WM_ECL_DISCARD, OnEclDiscard) \
   ON_MESSAGE(WM_ECL_ALLOW_TURN, OnEclAllowTurn) \
   ON_MESSAGE(WM_ECL_ALLOW_STORE, OnEclAllowStore) \
   ON_MESSAGE(WM_ECL_ALLOW_DISCARD, OnEclAllowDiscard) \
   ON_MESSAGE(WM_ECL_ALLOW_CLOSE, OnEclAllowClose) \
   ON_MESSAGE(WM_ECL_EXEC_DELAYED, OnEclExecDelayed) \
   ON_MESSAGE(WM_ECL_DRAG_ENTER, OnEclDragEnter) \
   ON_MESSAGE(WM_ECL_DRAG_OVER, OnEclDragOver) \
   ON_MESSAGE(WM_ECL_DRAG_SCROLL, OnEclDragScroll) \
   ON_MESSAGE(WM_ECL_DRAG_LEAVE, OnEclDragLeave) \
   ON_MESSAGE(WM_ECL_DROP, OnEclDrop)




#ifdef __INTERFACE__

// ===========================================================================
// WCHistoryCtrl
// ---------------------------------------------------------------------------
//
// COXHistoryCtrl
//  +--TWCHistoryCtrl<COXHistoryCtrl>
//      +--WCHistoryCtrl
//
// ===========================================================================

class WCHistoryCtrl : public TWCHistoryCtrl<COXHistoryCtrl> {
	DECLARE_DYNCREATE(WCHistoryCtrl)
public:
   WCHistoryCtrl() : TWCHistoryCtrl<COXHistoryCtrl>(0) { }
   WCHistoryCtrl(cwLogWin *srv) : TWCHistoryCtrl<COXHistoryCtrl>(srv) { }
   // Initialization
   //
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCView
// ===========================================================================

IMPLEMENT_DYNCREATE(WCHistoryCtrl, COXHistoryCtrl)

BEGIN_MESSAGE_MAP(WCHistoryCtrl, COXHistoryCtrl)
	//{{AFX_MSG_MAP(WCHistoryCtrl)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCView
// ---------------------------------------------------------------------------
//
// CView
//  +--TWCWnd<CView>
//      +--TWCView<CView>
//          +--WCView
//
// ===========================================================================

class WCView : public TWCView<CView> {
	DECLARE_DYNCREATE(WCView)
public:
   WCView() : TWCView<CView>(0) { }
   WCView(cwView *srv) : TWCView<CView>(srv) { }
   // Initialization
   //
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCView
// ===========================================================================

IMPLEMENT_DYNCREATE(WCView, CView)

BEGIN_MESSAGE_MAP(WCView, CView)
	//{{AFX_MSG_MAP(WCView)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCTabView
// ---------------------------------------------------------------------------
//
// CView
//  +--TWCWnd<CView>
//      +--TWCView<CView>
//          +--WCTabView
//
// ===========================================================================

class WCTabView : public TWCView< COXTabViewPage<CView> > {
	DECLARE_DYNCREATE(WCTabView)
public:
   WCTabView() : TWCView< COXTabViewPage<CView> >(0) { }
   WCTabView(cwView *srv) : TWCView< COXTabViewPage<CView> >(srv) { }
   void SetHasInternalScrollBars(BOOL value) { m_bHasInternalScrollBars = value; }
   void SetNeedsInternalRedrawing(BOOL value) { m_bNeedsInternalRedrawing = value; }
   // Initialization
   //
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCTabView
// ===========================================================================

IMPLEMENT_DYNCREATE(WCTabView, CView)

BEGIN_MESSAGE_MAP(WCTabView, CView)
	//{{AFX_MSG_MAP(WCTabView)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCZoomView
// ---------------------------------------------------------------------------
//
// CView
//  +--TWCWnd<CView>
//      +--TWCView<CView>
//          +--WCZoomView
//
// ===========================================================================

class WCZoomView : public TWCView<COXZoomView> {
	DECLARE_DYNCREATE(WCZoomView)
public:
   WCZoomView() : TWCView<COXZoomView>(0) { }
   WCZoomView(cwView *srv) : TWCView<COXZoomView>(srv) { }
   void LPtoDP(LPRECT lpRect);
   void DPtoLP(LPRECT lpRect);
   // Initialization
   //
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCZoomView
// ===========================================================================

IMPLEMENT_DYNCREATE(WCZoomView, COXZoomView)

BEGIN_MESSAGE_MAP(WCZoomView, COXZoomView)
	//{{AFX_MSG_MAP(WCZoomView)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void WCZoomView::LPtoDP(LPRECT lpRect)
{
   CClientDC dc(this);
   OnPrepareDC(&dc);
   dc.LPtoDP(lpRect);
}

void WCZoomView::DPtoLP(LPRECT lpRect)
{
   CClientDC dc(this);
   OnPrepareDC(&dc);
   dc.DPtoLP(lpRect);
}




#ifdef __INTERFACE__

// ===========================================================================
// WCTabZoomView
// ---------------------------------------------------------------------------
//
// CView
//  +--TWCWnd<CView>
//      +--TWCView<CView>
//          +--WCTabZoomView
//
// ===========================================================================

class WCTabZoomView : public TWCView< COXTabViewPage<COXZoomView> > {
	DECLARE_DYNCREATE(WCTabZoomView)
public:
   WCTabZoomView() : TWCView< COXTabViewPage<COXZoomView> >(0) { }
   WCTabZoomView(cwView *srv) : TWCView< COXTabViewPage<COXZoomView> >(srv) { }
   void LPtoDP(LPRECT lpRect);
   void DPtoLP(LPRECT lpRect);
   // Initialization
   //
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCTabZoomView
// ===========================================================================

IMPLEMENT_DYNCREATE(WCTabZoomView, COXZoomView)

BEGIN_MESSAGE_MAP(WCTabZoomView, COXZoomView)
	//{{AFX_MSG_MAP(WCTabZoomView)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void WCTabZoomView::LPtoDP(LPRECT lpRect)
{
   CClientDC dc(this);
   OnPrepareDC(&dc);
   dc.LPtoDP(lpRect);
}

void WCTabZoomView::DPtoLP(LPRECT lpRect)
{
   CClientDC dc(this);
   OnPrepareDC(&dc);
   dc.DPtoLP(lpRect);
}




#ifdef __INTERFACE__

// ===========================================================================
// WCFrameWnd
// ---------------------------------------------------------------------------
//
// CFrameWnd
//  +--TWCWnd<CFrameWnd>
//      +--TWCFrameWnd<CFrameWnd>
//          +--WCFrameWnd
//
// ===========================================================================

class WCFrameWnd : public TWCFrameWnd<CFrameWnd> {
	DECLARE_DYNCREATE(WCFrameWnd)
public:
   WCFrameWnd() : TWCFrameWnd<CFrameWnd>(0) { }
   WCFrameWnd(cwFrame *srv) : TWCFrameWnd<CFrameWnd>(srv) { }
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCFrameWnd
// ===========================================================================

IMPLEMENT_DYNCREATE(WCFrameWnd, CFrameWnd)

BEGIN_MESSAGE_MAP(WCFrameWnd, CFrameWnd)
	//{{AFX_MSG_MAP(WCFrameWnd)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCToolBarCtrl
// ---------------------------------------------------------------------------
//
// CToolBar
//  +--TWCWnd<CToolBar>
//      +--TWCToolBarCtrl<CToolBarCtrl>
//          +--WCToolBarCtrl
//
// ===========================================================================

class WCToolBarCtrl : public TWCToolBarCtrl<CToolBarCtrl> {
	DECLARE_DYNCREATE(WCToolBarCtrl)
public:
   WCToolBarCtrl();
   WCToolBarCtrl(cwToolWin *srv);
   ~WCToolBarCtrl();
   BOOL LoadToolBar(LPCTSTR lpszResourceName);
   BOOL LoadBitmap(LPCTSTR lpszResourceName);
   BOOL SetButtons(const UINT* lpIDArray, int nIDCount);
   void SetSizes(SIZE sizeButton, SIZE sizeImage);
   BOOL AddReplaceBitmap(HBITMAP hbmImageWell);
protected:
	HRSRC m_hRsrcImageWell; // handle to loaded resource for image well
	HINSTANCE m_hInstImageWell; // instance handle to load image well from
	HBITMAP m_hbmImageWell; // contains color mapped button images
	BOOL m_bDelayedButtonLayout; // used to manage when button layout should be done
	CSize m_sizeImage;  // current image size
	CSize m_sizeButton; // current button size
   void OnSysColorChange();
private:
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCToolBar
// ===========================================================================

IMPLEMENT_DYNCREATE(WCToolBarCtrl, CToolBarCtrl)

BEGIN_MESSAGE_MAP(WCToolBarCtrl, CToolBarCtrl)
	//{{AFX_MSG_MAP(WCToolBar)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

struct CToolBarData
{
	WORD wVersion;
	WORD wWidth;
	WORD wHeight;
	WORD wItemCount;
	//WORD aItems[wItemCount]

	WORD* items()
		{ return (WORD*)(this+1); }
};

WCToolBarCtrl::WCToolBarCtrl() :
   TWCToolBarCtrl<CToolBarCtrl>(0)
{
	m_hRsrcImageWell = NULL;
	m_hInstImageWell = NULL;
	m_hbmImageWell = NULL;
	m_bDelayedButtonLayout = TRUE;

	// default image sizes
	m_sizeImage.cx = 16;
	m_sizeImage.cy = 15;

	// default button sizes
	m_sizeButton.cx = 23;
	m_sizeButton.cy = 22;
}

WCToolBarCtrl::WCToolBarCtrl(cwToolWin *srv) :
   TWCToolBarCtrl<CToolBarCtrl>(srv)
{
	m_hRsrcImageWell = NULL;
	m_hInstImageWell = NULL;
	m_hbmImageWell = NULL;
	m_bDelayedButtonLayout = TRUE;

	// default image sizes
	m_sizeImage.cx = 16;
	m_sizeImage.cy = 15;

	// default button sizes
	m_sizeButton.cx = 23;
	m_sizeButton.cy = 22;
}

WCToolBarCtrl::~WCToolBarCtrl()
{
	AfxDeleteObject((HGDIOBJ*)&m_hbmImageWell);
}

BOOL WCToolBarCtrl::LoadToolBar(LPCTSTR lpszResourceName)
{
	ASSERT_VALID(this);
	ASSERT(lpszResourceName != NULL);

	// determine location of the bitmap in resource fork
	HINSTANCE hInst = AfxFindResourceHandle(lpszResourceName, RT_TOOLBAR);
	HRSRC hRsrc = ::FindResource(hInst, lpszResourceName, RT_TOOLBAR);
	if (hRsrc == NULL)
		return FALSE;

	HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
	if (hGlobal == NULL)
		return FALSE;

	CToolBarData* pData = (CToolBarData*)LockResource(hGlobal);
	if (pData == NULL)
		return FALSE;
	ASSERT(pData->wVersion == 1);

	UINT* pItems = new UINT[pData->wItemCount];
	for (int i = 0; i < pData->wItemCount; i++)
		pItems[i] = pData->items()[i];
	BOOL bResult = SetButtons(pItems, pData->wItemCount);
	delete[] pItems;

	if (bResult)
	{
		// set new sizes of the buttons
		CSize sizeImage(pData->wWidth, pData->wHeight);
		CSize sizeButton(pData->wWidth + 7, pData->wHeight + 7);
		SetSizes(sizeButton, sizeImage);

		// load bitmap now that sizes are known by the toolbar control
		bResult = LoadBitmap(lpszResourceName);
	}

	UnlockResource(hGlobal);
	FreeResource(hGlobal);

	return bResult;
}

BOOL WCToolBarCtrl::LoadBitmap(LPCTSTR lpszResourceName)
{
	ASSERT_VALID(this);
	ASSERT(lpszResourceName != NULL);

	// determine location of the bitmap in resource fork
	HINSTANCE hInstImageWell = AfxFindResourceHandle(lpszResourceName, RT_BITMAP);
	HRSRC hRsrcImageWell = ::FindResource(hInstImageWell, lpszResourceName, RT_BITMAP);
	if (hRsrcImageWell == NULL)
		return FALSE;

	// load the bitmap
	HBITMAP hbmImageWell;
	hbmImageWell = AfxLoadSysColorBitmap(hInstImageWell, hRsrcImageWell);

	// tell common control toolbar about the new bitmap
	if (!AddReplaceBitmap(hbmImageWell))
		return FALSE;

	// remember the resource handles so the bitmap can be recolored if necessary
	m_hInstImageWell = hInstImageWell;
	m_hRsrcImageWell = hRsrcImageWell;
	return TRUE;
}

BOOL WCToolBarCtrl::AddReplaceBitmap(HBITMAP hbmImageWell)
{
	// need complete bitmap size to determine number of images
	BITMAP bitmap;
	VERIFY(::GetObject(hbmImageWell, sizeof(BITMAP), &bitmap));

	// add the bitmap to the common control toolbar
	BOOL bResult;
	if (m_hbmImageWell == NULL)
	{
		TBADDBITMAP addBitmap;
		addBitmap.hInst = NULL; // makes TBADDBITMAP::nID behave a HBITMAP
		addBitmap.nID = (UINT)hbmImageWell;
		bResult =  DefWindowProc(TB_ADDBITMAP,
			bitmap.bmWidth / m_sizeImage.cx, (LPARAM)&addBitmap) == 0;
	}
	else
	{
		TBREPLACEBITMAP replaceBitmap;
		replaceBitmap.hInstOld = NULL;
		replaceBitmap.nIDOld = (UINT)m_hbmImageWell;
		replaceBitmap.hInstNew = NULL;
		replaceBitmap.nIDNew = (UINT)hbmImageWell;
		replaceBitmap.nButtons = bitmap.bmWidth / m_sizeImage.cx;
		bResult = (BOOL)DefWindowProc(TB_REPLACEBITMAP, 0,
			(LPARAM)&replaceBitmap);
	}
	// remove old bitmap, if present
	if (bResult)
	{
		AfxDeleteObject((HGDIOBJ*)&m_hbmImageWell);
		m_hbmImageWell = hbmImageWell;
	}

	return bResult;
}

BOOL WCToolBarCtrl::SetButtons(const UINT* lpIDArray, int nIDCount)
{
	ASSERT_VALID(this);
	ASSERT(nIDCount >= 1);  // must be at least one of them
	ASSERT(lpIDArray == NULL ||
		AfxIsValidAddress(lpIDArray, sizeof(UINT) * nIDCount, FALSE));

	// delete all existing buttons
	int nCount = (int)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
	while (nCount--)
		VERIFY(DefWindowProc(TB_DELETEBUTTON, 0, 0));

	TBBUTTON button; memset(&button, 0, sizeof(TBBUTTON));
	button.iString = -1;
	if (lpIDArray != NULL)
	{
		// add new buttons to the common control
		int iImage = 0;
		for (int i = 0; i < nIDCount; i++)
		{
			button.fsState = TBSTATE_ENABLED;
			if ((button.idCommand = *lpIDArray++) == 0)
			{
				// separator
				button.fsStyle = TBSTYLE_SEP;
				// width of separator includes 8 pixel overlap
				ASSERT(_afxComCtlVersion != -1);
				if ((GetStyle() & TBSTYLE_FLAT) || _afxComCtlVersion == VERSION_IE4)
					button.iBitmap = 6;
				else
					button.iBitmap = 8;
			}
			else
			{
				// a command button with image
				button.fsStyle = TBSTYLE_BUTTON;
				button.iBitmap = iImage++;
			}
			if (!DefWindowProc(TB_ADDBUTTONS, 1, (LPARAM)&button))
				return FALSE;
		}
	}
	else
	{
		// add 'blank' buttons
		button.fsState = TBSTATE_ENABLED;
		for (int i = 0; i < nIDCount; i++)
		{
			ASSERT(button.fsStyle == TBSTYLE_BUTTON);
			if (!DefWindowProc(TB_ADDBUTTONS, 1, (LPARAM)&button))
				return FALSE;
		}
	}
	//m_nCount = (int)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
	m_bDelayedButtonLayout = TRUE;

	return TRUE;
}

void WCToolBarCtrl::SetSizes(SIZE sizeButton, SIZE sizeImage)
{
	ASSERT_VALID(this);

	// sizes must be non-zero and positive
	ASSERT(sizeButton.cx > 0 && sizeButton.cy > 0);
	ASSERT(sizeImage.cx > 0 && sizeImage.cy > 0);

	// button must be big enough to hold image
	//   + 7 pixels on x
	//   + 6 pixels on y
	ASSERT(sizeButton.cx >= sizeImage.cx + 7);
	ASSERT(sizeButton.cy >= sizeImage.cy + 6);

	if (::IsWindow(m_hWnd))
	{
		// set the sizes via TB_SETBITMAPSIZE and TB_SETBUTTONSIZE
		VERIFY(SendMessage(TB_SETBITMAPSIZE, 0, MAKELONG(sizeImage.cx, sizeImage.cy)));
		VERIFY(SendMessage(TB_SETBUTTONSIZE, 0, MAKELONG(sizeButton.cx, sizeButton.cy)));

		Invalidate();   // just to be nice if called when toolbar is visible
	}
	else
	{
		// just set our internal values for later
		m_sizeButton = sizeButton;
		m_sizeImage = sizeImage;
	}
}

void WCToolBarCtrl::OnSysColorChange()
{
	// re-color bitmap for toolbar
	if (m_hInstImageWell != NULL && m_hbmImageWell != NULL)
	{
		HBITMAP hbmNew;
		hbmNew = AfxLoadSysColorBitmap(m_hInstImageWell, m_hRsrcImageWell);
		if (hbmNew != NULL)
			AddReplaceBitmap(hbmNew);
	}
}




#ifdef __INTERFACE__

// ===========================================================================
// WCControlBar
// ---------------------------------------------------------------------------
//
// CControlBar
//  +--TWCWnd<CControlBar>
//      +--TWCControlBar<CControlBar>
//          +--WCControlBar
//
// ===========================================================================

class WCControlBar : public TWCControlBar<COXSizeControlBar> {
	DECLARE_DYNCREATE(WCControlBar)
public:
   WCControlBar() : TWCControlBar<COXSizeControlBar>(0) { }
   WCControlBar(cwMiniFrame *srv) : TWCControlBar<COXSizeControlBar>(srv) { }
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCControlBar
// ===========================================================================

IMPLEMENT_DYNCREATE(WCControlBar, COXSizeControlBar)

BEGIN_MESSAGE_MAP(WCControlBar, COXSizeControlBar)
	//{{AFX_MSG_MAP(WCControlBar)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCDialogBar
// ---------------------------------------------------------------------------
//
// CDialogBar
//  +--TWCWnd<CDialogBar>
//      +--TWCDialogBar<CDialogBar>
//          +--WCDialogBar
//
// ===========================================================================

class WCDialogBar : public TWCDialogBar<CDialogBar> {
	DECLARE_DYNCREATE(WCDialogBar)
public:
   WCDialogBar() : TWCDialogBar<CDialogBar>(0) { }
   WCDialogBar(cwDialogBar *srv) : TWCDialogBar<CDialogBar>(srv) { }
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCDialogBar
// ===========================================================================

IMPLEMENT_DYNCREATE(WCDialogBar, CDialogBar)

BEGIN_MESSAGE_MAP(WCDialogBar, CDialogBar)
	//{{AFX_MSG_MAP(WCDialogBar)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCDialogBar2
// ---------------------------------------------------------------------------
//
// CDialogBar2
//  +--TWCWnd<CDialogBar>
//      +--TWCDialogBar2<CDialogBar>
//          +--WCDialogBar2
//
// ===========================================================================

class WCDialogBar2 : public TWCDialogBar2<CDialogBar> {
	DECLARE_DYNCREATE(WCDialogBar2)
public:
   WCDialogBar2() : TWCDialogBar2<CDialogBar>(0) { }
   WCDialogBar2(cwMiniFrame *srv) : TWCDialogBar2<CDialogBar>(srv) { }
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCDialogBar2
// ===========================================================================

IMPLEMENT_DYNCREATE(WCDialogBar2, CDialogBar)

BEGIN_MESSAGE_MAP(WCDialogBar2, CDialogBar)
	//{{AFX_MSG_MAP(WCDialogBar2)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCToolBar
// ---------------------------------------------------------------------------
//
// CToolBar
//  +--TWCWnd<CToolBar>
//      +--TWCToolBar<CToolBar>
//          +--WCToolBar
//
// ===========================================================================

class WCToolBar : public TWCToolBar<CToolBar> {
	DECLARE_DYNCREATE(WCToolBar)
public:
   WCToolBar() : TWCToolBar<CToolBar>(0) { }
   WCToolBar(cwToolBar *srv) : TWCToolBar<CToolBar>(srv) { }
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCToolBar
// ===========================================================================

IMPLEMENT_DYNCREATE(WCToolBar, CToolBar)

BEGIN_MESSAGE_MAP(WCToolBar, CToolBar)
	//{{AFX_MSG_MAP(WCToolBar)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCStatusBar
// ---------------------------------------------------------------------------
//
// CStatusBar
//  +--TWCWnd<CStatusBar>
//      +--TWCStatusBar<CStatusBar>
//          +--WCStatusBar
//
// ===========================================================================

class WCStatusBar : public TWCStatusBar<CStatusBar> {
	DECLARE_DYNCREATE(WCStatusBar)
public:
   WCStatusBar() : TWCStatusBar<CStatusBar>(0) { }
   WCStatusBar(cwStatusBar *srv) : TWCStatusBar<CStatusBar>(srv) { }
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCStatusBar
// ===========================================================================

IMPLEMENT_DYNCREATE(WCStatusBar, CStatusBar)

BEGIN_MESSAGE_MAP(WCStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(WCStatusBar)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCMDIFrameWnd
// ---------------------------------------------------------------------------
//
// CMDIFrameWnd
//  +--TWCWnd<CMDIFrameWnd>
//      +--TWCFrameWnd<CMDIFrameWnd>
//          +--WCMDIFrameWnd
//
// ===========================================================================

class WCMDIFrameWnd : public TWCFrameWnd<CMDIFrameWnd> {
	DECLARE_DYNCREATE(WCMDIFrameWnd)
public:
   WCMDIFrameWnd() : TWCFrameWnd<CMDIFrameWnd>(0) { }
   WCMDIFrameWnd(cwFrame *srv) : TWCFrameWnd<CMDIFrameWnd>(srv) { }
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCMDIFrameWnd
// ===========================================================================

IMPLEMENT_DYNCREATE(WCMDIFrameWnd, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(WCMDIFrameWnd, CMDIFrameWnd)
	//{{AFX_MSG_MAP(WCMDIFrameWnd)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int WCMDIFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if ( TWCFrameWnd<CMDIFrameWnd>::OnCreate(lpCreateStruct) == -1 )
      return -1;
	return 0;
}




#ifdef __INTERFACE__

// ===========================================================================
// WCMDIChildWnd
// ---------------------------------------------------------------------------
//
// CMDIChildWnd
//  +--TWCWnd<CMDIChildWnd>
//      +--TWCFrameWnd<CMDIChildWnd>
//          +--WCMDIChildWnd
//
// ===========================================================================

class WCMDIChildWnd : public TWCFrameWnd<CMDIChildWnd> {
	DECLARE_DYNCREATE(WCMDIChildWnd)
public:
   WCMDIChildWnd() : TWCFrameWnd<CMDIChildWnd>(0) { }
   WCMDIChildWnd(cwFrame *srv) : TWCFrameWnd<CMDIChildWnd>(srv) { }
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCMDIChildWnd
// ===========================================================================

IMPLEMENT_DYNCREATE(WCMDIChildWnd, CMDIChildWnd)

BEGIN_MESSAGE_MAP(WCMDIChildWnd, CMDIChildWnd)
	//{{AFX_MSG_MAP(WCMDIChildWnd)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int WCMDIChildWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if ( TWCFrameWnd<CMDIChildWnd>::OnCreate(lpCreateStruct) == -1 )
      return -1;
	return 0;
}




#ifdef __INTERFACE__

// ===========================================================================
// WCFrameDockWnd
// ---------------------------------------------------------------------------
//
// CFrameDockWnd
//  +--TWCWnd<CFrameDockWnd>
//      +--TWCFrameWnd<CFrameDockWnd>
//          +--WCFrameWnd
//
// ===========================================================================

#ifdef __Use_COXMenuBar__
typedef COXMenuBarFrame<COXFrameWndSizeDock,COXSizeDockBar> CFrameDockWnd;
#else
typedef COXFrameWndSizeDock CFrameDockWnd;
#endif

class WCFrameDockWnd : public TWCFrameWnd<CFrameDockWnd> {
	DECLARE_DYNAMIC(WCFrameDockWnd)
public:
   WCFrameDockWnd() : TWCFrameWnd<CFrameDockWnd>(0) { }
   WCFrameDockWnd(cwFrame *srv) : TWCFrameWnd<CFrameDockWnd>(srv) { }
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCFrameDockWnd
// ===========================================================================

IMPLEMENT_DYNAMIC(WCFrameDockWnd, COXFrameWndSizeDock)

BEGIN_MESSAGE_MAP(WCFrameDockWnd, COXFrameWndSizeDock)
	//{{AFX_MSG_MAP(WCFrameWnd)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int WCFrameDockWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if ( TWCFrameWnd<CFrameDockWnd>::OnCreate(lpCreateStruct) == -1 )
      return -1;

	EnableDocking(CBRS_ALIGN_ANY);

	return 0;
}




#ifdef __INTERFACE__

// ===========================================================================
// WCMDIFrameDockWnd
// ---------------------------------------------------------------------------
//
// CMDIFrameDockWnd
//  +--TWCWnd<CMDIFrameDockWnd>
//      +--TWCFrameWnd<CMDIFrameDockWnd>
//          +--WCMDIFrameDockWnd
//
// ===========================================================================

#ifdef __Use_COXMenuBar__
typedef COXMenuBarFrame<COXMDIFrameWndSizeDock,COXSizeDockBar> CMDIFrameDockWnd;
#else
typedef COXMDIFrameWndSizeDock CMDIFrameDockWnd;
#endif

class WCMDIFrameDockWnd : public TWCFrameWnd<CMDIFrameDockWnd> {
	DECLARE_DYNAMIC(WCMDIFrameDockWnd)
public:
   WCMDIFrameDockWnd() : TWCFrameWnd<CMDIFrameDockWnd>(0) { }
   WCMDIFrameDockWnd(cwFrame *srv) : TWCFrameWnd<CMDIFrameDockWnd>(srv) { }
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCFrameMDIDockWnd
// ===========================================================================

IMPLEMENT_DYNAMIC(WCMDIFrameDockWnd, COXMDIFrameWndSizeDock)

BEGIN_MESSAGE_MAP(WCMDIFrameDockWnd, COXMDIFrameWndSizeDock)
	//{{AFX_MSG_MAP(WCFrameWnd)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int WCMDIFrameDockWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if ( TWCFrameWnd<CMDIFrameDockWnd>::OnCreate(lpCreateStruct) == -1 )
      return -1;

	EnableDocking(CBRS_ALIGN_ANY);

	return 0;
}




#ifdef __INTERFACE__

// ===========================================================================
// WCMDIChildDockWnd
// ---------------------------------------------------------------------------
//
// CMDIChildDockWnd
//  +--TWCWnd<CMDIChildDockWnd>
//      +--TWCFrameWnd<CMDIChildDockWnd>
//          +--WCMDIChildDockWnd
//
// ===========================================================================

typedef COXMDIChildWndSizeDock CMDIChildDockWnd;

class WCMDIChildDockWnd : public TWCFrameWnd<CMDIChildDockWnd> {
	DECLARE_DYNAMIC(WCMDIChildDockWnd)
public:
   WCMDIChildDockWnd() : TWCFrameWnd<CMDIChildDockWnd>(0) { }
   WCMDIChildDockWnd(cwFrame *srv) : TWCFrameWnd<CMDIChildDockWnd>(srv) { }
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCFrameMDIDockWnd
// ===========================================================================

IMPLEMENT_DYNAMIC(WCMDIChildDockWnd, COXMDIChildWndSizeDock)

BEGIN_MESSAGE_MAP(WCMDIChildDockWnd, COXMDIChildWndSizeDock)
	//{{AFX_MSG_MAP(WCFrameWnd)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int WCMDIChildDockWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if ( COXMDIChildWndSizeDock::OnCreate(lpCreateStruct) == -1 )
      return -1;

	EnableDocking(CBRS_ALIGN_ANY);

	return 0;
}




#ifdef __INTERFACE__

// ===========================================================================
// WCDialog
// ---------------------------------------------------------------------------
//
// CDialog
//  +--TWCWnd<CDialog>
//      +--TWCDialog<CDialog>
//          +--WCDialog
//
// ===========================================================================

class WCDialog : public TWCDialog<CDialog> {
   bool m_bModal;
public:
   WCDialog() : TWCDialog<CDialog>(0) { m_bModal = false; }
   WCDialog(cwDialog *srv) : TWCDialog<CDialog>(srv) { m_bModal = false; }
   WCDialog(cwDialog *srv, UINT id, CWnd *parent) : TWCDialog<CDialog>(srv, id, parent) { m_bModal = false; }
   // START ECL EXTENSIONS
	BOOL EclCreate(UINT nIDTemplate, CWnd* pParentWnd = NULL);
   void EclEndDialog(int nResult);
   HWND EclPreModal();
   void EclPostModal();
   int EclDoModal();
   // END ECL EXTENSIONS
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCDialog
// ===========================================================================

BEGIN_MESSAGE_MAP(WCDialog, CDialog)
	//{{AFX_MSG_MAP(WCDialog)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL WCDialog::EclCreate(UINT nIDTemplate, CWnd* pParentWnd)
{
   m_pParentWnd = pParentWnd;
   return Create(nIDTemplate, pParentWnd);
}

void WCDialog::EclEndDialog(int nResult)
{
   if ( m_bModal ) {
      EndDialog(nResult);
   } else {
      DestroyWindow();
   }
}

HWND WCDialog::EclPreModal()
{
   // -TE- code copied from CDialog::PreModal()

	// -TE- // cannot call DoModal on a dialog already constructed as modeless
	// -TE- ASSERT(m_hWnd == NULL);

	// allow OLE servers to disable themselves
	CWinApp* pApp = AfxGetApp();
	if (pApp != NULL)
		pApp->EnableModeless(FALSE);

	// find parent HWND
	HWND hWnd = CWnd::GetSafeOwner_(m_pParentWnd->GetSafeHwnd(), &m_hWndTop);

	// -TE- // hook for creation of dialog
	// -TE- AfxHookWindowCreate(this);

	// return window to use as parent for dialog
	return hWnd;
}

void WCDialog::EclPostModal()
{
   // -TE- code copied from CDialog::PostModal()

	// -TE- AfxUnhookWindowCreate();   // just in case
	// -TE- Detach();               // just in case

	// re-enable windows
	if (::IsWindow(m_hWndTop))
		::EnableWindow(m_hWndTop, TRUE);
	m_hWndTop = NULL;
	CWinApp* pApp = AfxGetApp();
	if (pApp != NULL)
		pApp->EnableModeless(TRUE);
}

int WCDialog::EclDoModal()
{
   // -TE- code copied partially from CDialog::DoModal()

   m_bModal = true;
	HWND hWndParent = EclPreModal();

	// -TE- AfxUnhookWindowCreate();
	BOOL bEnableParent = FALSE;
	if (hWndParent != NULL && ::IsWindowEnabled(hWndParent))
	{
		::EnableWindow(hWndParent, FALSE);
		bEnableParent = TRUE;
	}

   EnableWindow();

	TRY
	{
   	DWORD dwFlags = MLF_SHOWONIDLE;
   	if (GetStyle() & DS_NOIDLEMSG)
   		dwFlags |= MLF_NOIDLEMSG;
      VERIFY(RunModalLoop(dwFlags) == m_nModalResult);
	}
	CATCH_ALL(e)
	{
      cBase::DbgError("WCDialog::EclDoModal: Caught exception");
		// -TE- DELETE_EXCEPTION(e);
		m_nModalResult = -1;
	}
	END_CATCH_ALL


   if (bEnableParent)
      ::EnableWindow(hWndParent, TRUE);
   if (hWndParent != NULL && ::GetActiveWindow() == m_hWnd)
      ::SetActiveWindow(hWndParent);

   EclPostModal();
   m_bModal = false;

   return m_nModalResult;
}




#ifdef __INTERFACE__

// ===========================================================================
// WCPropertyPage
// ---------------------------------------------------------------------------
//
// CPropertyPage
//  +--TWCWnd<CPropertyPage>
//      +--TWCDialog<CPropertyPage>
//          +--TWCPropertyPage<CPropertyPage>
//              +--WCPropertyPage
//
// ===========================================================================

class WCPropertyPage : public TWCPropertyPage<CPropertyPage> {
   friend class cwNotebookPage;
public:
   WCPropertyPage();
   WCPropertyPage(cwNotebookPage *srv);
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCPropertyPage
// ===========================================================================

BEGIN_MESSAGE_MAP(WCPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(WCPropertyPage)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

WCPropertyPage::WCPropertyPage() :
   TWCPropertyPage<CPropertyPage>(0)
{
}

WCPropertyPage::WCPropertyPage(cwNotebookPage *srv) :
   TWCPropertyPage<CPropertyPage>(srv)
{
}




#ifdef __INTERFACE__

// ===========================================================================
// WCPropertySheet
// ---------------------------------------------------------------------------
//
// CPropertySheet
//  +--TWCWnd<CPropertySheet>
//      +--TWCPropertySheet<CPropertySheet>
//          +--WCPropertySheet
//
// ===========================================================================

class WCPropertySheet : public TWCPropertySheet<CPropertySheet> {
	DECLARE_DYNCREATE(WCPropertySheet)
   COXLayoutManager m_pLayoutManager;
	CRect m_rectPage;
public:
   WCPropertySheet(cwNotebookDlg *srv);
   ~WCPropertySheet();
protected:
	BOOL OnInitDialog();
	BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCPropertySheet
// ===========================================================================

#define OX_OFFSET 7

IMPLEMENT_DYNAMIC(WCPropertySheet, CPropertySheet)

BEGIN_MESSAGE_MAP(WCPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(WCPropertySheet)
   ON_WCWND_MSGS()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

WCPropertySheet::WCPropertySheet(cwNotebookDlg *srv) :
   TWCPropertySheet<CPropertySheet>(srv)
{
}

WCPropertySheet::~WCPropertySheet()
{
}

int WCPropertySheet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if ( TWCPropertySheet<CPropertySheet>::OnCreate(lpCreateStruct) == -1 )
		return -1;
	
	// Remove standard Restore, Maximize & Minimize items out of system menu.
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if ( pSysMenu != NULL ) {
		//pSysMenu->RemoveMenu(SC_RESTORE, MF_BYCOMMAND);
		//pSysMenu->RemoveMenu(SC_MINIMIZE, MF_BYCOMMAND);
		pSysMenu->RemoveMenu(SC_MAXIMIZE, MF_BYCOMMAND);
	}
	
	// Make the window resizable
	ModifyStyle(NULL, WS_THICKFRAME|WS_MINIMIZEBOX);

	return 0;
}

BOOL WCPropertySheet::OnInitDialog()
{
	TWCPropertySheet<CPropertySheet>::OnInitDialog();

   m_pLayoutManager.Attach(this);

   // Setup constraints on the OK and Cancel buttons.
   //
   m_pLayoutManager.SetConstraint(ID_APPLY_NOW, OX_LMS_BOTTOM, OX_LMT_SAME, -OX_OFFSET);
   m_pLayoutManager.SetConstraint(IDCANCEL, OX_LMS_BOTTOM, OX_LMT_SAME, -OX_OFFSET);
   m_pLayoutManager.SetConstraint(IDOK, OX_LMS_BOTTOM, OX_LMT_SAME, -OX_OFFSET);

   if ( ccwNotebookDlg::hasButton(_srv, ID_APPLY_NOW) ) {
      m_pLayoutManager.SetConstraint(ID_APPLY_NOW, OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET);
      m_pLayoutManager.SetConstraint(IDCANCEL, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -OX_OFFSET, ID_APPLY_NOW);
   } else {
      m_pLayoutManager.SetConstraint(IDCANCEL, OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET);
      // 18.04.2002 -TE- Damit der APPLY-Knopf auch wirklich verschwindet:
      ::ShowWindow(::GetDlgItem(m_hWnd, ID_APPLY_NOW), SW_HIDE);
   }

   m_pLayoutManager.SetConstraint(IDOK, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -OX_OFFSET, IDCANCEL);

   //
   // Setup constraint on the CTabControl: Size it on the Left, Right and Top with the Window,
   // and on the Bottom with the OK button.
   m_pLayoutManager.SetConstraint(GetTabControl()->GetDlgCtrlID(), OX_LMS_LEFT, OX_LMT_SAME, OX_OFFSET);
   m_pLayoutManager.SetConstraint(GetTabControl()->GetDlgCtrlID(), OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET);
   m_pLayoutManager.SetConstraint(GetTabControl()->GetDlgCtrlID(), OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -OX_OFFSET, IDOK);
   m_pLayoutManager.SetConstraint(GetTabControl()->GetDlgCtrlID(), OX_LMS_TOP, OX_LMT_SAME, OX_OFFSET);

   // Draw the layout with the new constraints
   // This is necessary when constraints are implemented and the window must be refreshed
   CRect rect;
   GetWindowRect(&rect);
   GetTabControl()->AdjustRect(FALSE,&rect);
   m_pLayoutManager.OnSize(rect.Width(), rect.Height());

   GetTabControl()->GetWindowRect(&m_rectPage);
   GetTabControl()->AdjustRect(FALSE,&m_rectPage);
   ScreenToClient(&m_rectPage);

   CPropertyPage* active_page = GetActivePage();
   if ( active_page != 0 )
      active_page->MoveWindow(&m_rectPage);

   m_pLayoutManager.RedrawLayout();

	return TRUE;
}

void WCPropertySheet::OnSize(UINT nType, int cx, int cy)
{
	CPropertySheet::OnSize(nType, cx, cy);
	
	if ( ::IsWindow(m_hWnd) && IsWindowVisible() ) {
		// When the parent window (The Property Sheet) is resized we need
		// to resize the size of the CTabCtrl that is contained within the
		// control.  The OK and Cancel buttons are resized by the Layout
		// Manager.

		m_pLayoutManager.OnSize(cx, cy);

		GetTabControl()->GetWindowRect(&m_rectPage);
		GetTabControl()->AdjustRect(FALSE, &m_rectPage);
		
		ScreenToClient(&m_rectPage);
		GetActivePage()->MoveWindow(&m_rectPage);
	}
}

BOOL WCPropertySheet::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bResult = CPropertySheet::OnNotify(wParam, lParam, pResult);
	
	if ( bResult ) {
		NMHDR* pnmh = (LPNMHDR) lParam;

		// the sheet resizes the page whenever it is activated
		// so we need to resize it to what we want
		if ( pnmh->code == TCN_SELCHANGE ) {
			// user-defined message needs to be posted because page must
			// be resized after TCN_SELCHANGE has been processed
			GetActivePage()->MoveWindow(&m_rectPage);
		}
	}

    return bResult;
}

BOOL WCPropertySheet::PreCreateWindow(CREATESTRUCT& cs)
{
	// cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS,NULL,NULL,
	// 	AfxGetApp()->LoadIcon(IDR_LAYOUTTYPE));
	// ASSERT(cs.lpszClass);

   cs.style |= DS_SETFONT | DS_FIXEDSYS;
	return CPropertySheet::PreCreateWindow(cs);
}




#ifdef __INTERFACE__

// ===========================================================================
// WCButton
// ---------------------------------------------------------------------------
//
// CButton
//  +--TWCWnd<CButton>
//      +--TWCButton<CButton>
//          +--WCButton
//
// ===========================================================================

class WCButton : public TWCButton<CButton> {
public:
   WCButton() : TWCButton<CButton>(0) { }
   WCButton(cwButtonCtl *srv) : TWCButton<CButton>(srv) { }
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCButton
// ===========================================================================

BEGIN_MESSAGE_MAP(WCButton, CButton)
	//{{AFX_MSG_MAP(WCButton)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCStatic
// ---------------------------------------------------------------------------
//
// CStatic
//  +--TWCWnd<CStatic>
//      +--TWCStatic<CStatic>
//          +--WCStatic
//
// ===========================================================================

class WCStatic : public TWCStatic<CStatic> {
public:
   WCStatic() : TWCStatic<CStatic>(0) { }
   WCStatic(cwStaticCtl *srv) : TWCStatic<CStatic>(srv) { }
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCStatic
// ===========================================================================

BEGIN_MESSAGE_MAP(WCStatic, CStatic)
	//{{AFX_MSG_MAP(WCStatic)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCTabCtrl
// ---------------------------------------------------------------------------
//
// CTabCtrl
//  +--TWCWnd<CTabCtrl>
//      +--TWCTabCtrl<CTabCtrl>
//          +--WCTabCtrl
//
// ===========================================================================

class WCTabCtrl : public TWCTabCtrl<CTabCtrl> {
public:
   WCTabCtrl() : TWCTabCtrl<CTabCtrl>(0) { }
   WCTabCtrl(cwNotebookCtl *srv) : TWCTabCtrl<CTabCtrl>(srv) { }
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCTabCtrl
// ===========================================================================

BEGIN_MESSAGE_MAP(WCTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(WCTabCtrl)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCListCtrl
// ---------------------------------------------------------------------------
//
// CListCtrl
//  +--TWCWnd<CListCtrl>
//      +--TWCListCtrl<CListCtrl>
//          +--WCListCtrl
//
// ===========================================================================

class WCListCtrl : public TWCListCtrl<CListCtrl> {
   CFont font_bold;
public:
   WCListCtrl() : TWCListCtrl<CListCtrl>(0) { init(); }
   WCListCtrl(cwContainer *srv) : TWCListCtrl<CListCtrl>(srv) { init(); }
   HFONT GetFontHandle() { return HFONT(font_bold); }
private:
   void init();
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCListCtrl
// ===========================================================================

BEGIN_MESSAGE_MAP(WCListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(WCListCtrl)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void WCListCtrl::init()
{
   LOGFONT lf;
   BOOL ok = SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof lf, &lf, 0);

   if ( ok ) {
      lf.lfWeight = FW_BOLD;
      font_bold.CreateFontIndirect(&lf);
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// WCTreeCtrl
// ---------------------------------------------------------------------------
//
// CTreeCtrl
//  +--TWCWnd<CTreeCtrl>
//      +--TWCTreeCtrl<CTreeCtrl>
//          +--WCTreeCtrl
//
// ===========================================================================

class WCTreeCtrl : public TWCTreeCtrl<CTreeCtrl> {
public:
   WCTreeCtrl() : TWCTreeCtrl<CTreeCtrl>(0) { }
   WCTreeCtrl(cwTree *srv) : TWCTreeCtrl<CTreeCtrl>(srv) { }
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCTreeCtrl
// ===========================================================================

BEGIN_MESSAGE_MAP(WCTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(WCTreeCtrl)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCGridCtrl
// ---------------------------------------------------------------------------
//
// CGridCtrl
//  +--TWCWnd<CGridCtrl>
//      +--TWCGridCtrl<CGridCtrl>
//          +--WCGridCtrl
//
// ===========================================================================

class WCGridCtrl : public TWCGridCtrl<MyCug> {
   int font_normal, font_bold;
public:
   WCGridCtrl();
   WCGridCtrl(cwGrid *srv);
   DECLARE_MESSAGE_MAP( )
   int getFontNormal() const { return font_normal; }
   int getFontBold() const { return font_bold; }
protected:
   void OnSetup();
};

#endif /*__INTERFACE__*/


// Implementierung WCGridCtrl
// ===========================================================================

BEGIN_MESSAGE_MAP(WCGridCtrl, MyCug)
	//{{AFX_MSG_MAP(WCGridCtrl)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

WCGridCtrl::WCGridCtrl() : TWCGridCtrl<MyCug>(0)
{
   font_normal = font_bold = 0;
}

WCGridCtrl::WCGridCtrl(cwGrid *srv) : TWCGridCtrl<MyCug>(srv)
{
   font_normal = font_bold = 0;
}

void WCGridCtrl::OnSetup()
{
   EnableJoins(TRUE);
   SetCurrentCellMode(1/*=UG_CELLMODE_FOCUS*/);

   LOGFONT lf;
   BOOL ok = SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof lf, &lf, 0);

   if ( ok ) {
      font_normal = AddFont(
         lf.lfHeight, lf.lfWidth,
         lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
         lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut,
         lf.lfCharSet, lf.lfOutPrecision, lf.lfClipPrecision,
         lf.lfQuality, lf.lfPitchAndFamily,
         lf.lfFaceName
      );
      font_bold = AddFont(
         lf.lfHeight, lf.lfWidth,
         lf.lfEscapement, lf.lfOrientation, FW_BOLD,
         lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut,
         lf.lfCharSet, lf.lfOutPrecision, lf.lfClipPrecision,
         lf.lfQuality, lf.lfPitchAndFamily,
         lf.lfFaceName
      );
      SetDefFont(font_normal);
      SetDefRowHeight(labs(lf.lfHeight)+8);
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// WCListBox
// ---------------------------------------------------------------------------
//
// CListBox
//  +--TWCWnd<CListBox>
//      +--TWCListBox<CListBox>
//          +--WCListBox
//
// ===========================================================================

class WCListBox : public TWCListBox<CListBox> {
public:
   WCListBox() : TWCListBox<CListBox>(0) { }
   WCListBox(cwListBox *srv) : TWCListBox<CListBox>(srv) { }
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCListBox
// ===========================================================================

BEGIN_MESSAGE_MAP(WCListBox, CListBox)
	//{{AFX_MSG_MAP(WCListBox)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCCheckListBox
// ---------------------------------------------------------------------------
//
// CCheckListBox
//  +--TWCWnd<CCheckListBox>
//      +--TWCListBox<CCheckListBox>
//          +--TWCCheckListBox<CCheckListBox>
//              +--WCCheckListBox
//
// ===========================================================================

class WCCheckListBox : public TWCCheckListBox<CCheckListBox> {
public:
   WCCheckListBox() : TWCCheckListBox<CCheckListBox>(0) { }
   WCCheckListBox(cwSetBox *srv) : TWCCheckListBox<CCheckListBox>(srv) { }
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCListBox
// ===========================================================================

BEGIN_MESSAGE_MAP(WCCheckListBox, CCheckListBox)
	//{{AFX_MSG_MAP(WCCheckListBox)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCComboBox
// ---------------------------------------------------------------------------
//
// CComboBox
//  +--TWCWnd<CComboBox>
//      +--TWCComboBox<CComboBox>
//          +--WCComboBox
//
// ===========================================================================

class WCComboBox : public TWCComboBox<CComboBox> {
public:
   WCComboBox() : TWCComboBox<CComboBox>(0) { }
   WCComboBox(cwComboBox *srv) : TWCComboBox<CComboBox>(srv) { }
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCComboBox
// ===========================================================================

BEGIN_MESSAGE_MAP(WCComboBox, CComboBox)
	//{{AFX_MSG_MAP(WCComboBox)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCMultiComboBox
// ---------------------------------------------------------------------------
//
// CComboBox
//  +--TWCWnd<COXMultiComboBox>
//      +--TWCComboBox<COXMultiComboBox>
//          +--WCMultiComboBox
//
// ===========================================================================

class WCMultiComboBox : public TWCComboBox<COXMultiComboBox> {
public:
   WCMultiComboBox() : TWCComboBox<COXMultiComboBox>(0) { }
   WCMultiComboBox(cwComboBox *srv) : TWCComboBox<COXMultiComboBox>(srv) { }
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCMultiComboBox
// ===========================================================================

BEGIN_MESSAGE_MAP(WCMultiComboBox, COXMultiComboBox)
	//{{AFX_MSG_MAP(WCComboBox)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCEdit
// ---------------------------------------------------------------------------
//
// CEdit
//  +--TWCWnd<CEdit>
//      +--TWCEdit<CEdit>
//          +--WCEdit
//
// ===========================================================================

typedef COXDropEdit<CEdit> CMyOXDropEdit;

class WCEdit : public TWCEdit<CMyOXDropEdit> {
public:
   WCEdit() : TWCEdit<CMyOXDropEdit>(0) { ShowButton(FALSE); }
   WCEdit(cwEditCtl *srv) : TWCEdit<CMyOXDropEdit>(srv) { ShowButton(FALSE); }
   void OnDropButton() { ccwEditCtl::onDetailRequest(_srv); }
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCEdit
// ===========================================================================

BEGIN_MESSAGE_MAP(WCEdit, CEdit)
	//{{AFX_MSG_MAP(WCEdit)
   ON_WCWND_MSGS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




#ifdef __INTERFACE__

// ===========================================================================
// WCMonthCalCtrl
// ---------------------------------------------------------------------------
//
// CMonthCalCtrl
//  +--WCMonthCalCtrl
//
// ===========================================================================

class WCMonthCalCtrl : public CMonthCalCtrl {
   cwControl *_srv;
public:
   WCMonthCalCtrl(cwControl *srv);
   ~WCMonthCalCtrl();
   int DoModal();
protected:
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
   DECLARE_MESSAGE_MAP( )
};

#endif /*__INTERFACE__*/


// Implementierung WCMonthCalCtrl
// ===========================================================================

BEGIN_MESSAGE_MAP(WCMonthCalCtrl, CMonthCalCtrl)
	//{{AFX_MSG_MAP(WCMonthCalCtrl)
	ON_WM_CHAR() \
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

WCMonthCalCtrl::WCMonthCalCtrl(cwControl *srv)
{
   _srv = srv;
   CWnd *entry = (CWnd*)ccwWindow::__getWnd(_srv);
   CWnd *parent = entry->GetParent();

   /*
   // Load the window class.
   INITCOMMONCONTROLSEX icex;
   icex.dwSize = sizeof icex;
   icex.dwICC  = ICC_DATE_CLASSES;
   ::InitCommonControlsEx(&icex);
   */

   CreateEx(0, MONTHCAL_CLASS, "",
            WS_BORDER | WS_POPUP | WS_VISIBLE | MCS_WEEKNUMBERS /* | MCS_MULTISELECT*/,
            0,0,0,0,
            parent->m_hWnd, NULL);
}

WCMonthCalCtrl::~WCMonthCalCtrl()
{
   DestroyWindow();
}

int WCMonthCalCtrl::DoModal()
{
   RECT rect, rect2;
   CWnd *entry = (CWnd*)ccwWindow::__getWnd(_srv);

   cDate date;
   if ( _srv->getStorageVal(date) ) {
      SYSTEMTIME st; memset(&st, 0, sizeof st);
      st.wYear = (unsigned short)date.getYear();
      st.wMonth = (unsigned short)date.getMonth();
      st.wDay = (unsigned short)date.getDay();
      SetCurSel(&st);
   }

   entry->GetWindowRect(&rect);
   GetMinReqRect(&rect2);
   SetWindowPos(NULL, rect.left, rect.bottom, rect2.right, rect2.bottom, 0);

   return RunModalLoop(0);
}

LRESULT WCMonthCalCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch ( message ) {
   case WM_KILLFOCUS:
      EndModalLoop(0);
      break;
   case WM_KEYDOWN:
      if ( wParam == VK_ESCAPE )
         EndModalLoop(0);
      break;
   case WM_CHAR:
      if ( wParam == 13 )
         EndModalLoop(1);
      break;
   }

   return CMonthCalCtrl::WindowProc(message, wParam, lParam);
}

BOOL WCMonthCalCtrl::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
   NMSELCHANGE *nms;

   switch ( message ) {
   case WM_NOTIFY:
      switch ( ((NMHDR*)lParam)->code ) {
      case MCN_SELECT:
         nms = (NMSELCHANGE*)lParam;
         _srv->putStorageVal(cDate(nms->stSelStart.wYear, nms->stSelStart.wMonth, nms->stSelStart.wDay));
         EndModalLoop(1);
         break;
      case MCN_SELCHANGE:
         nms = (NMSELCHANGE*)lParam;
         _srv->putStorageVal(cDate(nms->stSelStart.wYear, nms->stSelStart.wMonth, nms->stSelStart.wDay));
         break;
      }
      break;
   }

	return CMonthCalCtrl::OnChildNotify(message, wParam, lParam, pLResult);
}

