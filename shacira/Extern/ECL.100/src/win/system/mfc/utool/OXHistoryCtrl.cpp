// ==========================================================================
//						   Class Implementation
// 							  COXHistoryCtrl
// ==========================================================================

// Copyright © Dundas Software Ltd. 1997 - 1999, All Rights Reserved
						
// //////////////////////////////////////////////////////////////////////////


#include "../stdafx.h"
#include "OXHistoryCtrl.h"

#include <afxdisp.h>

// default maximum number of history entries displayed in the control window
const int OXHISTCTRL_MAXENTRIES=100;


IMPLEMENT_DYNCREATE(COXHistoryCtrl, COXScrollWnd)

BEGIN_MESSAGE_MAP(COXHistoryCtrl, COXScrollWnd)
	//{{AFX_MSG_MAP(COXHistoryCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

COXHistoryCtrl::COXHistoryCtrl()
{
	//setup the critical section variable
	InitializeCriticalSection(&m_criticalSection);

	//logging variables
	m_sLogFileName=_T("");
	m_bEnableLog=FALSE;
	m_bTimeStampedLog=FALSE;
	m_logDay=0;
	m_logMonth=0;
	m_logYear=0;
	m_bTruncateLogFile=FALSE;

	//display properties
	m_clrText=::GetSysColor(COLOR_WINDOWTEXT);
	m_clrBack=::GetSysColor(COLOR_WINDOW);
	m_clrLeftOverBack=::GetSysColor(COLOR_WINDOW);
	m_nAlignment=DT_LEFT;
	m_nOffset=0;

	m_sizeSymbol=CSize(0,0);
	
	//max number of entries
	m_nMaxNumEntries=OXHISTCTRL_MAXENTRIES;

	//max line length
	m_nMaxLengthEntry=0;

	//datestamp to string format
	SetTimeStampFormat(_T("%X"));
}

COXHistoryCtrl::~COXHistoryCtrl()
{
	CloseLog();

	m_arrEntries.RemoveAll();

	//release the critical section
	DeleteCriticalSection(&m_criticalSection);
}


void COXHistoryCtrl::EnableLog(BOOL bYesNo)
{
	m_bEnableLog=bYesNo;
	if(m_bEnableLog)
		OpenLog();
	else
		CloseLog();
}


BOOL COXHistoryCtrl::AddLine(CString string, BOOL bAddToLog/*=TRUE*/)
{
	//enter into a critical section
	EnterCriticalSection(&m_criticalSection);

	//update the log file
	if(bAddToLog && m_bEnableLog)
		WriteToLog(string,TRUE);

	BOOL bUpdateScroll=FALSE;

	ASSERT(m_arrEntries.GetCount()<=GetMaxNumEntries());

	HISTORYENTRY entry(string,m_clrText,m_clrBack,m_nOffset,m_nAlignment);
	m_arrEntries.AddTail(entry);
	
	if(m_arrEntries.GetCount()==GetMaxNumEntries()+1)
	{
		entry=m_arrEntries.RemoveHead();
		ASSERT(entry.m_sText.GetLength()<=m_nMaxLengthEntry);
		if(entry.m_sText.GetLength()==m_nMaxLengthEntry)
		{
			UpdateMaxLengthInfo();
			bUpdateScroll=TRUE;
		}
	}
	else
		bUpdateScroll=TRUE;

	int nLength=string.GetLength();
	if(m_nMaxLengthEntry<nLength)
	{
		m_nMaxLengthEntry=nLength;
		bUpdateScroll=TRUE;
	}

	if(bUpdateScroll)
		UpdateScrollInfo();

	ScrollToEnd();

   #ifdef __Want_Ultra_Slow_Window_Refresh__
      RedrawWindow();
   #else
      // 01.04.2002 -TE- Das Ausblenden des standardmaessig gesetzten UPDATENOW-Flags
      // sorgt fuer den unglaublichen Geschwindigkeitszuwachs bei Scrollen
   	RedrawWindow(NULL, NULL, RDW_INVALIDATE /*| RDW_UPDATENOW*/ | RDW_ERASE );
   #endif

	//exit the critical section
	LeaveCriticalSection(&m_criticalSection);

	return TRUE;
}


BOOL COXHistoryCtrl::AddStampedLine(CString string,
									BOOL bAddToLog/*=TRUE*/)
{
	CString sStampedString=GetTimeDateStamp()+_T(" ")+string;
	BOOL bReturn=AddLine(sStampedString,bAddToLog);

	return bReturn;
}


BOOL COXHistoryCtrl::AppendToLine(CString string,
								  BOOL bAddToLog/*=TRUE*/)
{
	//enter into a critical section
	EnterCriticalSection(&m_criticalSection);

	if(m_arrEntries.IsEmpty())
		return FALSE;

	//update the log file
	if(bAddToLog && m_bEnableLog)
		WriteToLog(string,FALSE);

	HISTORYENTRY entry=m_arrEntries.GetTail();
	entry.m_sText+=string;
	m_arrEntries.SetAt(m_arrEntries.GetTailPosition(),entry);

	int nLength=entry.m_sText.GetLength();
	if(m_nMaxLengthEntry<nLength)
	{
		m_nMaxLengthEntry=nLength;
		UpdateScrollInfo();
	}

	ScrollToEnd();
	RedrawWindow();

	//exit the critical section
	LeaveCriticalSection(&m_criticalSection);

	return TRUE;
}


BOOL COXHistoryCtrl::ClearHistory()
{
	//enter into a critical section
	EnterCriticalSection(&m_criticalSection);

	m_arrEntries.RemoveAll();

	//max line length
	m_nMaxLengthEntry=0;

	UpdateScrollInfo();
	RedrawWindow();

	//exit the critical section
	LeaveCriticalSection(&m_criticalSection);

	return TRUE;
}


CString COXHistoryCtrl::GetTimeDateStamp() const
{
	//get the time/date
	COleDateTime time=COleDateTime::GetCurrentTime();
	return time.Format(GetTimeStampFormat());
}


int COXHistoryCtrl::OpenLog()
{
	CloseLog();

	CString sFileName=m_sLogFileName;
	if(m_bTimeStampedLog)
	{
		//get the time/date
		COleDateTime date=COleDateTime::GetCurrentTime();
		m_logDay=date.GetDay();
		m_logMonth=date.GetMonth();
		m_logYear=date.GetYear();
		CString sStampedLogFileName;
		sStampedLogFileName.Format(_T("%2.2d%2.2d%4.4d"),
			m_logDay,m_logMonth,m_logYear);
		
		//find the extension
		int nPos=m_sLogFileName.Find(_T("."));
		if(nPos!=-1)
			sStampedLogFileName+=m_sLogFileName.Mid(nPos);
		m_sTimeStampedLogFileName=sFileName=sStampedLogFileName;
	}

	BOOL bResult=m_fileLog.Open(sFileName,CFile::modeCreate|CFile::modeWrite|
		(GetTruncateLogFile() ? 0 : CFile::modeNoTruncate));
	if(bResult && !GetTruncateLogFile())
		m_fileLog.SeekToEnd();
	return bResult;
}


BOOL COXHistoryCtrl::CloseLog()
{
	if(m_fileLog.m_hFile!=CFile::hFileNull)
	{
		TRY
		{
			m_fileLog.Close();
		}
		CATCH(CFileException,pException)
		{
			UNREFERENCED_PARAMETER(pException);
			return FALSE;
		}
		END_CATCH
	}

	return TRUE;
}


void COXHistoryCtrl::WriteToLog(CString string, BOOL bNewLine)
{
	if(!m_bEnableLog)
		return;

	COleDateTime date=COleDateTime::GetCurrentTime();
	//check to see if the date has changed
	if(m_bTimeStampedLog)
	{
		if(m_logDay!=date.GetDay() || m_logMonth!=date.GetMonth() ||
			m_logYear!=date.GetYear())
		{
			OpenLog();
		}
		else if(m_logDay==date.GetDay() || m_logMonth!=date.GetMonth() ||
			m_logYear!=date.GetYear())
		{
#if _MSC_VER >= 1300
			if(bNewLine && m_fileLog.m_hFile!=(HANDLE)-1)
#else
			if(bNewLine && m_fileLog.m_hFile!=(UINT)-1)
#endif
				m_fileLog.Write(_T("\r\n"),2*sizeof(TCHAR));
		}
	}
	else
	{
#if _MSC_VER >= 1300
		if(m_fileLog.m_hFile==(HANDLE)-1)
#else
		if(m_fileLog.m_hFile==(UINT)-1)
#endif
		{
			OpenLog();
		}
		else
		{
#if _MSC_VER >= 1300
			if(bNewLine && m_fileLog.m_hFile!=(HANDLE)-1)
#else
			if(bNewLine && m_fileLog.m_hFile!=(UINT)-1)
#endif
				m_fileLog.Write(_T("\r\n"),2*sizeof(TCHAR));
		}
	}
	
#if _MSC_VER >= 1300
	if(m_fileLog.m_hFile!=(HANDLE)-1)
#else
	if(m_fileLog.m_hFile!=(UINT)-1)
#endif
		m_fileLog.Write(string,string.GetLength()*sizeof(TCHAR));
}


void COXHistoryCtrl::SetMaxNumEntries(int nMaxNum)
{
	if(nMaxNum<0)
		return;

	BOOL bUpdateScroll=FALSE;

	if(nMaxNum<GetMaxNumEntries())
	{
		int nEntriesToDelete=GetNumEntries()-nMaxNum;
		HISTORYENTRY entry;
		for(int nIndex=0; nIndex<nEntriesToDelete; nIndex++)
		{
			entry=m_arrEntries.RemoveHead();
			ASSERT(entry.m_sText.GetLength()<=m_nMaxLengthEntry);
			if(entry.m_sText.GetLength()==m_nMaxLengthEntry)
			{
				UpdateMaxLengthInfo();
			}
		}
		bUpdateScroll=TRUE;
	}

	m_nMaxNumEntries=nMaxNum;

	if(bUpdateScroll)
		UpdateScrollInfo();
}

/////////////////////////////////////////////////////////////////

void COXHistoryCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	OnPrepareDC(&dc);

	int nSavedDC=dc.SaveDC();
	ASSERT(nSavedDC!=0);

	ASSERT((HFONT)m_font!=NULL);
	dc.SelectObject(&m_font);

	//start from the bottom of the rect and work up
	CRect rect;
	GetClientRect(rect);
	CSize sizeTotal=GetTotalSize();
	if(sizeTotal.cx>rect.Width())
		rect.right=rect.left+sizeTotal.cx;
	if(sizeTotal.cy>rect.Height())
		rect.bottom=rect.top+sizeTotal.cy;

	CRect rectCopy=rect;


	HISTORYENTRY entry;
	POSITION pos=m_arrEntries.GetHeadPosition();

	int nEntries=GetNumEntries();
	rectCopy.top =0;
	rectCopy.bottom =0;
	for(int nIndex=0; nIndex<nEntries; nIndex++)
	{
		if(pos!=NULL)
		{
			entry=m_arrEntries.GetNext(pos);
			rectCopy.bottom+=m_sizeSymbol.cy;

			dc.SetTextColor(entry.m_clrText);
			dc.SetBkMode(TRANSPARENT);
			CRect rectItem=rectCopy;
			CBrush brush(entry.m_clrBack);
			dc.FillRect(rectItem,&brush);
			rectItem.left+=entry.m_nOffset;
			dc.DrawText(entry.m_sText,rectItem,
				DT_SINGLELINE|DT_VCENTER|entry.m_nAlignment);

			rectCopy.top=rectCopy.bottom;
		}
		else
			break;
	}

	if(rectCopy.bottom<rect.bottom)
	{
		rectCopy.bottom=rect.bottom;
		dc.FillSolidRect(rectCopy,m_clrLeftOverBack);
	}

	VERIFY(dc.RestoreDC(nSavedDC));

	// Do not call COXScrollWnd::OnPaint() for painting messages
}

BOOL COXHistoryCtrl::Initialize()
{
	if(!COXScrollWnd::Initialize())
		return FALSE;

#ifdef OXSCRLWND_USE_RULER
	DetachRuler();
#endif	//	OXSCRLWND_USE_RULER

	SetScrollSizes(MM_TEXT,CSize(0,0),CSize(0,0),CSize(0,0));

	// Create a fixed size font
	CFont font;
	font.CreateFont(	0,						// nHeight
						0,						// nWidth
						0,						// nEscapement
						0,						// nOrientation
						FW_DONTCARE,			// nWeight
						FALSE,					// bItalic
						FALSE,					// bUnderline
						0,						// cStrikeOut
						DEFAULT_CHARSET,		// nCharSet
						OUT_DEFAULT_PRECIS,		// nOutPrecision
						CLIP_DEFAULT_PRECIS,	// nClipPrecision
						DEFAULT_QUALITY,		// nQuality
						FIXED_PITCH,			// nPitchAndFamily
						NULL);					// lpszFacename

	SetFont(&font, FALSE);

	return TRUE;
}

void COXHistoryCtrl::SetFont(CFont* pFont, BOOL bRedraw/*=TRUE*/)
{
	ASSERT(pFont!=NULL);
	ASSERT((HFONT)*pFont!=NULL);

	if((HFONT)m_font!=NULL)
		m_font.DeleteObject();

	LOGFONT lf;
	VERIFY(pFont->GetLogFont(&lf)!=0);
	VERIFY(m_font.CreateFontIndirect(&lf));

	UpdateFontInfo();
	UpdateScrollInfo();

	if(bRedraw)
		RedrawWindow();
}

BOOL COXHistoryCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	UNREFERENCED_PARAMETER(pDC);
	return TRUE;
}

void COXHistoryCtrl::UpdateFontInfo()
{
	//get the symbol height and width
	CDC* pDC=GetDC();
	ASSERT_VALID(pDC);

	CFont* pOldFont=pDC->SelectObject(&m_font);
	
	::GetTextExtentPoint(pDC->GetSafeHdc(),_T("X"),1,&m_sizeSymbol);
	
	if(pOldFont!=NULL)
	{
		pDC->SelectObject(pOldFont);
	}
	ReleaseDC(pDC);
}


void COXHistoryCtrl::UpdateScrollInfo()
{
//	CPoint ptCurrent=GetDeviceScrollPosition();

	CRect rect;
	GetClientRect(rect);
	CSize sizeTotal(m_nMaxLengthEntry*m_sizeSymbol.cx,
		GetNumEntries()*m_sizeSymbol.cy+rect.Height()%m_sizeSymbol.cy);
	CSize sizePage(m_sizeSymbol.cx,m_sizeSymbol.cy);
	if(m_sizeSymbol.cx<rect.Width())
	{
		sizePage.cx=(rect.Width()/m_sizeSymbol.cx)*m_sizeSymbol.cx;
	}
	if(m_sizeSymbol.cy<rect.Height())
	{
		sizePage.cy=(rect.Height()/m_sizeSymbol.cy)*m_sizeSymbol.cy;
	}
	CSize sizeLine=m_sizeSymbol;

	SetScrollSizes(MM_TEXT,sizeTotal,sizePage,sizeLine);

//	ScrollToDevicePosition(ptCurrent);
}

void COXHistoryCtrl::UpdateMaxLengthInfo()
{
	m_nMaxLengthEntry=0;
	HISTORYENTRY entry;
	POSITION pos=m_arrEntries.GetHeadPosition();
	while(pos!=NULL)
	{
		entry=m_arrEntries.GetNext(pos);
		int nLength=entry.m_sText.GetLength();
		if(m_nMaxLengthEntry<nLength)
		{
			m_nMaxLengthEntry=nLength;
		}
	}
}

int COXHistoryCtrl::GetVisibleCount()
{
	ASSERT(::IsWindow(GetSafeHwnd()));

	CRect rect;
	GetClientRect(rect);

	int nResult=rect.Height()/m_sizeSymbol.cy;
	nResult=(nResult>GetNumEntries() ? GetNumEntries() : nResult);

	return nResult;
}


void COXHistoryCtrl::ScrollToEnd()
{
	CPoint ptScroll=GetScrollPosition();
	ptScroll.y=GetNumEntries()*m_sizeSymbol.cy;
	ScrollToPosition(ptScroll);
}



CString COXHistoryCtrl::GetTimeStampedFileName()
{
	COleDateTime date=COleDateTime::GetCurrentTime();
	int logDay=date.GetDay();
	int logMonth=date.GetMonth();
	int logYear=date.GetYear();
	m_sTimeStampedLogFileName.Format(_T("%2.2d%2.2d%4.4d"),
		logDay,logMonth,logYear);
	
	//find the extension
	int nPos=m_sLogFileName.Find(_T("."));
	if(nPos!=-1)
		m_sTimeStampedLogFileName+=m_sLogFileName.Mid(nPos);
	return m_sTimeStampedLogFileName;
}
