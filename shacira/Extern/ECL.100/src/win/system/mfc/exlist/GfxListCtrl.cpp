// GfxListCtrl.cpp : implementation file
//

#include "../stdafx.h"
//-TE-#include "GfxList.h"

#define IDC_IPEDIT 1234 /*-TE-*/

#include "GfxListCtrl.h"

#include "GfxInEdit.h"
#include "GfxInCombo.h"

#include "GfxPopupMenu.h"

//-TE-#include "GfxCustomizeColumnDlg.h"
//-TE-#include "GfxFormatColumnDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define _SORTASC_TEXT		"Sort ascending"
#define _SORTDESC_TEXT		"Sort descending"
#define _CUSTHEAD_TEXT		"Customize header"
#define _FORMATHEAD_TEXT	"Header format"

/*
#define _SORTASC_TEXT		"Ordinamento &crescente"
#define _SORTDESC_TEXT		"Ordinamento &descrescente"
#define _CUSTHEAD_TEXT		"&Personalizza colonne"
#define _FORMATHEAD_TEXT	"&Formattazione colonne"
*/

/////////////////////////////////////////////////////////////////////////////
// CSortClass

CSortClass::CSortClass(CListCtrl * _pWnd, const int _iCol, const bool _bIsNumeric, const bool _bIsValute)
{
	iCol = _iCol;
	pWnd = _pWnd;
	bIsNumeric = _bIsNumeric;
	bIsValute = _bIsValute;
	if (bIsValute) bIsNumeric = false;

	ASSERT(pWnd);
	int max = pWnd->GetItemCount();
	DWORD dw;
	CString txt;
	if (bIsNumeric)
	{
		for (int t = 0; t < max; t++)
		{
			dw = pWnd->GetItemData(t);
			txt = pWnd->GetItemText(t, iCol);
			pWnd->SetItemData(t, (DWORD) new CSortItemInt(dw, txt));
		}
	}
	else if (bIsValute)
	{
		for (int t = 0; t < max; t++)
		{
			dw = pWnd->GetItemData(t);
			txt = pWnd->GetItemText(t, iCol);

			pWnd->SetItemData(t, (DWORD) new CSortItemInt(dw, txt, true));
		}
	}
	else
	{
		for (int t = 0; t < max; t++)
		{
			dw = pWnd->GetItemData(t);
			txt = pWnd->GetItemText(t, iCol);
			pWnd->SetItemData(t, (DWORD) new CSortItem(dw, txt));
		}
	}
}

CSortClass::~CSortClass()
{
	ASSERT(pWnd);
	int max = pWnd->GetItemCount();
	if (bIsNumeric || bIsValute)
	{
		CSortItemInt * pItem;
		for (int t = 0; t < max; t++)
		{
			pItem = (CSortItemInt *) pWnd->GetItemData(t);
			ASSERT(pItem);
			pWnd->SetItemData(t, pItem->dw);
			delete pItem;
		}
	}
	else
	{
		CSortItem * pItem;
		for (int t = 0; t < max; t++)
		{
			pItem = (CSortItem *) pWnd->GetItemData(t);
			ASSERT(pItem);
			pWnd->SetItemData(t, pItem->dw);
			delete pItem;
		}
	}
}

void
CSortClass::Sort(const bool bAsc)
{
	if (bIsNumeric || bIsValute)
	{
		if (bAsc)
			pWnd->SortItems(CompareAscI, 0L);
		else
			pWnd->SortItems(CompareDesI, 0L);
	}
	else
	{
		if (bAsc)
			pWnd->SortItems(CompareAsc, 0L);
		else
			pWnd->SortItems(CompareDes, 0L);
	}
}

int CALLBACK CSortClass::CompareAsc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CSortItem * i1 = (CSortItem *) lParam1;
	CSortItem * i2 = (CSortItem *) lParam2;
	ASSERT(i1 && i2);
	return i1->txt.CompareNoCase(i2->txt);
}

int CALLBACK CSortClass::CompareDes(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CSortItem * i1 = (CSortItem *) lParam1;
	CSortItem * i2 = (CSortItem *) lParam2;
	ASSERT(i1 && i2);
	return i2->txt.CompareNoCase(i1->txt);
}

int CALLBACK CSortClass::CompareAscI(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CSortItemInt * i1 = (CSortItemInt *) lParam1;
	CSortItemInt * i2 = (CSortItemInt *) lParam2;
	ASSERT(i1 && i2);
	if (i1->iInt == i2->iInt) return 0;
	return i1->iInt > i2->iInt ? 1 : -1;
}

int CALLBACK CSortClass::CompareDesI(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CSortItemInt * i1 = (CSortItemInt *) lParam1;
	CSortItemInt * i2 = (CSortItemInt *) lParam2;
	ASSERT(i1 && i2);
	if (i1->iInt == i2->iInt) return 0;
	return i1->iInt < i2->iInt ? 1 : -1;
}

CSortClass::CSortItem::CSortItem(const DWORD _dw, const CString & _txt)
{
	dw = _dw;
	txt = _txt;
}

CSortClass::CSortItem::~CSortItem()
{
}

CSortClass::CSortItemInt::CSortItemInt(const DWORD _dw, CString & _txt, bool bIsValute)
{
	if (bIsValute)
	{
		static char newtxt[256];
		newtxt[0] = 0;
		char * ch = _txt.LockBuffer();
		int lmax = _txt.GetLength(), lidx = 0;
		for (int i = 0; i < lmax; i++)
		{
			if (ch[i] != '.') newtxt[lidx++] = ch[i];
		}
		newtxt[lidx] = 0;
		_txt.UnlockBuffer();
		iInt = atoi(newtxt);
	}
	else
	{
		iInt = atoi(_txt);
	}
	dw = _dw;
}


/////////////////////////////////////////////////////////////////////////////
// CGfxListCtrl

CGfxListCtrl::CGfxListCtrl()
{
	dwFlag = fHighRowSelect|fVertGrid|fHorizGrid|fAutoSort|fExInfo|fSubItemImages|fCellToolTip|fReturnModify|fReturnDblClk|fScrollBarAlways|fShowSelCell;
	dwhCombo = dwhComboEx = dwhEdit = dwhNumeric = dwhValute = dwhCombo = dwhImages = 0;
	
	wndHeader.dwSortUp = 0;
	m_clrText  = GetSysColor(COLOR_WINDOWTEXT);
	m_clrTextBk= GetSysColor(COLOR_WINDOW);
	m_clrBkgnd = GetSysColor(COLOR_WINDOW);
	crBackSel  = GetSysColor(COLOR_HIGHLIGHT);
	crCategoryBck = GetSysColor(COLOR_INACTIVECAPTION);
	cr3dFace = GetSysColor(COLOR_3DFACE);

	m_cxClient = 0;
	gpn = new CPen(PS_SOLID, 1, RGB(192,192,192));//GetSysColor(COLOR_INACTIVECAPTION));
	gcatpn = new CPen(PS_SOLID, 1, RGB(128,128,128));
	m_cxStateImageOffset = 0;

	CFont * ft = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	LOGFONT lf;
	ASSERT(ft);
	ft->GetLogFont(&lf);
	ftNormal.CreateFontIndirect(&lf);
	lf.lfWeight = 700;
	ftBold.CreateFontIndirect(&lf);
	lf.lfWeight = 0;
	lf.lfUnderline = TRUE;
	ftUnderline.CreateFontIndirect(&lf);
	lf.lfUnderline = FALSE;
	lf.lfItalic = TRUE;
	ftItalic.CreateFontIndirect(&lf);

	pReciper = NULL;

	iSubItemFocus = -1;

	pItemImageList = NULL;

	iCtrlId = -1;

	wndHeader.SetCallback((void (CWnd::*)(int &, int &))DragColumn);

	pManager = NULL;
	pCategoryManager = NULL;
	m_fpGetTextCallback = NULL;
	m_fpDaoCategoryFun = NULL;
	m_fpExInfoFun = NULL;

	iInternal1 = -1;

	iItemHeight = 17;
	iItemHeightCategory = 16;

	bBlendBitmap = true;

	iAutoPreviewHeight = 0;

	bDaoBind = false;
	//-TE-pRecordSet = NULL;

	rcMarginMM = CRect(0,0,0,0);
	dwPrintFlag = 0;
	csPrintName = "Gfx list Control";
}

CGfxListCtrl::~CGfxListCtrl()
{
	if (gpn) delete gpn;
	if (gcatpn) delete gcatpn;
	if (ftNormal.GetSafeHandle()) ftNormal.DeleteObject();
	if (ftUnderline.GetSafeHandle()) ftUnderline.DeleteObject();
	if (ftBold.GetSafeHandle()) ftBold.DeleteObject();
	if (ftItalic.GetSafeHandle()) ftItalic.DeleteObject();
	if (pManager) delete pManager;
	if (pCategoryManager) delete pCategoryManager;

}


BEGIN_MESSAGE_MAP(CGfxListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CGfxListCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydown)
	//-TE-ON_COMMAND(ID_GFX_CUSTOMIZEHEAD, OnGfxCustomizehead)
	//-TE-ON_UPDATE_COMMAND_UI(ID_GFX_CUSTOMIZEHEAD, OnUpdateGfxCustomizehead)
	//-TE-ON_COMMAND(ID_GFX_FORMATHEADER, OnGfxFormatheader)
	//-TE-ON_UPDATE_COMMAND_UI(ID_GFX_FORMATHEADER, OnUpdateGfxFormatheader)
/*-TE-
	ON_COMMAND(ID_GFX_SORTASC, OnGfxSortasc)
	ON_UPDATE_COMMAND_UI(ID_GFX_SORTASC, OnUpdateGfxSortasc)
	ON_COMMAND(ID_GFX_SORTDESC, OnGfxSortdesc)
	ON_UPDATE_COMMAND_UI(ID_GFX_SORTDESC, OnUpdateGfxSortdesc)
*/
	ON_WM_LBUTTONDBLCLK()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_MESSAGE(LVM_SETTEXTCOLOR, OnSetTextColor)
	ON_MESSAGE(LVM_SETTEXTBKCOLOR, OnSetTextBkColor)
	ON_MESSAGE(LVM_SETBKCOLOR, OnSetBkColor)
	ON_MESSAGE(LVM_SETIMAGELIST, OnSetImageList)
	ON_MESSAGE(WM_USER_TAB, OnUserTab)
	ON_WM_MEASUREITEM_REFLECT()
END_MESSAGE_MAP()
//	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	

/////////////////////////////////////////////////////////////////////////////
// CGfxListCtrl message handlers

LRESULT CGfxListCtrl::OnSetTextColor(WPARAM wParam, LPARAM lParam)
{
	m_clrText = (COLORREF) lParam;
	return (Default());
}

LRESULT CGfxListCtrl::OnSetTextBkColor(WPARAM wParam, LPARAM lParam)
{
	m_clrTextBk = (COLORREF) lParam;
	return (Default());
}

LRESULT CGfxListCtrl::OnSetBkColor(WPARAM wParam, LPARAM lParam)
{
	m_clrBkgnd = (COLORREF) lParam;
	return (Default());
}


LRESULT CGfxListCtrl::OnSetImageList(WPARAM wParam, LPARAM lParam)
{
	if ((int)wParam == LVSIL_STATE)
	{
		int cx, cy;
		if(::ImageList_GetIconSize((HIMAGELIST)lParam,&cx,&cy)) m_cxStateImageOffset=cx;
		else m_cxStateImageOffset=0;
	}
	return(Default());
}

int CGfxListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (wndToolTip.GetSafeHwnd() == NULL) OnInit();
/*	
	if ((GetStyle()&LVS_TYPEMASK) == LVS_REPORT)
	{
		HWND hHead = ::GetDlgItem(m_hWnd,0);
		VERIFY(wndHeader.SubclassWindow(hHead));
		TRACE0("Header subclassed.\n");
		wndToolTip.Create(this);
		wndToolTip.ShowWindow(SW_HIDE);
		wndHeader.ModifyStyle(0,HDS_DRAGDROP|HDS_FULLDRAG, SWP_FRAMECHANGED);
	}
*/	
	return 0;
}

int CGfxListCtrl::InsertColumnEx(int iPos, const char * cText, int iAlign, int iWidth, DWORD exData)
{
	int idx = InsertColumn(iPos, cText, iAlign, iWidth, iPos);
	ASSERT(idx >= 0);
	if (exData & fhComboBox)	dwhCombo   |= (1 << iPos);
	if (exData & fhComboBoxEx)	dwhComboEx |= (1 << iPos);
	if (exData & fhEdit)		dwhEdit    |= (1 << iPos);
	if (exData & fhNumeric)		dwhNumeric |= (1 << iPos);
	if (exData & fhValute)		dwhValute  |= (1 << iPos);
	if (exData & fhSortAble)		wndHeader.dwSortUp |= (1 << iPos);
	if (exData & fhImage)		dwhImages |= (1 << iPos);
	if (exData & fhNoSortArrow)	wndHeader.dwDontShowSortArrow |= (1 << iPos);
	if (exData & fhNoResizeColumn) wndHeader.dwNoResizeColumn |= (1 << iPos);
	
	return idx;
}

LPCTSTR CGfxListCtrl::MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset)
{
	static const _TCHAR szThreeDots[]=_T("...");

	int nStringLen=lstrlen(lpszLong);

	if(nStringLen==0 || pDC->GetTextExtent(lpszLong,nStringLen).cx+nOffset<=nColumnLen)
		return(lpszLong);

	static _TCHAR szShort[MAX_PATH];

	lstrcpy(szShort,lpszLong);
	int nAddLen=pDC->GetTextExtent(szThreeDots,sizeof(szThreeDots)).cx;

	for(int i=nStringLen-1; i>0; i--)
	{
		szShort[i]=0;
		if(pDC->GetTextExtent(szShort,i).cx+nOffset+nAddLen<=nColumnLen)
			break;
	}

	lstrcat(szShort,szThreeDots);

	return(szShort);
}

void CGfxListCtrl::MakeShortString(CDC* pDC, CString &cs, int nColumnLen, int nOffset)
{
	static const _TCHAR szThreeDots[]=_T("...");

	int nStringLen = cs.GetLength();

	if (nStringLen == 0 || pDC->GetTextExtent(cs).cx + nOffset <= nColumnLen) return;

	static _TCHAR szShort[MAX_PATH];

	lstrcpy(szShort, cs);

	int nAddLen = pDC->GetTextExtent(szThreeDots,sizeof(szThreeDots)).cx;

	for (int i = nStringLen-1; i > 0; i--)
	{
		szShort[i]=0;
		if(pDC->GetTextExtent(szShort,i).cx+nOffset+nAddLen<=nColumnLen)
			break;
	}

	lstrcat(szShort,szThreeDots);
	cs = szShort;
}


void CGfxListCtrl::DrawItemCategory(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rcItem(lpDrawItemStruct->rcItem);
	UINT uiFlags = ILD_TRANSPARENT;
	CImageList* pImageList;
	int nItem = lpDrawItemStruct->itemID;
	BOOL bFocus = (GetFocus() == this);
	COLORREF clrTextSave, clrBkSave;
	COLORREF clrImage = m_clrBkgnd;
	LV_ITEM lvi;
	lvi.mask	  = LVIF_IMAGE | LVIF_STATE | LVIF_PARAM;
	lvi.iItem     = nItem;
	lvi.iSubItem  = 0;
	lvi.stateMask = 0xFFFF;		// get all state flags
	GetItem(&lvi);

	CString csItem;

	DWORD dwItemData = GetItemData(nItem);
	csItem = GetItemText(nItem, 0);

	CRect clipBox;
	pDC->GetClipBox(clipBox);


	BOOL bSelected=(bFocus || (GetStyle() & LVS_SHOWSELALWAYS)) && lvi.state & LVIS_SELECTED;
	bSelected=bSelected || (lvi.state & LVIS_DROPHILITED);
	CRect rcAllLabels;
	GetItemRect(nItem,rcAllLabels,LVIR_BOUNDS);
	CRect rcLabel;
	GetItemRect(nItem,rcLabel,LVIR_LABEL);

	if (dwFlag&fHighRowSelect && rcAllLabels.right<m_cxClient) rcAllLabels.right = m_cxClient;

	CPen *opn = pDC->SelectObject(gcatpn);

	COLORREF crBck = crBackSel;
	COLORREF crBaseTextColor = bSelected ? GetSysColor(COLOR_HIGHLIGHTTEXT) : GetSysColor(COLOR_BTNTEXT);

	clrTextSave = pDC->SetTextColor(crBaseTextColor);

	int isCategory = pCategoryManager->IsListItemACategory(lvi.lParam);

	if (m_bitmap.m_hObject != NULL)
	{
		int isdc = pDC->SaveDC();

		CDC tempDC;
		tempDC.CreateCompatibleDC(pDC);
		tempDC.SelectObject(&m_bitmap);

		CRect rcClient;
		GetClientRect(&rcClient);

		CRgn rgnBitmap;
		CRect rcTmpBmp(rcItem);
		rcTmpBmp.right = rcClient.right;
		// We also need to check whether it is the last item
		// The update region has to be extended to the bottom if it is
		if (nItem == GetItemCount() - 1) rcTmpBmp.bottom = rcClient.bottom;

		rgnBitmap.CreateRectRgnIndirect(&rcTmpBmp);
		pDC->SelectClipRgn(&rgnBitmap);
		rgnBitmap.DeleteObject();
		
		if (pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE && m_pal.m_hObject != NULL)
		{
			pDC->SelectPalette(&m_pal, FALSE);
			pDC->RealizePalette();
		}

		CRect rcFirstItem;
		GetItemRect(0, rcFirstItem, LVIR_BOUNDS);
		for (int i = rcFirstItem.left; i < rcClient.right; i += m_cxBitmap)
			for (int j = rcFirstItem.top; j < rcClient.bottom; j += m_cyBitmap)
				pDC->BitBlt( i, j, m_cxBitmap, m_cyBitmap, &tempDC, 0, 0, SRCCOPY);

		pDC->RestoreDC(isdc);
	}


	if (bSelected)
	{
		clrBkSave=pDC->SetBkColor(crBck);

		if (!bBlendBitmap || m_bitmap.m_hObject == NULL || isCategory >= 0)
			pDC->FillSolidRect(rcAllLabels, crBck);
		else
		{
			CRect rcFirstItem;
			GetItemRect(0, rcFirstItem, LVIR_BOUNDS);

			int isdc = pDC->SaveDC();

			CRgn rgnBitmap;
			rgnBitmap.CreateRectRgnIndirect(&rcAllLabels);
			pDC->SelectClipRgn(&rgnBitmap);
			rgnBitmap.DeleteObject();

			for (int i = rcAllLabels.left; i < rcAllLabels.right; i += m_cxBitmap)
				for (int j = rcFirstItem.top; j < rcAllLabels.bottom; j += m_cyBitmap)
					if (j + m_cyBitmap > rcAllLabels.top) cBackImage.Draw(pDC, 0, CPoint(i, j), ILD_BLEND25);
			
			pDC->RestoreDC(isdc);
		}
	}
	else if (isCategory >= 0)
	{
		clrBkSave=pDC->SetBkColor(cr3dFace);
		pDC->FillSolidRect(rcAllLabels, cr3dFace);
	}
	else if (m_bitmap.m_hObject == NULL) pDC->FillSolidRect(rcAllLabels, m_clrTextBk);

	if (isCategory >= 0)
	{
		CRect rcButton(rcAllLabels.left + 3, rcAllLabels.top + (rcAllLabels.Height() - 12) / 2, rcAllLabels.left + 15, rcAllLabels.top + (rcAllLabels.Height() - 12) / 2 + 12);
		pDC->Draw3dRect(rcButton, RGB(255,255,255), RGB(0,0,0));
		rcButton.InflateRect(-1,-1);
		pDC->Draw3dRect(rcButton, RGB(192,192,192),RGB(128,128,128));
		rcButton.InflateRect(-1,-1);
		pDC->FillSolidRect(rcButton, RGB(192,192,192));
		CPen cBlackPen(PS_SOLID, 1, RGB(0,0,0));
		CPen cDkGrayPen(PS_SOLID, 1, RGB(128,128,128));
		CPen * open = pDC->SelectObject(&cBlackPen);
		
		pDC->MoveTo(rcAllLabels.left + 5, rcButton.top + 3);
		pDC->LineTo(rcAllLabels.left + 5 + 7, rcButton.top + 3);;

		if (!(pCategoryManager->pCategory[isCategory].bExpanded))
		{
			pDC->MoveTo(rcAllLabels.left + 8, rcButton.top);
			pDC->LineTo(rcAllLabels.left + 8, rcButton.top + 7);

			pDC->SelectObject(&cDkGrayPen);
			pDC->MoveTo(rcAllLabels.left, rcItem.bottom - 1);
			pDC->LineTo(rcAllLabels.right-1, rcItem.bottom - 1);
		}
		else
		{
			pDC->SelectObject(&cDkGrayPen);
			pDC->MoveTo(rcAllLabels.left+16, rcItem.bottom - 1);
			pDC->LineTo(rcAllLabels.right-1, rcItem.bottom - 1);
		}

		pDC->SelectObject(open);

		rcAllLabels.left += 20;
		pDC->DrawText(csItem, -1, rcAllLabels, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
		return;
	}

	if(lvi.state & LVIS_CUT)
	{
		clrImage=m_clrBkgnd;
		uiFlags|=ILD_BLEND50;
	}
	else if (bSelected)
	{
		clrImage=crBck;
		uiFlags|=ILD_BLEND50;
	}

	UINT nStateImageMask=lvi.state & LVIS_STATEIMAGEMASK;
	if(nStateImageMask)
	{
		int nImage=(nStateImageMask>>12)-1;
		pImageList=GetImageList(LVSIL_STATE);
		if(pImageList) pImageList->Draw(pDC,nImage,CPoint(rcItem.left,rcItem.top),ILD_TRANSPARENT);
	}
	CRect rcIcon;
	GetItemRect(nItem,rcIcon,LVIR_ICON);
	pImageList=GetImageList(LVSIL_SMALL);
	if(pImageList)
	{
		UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
		if(rcItem.left<rcItem.right-1) ImageList_DrawEx(pImageList->m_hImageList,lvi.iImage,pDC->m_hDC,rcIcon.left,rcIcon.top,16,rcIcon.Height()-1,m_clrBkgnd,clrImage,uiFlags | nOvlImageMask);
	}
	LV_COLUMN lvc;
	lvc.mask=LVCF_FMT | LVCF_WIDTH;
	GetColumn(0,&lvc);
	UINT nJustify1 = DT_LEFT;
	switch(lvc.fmt & LVCFMT_JUSTIFYMASK)
	{
	case LVCFMT_RIGHT: nJustify1=DT_RIGHT;
					   break;
	case LVCFMT_CENTER:nJustify1=DT_CENTER;
					   break;
	}
	
	GetItemRect(nItem, rcItem,LVIR_LABEL);
	rcItem.right -= m_cxStateImageOffset;
//	MakeShortString(pDC, csItem, rcItem.right-rcItem.left, 2*OFFSET_FIRST);
	rcLabel = rcItem;
	rcLabel.left += OFFSET_FIRST;
	rcLabel.right -= OFFSET_FIRST;

	CFont * oldFont = pDC->SelectObject(&ftNormal);

	clrTextSave = pDC->SetTextColor(crBaseTextColor);

	LXHDREX	lxhd;

	int iFirstColISubItem = GetColumnIndex(0);

	if (dwFlag&fExInfo)
	{
		lxhd.iNotifyCode = NTEX_ITEMINFO;
		lxhd.CtrlId = iCtrlId < 0 ? GetDlgCtrlID() : iCtrlId;
		lxhd.iItem = nItem;
		lxhd.iSubItem = iFirstColISubItem;
		lxhd.dwFlag = 0;
		lxhd.dwItemData = dwItemData;
	}

	int cxLittleBox = 0;
	{
		if (NeedColExInfo(0)) AskForInfo(&lxhd, pDC);

		if (dwFlag&fShowSelCell && iSubItemFocus == 0 && lvi.state&LVIS_FOCUSED)
		{
			if (!(dwFlag&fExInfo && lxhd.dwFlag&LXHDREX::exTextColor))
				pDC->SetTextColor(GetSysColor(COLOR_BTNTEXT));
		}
//		if (iSubItemFocus == 0 && lvi.state&LVIS_FOCUSED) pDC->FillSolidRect(rcLabel, m_clrTextBk);
		if (isCategory < 0)
		{
			CRect rcLittleBox(rcLabel);
			rcLittleBox.left = 0;
			pDC->FillSolidRect(rcLittleBox, cr3dFace);
			cxLittleBox = rcLittleBox.Width();
			CPen cDkGrayPen(PS_SOLID, 1, RGB(128,128,128));
			CPen * open = pDC->SelectObject(&cDkGrayPen);
			
			pDC->MoveTo(rcLittleBox.right, rcLittleBox.top);
			pDC->LineTo(rcLittleBox.right, rcLittleBox.bottom);

			pDC->SelectObject(open);
		}
		if (rcItem.left < clipBox.right && rcItem.right > clipBox.left)
		{
			if (dwFlag&fSubItemImages && dwhImages & 1 << iFirstColISubItem) 
			{
				int nImage = atoi(csItem);
				pImageList=pItemImageList;
			}
		}

		if ((dwFlag&fExInfo && lxhd.dwFlag&LXHDREX::exTextColor) && !(dwFlag&fExInfoOnRow)) 
			pDC->SetTextColor(crBaseTextColor);
	}

	int nColumnCount = GetColumnCount();

	bool bVert = dwFlag & fVertGrid ? true : false;
	bool bHorz = dwFlag & fHorizGrid ? true : false;


	for (int nColumn = 1; nColumn < nColumnCount; nColumn++)
	{
		GetColumn(nColumn,&lvc);
		rcItem.left=rcItem.right;
		rcItem.right+=lvc.cx;

		if (rcItem.left < clipBox.right && rcItem.right > clipBox.left)
		{
			GetItemTextEx(nItem, nColumn, csItem, &dwItemData);

			if (csItem != "")
			{
//				MakeShortString(pDC, csItem, rcItem.right-rcItem.left,2*OFFSET_OTHER);

				UINT nJustify=DT_LEFT;

				switch(lvc.fmt & LVCFMT_JUSTIFYMASK)
				{
					case LVCFMT_RIGHT:	nJustify=DT_RIGHT;	break;
					case LVCFMT_CENTER:	nJustify=DT_CENTER;	break;
					default:								break;
				}

				rcLabel=rcItem;
				rcLabel.left+=OFFSET_OTHER;
				rcLabel.right-=OFFSET_OTHER;

				if (dwFlag&fShowSelCell && iSubItemFocus == nColumn && lvi.state&LVIS_FOCUSED) pDC->SetTextColor(GetSysColor(COLOR_BTNTEXT)); else pDC->SetTextColor(crBaseTextColor);

				if (NeedColExInfo(nColumn))
				{
					lxhd.iNotifyCode = NTEX_ITEMINFO;
					lxhd.iSubItem = GetColumnIndex(nColumn);
					AskForInfo(&lxhd, pDC);
				}

				if (dwFlag&fShowSelCell && iSubItemFocus == nColumn && lvi.state&LVIS_FOCUSED)
				{
					rcItem.left --;
					pDC->FillSolidRect(rcItem, m_clrTextBk);
					rcItem.left ++;
				}

				if (dwFlag&fSubItemImages && dwhImages & 1 << GetColumnIndex(nColumn)) 
				{
					int nImage = atoi(csItem);
					pImageList=pItemImageList;
					if(pImageList)
					{
						IMAGEINFO ii;
						pImageList->GetImageInfo(nImage, &ii);
						CRect rcIma(ii.rcImage);

						int x = rcLabel.left + (rcLabel.Width() - rcIma.Width()) / 2;
						int y = rcLabel.top + (rcLabel.Height() - rcIma.Height()) / 2;

						UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
						if(rcLabel.left<rcLabel.right-1) 
							ImageList_DrawEx(pImageList->m_hImageList,nImage,pDC->m_hDC,x,y,rcIma.Width(),rcIma.Height()-1,m_clrBkgnd,clrImage,uiFlags | nOvlImageMask);
					}
				}
				else
				{
					pDC->DrawText(csItem,-1,rcLabel,nJustify | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER | DT_END_ELLIPSIS);
				}

				if (dwFlag&fExInfo && lxhd.dwFlag&LXHDREX::exTextColor) pDC->SetTextColor(crBaseTextColor);
				else if (iSubItemFocus >= 0 && lvi.state&LVIS_FOCUSED)
				{
					pDC->SetTextColor(crBaseTextColor);
				}
			}
			else
			{
				if (dwFlag&fShowSelCell && iSubItemFocus == nColumn && lvi.state&LVIS_FOCUSED)
					pDC->FillSolidRect(rcItem, m_clrTextBk);
			}
			if (bVert)
			{
				pDC->MoveTo(rcItem.right-1, rcItem.bottom - 1);
				pDC->LineTo(rcItem.right-1, rcItem.top-1);
			}
		}
		else 
		{
			if (rcItem.left >= clipBox.right) break;
		}
	}
	if (dwFlag & fAllowDivider)
	{
		LXHDREX_DIV lxhd1(&lxhd);
		lxhd1.iNotifyCode = NTEX_DIVIDER;
		lxhd1.rcItem = rcAllLabels;
		lxhd1.pDC = pDC;

		if (!SendInfoExMsg((LXHDREX *)(&lxhd1)))
		{
			if (bHorz)
			{
				pDC->MoveTo(rcAllLabels.left + cxLittleBox, rcItem.bottom - 1);
				pDC->LineTo(rcAllLabels.right-1, rcItem.bottom - 1);
			}
		}
	}
	else
	{
		if (bHorz)
		{
			pDC->MoveTo(rcAllLabels.left + cxLittleBox, rcItem.bottom - 1);
			pDC->LineTo(rcAllLabels.right-1, rcItem.bottom - 1);
		}
	}

	if (lvi.state&LVIS_FOCUSED) 
	{
		if (isCategory < 0) rcAllLabels.left += cxLittleBox;
		pDC->SetTextColor(RGB(0,0,0));
		rcAllLabels.bottom --;
		pDC->FrameRect(rcAllLabels, pDC->GetHalftoneBrush());
	}

	if(bSelected) pDC->SetBkColor(clrBkSave);

	pDC->SetTextColor(clrTextSave);
	pDC->SelectObject(opn);

	pDC->SelectObject(oldFont);
}


void CGfxListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (pCategoryManager)
	{
		DrawItemCategory(lpDrawItemStruct);
		return;
	}

	CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rcItem(lpDrawItemStruct->rcItem);
	UINT uiFlags=ILD_TRANSPARENT;
	CImageList* pImageList;
	int nItem=lpDrawItemStruct->itemID;
	BOOL bFocus=(GetFocus()==this);
	COLORREF clrTextSave, clrBkSave;
	COLORREF clrImage=m_clrBkgnd;

	LV_ITEM lvi;
	lvi.mask=LVIF_IMAGE | LVIF_STATE;
	lvi.iItem=nItem;
	lvi.iSubItem=0;
	lvi.stateMask=0xFFFF;		// get all state flags
	GetItem(&lvi);

	CRect clipBox;
	pDC->GetClipBox(clipBox);

	CString csItem;
	DWORD dwItemData = GetItemData(nItem);
	GetItemTextEx(nItem, 0, csItem, &dwItemData);

	BOOL bSelected=(bFocus || (GetStyle() & LVS_SHOWSELALWAYS)) && lvi.state & LVIS_SELECTED;
	bSelected=bSelected || (lvi.state & LVIS_DROPHILITED);
	CRect rcAllLabels;
	GetItemRect(nItem,rcAllLabels,LVIR_BOUNDS);
	CRect rcLabel;
	GetItemRect(nItem,rcLabel,LVIR_LABEL);
	rcAllLabels.bottom -= iAutoPreviewHeight;
	rcLabel.bottom -= iAutoPreviewHeight;

	if (dwFlag&fHighRowSelect && rcAllLabels.right<m_cxClient) rcAllLabels.right = m_cxClient;

	CPen *opn = pDC->SelectObject(gpn);

	COLORREF crBck = crBackSel;

	COLORREF crBaseTextColor = bSelected ? GetSysColor(COLOR_HIGHLIGHTTEXT) : GetSysColor(COLOR_BTNTEXT);

	clrTextSave = pDC->SetTextColor(crBaseTextColor);


	if (m_bitmap.m_hObject != NULL)
	{
		CDC tempDC;
		tempDC.CreateCompatibleDC(pDC);
		tempDC.SelectObject(&m_bitmap);

		CRect rcClient;
		GetClientRect(&rcClient);

		int isdc = pDC->SaveDC();

		CRgn rgnBitmap;
		CRect rcTmpBmp(rcAllLabels);
		rcTmpBmp.bottom += iAutoPreviewHeight;
		if (rcTmpBmp.right < m_cxClient) rcTmpBmp.right = m_cxClient;
		if (nItem == GetItemCount() - 1) rcTmpBmp.bottom = rcClient.bottom;

		rgnBitmap.CreateRectRgnIndirect(&rcTmpBmp);
		pDC->SelectClipRgn(&rgnBitmap);
		rgnBitmap.DeleteObject();
		
		if (pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE && m_pal.m_hObject != NULL)
		{
			pDC->SelectPalette(&m_pal, FALSE);
			pDC->RealizePalette();
		}

		CRect rcFirstItem;
		GetItemRect(0, rcFirstItem, LVIR_BOUNDS);

		for (int i = rcFirstItem.left; i < rcTmpBmp.right; i += m_cxBitmap)
			for (int j = rcFirstItem.top; j < rcTmpBmp.bottom; j += m_cyBitmap)
				pDC->BitBlt(i, j, m_cxBitmap, m_cyBitmap, &tempDC, 0, 0, SRCCOPY);

		pDC->RestoreDC(isdc);
	}


	if (bSelected)
	{
		clrBkSave = pDC->SetBkColor(crBck);

		if (!bBlendBitmap || m_bitmap.m_hObject == NULL)
			pDC->FillSolidRect(rcAllLabels, crBck);
		else
		{
			CRect rcFirstItem;
			GetItemRect(0, rcFirstItem, LVIR_BOUNDS);

			int isdc = pDC->SaveDC();

			CRgn rgnBitmap;
			rgnBitmap.CreateRectRgnIndirect(&rcAllLabels);
			pDC->SelectClipRgn(&rgnBitmap);
			rgnBitmap.DeleteObject();

			rcAllLabels.bottom += iAutoPreviewHeight;
//			for (int i = 0; i < rcAllLabels.right; i += m_cxBitmap)
//				for (int j = 0; j < rcAllLabels.bottom; j += m_cyBitmap)
//					if (j + m_cyBitmap > rcAllLabels.top) cBackImage.Draw(pDC, 0, CPoint(i, j), ILD_BLEND25);
			for (int i = rcAllLabels.left; i < rcAllLabels.right; i += m_cxBitmap)
				for (int j = rcFirstItem.top; j < rcAllLabels.bottom; j += m_cyBitmap)
					if (j + m_cyBitmap > rcAllLabels.top) cBackImage.Draw(pDC, 0, CPoint(i, j), ILD_BLEND25);
			
			rcAllLabels.bottom -= iAutoPreviewHeight;
			pDC->RestoreDC(isdc);
		}
	}
	else if (m_bitmap.m_hObject == NULL) pDC->FillSolidRect(rcAllLabels, m_clrTextBk);

	if(lvi.state & LVIS_CUT)
	{
		clrImage=m_clrBkgnd;
		uiFlags|=ILD_BLEND50;
	}
	else if (bSelected)
	{
		clrImage=crBck;
		uiFlags|=ILD_BLEND50;
	}

	UINT nStateImageMask=lvi.state & LVIS_STATEIMAGEMASK;
	if(nStateImageMask)
	{
		int nImage=(nStateImageMask>>12)-1;
		pImageList=GetImageList(LVSIL_STATE);
		if(pImageList) pImageList->Draw(pDC,nImage,CPoint(rcItem.left,rcItem.top),ILD_TRANSPARENT);
	}
	CRect rcIcon;
	GetItemRect(nItem,rcIcon,LVIR_ICON);
	rcIcon.OffsetRect(0, -iAutoPreviewHeight / 2);

	pImageList=GetImageList(LVSIL_SMALL);
	if(pImageList)
	{
		UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
		if(rcItem.left<rcItem.right-1) ImageList_DrawEx(pImageList->m_hImageList,lvi.iImage,pDC->m_hDC,rcIcon.left,rcIcon.top,16,rcIcon.Height()-1,m_clrBkgnd,clrImage,uiFlags | nOvlImageMask);
	}
	LV_COLUMN lvc;
	lvc.mask=LVCF_FMT | LVCF_WIDTH;
	GetColumn(0,&lvc);
	UINT nJustify1=DT_LEFT;
	switch(lvc.fmt & LVCFMT_JUSTIFYMASK)
	{
	case LVCFMT_RIGHT: nJustify1=DT_RIGHT;
					   break;
	case LVCFMT_CENTER:nJustify1=DT_CENTER;
					   break;
	}
	GetItemRect(nItem,rcItem,LVIR_LABEL);
	rcItem.bottom -= iAutoPreviewHeight;

	rcItem.right-=m_cxStateImageOffset;
//	MakeShortString(pDC, csItem, rcItem.right-rcItem.left, 2*OFFSET_FIRST);
	rcLabel=rcItem;
	rcLabel.left+=OFFSET_FIRST;
	rcLabel.right-=OFFSET_FIRST;

	CFont * oldFont = pDC->SelectObject(&ftNormal);

	clrTextSave = pDC->SetTextColor(crBaseTextColor);

	LXHDREX	lxhd;

	int iFirstColISubItem = GetColumnIndex(0);

	if (dwFlag&fExInfo)
	{
		lxhd.iNotifyCode = NTEX_ITEMINFO;
		lxhd.CtrlId = iCtrlId < 0 ? GetDlgCtrlID() : iCtrlId;
		lxhd.iItem = nItem;
		lxhd.iSubItem = iFirstColISubItem;
		lxhd.dwFlag = 0;
		lxhd.dwItemData = dwItemData;
	}

	if (NeedColExInfo(0)) AskForInfo(&lxhd, pDC);

	bool bVert = dwFlag & fVertGrid ? true : false;
	bool bHorz = dwFlag & fHorizGrid ? true : false;

//	if (rcItem.left < clipBox.right && rcItem.right > clipBox.left)
	{
		if (dwFlag&fShowSelCell && iSubItemFocus == 0 && lvi.state&LVIS_FOCUSED)
		{
			if (!(dwFlag&fExInfo && lxhd.dwFlag&LXHDREX::exTextColor))
				pDC->SetTextColor(GetSysColor(COLOR_BTNTEXT));

			if (rcLabel.right > rcLabel.left + 4) pDC->FillSolidRect(rcLabel, m_clrTextBk);
		}
		

		if (rcItem.left < clipBox.right && rcItem.right > clipBox.left && rcItem.right > rcItem.left)
		{
			if (dwFlag&fSubItemImages && dwhImages & 1 << iFirstColISubItem) 
			{
				int nImage = atoi(csItem);
				pImageList=pItemImageList;
				if(pImageList)
				{
					UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
					if(rcLabel.left<rcLabel.right-1) ImageList_DrawEx(pImageList->m_hImageList,nImage,pDC->m_hDC,rcLabel.left,rcLabel.top,16,rcLabel.Height()-1,m_clrBkgnd,clrImage,uiFlags | nOvlImageMask);
				}
			}
			else pDC->DrawText(csItem, -1, rcLabel, nJustify1 | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
		}

		if ((dwFlag&fExInfo && lxhd.dwFlag&LXHDREX::exTextColor) && !(dwFlag&fExInfoOnRow)) 
			pDC->SetTextColor(crBaseTextColor);

		if (bVert)
		{
			pDC->MoveTo(rcLabel.right-1, rcLabel.bottom - 1);
			pDC->LineTo(rcLabel.right-1, rcLabel.top-1);
		}
	}

	int nColumnCount = GetColumnCount();

	for (int nColumn = 1; nColumn < nColumnCount; nColumn++)
	{
		GetColumn(nColumn,&lvc);
		rcItem.left=rcItem.right;
		rcItem.right+=lvc.cx;

		if (rcItem.left < clipBox.right && rcItem.right > clipBox.left && rcItem.right > rcItem.left)
		{
			GetItemTextEx(nItem, nColumn, csItem, &dwItemData);

			if (csItem != "")
			{
				UINT nJustify=DT_LEFT;
				switch(lvc.fmt & LVCFMT_JUSTIFYMASK)
				{
					case LVCFMT_RIGHT:	nJustify=DT_RIGHT;	break;
					case LVCFMT_CENTER:	nJustify=DT_CENTER;	break;
					default:								break;
				}

				rcLabel=rcItem;
				rcLabel.left+=OFFSET_OTHER;
				rcLabel.right-=OFFSET_OTHER;

				if (dwFlag&fShowSelCell && iSubItemFocus == nColumn && lvi.state&LVIS_FOCUSED) pDC->SetTextColor(GetSysColor(COLOR_BTNTEXT)); else pDC->SetTextColor(crBaseTextColor);

				if (NeedColExInfo(nColumn))
				{
					lxhd.iNotifyCode = NTEX_ITEMINFO;
					lxhd.iSubItem = GetColumnIndex(nColumn);
					AskForInfo(&lxhd, pDC);
				}

				if (dwFlag&fShowSelCell && iSubItemFocus == nColumn && lvi.state&LVIS_FOCUSED)
				{
					rcItem.left --;
					pDC->FillSolidRect(rcItem, m_clrTextBk);
					rcItem.left ++;
				}

				if (dwFlag&fSubItemImages && dwhImages & 1 << GetColumnIndex(nColumn)) 
				{
					int nImage = atoi(csItem);
					pImageList=pItemImageList;//GetImageList(LVSIL_SMALL);
					if(pImageList)
					{
						IMAGEINFO ii;
						pImageList->GetImageInfo(nImage, &ii);
						CRect rcIma(ii.rcImage);

						int x = rcLabel.left + (rcLabel.Width() - rcIma.Width()) / 2;
						int y = rcLabel.top + (rcLabel.Height() - rcIma.Height()) / 2;

						UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
						if(rcLabel.left<rcLabel.right-1) 
							ImageList_DrawEx(pImageList->m_hImageList,nImage,pDC->m_hDC,x,y,rcIma.Width(),rcIma.Height()-1,m_clrBkgnd,clrImage,uiFlags | nOvlImageMask);
					}
				}
				else
				{
					pDC->DrawText(csItem,-1,rcLabel,nJustify | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER | DT_END_ELLIPSIS);
				}

				if (dwFlag&fExInfo && lxhd.dwFlag&LXHDREX::exTextColor) pDC->SetTextColor(crBaseTextColor);
				else if (iSubItemFocus >= 0 && lvi.state&LVIS_FOCUSED)
				{
					pDC->SetTextColor(crBaseTextColor);
				}
			}
			else
			{
				if (dwFlag&fShowSelCell && iSubItemFocus == nColumn && lvi.state&LVIS_FOCUSED)
					pDC->FillSolidRect(rcItem, m_clrTextBk);
			}
			if (bVert)
			{
				pDC->MoveTo(rcItem.right-1, rcItem.bottom - 1);
				pDC->LineTo(rcItem.right-1, rcItem.top-1);
			}
		}
		else 
		{
			if (rcItem.left >= clipBox.right) break;
		}
	}
	if (iAutoPreviewHeight > 0)
	{
		LXHDREX_DIV lxhd1(&lxhd);
		lxhd1.iNotifyCode = NTEX_AUTOPREVIEW;
		lxhd1.rcItem = rcAllLabels;
		lxhd1.rcItem.top = lxhd1.rcItem.bottom;
		lxhd1.rcItem.bottom += iAutoPreviewHeight;
		if (m_bitmap.m_hObject == NULL) pDC->FillSolidRect(lxhd1.rcItem, m_clrTextBk);
		lxhd1.pDC = pDC;
		pDC->SelectObject(&ftNormal);
		SendInfoExMsg((LXHDREX *)(&lxhd1));
		pDC->MoveTo(rcAllLabels.left, lxhd1.rcItem.bottom - 1);
		pDC->LineTo(rcAllLabels.right-1, lxhd1.rcItem.bottom - 1);
	}
	if (dwFlag & fAllowDivider)
	{
		LXHDREX_DIV lxhd1(&lxhd);
		lxhd1.iNotifyCode = NTEX_DIVIDER;
		lxhd1.rcItem = rcAllLabels;
		lxhd1.pDC = pDC;

		if (!SendInfoExMsg((LXHDREX *)(&lxhd1)))
		{
			if (bHorz)
			{
				pDC->MoveTo(rcAllLabels.left, rcItem.bottom - 1);
				pDC->LineTo(rcAllLabels.right-1, rcItem.bottom - 1);
			}
		}
	}
	else
	{
		if (bHorz)
		{
			pDC->MoveTo(rcAllLabels.left, rcItem.bottom - 1);
			pDC->LineTo(rcAllLabels.right-1, rcItem.bottom - 1);
		}
	}

	if (lvi.state&LVIS_FOCUSED) 
	{
		pDC->SetTextColor(RGB(0,0,0));
		rcAllLabels.bottom --;
		pDC->FrameRect(rcAllLabels, pDC->GetHalftoneBrush());
	}

	if(bSelected) pDC->SetBkColor(clrBkSave);

	pDC->SetTextColor(clrTextSave);
	pDC->SelectObject(opn);

	pDC->SelectObject(oldFont);
}

bool CGfxListCtrl::AskForInfo(LXHDREX * pLx, CDC *pDC)
{
	CWnd * pWnd = GetReciper();
	pLx->dwFlag = 0;
//	if (pWnd->SendMessage(WM_LISTEX_NOTIFY, 0, (LPARAM) pLx))
	if (SendInfoExMsg(pLx))
	{
		if (pLx->dwFlag&LXHDREX::exHFont) ::SelectObject(pDC->GetSafeHdc(), (HGDIOBJ) pLx->hfText);
		else if (pLx->dwFlag&LXHDREX::exBold) pDC->SelectObject(&ftBold);
		else if (pLx->dwFlag&LXHDREX::exItalic) pDC->SelectObject(&ftItalic);
		else if (pLx->dwFlag&LXHDREX::exUnderline) pDC->SelectObject(&ftUnderline);
		else pDC->SelectObject(&ftNormal);

		if (pLx->dwFlag&LXHDREX::exTextColor) pDC->SetTextColor(pLx->crText);

		return true;
	}
	return false;
}

long CGfxListCtrl::SendInfoExMsg(LXHDREX * pLx)
{
	CWnd * pWnd = GetReciper();
	if (m_fpExInfoFun) return (GetParent()->*m_fpExInfoFun)(pLx);
	return pWnd->SendMessage(WM_LISTEX_NOTIFY, 0, (LPARAM) pLx);
}

void CGfxListCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;

	if (dwFlag & fAutoSort)
	{
		CWaitCursor tom;
/*-TE-
		if (bDaoBind && pRecordSet)
		{
			if (pNMListView->iSubItem == 0) return;

			if (pCategoryManager != NULL) pCategoryManager->ResetList(this);

			bool bAsc = wndHeader.GetSortOrder(pNMListView->iSubItem);
			bAsc = !bAsc;
			wndHeader.SetSortImage(pNMListView->iSubItem, bAsc);

			CDaoFieldInfo fieldinfo;
			pRecordSet->GetFieldInfo(pNMListView->iSubItem - 1, fieldinfo);

			pRecordSet->m_strSort = fieldinfo.m_strName;
			if (!bAsc) pRecordSet->m_strSort += " DESC";
			pRecordSet->Requery();
			pRecordSet->MoveLast();
			Invalidate();
			if (pCategoryManager != NULL) pCategoryManager->SetupList(this);
		}
		else
*/
		{

			if (pManager != NULL)
			{
				int col = pManager->FindColumnById(GetColumnIndex(pNMListView->iSubItem));
				if (col >= 0)
				{
					if (!(pManager->pColumnData[col].dwData&fhSortAble)) return;
				}
			}

			if (pCategoryManager != NULL) pCategoryManager->ResetList(this);

			bool bAsc = wndHeader.GetSortOrder(pNMListView->iSubItem);
			bAsc = !bAsc;
			wndHeader.SetSortImage(pNMListView->iSubItem, bAsc);
			
			{
				CSortClass csc(this, pNMListView->iSubItem, dwhNumeric & (1 << GetColumnIndex(pNMListView->iSubItem)) ? true : false, dwhValute & (1 << GetColumnIndex(pNMListView->iSubItem)) ? true : false);
				csc.Sort(bAsc);
			}

			if (pCategoryManager != NULL) pCategoryManager->SetupList(this);
			else
			{
				int idx = GetNextItem(-1, LVNI_SELECTED);
				if (idx >= 0) EnsureVisible(idx, false);
			}
		}
	}
}


int CGfxListCtrl::CellRectFromPoint(CPoint & point, RECT * cellrect, int * col) const
{
	int colnum;
	if ((GetStyle() & LVS_TYPEMASK) != LVS_REPORT) return -1;

	int row = GetTopIndex();
	int bottom = row + GetCountPerPage();
	if (bottom > GetItemCount()) bottom = GetItemCount();
	int nColumnCount = GetColumnCount();
	for (;row <=bottom; row++)
	{
		CRect rect;
		GetItemRect(row, &rect, LVIR_BOUNDS);
		rect.bottom -= iAutoPreviewHeight;

		if (rect.PtInRect(point))
		{
			for (colnum = 0; colnum < nColumnCount; colnum++)
			{
				int colwidth = GetColumnWidth(colnum);
				if (point.x >= rect.left && point.x <= (rect.left + colwidth))
				{
					RECT rectClient;
					GetClientRect(&rectClient);
					if (point.x > rectClient.right) return -1;
					if (col) *col = colnum;
					rect.right = rect.left + colwidth;
					if (rect.right > rectClient.right) rect.right = rectClient.right;
					*cellrect = rect;
					return row;
				}
				rect.left += colwidth;
			}
		}
	}
	return -1;
}

void CGfxListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (dwFlag & fCellToolTip && nFlags == 0 && wndToolTip.GetSafeHwnd() && GetFocus() == this)
	{
		int row, col;
		RECT cellrect;
		row = CellRectFromPoint(point, &cellrect, &col );
		if (row != -1)
		{
			DWORD dw = GetItemData(row);
			if (pCategoryManager != NULL)
			{
				if (col == 0 || pCategoryManager->IsListItemACategory(dw) >= 0) return;
			}
			int offset = 6;
			if (col == 0) 
			{
				CRect rcLabel;
				GetItemRect(row, &rcLabel, LVIR_LABEL);
				offset = rcLabel.left - cellrect.left + offset / 2;
			}
			cellrect.top--;
			if (!(dwFlag&fSubItemImages) || !(dwhImages & 1 << GetColumnIndex(col)))
			{
				CString csItem;
				GetItemTextEx(row, col, csItem, &dw);
				wndToolTip.Show(cellrect, csItem, offset-1);

//				wndToolTip.Show(cellrect, GetItemText( row, col ), offset-1);
			}
		}
	}
	
	CListCtrl::OnMouseMove(nFlags, point);
}

void CGfxListCtrl::ModifyFlag(const DWORD dwRemove, const DWORD dwAdd, const UINT dwRedraw)
{
	if (dwRemove != 0) dwFlag &= ~dwRemove;
	if (dwAdd != 0) dwFlag |= dwAdd;
	if (GetSafeHwnd())
	{
		if (dwRedraw != 0) SetWindowPos(0,0,0,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOMOVE|dwRedraw);
		else Invalidate();
	}
}

void CGfxListCtrl::OnSize(UINT nType, int cx, int cy) 
{
/*	CWnd * pf = GetFocus();
	if (pf != this && IsChild(pf)) SetFocus();
*/
	CListCtrl::OnSize(nType, cx, cy);
	m_cxClient = cx;	

	int iItemCount = GetItemCount();
	if (dwFlag&fScrollBarAlways)
	{
		ShowScrollBar(SB_BOTH);
		int iPageItem = GetCountPerPage();
		if (iItemCount < iPageItem) EnableScrollBar(SB_VERT, ESB_DISABLE_BOTH);
		else EnableScrollBar(SB_VERT, ESB_ENABLE_BOTH);

		if (iItemCount > 0)
		{
			CRect rcAllLabels;
			GetItemRect(0,rcAllLabels,LVIR_BOUNDS);
			EnableScrollBar(SB_HORZ, rcAllLabels.Width() < cx ? ESB_DISABLE_BOTH : ESB_ENABLE_BOTH);
		}
		else EnableScrollBar(SB_HORZ, ESB_DISABLE_BOTH);
	}

	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);
	int iCol, i = HitTestEx(pt, &iCol);
	if (i > 0)
	{
		CRect rc;
		GetSubItemRect(i,iCol,rc);
		InvalidateRect(rc, true);
		if (i > 0)
		{
			GetSubItemRect(i-1,iCol,rc);
			InvalidateRect(rc, true);
		}
		if (i < iItemCount - 1)
		{
			GetSubItemRect(i+1,iCol,rc);
			InvalidateRect(rc, true);
		}
	}
}

void CGfxListCtrl::OnInit()
{
	if ((GetStyle()&LVS_TYPEMASK) == LVS_REPORT)
	{
		HWND hHead = ::GetDlgItem(m_hWnd,0);
		VERIFY(wndHeader.SubclassWindow(hHead));
		TRACE0("Header subclassed.\n");
		wndToolTip.Create(this);
		wndToolTip.ShowWindow(SW_HIDE);
		ModifyStyle(0,WS_CLIPSIBLINGS|WS_CLIPCHILDREN);
	}
}

void CGfxListCtrl::OnPaint() 
{
	int iItemCount = GetItemCount();
	CRect rcAllLabels, rc;

	if (iItemCount > 0)
	{
		GetItemRect(0,rcAllLabels,LVIR_BOUNDS);
		if (dwFlag&fHighRowSelect)
		{
			if (rcAllLabels.right<m_cxClient)
			{
 				CPaintDC dc(this);
				CRect rcClip;
				dc.GetClipBox(rcClip);
				if (!rcClip.IsRectEmpty())
				{
					rcClip.left = min(rcAllLabels.right-1, rcClip.left);
					rcClip.right = m_cxClient;
					InvalidateRect(rcClip,FALSE);
				}
			}
		}
	}
	const MSG *msg = GetCurrentMessage();
	DefWindowProc( msg->message, msg->wParam, msg->lParam );

	if (iItemCount == 0)
	{
		GetClientRect(rc);
		CRect hrc;
		CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
		ASSERT(pHeader);
		pHeader->GetClientRect(hrc);
		rc.top += hrc.Height() + 2;
		rc.bottom += 20;
		CClientDC dc(this);
		COLORREF ocrt = dc.SetTextColor(GetSysColor(COLOR_GRAYTEXT));
		int obk = dc.SetBkMode(TRANSPARENT);
		CFont * oft = dc.SelectObject(&ftNormal);
		dc.FillSolidRect(rc, m_clrTextBk);
		dc.DrawText(CString("Nessun elemento presente nella lista"),rc, DT_SINGLELINE|DT_CENTER);
		dc.SelectObject(oft);
		dc.SetBkMode(obk);
		dc.SetTextColor(ocrt);
		if (dwFlag&fScrollBarAlways) EnableScrollBar(SB_HORZ, ESB_DISABLE_BOTH);
	}
	else 
	{
		if (dwFlag&fScrollBarAlways) 
		{
			CRect rcAllLabels;
			GetItemRect(0,rcAllLabels,LVIR_BOUNDS);
			EnableScrollBar(SB_HORZ, rcAllLabels.Width() < m_cxClient ? ESB_DISABLE_BOTH : ESB_ENABLE_BOTH);
		}
	}
}

int CGfxListCtrl::HitTestEx(CPoint & point, int * col) const
{
	int colnum = 0;
	int row = HitTest(point, NULL);
	
	if (col) *col = 0;
	if ((GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT) return row;
	row = GetTopIndex();
	int bottom = row + GetCountPerPage();
	if (bottom > GetItemCount()) bottom = GetItemCount();
	int nColumnCount = GetColumnCount();
	for( ;row <=bottom;row++)
	{
		CRect rect;
		GetItemRect(row, &rect, LVIR_BOUNDS);
		if (rect.PtInRect(point))
		{
			for (colnum = 0; colnum < nColumnCount; colnum++)
			{
				int colwidth = GetColumnWidth(colnum);
				if (point.x >= rect.left && point.x <= (rect.left + colwidth))
				{
					if (col) *col = colnum;
					return row;
				}
				rect.left += colwidth;
			}
		}
	}
	return -1;
}

void CGfxListCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CListCtrl::OnLButtonUp(nFlags, point);
}

CGfxInCombo * CGfxListCtrl::ComboSubLabel(int nItem, int nCol, bool bEditable, bool bClick)
{
	if (!EnsureVisible(nItem, TRUE)) return NULL;

	EnsureSubItemVisible(nCol);
	int nColumnCount = GetColumnCount();
	int iColWidth = GetColumnWidth(nCol);
	if (nCol >= nColumnCount || iColWidth < 5) return NULL;

	int offset = 0;
	for (int i = 0; i < nCol; i++) offset += GetColumnWidth(i);

	CRect rect;
	GetItemRect(nItem, &rect, LVIR_BOUNDS);
	rect.bottom -= iAutoPreviewHeight;
	rect.top ++;
	rect.bottom -= 2;

	CRect rcClient;
	GetClientRect(&rcClient);
	LV_COLUMN lvcol;
	lvcol.mask = LVCF_FMT;
	GetColumn(nCol, &lvcol);
	DWORD dwStyle = 0;

	rect.left += offset+OFFSET_OTHER;//+4;
	rect.right = rect.left + GetColumnWidth(nCol)- OFFSET_OTHER;// - 3 ;
	if (rect.right > rcClient.right) rect.right = rcClient.right;

	dwStyle |= WS_CHILD|WS_VISIBLE;


	LXHDREX	lxhd;

	lxhd.iNotifyCode = NTEX_COMBOREQUEST;
	lxhd.CtrlId = iCtrlId < 0 ? GetDlgCtrlID() : iCtrlId;
	lxhd.iItem = nItem;
	lxhd.iSubItem = GetColumnIndex(nCol);
	lxhd.dwFlag = 0;
	lxhd.dwItemData = GetItemData(nItem);
	lxhd.dwMask = LXHDREX::exComboArray;

	GetItemTextEx(nItem, nCol, lxhd.csText, &(lxhd.dwItemData));

	lxhd.pComboArray = new CStringArray;
	ASSERT(lxhd.pComboArray);
	if (!SendInfoExMsg(&lxhd))
	{
		ASSERT(lxhd.pComboArray);
		delete lxhd.pComboArray;
		return NULL;
	}

	CGfxInCombo * pCombo = new CGfxInCombo(nItem, nCol, lxhd.csText, lxhd.pComboArray, bEditable, bClick);

	pCombo->bLightBorder = pCategoryManager == NULL;

	if (dwFlag&fExInfo)
	{
		lxhd.iNotifyCode = NTEX_ITEMINFO;

		CWnd * pWnd = GetReciper();
		if (SendInfoExMsg(&lxhd))
		{
			if (lxhd.dwFlag&LXHDREX::exHFont) pCombo->hFontHandle = lxhd.hfText;
			else if (lxhd.dwFlag&LXHDREX::exBold) pCombo->hFontHandle = (HFONT) ftBold.GetSafeHandle();
			else if (lxhd.dwFlag&LXHDREX::exItalic) pCombo->hFontHandle = (HFONT) ftItalic.GetSafeHandle();
			else if (lxhd.dwFlag&LXHDREX::exUnderline) pCombo->hFontHandle = (HFONT) ftUnderline.GetSafeHandle();
			else pCombo->hFontHandle = (HFONT) ftNormal.GetSafeHandle();

			if (lxhd.dwFlag&LXHDREX::exTextColor) pCombo->crColor = lxhd.crText;
		}
	}
	// defie IDC_IPEDIT as you want; is a control id
	pCombo->Create(dwStyle, rect, this, IDC_IPEDIT);

	return pCombo;
}


CRichEditCtrl * CGfxListCtrl::EditSubLabel(int nItem, int nCol, bool bClick)
{
	if (!EnsureVisible(nItem, TRUE)) return NULL;

	EnsureSubItemVisible(nCol);

	int nColumnCount = GetColumnCount();
	int iColWidth = GetColumnWidth(nCol);
	if (nCol >= nColumnCount || iColWidth < 5) return NULL;

	int offset = 0;
	for (int i = 0; i < nCol; i++) offset += GetColumnWidth(i);

	CRect rect;
	GetItemRect(nItem, &rect, LVIR_BOUNDS);

	rect.bottom -= iAutoPreviewHeight;

	rect.top ++;
	rect.bottom -= 2;

	CRect rcClient;
	GetClientRect(&rcClient);

	LV_COLUMN lvcol;
	lvcol.mask = LVCF_FMT;
	GetColumn(nCol, &lvcol);
	DWORD dwStyle = WS_CHILD|WS_VISIBLE;
	if ((lvcol.fmt&LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT) dwStyle |= ES_LEFT;
	else if ((lvcol.fmt&LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT) dwStyle |= ES_RIGHT|ES_MULTILINE;
	else dwStyle |= ES_CENTER|ES_MULTILINE;

	rect.left += offset+OFFSET_OTHER;//+4;
	rect.right = rect.left + GetColumnWidth(nCol)- OFFSET_OTHER- OFFSET_OTHER;// - 3 ;
	if (rect.right > rcClient.right) rect.right = rcClient.right;

	DWORD dwData = GetItemData(nItem);

	CString csItem;
	GetItemTextEx(nItem, nCol, csItem, &dwData);


	CRichEditCtrl *pEdit = new CGfxInEdit(nItem, nCol, csItem, bClick);
	pEdit->Create(dwStyle, rect, this, IDC_IPEDIT);

	LXHDREX	lxhd;

	if (dwFlag&fExInfo)
	{
		lxhd.iNotifyCode = NTEX_ITEMINFO;
		lxhd.CtrlId = iCtrlId < 0 ? GetDlgCtrlID() : iCtrlId;
		lxhd.iItem = nItem;
		lxhd.iSubItem = GetColumnIndex(nCol);
		lxhd.dwFlag = 0;
		lxhd.dwItemData = dwData;

		if (SendInfoExMsg(&lxhd))
		{
			if (lxhd.dwFlag&LXHDREX::exHFont) pEdit->SendMessage(WM_SETFONT, (WPARAM) lxhd.hfText, MAKELPARAM(FALSE, 0));
			else if (lxhd.dwFlag&LXHDREX::exBold) pEdit->SendMessage(WM_SETFONT, (WPARAM) ftBold.GetSafeHandle(), MAKELPARAM(FALSE, 0));
			else if (lxhd.dwFlag&LXHDREX::exItalic) pEdit->SendMessage(WM_SETFONT, (WPARAM) ftItalic.GetSafeHandle(), MAKELPARAM(FALSE, 0));
			else if (lxhd.dwFlag&LXHDREX::exUnderline) pEdit->SendMessage(WM_SETFONT, (WPARAM) ftUnderline.GetSafeHandle(), MAKELPARAM(FALSE, 0));
			else pEdit->SendMessage(WM_SETFONT, (WPARAM) ftNormal.GetSafeHandle(), MAKELPARAM(FALSE, 0));

			if (lxhd.dwFlag&LXHDREX::exTextColor) 
			{
				CHARFORMAT chf;
				chf.cbSize = sizeof(CHARFORMAT);
				chf.crTextColor = lxhd.crText;
				chf.dwMask = CFM_COLOR;

				CHARRANGE cr;
				pEdit->GetSel(cr);

				pEdit->SetSel(0,-1);
				pEdit->SetDefaultCharFormat(chf);
				pEdit->SetSelectionCharFormat(chf);

				pEdit->SetSel(cr);
			}
		}
	}
	return pEdit;
}

void CGfxListCtrl::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (GetFocus() != this) SetFocus();

	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	int index, colnum;
	if ((index = HitTestEx(point, &colnum)) != -1)
	{
		int cate = -1;
		if (pCategoryManager != NULL) 
		{
			cate = pCategoryManager->IsListItemACategory(GetItemData(index));
			if (cate >= 0)
			{
				if (colnum == 0)
				{
					if (pCategoryManager->pCategory[cate].bExpanded)
					{
						pCategoryManager->RemoveCategoryItems(cate, index, this);
						CRect rcAllLabels;
						GetItemRect(index,rcAllLabels,LVIR_BOUNDS);
						CRect rc;
						GetClientRect(&rc);
						if (rc.right > rcAllLabels.right)
						{
							rc.left = rcAllLabels.right;
							rc.top = rcAllLabels.bottom;
							InvalidateRect(rc, true);
						}
					}
					else
					{
						pCategoryManager->FillCategoryItems(cate, index, this);
					}

					pCategoryManager->pCategory[cate].bExpanded = !(pCategoryManager->pCategory[cate].bExpanded);

					CRect rcLittleBox;
					GetSubItemRect(index, 0, rcLittleBox);
					rcLittleBox.bottom ++;
					rcLittleBox.right ++;
					InvalidateRect(rcLittleBox, false);



					if (dwFlag&fScrollBarAlways) 
					{
						ShowScrollBar(SB_BOTH);
						int iPageItem = GetCountPerPage();
						int iItemCount = GetItemCount();
						if (iItemCount < iPageItem) EnableScrollBar(SB_VERT, ESB_DISABLE_BOTH);
						else EnableScrollBar(SB_VERT, ESB_ENABLE_BOTH);

						CRect rcAllLabels;
						GetItemRect(0,rcAllLabels,LVIR_BOUNDS);

						EnableScrollBar(SB_HORZ, rcAllLabels.Width() < m_cxClient ? ESB_DISABLE_BOTH : ESB_ENABLE_BOTH);
					}

					*pResult = 1;
					return;
				}
			}
		}


		if (iSubItemFocus != colnum)
		{
			CRect src;
			GetSubItemRect(index, iSubItemFocus, src);
			InvalidateRect(src);
			iSubItemFocus = colnum;
			GetSubItemRect(index, iSubItemFocus, src);
			InvalidateRect(src);
		}
		UINT flag = LVIS_FOCUSED;
		if ((GetItemState(index, flag) & flag) == flag)
		{
			if (cate < 0)
			{
				int irealcol = GetColumnIndex(colnum);
				if (dwhEdit&(1 << irealcol)) EditSubLabel(index, colnum);
				else if (dwhCombo&(1 << irealcol)) ComboSubLabel(index, colnum);
				else if (dwhComboEx&(1 << irealcol)) ComboSubLabel(index, colnum, true);
			}
		}
		else 
		{
			SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);
		}
	}
	
	*pResult = 1;
}

void CGfxListCtrl::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM	*plvItem = &pDispInfo->item;
	*pResult = 0;

	if (plvItem->pszText == NULL) return;

	if (dwFlag & fAllowMultiChange && GetSelectedCount() > 1)
	{
		{
			LXHDREX	lxhd;
			lxhd.iNotifyCode = NTEX_SETTEXT;
			lxhd.CtrlId = iCtrlId < 0 ? GetDlgCtrlID() : iCtrlId;
			lxhd.dwFlag = 0;
			int idx = GetNextItem(-1, LVNI_SELECTED);
			while (idx >= 0)
			{
				lxhd.iItem = idx;
				lxhd.iSubItem = GetColumnIndex(plvItem->iSubItem);
				lxhd.dwItemData = GetItemData(idx);
				lxhd.csText = plvItem->pszText;
				
				if (SendInfoExMsg(&lxhd)) ModifyItemEx(lxhd.iItem, plvItem->iSubItem, lxhd.dwItemData, lxhd.csText);
				else ModifyItemEx(lxhd.iItem, plvItem->iSubItem, lxhd.dwItemData);

				idx = GetNextItem(idx, LVNI_SELECTED);
			}
			SetFocus();
			return;
		}
	}
	if (plvItem->pszText != NULL)
	{
		LXHDREX	lxhd;
		lxhd.iNotifyCode = NTEX_SETTEXT;
		lxhd.CtrlId = iCtrlId < 0 ? GetDlgCtrlID() : iCtrlId;
		lxhd.iItem = plvItem->iItem;
		lxhd.iSubItem = GetColumnIndex(plvItem->iSubItem);
		lxhd.dwFlag = 0;
		lxhd.dwItemData = GetItemData(plvItem->iItem);
		lxhd.csText = plvItem->pszText;

		if (SendInfoExMsg(&lxhd)) 
			ModifyItemEx(lxhd.iItem, plvItem->iSubItem, lxhd.dwItemData, lxhd.csText);
		else ModifyItemEx(lxhd.iItem, plvItem->iSubItem, lxhd.dwItemData);
	}
}

void CGfxListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if( GetFocus() != this ) SetFocus();
	if (dwFlag & fCellToolTip && wndToolTip.IsWindowVisible()) wndToolTip.ShowWindow(SW_HIDE);
	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CGfxListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if( GetFocus() != this ) SetFocus();
	if (dwFlag & fCellToolTip && wndToolTip.IsWindowVisible()) wndToolTip.ShowWindow(SW_HIDE);
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

bool CGfxListCtrl::EnsureSubItemVisible(const int iSubItem)
{
	int nColumnCount = GetColumnCount();
	int iColWidth = GetColumnWidth(iSubItem);
	if (iSubItem >= nColumnCount || iColWidth < 5) return false;

	int offset = 0;
	for (int i = 0; i < iSubItem; i++) offset += GetColumnWidth(i);

	CRect rect, subRect;
	GetItemRect(0, &rect, LVIR_BOUNDS);
	subRect.SetRect(offset + rect.left, 0, offset + iColWidth + rect.left, 0);

	CRect rcClient;
	GetClientRect(&rcClient);

	if (subRect.left < rcClient.left)
	{
		CSize sz(rcClient.left + subRect.left, 0);
		Scroll(sz);
		return true;
	}
	else if (subRect.right > rcClient.right)
	{
		CSize sz(subRect.right - rcClient.right, 0);
		Scroll(sz);
		return true;
	}
	return true;
}

void CGfxListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if( GetFocus() != this ) SetFocus();
	CListCtrl::OnLButtonDown(nFlags, point);
}

void CGfxListCtrl::GetSubItemRect(const int nItem, const int nCol, CRect & rcItem)
{
//	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
	int nColumnCount = GetColumnCount();//pHeader->GetItemCount();
	int iColWidth = GetColumnWidth(nCol);
	if (nCol >= nColumnCount || iColWidth < 5) return;

	int offset = 0;
	for (int i = 0; i < nCol; i++) offset += GetColumnWidth(i);

	CRect rect;
	GetItemRect(nItem, &rect, LVIR_BOUNDS);

	rect.bottom --;
	rect.left += offset;
	rect.right = rect.left + GetColumnWidth(nCol);
	rcItem = rect;
}

LRESULT CGfxListCtrl::OnUserTab(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)
	{
		int nColumnCount = GetColumnCount();
		int col = ((int *)lParam)[1]+1;
		int row = ((int *)lParam)[0];
		if (col >= nColumnCount)
		{
			col = 0;
			row ++;
			if (row >= GetItemCount()) return 0L;
		}

		bool bFind = dwhEdit&(1 << GetColumnIndex(col)) || dwhCombo&(1 << GetColumnIndex(col)) || dwhComboEx&(1 << GetColumnIndex(col));
		while (!bFind)
		{
			col ++;
			if (col >= nColumnCount)
			{
				col = 0;
				row ++;
				if (row >= GetItemCount()) return 0L;
			}
			bFind = dwhEdit&(1 << GetColumnIndex(col)) || dwhCombo&(1 << GetColumnIndex(col)) || dwhComboEx&(1 << GetColumnIndex(col));
		}
		iSubItemFocus = col;

		if (GetSelectedCount() == 1) 
		{
			int sidx = GetNextItem(-1, LVNI_SELECTED);
			if (sidx != row) RemoveAllSelection();
		}
		SetItemState(row, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);

		if (pCategoryManager == NULL || pCategoryManager->IsListItemACategory(GetItemData(row)) < 0)
		{
			int irealcol = GetColumnIndex(col);
			if (dwhEdit&(1 << irealcol)) EditSubLabel(row, col, false);
			else if (dwhCombo&(1 << irealcol)) ComboSubLabel(row, col, false, false);
			else if (dwhComboEx&(1 << irealcol)) ComboSubLabel(row, col, true, false);
		}
	}
	if (wParam == 1) // Prev Tab
	{
		int nColumnCount = GetColumnCount();
		int col = ((int *)lParam)[1] - 1;
		int row = ((int *)lParam)[0];
		if (col < 0)
		{
			col = nColumnCount-1;
			row --;
			if (row < 0) return 0L;
		}
		bool bFind = dwhEdit&(1 << GetColumnIndex(col)) || dwhCombo&(1 << GetColumnIndex(col)) || dwhComboEx&(1 << GetColumnIndex(col));
		while (!bFind)
		{
			col --;
			if (col < 0)
			{
				col = nColumnCount-1;
				row --;
				if (row < 0) return 0L;
			}
			bFind = dwhEdit&(1 << GetColumnIndex(col)) || dwhCombo&(1 << GetColumnIndex(col)) || dwhComboEx&(1 << GetColumnIndex(col));
		}
		iSubItemFocus = col;

		if (GetSelectedCount() == 1) 
		{
			int sidx = GetNextItem(-1, LVNI_SELECTED);
			if (sidx != row) RemoveAllSelection();
		}
		SetItemState(row, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);

		if (pCategoryManager == NULL || pCategoryManager->IsListItemACategory(GetItemData(row)) < 0)
		{
			int irealcol = GetColumnIndex(col);
			if (dwhEdit&(1 << irealcol)) EditSubLabel(row, col, false);
			else if (dwhCombo&(1 << irealcol)) ComboSubLabel(row, col, false, false);
			else if (dwhComboEx&(1 << irealcol)) ComboSubLabel(row, col, true, false);
		}

		return (LRESULT) 0L;
	}
	if (wParam == 2) // Left
	{
		if (iSubItemFocus > 0) iSubItemFocus--;
		int sidx = GetNextItem(-1, LVNI_SELECTED);
		if (sidx >= 0)
		{
			CRect rect;
			GetItemRect(sidx, &rect, LVIR_BOUNDS);
			rect.bottom --;
			InvalidateRect(rect);
			EnsureSubItemVisible(iSubItemFocus);
		}
	}
	if (wParam == 3) // Right
	{
		int nColumnCount = GetColumnCount();

		if (iSubItemFocus < nColumnCount - 1) iSubItemFocus++;
		int sidx = GetNextItem(-1, LVNI_SELECTED);
		if (sidx >= 0)
		{
			CRect rect;
			GetItemRect(sidx, &rect, LVIR_BOUNDS);
			rect.bottom --;
			InvalidateRect(rect);
			EnsureSubItemVisible(iSubItemFocus);
		}
	}
	if (wParam == 4) // Up
	{
		int sidx = GetNextItem(-1, LVNI_FOCUSED);
		if (sidx >= 0)
		{
			sidx --;
			if (sidx >= 0)
			{
				if (GetSelectedCount() == 1) SetItemState(sidx+1, 0, LVIS_SELECTED | LVIS_FOCUSED);
				SetItemState(sidx, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);
			}
		}
	}
	if (wParam == 5) // Down
	{
		int sidx = GetNextItem(-1, LVNI_FOCUSED);
		if (sidx >= 0)
		{
			sidx ++;
			if (sidx < GetItemCount() - 1)
			{
				if (GetSelectedCount() == 1) SetItemState(sidx-1, 0, LVIS_SELECTED | LVIS_FOCUSED);
				SetItemState(sidx, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);
			}
		}
	}
	return 0L;
}

void CGfxListCtrl::RemoveAllSelection()
{
	int idx = GetNextItem(-1, LVNI_SELECTED);
	while (idx >= 0)
	{
		SetItemState(idx, 0, LVIS_SELECTED | LVIS_FOCUSED);
		idx = GetNextItem(idx, LVNI_SELECTED);
	}
}

void CGfxListCtrl::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	if (dwFlag & fCellToolTip && wndToolTip.IsWindowVisible()) wndToolTip.ShowWindow(SW_HIDE);
	
	if (pLVKeyDow->wVKey == VK_LEFT)
	{
		if (iSubItemFocus > 0) iSubItemFocus--;
		else { *pResult = 1; return; }
		int sidx = GetNextItem(-1, LVNI_FOCUSED|LVNI_FOCUSED);
		if (sidx >= 0)
		{
			if (EnsureSubItemVisible(iSubItemFocus))
			{
				CRect src;
				GetSubItemRect(sidx, iSubItemFocus, src);
				InvalidateRect(src);
				GetSubItemRect(sidx, iSubItemFocus+1, src);
				InvalidateRect(src);
			}
			*pResult = 1;
			return;
		}
	}
	if (pLVKeyDow->wVKey == VK_RIGHT)
	{
		int nColumnCount = GetColumnCount();

		if (iSubItemFocus < nColumnCount - 1) iSubItemFocus++;
		else { *pResult = 1; return; }

		int sidx = GetNextItem(-1, LVNI_FOCUSED|LVNI_FOCUSED);
		if (sidx >= 0)
		{
			if (EnsureSubItemVisible(iSubItemFocus))
			{
				CRect src;
				GetSubItemRect(sidx, iSubItemFocus, src);
				InvalidateRect(src);
				GetSubItemRect(sidx, iSubItemFocus-1, src);
				InvalidateRect(src);
			}
			*pResult = 1;
			return;
		}
	}
	*pResult = 0;
}

BOOL CGfxListCtrl::PreTranslateMessage(MSG* pMsg) 
{
	if (dwFlag & fReturnModify || dwFlag & fReturnDblClk)
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			if (pMsg->wParam == VK_RETURN)
			{
				int sidx = GetNextItem(-1, LVNI_SELECTED);
				
				if (pCategoryManager != NULL)
				{
					int cate = pCategoryManager->IsListItemACategory(GetItemData(sidx));
					if (cate >= 0)
					{
						if (pCategoryManager->pCategory[cate].bExpanded)
						{
							pCategoryManager->RemoveCategoryItems(cate, sidx, this);
							CRect rcAllLabels;
							GetItemRect(sidx,rcAllLabels,LVIR_BOUNDS);
							CRect rc;
							GetClientRect(&rc);
							if (rc.right > rcAllLabels.right)
							{
								rc.left = rcAllLabels.right;
								rc.top = rcAllLabels.bottom;
								InvalidateRect(rc, true);
							}
						}
						else
						{
							pCategoryManager->FillCategoryItems(cate, sidx, this);
						}

						pCategoryManager->pCategory[cate].bExpanded = !(pCategoryManager->pCategory[cate].bExpanded);

						CRect rcLittleBox;
						GetSubItemRect(sidx, 0, rcLittleBox);
						rcLittleBox.bottom ++;
						rcLittleBox.right ++;
						InvalidateRect(rcLittleBox, false);

						if (dwFlag&fScrollBarAlways) 
						{
							ShowScrollBar(SB_BOTH);
							int iPageItem = GetCountPerPage();
							int iItemCount = GetItemCount();
							if (iItemCount < iPageItem) EnableScrollBar(SB_VERT, ESB_DISABLE_BOTH);
							else EnableScrollBar(SB_VERT, ESB_ENABLE_BOTH);

							CRect rcAllLabels;
							GetItemRect(0,rcAllLabels,LVIR_BOUNDS);

							EnableScrollBar(SB_HORZ, rcAllLabels.Width() < m_cxClient ? ESB_DISABLE_BOTH : ESB_ENABLE_BOTH);
						}

						return true;
					}
				}

				if (sidx >= 0 && iSubItemFocus >= 0 && dwFlag & fReturnModify)
				{
//					if (pCategoryManager == NULL || pCategoryManager->IsListItemACategory(GetItemData(sidx)) < 0)
					{
						int irealcol = GetColumnIndex(iSubItemFocus);
						if (dwhEdit&(1 << irealcol)) 
						{
							EditSubLabel(sidx, iSubItemFocus, false);
							return true;
						}
						else if (dwhCombo&(1 << irealcol)) 
						{
							ComboSubLabel(sidx, iSubItemFocus, false, false);
							return true;
						}
						else if (dwhComboEx&(1 << irealcol)) 
						{
							ComboSubLabel(sidx, iSubItemFocus, true, false);
							return true;
						}
					}
				}
				if (dwFlag & fReturnDblClk)
				{
					NMHDR nh;
					nh.hwndFrom = GetSafeHwnd();
					nh.idFrom = iCtrlId < 0 ? GetDlgCtrlID() : iCtrlId;
					nh.code = NM_DBLCLK;
					GetReciper()->SendMessage(WM_NOTIFY, nh.idFrom, (LPARAM) &nh);
					return true;
				}
			}
		}
	}
	
	return CListCtrl::PreTranslateMessage(pMsg);
}

void CGfxListCtrl::SetSubItemImage(const int iItem, const int iSubItem, const int iIndex)
{
	if (dwFlag&fSubItemImages)
	{
		ASSERT(dwhImages & (1 << iSubItem));
		CString cs;
		cs.Format("%d", iIndex);
		SetItemText(iItem, iSubItem, cs);
	}
}


void CGfxListCtrl::SetHeaderImageList(CImageList * pIma)
{
	wndHeader.pImageList = pIma;
}

void CGfxListCtrl::SetColumnImage(const int iCol, const int iImage)
{
	ASSERT(wndHeader.GetSafeHwnd());

	CString cs;
	cs.Format("%d_", iImage);

	HD_ITEM hditem;
	hditem.mask = HDI_FORMAT;
	wndHeader.GetItem(iCol, &hditem );
	hditem.fmt |= HDF_OWNERDRAW;
	hditem.mask |= HDI_TEXT;
	hditem.pszText = cs.LockBuffer();
	hditem.cchTextMax = cs.GetLength();
	wndHeader.SetItem(iCol, &hditem );
	cs.UnlockBuffer();
}

void CGfxListCtrl::ResetScrollBar()
{
	ShowScrollBar(SB_BOTH);
	int iPageItem = GetCountPerPage();
	int iItemCount = GetItemCount();
	if (iItemCount < iPageItem) EnableScrollBar(SB_VERT, ESB_DISABLE_BOTH);
	else EnableScrollBar(SB_VERT, ESB_ENABLE_BOTH);

	if (iItemCount > 0)
	{
		CRect rcAllLabels;
		GetItemRect(0,rcAllLabels,LVIR_BOUNDS);
		EnableScrollBar(SB_HORZ, rcAllLabels.Width() < m_cxClient ? ESB_DISABLE_BOTH : ESB_ENABLE_BOTH);
	}
	else EnableScrollBar(SB_HORZ, ESB_DISABLE_BOTH);
}


int CGfxListCtrl::GetColumnCount() const
{
	CHeaderCtrl* pHeader = (CHeaderCtrl*) GetDlgItem(0);
	return pHeader ? pHeader->GetItemCount() : 0;
}

bool CGfxListCtrl::DoCopyInClipboard(const bool bOnlySel)
{
	CString source; 
	CWaitCursor tom;
	int nCol = GetColumnCount();
	if (nCol < 0) return false;

	if (bOnlySel)
	{
		if (GetSelectedCount() > 0)
		{
			int idx = GetNextItem(-1, LVNI_SELECTED);
			while (idx >= 0)
			{
				if (source != "") source += '\n';
				for (int t = 0; t < nCol; t ++)
				{
					CString item;
					GetItemTextEx(idx, t, item, NULL);
//					item = GetItemText(idx, t);
					if (t > 0) source += '\t';
					source += item;			
				}
				idx = GetNextItem(idx, LVNI_SELECTED);
			}
		}
	}
	else
	{
		int max = 10;//GetItemCount();
		for (int idx = 0; idx < max; idx ++)
		{
			if (source != "") source += '\n';
			for (int t = 0; t < nCol; t ++)
			{
				CString item;
//				item = GetItemText(idx, t);
				GetItemTextEx(idx, t, item, NULL);
				if (t > 0) source += '\t';
				source += item;			
			}
		}
	}
	if(source != "" && OpenClipboard())
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, source.GetLength()+1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(source));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
		return true;
	}
	return false;
}

void CGfxListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if (pCategoryManager) lpMeasureItemStruct->itemHeight = iItemHeightCategory;//17;
	else lpMeasureItemStruct->itemHeight = iItemHeight + iAutoPreviewHeight;//16;
}

void CGfxListCtrl::SetItemHeight(const int iHeight, const bool bCategory)
{
	if (bCategory) iItemHeightCategory = iHeight;
	else iItemHeight = iHeight;

	if (GetSafeHwnd())
	{
		CRect rc;
		GetWindowRect( &rc );
		WINDOWPOS wp;
		wp.hwnd = m_hWnd;
		wp.cx = rc.Width();	
		wp.cy = rc.Height();
		wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
		SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
	}
}

BOOL CGfxListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	switch (((NMHDR*)lParam)->code)        
	{   
		case HDN_BEGINTRACKW:
		case HDN_BEGINTRACKA: 
			{
				HD_NOTIFY * phd = (HD_NOTIFY *) lParam;

				if (wndHeader.dwNoResizeColumn & (1 << GetColumnIndex(phd->iItem)))
				{
					*pResult = TRUE;
					return TRUE;
				}
				if( GetFocus() != this ) SetFocus();
			}
			break;
		case HDN_ITEMCHANGINGW:
		case HDN_ITEMCHANGINGA: 
			{
				HD_NOTIFY * phd = (HD_NOTIFY *) lParam;
				if( m_bitmap.m_hObject != NULL )
				{
					CRect rcClient;
					GetClientRect(&rcClient);
					CPoint pt(GetMessagePos());
					ScreenToClient(&pt);
					rcClient.left = pt.x;
					InvalidateRect(&rcClient);
				}
				if (phd->pitem->cxy < 16 && phd->iItem != 0)
				{
					*pResult = TRUE;
					return TRUE;
				}
			}
			break;
/*-TE-
		case NM_RCLICK:
			if (wParam == 0)
			{
				CPoint pt(GetMessagePos());
				CPoint spt(pt);
				CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
				pHeader->ScreenToClient(&pt);
				CRect rcCol;
				iInternal1 = -1;
				for( int i=0; Header_GetItemRect(pHeader->m_hWnd, i, &rcCol); i++ )
				{
					if( rcCol.PtInRect( pt ) )
					{
						iInternal1 = i;
						break;
					}
				}

				CGfxPopupMenu cMenu;
				cMenu.CreatePopupMenu();

				cMenu.AppendMenu(MF_STRING, ID_GFX_SORTASC, _SORTASC_TEXT);
				cMenu.AppendMenu(MF_STRING, ID_GFX_SORTDESC, _SORTDESC_TEXT);
				cMenu.AppendMenu(MF_SEPARATOR);
				cMenu.AppendMenu(MF_STRING, ID_GFX_CUSTOMIZEHEAD, _CUSTHEAD_TEXT);
				cMenu.AppendMenu(MF_STRING, ID_GFX_FORMATHEADER, _FORMATHEAD_TEXT);
				
				cMenu.LoadToolBarResource(IDR_LISTMENUBMP);
				cMenu.RemapMenu(&cMenu);
				cMenu.EnableMenuItems(&cMenu, this);

				cMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, spt.x, spt.y, this);

				cMenu.DestroyMenu();
			}
*/
	}	
	return CListCtrl::OnNotify(wParam, lParam, pResult);
}

int CGfxListCtrl::GetColumnIndex(const int iCol) const
{
	LV_COLUMN lv;
	lv.mask = LVCF_SUBITEM;
	GetColumn(iCol, &lv);
	return lv.iSubItem;
}

void CGfxListCtrl::DragColumn(int &source, int &dest)
{
	if (GetFocus() != this) SetFocus();

	if (source == 0) return;
	if (dest == 0) dest = 1;
	if (source == dest) return;

	SetRedraw(false);

	TCHAR sColText[160];

	LV_COLUMN	lv_col;
	lv_col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lv_col.pszText = sColText;
	lv_col.cchTextMax = 159;
	GetColumn(source, &lv_col);

	InsertColumn(dest, &lv_col);

	HD_ITEM hditem;
	hditem.mask = HDI_FORMAT;
	wndHeader.GetItem(dest, &hditem);
	hditem.fmt |= HDF_OWNERDRAW;
	wndHeader.SetItem(dest, &hditem );

	// Adjust source col number since it might have changed&nbsp;
	// because a new column was inserted
	if (source > dest) source++;

	// Moving a col to position 0 is a special case
	if (dest == 0)
		for (int i = GetItemCount()-1; i > -1 ; i--)
			SetItemText(i, 0, LPSTR_TEXTCALLBACK);

	
	// Copy sub item from source to dest
	for (int i = GetItemCount()-1; i > -1 ; i--)
		SetItemText(i, dest, LPSTR_TEXTCALLBACK);

	// Delete the source column, but not if it is the first
	if (source != 0)
		DeleteColumn(source);
	else
	{
		// If source col is 0, then copy col# 1 to col#0
		// and then delete col# 1
		int isi = lv_col.iSubItem;
		GetColumn(1, &lv_col);
		lv_col.iSubItem = isi;
		SetColumn(0, &lv_col);
		for (int i = GetItemCount()-1; i > -1 ; i--)
			SetItemText(i, 0, LPSTR_TEXTCALLBACK);//GetItemText( i, 1));
		DeleteColumn(1);

		lv_col.mask = LVCF_SUBITEM;
		lv_col.iSubItem = isi;
		SetColumn(0, &lv_col);
		GetColumn(0, &lv_col);
	}
	SetRedraw(true);

	Invalidate();
}

void CGfxListCtrl::EnableColumnDrag(const bool bEnableDrag)
{
	wndHeader.bEnableDrag = bEnableDrag;
}

/*-TE-
void CGfxListCtrl::OnGfxCustomizehead() 
{
	if (pManager == NULL) return;
	pManager->RetrieveColumnData(this);

	CGfxCustomizeColumnDlg dlg;
	dlg.pManager = pManager;
	if (IDOK == dlg.DoModal())
	{
		pManager->SetupColumnData(this, true);
//		Invalidate();
	}
}
*/

void CGfxListCtrl::OnUpdateGfxCustomizehead(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pManager != NULL && bDaoBind == false);
}

/*-TE-
void CGfxListCtrl::OnGfxFormatheader() 
{
	if (pManager == NULL) return;
	pManager->RetrieveColumnData(this);

	CGfxFormatColumnDlg dlg;
	dlg.pManager = pManager;
	if (IDOK == dlg.DoModal())
	{
		pManager->SetupColumnData(this, true);
//		Invalidate();
	}
}
*/

void CGfxListCtrl::OnUpdateGfxFormatheader(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pManager != NULL && bDaoBind == false);
}

void CGfxListCtrl::OnGfxSortasc() 
{
	if (GetFocus() != this) SetFocus();

	if (iInternal1 >= 0 && iInternal1 < GetColumnCount())
	{
		if (dwFlag & fAutoSort)
		{
			if (pManager != NULL)
			{
				int col = pManager->FindColumnById(GetColumnIndex(iInternal1));
				if (col >= 0)
				{
					if (!(pManager->pColumnData[col].dwData&fhSortAble)) return;
				}
			}

			CWaitCursor tom;
/*-TE-
			if (bDaoBind && pRecordSet)
			{
				if (iInternal1 == 0) return;

				wndHeader.SetSortImage(iInternal1, true);

				if (pCategoryManager != NULL) pCategoryManager->ResetList(this);

				CDaoFieldInfo fieldinfo;
				pRecordSet->GetFieldInfo(iInternal1 - 1, fieldinfo);

				pRecordSet->m_strSort = fieldinfo.m_strName;
				pRecordSet->Requery();
				pRecordSet->MoveLast();
				Invalidate();
				if (pCategoryManager != NULL) pCategoryManager->SetupList(this);
			}
			else
*/
			{
				if (pCategoryManager != NULL) pCategoryManager->ResetList(this);
				wndHeader.SetSortImage(iInternal1, true);

				{
					CSortClass csc(this, iInternal1, dwhNumeric & (1 << GetColumnIndex(iInternal1)) ? true : false, dwhValute & (1 << GetColumnIndex(iInternal1)) ? true : false);
					csc.Sort(true);
				}
				
				if (pCategoryManager != NULL) pCategoryManager->SetupList(this);
				else
				{
					int idx = GetNextItem(-1, LVNI_SELECTED);
					if (idx >= 0) EnsureVisible(idx, false);
				}
			}
		}
	}
}

void CGfxListCtrl::OnUpdateGfxSortasc(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dwFlag & fAutoSort);
}

void CGfxListCtrl::OnGfxSortdesc() 
{
	if (GetFocus() != this) SetFocus();

	if (iInternal1 >= 0 && iInternal1 < GetColumnCount())
	{
		if (dwFlag & fAutoSort)
		{
			if (pManager != NULL)
			{
				int col = pManager->FindColumnById(GetColumnIndex(iInternal1));
				if (col >= 0)
				{
					if (!(pManager->pColumnData[col].dwData&fhSortAble)) return;
				}
			}

			CWaitCursor tom;
/*-TE-
			if (bDaoBind && pRecordSet)
			{
				if (iInternal1 == 0) return;

				wndHeader.SetSortImage(iInternal1, false);

				if (pCategoryManager != NULL) pCategoryManager->ResetList(this);

				CDaoFieldInfo fieldinfo;
				pRecordSet->GetFieldInfo(iInternal1 - 1, fieldinfo);

				pRecordSet->m_strSort = fieldinfo.m_strName;
				pRecordSet->m_strSort += " DESC";
				pRecordSet->Requery();
				pRecordSet->MoveLast();
				Invalidate();
				if (pCategoryManager != NULL) pCategoryManager->SetupList(this);
			}
			else
*/
			{
				if (pCategoryManager != NULL) pCategoryManager->ResetList(this);

				wndHeader.SetSortImage(iInternal1, false);

				{
					CSortClass csc(this, iInternal1, dwhNumeric & (1 << GetColumnIndex(iInternal1)) ? true : false, dwhValute & (1 << GetColumnIndex(iInternal1)) ? true : false);
					csc.Sort(false);
				}

				if (pCategoryManager != NULL) pCategoryManager->SetupList(this);
				else
				{
					int idx = GetNextItem(-1, LVNI_SELECTED);
					if (idx >= 0) EnsureVisible(idx, false);
				}
			}
		}
	}

}

void CGfxListCtrl::OnUpdateGfxSortdesc(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dwFlag & fAutoSort);
}

CGfxColumnManager * CGfxListCtrl::CreateColumnManager()
{
	ASSERT(pManager == NULL);
	if (pManager) delete pManager;
	pManager = new CGfxColumnManager;
	ASSERT(pManager);
	return pManager;
}

CGfxColumnManager * CGfxListCtrl::GetColumnManager()
{
	return pManager;
}

void CGfxListCtrl::SetupColumnData()
{
	ASSERT(pManager);
	if (pManager) pManager->SetupColumnData(this, true);
}

void CGfxListCtrl::RetrieveColumnData()
{
	ASSERT(pManager);
	if (pManager) pManager->RetrieveColumnData(this);
}

CGfxCategoryManager * CGfxListCtrl::CreateCategoryManager()
{
	ASSERT(pCategoryManager == NULL);
	pCategoryManager = new CGfxCategoryManager;
	return pCategoryManager;
}

CGfxCategoryManager * CGfxListCtrl::GetCategoryManager()
{
	return pCategoryManager;
}

void CGfxListCtrl::EnableCategoryView(const bool bEnab)
{
	if (GetFocus() != this) SetFocus();

	if (bEnab)
	{
		if (pCategoryManager == NULL) CreateCategoryManager();
		ASSERT(pCategoryManager);
		pCategoryManager->pCallBackOwner = GetParent();

/*-TE-
		if (bDaoBind && pRecordSet) 
		{
			ASSERT(m_fpDaoCategoryFun != NULL);
			pCategoryManager->SetDaoCategoryCallback(m_fpDaoCategoryFun);
		}
		else 
*/
		{
			ASSERT(m_fpCategoryFun != NULL);
			pCategoryManager->SetCategoryCallback(m_fpCategoryFun);
		}

		LV_COLUMN lvc;
		lvc.mask = LVCF_WIDTH | LVCF_SUBITEM;
		GetColumn(0, &lvc);
		if (lvc.iSubItem == 0 && lvc.cx == 0)
		{
			lvc.cx = 18;
			SetColumn(0, &lvc);
		}
		pCategoryManager->SetupList(this);
	}
	else
	{
		ASSERT(pCategoryManager);
		if (pCategoryManager == NULL) return;
		

		HD_ITEM hd_item;
		hd_item.mask = HDI_WIDTH|HDI_LPARAM;
		CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
		pHeader->GetItem(0, &hd_item);
		if (hd_item.lParam == 0 && hd_item.cxy == 18)
		{
			hd_item.cxy = 0;
			pHeader->SetItem(0, &hd_item);
		}
		pCategoryManager->ResetList(this);
		delete pCategoryManager;
		pCategoryManager = NULL;
	}
	CRect rc;
	GetWindowRect( &rc );
	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rc.Width();	
	wp.cy = rc.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);

	if (GetFocus() != this) SetFocus();
}

void CGfxListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if( GetFocus() != this ) SetFocus();

	if (pCategoryManager != NULL) 
	{
		int index, colnum;
		if ((index = HitTestEx(point, &colnum)) != -1)
		{
			int cate = pCategoryManager->IsListItemACategory(GetItemData(index));
			if (cate >= 0)
			{
				if (colnum > 0)
				{
					if (pCategoryManager->pCategory[cate].bExpanded)
					{
						pCategoryManager->RemoveCategoryItems(cate, index, this);
						CRect rcAllLabels;
						GetItemRect(index,rcAllLabels,LVIR_BOUNDS);
						CRect rc;
						GetClientRect(&rc);
						if (rc.right > rcAllLabels.right)
						{
							rc.left = rcAllLabels.right;
							rc.top = rcAllLabels.bottom;
							InvalidateRect(rc, true);
						}
					}
					else
					{
						pCategoryManager->FillCategoryItems(cate, index, this);
					}

					pCategoryManager->pCategory[cate].bExpanded = !(pCategoryManager->pCategory[cate].bExpanded);

					CRect rcLittleBox;
					GetSubItemRect(index, 0, rcLittleBox);
					rcLittleBox.bottom ++;
					rcLittleBox.right ++;
					InvalidateRect(rcLittleBox, false);

					if (dwFlag&fScrollBarAlways) 
					{
						ShowScrollBar(SB_BOTH);
						int iPageItem = GetCountPerPage();
						int iItemCount = GetItemCount();
						if (iItemCount < iPageItem) EnableScrollBar(SB_VERT, ESB_DISABLE_BOTH);
						else EnableScrollBar(SB_VERT, ESB_ENABLE_BOTH);

						CRect rcAllLabels;
						GetItemRect(0,rcAllLabels,LVIR_BOUNDS);

						EnableScrollBar(SB_HORZ, rcAllLabels.Width() < m_cxClient ? ESB_DISABLE_BOTH : ESB_ENABLE_BOTH);
					}

					return;
				}
			}
		}
	}
	CListCtrl::OnLButtonDblClk(nFlags, point);
}

void CGfxListCtrl::GetItemTextEx(const int idx, const int sub, CString & cs, const unsigned long * dwData)
{
	if (m_fpGetTextCallback)
	{
		(GetReciper()->*m_fpGetTextCallback)(idx, sub, dwData ? *dwData : GetItemData(idx), cs);
	}
	else
	{
		cs = GetItemText(idx, sub);
	}
}


int CGfxListCtrl::InsertItemEx(const int iIndex, const long lData)
{
	if (pCategoryManager != NULL) 
	{
		return pCategoryManager->InsertNewItem(this, lData);
	}

	static LV_ITEM lvi;
	lvi.mask = LVIF_TEXT|LVIF_PARAM;
	lvi.iItem = iIndex;
	lvi.iSubItem = 0;
	lvi.pszText = LPSTR_TEXTCALLBACK;
	lvi.lParam = lData;

	return (int) DefWindowProc(LVM_INSERTITEM, 0, (LPARAM) &lvi);
	
/*	int idx = InsertItem(iIndex, LPSTR_TEXTCALLBACK);
	SetItemData(idx, lData);
	return idx;*/
}


void CGfxListCtrl::DeleteItemEx(const int iIndex, const long lData)
{
	if (pCategoryManager != NULL) 
	{
		if (pCategoryManager->IsListItemACategory(iIndex) >= 0) return;

		LV_FINDINFO lfv;
		lfv.flags = LVFI_PARAM;
		lfv.lParam = lData;

		int idx = FindItem(&lfv, -1);
		while (idx >= 0)
		{
			DeleteItem(idx);
			idx = FindItem(&lfv, idx-1);
		}
		return;
	}
	DeleteItem(iIndex);
}

void CGfxListCtrl::ModifyItemEx(const int iIndex, const int iSubItem, const long lData)
{
	if (pCategoryManager != NULL) 
	{
		if (pCategoryManager->IsListItemACategory(iIndex) >= 0) return;

		LV_FINDINFO lfv;
		lfv.flags = LVFI_PARAM;
		lfv.lParam = lData;

		int idx = FindItem(&lfv, -1);
		while (idx >= 0)
		{
			SetItemText(idx, iSubItem, LPSTR_TEXTCALLBACK);
			idx = FindItem(&lfv, idx);
		}
		return;
	}
	SetItemText(iIndex, iSubItem, LPSTR_TEXTCALLBACK);
}

void CGfxListCtrl::ModifyItemEx(const int iIndex, const int iSubItem, const long lData, CString &cs)
{
	if (pCategoryManager != NULL) 
	{
		if (pCategoryManager->IsListItemACategory(iIndex) >= 0) return;

		LV_FINDINFO lfv;
		lfv.flags = LVFI_PARAM;
		lfv.lParam = lData;

		int idx = FindItem(&lfv, -1);
		while (idx >= 0)
		{
			SetItemText(idx, iSubItem, cs);
			idx = FindItem(&lfv, idx);
		}
		return;
	}
	SetItemText(iIndex, iSubItem, cs);
}

bool CGfxListCtrl::SetBkImage(UINT nIDResource)
{
	if (nIDResource == (UINT) -1)
	{
		if (m_bitmap.m_hObject != NULL) m_bitmap.DeleteObject();
		if (m_pal.m_hObject != NULL) m_pal.DeleteObject();
		Invalidate();
		return true;
	}

	return SetBkImage(MAKEINTRESOURCE(nIDResource)); 
}

bool CGfxListCtrl::SetBkImage(LPCTSTR lpszResourceName)
{
	if (m_bitmap.m_hObject != NULL) m_bitmap.DeleteObject();
	if (m_pal.m_hObject != NULL) m_pal.DeleteObject();
	
	
	HBITMAP hBmp = (HBITMAP):: LoadImage(AfxGetInstanceHandle(), lpszResourceName, IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION);

	if (hBmp == NULL) return false;

	m_bitmap.Attach(hBmp);
	BITMAP bm;
	m_bitmap.GetBitmap( &bm );
	m_cxBitmap = bm.bmWidth;
	m_cyBitmap = bm.bmHeight;

	if (cBackImage.GetSafeHandle()) cBackImage.DeleteImageList();

	
	cBackImage.Create(m_cxBitmap, m_cyBitmap, ILC_COLOR16, 1, 0);
	cBackImage.Add(&m_bitmap, (CBitmap *) NULL);




	// Create a logical palette for the bitmap
	DIBSECTION ds;
	BITMAPINFOHEADER &bmInfo = ds.dsBmih;
	m_bitmap.GetObject(sizeof(ds), &ds);

	int nColors = bmInfo.biClrUsed ? bmInfo.biClrUsed : 1 << bmInfo.biBitCount;

	// Create a halftone palette if colors > 256. 
	CClientDC dc(NULL);			// Desktop DC
	if (nColors > 256) m_pal.CreateHalftonePalette( &dc );
	else
	{
		// Create the palette

		RGBQUAD *pRGB = new RGBQUAD[nColors];
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		memDC.SelectObject( &m_bitmap );
		::GetDIBColorTable( memDC, 0, nColors, pRGB );

		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];

		pLP->palVersion = 0x300;
		pLP->palNumEntries = nColors;

		for( int i=0; i < nColors; i++)
		{
			pLP->palPalEntry[i].peRed = pRGB[i].rgbRed;
			pLP->palPalEntry[i].peGreen = pRGB[i].rgbGreen;
			pLP->palPalEntry[i].peBlue = pRGB[i].rgbBlue;
			pLP->palPalEntry[i].peFlags = 0;
		}

		m_pal.CreatePalette( pLP );

		delete[] pLP;
		delete[] pRGB;
	}
	Invalidate();
	return true;
}

BOOL CGfxListCtrl::OnQueryNewPalette() 
{
	CClientDC dc(this);
	if (dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE && m_pal.m_hObject != NULL)
	{
		dc.SelectPalette(&m_pal, FALSE);
		BOOL result = dc.RealizePalette();
		if (result) Invalidate();
		return result;
	}
	return CListCtrl::OnQueryNewPalette();
}

void CGfxListCtrl::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CListCtrl::OnPaletteChanged(pFocusWnd);
	if (pFocusWnd == this) return;
	OnQueryNewPalette();
}

BOOL CGfxListCtrl::OnEraseBkgnd(CDC* pDC) 
{
	if (m_bitmap.m_hObject != NULL) return true;
	return CListCtrl::OnEraseBkgnd(pDC);
}

void CGfxListCtrl::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	if (pft.GetSafeHandle()) pft.DeleteObject();
	if (pfb.GetSafeHandle()) pfb.DeleteObject();
	if (pfi.GetSafeHandle()) pfi.DeleteObject();
	if (pfu.GetSafeHandle()) pfu.DeleteObject();

	pInfo->m_rectDraw.SetRect(0, 0, pDC->GetDeviceCaps(HORZRES), pDC->GetDeviceCaps(VERTRES));
	pDC->DPtoLP(&(pInfo->m_rectDraw));

	CSize upsz(rcMarginMM.left*100, rcMarginMM.top*100);
	CSize dwsz(rcMarginMM.right*100, rcMarginMM.bottom*100);
	pDC->HIMETRICtoDP(&upsz);
	pDC->HIMETRICtoDP(&dwsz);
	pInfo->m_rectDraw.top    += upsz.cy;
	pInfo->m_rectDraw.left   += upsz.cx;
	pInfo->m_rectDraw.right  -= dwsz.cx;
	pInfo->m_rectDraw.bottom -= dwsz.cy;

	pft.CreatePointFont(90, "Arial", pDC);
	LOGFONT lf;
	pft.GetLogFont(&lf);
	lf.lfWeight = 700;
	pfb.CreateFontIndirect(&lf);
	lf.lfWeight = 0;
	lf.lfItalic = TRUE;
	pfi.CreateFontIndirect(&lf);
	lf.lfItalic = FALSE;
	lf.lfUnderline = TRUE;
	pfu.CreateFontIndirect(&lf);

	CFont * of = pDC->SelectObject(&pft);
	CSize sz = pDC->GetTextExtent("XX");
	pDC->SelectObject(&pfb);
	CSize szb = pDC->GetTextExtent("XX");

	if (dwPrintFlag & ptListName || dwPrintFlag & ptPageNumbers || dwPrintFlag & ptPageDate)
		iPrintCountPerPage = (pInfo->m_rectDraw.Height() - szb.cy * 2) / sz.cy;
	else
		iPrintCountPerPage = (pInfo->m_rectDraw.Height() - szb.cy * 1) / sz.cy;

	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(1+GetItemCount() / iPrintCountPerPage);
	pDC->SelectObject(of);
}

void CGfxListCtrl::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	CRect rc(pInfo->m_rectDraw);

	CSize upsz(rcMarginMM.left*100, rcMarginMM.top*100);
	CSize dwsz(rcMarginMM.right*100, rcMarginMM.bottom*100);
	pDC->HIMETRICtoDP(&upsz);
	pDC->HIMETRICtoDP(&dwsz);
	rc.top    += upsz.cy;
	rc.left   += upsz.cx;
	rc.right  -= dwsz.cx;
	rc.bottom -= dwsz.cy;


	int iFirst = (pInfo->m_nCurPage -1) * iPrintCountPerPage;
	int iLast = pInfo->m_nCurPage * iPrintCountPerPage;
	if (iLast > GetItemCount()) iLast = GetItemCount();
	CFont * of = pDC->SelectObject(&pft);
	CSize sz = pDC->GetTextExtent("X");

	CString cs;
	CRect rcItem(rc);
	rcItem.bottom = rcItem.top + sz.cy;

	int nColumnCount = GetColumnCount();

	CRect rcAllLabels;
	GetItemRect(iFirst, rcAllLabels, LVIR_BOUNDS);

	int obkm = pDC->SetBkMode(TRANSPARENT), nColumn;

	pDC->SelectObject(&pfb);

	int x1 = rc.left, x2 = rc.left;
	for (nColumn = 0; nColumn < nColumnCount; nColumn++)
	{
		CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);

		static TCHAR buf[256];
		HD_ITEM hditem;
		hditem.mask = HDI_TEXT | HDI_FORMAT | HDI_LPARAM | HDI_WIDTH;
		hditem.pszText = buf;
		hditem.cchTextMax = 255;

		pHeader->GetItem(nColumn, &hditem);
		UINT nJustify1 = DT_LEFT;
		if( hditem.fmt & HDF_CENTER) nJustify1 |= DT_CENTER;
		else if( hditem.fmt & HDF_RIGHT) nJustify1 |= DT_RIGHT;
		
		x2 += hditem.cxy * rcItem.Width() / rcAllLabels.Width();

		CRect rcSubItem;

		rcSubItem.top = rcItem.top;
		rcSubItem.bottom = rcItem.bottom;
		rcSubItem.left = x1;
		rcSubItem.right = x2;
		x1 = x2;

		CRect rcTextItem(rcSubItem);
		rcTextItem.left += sz.cx;
		rcTextItem.right -= sz.cx;

		CString csBuf(buf);

		if (wndHeader.pImageList && csBuf.Right(1) == "_")
		{
			int iIdx = atoi(cs);
			IMAGEINFO ii;
			if (wndHeader.pImageList->GetImageInfo(nColumn, &ii))
			{
				CRect rcIma(ii.rcImage);
				int x = rcSubItem.left + 1;
				int y = rcSubItem.top + 1;

				if (rcTextItem.left < rcTextItem.right-1) 
				{
					CDC memDC;
					memDC.CreateCompatibleDC(pDC);
					CBitmap bmp;
					bmp.CreateCompatibleBitmap(pDC, rcIma.Width(), rcIma.Height());
					CBitmap * ob = memDC.SelectObject(&bmp);
					memDC.FillSolidRect(CRect(0,0,rcIma.Width(),rcIma.Height()), RGB(255,255,255));
					ImageList_DrawEx(wndHeader.pImageList->m_hImageList, nColumn, memDC.m_hDC, 0, 0, rcIma.Width(), rcIma.Height()-1, m_clrBkgnd, m_clrBkgnd, ILD_TRANSPARENT);

					int dx = rcSubItem.Width() / rcIma.Width();
					int dy = rcSubItem.Height() / rcIma.Height();
					int dd = dx < dy ? dx : dy;
					dx = rcIma.Width() * dd;
					dy = rcIma.Height() * dd;
					x = rcSubItem.left + (rcSubItem.Width() - dx) / 2;
					pDC->StretchBlt(x, y, dx, dy, &memDC, 0, 0, rcIma.Width(), rcIma.Height(), SRCCOPY);
					memDC.SelectObject(ob);
				}
			}
		}
		else pDC->DrawText(csBuf, rcTextItem, DT_SINGLELINE|DT_VCENTER|nJustify1|DT_END_ELLIPSIS);

		pDC->MoveTo(rcSubItem.right-1, rcSubItem.bottom - 1);
		pDC->LineTo(rcSubItem.right-1, rcSubItem.top-1);
	}
	pDC->MoveTo(rcItem.left, rcItem.top - 1);
	pDC->LineTo(rcItem.right-1, rcItem.top - 1);

	pDC->MoveTo(rcItem.left, rcItem.bottom - 1);
	pDC->LineTo(rcItem.right-1, rcItem.bottom - 1);
	rcItem.OffsetRect(0, sz.cy);
	
	pDC->SelectObject(&pft);

	unsigned long lData;
	for (int t = iFirst; t < iLast; t++)
	{
		LV_ITEM lvi;
		lvi.mask=LVIF_IMAGE | LVIF_STATE;
		lvi.iItem = t;
		lvi.iSubItem=0;
		lvi.stateMask=0xFFFF;		// get all state flags
		GetItem(&lvi);

		lData = GetItemData(t);
		x1 =  x2 = rc.left;
		for (nColumn = 0; nColumn < nColumnCount; nColumn++)
		{
			LV_COLUMN lvc;
			lvc.mask = LVCF_FMT | LVCF_WIDTH;
			GetColumn(nColumn, &lvc);
			UINT nJustify1 = DT_LEFT;
			switch(lvc.fmt & LVCFMT_JUSTIFYMASK)
			{
				case LVCFMT_RIGHT: nJustify1 = DT_RIGHT;   break;
				case LVCFMT_CENTER:nJustify1 = DT_CENTER;  break;
			}
			x2 += lvc.cx * rcItem.Width() / rcAllLabels.Width();

			GetItemTextEx(t, nColumn, cs, &lData);

			CRect rcSubItem;

			rcSubItem.top = rcItem.top;
			rcSubItem.bottom = rcItem.bottom;
			rcSubItem.left = x1;
			rcSubItem.right = x2;
			x1 = x2;

			CRect rcTextItem(rcSubItem);
			rcTextItem.left += sz.cx;
			rcTextItem.right -= sz.cx;


			if (dwFlag&fSubItemImages && dwhImages & 1 << GetColumnIndex(nColumn)) 
			{
				int nImage = atoi(cs);
				CImageList * pImageList = pItemImageList;//GetImageList(LVSIL_SMALL);
				if (pImageList)
				{
					IMAGEINFO ii;
					pImageList->GetImageInfo(nImage, &ii);
					CRect rcIma(ii.rcImage);

					int x = rcSubItem.left + 1;
					int y = rcSubItem.top + 1;

					UINT nOvlImageMask = lvi.state & LVIS_OVERLAYMASK;
					if (rcTextItem.left < rcTextItem.right-1) 
					{
						CDC memDC;
						memDC.CreateCompatibleDC(pDC);
						CBitmap bmp;
						bmp.CreateCompatibleBitmap(pDC, rcIma.Width(), rcIma.Height());
						CBitmap * ob = memDC.SelectObject(&bmp);
						memDC.FillSolidRect(CRect(0,0,rcIma.Width(),rcIma.Height()), RGB(255,255,255));
						ImageList_DrawEx(pImageList->m_hImageList, nImage, memDC.m_hDC, 0, 0, rcIma.Width(), rcIma.Height()-1, m_clrBkgnd, m_clrBkgnd, ILD_TRANSPARENT | nOvlImageMask);

						int dx = rcSubItem.Width() / rcIma.Width();
						int dy = rcSubItem.Height() / rcIma.Height();
						int dd = dx < dy ? dx : dy;
						dx = rcIma.Width() * dd;
						dy = rcIma.Height() * dd;
						x = rcSubItem.left + (rcSubItem.Width() - dx) / 2;
						pDC->StretchBlt(x, y, dx, dy, &memDC, 0, 0, rcIma.Width(), rcIma.Height(), SRCCOPY);


						memDC.SelectObject(ob);
					}
				}	

			}
			else
			{
				if (NeedColExInfo(nColumn)) 
				{
					LXHDREX	lxhd;

					lxhd.iNotifyCode = NTEX_ITEMINFO;
					lxhd.CtrlId = iCtrlId < 0 ? GetDlgCtrlID() : iCtrlId;
					lxhd.iItem = t;
					lxhd.iSubItem = GetColumnIndex(nColumn);;
					lxhd.dwFlag = 0;
					lxhd.dwItemData = GetItemData(t);

					SendInfoExMsg(&lxhd);

					CFont * usf = NULL;
					if (dwPrintFlag&ptUseFonts)
					{
						if (lxhd.dwFlag&LXHDREX::exHFont) 
						{
							LOGFONT lf;
							CFont * ft = CFont::FromHandle(lxhd.hfText);
							ft->GetLogFont(&lf);
							usf = new CFont;
							lf.lfHeight *= 8;
							usf->CreatePointFontIndirect(&lf, pDC);
							pDC->SelectObject(usf);
						}
						else if (lxhd.dwFlag&LXHDREX::exBold) pDC->SelectObject(&pfb);
						else if (lxhd.dwFlag&LXHDREX::exItalic) pDC->SelectObject(&pfi);
						else if (lxhd.dwFlag&LXHDREX::exUnderline) pDC->SelectObject(&pfu);
						else pDC->SelectObject(&pft);
					}

					COLORREF ocr = pDC->GetTextColor();

					if (dwPrintFlag&ptUseColor)
					{
						if (lxhd.dwFlag&LXHDREX::exTextColor) pDC->SetTextColor(lxhd.crText);
					}

					pDC->DrawText(cs, rcTextItem, DT_SINGLELINE|DT_VCENTER|nJustify1|DT_END_ELLIPSIS);
					pDC->SetTextColor(ocr);
					pDC->SelectObject(&pft);
					if (usf) delete usf;
				}
				else pDC->DrawText(cs, rcTextItem, DT_SINGLELINE|DT_VCENTER|nJustify1|DT_END_ELLIPSIS);
			}

			pDC->MoveTo(rcSubItem.right-1, rcSubItem.bottom - 1);
			pDC->LineTo(rcSubItem.right-1, rcSubItem.top-1);
		}
		pDC->MoveTo(rcItem.left, rcItem.bottom - 1);
		pDC->LineTo(rcItem.right-1, rcItem.bottom - 1);

		rcItem.OffsetRect(0, sz.cy);
	}
//	rcItem.OffsetRect(0, sz.cy);
	if (dwPrintFlag & ptListName && csPrintName != "")
	{
		pDC->DrawText(csPrintName, rcItem, DT_SINGLELINE|DT_LEFT|DT_TOP);
	}
	if (dwPrintFlag & ptPageNumbers)
	{
		CString cs;
		cs.Format("%d", pInfo->m_nCurPage);
		pDC->DrawText(cs, rcItem, DT_SINGLELINE|DT_CENTER|DT_TOP);
	}
	if (dwPrintFlag & ptPageDate)
	{
		CTime tm = CTime::GetCurrentTime();
		CString cs;
		cs.Format("%02d/%02d/%d", tm.GetDay(), tm.GetMonth(), tm.GetYear());
		pDC->DrawText(cs, rcItem, DT_SINGLELINE|DT_RIGHT|DT_TOP);
	}

	pDC->SelectObject(of);

	pDC->SetBkMode(obkm);
}

void CGfxListCtrl::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	if (pfb.GetSafeHandle()) pfb.DeleteObject();
	if (pft.GetSafeHandle()) pft.DeleteObject();
	if (pfi.GetSafeHandle()) pfi.DeleteObject();
	if (pfu.GetSafeHandle()) pfu.DeleteObject();
}

/*-TE-
bool
CGfxListCtrl::BindDaoRecordset(CDaoRecordset * pSet)
{
	if (pSet)
	{
		bDaoBind = true;
		pRecordSet = pSet;
	}
	else
	{
		bDaoBind = false;
		pRecordSet = NULL;
	}
	return true;
}
*/

/*-TE-
bool
CGfxListCtrl::FillRecordsetColumn()
{
	if (pRecordSet == NULL || !(pRecordSet->IsOpen())) return false;

	CGfxColumnManager * pManager = CreateColumnManager();

	int i, max = pRecordSet->GetFieldCount();
	CDaoFieldInfo fieldinfo;

	pManager->DefineColumn(0, "", NULL, LVCFMT_LEFT, 0, fhNoSortArrow|fhNoResizeColumn);

	InsertColumnEx(0, "", LVCFMT_LEFT, 0, fhNoSortArrow|fhNoResizeColumn);

	int * pdef = new int[max + 1];
	pdef[0] = 0;

	for (i = 0; i < max; i++)
	{
		pdef[i+1] = i + 1;

		pRecordSet->GetFieldInfo(i, fieldinfo);//get field name

		DWORD dw = 0;
		
		if (fieldinfo.m_nType == dbByte || fieldinfo.m_nType == dbInteger || 
			fieldinfo.m_nType == dbLong || fieldinfo.m_nType == dbCurrency|| 
			fieldinfo.m_nType == dbSingle || fieldinfo.m_nType == dbDouble) 
			dw = fhNumeric;

		if (fieldinfo.m_nType == dbBoolean) 
		{
			InsertColumnEx(i + 1, fieldinfo.m_strName, LVCFMT_LEFT, 120, fhComboBox);
			pManager->DefineColumn(i + 1, fieldinfo.m_strName, NULL, LVCFMT_LEFT, 120, fhComboBox);
		}
		else 
		{
			InsertColumnEx(i + 1, fieldinfo.m_strName, LVCFMT_LEFT, 120, fhEdit|dw);
			pManager->DefineColumn(i + 1, fieldinfo.m_strName, NULL, LVCFMT_LEFT, 120, fhEdit|dw);
		}
	}
	pManager->DefineDefaultColumns(max + 1, pdef);
	delete pdef;

	return true;
}
*/

/*-TE-
bool
CGfxListCtrl::FillDaoItems()
{
	if (pRecordSet == NULL || !(pRecordSet->IsOpen())) return false;

	DeleteAllItems();
	pRecordSet->MoveLast();
	int count = pRecordSet->GetRecordCount(); //Get number of records

	SetItemCount(count);

	for (int t = 0; t < count; t++)	InsertItemEx(t,t);

	ResetScrollBar();

	return true;
}
*/

/*-TE-
void
CGfxListCtrl::OnDaoGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	*pResult = 0;

	if(pDispInfo->item.mask & LVIF_TEXT)
	{
		CString cs;
		OnDaoGetTextCallback((int)pDispInfo->item.iItem, (int) pDispInfo->item.iSubItem, (long) pDispInfo->item.lParam, cs);
		lstrcpyn(pDispInfo->item.pszText, cs, pDispInfo->item.cchTextMax);
	}
	
	if(pDispInfo->item.mask & LVIF_IMAGE) pDispInfo->item.iImage = 0;//set image to first in list	
}
*/

/*-TE-
void
CGfxListCtrl::OnDaoGetTextCallback(int iIndex, int iSubItem, long lCode, CString &cs)
{
	COleVariant varValue;

	int rc = GetColumnIndex(iSubItem) - 1;
	if (rc < 0) return;

	ASSERT(pManager);

	try
	{
		pRecordSet->SetAbsolutePosition(lCode);//Set the file to desired index
	}
	catch(CDaoException* e)
	{
		e->Delete();
		return;		
	}
	
	try
	{
		pRecordSet->GetFieldValue(rc, varValue);
	}
	catch(CDaoException* e)
	{
		e->Delete();
		return;
	}

	const VARIANT* variant = LPCVARIANT(varValue);
	switch(variant->vt)
	{
		case VT_I2:{	cs.Format("%d", variant->iVal);
						break;
				   }
		case VT_I4:{	cs.Format("%d", variant->lVal);
						break;
				   }
		case VT_R4:{	cs.Format("%f", variant->fltVal);
						break;
				   }	
		case VT_R8:{	cs.Format("%f", variant->dblVal);
						break;
				   }
		case VT_CY:{	COleCurrency c(varValue);
						cs = c.Format();//ie. 1.00
						break;
				   }
		case VT_DATE:{	COleDateTime t(variant->date);
						cs = t.Format( "%A, %B %d, %Y");//Day of Week, Month Day, Year
						break;
					 }
		case VT_BSTR:{  cs = V_BSTRT(&varValue);//convert BSTR to CString
						break;
					}
		case VT_BOOL:{	if(variant->boolVal) cs = "true"; else cs = "false";
						break;
					 }
		case VT_UI1:{	cs = (char*)variant->bVal;
						break;
					}

		default: break;

	}
	if (pManager->pColumnData[rc + 1].pSet != NULL)
	{
		CDaoFieldInfo fieldinfo;
		pManager->pColumnData[rc + 1].pSet->GetFieldInfo(pManager->pColumnData[rc + 1].iLinkField, fieldinfo);
		CString sql, fi;
		sql.Format("%s = %s", fieldinfo.m_strName, cs);
		if (pManager->pColumnData[rc + 1].pSet->FindFirst(sql))
		{
			pManager->pColumnData[rc + 1].pSet->GetFieldValue(pManager->pColumnData[rc + 1].iTextField, varValue);
			cs = "";

			const VARIANT* variant = LPCVARIANT(varValue);
			switch(variant->vt)
			{
				case VT_I2:{	cs.Format("%d", variant->iVal);
								break;
						   }
				case VT_I4:{	cs.Format("%d", variant->lVal);
								break;
						   }
				case VT_R4:{	cs.Format("%f", variant->fltVal);
								break;
						   }	
				case VT_R8:{	cs.Format("%f", variant->dblVal);
								break;
						   }
				case VT_CY:{	COleCurrency c(varValue);
								cs = c.Format();//ie. 1.00
								break;
						   }
				case VT_DATE:{	COleDateTime t(variant->date);
								cs = t.Format( "%A, %B %d, %Y");//Day of Week, Month Day, Year
								break;
							 }
				case VT_BSTR:{  cs = V_BSTRT(&varValue);//convert BSTR to CString
								break;
							}
				case VT_BOOL:{	if(variant->boolVal) cs = "true"; else cs = "false";
								break;
							 }
				case VT_UI1:{	cs = (char*)variant->bVal;
								break;
							}

				default: break;

			}

			return;
		}

		return;
	}
}
*/

long
CGfxListCtrl::GetExInfoCallback(LXHDREX * pLx)
{
	ASSERT(pLx);

	switch(pLx->iNotifyCode)
	{
	case NTEX_ITEMINFO:
		return 1;
		break;
	case NTEX_COMBOREQUEST:
		{
			if (pLx->iSubItem < 1) return 0;

/*-TE-
			if (pManager->pColumnData[pLx->iSubItem].pSet != NULL)
			{
				if (pManager->pColumnData[pLx->iSubItem].pSet->IsEOF() && pManager->pColumnData[pLx->iSubItem].pSet->IsBOF()) return 0;
				COleVariant varValue;
				pManager->pColumnData[pLx->iSubItem].pSet->MoveFirst();
				while (!(pManager->pColumnData[pLx->iSubItem].pSet->IsEOF()))
				{
					if (!(pManager->pColumnData[pLx->iSubItem].pSet->IsFieldStatusNull(pManager->pColumnData[pLx->iSubItem].iTextField)))
					{
						pManager->pColumnData[pLx->iSubItem].pSet->GetFieldValue(pManager->pColumnData[pLx->iSubItem].iTextField, varValue);

						varValue.ChangeType(VT_BSTR);
						pLx->pComboArray->Add(CString(V_BSTRT(&varValue)));
					}
					pManager->pColumnData[pLx->iSubItem].pSet->MoveNext();
				}
				return 1;
			}
*/
			pLx->pComboArray->Add(CString("true"));
			pLx->pComboArray->Add(CString("false"));
			return 1;
		}
		break;
	case NTEX_SETTEXT:
		{
			if (pLx->iSubItem < 1) return 0;

/*-TE-
			try
			{
				pRecordSet->SetAbsolutePosition(pLx->dwItemData);//Set the file to desired index
			}
			catch(CDaoException* e)
			{
				e->Delete();
				TRACE0("Error setting value (2)\n");
				return 0;		
			}

			if (pManager->pColumnData[pLx->iSubItem].pSet != NULL)
			{
				COleVariant varValue;
				CDaoFieldInfo fieldinfo;
				pManager->pColumnData[pLx->iSubItem].pSet->GetFieldInfo(pManager->pColumnData[pLx->iSubItem].iTextField, fieldinfo);
				CString sql, fi;
				sql.Format("%s = '%s'", fieldinfo.m_strName, pLx->csText);
				if (pManager->pColumnData[pLx->iSubItem].pSet->FindFirst(sql))
				{
					pManager->pColumnData[pLx->iSubItem].pSet->GetFieldValue(pManager->pColumnData[pLx->iSubItem].iLinkField, varValue);

					CString cs;
					const VARIANT* variant = LPCVARIANT(varValue);
					switch(variant->vt)
					{
						case VT_I2:{	cs.Format("%d", variant->iVal);
										break;
								   }
						case VT_I4:{	cs.Format("%d", variant->lVal);
										break;
								   }
						case VT_R4:{	cs.Format("%f", variant->fltVal);
										break;
								   }	
						case VT_R8:{	cs.Format("%f", variant->dblVal);
										break;
								   }
						case VT_CY:{	COleCurrency c(varValue);
										cs = c.Format();//ie. 1.00
										break;
								   }
						case VT_DATE:{	COleDateTime t(variant->date);
										cs = t.Format( "%A, %B %d, %Y");//Day of Week, Month Day, Year
										break;
									 }
						case VT_BSTR:{  cs = V_BSTRT(&varValue);//convert BSTR to CString
										break;
									}
						case VT_BOOL:{	if(variant->boolVal) cs = "true"; else cs = "false";
										break;
									 }
						case VT_UI1:{	cs = (char*)variant->bVal;
										break;
									}

						default: break;

					}
					try
					{
						pRecordSet->Edit();
						pRecordSet->SetFieldValue(pLx->iSubItem-1, (const char *) cs);
						pRecordSet->Update();
						TRACE1("Setting value to %s\n", cs);
					}
					catch(CDaoException* e)
					{
						e->Delete();
						TRACE0("Error setting value (3)\n");
					}
				}
				return 0;
			}
			
			try
			{
				pRecordSet->Edit();
				pRecordSet->SetFieldValue(pLx->iSubItem-1, (const char *) pLx->csText);
				pRecordSet->Update();
				TRACE1("Setting value to %s\n", pLx->csText);
			}
			catch(CDaoException* e)
			{
				e->Delete();
				TRACE0("Error setting value (3)\n");
				return 0;
			}
*/
		}
		return 0;
	};

	return 0L;
}



void CGfxListCtrl::DeleteAllColumns()
{
	for (int i = GetColumnCount() - 1; i >= 0; i--) DeleteColumn(i);
}

void CGfxListCtrl::ModifyExStyle(DWORD dwRemove, DWORD dwAdd, UINT dwRedraw)
{
	if (GetSafeHwnd())
	{
		DWORD dwStyle = SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE,0,0);
		dwStyle &= ~dwRemove;
		dwStyle |= dwAdd;
		SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);

		if (dwRedraw != 0) SetWindowPos(0,0,0,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOMOVE|dwRedraw);
		else Invalidate();
	}
}

 

void CGfxListCtrl::OnMoveFirstRecord()
{
	if (GetItemCount() > 0)
	{
		if (GetFocus() != this) SetFocus();
		SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);
		EnsureVisible(0, false);
	}
}

void CGfxListCtrl::OnMoveLastRecord()
{
	if (GetItemCount() > 0)
	{
		if (GetFocus() != this) SetFocus();
		SetItemState(GetItemCount() - 1, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);
		EnsureVisible(GetItemCount() - 1, false);
	}
}

void CGfxListCtrl::OnMoveNextRecord()
{
	int idx = GetNextItem(-1, LVNI_SELECTED);
	if (idx >= 0 && idx < GetItemCount() - 1)
	{
		if (GetFocus() != this) SetFocus();
		SetItemState(idx + 1, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);
		EnsureVisible(idx + 1, false);
	}
}

void CGfxListCtrl::OnMovePrevRecord()
{
	int idx = GetNextItem(-1, LVNI_SELECTED);
	if (idx > 0)
	{
		if (GetFocus() != this) SetFocus();
		SetItemState(idx - 1, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);
		EnsureVisible(idx - 1, false);
	}
}

bool CGfxListCtrl::EnableMoveFirst()
{
	if (GetItemCount() <= 0) return false;
	int idx = GetNextItem(-1, LVNI_SELECTED);
	return idx > 0;
}

bool CGfxListCtrl::EnableMoveLast()
{
	int max = GetItemCount();
	if (max <= 0) return false;
	int idx = GetNextItem(-1, LVNI_SELECTED);
	return idx < max - 1;
}

bool CGfxListCtrl::EnableMovePrev()
{
	if (GetItemCount() <= 0) return false;
	int idx = GetNextItem(-1, LVNI_SELECTED);
	return idx > 0;
}

bool CGfxListCtrl::EnableMoveNext()
{
	int max = GetItemCount();
	if (max <= 0) return false;
	int idx = GetNextItem(-1, LVNI_SELECTED);
	return idx < max - 1;
}

/*-TE-
bool CGfxListCtrl::LinkRecordset(const int iColId, CDaoRecordset * ps, const int iLnk, const int iTxtLnk)
{
	CGfxColumnManager * pc = GetColumnManager();
	ASSERT(pc);

	dwhCombo   |= (1 << (iColId + 1));
	dwhEdit    &= ~(1 << (iColId + 1));

	return pc->LinkRecordset(iColId + 1, ps, iLnk, iTxtLnk);
}
*/

/*-TE-
bool CGfxListCtrl::LinkRecordset(const char * cMainRecord, CDaoRecordset * ps, const char * cLinkRecord, const char * cTextField)
{
	CGfxColumnManager * pc = GetColumnManager();
	ASSERT(pc);
	
	CDaoFieldInfo fieldinfo;
	int i, max = pRecordSet->GetFieldCount(), idx1 = -1, idx2 = -1, idx3 = -1;

	for (i = 0; i < max; i++)
	{
		pRecordSet->GetFieldInfo(i, fieldinfo);
		if (fieldinfo.m_strName.CompareNoCase(cMainRecord) == 0)
		{
			idx1 = i;
			break;
		}
	}
	if (idx1 < 0) return false;

	max = ps->GetFieldCount();

	for (i = 0; i < max; i++)
	{
		ps->GetFieldInfo(i, fieldinfo);
		if (fieldinfo.m_strName.CompareNoCase(cLinkRecord) == 0)
		{
			idx2 = i;
			break;
		}
	}
	if (idx2 < 0) return false;

	for (i = 0; i < max; i++)
	{
		ps->GetFieldInfo(i, fieldinfo);
		if (fieldinfo.m_strName.CompareNoCase(cTextField) == 0)
		{
			idx3 = i;
			break;
		}
	}
	if (idx3 < 0) return false;

	dwhCombo   |= (1 << (idx1 + 1));
	dwhEdit    &= ~(1 << (idx1 + 1));

	return pc->LinkRecordset(idx1 + 1, ps, idx2, idx3);
}
*/