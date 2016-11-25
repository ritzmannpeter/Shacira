// GfxCategoryManager.cpp: implementation of the CGfxCategoryManager class.
//
//////////////////////////////////////////////////////////////////////

#include "../stdafx.h"
//-TE-#include "GfxList.h"
#include "GfxCategoryManager.h"
#include "GfxListCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGfxCategoryManager::CGfxCategoryManager()
{
	lMode = 0;

	pItems = NULL;
	iItems = 0;

	iCategory = 0; 
	pCategory = NULL;

	pCallBackOwner = NULL;
	m_fpCategoryFun = NULL;
	m_fpDaoCategoryFun = NULL;
}

CGfxCategoryManager::~CGfxCategoryManager()
{
	if (iItems > 0 && pItems) GlobalFree((HGLOBAL) pItems);
	if (iCategory && pCategory)
	{
		for (iCategory--; iCategory >= 0; iCategory --)
			pCategory[iCategory].Clear();

		GlobalFree((HGLOBAL)pCategory);
	}
}

int CGfxCategoryManager::FindCategory(const char * cText)
{
	for (long t = 0; t < iCategory; t++)
		if (pCategory[t].lKind == fcFixedTextCategory && lstrcmp(cText, pCategory[t].cCategory) == 0) return t;

	return -1;
}

int CGfxCategoryManager::FindCategory(const CTime tmTime)
{
	for (long t = 0; t < iCategory; t++)
		if (pCategory[t].lKind == fcTimeCategory && tmTime >= pCategory[t].tmFrom && tmTime < pCategory[t].tmTo) return t;

	return -1;
}

int CGfxCategoryManager::FindCategory(const double dbVal)
{
	for (long t = 0; t < iCategory; t++)
		if (pCategory[t].lKind == fcNumericCategory && dbVal >= pCategory[t].dbMin && dbVal < pCategory[t].dbMax) return t;

	return -1;
}

int CGfxCategoryManager::AddCategory(const char * cText, const char * cCategory)
{
	iCategory ++;
	if (iCategory > 1) pCategory = (CGfxCategory *) GlobalReAlloc((HGLOBAL) pCategory, sizeof(CGfxCategory) * (iCategory), GMEM_MOVEABLE|GMEM_ZEROINIT);
	else pCategory = (CGfxCategory *) GlobalAlloc(GPTR, sizeof(CGfxCategory));

	ASSERT(pCategory != NULL);

	pCategory[iCategory - 1].Init(cText, cCategory);

	if (iItems > 0)
	{
		pCategory[iCategory - 1].iItems = 0;
		pCategory[iCategory - 1].pItems = (long *) GlobalAlloc(GMEM_FIXED, sizeof(long) * iItems);
		ASSERT(pCategory[iCategory - 1].pItems);
	}

	return iCategory - 1;
}

int CGfxCategoryManager::AddCategory(const char * cText, const CTime tmFrom, const CTime tmTo)
{
	iCategory ++;
	if (iCategory > 1) pCategory = (CGfxCategory *) GlobalReAlloc((HGLOBAL) pCategory, sizeof(CGfxCategory) * (iCategory), GMEM_MOVEABLE|GMEM_ZEROINIT);
	else pCategory = (CGfxCategory *) GlobalAlloc(GPTR, sizeof(CGfxCategory));

	ASSERT(pCategory != NULL);

	pCategory[iCategory - 1].Init(cText, tmFrom, tmTo);

	if (iItems > 0)
	{
		pCategory[iCategory - 1].iItems = 0;
		pCategory[iCategory - 1].pItems = (long *) GlobalAlloc(GMEM_FIXED, sizeof(long) * iItems);
		ASSERT(pCategory[iCategory - 1].pItems);
	}

	return iCategory - 1;
}

int CGfxCategoryManager::AddCategory(const char * cText, const dbMin, const dbMax)
{
	iCategory ++;
	if (iCategory > 1) pCategory = (CGfxCategory *) GlobalReAlloc((HGLOBAL) pCategory, sizeof(CGfxCategory) * (iCategory), GMEM_MOVEABLE|GMEM_ZEROINIT);
	else pCategory = (CGfxCategory *) GlobalAlloc(GPTR, sizeof(CGfxCategory));

	ASSERT(pCategory != NULL);

	pCategory[iCategory - 1].Init(cText, dbMin, dbMax);

	if (iItems > 0)
	{
		pCategory[iCategory - 1].iItems = 0;
		pCategory[iCategory - 1].pItems = (long *) GlobalAlloc(GMEM_FIXED, sizeof(long) * iItems);
		ASSERT(pCategory[iCategory - 1].pItems);
	}

	return iCategory - 1;
}

void CGfxCategoryManager::CGfxCategory::Init(const char * _cText, const char * _cCategory)
{
	ASSERT(_cText != NULL && _cCategory != NULL);

	cText = new char[lstrlen(_cText) + 1];
	lstrcpy(cText, _cText);

	cCategory = new char[lstrlen(_cCategory) + 1];
	lstrcpy(cCategory, _cCategory);

	lKind = fcFixedTextCategory;
	iItems = 0;
	pItems = NULL;
	bExpanded = false;
}

void CGfxCategoryManager::CGfxCategory::Init(const char * _cText, const CTime _tmFrom, const CTime _tmTo)
{
	ASSERT(_cText != NULL);

	cText = new char[lstrlen(_cText) + 1];
	lstrcpy(cText, _cText);

	cCategory = NULL;

	tmFrom = _tmFrom;
	tmTo = _tmTo;

	lKind = fcTimeCategory;
	iItems = 0;
	pItems = NULL;
	bExpanded = false;
}

void CGfxCategoryManager::CGfxCategory::Init(const char * _cText, const double _dbMin, const double _dbMax)
{
	ASSERT(_cText != NULL);

	cText = new char[lstrlen(_cText) + 1];
	lstrcpy(cText, _cText);

	cCategory = NULL;

	dbMin = _dbMin;
	dbMax = _dbMax;

	lKind = fcNumericCategory;
	iItems = 0;
	pItems = NULL;
	bExpanded = false;
}

void CGfxCategoryManager::CGfxCategory::Clear()
{
	if (cText) 
	{
		delete [] cText;
		cText = NULL;
	}
	if (cCategory) 
	{
		delete [] cCategory;
		cCategory = NULL;
	}
	if (pItems != NULL)
	{
		GlobalFree((HGLOBAL) pItems);
	}
	iItems = 0;
	pItems = NULL;
}

void CGfxCategoryManager::AddItemToCategory(const int _iCategory, const long dwData)
{
	ASSERT(_iCategory >= 0 && _iCategory < iCategory);
	pCategory[_iCategory].pItems[pCategory[_iCategory].iItems] = dwData;
	pCategory[_iCategory].iItems++;
}

/*
// Author: Keith Rule -- keithr@europa.com
//
// Copyright (c) 1995-1996, Keith Rule
// May be freely used provided this comment
// is included with the source and all derived
// versions of this source.
void StatusBarMessage(char* fmt, ...)
{
	if (AfxGetApp() != NULL && AfxGetApp()->m_pMainWnd != NULL) {
		char buffer[256];
		CStatusBar* pStatus = (CStatusBar*) 
			AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR);
		va_list argptr;
		va_start(argptr, fmt);
		vsprintf(buffer, fmt, argptr);
		va_end(argptr);
		if (pStatus != NULL) {
			pStatus->SetPaneText(0, buffer);
			pStatus->UpdateWindow();
		}
	}
}
*/

void CGfxCategoryManager::SetupList(CGfxListCtrl * pList)
{
	if (iItems > 0 && pItems) 
	{
		GlobalFree((HGLOBAL) pItems);
		iItems = 0;
		pItems = NULL;
	}
	int t, max = pList->GetItemCount();
	if (max < 0) return;
	pItems = (long *) GlobalAlloc(GPTR, sizeof(long) * max);
	ASSERT(pItems);
	iItems = max;

	ASSERT(m_fpCategoryFun != NULL || m_fpDaoCategoryFun != NULL);

	

	if (m_fpCategoryFun)
	{
		for (t = 0; t < max; t++)
		{
			pItems[t] = pList->GetItemData(t);
			(pCallBackOwner->*m_fpCategoryFun)(this, pItems[t]);
		}
	}
	else if (m_fpDaoCategoryFun)
	{
		for (t = 0; t < max; t++) pItems[t] = t;
		(pCallBackOwner->*m_fpDaoCategoryFun)(this);
	}

	InsertCategoryInList(pList);
}


void CGfxCategoryManager::ResetList(CGfxListCtrl * pList)
{
	pList->SetRedraw(false);
	pList->DeleteAllItems();
	int t;
	for (t = 0; t < iItems; t++)
		pList->SetItemData(pList->InsertItem(t, LPSTR_TEXTCALLBACK), pItems[t]);

	for (t = 0; t < iCategory; t++)
	{
		if (pCategory[t].iItems > 0 && pCategory[t].pItems != NULL) 
		{
			pCategory[t].iItems = 0;
		}
	}

	pList->SetRedraw(true);
}

int CGfxCategoryManager::IsListItemACategory(DWORD dwData)
{
	for (int t = 0; t < iCategory; t++)
	{
		if (&pCategory[t] == (CGfxCategory *) dwData) return t;
	}
	return -1;
}

void CGfxCategoryManager::InsertCategoryInList(CGfxListCtrl * pList)
{
	pList->SetRedraw(false);
	pList->DeleteAllItems();

	int idx = 0;
	for (int t = 0; t < iCategory; t++)
	{
//		DWORD dw = t;
//		dw |= (1 << 31);
		ASSERT(pCategory[t].cText);
		CString cs;
		cs.Format("Categoria: %s (%d element%c)", pCategory[t].cText, pCategory[t].iItems, pCategory[t].iItems == 1 ? 'o' : 'i');
		idx = pList->InsertItem(idx, cs);
		pList->SetItemData(idx, (DWORD) &pCategory[t]);
		idx ++;
		if (pCategory[t].bExpanded == true)
		{
			for (int x = 0; x < pCategory[t].iItems; x++)
			{
				idx = pList->InsertItem(idx, LPSTR_TEXTCALLBACK);
				pList->SetItemData(idx, pCategory[t].pItems[x]);
				idx ++;
			}
		}
	}
	
	pList->SetRedraw(true);
}

void CGfxCategoryManager::FillCategoryItems(const int iCat, const int iIdx, CGfxListCtrl * pList)
{
	pList->SetRedraw(false);
	int idx = iIdx + 1;
	for (int t = 0; t < pCategory[iCat].iItems; t++)
	{
		idx = pList->InsertItem(idx, LPSTR_TEXTCALLBACK);
		pList->SetItemData(idx, pCategory[iCat].pItems[t]);
		idx ++;
	}
	pList->SetRedraw(true);
}

void CGfxCategoryManager::RemoveCategoryItems(const int iCat, const int iIdx, CGfxListCtrl * pList)
{
	pList->SetRedraw(false);
	int max = pList->GetItemCount(), t;

	bool bLoop = true;
	DWORD dw;
	while (bLoop)
	{
		dw = pList->GetItemData(iIdx + 1);

		bool bIsCat = false;
		for (t = 0; t < iCategory; t++)
		{
			if (&pCategory[t] == (CGfxCategory *) dw) 
			{
				bIsCat = true;
				break;
			}
		}

		if (bIsCat) bLoop = false;
		else
		{
			pList->DeleteItem(iIdx + 1);
			max --;
			if (iIdx + 1 >= max) bLoop = false;
		}

	}
	pList->SetRedraw(true);
}

int CGfxCategoryManager::InsertNewItem(CGfxListCtrl * pList, const long lData)
{
	int iResult = -1;

	iItems ++;
	if (iItems > 1) pItems = (long *) GlobalReAlloc((HGLOBAL) pItems, sizeof(long) * iItems, GMEM_MOVEABLE|GMEM_ZEROINIT);
	else pItems = (long *) GlobalAlloc(GPTR, sizeof(long));
	pItems[iItems-1] = lData;

	int * iOldCatTot = iCategory > 0 ? new int[iCategory] : NULL, t;

	for (t = 0; t < iCategory; t++)
	{
		iOldCatTot[t] = pCategory[t].iItems;

		if (pCategory[t].pItems != NULL) pCategory[t].pItems = (long *) GlobalReAlloc((HGLOBAL) pCategory[t].pItems, sizeof(long) * iItems, GMEM_MOVEABLE|GMEM_ZEROINIT);
		else pCategory[t].pItems = (long *) GlobalAlloc(GPTR, sizeof(long));
	}
	CGfxCategory * pOldCat = pCategory;
	int iOldCat = iCategory;

	(pCallBackOwner->*m_fpCategoryFun)(this, pItems[iItems-1]);

	CGfxCategory * pNewCat = pCategory;

	LV_FINDINFO lfv;
	lfv.flags = LVFI_PARAM;
	if (pNewCat != pOldCat)
	{
		ASSERT(iOldCat != iCategory);
		for (t = 0; t < iOldCat; t++)
		{
			lfv.lParam = (long) &(pOldCat[t]);
			int idx = pList->FindItem(&lfv, -1);
			if (idx >= 0)
			{
				pList->SetItemData(idx, (long) &(pNewCat[t]));
			}
//			pNewCat += sizeof(CGfxCategory);
//			pOldCat += sizeof(CGfxCategory);
		}
	}

	for (t = 0; t < iCategory; t++)
	{
		if (t >= iOldCat || iOldCatTot[t] != pCategory[t].iItems)
		{
			lfv.lParam = (long) &(pCategory[t]);
			int idx = pList->FindItem(&lfv, -1);
			if (idx >= 0)
			{
				CString cs;
				cs.Format("Categoria: %s (%d element%c)", pCategory[t].cText, pCategory[t].iItems, pCategory[t].iItems == 1 ? 'o' : 'i');
				pList->SetItemText(idx, 0, cs);
				CRect rcItem;
				pList->GetItemRect(idx, rcItem, LVIR_BOUNDS);
				pList->InvalidateRect(rcItem, false);
				if (pCategory[t].bExpanded == true)
				{
					iResult = pList->InsertItem(idx + 1, LPSTR_TEXTCALLBACK);
					pList->SetItemData(iResult, lData);
				}
			}
			else
			{
				ASSERT(pCategory[t].cText);
				CString cs;
				cs.Format("Categoria: %s (%d element%c)", pCategory[t].cText, pCategory[t].iItems, pCategory[t].iItems == 1 ? 'o' : 'i');
				idx = pList->InsertItem(pList->GetItemCount(), cs);
				pList->SetItemData(idx, (DWORD) &pCategory[t]);

				CRect rcItem;
//				pList->GetSubItemRect(idx, 0, rcItem);
//				rcItem.bottom ++;
//				rcItem.right ++;
//				pList->ValidateRect(rcItem);
				pList->GetItemRect(idx, rcItem, LVIR_BOUNDS);
				pList->InvalidateRect(rcItem, false);
			}
		}
	}

	if (iOldCatTot) delete [] iOldCatTot;

	return iResult;
}
