// GfxInComboEdit.cpp : implementation file
//

#include "../stdafx.h"
//-TE-#include "GfxList.h"


#include "GfxInComboEdit.h"
#include "GfxInCombo.h"
#include "GfxPopupMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGfxInComboEdit

CGfxInComboEdit::CGfxInComboEdit()
{
	m_bESC = FALSE;
	pCombo = NULL;
	bNoNextChange = false;
	bMouseSelect = true;
}

CGfxInComboEdit::~CGfxInComboEdit()
{
}


BEGIN_MESSAGE_MAP(CGfxInComboEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CGfxInComboEdit)
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGfxInComboEdit message handlers

int CGfxInComboEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (bMouseSelect)
	{
		CPoint pt;
		GetCursorPos(&pt);
		ScreenToClient(&pt);

		PostMessage(WM_LBUTTONDOWN, 0, MAKELONG(pt.x, pt.y));
		PostMessage(WM_LBUTTONUP, 0, MAKELONG(pt.x, pt.y));
	}

	SetEventMask(ENM_CHANGE|ENM_KEYEVENTS);


	return 0;
}

BOOL CGfxInComboEdit::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_UP)   
		{
			pCombo->SetCurSel(pCombo->iCurSel - 1);
			return TRUE;
		}

		if (pMsg->wParam == VK_DOWN) 
		{
			pCombo->SetCurSel(pCombo->iCurSel + 1);
			return TRUE;
		}
		if (pMsg->wParam == VK_DELETE || pMsg->wParam == VK_BACK) bNoNextChange = true;

		::TranslateMessage(pMsg);
		::DispatchMessage(pMsg);
		return TRUE;
	}
	
	return CRichEditCtrl::PreTranslateMessage(pMsg);
}

void CGfxInComboEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == VK_ESCAPE || nChar == VK_RETURN || nChar == VK_TAB)
	{
		if (nChar == VK_ESCAPE) m_bESC = TRUE;
		GetParent()->SetFocus();
		return;
	}
	CRichEditCtrl::OnChar(nChar, nRepCnt, nFlags);
}

void CGfxInComboEdit::OnKillFocus(CWnd* pNewWnd) 
{
	if (m_bESC)
	{
		pCombo->m_bESC = true;
		//pCombo->PostMessage(WM_CLOSE);
		pCombo->DestroyWindow();
		return;
	}
	if (pNewWnd && (pNewWnd->GetSafeHwnd() == pCombo->wndList.GetSafeHwnd() || pCombo->IsChild(pNewWnd))) return;

	CRichEditCtrl::OnKillFocus(pNewWnd);

	CString csItem;
	GetWindowText(csItem);

	char * ptx = csItem.LockBuffer();
	pCombo->SendMessage(WM_USER_SELENDOK, 0, (LPARAM) ptx);
	csItem.UnlockBuffer();
	csLstText = csItem;

	pCombo->ProcessSelect(csItem);

	//PostMessage(WM_CLOSE);
	//DestroyWindow();
	pCombo->DestroyWindow();
	//pCombo->PostMessage(WM_CLOSE);
}

BOOL CGfxInComboEdit::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{

	return CRichEditCtrl::OnNotify(wParam, lParam, pResult);
}

void CGfxInComboEdit::OnChange() 
{
	if (!(pCombo->m_bAutoComplete)) return;

	if (bNoNextChange)
	{
		bNoNextChange = false;
		return;
	}

	CString str;
	GetWindowText(str);
	int nLength = str.GetLength();

	int idx = pCombo->FindString(-1, str);
	if (idx >= 0 && str != (*(pCombo->pArray))[idx])
	{
		SetWindowText((*(pCombo->pArray))[idx]);
		SetSel(nLength,-1);
	}
}


void CGfxInComboEdit::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CRichEditCtrl::OnLButtonDblClk(nFlags, point);

	NMHDR nh;
	nh.hwndFrom = GetParent()->GetParent()->GetSafeHwnd();
	nh.idFrom = GetParent()->GetParent()->GetDlgCtrlID();
	nh.code = NM_DBLCLK;

	GetParent()->GetParent()->GetParent()->PostMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM) &nh);
}

void CGfxInComboEdit::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CRichEditCtrl::PostNcDestroy();
}

void CGfxInComboEdit::OnRButtonDown(UINT nFlags, CPoint point) 
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

bool CGfxInComboEdit::UpdateCopy()
{
	long ns = 0, ne = 0;
	GetSel(ns, ne);
	return (ns != ne) ? true : false;
}

bool CGfxInComboEdit::UpdatePaste()
{
	return CanPaste() ? true : false;
}

bool CGfxInComboEdit::UpdateCut()
{
	long ns = 0, ne = 0;
	GetSel(ns, ne);
	return (ns != ne) ? true : false;
}

bool CGfxInComboEdit::UpdateUndo()
{
	return CanUndo() ? true : false;
}


void CGfxInComboEdit::OnEditCopy() 
{
	Copy();	
}

void CGfxInComboEdit::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(UpdateCopy());
}

void CGfxInComboEdit::OnEditCut() 
{
	Cut();	
}

void CGfxInComboEdit::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(UpdateCut());
}

void CGfxInComboEdit::OnEditPaste() 
{
	Paste();	
}

void CGfxInComboEdit::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(UpdatePaste());
}

void CGfxInComboEdit::OnEditUndo() 
{
	Undo();
}

void CGfxInComboEdit::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(UpdateUndo());
}
