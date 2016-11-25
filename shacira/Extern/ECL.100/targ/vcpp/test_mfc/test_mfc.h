// TEST_MFC.h : main header file for the TEST_MFC application
//

#if !defined(AFX_TEST_MFC_H__E0458A4A_ED1F_11D4_A273_0050BF06AB37__INCLUDED_)
#define AFX_TEST_MFC_H__E0458A4A_ED1F_11D4_A273_0050BF06AB37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWrapper_testApp:
// See TEST_MFC.cpp for the implementation of this class
//

class CWrapper_testApp : public CWinApp
{
public:
	CWrapper_testApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWrapper_testApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWrapper_testApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_MFC_H__E0458A4A_ED1F_11D4_A273_0050BF06AB37__INCLUDED_)
