// GfxInCombo.cpp : implementation file
//

#include "../stdafx.h"
//-TE-#include "GfxList.h"


#include "GfxInCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGfxInCombo

CGfxInCombo::CGfxInCombo(int iItem, int iSubItem, CString sInitText, CStringArray * pComboArray, bool _bEditable, bool _bMouseSelect)
{
	bMouseSelect = _bMouseSelect;
	pArray = pComboArray;
	m_iItem = iItem;
	m_iSubItem = iSubItem;
	m_bESC = FALSE;
	hArrow = LoadBitmap(NULL, MAKEINTRESOURCE(32738));
	ASSERT(hArrow);
	m_sInitText = sInitText;
	wndList.pCombo = this;
	wndEdit.pCombo = this;
	wndStatic.pCombo = this;
	iButtonDx = GetSystemMetrics(SM_CXHSCROLL);
//	pFont = NULL;
	hFontHandle = NULL;
	bEditable = _bEditable;
	m_bAutoComplete = true;
	iCurSel = -1;

	bProcessed = false;
	bLightBorder = true;

	crColor = GetSysColor(COLOR_WINDOWTEXT);
}

CGfxInCombo::~CGfxInCombo()
{
	if (pArray)
	{
		pArray->RemoveAll();
		delete pArray;
	}
}


BEGIN_MESSAGE_MAP(CGfxInCombo, CWnd)
	//{{AFX_MSG_MAP(CGfxInCombo)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_KILLFOCUS()
	ON_WM_NCDESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_SELENDOK, OnSelendOk)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGfxInCombo message handlers

int CGfxInCombo::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rc;
	GetClientRect(rc);
	CRect btrc(rc.left, rc.top, rc.right - iButtonDx, rc.bottom);

	CFont* font = hFontHandle ? CFont::FromHandle(hFontHandle) : GetFont();
	SetFont(font);

	if (bEditable)
	{
		wndEdit.bMouseSelect = bMouseSelect;
		wndEdit.Create(WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL, btrc, this, GetDlgCtrlID() + 1);
		wndEdit.SetFont(font);
		wndEdit.SetWindowText(m_sInitText);

				
		CHARFORMAT chf;
		chf.cbSize = sizeof(CHARFORMAT);
		chf.crTextColor = crColor;
		chf.dwMask = CFM_COLOR;

		CHARRANGE cr;
		wndEdit.GetSel(cr);

		wndEdit.SetSel(0,-1);
		wndEdit.SetDefaultCharFormat(chf);
		wndEdit.SetSelectionCharFormat(chf);

		wndEdit.SetSel(cr);
	}
	else
	{
		wndStatic.Create(m_sInitText, WS_VISIBLE|WS_CHILD, btrc, this, GetDlgCtrlID() + 1);
		wndStatic.SetFont(font);

		wndStatic.crColor = crColor;
	}
	iCurSel = FindStringExact(-1, m_sInitText);
	SetFocus();
	return 0;
}

void CGfxInCombo::OnPaint() 
{
	CPaintDC dc(this);

	CRect rc;
	GetClientRect(rc);
	CRect btrc(rc.right - iButtonDx, rc.top, rc.right, rc.bottom);
	DrawButton(&dc, wndList.GetSafeHwnd() && wndList.IsWindowVisible());
}

void CGfxInCombo::DrawButton(CDC * pDC, const bool bPressed)
{
	CRect rc;
	GetClientRect(rc);
	CRect btrc(rc.right - iButtonDx, rc.top, rc.right, rc.bottom);
	pDC->FillSolidRect(btrc, GetSysColor(COLOR_3DFACE));

	CBitmap * pBmp = CBitmap::FromHandle(hArrow);

	CDC dcImage;
	if (dcImage.CreateCompatibleDC(pDC))
	{ 
		BITMAP bm;
		pBmp->GetBitmap(&bm);

		int x = btrc.left + (btrc.Width() - bm.bmWidth) / 2;
		int y = btrc.top + (btrc.Height() - bm.bmHeight) / 2;
		CBitmap* pOldBitmap = dcImage.SelectObject(pBmp);
		pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
		dcImage.SelectObject(pOldBitmap);
	}

	if (bPressed) 
	{
		pDC->Draw3dRect(btrc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
		if (!bLightBorder)
		{
			btrc.InflateRect(-1,-1);
			pDC->Draw3dRect(btrc, RGB(0,0,0), GetSysColor(COLOR_3DFACE));
		}
	}
	else 
	{
		if (!bLightBorder)
		{
			pDC->Draw3dRect(btrc, GetSysColor(COLOR_3DFACE),RGB(0,0,0));
			btrc.InflateRect(-1,-1);
		}
		pDC->Draw3dRect(btrc, GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
	}

}

void CGfxInCombo::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	if (wndStatic.GetSafeHwnd()) wndStatic.SetWindowPos(0,0,0,cx - iButtonDx, cy, SWP_NOZORDER);
	if (wndEdit.GetSafeHwnd())   wndEdit.SetWindowPos(0,0,0,cx - iButtonDx, cy, SWP_NOZORDER);
}

bool CGfxInCombo::Create(DWORD dwFlag, CRect rc, CWnd * pParent, int id)
{
	return CWnd::Create(NULL, "", dwFlag|WS_CHILD, rc, pParent, id) ? true : false;
}

void CGfxInCombo::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);
	if (m_bESC)
	{
		//PostMessage(WM_CLOSE);
		DestroyWindow();
		return;
	}
	
	if (!IsChild(pNewWnd) && pNewWnd->GetSafeHwnd() != wndList.GetSafeHwnd()) 
	{
		ProcessSelect();
		DestroyWindow();
		//PostMessage(WM_CLOSE);
	}
}

void CGfxInCombo::OnNcDestroy() 
{
	CWnd::OnNcDestroy();
//	delete this;	
}

BOOL CGfxInCombo::OnEraseBkgnd(CDC* pDC) 
{
	CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(rc, GetSysColor(COLOR_WINDOW));
	return true;	
}

void CGfxInCombo::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rc, rc1;
	GetClientRect(rc);
	CFont* font = GetParent()->GetFont(); 
	{
		CClientDC dc(this);
		CFont * of = dc.SelectObject(font);
		CSize sz = dc.GetTextExtent("X");
		sz.cy += 3;
		dc.SelectObject(of);
		int icy = pArray ? sz.cy * (pArray->GetSize()+1) : 100;
		if (icy > 100) icy = 100;
		if (icy == 0) icy = 20;
		rc1.SetRect(rc.left, rc.bottom, rc.right, rc.bottom + icy);
	}

	rc.left = rc.right - iButtonDx;
	if (pArray && pArray->GetSize() > 0 && rc.PtInRect(point))
	{
		if (wndList.GetSafeHwnd()) wndList.PostMessage(WM_CLOSE);//wndList.DestroyWindow();
		else
		{
			ClientToScreen(rc1);
			GetParent()->ScreenToClient(rc1);

			wndList.Create(WS_BORDER|WS_VISIBLE|WS_CHILD|WS_VSCROLL|LBS_SORT, rc1, GetParent(), GetDlgCtrlID() + 2);
			if (pArray)
			{
				for (int t = 0; t < pArray->GetSize(); t++)
					wndList.AddString((*pArray)[t]);
			}
			int icy = wndList.GetItemHeight(0) * pArray->GetSize();
			wndList.SetWindowPos(&wndTopMost, 0,0,rc1.Width(),icy > 100 ? 100 : icy, SWP_NOMOVE);
			wndList.SetFont(font);

			CString str;

			if (bEditable) wndEdit.GetWindowText(str);
			else wndStatic.GetWindowText(str);

			wndList.SetCurSel(wndList.FindStringExact(-1, str));
			wndList.SetFocus();
		}
		InvalidateButton();
	}
	else
	{
		if (wndList.GetSafeHwnd()) wndList.DestroyWindow();
		InvalidateButton();
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CGfxInCombo::InvalidateButton()
{
	CRect rc;
	GetClientRect(rc);
	CRect btrc(rc.right - iButtonDx, rc.top, rc.right, rc.bottom);
	InvalidateRect(btrc);
}

BOOL CGfxInCombo::PreTranslateMessage(MSG* pMsg) 
{
	CWnd * pParent = GetParent();
	ASSERT(pParent);
	if (pMsg->message == WM_NCHITTEST)
	{
		int x = LOWORD(pMsg->lParam);
		int y = HIWORD(pMsg->lParam);
		CPoint pt(x,y);
		CWnd *pw = WindowFromPoint(pt);
		if (pw && !IsChild(pw) && pw->GetSafeHwnd() != wndList.GetSafeHwnd()) 
		{
			//PostMessage(WM_CLOSE);
			DestroyWindow();
			return TRUE;
		}
	}
	if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_CHAR)
	{
		if (pMsg->wParam == VK_UP)   SetCurSel(iCurSel - 1);
		if (pMsg->wParam == VK_DOWN) SetCurSel(iCurSel + 1);
		if (pMsg->wParam == VK_RETURN)
		{
			ProcessSelect();
			pParent->SetFocus();
			return TRUE;
		}
		if (pMsg->wParam == VK_ESCAPE)
		{
			m_bESC = TRUE;
			pParent->SetFocus();
			return TRUE;
		}
		if (pMsg->wParam == VK_TAB)
		{
			SHORT sh = GetKeyState(VK_SHIFT);
			if (sh < 0) PreviousTab();
			else NextTab();
			return TRUE;
		}

		if (pMsg->wParam == VK_LEFT)
		{
			LeftCell();
			return TRUE;
		}
		if (pMsg->wParam == VK_RIGHT)
		{
			RightCell();
			return TRUE;
		}


		if (!bEditable) 
		{
			if (((char) pMsg->wParam >= 'a' && (char) pMsg->wParam >= 'z') || ((char) pMsg->wParam >= 'A' && (char) pMsg->wParam >= 'Z') || ((char) pMsg->wParam >= '0' && (char) pMsg->wParam >= '9'))
			{
				CString cs = FindFromCharPressed((char) pMsg->wParam);
				if (cs != "") 
				{
					wndStatic.SetWindowText(cs);
					wndStatic.Invalidate();
				}
			}
		}

		::TranslateMessage(pMsg);
		::DispatchMessage(pMsg);
		return TRUE;
	}
	
	return CWnd::PreTranslateMessage(pMsg);
}

LRESULT CGfxInCombo::OnSelendOk(WPARAM wParam, LPARAM lParam)
{
	if (bEditable) wndEdit.SetWindowText((char *) lParam);
	else 
	{
		wndStatic.SetWindowText((char *) lParam);
		wndStatic.Invalidate();
	}
	if ((int) wParam >= 0) iCurSel = (int) wParam;

	return 1L;
}

void CGfxInCombo::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == VK_ESCAPE) 
	{
		m_bESC = TRUE;
		GetParent()->SetFocus();
		return;
	}
	
	CWnd::OnChar(nChar, nRepCnt, nFlags);
}

int CGfxInCombo::FindStringExact(const int iStart, const char * cText)
{
	if (pArray)
	{
		CString csText(cText);
		for (int t = 0; t < pArray->GetSize(); t++)
			if ((*pArray)[t] != "" && (*pArray)[t] == csText && t >= iStart) return t;
	}
	return -1;
}

CString CGfxInCombo::FindFromCharPressed(char c)
{
	CString cs;
	int iActSel = iCurSel;

	if (pArray)
	{
		int t;
		CString csText(c);

		for (t = iCurSel >= 0 ? iCurSel : 0; t < pArray->GetSize(); t++)
		{
			CString item = (*pArray)[t];
			if ((*pArray)[t] != "")
			{
				if (item.Left(1) == csText)
				{
					iCurSel = t;
					return item;
				}
			}
		}
		if (iCurSel > 0)
		{
			for (t = 0; t < iCurSel; t++)
			{
				CString item = (*pArray)[t];
				if ((*pArray)[t] != "")
				{
					if (item.Left(1) == csText)
					{
						iCurSel = t;
						return item;
					}
				}
			}
		}
	}
	return cs;
}

int CGfxInCombo::SetCurSel(const int iSel)
{
	if (iSel >= 0 && (pArray != NULL && iSel < pArray->GetSize()))
	{
		iCurSel = iSel;
		CString cs = (*pArray)[iCurSel];
		if (bEditable) wndEdit.SetWindowText(cs);
		else 
		{
			wndStatic.SetWindowText(cs);
			wndStatic.Invalidate();
		}
	}
	return -1;
}

void CGfxInCombo::ProcessSelect(const char * cForceText)
{
//	if (bProcessed) return;
//	bProcessed = true;
	if (!GetSafeHwnd() || !IsWindow(GetSafeHwnd())) return;
	CString str;

	if (cForceText) 
	{
		str = cForceText;
	}
	else
	{
		if (bEditable) 
		{
			if (wndEdit.GetSafeHwnd()) wndEdit.GetWindowText(str);
			else str = wndEdit.csLstText;
		}
		else wndStatic.GetWindowText(str);
	}

	if (m_sInitText != str) 
	{
		m_sInitText = str;
		LV_DISPINFO dispinfo;
		dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
		dispinfo.hdr.idFrom = GetDlgCtrlID();
		dispinfo.hdr.code = LVN_ENDLABELEDIT;

		dispinfo.item.mask = LVIF_TEXT;
		dispinfo.item.iItem = m_iItem;
		dispinfo.item.iSubItem = m_iSubItem;
		dispinfo.item.pszText = m_bESC ? NULL : LPTSTR((LPCTSTR)str);
		dispinfo.item.cchTextMax = str.GetLength();

		GetParent()->SendMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM)&dispinfo);
		
	}
}

int CGfxInCombo::FindString(int nStartAfter, CString find)
{
	if (pArray)
	{
		for (int t = nStartAfter >= 0 ? nStartAfter : 0; t < pArray->GetSize(); t++)
		{
			CString item = (*pArray)[t];
			if (item.GetLength() >= find.GetLength())
				if (item.Left(find.GetLength()).CompareNoCase(find) == 0) return t;
		}
	}
	return -1;
}

void CGfxInCombo::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	if (bEditable && wndEdit.GetSafeHwnd()) wndEdit.SetFocus();
}

void CGfxInCombo::LeftCell()
{
	CWnd * pParent = GetParent();
	int ip[2] = { m_iItem, m_iSubItem };
	ProcessSelect();
	//PostMessage(WM_CLOSE);
	DestroyWindow();
	pParent->SendMessage(WM_USER_TAB, 2, (LPARAM) &ip);
}

void CGfxInCombo::RightCell()
{
	CWnd * pParent = GetParent();
	int ip[2] = { m_iItem, m_iSubItem };
	ProcessSelect();
	DestroyWindow();
	//PostMessage(WM_CLOSE);
	pParent->SendMessage(WM_USER_TAB, 3, (LPARAM) &ip);
}

void CGfxInCombo::UpCell()
{

}

void CGfxInCombo::DownCell()
{

}

void CGfxInCombo::NextTab()
{
	CWnd * pParent = GetParent();
	int ip[2] = { m_iItem, m_iSubItem };
	ProcessSelect();
	DestroyWindow();
	//PostMessage(WM_CLOSE);
	pParent->SendMessage(WM_USER_TAB, 0, (LPARAM) &ip);
}

void CGfxInCombo::PreviousTab()
{
	CWnd * pParent = GetParent();
	int ip[2] = { m_iItem, m_iSubItem };
	ProcessSelect();
	DestroyWindow();
	//PostMessage(WM_CLOSE);
	pParent->SendMessage(WM_USER_TAB, 1, (LPARAM) &ip);
}

void CGfxInCombo::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDblClk(nFlags, point);
	NMHDR nh;
	nh.hwndFrom = GetParent()->GetSafeHwnd();
	nh.idFrom = GetParent()->GetDlgCtrlID();
	nh.code = NM_DBLCLK;
	GetParent()->GetParent()->PostMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM) &nh);
}

void CGfxInCombo::PostNcDestroy() 
{
	CWnd::PostNcDestroy();
	delete this;	
}
