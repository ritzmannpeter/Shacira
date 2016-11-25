// GfxInComboStatic.cpp : implementation file
//

#include "../stdafx.h"
//-TE-#include "GfxList.h"


#include "GfxInComboStatic.h"
#include "GfxInCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGfxInComboStatic

CGfxInComboStatic::CGfxInComboStatic()
{
	pCombo = NULL;
	crColor = GetSysColor(COLOR_WINDOWTEXT);
}

CGfxInComboStatic::~CGfxInComboStatic()
{
}


BEGIN_MESSAGE_MAP(CGfxInComboStatic, CStatic)
	//{{AFX_MSG_MAP(CGfxInComboStatic)
	ON_WM_KILLFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGfxInComboStatic message handlers

void CGfxInComboStatic::OnKillFocus(CWnd* pNewWnd) 
{
	CStatic::OnKillFocus(pNewWnd);
	if (pNewWnd != GetParent() && !(GetParent()->IsChild(pNewWnd))) 
		GetParent()->DestroyWindow();
}

BOOL CGfxInComboStatic::OnEraseBkgnd(CDC* pDC) 
{
	CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(rc, GetSysColor(COLOR_WINDOW));
	return true;	
}

void CGfxInComboStatic::OnPaint() 
{
	CPaintDC dc(this);

	CFont * pf = GetFont();
	CFont  * of = dc.SelectObject(pf);
	CRect rc;
	GetClientRect(rc);
	dc.FillSolidRect(rc, GetSysColor(COLOR_WINDOW));
	int obk = dc.SetBkMode(TRANSPARENT);
	CString cs;
	GetWindowText(cs);
	dc.TextOut(0,0,cs);
	dc.SetBkMode(obk);
	dc.SelectObject(of);
}

BOOL CGfxInComboStatic::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_CHAR)
	{
		if (pMsg->wParam == VK_UP)   pCombo->SetCurSel(pCombo->iCurSel - 1);
		if (pMsg->wParam == VK_DOWN) pCombo->SetCurSel(pCombo->iCurSel + 1);
		if (((char) pMsg->wParam >= 'a' && (char) pMsg->wParam >= 'z') || 
			((char) pMsg->wParam >= 'A' && (char) pMsg->wParam >= 'Z') ||
			((char) pMsg->wParam >= '0' && (char) pMsg->wParam >= '9'))
		{
			CString cs = pCombo->FindFromCharPressed((char) pMsg->wParam);
			if (cs != "") SetWindowText(cs);
		}
				
		::TranslateMessage(pMsg);
		::DispatchMessage(pMsg);
		return TRUE;
	}
	
	return CStatic::PreTranslateMessage(pMsg);
}
