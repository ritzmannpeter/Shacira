// ===================================================================================
// 					Class Specification : 
//				COXToolCmdUI & COXToolBarCtrl & COXSizeToolBar
// ===================================================================================

// Header file : OXSizeToolBar.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
// Some portions Copyright (C)1994-5	Micro Focus Inc, 2465 East Bayshore Rd, Palo Alto, CA 94303.
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CCmdUI / CToolBarCtrl / COXSizeControlBar

//	NO / YES / YES	Is a Cwnd.                     
//	NO / YES /YES	Two stage creation (constructor & Create())
//	NO / YES / YES	Has a message map
//	NO / YES / YES	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//
// COXToolCmdUI   - CCmdUI derived class.
//
// COXToolBarCtrl - CToolBarCtrl derived object with addition left mouse button handling, etc.
//
// COXSizeToolBar - a sizeable toolbar. A sizeable control bar containing a CToolBarCtrl object.
//					which responds to tooltips/command enabling through the normal MFC architecture

//					COXSizeToolBar implements a sizeable toolbar that is largely compatible with
//					CToolBar. It responds to the standard MFC ON_UPDATE_CMD_UI handling and
//					routing, tooltips and prompting, and provides the benefits of the common
//					control, such as configuration.
//					This class is actually implemented as a Windows’95 CToolBarCtrl placed on
//					a COXSizeControlBar. Due to restrictions in the underlying common control it
//					is not (and don’t think it ever can be) 100% compatible with the CToolBar
//					class. However, enough compatibility is provided for AppWizard generated
//					apps to work with minimal change (i.e. altering CMainFrame::m_wndToolBar
//					to be a COXSizeToolBar). 
//					Some additional functionality has been added to utiltise the Windows’95
//					common control configuration. To use this class, you must include the
//					header file "afxcmn.h".
// Remark:
//

// Prerequisites (necessary conditions):
//		***

/////////////////////////////////////////////////////////////////////////////

#ifndef __SIZETOOLBAR_H__
#define __SIZETOOLBAR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include "OXSizeCtrlBar.h"


class OX_CLASS_DECL COXToolCmdUI : public CCmdUI    
{
// Data members -------------------------------------------------------------
public:

protected:

private :

// Member functions ---------------------------------------------------------
public: // re-implementations only

	virtual void Enable(BOOL bOn);
	// --- In  : See CCmdUI::Enable
	// --- Out : See CCmdUI::Enable
	// --- Returns : See CCmdUI::Enable
	// --- Effect : See CCmdUI::Enable

	virtual void SetCheck(int nCheck);
	// --- In  : See CCmdUI::SetCheck
	// --- Out : See CCmdUI::SetCheck
	// --- Returns : See CCmdUI::SetCheck
	// --- Effect : See CCmdUI::SetCheck

	virtual void SetText(LPCTSTR lpszText);
	// --- In  : See CCmdUI::SetText
	// --- Out : See CCmdUI::SetText
	// --- Returns : See CCmdUI::SetText
	// --- Effect : See CCmdUI::SetText

protected:

private :

};

class OX_CLASS_DECL COXToolBarCtrl : public CToolBarCtrl
{
// Data members -------------------------------------------------------------
public:

protected:

private :

// Member functions ---------------------------------------------------------
public:
	COXToolBarCtrl();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Constructor of object
	//				It will initialize the internal state

	void GetBoundingSize(CSize& size);
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : 
	
	int HitTestButtons(CPoint point);
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : 
	
	virtual ~COXToolBarCtrl();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXToolBarCtrl)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(COXToolBarCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:

};

class OX_CLASS_DECL COXSizeToolBar : public COXSizeControlBar
{
DECLARE_DYNAMIC(COXSizeToolBar);

// Data members -------------------------------------------------------------
public:

	COXToolBarCtrl	m_ToolCtrl;

protected:

	CSize	m_ToolCtrlButtonSize;		// size of buttons in CToolBarCtrl - not available
	CBitmap m_Bitmap;					// bitmap to be used in control

private :

	UINT* 	m_pBitmapIds;				// ID pallette in the bitmap 
	int		m_nBitmapButtons;			// no of buttons in the toolbar palette

// Member functions ---------------------------------------------------------
public:
	
	COXSizeToolBar(int nStyle = 0);
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Constructor of object
	//				It will initialize the internal state

	BOOL Create(CWnd* pParent, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP,
	 			UINT nID = AFX_IDW_TOOLBAR, LPRECT pRect = NULL);
	// --- In  : pParent : Parent window
	//			 dwStyle : Style.
	//			 nID : ID.
	//			 pRect : Points to a rectangle for the initial size of the toolbar.
	//					 If NULL, the a rectangle big enough for 1 row of standard sized
	//					 toolbar buttons is used.  
	// --- Out : 
	// --- Returns : succeeded or not
	// --- Effect : Creates the underlying windows objects for the toolbar.

	BOOL LoadBitmap(LPCTSTR lpszResourceName);
	// --- In  : lpszResourceName : Resource string of bitmap to load
	// --- Out : 
	// --- Returns : succeeded or not
	// --- Effect : Sets the underlying bitmap to be used for the images on the toolbar
	//				buttons
	//				Non-Compatibility with CToolBar
	//					1.LoadBitmap() may only be called once for COXSizeToolBar.
	//					2. If you wish to use a toolbar with non-standard sizes, you should call SetSizes() before LoadBitmap().
	//				These are underlying restrictions in CToolBarCtrl.


	BOOL LoadBitmap(UINT nID)
			{ return LoadBitmap(MAKEINTRESOURCE(nID)); };
	// --- In  : nID : Resource ID of bitmap to load
	// --- Out : 
	// --- Returns : succeeded or not
	// --- Effect : Sets the underlying bitmap to be used for the images on the toolbar
	//				buttons
	//				Non-Compatibility with CToolBar
	//					1.LoadBitmap() may only be called once for COXSizeToolBar.
	//					2. If you wish to use a toolbar with non-standard sizes, you should call SetSizes() before LoadBitmap().
	//				These are underlying restrictions in CToolBarCtrl.

	void SetSizes(SIZE sizeButton, SIZE sizeImage);
	// --- In  : sizeButton : Sizes of the buttons in the underlying toolbar.
	//			 sizeImage : Sizes of images in the underlying toolbar
	// --- Out : 
	// --- Returns :
	// --- Effect : Sets the sizes of the images in the underlying bitmap, and of the buttons
	//				in the toolbar.
	//				Non-Compatibility with CToolBar
	//					1. Setsizes() must be called after Create()
	//					2. SetSizes() should be called before LoadBitmap() to have any effect on the image sizes.
	//				These are underlying restrictions in CToolBarCtrl.

	BOOL SetButtons(UINT* pButtons, int nButtons);
	// --- In  : pButtons : Points to an array of button command Ids.
	//			 nButtons : Number of buttons in the above array.
	// --- Out : 
	// --- Returns : succeeded or not
	// --- Effect : Sets the command id’s for the buttons in the toolbar. This function
	//				is equivalent to CToolBar::SetButtons(). 
	//				Non-Compatibility with CToolBar
	//					1. SetButtons() must be called after Create() and LoadBitmap().


	void SetBitmapIds(UINT* pIds, int nButtons);
	// --- In  : pIds : Points to an array of button bitmap Ids.
	//			 nButtons : Number of buttons in the above array.
	// --- Out : 
	// --- Returns :
	// --- Effect : This function enables the CToolBarCtrl configuration features. It specifies
	//				an array of command IDs that the images in the bitmap represent. Call this
	//				function before Create(), and SetButtons() and the toolbar will be created
	//				with the CCS_ADJUSTABLE style. SetButtons() then uses this specified array
	//				to determine which bitmap images to use, and the common control customization
	//				dialog uses it to determine which buttons could possible be on the toolbar.
	//				The idea is that you call SetBitmapIds() to set the ID’s that correspond  to
	//				the images in the bitmap, and SetButtons() to determine the command ID’s
	//				that are actually on the toolbar. 
	//
	//				The common control customization allows buttons you to drag buttons,
	//				by holding the shift button and clicking and dragging the button, either to
	//				a new position on the toolbar, or off it (to remove it from the toolbar).
	//				Double-clicking displays the configuration dialog.

	CToolBarCtrl* GetToolBarCtrl();
	// --- In  :
	// --- Out : 
	// --- Returns : the underlying CToolBarCtrl object
	// --- Effect : Returns a pointer to the underlying CToolBarCtrl object (Windows’95 common
	//				control). You should manipulate this object explicitly to obtain more
	//				refined toolbar behaviour - e.g. setting buttons, etc.

	virtual ~COXSizeToolBar();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

protected:

	//{{AFX_MSG(COXSizeToolBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:

	int FindBitmapIndex(UINT nID);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXSizeToolBar)
	protected:
	//}}AFX_VIRTUAL
	afx_msg void OnTBNToolTip(UINT uID, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTBNBeginAdjust(UINT uID, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTBNQueryInsert(UINT uID, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTBNQueryDelete(UINT uID, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTBNToolBarChange(UINT uID, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTBNGetButtonInfo(UINT uID, NMHDR* pNMHDR, LRESULT* pResult);

	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

};

#endif // __SIZETOOLBAR_H__

