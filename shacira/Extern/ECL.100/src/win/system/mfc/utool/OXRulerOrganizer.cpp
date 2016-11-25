// ==========================================================================
//				Class Implementation : COXRulerOrganizer
// ==========================================================================

// Copyright © Dundas Software Ltd. 1997-1999, All Rights Reserved                      

// //////////////////////////////////////////////////////////////////////////

#include "../stdafx.h"
#include "OXRulerOrganizer.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

double COXRulerBar::PIXEL_PAD=14.0;

COXRulerBar::COXRulerBar() :
	m_rectInvert(0,0,0,0), 
	m_rectOldInvert(0,0,0,0)
{
	m_bHorizontal=TRUE;
	m_nPos=0;
	m_nZoom=100;
	m_nCalibrate=100;
	m_bOldIsHilited=FALSE;
	m_dDisplayDpi=100.0;
	m_bUseNonDefaultDpi=FALSE;
}

COXRulerBar::~COXRulerBar()
{
}

BOOL COXRulerBar::Init(BOOL bHorizontal /*=TRUE*/, UINT nCalibrate /*=100*/)
{
	m_nCalibrate=nCalibrate;
	m_bHorizontal=bHorizontal;
	
	// for 1, 2, ...
	// font for horizontal bar
    VERIFY(m_font.CreateFont(-12,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,ANSI_CHARSET,
		0,0,0,0,_T("Times New Roman")));
	// font for vertical bar
    VERIFY(m_fontVert.CreateFont(-12,0,900,0,FW_NORMAL,FALSE,FALSE,FALSE,ANSI_CHARSET,
		0,0,0,0,_T("Times New Roman")));

	return TRUE;
}

BEGIN_MESSAGE_MAP(COXRulerBar, CWnd)
	//{{AFX_MSG_MAP(COXRulerBar)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COXRulerBar implementation

BOOL COXRulerBar::Create(CWnd* pParentWnd, BOOL bHorizontal, CRect rect, 
						 DWORD dwStyle/*=WS_CHILD|WS_VISIBLE*/, 
						 UINT nCalibrate/*=100*/, 
						 UINT nID/*=IDC_STATIC*/)
{
	ASSERT(pParentWnd!=NULL);

	WNDCLASS wndClass;
	wndClass.style=CS_DBLCLKS; 
    wndClass.lpfnWndProc=AfxWndProc; 
    wndClass.cbClsExtra=0; 
    wndClass.cbWndExtra=0; 
    wndClass.hInstance=AfxGetInstanceHandle(); 
    wndClass.hIcon=::LoadCursor(NULL,IDC_ARROW); 
    wndClass.hCursor=0; 
    wndClass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1); 
    wndClass.lpszMenuName=NULL; 
	wndClass.lpszClassName=_T("RulerBarWnd");
	
	if(!AfxRegisterClass(&wndClass))
	{
		return FALSE;
	}

	if(!CWnd::Create(wndClass.lpszClassName,NULL,dwStyle,rect,pParentWnd,nID,NULL))
	{
		return FALSE;
	}

	return Init(bHorizontal,nCalibrate);
}

	
void COXRulerBar::DrawTick(CDC* pDC, CRect& rect, double dOffset, BOOL bMidTick)
{
	int nTickX, nTickY;
	int nTickWidth, nTickHeight;

	if(dOffset < 0)
		return;

	if(m_bHorizontal)
	{
		if(bMidTick)
			nTickHeight=rect.Height()/2;
		else
			nTickHeight=rect.Height()/4;

		nTickWidth=0;

		nTickX=(int)floor(rect.left+dOffset);
		nTickY=rect.top+(rect.Height()-nTickHeight+1)/2;
	}
	else
	{
		if(bMidTick)
			nTickWidth=rect.Width()/2;
		else
			nTickWidth=rect.Width()/4;

		nTickHeight=0;
		nTickX=rect.left+(rect.Width()-nTickWidth+1)/2;
		nTickY=(int)floor(rect.top+dOffset);
	}

	CPoint pt(nTickX, nTickY);
	CPoint ptTo(nTickX+nTickWidth, nTickY+nTickHeight);
	if(rect.PtInRect(pt) && rect.PtInRect(ptTo))
	{
		pDC->MoveTo(nTickX, nTickY);
		pDC->LineTo(nTickX+nTickWidth, nTickY+nTickHeight);
	}
}

void COXRulerBar::DrawScale(CDC* pDC, CRect rect)
{
	CBrush bkgndBrush(::GetSysColor(COLOR_WINDOW));
	pDC->FillRect(rect,&bkgndBrush);
	pDC->DrawEdge(rect,EDGE_SUNKEN,BF_RECT);
	rect.DeflateRect(2,2);

	// Clip all output to the rectangle
	pDC->IntersectClipRect(rect);

    CFont* oldFont=NULL;
	if(m_bHorizontal)
		pDC->SelectObject(&m_font);
	else
		pDC->SelectObject(&m_fontVert);
	COLORREF crOldText=pDC->SetTextColor(::GetSysColor(COLOR_BTNTEXT));
	CPen pen(PS_SOLID,1,::GetSysColor(COLOR_BTNTEXT));
	CPen* oldPen=pDC->SelectObject(&pen);
    int oldMode=pDC->SetBkMode(TRANSPARENT);

	double dSpacer=m_nZoom*0.1;
	int nTicksPerUnit=(100!=m_nCalibrate) ? 4 : 10;
	double dDPI=(m_bUseNonDefaultDpi) ? m_dDisplayDpi : 100.0;
	double dPixelsPerUnit=m_nZoom*100.0/m_nCalibrate*dDPI/100.0;
	double dTickSpace=dPixelsPerUnit/nTicksPerUnit;
	double dOrg=nTicksPerUnit-fmod(m_nPos, dSpacer);
	int nSpan=(m_bHorizontal) ? rect.Width() : rect.Height();

	double dSpanEnd=nSpan+2*dSpacer+dPixelsPerUnit;
	int nUnitNumber=(int)(m_nPos/dPixelsPerUnit);

	int nXErr=0;
	int nYErr=0;

	for(double d=dOrg; d<dSpanEnd; d+=dPixelsPerUnit, nUnitNumber++)
	{
		double dPos=-fmod(m_nPos,dPixelsPerUnit)-dOrg;

		// If the space between ticks is greater than PIXEL_PAD/2.0, 
		// draw all of the ticks
		if(dTickSpace>PIXEL_PAD/2.0)
		{
			for(int nIndex=1; nIndex<nTicksPerUnit; nIndex++)
			{	
  				double dOffset=d+dPos+0.5+dTickSpace*nIndex;
				DrawTick(pDC,rect,dOffset,nIndex==nTicksPerUnit/2);
			}
		}
		// Just draw the mid tick
		else if(dPixelsPerUnit>=PIXEL_PAD)
		{
			double dOffset=d+dPos+0.5+dTickSpace*nTicksPerUnit/2;
			DrawTick(pDC,rect,dOffset,TRUE);
		}

		if(dPixelsPerUnit<PIXEL_PAD && nUnitNumber%5)
			continue;

		// draw the unit number, starting at 1
		if(nUnitNumber>0)
		{
			char nCh=(char)(48+(nUnitNumber%10)); // 47 is '0'
			// Keep things as ASCII, since Unicode numeric characters 
			// may be non-consective
			CString sCh(nCh); 

			if(dPixelsPerUnit<PIXEL_PAD)
			{
				int nHundreds=nUnitNumber%100;
				sCh.Format(_T("%d"),nHundreds);
			}

			CSize sNum=pDC->GetOutputTextExtent(sCh);
			int nXPos;
			int nYPos;

			if(m_bHorizontal)
			{
				nXPos=(int)floor(rect.left+d+dPos+0.5-(sNum.cx/2.0));
				nYPos=rect.top+(rect.Height()-sNum.cy)/2;

				if(nXPos <= nXErr)
					continue;
				else
					nXErr=sNum.cx+nXPos;
			}
			else
			{
				nXPos=rect.left+(rect.Width()-sNum.cy)/2; 
				nYPos=(int)floor(rect.top+d+dPos+0.5+(sNum.cx/2.0));

				if(nYPos <= nYErr)
					continue;
				else
					nYErr=sNum.cy+nYPos;
			}

			pDC->TextOut(nXPos, nYPos, sCh);
		}

	}

	// Get rid of the clipping region
	pDC->SelectClipRgn(NULL,RGN_COPY);

    pDC->SetBkMode(oldMode);
	pDC->SelectObject(oldPen);
	pDC->SetTextColor(crOldText);
	pDC->SelectObject(oldFont);
}

void COXRulerBar::DrawRuler(CDC* pDC, CRect rect, CRect rectClip)
{
	ASSERT(pDC!=NULL);
	if(rect.IsRectEmpty() || rectClip.IsRectEmpty())
		return;

	pDC->IntersectClipRect(rectClip);
	DrawScale(pDC,rect);
	pDC->SelectClipRgn(NULL,RGN_COPY);

	if(m_bOldIsHilited)
	{
		CRect rectIntersect;
		rectIntersect.IntersectRect(m_rectOldInvert,rectClip);
		ReverseHilite(pDC,rectIntersect);
	}
}

void COXRulerBar::ReverseHilite(CDC* pDC, CRect rect)
{
	ASSERT(pDC!=NULL);
	pDC->PatBlt(rect.left,rect.top,rect.Width(),rect.Height(),PATINVERT);
}

void COXRulerBar::Hilite(CDC* pDC, CRect rect, int nStartPos, int nWidth/*=1*/)
{
	ASSERT(pDC!=NULL);

	BOOL bRemoveHilite=FALSE;
	m_rectInvert=rect;
	m_rectInvert.DeflateRect(2,2);

	if(m_bHorizontal)
	{
		m_rectInvert.left+=nStartPos;
		bRemoveHilite=((m_rectInvert.left<=2) || (m_rectInvert.left>=m_rectInvert.right));
		m_rectInvert.right=m_rectInvert.left+nWidth;
		if(m_rectInvert.right>rect.right-2)
			m_rectInvert.right=rect.right-2;
	}
	else
	{
		m_rectInvert.top+=nStartPos;
		bRemoveHilite=((m_rectInvert.top<=2) || (m_rectInvert.top>=m_rectInvert.bottom));
		m_rectInvert.bottom=m_rectInvert.top+nWidth;
		if(m_rectInvert.bottom>rect.bottom-2)
			m_rectInvert.bottom=rect.bottom-2;
	}

	m_rectInvert.NormalizeRect(); // for nWidth < 0

	if(bRemoveHilite)
	{
		if(m_bOldIsHilited)
		{
			CRect rectOldInvert=m_rectOldInvert;
			rectOldInvert.IntersectRect(rectOldInvert,rect);
			ReverseHilite(pDC,rectOldInvert);
		}
		m_rectOldInvert.SetRectEmpty();
		m_rectInvert.SetRectEmpty();
		m_bOldIsHilited=FALSE;
	}
	else
	{
		if(m_bOldIsHilited)
		{
			CRect rectIntersect;
			rectIntersect.IntersectRect(m_rectOldInvert,m_rectInvert);

			CRect rectOldInvert;
			rectOldInvert.SubtractRect(m_rectOldInvert,rectIntersect);
			rectOldInvert.IntersectRect(rectOldInvert,rect);
			ReverseHilite(pDC,rectOldInvert);
			
			CRect rectInvert;
			rectInvert.SubtractRect(m_rectInvert,rectIntersect);
			ReverseHilite(pDC,rectInvert);
		}
		else
			ReverseHilite(pDC,m_rectInvert);
		m_bOldIsHilited=TRUE;
		m_rectOldInvert=m_rectInvert;
	}
}


/////////////////////////////////////////////////////////////////////////////
// COXRulerBar message handlers

void COXRulerBar::Scroll(UINT nPos, BOOL bRedraw/*=TRUE*/)
{
	m_nPos=m_nZoom*nPos/100;
	if(bRedraw)
		Invalidate();
}

void COXRulerBar::Zoom(UINT nZoom, BOOL bRedraw/*=TRUE*/)
{
	m_nZoom=nZoom;
	if(bRedraw)
		Invalidate();
}

void COXRulerBar::SetDpi(double dDpi, BOOL bRedraw/*=TRUE*/)
{
	m_dDisplayDpi=dDpi;
	m_bUseNonDefaultDpi=TRUE;
	if(bRedraw)
		Invalidate();
}

void COXRulerBar::UseDefaultDpi(BOOL bUseDefaultDpi, BOOL bRedraw/*=TRUE*/)
{
	m_bUseNonDefaultDpi=!bUseDefaultDpi;
	if(bRedraw)
		Invalidate();
}

void COXRulerBar::SetCalibrate(UINT nCalibrate, BOOL bRedraw/*=TRUE*/)
{
	m_nCalibrate=nCalibrate;
	if(bRedraw)
		Invalidate();
}

void COXRulerBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectClient;
	GetClientRect(rectClient);
	CRect rectClip;
	dc.GetClipBox(&rectClip); // invalidated region

	DrawRuler(&dc,rectClient,rectClip);
}


////////////////////////////////////////////////////////////////////////////////////


COXRulerOrganizer::COXRulerOrganizer()
	:
	m_bShowHorzRulerBar(FALSE),
	m_bShowVertRulerBar(FALSE),
	m_rectHorzRulerBar(0,0,0,0),
	m_rectVertRulerBar(0,0,0,0),
	m_rectBlank(0,0,0,0),
	m_nHorzRulerBarHeight(OXRB_HORZHEIGHT),
	m_nVertRulerBarWidth(OXRB_VERTWIDTH),
	m_nTimerCheckScrollPos(NULL)
{
}


COXRulerOrganizer::~COXRulerOrganizer()
{
}

BOOL COXRulerOrganizer::Attach(CWnd* pWnd, BOOL bHorzRuler/*=TRUE*/, 
							   BOOL bVertRuler/*=TRUE*/)
{
	ASSERT(pWnd!=NULL);

	if(!::IsWindow(pWnd->GetSafeHwnd()))
	{
		TRACE(_T("COXRulerOrganizer::Attach: failed, invalid window handle has been specified\n"));
		return FALSE;
	}

	if(IsAttached())
	{
		TRACE(_T("COXRulerOrganizer::Attach: failed, object already has attached window. Call Detach() before!\n"));
		return FALSE;
	}

	HookWindow(pWnd);

	// create ruler bars
	ASSERT(!::IsWindow(m_horzRulerBar.GetSafeHwnd()) && 
		!::IsWindow(m_vertRulerBar.GetSafeHwnd()));
	CRect rect(0,0,0,0);
	if(!m_horzRulerBar.Create(pWnd,TRUE,rect,WS_CHILD) || 
		!m_vertRulerBar.Create(pWnd,FALSE,rect,WS_CHILD))
	{
		TRACE(_T("COXRulerOrganizer::Attach: failed to create the ruler bars\n"));
		Detach();
		return FALSE;
	}

	// create timer for checking scroll position
	m_nTimerCheckScrollPos=pWnd->SetTimer(IDT_OXRBO_CHECK_SCROLLPOS,
		OXRBO_CHECK_SCROLLPOS_DELAY,NULL);
	if(m_nTimerCheckScrollPos==NULL)
	{
		TRACE(_T("COXRulerOrganizer::Attach: failed to create timer\n"));
		Detach();
		return FALSE;
	}

	m_bShowHorzRulerBar=bHorzRuler;
	m_bShowVertRulerBar=bVertRuler;

	CalcLayout(TRUE);

	return TRUE;
}


void COXRulerOrganizer::Detach()
{
	// destroy ruler bars
	if(::IsWindow(m_horzRulerBar.GetSafeHwnd()))
		m_horzRulerBar.DestroyWindow();
	if(::IsWindow(m_vertRulerBar.GetSafeHwnd()))
		m_vertRulerBar.DestroyWindow();

	if(::IsWindow(m_hWndHooked))
	{
		if(m_nTimerCheckScrollPos!=NULL)
		{
			GetHookedWnd()->KillTimer(m_nTimerCheckScrollPos);
		}

		RedrawAttached(TRUE);
	}

	UnhookWindow();

	m_bShowHorzRulerBar=FALSE;
	m_bShowVertRulerBar=FALSE;

	m_nTimerCheckScrollPos=NULL;
}


void COXRulerOrganizer::SetHorzRulerBarHeight(int nHorzRulerBarHeight)
{
	m_nHorzRulerBarHeight=nHorzRulerBarHeight;
	CalcLayout(TRUE);
}


void COXRulerOrganizer::SetVertRulerBarWidth(int nVertRulerBarWidth)
{
	m_nVertRulerBarWidth=nVertRulerBarWidth;
	CalcLayout(TRUE);
}


LRESULT COXRulerOrganizer::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#ifdef _WINDLL 
#ifndef _AFXEXT
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
#endif

	LRESULT result=0;

	switch(uMsg)
	{
	case WM_NCCALCSIZE:
		{
			result=COXHookWnd::WindowProc(uMsg,wParam,lParam);

			LPNCCALCSIZE_PARAMS lpncsp=(LPNCCALCSIZE_PARAMS)lParam;
			// add an offset
			if(GetShowVertRulerBar())
			{
				if(lpncsp->rgrc[0].right-lpncsp->rgrc[0].left>
					GetVertRulerBarWidth()+OXRBO_BORDER)
				{
					lpncsp->rgrc[0].left+=GetVertRulerBarWidth()+OXRBO_BORDER;
				}
				else
				{
					lpncsp->rgrc[0].left=lpncsp->rgrc[0].right;
				}
			}

			if(GetShowHorzRulerBar())
			{
				if(lpncsp->rgrc[0].bottom-lpncsp->rgrc[0].top>
					GetHorzRulerBarHeight()+OXRBO_BORDER)
				{
					lpncsp->rgrc[0].top+=GetHorzRulerBarHeight()+OXRBO_BORDER;
				}
				else
				{
					lpncsp->rgrc[0].top=lpncsp->rgrc[0].bottom;
				}
			}
			break;
		}

	case WM_NCPAINT:
		{
			result=COXHookWnd::WindowProc(uMsg,wParam,lParam);

			CWindowDC dc(GetHookedWnd());

			if(!m_rectBlank.IsRectEmpty())
				dc.FillSolidRect(m_rectBlank,::GetSysColor(COLOR_BTNFACE));

			if(GetShowHorzRulerBar())
			{
				m_horzRulerBar.DrawRuler(&dc,m_rectHorzRulerBar,m_rectHorzRulerBar);

				dc.MoveTo(m_rectHorzRulerBar.left+1,m_rectHorzRulerBar.bottom+1);
				dc.LineTo(m_rectHorzRulerBar.right+1,m_rectHorzRulerBar.bottom+1);
				CPen pen(PS_SOLID,1,::GetSysColor(COLOR_3DSHADOW));
				CPen* pOldPen=dc.SelectObject(&pen);
				dc.MoveTo(m_rectHorzRulerBar.left,m_rectHorzRulerBar.bottom);
				dc.LineTo(m_rectHorzRulerBar.right+1,m_rectHorzRulerBar.bottom);
				if(pOldPen!=NULL)
					dc.SelectObject(pOldPen);
			}
			if(GetShowVertRulerBar())
			{
				m_vertRulerBar.DrawRuler(&dc,m_rectVertRulerBar,m_rectVertRulerBar);

				dc.MoveTo(m_rectVertRulerBar.right+1,m_rectVertRulerBar.top+1);
				dc.LineTo(m_rectVertRulerBar.right+1,m_rectVertRulerBar.bottom+1);
				CPen pen(PS_SOLID,1,::GetSysColor(COLOR_3DSHADOW));
				CPen* pOldPen=dc.SelectObject(&pen);
				dc.MoveTo(m_rectVertRulerBar.right,m_rectVertRulerBar.top);
				dc.LineTo(m_rectVertRulerBar.right,m_rectVertRulerBar.bottom+1);
				if(pOldPen!=NULL)
					dc.SelectObject(pOldPen);
			}

			break;
		}

	case WM_SIZE:
		{
			result=COXHookWnd::WindowProc(uMsg,wParam,lParam);
			if(wParam==SIZE_MAXIMIZED || wParam==SIZE_RESTORED)
			{
				CalcLayout();
				CheckScrollPos();
				RedrawAttached();
			}
			break;
		}

	case WM_HSCROLL:
		{
			result=COXHookWnd::WindowProc(uMsg,wParam,lParam);
			CheckScrollPos();
			break;
		}

	case WM_VSCROLL:
		{
			result=COXHookWnd::WindowProc(uMsg,wParam,lParam);
			CheckScrollPos();
			break;
		}

	case WM_MOUSEMOVE:
		{
			result=COXHookWnd::WindowProc(uMsg,wParam,lParam);

			if(GetShowHorzRulerBar())
			{
				HiliteRuler(LOWORD(lParam),TRUE,1);
			}

			if(GetShowVertRulerBar())
			{
				HiliteRuler(HIWORD(lParam),FALSE,1);
			}

			break;
		}

	case WM_TIMER:
		{
			if(wParam==(UINT)m_nTimerCheckScrollPos)
			{
				CheckScrollPos();
				return 0;
			}
			result=COXHookWnd::WindowProc(uMsg,wParam,lParam);
			break;
		}

	default:
		{
			result=COXHookWnd::WindowProc(uMsg,wParam,lParam);
			break;
		}
	}

	return result;
}


void COXRulerOrganizer::CalcLayout(BOOL bRepositionBars/*=FALSE*/)
{
	m_rectHorzRulerBar.SetRectEmpty();
	m_rectVertRulerBar.SetRectEmpty();
	m_rectBlank.SetRectEmpty();

	if(!IsAttached())
		return;

	ASSERT(::IsWindow(m_hWndHooked));

	CRect rectWindow;
	::GetWindowRect(m_hWndHooked,rectWindow);
	GetHookedWnd()->ScreenToClient(rectWindow);
	CRect rect;
	::GetClientRect(m_hWndHooked,rect);
	rect-=rectWindow.TopLeft();

	DWORD dwStyle=GetHookedWnd()->GetStyle();
	if((dwStyle&WS_VSCROLL)==WS_VSCROLL)
	{
		rect.right+=::GetSystemMetrics(SM_CXVSCROLL);
	}
	if((dwStyle&WS_HSCROLL)==WS_HSCROLL)
	{
		rect.bottom+=::GetSystemMetrics(SM_CYHSCROLL);
	}
	if(GetShowVertRulerBar())
	{
		rect.left-=GetVertRulerBarWidth()+OXRBO_BORDER;
	}
	if(GetShowHorzRulerBar())
	{
		rect.top-=GetHorzRulerBarHeight()+OXRBO_BORDER;
	}


	if(GetShowHorzRulerBar() && GetShowVertRulerBar())
	{
		m_rectBlank=rect;
		m_rectBlank.right=m_rectBlank.left+GetVertRulerBarWidth();
		m_rectBlank.bottom=m_rectBlank.top+GetHorzRulerBarHeight();
	}

	if(GetShowHorzRulerBar())
	{
		m_rectHorzRulerBar.left=m_rectBlank.right;
		m_rectHorzRulerBar.right=rect.right;
		m_rectHorzRulerBar.top=rect.top;
		m_rectHorzRulerBar.bottom=m_rectHorzRulerBar.top+GetHorzRulerBarHeight();
	}

	if(GetShowVertRulerBar())
	{
		m_rectVertRulerBar.top=m_rectBlank.bottom;
		m_rectVertRulerBar.bottom=rect.bottom;
		m_rectVertRulerBar.left=rect.left;
		m_rectVertRulerBar.right=m_rectVertRulerBar.left+GetVertRulerBarWidth();
	}

	if(bRepositionBars)
		RedrawAttached(TRUE);
}


void COXRulerOrganizer::CheckScrollPos()
{
	BOOL bRedraw=FALSE;
	if(GetShowHorzRulerBar())
	{
		SCROLLINFO scrollInfo={ sizeof(SCROLLINFO) };
		if(GetHookedWnd()->GetScrollInfo(SB_HORZ,&scrollInfo))
		{
			int nNewScrollPos=scrollInfo.nPos;

			if(nNewScrollPos!=0 && scrollInfo.nPage!=0)
			{
				CRect rectClient;
				::GetClientRect(m_hWndHooked,rectClient);

				nNewScrollPos*=(rectClient.Width()/scrollInfo.nPage);
			}

			int nOldScrollPos=(int)m_horzRulerBar.GetCurrentPos();
			nNewScrollPos=nNewScrollPos*100/m_horzRulerBar.GetZoomLevel();
			m_horzRulerBar.Scroll(nNewScrollPos,FALSE);
			if(nOldScrollPos!=(int)m_horzRulerBar.GetCurrentPos())
			{
				bRedraw=TRUE;
			}
		}
	}

	if(GetShowVertRulerBar())
	{
		SCROLLINFO scrollInfo={ sizeof(SCROLLINFO) };
		if(GetHookedWnd()->GetScrollInfo(SB_VERT,&scrollInfo))
		{
			int nNewScrollPos=scrollInfo.nPos;

			if(nNewScrollPos!=0 && scrollInfo.nPage!=0)
			{
				CRect rectClient;
				::GetClientRect(m_hWndHooked,rectClient);

				nNewScrollPos*=(rectClient.Height()/scrollInfo.nPage);
			}

			int nOldScrollPos=(int)m_vertRulerBar.GetCurrentPos();
			nNewScrollPos=nNewScrollPos*100/m_vertRulerBar.GetZoomLevel();
			m_vertRulerBar.Scroll(nNewScrollPos,FALSE);
			if(nOldScrollPos!=(int)m_vertRulerBar.GetCurrentPos())
			{
				bRedraw=TRUE;
			}
		}
	}

	if(bRedraw)
	{
		RedrawAttached();
		TRACE(_T("RedrawAttached\n"));
	}
}	

