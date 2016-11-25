// GfxColumnManager.cpp : implementation of the CGfxColumnManager class
//

#include "../stdafx.h"
//-TE-#include "GfxList.h"

#include "GfxListCtrl.h"
#include "GfxColumnManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGfxColumnManager::CGfxColumn

CGfxColumnManager::CGfxColumn::CGfxColumn()
{
	cText = NULL;
	cTextDt = NULL;
	//-TE-pSet = NULL;
	iLinkField = -1;
}

CGfxColumnManager::CGfxColumn::~CGfxColumn()
{
	Clear();
}

void CGfxColumnManager::CGfxColumn::Clear()
{
	if (cText)   delete [] cText;
	if (cTextDt) delete [] cTextDt;
	if (cDescr)  delete [] cDescr;
	cText = NULL;
	cTextDt = NULL;
	cDescr = NULL;
	//-TE-pSet = NULL;
	iLinkField = -1;
}

void CGfxColumnManager::CGfxColumn::Init(const int _iId, const char * _cText, const char * _cTextDt, const int _iAlign, const int _iWidth, DWORD _dwData, const int _iImage, const char * _cDescr)
{
	iId = _iId;
	iAlign = _iAlign;
	iWidth = _iWidth;
	iImage = _iImage;
	dwData = _dwData;
	cText = NULL;
	if (_cText)
	{
		cText = new char[lstrlen(_cText) + 1];
		lstrcpy(cText, _cText);
	}
	cTextDt = NULL;
	if (_cTextDt)
	{
		cTextDt = new char[lstrlen(_cTextDt) + 1];
		lstrcpy(cTextDt, _cTextDt);
	}
	cDescr = NULL;
	if (_cDescr)
	{
		cDescr = new char[lstrlen(_cDescr) + 1];
		lstrcpy(cDescr, _cDescr);
	}
	//-TE-pSet = NULL;
	iLinkField = -1;
}


/////////////////////////////////////////////////////////////////////////////
// CGfxColumnManager

CGfxColumnManager::CGfxColumnManager()
{
	iColumnData = 0;
	pColumnData = NULL;

	iDefColumn = 0;
	pDefColumn = NULL;
}

CGfxColumnManager::CGfxColumnManager(const CGfxColumnManager * p)
{
	iColumnData = 0;
	pColumnData = NULL;

	iDefColumn = 0;
	pDefColumn = NULL;

	ASSERT(p);

	if (p->iDefColumn > 0)
	{
		iDefColumn = p->iDefColumn;
		pDefColumn = new int[iDefColumn];
		CopyMemory(pDefColumn, p->pDefColumn, sizeof(int) * iDefColumn);
	}
	if (p->iColumnData)
	{
		for (int t = 0; t < p->iColumnData; t++)
		{
			DefineColumn(p->pColumnData[t].iId, p->pColumnData[t].cText, p->pColumnData[t].cTextDt, p->pColumnData[t].iAlign, p->pColumnData[t].iWidth, p->pColumnData[t].dwData, p->pColumnData[t].iImage, p->pColumnData[t].cDescr);
			ASSERT(p->pColumnData[t].iWidth == pColumnData[t].iWidth);
			//-TE-p->pColumnData[t].pSet = pColumnData[t].pSet;
			p->pColumnData[t].iLinkField = pColumnData[t].iLinkField;
		}
	}
}


CGfxColumnManager::~CGfxColumnManager()
{
	if (iColumnData > 0 && pColumnData != NULL)
	{
		for (;iColumnData > 0; iColumnData --) pColumnData[iColumnData-1].Clear();
		GlobalFree((HGLOBAL) pColumnData);
	}
	if (iDefColumn > 0 && pDefColumn)
	{
		delete [] pDefColumn;
	}
}

int CGfxColumnManager::DefineColumn(const int iId, const char * cText, const char * cTextDt, const int iAlign, const int iWidth, DWORD dwData, const int iImage, const char * cDescr)
{
	iColumnData ++;
	if (iColumnData > 1) pColumnData = (CGfxColumn *) GlobalReAlloc((HGLOBAL) pColumnData, sizeof(CGfxColumn) * (iColumnData), GMEM_MOVEABLE|GMEM_ZEROINIT);
	else pColumnData = (CGfxColumn *) GlobalAlloc(GPTR, sizeof(CGfxColumn));

	ASSERT(pColumnData != NULL);

	pColumnData[iColumnData - 1].Init(iId, cText, cTextDt, iAlign, iWidth, dwData, iImage, cDescr);
	return iColumnData -1;
}

bool CGfxColumnManager::CustomizeColumn(CGfxListCtrl * pList, CWnd * pParent)
{
	return false;
}

bool CGfxColumnManager::SetupColumnData(CGfxListCtrl * pList, const bool bNeedOwnerDraw)
{
	ASSERT(pList && pList->GetSafeHwnd());

	int t, idx, irealidx = 0;
	CHeaderCtrl* pHeader = (CHeaderCtrl*) pList->GetDlgItem(0);
	ASSERT(pHeader);
	if (pHeader == NULL) return false;

	pList->dwhCombo = pList->dwhComboEx = pList->dwhEdit = pList->dwhNumeric = pList->dwhValute = pList->dwhCombo = pList->dwhImages = 0;

	irealidx = pHeader->GetItemCount();
	int iDelTo = irealidx;

	for (t = 0; t < iDefColumn; t++)
	{
		idx = FindColumnById(pDefColumn[t]);
		ASSERT(idx >= 0);
		if (idx >= 0)
		{
			int iChkIdx = pList->InsertColumn(irealidx, pColumnData[idx].cText, pColumnData[idx].iAlign|HDF_OWNERDRAW, pColumnData[idx].iWidth, pColumnData[idx].iId);

			if (pColumnData[idx].dwData & fhComboBox)		pList->dwhCombo   |= (1 << pColumnData[idx].iId);
			if (pColumnData[idx].dwData & fhComboBoxEx)		pList->dwhComboEx |= (1 << pColumnData[idx].iId);
			if (pColumnData[idx].dwData & fhEdit)			pList->dwhEdit    |= (1 << pColumnData[idx].iId);
			if (pColumnData[idx].dwData & fhNumeric)		pList->dwhNumeric |= (1 << pColumnData[idx].iId);
			if (pColumnData[idx].dwData & fhValute)			pList->dwhValute  |= (1 << pColumnData[idx].iId);
			if (pColumnData[idx].dwData & fhSortAble)		pList->wndHeader.dwSortUp |= (1 << pColumnData[idx].iId);
			if (pColumnData[idx].dwData & fhImage)			pList->dwhImages |= (1 << pColumnData[idx].iId);
			if (pColumnData[idx].dwData & fhNoSortArrow)	pList->wndHeader.dwDontShowSortArrow |= (1 << pColumnData[idx].iId);
			if (pColumnData[idx].dwData & fhNoResizeColumn) pList->wndHeader.dwNoResizeColumn |= (1 << pColumnData[idx].iId);

			if (pColumnData[idx].dwData & fhColumnHasImage)//fhImage)
				pList->SetColumnImage(iChkIdx, pColumnData[idx].iImage); //atoi(pColumnData[idx].cText));

			irealidx ++;
		}
	}

	if (iDelTo > 0)
	{
		for (t = 0; t < iDelTo; t++)
			pList->DeleteColumn(0);
	}

	pHeader->Invalidate();

	pList->Invalidate();

	return true;
}

bool CGfxColumnManager::RetrieveColumnData(CGfxListCtrl * pList)
{
	ASSERT(pList && pList->GetSafeHwnd());

	int t, irealidx = 0;
	CHeaderCtrl* pHeader = (CHeaderCtrl*) pList->GetDlgItem(0);
	ASSERT(pHeader);
	if (pHeader == NULL) return false;

	HD_ITEM hditem;
	hditem.mask = HDI_LPARAM|HDI_WIDTH;
	
	ASSERT(pHeader->GetItemCount() == iDefColumn);

	for (t = pHeader->GetItemCount() - 1; t >= 0; t --)
	{
		pHeader->GetItem(t, &hditem);
		pDefColumn[t] = hditem.lParam;
		int id = FindColumnById(pDefColumn[t]);
		ASSERT(id >= 0);
		pColumnData[id].iWidth = hditem.cxy;
	}
	return true;
}

int CGfxColumnManager::FindColumnById(const int iId) const
{
	ASSERT(iColumnData > 0 && iId >= 0);

	for (int t = 0; t < iColumnData; t++)
		if (pColumnData[t].iId == iId) return t;

	return -1;
}

bool CGfxColumnManager::IsDefColumn(const int iId) const
{
	ASSERT(iDefColumn > 0 && iId >= 0);

	for (int t = 0; t < iDefColumn; t++)
		if (pDefColumn[t] == iId) return true;

	return false;
}

bool CGfxColumnManager::DefineDefaultColumns(const int iCount, const int * iCols)
{
	ASSERT(iCount > 0 && iCols != NULL);

	if (iDefColumn > 0 && pDefColumn != NULL) delete [] pDefColumn;
	if (iCount > 0)
	{
		pDefColumn = new int[iCount];
		ASSERT(pDefColumn);
		CopyMemory(pDefColumn, iCols, sizeof(int) * iCount);
		iDefColumn = iCount;
		return true;
	}
	iDefColumn = 0;
	pDefColumn = NULL;
	return false;
}

void CGfxColumnManager::ReadFromProfile(const char * cListName)
{
	int t, i;

	CString csProfile, cs, cs1;
	csProfile.Format("GfxLists\\%s", cListName);
	int iDat = AfxGetApp()->GetProfileInt(csProfile,"NumDef", 0), iDat1;
	if (iDat == 0) return;

	if (iDefColumn > 0 && pDefColumn != NULL) delete [] pDefColumn;

	iDefColumn = 0;
	pDefColumn = new int[iDat];
	for (t = 0; t < iDat; t++)
	{
		cs.Format("DefColId %d", t);
		iDat1 = AfxGetApp()->GetProfileInt(csProfile, cs, -1);
		if (iDat1 >= 0) 
		{
			pDefColumn[iDefColumn++] = iDat1;
		}
	}

	ASSERT(iDefColumn > 0);

	iDat = AfxGetApp()->GetProfileInt(csProfile,"DefNum", -1);

	for (t = 0; t < iDat; t++)
	{
		cs.Format("ColDef_id_%d", t);
		iDat1 = AfxGetApp()->GetProfileInt(csProfile, cs, -1);
		if (iDat1 >= 0)
		{
			for (i = 0; i < iColumnData; i++)
			{
				if (iDat1 == pColumnData[i].iId)
				{
					cs.Format("ColDef_align_%d", t);
					pColumnData[i].iAlign = AfxGetApp()->GetProfileInt(csProfile, cs, pColumnData[i].iAlign);
					cs.Format("ColDef_width_%d", t);
					pColumnData[i].iWidth = AfxGetApp()->GetProfileInt(csProfile, cs, pColumnData[i].iWidth);
					cs.Format("ColDef_image_%d", t);
					pColumnData[i].iImage = AfxGetApp()->GetProfileInt(csProfile, cs, pColumnData[i].iImage);
					cs.Format("ColDef_dwdata_%d", t);
					pColumnData[i].dwData = AfxGetApp()->GetProfileInt(csProfile, cs, pColumnData[i].dwData);

					cs.Format("ColDef_text_%d", t);
					cs1 = AfxGetApp()->GetProfileString(csProfile, cs, "");
					if (pColumnData[t].cText) delete [] pColumnData[t].cText;
					pColumnData[t].cText = new char[cs1.GetLength() + 1];
					ASSERT(pColumnData[t].cText);
					lstrcpy(pColumnData[t].cText, cs1);

					cs.Format("ColDef_textdt_%d", t);
					cs1 = AfxGetApp()->GetProfileString(csProfile, cs, "");
					if (pColumnData[t].cTextDt) delete [] pColumnData[t].cTextDt;
					pColumnData[t].cTextDt = new char[cs1.GetLength() + 1];
					ASSERT(pColumnData[t].cTextDt);
					lstrcpy(pColumnData[t].cTextDt, cs1);

					cs.Format("ColDef_descr_%d", t);
					cs1 = AfxGetApp()->GetProfileString(csProfile, cs, "");
					if (pColumnData[t].cDescr) delete [] pColumnData[t].cDescr;
					pColumnData[t].cDescr = new char[cs1.GetLength() + 1];
					ASSERT(pColumnData[t].cDescr);
					lstrcpy(pColumnData[t].cDescr, cs1);

					break;
				}
			}
		}
	}
}

void CGfxColumnManager::WriteToProfile(const char * cListName)
{
	int t;

	CString csProfile, cs;
	csProfile.Format("GfxLists\\%s", cListName);
	AfxGetApp()->WriteProfileInt(csProfile,"NumDef", iDefColumn);
	
	for (t = 0; t < iDefColumn; t++)
	{
		cs.Format("DefColId %d", t);
		AfxGetApp()->WriteProfileInt(csProfile, cs, pDefColumn[t]);
	}
	AfxGetApp()->WriteProfileInt(csProfile,"DefNum", iDefColumn);
	for (t = 0; t < iColumnData; t++)
	{
		cs.Format("ColDef_id_%d", t);
		AfxGetApp()->WriteProfileInt(csProfile, cs, pColumnData[t].iId);
		cs.Format("ColDef_align_%d", t);
		AfxGetApp()->WriteProfileInt(csProfile, cs, pColumnData[t].iAlign);
		cs.Format("ColDef_width_%d", t);
		AfxGetApp()->WriteProfileInt(csProfile, cs, pColumnData[t].iWidth);
		cs.Format("ColDef_image_%d", t);
		AfxGetApp()->WriteProfileInt(csProfile, cs, pColumnData[t].iImage);
		cs.Format("ColDef_dwdata_%d", t);
		AfxGetApp()->WriteProfileInt(csProfile, cs, pColumnData[t].dwData);

		cs.Format("ColDef_text_%d", t);
		AfxGetApp()->WriteProfileString(csProfile, cs, pColumnData[t].cText ? pColumnData[t].cText : "");
		cs.Format("ColDef_textdt_%d", t);
		AfxGetApp()->WriteProfileString(csProfile, cs, pColumnData[t].cTextDt ? pColumnData[t].cTextDt : "");
		cs.Format("ColDef_descr_%d", t);
		AfxGetApp()->WriteProfileString(csProfile, cs, pColumnData[t].cDescr ? pColumnData[t].cDescr : "");
	}
}



/*-TE-
bool CGfxColumnManager::LinkRecordset(const int iId, CDaoRecordset * ps, const int iLnk, const int iTxtLnk)
{
	int idx = FindColumnById(iId);
	if (idx >= 0)
	{
		pColumnData[idx].pSet = ps;
		pColumnData[idx].iLinkField = iLnk;
		pColumnData[idx].iTextField = iTxtLnk;
		pColumnData[idx].dwData |= fhComboBox;
		pColumnData[idx].dwData &= ~(fhEdit);
		return true;
	}
	return false;
}
*/