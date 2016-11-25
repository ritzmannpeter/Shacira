// TEST_MFCDoc.cpp : implementation of the CWrapper_testDoc class
//

#include "stdafx.h"
#include "TEST_MFC.h"

#include "TEST_MFCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWrapper_testDoc

IMPLEMENT_DYNCREATE(CWrapper_testDoc, CDocument)

BEGIN_MESSAGE_MAP(CWrapper_testDoc, CDocument)
	//{{AFX_MSG_MAP(CWrapper_testDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWrapper_testDoc construction/destruction

CWrapper_testDoc::CWrapper_testDoc()
{
}

CWrapper_testDoc::~CWrapper_testDoc()
{
}

BOOL CWrapper_testDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWrapper_testDoc serialization

void CWrapper_testDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWrapper_testDoc diagnostics

#ifdef _DEBUG
void CWrapper_testDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWrapper_testDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWrapper_testDoc commands
