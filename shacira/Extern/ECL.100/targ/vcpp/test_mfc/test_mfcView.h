// TEST_MFCView.h : interface of the CWrapper_testView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST_MFCVIEW_H__E0458A52_ED1F_11D4_A273_0050BF06AB37__INCLUDED_)
#define AFX_TEST_MFCVIEW_H__E0458A52_ED1F_11D4_A273_0050BF06AB37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWrapper_testView : public CView
{
protected: // create from serialization only
	CWrapper_testView();
	DECLARE_DYNCREATE(CWrapper_testView)

// Attributes
public:
	CWrapper_testDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWrapper_testView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWrapper_testView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWrapper_testView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TEST_MFCView.cpp
inline CWrapper_testDoc* CWrapper_testView::GetDocument()
   { return (CWrapper_testDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_MFCVIEW_H__E0458A52_ED1F_11D4_A273_0050BF06AB37__INCLUDED_)
