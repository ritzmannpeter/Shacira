// GfxListTip.cpp : implementation file
//

#include "../stdafx.h"
//-TE-#include "GfxList.h"

#include "GfxListTip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define GFXLISTTIP_CLASSNAME _T("ZGfxListTip")

/////////////////////////////////////////////////////////////////////////////
// CGfxListTip

CGfxListTip::CGfxListTip()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();
	if(!(::GetClassInfo(hInst, GFXLISTTIP_CLASSNAME, &wndcls)))
	{
		wndcls.style = CS_SAVEBITS ;
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
		wndcls.hInstance = hInst;
		wndcls.hIcon = NULL;
		wndcls.hCursor = LoadCursor(hInst, IDC_ARROW);
		wndcls.hbrBackground = (HBRUSH)(COLOR_INFOBK + 1); 
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = GFXLISTTIP_CLASSNAME;
		if (!AfxRegisterClass(&wndcls)) AfxThrowResourceException();
	}
}

CGfxListTip::~CGfxListTip()
{
}


BEGIN_MESSAGE_MAP(CGfxListTip, CWnd)
	//{{AFX_MSG_MAP(CGfxListTip)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGfxListTip message handlers

BOOL CGfxListTip::PreTranslateMessage(MSG* pMsg) 
{
	CWnd *pWnd;
	int hittest;
	switch(pMsg->message)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		POINTS pts = MAKEPOINTS(pMsg->lParam);
		POINT  point;
		point.x = pts.x;
		point.y = pts.y;
		ClientToScreen(&point);
		pWnd = WindowFromPoint(point);
		if( pWnd == this ) pWnd = m_pParentWnd;

		hittest = (int)pWnd->SendMessage(WM_NCHITTEST, 0,MAKELONG(point.x,point.y));
		if (hittest == HTCLIENT) 
		{
			pWnd->ScreenToClient(&point);
			pMsg->lParam = MAKELONG(point.x,point.y);
		} 
		else 
		{
			switch (pMsg->message) 
			{
			case WM_LBUTTONDOWN: 
				pMsg->message = WM_NCLBUTTONDOWN;
				break;
			case WM_RBUTTONDOWN: 
				pMsg->message = WM_NCRBUTTONDOWN;
				break;
			case WM_MBUTTONDOWN: 
				pMsg->message = WM_NCMBUTTONDOWN;
				break;
			}
			pMsg->wParam = hittest;
			pMsg->lParam = MAKELONG(point.x,point.y);
		}
		ReleaseCapture();
		ShowWindow(SW_HIDE);
		pWnd->PostMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
		return TRUE;		
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		ReleaseCapture();
		ShowWindow(SW_HIDE);
		m_pParentWnd->PostMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
		return TRUE;
	}

	if (GetFocus() == NULL)
	{
		ReleaseCapture();
		ShowWindow(SW_HIDE);
		return TRUE;
	}

	return CWnd::PreTranslateMessage(pMsg);
}

BOOL CGfxListTip::Create(CWnd * pParentWnd)
{
	ASSERT_VALID(pParentWnd);
	DWORD dwStyle = WS_BORDER | WS_POPUP; 
	DWORD dwExStyle = WS_EX_TOOLWINDOW | WS_EX_TOPMOST;
	m_pParentWnd = pParentWnd;
	return CreateEx(dwExStyle, GFXLISTTIP_CLASSNAME, NULL, dwStyle, 0, 0, 0, 0, NULL, NULL, NULL);
}


void CGfxListTip::Show(CRect rectTitle, LPCTSTR lpszTitleText, int xoffset)
{
	if (!::IsWindow( m_hWnd )) return;
	if (rectTitle.IsRectEmpty()) return;

	ASSERT(!rectTitle.IsRectEmpty());

	if (lpszTitleText == NULL || *lpszTitleText == 0) return;
	if (IsWindowVisible()) return;
	if (GetFocus() == NULL) return;
	m_rectTitle.top = -1;
	m_rectTitle.left = -xoffset-1;
	m_rectTitle.right = rectTitle.Width()-xoffset;
	m_rectTitle.bottom = rectTitle.Height()+1;
	m_pParentWnd->ClientToScreen( rectTitle );
	CClientDC dc(this);
	CString strTitle(lpszTitleText);
	CFont *pFont = m_pParentWnd->GetFont(); 	// use same font as ctrl
	CFont *pFontDC = dc.SelectObject( pFont );
	CRect rectDisplay = rectTitle;
	CSize size = dc.GetTextExtent( strTitle );
	rectDisplay.left += xoffset;
	rectDisplay.right = rectDisplay.left + size.cx + 3;
	if (rectDisplay.right <= rectTitle.right-xoffset) return;
	SetWindowPos(&wndTop, rectDisplay.left, rectDisplay.top, rectDisplay.Width(), rectDisplay.Height(), SWP_SHOWWINDOW|SWP_NOACTIVATE);
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(0, 0, strTitle);
	dc.SelectObject(pFontDC);
	SetCapture();
}

void CGfxListTip::OnMouseMove(UINT nFlags, CPoint point) 
{
	 if (!m_rectTitle.PtInRect(point)) 
	 {
		  ReleaseCapture();
		  ShowWindow( SW_HIDE );
		  ClientToScreen(&point);
		  CWnd *pWnd = WindowFromPoint(point);
		  if (pWnd == this) pWnd = m_pParentWnd;
		  int hittest = (int)pWnd->SendMessage(WM_NCHITTEST, 0,MAKELONG(point.x,point.y));
		  if (hittest == HTCLIENT) 
		  {
			   pWnd->ScreenToClient( &point );
			   pWnd->PostMessage(WM_MOUSEMOVE, nFlags, MAKELONG(point.x,point.y));
		  } 
		  else pWnd->PostMessage(WM_NCMOUSEMOVE, hittest, MAKELONG(point.x,point.y));
	 }
}

