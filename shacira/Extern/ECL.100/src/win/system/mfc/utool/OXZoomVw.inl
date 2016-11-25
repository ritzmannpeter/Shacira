// ==========================================================================
//                     Template Implementation : COXZoomView
// ==========================================================================

// Source file : OXZoomView.inl 

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved                      
			  

inline BOOL COXZoomView::GetAlignToBottom() const
{
	return( m_bAlignToBottom );
}

inline void COXZoomView::SetAlignToBottom( BOOL bAlignToBottom )
{
	m_bAlignToBottom = bAlignToBottom;
}

inline BOOL COXZoomView::IsCentered() const
{
	return( m_bCenter );
}

inline void COXZoomView::Center( BOOL bCenter )
{
	m_bCenter = bCenter;
}

inline CSize COXZoomView::GetTotalSize() const
{
	return m_totalLog;
}

inline COXZoomView::ZoomAlignment COXZoomView::GetZoomAlign()
{
	return( m_align );
}

inline int COXZoomView::GetZoomLevel() const
{
	return( m_nZoomLevel );
}


