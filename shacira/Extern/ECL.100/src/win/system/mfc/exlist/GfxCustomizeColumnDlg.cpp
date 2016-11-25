// GfxCustomizeColumnDlg.cpp : implementation file
//

#include "../stdafx.h"
//-TE-#include "GfxList.h"


#include "GfxCustomizeColumnDlg.h"
#include "GfxColumnManager.h"
#include "GfxListCtrl.h"
#include <stdlib.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGfxCustomizeColumnDlg dialog


CGfxCustomizeColumnDlg::CGfxCustomizeColumnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGfxCustomizeColumnDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGfxCustomizeColumnDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pManager = NULL;
}


void CGfxCustomizeColumnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGfxCustomizeColumnDlg)
	DDX_Control(pDX, IDC_FREECOL, wndFreeCol);
	DDX_Control(pDX, IDC_ACTCOL, wndCol);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGfxCustomizeColumnDlg, CDialog)
	//{{AFX_MSG_MAP(CGfxCustomizeColumnDlg)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_MOVEDOWN, OnMovedown)
	ON_BN_CLICKED(IDC_MOVEUP, OnMoveup)
	ON_LBN_SELCHANGE(IDC_ACTCOL, OnSelchangeActcol)
	ON_LBN_SELCHANGE(IDC_FREECOL, OnSelchangeFreecol)
	ON_LBN_DBLCLK(IDC_ACTCOL, OnDblclkActcol)
	ON_LBN_DBLCLK(IDC_FREECOL, OnDblclkFreecol)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGfxCustomizeColumnDlg message handlers

BOOL CGfxCustomizeColumnDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ASSERT(pManager);

	for (int t = 0; t < pManager->iColumnData; t ++)
	{
		if (!(pManager->IsDefColumn(pManager->pColumnData[t].iId)))
		{
			CString cs;

			if (pManager->pColumnData[t].dwData & fhImage)
				cs = pManager->pColumnData[t].cDescr ? pManager->pColumnData[t].cDescr : pManager->pColumnData[t].cText;
			else
				cs = pManager->pColumnData[t].cText;

			if (cs != "")
			{
				wndFreeCol.SetItemData(wndFreeCol.AddString(cs), pManager->pColumnData[t].iId);
			}
		}
	}

	for (int i = 0; i < pManager->iDefColumn; i ++)
	{
		t = pManager->FindColumnById(pManager->pDefColumn[i]);
		if (t >= 0)
		{
			CString cs;

			if (pManager->pColumnData[t].dwData & fhImage)
				cs = pManager->pColumnData[t].cDescr ? pManager->pColumnData[t].cDescr : pManager->pColumnData[t].cText;
			else
				cs = pManager->pColumnData[t].cText;

			if (cs != "")
			{
				wndCol.SetItemData(wndCol.AddString(cs), pManager->pColumnData[t].iId);
			}
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int SortIntRev(const void *arg1, const void *arg2 )
{
	if (*((INT *)arg1)>*((INT *)arg2)) return -1;
	if (*((INT *)arg1)<*((INT *)arg2)) return 1;
	return 0;
}

void CGfxCustomizeColumnDlg::OnAdd() 
{
	int max = wndFreeCol.GetSelCount();
	if (max > 0)
	{
		INT * pi = new INT[max];
		ASSERT(pi);
		if (LB_ERR != wndFreeCol.GetSelItems(max, pi))
		{
			qsort((void *) pi, (size_t) max, sizeof(int), SortIntRev);
			for (int t = 0; t < max; t++)
			{
				int idx = pi[t];
				CString cs;
				wndFreeCol.GetText(idx, cs);
				long lParam = wndFreeCol.GetItemData(idx);
				wndFreeCol.DeleteString(idx);
				wndCol.SetItemData(wndCol.AddString(cs), lParam);
			}
			if (GetDlgItem(IDOK)->IsWindowEnabled() == false) GetDlgItem(IDOK)->EnableWindow(true);
			OnSelchangeFreecol();
		}
		if (pi) delete [] pi;
	}
}

void CGfxCustomizeColumnDlg::OnRemove() 
{
	int max = wndCol.GetSelCount();
	if (max > 0)
	{
		INT * pi = new INT[max];
		ASSERT(pi);
		if (LB_ERR != wndCol.GetSelItems(max, pi))
		{
			qsort((void *) pi, (size_t) max, sizeof(int), SortIntRev);
	
			for (int t = 0; t < max; t++)
			{
				int idx = pi[t];
				CString cs;
				wndCol.GetText(idx, cs);
				long lParam = wndCol.GetItemData(idx);
				wndCol.DeleteString(idx);
				wndFreeCol.SetItemData(wndFreeCol.AddString(cs), lParam);
			}
			if (GetDlgItem(IDOK)->IsWindowEnabled() == false) GetDlgItem(IDOK)->EnableWindow(true);
			OnSelchangeActcol();
		}
		if (pi) delete [] pi;
	}
}

void CGfxCustomizeColumnDlg::OnMovedown() 
{
	if (wndCol.GetSelCount() == 1)
	{
		if (GetDlgItem(IDOK)->IsWindowEnabled() == false) GetDlgItem(IDOK)->EnableWindow(true);
		int idx = wndCol.GetCurSel();
		if (idx >= 0 && idx < wndCol.GetCount() - 1)
		{
			CString cs;
			wndCol.GetText(idx, cs);
			long lParam = wndCol.GetItemData(idx);
			wndCol.DeleteString(idx);
			idx ++;
			int newins = wndCol.InsertString(idx, cs);
			wndCol.SetItemData(newins, lParam);
			wndCol.SetSel(newins);
			OnSelchangeActcol();
		}
	}
}

void CGfxCustomizeColumnDlg::OnMoveup() 
{
	if (wndCol.GetSelCount() == 1)
	{
		if (GetDlgItem(IDOK)->IsWindowEnabled() == false) GetDlgItem(IDOK)->EnableWindow(true);
		int idx = wndCol.GetCurSel();
		if (idx > 0)
		{
			CString cs;
			wndCol.GetText(idx, cs);
			long lParam = wndCol.GetItemData(idx);
			wndCol.DeleteString(idx);
			idx --;
			int newins = wndCol.InsertString(idx, cs);
			wndCol.SetItemData(newins, lParam);
			wndCol.SetSel(newins);
			OnSelchangeActcol();
		}
	}
}

void CGfxCustomizeColumnDlg::OnOK() 
{
	int t, max = wndCol.GetCount(), * pi = NULL;

	if (max == 0)
	{
		AfxMessageBox("E' necessario inserire almeno una colonna ..");
		return;
	}

	pi = new int[max + 1];
	ASSERT(pi);

	for (t = 0; t < max; t++)
	{
		pi[t + 1] = wndCol.GetItemData(t);
	}

	pi[0] = 0;

	if (pManager->pDefColumn) delete [] pManager->pDefColumn;

	pManager->pDefColumn = pi;
	pManager->iDefColumn = max+1;
	
	CDialog::OnOK();
}

void CGfxCustomizeColumnDlg::OnSelchangeActcol() 
{
	int ic = wndCol.GetSelCount();
	if (ic <= 0 || wndCol.GetCount() <= 0)
	{
		if (GetDlgItem(IDC_REMOVE)->IsWindowEnabled()) GetDlgItem(IDC_REMOVE)->EnableWindow(false);
		if (ic != 1) if (GetDlgItem(IDC_MOVEDOWN)->IsWindowEnabled()) GetDlgItem(IDC_MOVEDOWN)->EnableWindow(false);
		if (ic != 1) if (GetDlgItem(IDC_MOVEUP)->IsWindowEnabled()) GetDlgItem(IDC_MOVEUP)->EnableWindow(false);
	}
	else
	{
		if (!(GetDlgItem(IDC_REMOVE)->IsWindowEnabled())) GetDlgItem(IDC_REMOVE)->EnableWindow(true);
		if (ic == 1 && wndCol.GetCurSel() < wndCol.GetCount() - 1)
		{
			if (!(GetDlgItem(IDC_MOVEDOWN)->IsWindowEnabled())) GetDlgItem(IDC_MOVEDOWN)->EnableWindow(true);
		}
		else
		{
			if (GetDlgItem(IDC_MOVEDOWN)->IsWindowEnabled()) GetDlgItem(IDC_MOVEDOWN)->EnableWindow(false);
		}
		if (ic == 1 && wndCol.GetCurSel() > 0) 
		{
			if (!(GetDlgItem(IDC_MOVEUP)->IsWindowEnabled())) GetDlgItem(IDC_MOVEUP)->EnableWindow(true);
		}
		else
		{
			if (GetDlgItem(IDC_MOVEUP)->IsWindowEnabled()) GetDlgItem(IDC_MOVEUP)->EnableWindow(false);
		}
	}
}

void CGfxCustomizeColumnDlg::OnSelchangeFreecol() 
{
	if (wndFreeCol.GetSelCount() <= 0  || wndFreeCol.GetCount() <= 0)
	{
		if (GetDlgItem(IDC_ADD)->IsWindowEnabled()) GetDlgItem(IDC_ADD)->EnableWindow(false);
	}
	else
	{
		if (!(GetDlgItem(IDC_ADD)->IsWindowEnabled())) GetDlgItem(IDC_ADD)->EnableWindow(true);
	}
}

void CGfxCustomizeColumnDlg::OnDblclkActcol() 
{
	OnRemove();
}

void CGfxCustomizeColumnDlg::OnDblclkFreecol() 
{
	OnAdd();
}
