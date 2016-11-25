// TEST_MFCView.cpp : implementation of the CWrapper_testView class
//

#include "stdafx.h"
#include "TEST_MFC.h"

#include "TEST_MFCDoc.h"
#include "TEST_MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWrapper_testView

IMPLEMENT_DYNCREATE(CWrapper_testView, CView)

BEGIN_MESSAGE_MAP(CWrapper_testView, CView)
	//{{AFX_MSG_MAP(CWrapper_testView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWrapper_testView construction/destruction

CWrapper_testView::CWrapper_testView()
{
}

CWrapper_testView::~CWrapper_testView()
{
}

BOOL CWrapper_testView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWrapper_testView drawing

void CWrapper_testView::OnDraw(CDC* pDC)
{
	CWrapper_testDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CWrapper_testView diagnostics

#ifdef _DEBUG
void CWrapper_testView::AssertValid() const
{
	CView::AssertValid();
}

void CWrapper_testView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWrapper_testDoc* CWrapper_testView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWrapper_testDoc)));
	return (CWrapper_testDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWrapper_testView message handlers
