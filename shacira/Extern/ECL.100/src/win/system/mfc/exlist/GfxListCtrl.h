#if !defined(AFX_GFXLISTCTRL_H__31F5CEA8_E5CA_11D1_86E7_000000000000__INCLUDED_)
#define AFX_GFXLISTCTRL_H__31F5CEA8_E5CA_11D1_86E7_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GfxListCtrl.h : header file
//


#include "GfxHeaderCtrl.h"
#include "GfxListTip.h"

#include "GfxColumnManager.h"
#include "GfxCategoryManager.h"

#define WM_LISTEX_NOTIFY	WM_USER+1

class LXHDREX;

class CGfxInCombo;

enum {	fHighRowSelect = 1 << 0, fVertGrid = 1 << 1, fHorizGrid = 1 << 2, fAutoSort = 1 << 3,
		fExInfo = 1 << 4, fSubItemImages = 1 << 5,  fAllowMultiChange = 1 << 6, fAllowDivider = 1 << 7,
		fCellToolTip = 1 << 8, fExInfoOnRow  = 1 << 9, fExInfoOnCol = 1 << 10, fReturnDblClk = 1 << 11,
		fReturnModify = 1 << 12, fScrollBarAlways = 1 << 13, fShowSelCell = 1 << 14
 };

enum {	fiBold = 1 << 0, fiItalic = 1 << 1, fiUnderline = 1 << 2 };
enum {	fhComboBox = 1 << 0, fhComboBoxEx = 1 << 1, fhEdit = 1 << 2, fhNumeric = 1 << 3, fhValute = 1 << 4, fhSortAble = 1 << 5, fhImage = 1 << 6, fhNoSortArrow = 1 << 7, fhNoResizeColumn = 1 << 8, fhColumnHasImage = 1 << 9 };
enum {	ptUseColor = 1 << 0, ptUseFonts = 1 << 1, ptListName = 1 << 2, ptPageNumbers = 1 << 3, ptPageDate = 1 << 4 };

/////////////////////////////////////////////////////////////////////////////
// CGfxListCtrl window
class CSortClass
{
public:
	CSortClass(CListCtrl * _pWnd, const int _iCol, const bool _bIsNumeric, const bool _bIsValute = false);
	virtual ~CSortClass();

	int iCol;
	CListCtrl * pWnd;
	bool bIsNumeric, bIsValute;
	void Sort(const bool bAsc);

	static int CALLBACK CompareAsc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK CompareDes(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	static int CALLBACK CompareAscI(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK CompareDesI(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

public:
	class CSortItem
	{
	public:
		virtual  ~CSortItem();
		CSortItem(const DWORD _dw, const CString &_txt);
		CString txt;
		DWORD dw;
	};
	class CSortItemInt
	{
	public:
		CSortItemInt(const DWORD _dw, CString &_txt, bool bIsValute = false);
		int iInt ;
		DWORD dw;
	};
};

enum {	NTEX_ITEMINFO = 0, NTEX_COMBOREQUEST = 1, NTEX_SETTEXT = 2, NTEX_DIVIDER = 3, NTEX_AUTOPREVIEW = 4 };

class LXHDREX
{
public:
	LXHDREX() 
	{
		iNotifyCode = -1;
		CtrlId = -1;
		pComboArray = NULL;
		dwMask = dwFlag = 0;
	};

	virtual ~LXHDREX() {};

	enum {	exBold = (1 << 0), exItalic = (1 << 1), exUnderline = (1 << 2), exHFont = (1 << 3), 
			exTextColor = (1 << 4), exBackColor = (1 << 5), exText = (1 << 6), exComboArray = (1 << 7)
	};

	int			iNotifyCode;
	int			CtrlId;
	int			iItem, iSubItem;
	DWORD		dwItemData;
	DWORD		dwMask;
	DWORD		dwFlag;
	COLORREF	crText, crBack;
	HFONT		hfText;
	CString		csText;
	CStringArray * pComboArray;
};

class LXHDREX_DIV : public LXHDREX
{
public:
	LXHDREX_DIV() { pDC = NULL; };
	virtual ~LXHDREX_DIV() {};
	LXHDREX_DIV(LXHDREX * pRex)
	{
		iNotifyCode = pRex->iNotifyCode;
		CtrlId = pRex->CtrlId;
		iItem = pRex->iItem;
		iSubItem = pRex->iSubItem;
		dwItemData = pRex->dwItemData;
		pDC = NULL;
	};

	CDC *	pDC;
	CRect	rcItem;
};


class CGfxListCtrl : public CListCtrl
{
// Construction
public:
	CGfxListCtrl();
	CGfxHeaderCtrl wndHeader;

	CGfxColumnManager * pManager;
	CGfxCategoryManager * pCategoryManager;

	COLORREF m_clrText, crBackSel, m_clrTextBk, m_clrBkgnd, crCategoryBck, cr3dFace;

	int iCtrlId;
	int iSubItemFocus;
	int m_cxClient;
	int m_cxStateImageOffset;

	int iItemHeight;
	int iAutoPreviewHeight;
	int iItemHeightCategory;

	void SetItemHeight(const int iHeight, const bool bCategory = false);
	void SetAutoPreviewHeight(const int iHeight = 0);
	int  GetAutoPreviewHeight() const;

	int iInternal1;

	CPen * gpn, *gcatpn;

	CFont	ftNormal, ftUnderline, ftBold, ftItalic;

	CWnd * pReciper;

	CWnd * GetReciper() const { return pReciper ? pReciper : GetParent(); };

// Database Bind Mode
public:
	bool			bDaoBind;
	//-TE-CDaoRecordset * pRecordSet;
	//-TE-bool			BindDaoRecordset(CDaoRecordset * pSet);
	bool			FillRecordsetColumn();
	bool			FillDaoItems();
	void			OnDaoGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	void			OnDaoGetTextCallback(int iIndex, int iSubItem, long lCode, CString &cs);
	long			GetExInfoCallback(LXHDREX * pLx);

// Printing support
public:
	void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	CFont pft, pfb,	pfi, pfu;
	int iPrintCountPerPage;
	CRect rcMarginMM;
	DWORD dwPrintFlag;
	CString csPrintName;
	void SetPrintFlag(const DWORD dwf);
	void SetPrintName(const char * name);
	void SetMargins(const int left, const int top, const int right, const int bottom);

// Bitmap background
public:
	bool bBlendBitmap;
	CPalette m_pal;
	CBitmap m_bitmap;
	int m_cxBitmap, m_cyBitmap;
	CImageList cBackImage;
	bool SetBkImage(UINT nIDResource);
	bool SetBkImage(LPCTSTR lpszResourceName);
	void SetBlendBitmap(const bool bBlend);

// Attributes
public:
	enum { OFFSET_FIRST = 2, OFFSET_OTHER = 6 };

	long	(CWnd::*m_fpExInfoFun)(LXHDREX *);
	void	(CWnd::*m_fpGetTextCallback)(int , int, long, CString &);
	void	(CWnd::*m_fpCategoryFun)(CGfxCategoryManager * , long &);
	void	(CWnd::*m_fpDaoCategoryFun)(CGfxCategoryManager *);

	void	SetExInfoCallback(long (CWnd::*fpExInfoFun)(LXHDREX *));
	void	SetCategoryCallback(void (CWnd::*fpCategoryFun)(CGfxCategoryManager * , long &));
	void	SetGetTextCallback(void (CWnd::*fpGetTextCallback)(int , int, long, CString &));
	void	SetDaoCategoryCallback(void (CWnd::*fpDaoCategoryFun)(CGfxCategoryManager *));

	DWORD	dwFlag;
	DWORD	dwhCombo, dwhComboEx, dwhEdit, dwhNumeric, dwhValute, dwhImages;
	DWORD	wdhExInfoOnCol;

	void SetNumeric(const int iCol);
	void SetValute(const int iCol);
	void SetEditCol(const int iCol);
	void SetComboCol(const int iCol);
	void SetComboExCol(const int iCol);
	void SetExColRequest(const int iCol);
	void DontDrawSortArrow(const int iCol);
	bool NeedColExInfo(const int iCol) const;

	CImageList * pItemImageList;
	void SetItemImageList(CImageList * pList);


// Operations
public:
	CGfxListTip	wndToolTip;
	int CellRectFromPoint(CPoint & point, RECT * cellrect, int * col) const;

	// Drag column
	void DragColumn(int &source, int &dest);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGfxListCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	virtual void DrawItemCategory(LPDRAWITEMSTRUCT lpDrawItemStruct);

// Implementation
public:
	//-TE-bool LinkRecordset(const char * cMainRecord, CDaoRecordset * ps, const char * cLinkRecord, const char * cTextField);
	//-TE-bool LinkRecordset(const int iColId, CDaoRecordset * ps, const int iLnk, const int iTxtLnk);
	bool EnableMoveNext();
	bool EnableMovePrev();
	bool EnableMoveLast();
	bool EnableMoveFirst();
	void OnMovePrevRecord();
	void OnMoveNextRecord();
	void OnMoveLastRecord();
	void OnMoveFirstRecord();
	void ModifyExStyle(DWORD dwRemove, DWORD dwAdd, UINT dwRedraw = 0);
	void DeleteAllColumns();

	void ModifyItemEx(const int iIndex, const int iSubItem, const long lData, CString &cs);
	void ModifyItemEx(const int iIndex, const int iSubItem, const long lData);
	void DeleteItemEx(const int iIndex, const long lData);
	void GetItemTextEx(const int idx, const int sub, CString &cs, const unsigned long *dwData = NULL);
	int InsertItemEx(const int iIndex, const long lData);
	void EnableCategoryView(const bool bEnab = true);
	CGfxCategoryManager * GetCategoryManager();
	CGfxCategoryManager * CreateCategoryManager();
	void RetrieveColumnData();
	void SetupColumnData();
	CGfxColumnManager * GetColumnManager();
	CGfxColumnManager * CreateColumnManager();
	void EnableColumnDrag(const bool bEnableDrag = true);
	bool IsColumnDragEnabled() const { return wndHeader.bEnableDrag; };
	int GetColumnIndex(const int iCol) const;
	bool DoCopyInClipboard(const bool bOnlySel = true);
	int GetColumnCount() const;
	void ResetScrollBar();
	void SetColumnImage(const int iCol, const int iImage);
	void SetHeaderImageList(CImageList * pIma);
	void SetSubItemImage(const int iItem, const int iSubItem, const int iIndex);
	void RemoveAllSelection();
	void GetSubItemRect(const int nItem, const int nCol, CRect &rcItem);
	bool EnsureSubItemVisible(const int iSubItem);
	int HitTestEx(CPoint & point, int * col) const;
	CGfxInCombo * ComboSubLabel(int nItem, int nCol, bool bEditable = false, bool bClick = true);
	CRichEditCtrl * EditSubLabel(int nItem, int nCol, bool bClick = true);
	void OnInit();
	void ModifyFlag(const DWORD dwRemove, const DWORD dwAdd, const UINT dwRedraw);
	DWORD GetFlag() const { return dwFlag; };
	LPCTSTR MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset);
	void MakeShortString(CDC* pDC, CString &cs, int nColumnLen, int nOffset);
	int InsertColumnEx(int iPos, const char * cText, int iAlign, int iWidth, DWORD exData); // LVCFMT_LEFT
	virtual ~CGfxListCtrl();
	bool AskForInfo(LXHDREX * pLx, CDC *pDC);
	long SendInfoExMsg(LXHDREX * pLx);

	// Generated message map functions
	//-TE-afx_msg void OnGfxCustomizehead();
	//-TE-afx_msg void OnGfxFormatheader();
protected:
	//{{AFX_MSG(CGfxListCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateGfxCustomizehead(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGfxFormatheader(CCmdUI* pCmdUI);
	afx_msg void OnGfxSortasc();
	afx_msg void OnUpdateGfxSortasc(CCmdUI* pCmdUI);
	afx_msg void OnGfxSortdesc();
	afx_msg void OnUpdateGfxSortdesc(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	afx_msg LRESULT OnSetTextColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetTextBkColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetBkColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetImageList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserTab(WPARAM wParam, LPARAM lParam);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

//	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
};


inline void CGfxListCtrl::SetAutoPreviewHeight(const int iHeight) 
	{ 
		iAutoPreviewHeight = iHeight; 
		if (GetSafeHwnd())
		{
			if (GetFocus() != this) SetFocus();
			if (pCategoryManager == NULL) 
			{
				Invalidate(); 
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
	};

inline int CGfxListCtrl::GetAutoPreviewHeight() const 
	{ return iAutoPreviewHeight; };

inline void CGfxListCtrl::SetPrintFlag(const DWORD dwf) 
	{ dwPrintFlag = dwf; }

inline void CGfxListCtrl::SetPrintName(const char * name) 
	{ csPrintName = name; };

inline void CGfxListCtrl::SetMargins(const int left, const int top, const int right, const int bottom) 
	{ rcMarginMM.SetRect(left,top,right,bottom); }

inline void CGfxListCtrl::SetBlendBitmap(const bool bBlend) 
	{ bBlendBitmap = bBlend; }

inline void CGfxListCtrl::SetNumeric(const int iCol) 
	{ dwhNumeric |= (1 << iCol); };

inline void CGfxListCtrl::SetValute(const int iCol) 
	{ dwhValute |= (1 << iCol); };

inline void CGfxListCtrl::SetEditCol(const int iCol) 
	{ dwhEdit |= (1 << iCol); };

inline void CGfxListCtrl::SetComboCol(const int iCol)
	{ dwhCombo |= (1 << iCol); };

inline void CGfxListCtrl::SetComboExCol(const int iCol)
	{ dwhComboEx |= (1 << iCol); };

inline void CGfxListCtrl::SetExColRequest(const int iCol)
	{ wdhExInfoOnCol |= (1 << iCol); };

inline void CGfxListCtrl::DontDrawSortArrow(const int iCol)
	{ wndHeader.dwDontShowSortArrow |= (1 << iCol); };

inline bool CGfxListCtrl::NeedColExInfo(const int iCol) const
	{
		if (dwFlag&fExInfo)
		{
			if (dwFlag&fExInfoOnRow) return iCol == 0 ? true : false;
			if (dwFlag&wdhExInfoOnCol) return wdhExInfoOnCol & (1 << GetColumnIndex(iCol)) ? true : false;
			return true;
		}
		return false;
	};

inline void CGfxListCtrl::SetItemImageList(CImageList * pList) 
	{ pItemImageList = pList; };
inline void	CGfxListCtrl::SetExInfoCallback(long (CWnd::*fpExInfoFun)(LXHDREX *)) 
	{ m_fpExInfoFun = fpExInfoFun; };
inline void	CGfxListCtrl::SetCategoryCallback(void (CWnd::*fpCategoryFun)(CGfxCategoryManager * , long &)) 
	{ m_fpCategoryFun = fpCategoryFun; };
inline void	CGfxListCtrl::SetGetTextCallback(void (CWnd::*fpGetTextCallback)(int , int, long, CString &)) 
	{ m_fpGetTextCallback = fpGetTextCallback; };
inline void	CGfxListCtrl::SetDaoCategoryCallback(void (CWnd::*fpDaoCategoryFun)(CGfxCategoryManager *)) 
	{ m_fpDaoCategoryFun = fpDaoCategoryFun; };

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GFXLISTCTRL_H__31F5CEA8_E5CA_11D1_86E7_000000000000__INCLUDED_)
