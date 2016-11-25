// ==========================================================================
// 					Class Specification : COXLayoutManager
// ==========================================================================
// Header file :		OXLayoutManager.h
//
// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
/////////////////////////////////////////////////////////////////////////////

inline int COXLayoutManager::AddChild(CWnd* pChildWnd,
									  BOOL bSetDefaultConstraints /* = TRUE */)
{
	ASSERT(pChildWnd && pChildWnd->GetDlgCtrlID());
	return AddChild(pChildWnd->GetDlgCtrlID(), bSetDefaultConstraints);
}

inline BOOL COXLayoutManager::RemoveChild(CWnd* pChildWnd)
{
	ASSERT(pChildWnd && pChildWnd->GetDlgCtrlID());
	return RemoveChild(pChildWnd->GetDlgCtrlID());
}

inline BOOL COXLayoutManager::SetConstraint(CWnd* pChildWnd, int nSide, int nType,
											int nOffset /* = 0 */, CWnd* pBaseWnd /* = NULL */)
{
	ASSERT(pChildWnd && pChildWnd->GetDlgCtrlID());
	ASSERT(pBaseWnd == NULL || pBaseWnd->GetDlgCtrlID() != 0);
	return SetConstraint(pChildWnd->GetDlgCtrlID(), nSide, nType,
		nOffset, pBaseWnd == NULL ? 0 : pBaseWnd->GetDlgCtrlID());
}

inline BOOL COXLayoutManager::SetMinMax(CWnd* pChildWnd, CSize sizeMin, 
										CSize sizeMax /* = CSize(0,0) */)
{
	ASSERT(pChildWnd && pChildWnd->GetDlgCtrlID());
	return SetMinMax(pChildWnd->GetDlgCtrlID(), sizeMin, sizeMax);
}

inline BOOL COXLayoutManager::RemoveConstraint(CWnd* pChildWnd, int nSide)
{
	ASSERT(pChildWnd && pChildWnd->GetDlgCtrlID());
	return RemoveConstraint(pChildWnd->GetDlgCtrlID(), nSide);
}

inline int COXLayoutManager::GetFractionBase() const
{
	return m_nBase;
}

inline void COXLayoutManager::SetFractionBase(int nBase)
{
	if (nBase) m_nBase = nBase;
}

inline void COXLayoutManager::ResetContainerMinMax()
{
	m_cxMin = m_cyMin = -1;
	m_cxMax = m_cyMax = 32767;
}

inline BOOL COXLayoutManager::TieChild(CWnd* pChildWnd, int nSide, int nType, 
									   CWnd* pBaseWnd/*=NULL*/)
{
	ASSERT(pChildWnd && pChildWnd->GetDlgCtrlID());
	ASSERT(pBaseWnd==NULL || pBaseWnd->GetDlgCtrlID()!=0);
	return TieChild(pChildWnd->GetDlgCtrlID(),nSide, nType,
		pBaseWnd==NULL ? 0 : pBaseWnd->GetDlgCtrlID());
}

inline BOOL COXLayoutManager::IsAttached() const
{
	return (m_pContainerWnd!=NULL);
}

// end of OXLayoutManager.inl