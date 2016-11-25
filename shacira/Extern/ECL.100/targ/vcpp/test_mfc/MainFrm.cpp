// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TEST_MFC.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


#include "win/ew_frames.hpp"
#include "win/ew_dialogs.hpp"
#include "win/ew_buttons.hpp"
#include "win/ew_listctls.hpp"
#include "dbi/edb_query.hpp"

cwFrame ecl_frame1, ecl_frame2;
cdbTransaction ecl_ta(cdbDatabase::ODBC, "NWIND", "admin", "");

void CMainFrame::OnFileNew()
{
   cBase::DbgError(">>> Entering OnFileNew()...");
   cBase::setDebugMask(0xffff);

   ecl_frame1.create(0, 123, 0, "Fenster 1");
   ecl_frame1.show();
   ecl_frame1.forceUpdate();

   ecl_frame1.showInfo("Eine Information für den Benutzer");

   // -- Dialog START
   cwDialog ecl_dialog;
   cwButton ecl_button;
   cwListBox ecl_listbox;

   csEnumQuery *query1 = new csEnumQuery("MON$Montag", "TUE$Dienstag",
      "WED$Mittwoch", "THU$Donnerstag", "FRI$Freitag",
      "SAT$Samstag", "SUN$Sonntag", NULL);
   cdbQuery query2(&ecl_ta,
      SQL::SELECT(
         SQL::STYLE_DISTINCT,
         SQL::FIELDS("ArtikelNr,ArtikelName"),
         SQL::FROM("Artikel")
      ));

   ecl_dialog.create(cwResource(IDD_DIALOG1), &ecl_frame1);
   ecl_button.attach(&ecl_dialog, IDC_CHECK1);
   ecl_listbox.attach(&ecl_dialog, IDC_LIST1, 0, &query2);

   ecl_dialog.process(true);

   // -- Dialog END

   ecl_frame2.create(0, 123, 0, "Fenster 2");
   ecl_frame2.show();
   ecl_frame2.forceUpdate();

   ecl_frame1.showError("Da hat sich wohl ein Fehler eingeschlichen...");

   cBase::DbgError("<<< Leaving OnFileNew()...");
}

void CMainFrame::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFrameWnd::OnCommand(wParam, lParam);
}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFrameWnd::WindowProc(message, wParam, lParam);
}

BOOL CMainFrame::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFrameWnd::OnChildNotify(message, wParam, lParam, pLResult);
}
