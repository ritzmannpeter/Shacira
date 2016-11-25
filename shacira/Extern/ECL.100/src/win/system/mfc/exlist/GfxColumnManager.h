// GfxColumnManager.h: interface for the CGfxColumnManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GFXCOLUMNMANAGER_H__BA849A59_FED4_11D1_83D4_0000B43382FE__INCLUDED_)
#define AFX_GFXCOLUMNMANAGER_H__BA849A59_FED4_11D1_83D4_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGfxListCtrl;

class CGfxColumnManager  
{
public:
	CGfxColumnManager();
	CGfxColumnManager(const CGfxColumnManager * p);
	virtual ~CGfxColumnManager();
	int DefineColumn(const int iId, const char * cText, const char * cTextDt = NULL, const int iAlign = LVCFMT_LEFT, const int iWidth = 80, DWORD dwData = 0, const int iImage = -1, const char * cDescr = NULL);

public:
	//-TE-bool LinkRecordset(const int iId, CDaoRecordset * ps, const int iLnk, const int iTxtLnk);
	bool IsDefColumn(const int iId) const;
	int FindColumnById(const int iId) const;
	bool CustomizeColumn(CGfxListCtrl * pList, CWnd * pParent = NULL);
	bool SetupColumnData(CGfxListCtrl * pList, const bool bNeedOwnerDraw = false);
	bool RetrieveColumnData(CGfxListCtrl * pList);
	bool DefineDefaultColumns(const int iCount, const int * iCols);
	void ReadFromProfile(const char * cListName);
	void WriteToProfile(const char * cListName);
	class CGfxColumn
	{
	public:
		void Clear();
		void Init(const int _iId, const char * _cText, const char * _cTextDt, const int _iAlign, const int _iWidth, DWORD _dwData, const int _iImage, const char * _cDescr);
		CGfxColumn();
		virtual ~CGfxColumn();

		int iId, iAlign, iWidth, iImage;
		DWORD dwData;
		char * cText, * cTextDt, * cDescr;

		//-TE-CDaoRecordset * pSet;
		int				iLinkField, iTextField;
	};

	int			 iColumnData;
	CGfxColumn * pColumnData;

	int			 iDefColumn;
	int	*		 pDefColumn;
};

#endif // !defined(AFX_GFXCOLUMNMANAGER_H__BA849A59_FED4_11D1_83D4_0000B43382FE__INCLUDED_)
