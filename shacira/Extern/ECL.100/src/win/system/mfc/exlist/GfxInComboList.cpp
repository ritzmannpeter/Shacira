// GfxInComboList.cpp : implementation file
//

#include "../stdafx.h"
//-TE-#include "GfxList.h"


#include "GfxInComboList.h"
#include "GfxInCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGfxInComboList

CGfxInComboList::CGfxInComboList()
{
	pCombo = NULL;
	iLastSel = -1;
}

CGfxInComboList::~CGfxInComboList()
{
}


BEGIN_MESSAGE_MAP(CGfxInComboList, CListBox)
	//{{AFX_MSG_MAP(CGfxInComboList)
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGfxInComboList message handlers

void CGfxInComboList::OnKillFocus(CWnd* pNewWnd) 
{
	iLastSel = GetCurSel();
	if (iLastSel >= 0) GetText(iLastSel, csLastItem);

	CListBox::OnKillFocus(pNewWnd);

	if (pCombo && ::IsWindow(pCombo->GetSafeHwnd())) 
	{
		pCombo->SetFocus();
		pCombo->InvalidateButton();
	}
//	PostMessage(WM_CLOSE);
	DestroyWindow();
}

void CGfxInComboList::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CListBox::OnLButtonUp(nFlags, point);

	if (pCombo && ::IsWindow(pCombo->GetSafeHwnd())) 
	{
		pCombo->SetFocus();
		pCombo->InvalidateButton();
		if (GetSafeHwnd())
		{
			int iCurSel = GetCurSel();
			if (iCurSel >= 0)
			{
				CString csItem;
				GetText(iCurSel, csItem);
				char * ptx = csItem.LockBuffer();
				pCombo->SendMessage(WM_USER_SELENDOK, iCurSel, (LPARAM) ptx);
				csItem.UnlockBuffer();
			}
		}
		else
		{
			if (iLastSel >= 0) 	
			{
				char * ptx = csLastItem.LockBuffer();
				pCombo->SendMessage(WM_USER_SELENDOK, iLastSel, (LPARAM) ptx);
				csLastItem.UnlockBuffer();
			}
		}
	}

//	PostMessage(WM_CLOSE);
	DestroyWindow();
}

BOOL CGfxInComboList::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			pCombo->SetFocus();
			pCombo->InvalidateButton();

			if (GetSafeHwnd())
			{
				int iCurSel = GetCurSel();
				if (iCurSel >= 0)
				{
					CString csItem;
					GetText(iCurSel, csItem);
					char * ptx = csItem.LockBuffer();
					pCombo->SendMessage(WM_USER_SELENDOK, iCurSel, (LPARAM) ptx);
					csItem.UnlockBuffer();
				}
			}
			else
			{
				if (iLastSel >= 0)
				{
					char * ptx = csLastItem.LockBuffer();
					pCombo->SendMessage(WM_USER_SELENDOK, iLastSel, (LPARAM) ptx);
					csLastItem.UnlockBuffer();
				}
			}
//			PostMessage(WM_CLOSE);
			DestroyWindow();
			return true;
		}
		if (pMsg->wParam == VK_ESCAPE)
		{
			pCombo->SetFocus();
			pCombo->InvalidateButton();
//			PostMessage(WM_CLOSE);
			DestroyWindow();
			return true;
		}
	}
	
	return CListBox::PreTranslateMessage(pMsg);
}
