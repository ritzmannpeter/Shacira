// ==========================================================================
// 					Class Specification : COXLayoutManager
// ==========================================================================
// Header file :		OXLayoutManager.h
//
// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
//
//
// Properties:
//		NO		 Abstract class (does not have any objects)
//		YES		 Derived from CObject
//
//		NO		 Is a CWnd.                     
//		NO		 Two stage creation (constructor & Create())
//		NO		 Has a message map
//		NO		 Needs a resource (template)
//
//		NO		 Persistent objects (saveable on disk)      
//		NO		 Uses exceptions
//
// Description:
//		COXLayoutManager can be attached to a container window (dialog, form etc.).
//		From that moment on the layout manager will manage the layout of the child
//		windows of this container. So imagine you have a dialog with several
//		controls on it. When the dialog is resized the layout manager moves and 
//		resizes the controls of this dialog. The programmer can specify certain 
//		constraints that have to be fulfilled at all times. By using these 
//		constraints and the new size of the container window (dialog), the layout
//		manager is able to move and resize the controls appropriately.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __OXLAYOUTMANAGER_H__
#define __OXLAYOUTMANAGER_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#ifndef __AFXTEMPL_H__
#include <AfxTempl.h>
#define __AFXTEMPL_H__
#endif


#define OX_LMS_TOP		1	// 0001
#define OX_LMS_BOTTOM	2	// 0010
#define OX_LMS_LEFT		4	// 0100
#define OX_LMS_RIGHT	8	// 1000
#define OX_LMS_VERT		3	// 0011
#define OX_LMS_HORZ		12	// 1100
#define OX_LMS_MAJOR	5	// 0101
#define OX_LMS_MINOR	10	// 1010
#define OX_LMS_ANY		15	// 1111

#define OX_LMT_SAME			1
#define OX_LMT_OPPOSITE		2
#define OX_LMT_POSITION		3

#define OX_LMOFFSET_ANY		32767
#define OX_LMPOS_NULL		32767
#define OX_LMPOS_TRACING	32766

/////////////////////////////////////////////////////////////////////////////
// helper classes for COXLayoutManager

class COXLayoutManager;
class COXWndConstraint;
class OX_CLASS_DECL COXSideConstraint
{
	friend class COXLayoutManager;
	friend class COXWndConstraint;

protected:
	COXSideConstraint();
	void Empty();
	BOOL IsEmpty();

	UINT nBaseWnd;
	int	 nOffset1;
	int	 nOffset2;
	int	 nPos;
	int  nBaseWndIndex;
};

class OX_CLASS_DECL COXWndConstraint
{
	friend class COXLayoutManager;

protected:
	COXWndConstraint(UINT nChildID);
	void  Empty();
	CRect GetRect();
	void ResetPos();

	UINT  nID;
	BOOL  bHasMinMax;
	CSize sizeMin;
	CSize sizeMax;
	COXSideConstraint sc[4];
};

/////////////////////////////////////////////////////////////////////////////
class OX_CLASS_DECL COXLayoutManager : public CObject
{
	DECLARE_DYNCREATE(COXLayoutManager)

// Data members -------------------------------------------------------------
public:
protected:
	CWnd* m_pContainerWnd;
	int	  m_nBase;
	UINT  m_nMinMaxCount;
	int	  m_cx;
	int	  m_cy;
	int   m_cxMin;
	int	  m_cxMax;
	int   m_cyMin;
	int   m_cyMax;
	CArray<COXWndConstraint*, COXWndConstraint*> m_wcTable;

	HWND	m_hWnd;
	WNDPROC m_pfnSuper;
	static CMap<HWND, HWND, COXLayoutManager*, COXLayoutManager*> m_allLayoutManagers;

private:

// Member functions ---------------------------------------------------------
public:
	COXLayoutManager(CWnd* pContainerWnd = NULL);
	// --- In      : pContainerWnd, the container window to attach
	// --- Out     : 
	// --- Returns :
	// --- Effect  : Constructor of object

	virtual ~COXLayoutManager();
	// --- In      :
	// --- Out     : 
	// --- Returns :
	// --- Effect  : Destructor of object

	void Attach(CWnd* pContainerWnd);
	// --- In      : pContainerWnd, the container window to attach
	// --- Out     : 
	// --- Returns :
	// --- Effect  : attach a container window to start the layout management
	//				 of this window

	void Detach();
	// --- In      :
	// --- Out     : 
	// --- Returns :
	// --- Effect  : detach the container window (and remove all constraints)

	BOOL IsAttached() const;
	// --- In      :
	// --- Out     : 
	// --- Returns : TRUE if any container is attached to layout manager object
	// --- Effect  : retrieves the flag that specifies whether any container 
	//				 window is attached to the object or not

	int AddChild(UINT  nChildWnd, BOOL bSetDefaultConstraints = TRUE);
	int AddChild(CWnd* pChildWnd, BOOL bSetDefaultConstraints = TRUE);
	// --- In      : nChildWnd, the ID of the child window to add
	//				 pChildWnd, the child window to add
	//				 bSetDefaultConstraints, if TRUE, left and top will be constrainted
	//					to the container window using current distance
	// --- Out     : 
	// --- Returns : internal index of this child window; -1 if not successful
	// --- Effect  : add one child window of the container window to prepare for
	//				 setting constraints

	void AddAllChildren(BOOL bSetDefaultConstraints = TRUE);
	// --- In      : bSetDefaultConstraints, if TRUE, left and top will be constrainted
	//					to the container window using current distance
	// --- Out     : 
	// --- Returns :
	// --- Effect  : add all child windows of the container window to prepare for
	//				 setting constraints, and set default constraints if specified

	BOOL RemoveChild(UINT  nChildWnd);
	BOOL RemoveChild(CWnd* pChildWnd);
	// --- In      : nChildWnd, the ID of the child window to remove
	//				 pChildWnd, the child window to remove
	// --- Out     : 
	// --- Returns : TRUE if successful; FALSE if not found or it is necessary
	//					for another window to calculate positions
	// --- Effect  : remove one child window of the container window to free all its
	//				 constraints

	void RemoveAllChildren();
	// --- In      :
	// --- Out     : 
	// --- Returns :
	// --- Effect  : remove all child windows that are previously added and free
	//				 all constraints

	void SetFractionBase(int nBase);
	// --- In      : nBase, the new fraction base to use (cannot be 0)
	// --- Out     : 
	// --- Returns :
	// --- Effect  : set a new fraction base that is used in specifying an OX_LMT_POSITION
	//				 constraint (default is 100)

	int GetFractionBase() const;
	// --- In      :
	// --- Out     : 
	// --- Returns : the current fraction base
	// --- Effect  : get the current fraction base

	BOOL SetConstraint(UINT  nChildWnd, int nSide, int nType, int nOffset = 0, 
		UINT  nBaseWnd = 0);
	BOOL SetConstraint(CWnd* pChildWnd, int nSide, int nType, int nOffset = 0, 
		CWnd* pBaseWnd = NULL);
	// --- In      : nChildWnd, pChildWnd, the child window to apply constraint
	//				 nSide, can be any combination of the following values:
	//						OX_LMS_TOP		top side
	//						OX_LMS_BOTTOM	bottom side
	//						OX_LMS_LEFT		left side
	//						OX_LMS_RIGHT	right side
	//						OX_LMS_VERT		top and bottom sides
	//						OX_LMS_HORZ		left and right sides
	//						OX_LMS_MAJOR	top and left sides
	//						OX_LMS_MINOR	bottom and right sides
	//						OX_LMS_ANY		all four sides
	//				 nType, can be one of the following values (see .html file for details):
	//						OX_LMT_SAME		the constrainted side of the child window is based on
	//											the same side of the base window
	//						OX_LMT_OPPOSITE the constrainted side of the child window is based on
	//											the opposite side of the base window
	//						OX_LMT_POSITION	the constrainted side of the child window is based on
	//											a fraction to both sides of the base window
	//				 nOffset, when nType is OX_LMT_POSITION, the fraction that the 
	//					constrainted side will be positioned within the base window;
	//					otherwise, the offset that the constrainted side will be positioned
	//					from the specified side (determined by nType) of the base window.
	//				 nBaseWnd, pBaseWnd, the window upon which the constrainted side
	//					will be positioned
	// --- Out     : 
	// --- Returns :
	// --- Effect  : set constraints on one or more sides of a child window

	virtual void SetDefaultConstraint(UINT nChildWnd);
	// --- In  : nChildWnd : the child window to apply default constraint on 
	// --- Out : 
	// --- Returns :
	// --- Effect : set default constraints on a child window; called by AddChild()
	//				left and top will be constrainted to the container window using 
	//					current distance
	//				right and bottom will not be constrained

	BOOL SetMinMax(UINT  nChildWnd, CSize sizeMin, CSize sizeMax = CSize(0,0));
	BOOL SetMinMax(CWnd* pChildWnd, CSize sizeMin, CSize sizeMax = CSize(0,0));
	// --- In      : nChildWnd, pChildWnd, the child window to apply min/max limits
	//				 sizeMin, minimum size of the child window; CSize(0,0) means "don't care"
	//				 sizeMax, maximum size of the child window; CSize(0,0) means "don't care"
	// --- Out     : 
	// --- Returns :
	// --- Effect  : set the minimum size and maximum size of a child window

	BOOL RemoveConstraint(UINT  nChildWnd, int nSide);
	BOOL RemoveConstraint(CWnd* pChildWnd, int nSide);
	// --- In      : nChildWnd, pChildWnd, the child window to remove constraints on
	//				 nSide, can be any combination of the following values:
	//						OX_LMS_TOP		top side
	//						OX_LMS_BOTTOM	bottom side
	//						OX_LMS_LEFT		left side
	//						OX_LMS_RIGHT	right side
	//						OX_LMS_VERT		top and bottom sides
	//						OX_LMS_HORZ		left and right sides
	//						OX_LMS_MAJOR	top and left sides
	//						OX_LMS_MINOR	bottom and right sides
	//						OX_LMS_ANY		all four sides
	// --- Out     : 
	// --- Returns :
	// --- Effect  : remove constraints from one or more sides of a child window

	BOOL GetConstraint(UINT nChildWnd, int nSide, int& nType, int& nOffset, UINT& nBaseWnd);
	// --- In      : nChildWnd, the child window to check constraints on
	//				 nSide, can be one of the following values:
	//						OX_LMS_TOP		top side
	//						OX_LMS_BOTTOM	bottom side
	//						OX_LMS_LEFT		left side
	//						OX_LMS_RIGHT	right side
	// --- Out     : nType, the constraint type
	//				 nOffset, offset position or fraction
	//				 nBaseWnd, base window of the constraint
	// --- Returns : TRUE if successful; false otherwise
	// --- Effect  : retrieve constraints on a side of a child window

	BOOL GetMinMax(UINT nChildWnd, CSize& sizeMin, CSize& sizeMax);
	// --- In      : nChildWnd, the child window to check min/max limits
	// --- Out     : sizeMin, minimum size of the child window
	//				 sizeMax, maximum size of the child window
	// --- Returns : TRUE if successful; false otherwise
	// --- Effect  : retrieve the minimum size and maximum size of a child window

	BOOL TieChild(UINT  nChildWnd, int nSide, int nType, UINT nBaseWnd=0);
	BOOL TieChild(CWnd* pChildWnd, int nSide, int nType, CWnd* pBaseWnd=NULL);
	// --- In      : nChildWnd, pChildWnd, the child window to apply constraint
	//				 nSide, can be any combination of the following values:
	//						OX_LMS_TOP		top side
	//						OX_LMS_BOTTOM	bottom side
	//						OX_LMS_LEFT		left side
	//						OX_LMS_RIGHT	right side
	//						OX_LMS_VERT		top and bottom sides
	//						OX_LMS_HORZ		left and right sides
	//						OX_LMS_MAJOR	top and left sides
	//						OX_LMS_MINOR	bottom and right sides
	//						OX_LMS_ANY		all four sides
	//				 nType, can be one of the following values :
	//						OX_LMT_SAME		child window will be tied to the
	//										same sides of base window
	//						OX_LMT_OPPOSITE child window will be tied to the
	//										opposite sides of base window
	//				 nBaseWnd, pBaseWnd, the window to which the specified 
	//						child window will be tied
	// --- Out     : 
	// --- Returns :
	// --- Effect  :	ties specified side(s) of child control to the base window 

	virtual BOOL RedrawLayout();
	// --- In      :
	// --- Out     : 
	// --- Returns : TRUE if all constraints and min/max limits can be fulfilled,
	//				 FALSE otherwise
	// --- Effect  : read container window's current positions and apply constraints
	//				 on all child windows

	virtual BOOL OnSize(int cx, int cy);
	// --- In      : cx, new width of the container window
	//				 cy, new height of the container window
	// --- Out     : 
	// --- Returns : TRUE if all constraints and min/max limits can be fulfilled,
	//				 FALSE otherwise
	// --- Effect  : use new size of the container window to apply constraints
	//				 on all child windows

protected:
	int CalcLayout();
	void ResetContainerMinMax();
	int	GetChildIndex(UINT nChildWnd) const;
	BOOL CalcBaseWndIndex(COXSideConstraint* pSC);
	int CalcSideConstraint(COXWndConstraint* pWC, int nSideIndex);

	BOOL SubclassContainer(CWnd* pContainerWnd);
	void UnsubclassContainer();
	static LRESULT CALLBACK GlobalLayoutManagerProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT LayoutManagerProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
};

/////////////////////////////////////////////////////////////////////////////

#include "OXLayoutManager.inl"

#endif	// __OXLAYOUTMANAGER_H__

// end of OXLayoutManager.h