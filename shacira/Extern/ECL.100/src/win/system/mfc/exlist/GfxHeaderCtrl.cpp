// GfxHeaderCtrl.cpp : implementation file
//

#include "../stdafx.h"
//-TE-#include "GfxList.h"


#include "GfxHeaderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGfxHeaderCtrl

CGfxHeaderCtrl::CGfxHeaderCtrl()
{
	dwSortUp = 0;
	m_nSortCol = -1;
	pImageList = NULL;
	dwDontShowSortArrow = 0;
	dwNoResizeColumn = 0;
	bIsDragAllowed = true;

// Column dragging support
	m_pWidth = NULL;	
	m_bDragging = FALSE;	
	m_bCheckForDrag = FALSE;
	m_fpDragCol = NULL;	
//	m_pOwnerWnd = NULL;
	bEnableDrag = true;
}

CGfxHeaderCtrl::~CGfxHeaderCtrl()
{
}


BEGIN_MESSAGE_MAP(CGfxHeaderCtrl, CHeaderCtrl)
	//{{AFX_MSG_MAP(CGfxHeaderCtrl)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_NCHITTEST()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGfxHeaderCtrl message handlers

int CGfxHeaderCtrl::SetSortImage( int nCol, BOOL bAsc )
{
	int nPrevCol = m_nSortCol;

	m_nSortCol = nCol;
	m_bSortAsc = bAsc;

	// Change the item to ownder drawn
	HD_ITEM hditem;

	hditem.mask = HDI_FORMAT;
	GetItem(nCol, &hditem);
	hditem.fmt |= HDF_OWNERDRAW;
	SetItem(nCol, &hditem);

	// Invalidate header control so that it gets redrawn
	Invalidate();
	SetSortOrder(nCol, bAsc == TRUE);
	return nPrevCol;
}

void CGfxHeaderCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	CRect rcLabel(lpDrawItemStruct->rcItem);

	int nSavedDC = dc.SaveDC();

	CRgn rgn;
	rgn.CreateRectRgnIndirect(&rcLabel);
	dc.SelectObject(&rgn);
	rgn.DeleteObject();

	// Draw the background
//	dc.FillRect(rcLabel, &CBrush(::GetSysColor(COLOR_3DFACE)));
	dc.FillSolidRect(rcLabel, GetSysColor(COLOR_3DFACE));
	// Labels are offset by a certain amount  
	// This offset is related to the width of a space character
	int offset = dc.GetTextExtent(_T(" "), 1).cx*2;
	// Get the column text and format
	static TCHAR buf[256];
	HD_ITEM hditem;
	hditem.mask = HDI_TEXT | HDI_FORMAT | HDI_LPARAM;
	hditem.pszText = buf;
	hditem.cchTextMax = 255;

	GetItem(lpDrawItemStruct->itemID, &hditem);

	int iSubItem = hditem.lParam;

	// Determine format for drawing column label
	UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER | DT_END_ELLIPSIS ;

	if( hditem.fmt & HDF_CENTER) uFormat |= DT_CENTER;
	else if( hditem.fmt & HDF_RIGHT) uFormat |= DT_RIGHT;
	else uFormat |= DT_LEFT;

	// Adjust the rect if the mouse button is pressed on it
	if (lpDrawItemStruct->itemState == ODS_SELECTED)
	{
		rcLabel.left++;
		rcLabel.top += 2;
		rcLabel.right++;
	}

	// Draw column label
	CString cs(buf);

	if (pImageList && cs.Right(1) == "_")
	{
		int iIdx = atoi(cs);
		IMAGEINFO ii;
		if (pImageList->GetImageInfo(iIdx, &ii))
		{
			CRect rcIma(ii.rcImage);
			if (rcLabel.Width() >= rcIma.Width())
			{
				int x = rcLabel.left + (rcLabel.Width() - rcIma.Width()) / 2;
				int y = rcLabel.top + (rcLabel.Height() - rcIma.Height()) / 2;
				pImageList->Draw(&dc, iIdx, CPoint(x,y), ILD_TRANSPARENT);//ILD_NORMAL);rcLabel.TopLeft()
			}
		}
	}
	else
	{
		// Adjust the rect further if Sort arrow is to be displayed
		if (lpDrawItemStruct->itemID == (UINT)m_nSortCol) rcLabel.right -= 3 * offset;

		rcLabel.left += offset;
		rcLabel.right -= offset;

		if (rcLabel.left < rcLabel.right) 
			dc.DrawText(buf,-1,rcLabel, uFormat);
	}

	// Draw the Sort arrow
	if (lpDrawItemStruct->itemID == (UINT)m_nSortCol && !(dwDontShowSortArrow & 1 << iSubItem))//m_nSortCol))
	{
		CRect rcIcon(lpDrawItemStruct->rcItem);

		// Set up pens to use for drawing the triangle
		CPen penLight(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
		CPen penShadow(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
		CPen *pOldPen = dc.SelectObject(&penLight);

		if (m_bSortAsc)
		{
			// Draw triangle pointing upwards
			dc.MoveTo(rcIcon.right - 2*offset, offset-1);
			dc.LineTo(rcIcon.right - 3*offset/2, rcIcon.bottom - offset);
			dc.LineTo(rcIcon.right - 5*offset/2-2, rcIcon.bottom - offset);
			dc.MoveTo(rcIcon.right - 5*offset/2-1, rcIcon.bottom - offset-1);

			dc.SelectObject(&penShadow);
			dc.LineTo(rcIcon.right - 2*offset, offset-2);
		}
		else
		{
			// Draw triangle pointing downwords
			dc.MoveTo(rcIcon.right - 3*offset/2, offset-1);
			dc.LineTo(rcIcon.right - 2*offset-1, rcIcon.bottom - offset + 1);
			dc.MoveTo(rcIcon.right - 2*offset-1, rcIcon.bottom - offset);

			dc.SelectObject(&penShadow);
			dc.LineTo(rcIcon.right - 5*offset/2-1, offset -1);
			dc.LineTo(rcIcon.right - 3*offset/2, offset -1);
		}

		// Restore the pen
		dc.SelectObject(pOldPen);
	}

	if ((m_bDragging) && (int)lpDrawItemStruct->itemID == m_nDragCol)//|| m_bCheckForDrag
	{
		CBrush* pBrush = CBrush::FromHandle((HBRUSH) GetStockObject(WHITE_BRUSH));
		HBRUSH hOldBrush = NULL;
		if (pBrush != NULL) hOldBrush = (HBRUSH)SelectObject(dc.m_hDC, pBrush->m_hObject);
		CRect rcx(lpDrawItemStruct->rcItem);
		dc.PatBlt(rcx.left, rcx.top, rcx.Width(), rcx.Height(), PATINVERT);
		if (hOldBrush != NULL) SelectObject(dc.m_hDC, hOldBrush);
	}

	dc.RestoreDC(nSavedDC);
	dc.Detach();
}

bool CGfxHeaderCtrl::GetSortOrder(const int iCol)
{
	return dwSortUp & (1 << iCol) ? true : false;
}

void CGfxHeaderCtrl::SetSortOrder(const int iCol, const bool bAscending)
{
	if (bAscending) dwSortUp |= (1 << iCol);
	else dwSortUp &= ~ (1 << iCol);
}


BOOL CGfxHeaderCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{	
	if (bIsDragAllowed) return CHeaderCtrl::OnSetCursor(pWnd, nHitTest, message);
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	return TRUE;
}

void CGfxHeaderCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if (IsDragAllowed(point)) CHeaderCtrl::OnLButtonDblClk(nFlags, point);
}

UINT CGfxHeaderCtrl::OnNcHitTest(CPoint point) 
{
	CPoint clientPoint = point;	
	ScreenToClient(&clientPoint);
	bIsDragAllowed = IsDragAllowed(clientPoint);
	return CHeaderCtrl::OnNcHitTest(point);
}

bool CGfxHeaderCtrl::IsDragAllowed(CPoint point)
{
	if (dwNoResizeColumn == 0) return true;
	HD_ITEM hi;	
	hi.mask = HDI_WIDTH|HDI_LPARAM;

	int dividerLocations = 0;
	int dragWidth = GetSystemMetrics(SM_CXCURSOR);

	bool allowDrag = true;

	int i, max = GetItemCount();
	for (i = 0; i < max; ++i) 
	{		
		GetItem(i, &hi);
		dividerLocations += hi.cxy;
		if (dwNoResizeColumn & (1 << hi.lParam))//i)
			if (point.x > dividerLocations - dragWidth/2 && point.x < dividerLocations + dragWidth/2)
				allowDrag = false;
	}
	return allowDrag;
}

void CGfxHeaderCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (bEnableDrag)
	{
		if( (MK_LBUTTON & nFlags) == 0)
		{
			// The left mouse button is not pressed - so reset flags
			m_bCheckForDrag = FALSE;
			m_bDragging = FALSE;
		}
		else if (m_bDragging)
		{
			// Get column number that falls under the mouse
			int i=0, cx = 0;
			if( point.x > 0 )
			{
				for( i = 0; i < GetItemCount(); i++ )
				{
					if( point.x >= cx && point.x < cx + m_pWidth[i] )
						break;
					cx += m_pWidth[i];
				}
			}

			if (i != m_nDropPos)
			{
				m_nDropPos = i;

				CRect rect;
				//GetWindowRect(&rect);
				GetClientRect(&rect);

				// Invalidate area occupied by previous marker
				InvalidateRect(&marker_rect);

				// Draw a new marker
				CClientDC dc(this);
				POINT pts[3];

				CBrush rbr(RGB(255,0,0)), * obr = dc.SelectObject(&rbr);
				CPen rpn(PS_SOLID,1,RGB(255,0,0)), * opn = dc.SelectObject(&rpn);

				pts[0].x = cx; pts[1].x = cx -3; pts[2].x = cx +3;
				pts[0].y = rect.Height() - 8; pts[1].y = pts[2].y = rect.Height()-1;

				dc.Polygon(pts, 3);

				// save marker information
				marker_rect.left = cx - 4;
				marker_rect.top = rect.bottom - 8;
				marker_rect.right = cx + 4;
				marker_rect.bottom = rect.bottom;//Height();

				dc.SelectObject(obr);
				dc.SelectObject(opn);
			}

			{
				CClientDC dc(GetParent());
				CPoint spt(point);
				ClientToScreen(&spt);
				GetParent()->ScreenToClient(&spt);

				CRect rcNewDragColumn(spt.x - rcDragColumn.Width() / 2, spt.y - rcDragColumn.Height() / 2, spt.x + rcDragColumn.Width() / 2, spt.y + rcDragColumn.Height() / 2);
				dc.DrawDragRect(&rcNewDragColumn, CSize(2,2), rcLastDragColumn.IsRectEmpty() ? NULL : &rcLastDragColumn, CSize(2,2));
				rcLastDragColumn = rcNewDragColumn;
			}

			return;
		}
		else if(m_bCheckForDrag)
		{
			// The mouse button was pressed over a column header
			// and now the mouse has moved - so start drag
			m_bCheckForDrag = FALSE;

			m_bDragging = TRUE;
			m_nDropPos = m_nDragCol;

			SetCapture();

			// Store information for later use
			int iCount = GetItemCount();
			HD_ITEM hd_item;
			m_pWidth = new int[iCount];
			for (int i = 0; i < iCount; i++)
			{
				hd_item.mask = HDI_WIDTH|HDI_FORMAT;
				GetItem(i, &hd_item);
				m_pWidth[i] = hd_item.cxy;

				if (!(hd_item.fmt & HDF_OWNERDRAW))
				{
					hd_item.mask = HDI_FORMAT;
					hd_item.fmt |= HDF_OWNERDRAW;
					SetItem(i, &hd_item);
				}
			}
			rcLastDragColumn.SetRect(0,0,0,0);
			DrawDragColumn(m_nDragCol);
			Invalidate();
			return;
		}
	}
	
	CHeaderCtrl::OnMouseMove(nFlags, point);
}

void CGfxHeaderCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// Determine if mouse was pressed over a column header
	if (bEnableDrag)
	{
		HD_HITTESTINFO hd_hittestinfo;
		hd_hittestinfo.pt = point;
		SendMessage(HDM_HITTEST, 0, (LPARAM)(&hd_hittestinfo));
		if( hd_hittestinfo.flags == HHT_ONHEADER )
		{
			m_nDragCol = hd_hittestinfo.iItem;
			m_bCheckForDrag = TRUE;
			Invalidate();
		}
	}
	
	CHeaderCtrl::OnLButtonDown(nFlags, point);
}

void CGfxHeaderCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (bEnableDrag)
	{
		if (m_bDragging)
		{
			if (!(rcLastDragColumn.IsRectEmpty())) 
			{
				rcLastDragColumn.top --;
				GetParent()->InvalidateRect(rcLastDragColumn);
				GetParent()->UpdateWindow();
				rcLastDragColumn.SetRect(0,0,0,0);
			}
			m_bDragging = FALSE;
			delete[] m_pWidth;
			ReleaseCapture();
			if (m_nDragCol != m_nDropPos && m_nDragCol != m_nDropPos -1)
			{
				(GetParent()->*m_fpDragCol)(m_nDragCol, m_nDropPos);

				if (m_nSortCol == m_nDragCol) m_nSortCol = m_nDropPos;
				else if (m_nSortCol == m_nDropPos) m_nSortCol = m_nDragCol;
			}
			Invalidate();
		}
	}
	CHeaderCtrl::OnLButtonUp(nFlags, point);
}

void CGfxHeaderCtrl::SetCallback(void (CWnd::*fpDragCol)(int &, int &))
{	
	m_fpDragCol = fpDragCol;
}


void CGfxHeaderCtrl::DrawDragColumn(const int iCol)
{
	int cx = 0;
	cx = m_pWidth[iCol];

	CRect rc;
	GetClientRect(&rc);

	HD_ITEM hditem;
	hditem.mask = HDI_WIDTH;
	GetItem(iCol, &hditem);

	rcDragColumn.SetRect(0, 0, hditem.cxy, rc.Height());
}
