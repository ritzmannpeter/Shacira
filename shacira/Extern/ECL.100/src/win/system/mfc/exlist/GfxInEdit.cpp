// GfxInEdit.cpp : implementation file
//

#include "../stdafx.h"
//-TE-#include "GfxList.h"

#include "GfxInEdit.h"
#include "GfxInCombo.h"

#include "GfxListCtrl.h"

#include "GfxPopupMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGfxInEdit


CGfxInEdit::CGfxInEdit(int iItem, int iSubItem, CString sInitText, bool _bMouseSelect) : m_sInitText(sInitText)
{
	bMouseSelect = _bMouseSelect;
	m_iItem = iItem;
	m_iSubItem = iSubItem;
	m_bESC = FALSE;
}

CGfxInEdit::~CGfxInEdit()
{
}

//CEdit)
BEGIN_MESSAGE_MAP(CGfxInEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CGfxInEdit)
	ON_WM_CHAR()
	ON_WM_CREATE()
	ON_WM_KILLFOCUS()
	ON_WM_NCDESTROY()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGfxInEdit message handlers

void CGfxInEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == VK_ESCAPE || nChar == VK_RETURN || nChar == VK_TAB)
	{
		if (nChar == VK_ESCAPE) m_bESC = TRUE;
		if (nChar == VK_TAB)
		{
			SHORT sh = GetKeyState(VK_SHIFT);

			ProcessSelect();
			CWnd * pParent = GetParent();
			int ip[2] = { m_iItem, m_iSubItem };
			DestroyWindow();
			if (sh < 0) pParent->SendMessage(WM_USER_TAB, 1, (LPARAM) &ip);
			else pParent->SendMessage(WM_USER_TAB, 0, (LPARAM) &ip);
			return;
		}
		GetParent()->SetFocus();
		return;
	}

	CRichEditCtrl::OnChar(nChar, nRepCnt, nFlags);

	CString str;

	GetWindowText( str );
	CWindowDC dc(this);
	CFont *pFont = GetParent()->GetFont();
	CFont *pFontDC = dc.SelectObject(pFont);
	CSize size = dc.GetTextExtent(str);
	dc.SelectObject(pFontDC);
	size.cx += 5;

	CRect rect, parentrect;
	GetClientRect(&rect);
	GetParent()->GetClientRect(&parentrect);

	ClientToScreen(&rect);
	GetParent()->ScreenToClient(&rect);

	if (size.cx > rect.Width())
	{
		if (size.cx + rect.left > parentrect.right) rect.right = rect.left + size.cx;
		else rect.right = parentrect.right;
		MoveWindow(&rect);
	}
}

int CGfxInEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) == -1) return -1;
	CFont* font = GetParent()->GetFont();
	SetFont(font);

	SetWindowText(m_sInitText);
	SetFocus();

	SetSel(0, -1);

	if (bMouseSelect)
	{
		CPoint pt;
		GetCursorPos(&pt);
		ScreenToClient(&pt);
		PostMessage(WM_LBUTTONDOWN, 0, MAKELONG(pt.x, pt.y));
		PostMessage(WM_LBUTTONUP, 0, MAKELONG(pt.x, pt.y));
	}

	return 0;
}

void CGfxInEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CRichEditCtrl::OnKillFocus(pNewWnd);

	if (m_bESC)
	{
		DestroyWindow();
		return;
	}
	ProcessSelect();
	DestroyWindow();
}

void CGfxInEdit::OnNcDestroy() 
{
	CRichEditCtrl::OnNcDestroy();
//	delete this;
}

BOOL CGfxInEdit::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_LEFT)
		{
			long ls,le;
			GetSel(ls, le);
			if (ls == 0 && ls == le)
			{
				ProcessSelect();
				CWnd * pParent = GetParent();
				int ip[2] = { m_iItem, m_iSubItem };
				DestroyWindow();
				pParent->SendMessage(WM_USER_TAB, 2, (LPARAM) &ip);
				return TRUE;
			}
		}
		if (pMsg->wParam == VK_RIGHT)
		{
			long ls,le;
			GetSel(ls, le);
			CString cs;
			GetWindowText(cs);

			if (ls == cs.GetLength() && ls == le)
			{
				ProcessSelect();
				CWnd * pParent = GetParent();
				int ip[2] = { m_iItem, m_iSubItem };
				DestroyWindow();
				pParent->SendMessage(WM_USER_TAB, 3, (LPARAM) &ip);
				return TRUE;
			}
		}

		if (pMsg->wParam == VK_UP)
		{
			ProcessSelect();
			CWnd * pParent = GetParent();
			int ip[2] = { m_iItem, m_iSubItem };
			DestroyWindow();
			pParent->SendMessage(WM_USER_TAB, 4, (LPARAM) &ip);
			return TRUE;
		}
		if (pMsg->wParam == VK_DOWN)
		{
			ProcessSelect();
			CWnd * pParent = GetParent();
			int ip[2] = { m_iItem, m_iSubItem };
			DestroyWindow();
			pParent->SendMessage(WM_USER_TAB, 5, (LPARAM) &ip);
			return TRUE;
		}


		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_DELETE || pMsg->wParam == VK_ESCAPE || 
			pMsg->wParam == VK_RIGHT || pMsg->wParam == VK_LEFT || pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN || 
			pMsg->wParam == VK_TAB || GetKeyState(VK_CONTROL))
		{
			::TranslateMessage(pMsg);
			::DispatchMessage(pMsg);
			return TRUE;
		}
	}
	
	return CRichEditCtrl::PreTranslateMessage(pMsg);
}

void CGfxInEdit::ProcessSelect()
{
	CString str;
	GetWindowText(str);

	if (m_sInitText != str) 
	{
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

void CGfxInEdit::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CRichEditCtrl::OnLButtonDblClk(nFlags, point);

	NMHDR nh;
	nh.hwndFrom = GetParent()->GetSafeHwnd();
	nh.idFrom = GetParent()->GetDlgCtrlID();
	nh.code = NM_DBLCLK;

	CWnd * pWnd = ((CGfxListCtrl *)GetParent())->GetReciper();//GetParent();
	pWnd->SendMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM) &nh);
}

void CGfxInEdit::PostNcDestroy() 
{
	CRichEditCtrl::PostNcDestroy();
	delete this;	
}

void CGfxInEdit::OnRButtonDown(UINT nFlags, CPoint point) 
{
/*-TE-
	CGfxPopupMenu cMenu;
	cMenu.CreatePopupMenu();

	cMenu.AppendMenu(MF_STRING, ID_EDIT_UNDO, "&Annulla");
	cMenu.AppendMenu(MF_SEPARATOR);
	cMenu.AppendMenu(MF_STRING, ID_EDIT_CUT, "&Taglia");
	cMenu.AppendMenu(MF_STRING, ID_EDIT_COPY, "&Copia");
	cMenu.AppendMenu(MF_STRING, ID_EDIT_PASTE, "&Incolla");

	CPoint pt(GetMessagePos());

	cMenu.LoadToolBarResource(IDR_LISTMENUBMP);//IDR_MAINFRAME);
	cMenu.RemapMenu(&cMenu);
	cMenu.EnableMenuItems(&cMenu, this);

	cMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, pt.x, pt.y, this);

	cMenu.DestroyMenu();
*/

	CRichEditCtrl::OnRButtonDown(nFlags, point);
}

bool CGfxInEdit::UpdateCopy()
{
	long ns = 0, ne = 0;
	GetSel(ns, ne);
	return (ns != ne) ? true : false;
}

bool CGfxInEdit::UpdatePaste()
{
	return CanPaste() ? true : false;
}

bool CGfxInEdit::UpdateCut()
{
	long ns = 0, ne = 0;
	GetSel(ns, ne);
	return (ns != ne) ? true : false;
}

bool CGfxInEdit::UpdateUndo()
{
	return CanUndo() ? true : false;
}


void CGfxInEdit::OnEditCopy() 
{
	Copy();	
}

void CGfxInEdit::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(UpdateCopy());
}

void CGfxInEdit::OnEditCut() 
{
	Cut();	
}

void CGfxInEdit::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(UpdateCut());
}

void CGfxInEdit::OnEditPaste() 
{
	Paste();	
}

void CGfxInEdit::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(UpdatePaste());
}

void CGfxInEdit::OnEditUndo() 
{
	Undo();
}

void CGfxInEdit::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(UpdateUndo());
}
