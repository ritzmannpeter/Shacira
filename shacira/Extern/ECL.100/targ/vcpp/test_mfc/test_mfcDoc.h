// TEST_MFCDoc.h : interface of the CWrapper_testDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST_MFCDOC_H__E0458A50_ED1F_11D4_A273_0050BF06AB37__INCLUDED_)
#define AFX_TEST_MFCDOC_H__E0458A50_ED1F_11D4_A273_0050BF06AB37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWrapper_testDoc : public CDocument
{
protected: // create from serialization only
	CWrapper_testDoc();
	DECLARE_DYNCREATE(CWrapper_testDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWrapper_testDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWrapper_testDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWrapper_testDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_MFCDOC_H__E0458A50_ED1F_11D4_A273_0050BF06AB37__INCLUDED_)
