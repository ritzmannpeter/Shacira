// ==========================================================================
// 					Class Specification : COXDropEdit
// ==========================================================================

// Header file : OXDropEdit.h

// Copyright © Dundas Software Ltd. 1997 - 1999, All Rights Reserved

// //////////////////////////////////////////////////////////////////////////


/*

DESCRIPTION


COXDropEdit is template class that provides the functionality of adding dropdown button
to any edit control. Dropdown button is displayed on the right or left side of the 
edit box and takes all height of the control window. The width of the dropdown button 
can be set programmatically (by default we use the width of the current width of 
the scroll bar). 

The dropdown button is clickable and combination of 'pressed down' and 'unpressed' 
events would generate 'dropdown' event that can be handled by a programmer. By default,
COXDropEdit class allows you to display associated menu (see below how to associate 
a menu with COXDropEdit).

At any time you can hide or show the dropdown button. Internally, the dropdown button 
resides in the non-client area so this class can be safely used with most of
customized edit controls. E.g. you can use it with our extended controls (COXEdit,
COXNumericEdit, COXCurrencyEdit, COXMaskedEdit) without any problems. In fact, we've
updated our COXPhysicalEdit class to be derived from COXDropEdit in order to provide the 
functionality of changing the base unit by clicking on the dropdown button and choosing 
the unit from the popup menu.


A programmer would normally use COXDropEdit class in order to derive from it. 
Let's go through the steps of creating a simple edit control that will display
popup menu as a result of clicking the dropdown button and after a user choose  
an item in the menu the text in the edit box will be updated orrespondingly.

1)	Derive your own class from COXDropEdit using any existing edit class as the base one:
	
	class CMenuEdit: public COXDropEdit<CEdit>

	In this case we declare the class that would use standard CEdit as the base class


2)	Declare the following protected virtual	function in the class that will be called 
	every time the dropdown button is clicked:

	virtual void OnDropButton();

	In our case we would use the default implementation of this function as long as we
	are going to display the menu (this functionality provided by COXDropEdit by default).
	But, generally, you can put here any functionality you please: e.g display popup 
	window or dialog.

	void CMenuEdit::OnDropButton()
	{
		COXDropEdit<CEdit>::OnDropButton();
	}


3)	Declare the following protected	member for the popup menu that will be displayed
	when the dropdown button is clicked:

	CMenu m_menu;

	In order to associate a menu with COXDropEdit object you have to call the 
	following COXDropEdit function:

	AssociateMenu();

	and the pointer to the associated menu can be retrieved using this function:

	GetAssociatedMenu();


4)	So we need to create popup menu and associate it with the object. We suggest 
	you can do that in the following COXDropEdit protected virtual function that 
	should be overridden in CMenuEdit class:

	virtual BOOL InitializeDropEdit();
	
	This function is called right after creation or subclassing of existed control.
	Primarily it was designed in order to provide a programmer with the functionality
	that can be used in order to safely initialize the control. This function must
	return TRUE if the control has been successfully initialized or FALSE otherwise.
	In your implementation you must call the parent implementation first of all.

	BOOL CMenuEdit::InitializeDropEdit()
	{
		if(!COXDropEdit<CEdit>::InitializeDropEdit())
			return FALSE;

		if(!m_menu.CreatePopupMenu())
			return FALSE;
		for(int nIndex=1; nIndex<=10; nIndex++)
		{
			CString sMenuText;
			sMenuText.Format(_T("Item %d"),nIndex);
			m_menu.AppendMenu(MF_STRING,nIndex,sMenuText);
		}
		AssociateMenu(&m_menu);

		return TRUE;
	}

	
5)	In our case we display popup menu as a result of dropdown event. 
	In order to handle the process of choosing the menu item we have to provide
	WM_COMMAND handler for the class using ON_COMMAND_RANGE() or ON_COMMAND() macro.
	In our case our actions are not going to depend on the chosen item so we would 
	define our handler as follows:

	afx_msg void OnMenuSelect(UINT nID);
	. . . . . . . . . . . . . . . . . . 
	BEGIN_MESSAGE_MAP(CMenuEdit, CEdit)
		//{{AFX_MSG_MAP(CMenuEdit)
		//}}AFX_MSG_MAP
		ON_COMMAND_RANGE(1,10,OnMenuSelect)
	END_MESSAGE_MAP()
	. . . . . . . . . . . . . . . . . . 
	void CMenuEdit::OnMenuSelect(UINT nID)
	{
		CString sItem;
		m_menu.GetMenuString(nID,sItem,MF_BYCOMMAND);
		CString sText;
		sText.Format(_T("<%s> has been picked"),sItem);

		SetWindowText(sText);
	}



6)	Basically we went through all the major steps that should be taken in order to 
	implement COXDropEdit derived object. Below you will find information about 
	some useful COXDropEdit functions that you might want to use in your applications:

	-	the following two protected virtual functions can be overridden in order
	to customize the appearance of the dropdown button:

  	virtual CRect DrawButtonFrame(CDC* pDC, CRect rect, BOOL bPressed);
	virtual void DrawButtonImage(CDC* pDC, CRect rect, BOOL bPressed);

	
	-	the following functions can be used in order to set/retrieve the width 
	of the dropdown button:

	SetButtonWidth(); 
	GetButtonWidth();


	-	these functions can be used in order to show/hide the dropdown button and 
	to retrieve the flag that specifies the visibility of the dropdown button:

	void ShowButton();
	BOOL IsButtonVisible();

	
	For details refer to the COXDropEdit class reference.



As we mentioned before we use COXDropEdit derivation with our COXPhysicalEdit class.
Also we designed and implemented a number of COXDropEdit derived classes with predefined
functionality. These classes are: COXBrowseColorEdit (edit control with color picker
using our COXColorPickerCtrl), COXBrowseDirEdit (edit control with Directory Picker 
using our COXFolderPicker), COXBrowseDirEdit16 (edit control with Directory Picker 
using our COXDirectoryDialog), COXBrowseFileEdit (edit control with File Picker using
standard CFileDialog).



Take a look at the ExtendedEditControls sample that can be found in the 
.\Samples\gui\ExtendedEditControls subdirectory of your Ultimate Toolbox directory.
In the sample check out the 'Physical Edit' and 'Drop Edit' pages that demonstrate the
power of COXDropEdit class.



Dependencies:
	#include "OXDropEdit.h"


*/

#if !defined(_OXDROPEDIT_H__)
#define _OXDROPEDIT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXDllExt.h"


// dropbutton alignment
#define OXDROPEDIT_BUTTONRIGHT				0
#define OXDROPEDIT_BUTTONLEFT				1

// timer for checking the state of the button (pressed or unpressed)
#define IDT_OXDROPEDIT_CHECKBUTTONSTATE		227
#define ID_OXDROPEDIT_TIMER_DELAY			200

// system keys state
#define PRESSEDIN_CONTROL			0x00000001
#define PRESSEDIN_SHIFT				0x00000002
#define PRESSEDIN_ALT				0x00000004
/////////////////////////////////////////////////////////////////////////////
// COXDropEdit window

template<class PARENTEDIT>
class OX_CLASS_DECL COXDropEdit : public PARENTEDIT
{
// Construction
public:
	// --- In  :	
	// --- Out : 
	// --- Returns:
	// --- Effect : Constructs the object
	COXDropEdit();

// Attributes
public:

protected:
	// button alignment (left or right)
	int m_nButtonAlignment;
	// button width
	int m_nButtonWidth;
	// flag that specifies whether the button is visible or not
	BOOL m_bShowButton;
	// flag that specifies button state
	BOOL m_bButtonPressed;
	// flag that specifies that at the time of last check mouse cursor 
	// was over the dropdown button
	BOOL m_bMouseWasOver;

	// internal flag that specifies whether the window is needed to be
	// properly initialized
	BOOL m_bInitializedDropEdit;
	// internal flag that specifies that process of creation has been finished
	BOOL m_bCreated;


	// if control must recalc its size in order to make room for dropdown button
	BOOL m_bForceToRecalc;

	// timer to check the state of a dropdown button
	int m_nTimerToCheckButtonState;

	// menu to be displayed as result of drop button event
	CMenu* m_pMenu;

	// virtual code of the key that used to emulate the process of clicking on 
	// the button. The value of m_dwDropdownKeyState member is also checked which
	// determines what system key(s) must be also pressed in.
	int m_nVCDropdownKey;

	// state of the "Ctrl", "Shift", "Alt" keys when m_nVCDropdownKey key is pressed in.
	// Can be zero or any combination of folowing flags:
	//
	//		PRESSEDIN_CONTROL	-	"Ctrl" key must be pressed in
	//		PRESSEDIN_SHIFT	-	"Shift" key must be pressed	in
	//		PRESSEDIN_ALT		-	"Alt" key must be pressed in
	DWORD m_dwDropdownKeyState;


// Operations
public:

	// --- In  :	
	// --- Out : 
	// --- Returns: The width of the dropdown button in pixels
	// --- Effect : Retrieves the width of the dropdown button
	inline int GetButtonWidth() const { return m_nButtonWidth; }

	// --- In  :	nButtonWidth	-	new width of the dropdown button in pixels
	// --- Out : 
	// --- Returns: 
	// --- Effect : Sets the width of the dropdown button
	inline void SetButtonWidth(int nButtonWidth) 
	{ 
		if(m_nButtonWidth!=nButtonWidth)
		{
			m_nButtonWidth=nButtonWidth;
			ForceToRecalcLayout();
		}
	}


	// --- In  :	
	// --- Out : 
	// --- Returns: TRUE if dropdown button is displayed or FALSE otherwise
	// --- Effect : Retrieves the flag that specifies the visibility  
	//				of the dropdown button
	inline BOOL IsButtonVisible() const { return m_bShowButton; }

	// --- In  :	bShowButton	-	if TRUE then the dropdown button will be displayed,
	//								if FALSE - hidden	
	// --- Out : 
	// --- Returns: 
	// --- Effect : Shows/Hides the dropdown button
	inline void ShowButton(BOOL bShowButton) 
	{
		if(m_bShowButton!=bShowButton)
		{
			m_bShowButton=bShowButton;
			ForceToRecalcLayout();
		}
	}


	// --- In  :	
	// --- Out : 
	// --- Returns: The dropdown button alignment. Could be one of the followinfg:
	//				
	//					OXDROPEDIT_BUTTONRIGHT		-	the dropdown button will be
	//													located on the right side of
	//													the control
	//					OXDROPEDIT_BUTTONLEFT		-	the dropdown button will be
	//													located on the left side of
	//													the control
	// --- Effect : Retrieves the value that specifies the position of the dropdown 
	//				button  in the control
	inline int GetButtonAlignment() const { return m_nButtonAlignment; }

	// --- In  :	nButtonAlignment	-	The new dropdown button alignment. Could be 
	//										one of the followinfg:
	//				
	//					OXDROPEDIT_BUTTONRIGHT		-	the dropdown button will be
	//													located on the right side of
	//													the control
	//					OXDROPEDIT_BUTTONLEFT		-	the dropdown button will be
	//													located on the left side of
	//													the control
	// --- Out : 
	// --- Returns: 
	// --- Effect : Sets the value that specifies the position of the dropdown 
	//				button  in the control
	inline void SetButtonAlignment(int nButtonAlignment) 
	{ 
		if(m_nButtonAlignment!=nButtonAlignment)
		{
			m_nButtonAlignment=nButtonAlignment;
			ForceToRecalcLayout();
		}
	}


	// --- In  :	
	// --- Out : 
	// --- Returns: pointer to the associated menu that will be displayed when
	//				the dropdown button is pressed if any was set using AssociateMenu()
	//				function, or NULL if there is no menu associated with the control
	// --- Effect : Retrieves the pointer to the associated menu. If any menu is
	//				associated with the control then it will be automatically activated
	//				whenever the dropdown button is pressed
	inline CMenu* GetAssociatedMenu() const { return m_pMenu; }

	// --- In  :	pMenu	-	pointer to created popup menu that will be displayed 
	//							when the dropdown button is pressed
	// --- Out : 
	// --- Returns: 
	// --- Effect : Assotiates the specified menu with the control. The menu 
	//				associated with the control will be automatically activated
	//				whenever the dropdown button is pressed
	void AssociateMenu(const CMenu* pMenu);


	// --- In     :
	// --- Out    :
	// --- Returns:
	// --- Effect : Recalculates the layout of the control
	inline void ForceToRecalcLayout() { 
		if(::IsWindow(GetSafeHwnd()))
		{
			::SetWindowPos(GetSafeHwnd(),NULL,0,0,0,0,
				SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED); 
		}
	}


	// --- In  :	nVCDropdownKey	-	virtual-key code of the button that 
	//									can be used in combination with pressed in
	//									'Alt' key in order to emulate clicking
	//									on the dropdown button
	//				dwKeyState		-	state of the "Ctrl", "Shift", "Alt" keys 
	//									when nVCDropdownKey key is pressed. Can be
	//									zero or any combination of following flags:
	//
	//							PRESSEDIN_CONTROL	-	"Ctrl" key must be pressed
	//							PRESSEDIN_SHIFT		-	"Shift" key must be pressed
	//							PRESSEDIN_ALT		-	"Alt" key must be pressed
	// --- Out : 
	// --- Returns: 
	// --- Effect : Sets the virtual-key code of the button that can be used in 
	//				combination with pressed in	'Alt' key in order to emulate clicking
	//				on the dropdown button
	inline void SetDropdownKey(const int nVCDropdownKey, 
		DWORD dwKeyState=PRESSEDIN_ALT) 
	{
		m_nVCDropdownKey=nVCDropdownKey; 
		m_dwDropdownKeyState=dwKeyState;
	}

	// --- In  :	
	// --- Out :	
	// --- Returns: Virtual-key code of the button that can be used in order to 
	//				emulate clicking on the dropdown button
	// --- Effect : Retrieves the virtual-key code of the key that can be used 
	//				in order to emulate clicking on the dropdown button
	inline int GetDropdownKey() const 
	{ 
		return m_nVCDropdownKey; 
	}

	// --- In  :	
	// --- Out :	
	// --- Returns: State of the "Ctrl", "Shift", "Alt" keys when dropdown key is 
	//				pressed. Can be	zero or any combination of following flags:
	//
	//						PRESSEDIN_CONTROL	-	"Ctrl" key must be pressed
	//						PRESSEDIN_SHIFT		-	"Shift" key must be pressed
	//						PRESSEDIN_ALT		-	"Alt" key must be pressed	
	//
	// --- Effect : Retrieves the state of the system keys that that they must be in
	//				when dropdown key is pressed
	inline DWORD GetDropdownKeyState() const 
	{ 
		return m_dwDropdownKeyState; 
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXDropEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	// --- In     :
	// --- Out    :
	// --- Returns:
	// --- Effect : Destructs the object
	virtual ~COXDropEdit();


	// --- In     :	ptTest	-	point (in screen coordinates) to test it it lays 
	//							in the dropdown button rectangle
	// --- Out    :
	// --- Returns: TRUE if specified point lays in the dropdown button rectangle
	// --- Effect : Retrieves the flag that defines if specified point in screen
	//				coordinates lays in the dropdown button rectangle
	BOOL HitButtonTest(CPoint ptTest);

protected:
	// called every time button is pressed
	virtual void OnDropButton();

	// initialize control
	virtual BOOL InitializeDropEdit();

	// calculates dropdown button coordinates based on the control position,
	// button alignment and button width
	CRect CalcButtonRect() const;

	// called every time button border must be drawn
	virtual CRect DrawButtonFrame(CDC* pDC, CRect rect, BOOL bPressed);
	// called every time button image must be drawn
	virtual void DrawButtonImage(CDC* pDC, CRect rect, BOOL bPressed);

protected:
	// is handled in order to properly initialize the subclassed window
	virtual void PreSubclassWindow();
	// handles some messages that are important for internal implementation
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////

template<class PARENTEDIT>
COXDropEdit<PARENTEDIT>::COXDropEdit() 
{
	if(!PARENTEDIT::IsKindOf(RUNTIME_CLASS(CEdit)))
	{
		TRACE(_T("COXDropEdit<PARENTEDIT>::COXDropEdit: Parent class must be CEdit derived\n"));
		AfxThrowNotSupportedException();
	}
	m_bShowButton=TRUE;
	m_nButtonAlignment=OXDROPEDIT_BUTTONRIGHT;
	m_nButtonWidth=::GetSystemMetrics(SM_CXHTHUMB);
	m_bButtonPressed=FALSE;

	m_bInitializedDropEdit=FALSE;
	m_bCreated=FALSE;

	m_bForceToRecalc=FALSE;

	m_nTimerToCheckButtonState=0;

	m_pMenu=NULL;

	m_nVCDropdownKey=VK_RETURN;
	m_dwDropdownKeyState=PRESSEDIN_ALT;

	m_bMouseWasOver=FALSE;
}


template<class PARENTEDIT>
COXDropEdit<PARENTEDIT>::~COXDropEdit() 
{
}

template<class PARENTEDIT>
LRESULT COXDropEdit<PARENTEDIT>::WindowProc(UINT message, WPARAM wParam, 
											LPARAM lParam) 
{
#if defined (_WINDLL)
#if defined (_AFXDLL)
	AFX_MANAGE_STATE(AfxGetAppModuleState());
#else
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
#endif

	// TODO: Add your specialized code here and/or call the base class
	ASSERT_VALID(this);

	if(!m_bInitializedDropEdit && m_bCreated)
	{
		m_bInitializedDropEdit=TRUE;
		InitializeDropEdit();
	}

	if(m_bForceToRecalc)
	{
		m_bForceToRecalc=FALSE;
		ForceToRecalcLayout();
	}

	switch(message) 
	{
	case WM_DESTROY:
		{
			if(m_nTimerToCheckButtonState!=0)
			{
				KillTimer(m_nTimerToCheckButtonState);
				m_nTimerToCheckButtonState=0;
			}
			break;
		}
	case WM_NCCALCSIZE:
		{
			LRESULT lResult=PARENTEDIT::WindowProc(message, wParam, lParam);
			// add an offset
			if(IsButtonVisible())
			{
				LPNCCALCSIZE_PARAMS lpncsp=(LPNCCALCSIZE_PARAMS)lParam;
				if(lpncsp->rgrc[0].right-lpncsp->rgrc[0].left>GetButtonWidth())
				{
					if(GetButtonAlignment()==OXDROPEDIT_BUTTONRIGHT)
						lpncsp->rgrc[0].right-=GetButtonWidth();
					else
						lpncsp->rgrc[0].left+=GetButtonWidth();
				}
				else
				{
					lpncsp->rgrc[0].right=lpncsp->rgrc[0].left;
				}
			}
			return lResult;
		}


	case WM_NCPAINT:
    case WM_PAINT:
		{
			LRESULT lResult=PARENTEDIT::WindowProc(message, wParam, lParam);
			if(IsButtonVisible())
			{
				CWindowDC dc(this);
				CRect rectWindow;
				GetWindowRect(rectWindow);
				ScreenToClient(rectWindow);
				CRect rectButton=CalcButtonRect();
				rectButton-=rectWindow.TopLeft();
				rectButton=DrawButtonFrame(&dc,rectButton,
					m_bButtonPressed&m_bMouseWasOver);
				DrawButtonImage(&dc,rectButton,
					m_bButtonPressed&m_bMouseWasOver);
			}
			return lResult;
		}


	case WM_NCHITTEST:
		{
			if(HitButtonTest(CPoint(LOWORD(lParam),HIWORD(lParam))))
			{
				return (LRESULT)HTBORDER;
			}
			break;
		}


	case WM_NCLBUTTONDOWN:
		{
			LRESULT lResult=PARENTEDIT::WindowProc(message, wParam, lParam);
			
			if(!IsWindowEnabled() || (GetStyle()&ES_READONLY))
				return lResult;

			if(HitButtonTest(CPoint(LOWORD(lParam),HIWORD(lParam))))
			{
				m_bButtonPressed=TRUE;
				m_bMouseWasOver=TRUE;
				RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_FRAME);

				m_nTimerToCheckButtonState=SetTimer(IDT_OXDROPEDIT_CHECKBUTTONSTATE,
					ID_OXDROPEDIT_TIMER_DELAY,NULL);
				if(m_nTimerToCheckButtonState==0)
				{
					TRACE(_T("COXDropEdit::WindowProc: failed to set timer for checking the sate of the dropdown button\n"));
				}	
			}
			return lResult;
		}


	case WM_NCLBUTTONUP:
		{
			LRESULT lResult=PARENTEDIT::WindowProc(message, wParam, lParam);
			if(HitButtonTest(CPoint(LOWORD(lParam),HIWORD(lParam))))
			{
				if(m_bButtonPressed)
				{
					m_bButtonPressed=FALSE;
					m_bMouseWasOver=FALSE;
					if(m_nTimerToCheckButtonState!=0)
					{
						KillTimer(m_nTimerToCheckButtonState);
						m_nTimerToCheckButtonState=0;
					}
					RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_FRAME);
					OnDropButton();
				}
			}
			return lResult;
		}


	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		{
			if(!IsWindowEnabled() || (GetStyle()&ES_READONLY))
				break;

			if((int)wParam==GetDropdownKey())
			{
				BOOL bKeyState=TRUE;
				if((m_dwDropdownKeyState&PRESSEDIN_CONTROL)!=0)
					bKeyState&=(GetKeyState(VK_CONTROL)<0);
				if((m_dwDropdownKeyState&PRESSEDIN_SHIFT)!=0)
					bKeyState&=(GetKeyState(VK_SHIFT)<0);
				if((m_dwDropdownKeyState&PRESSEDIN_ALT)!=0)
					bKeyState&=(GetKeyState(VK_MENU)<0);

				if(bKeyState)
				{
					if(m_bButtonPressed)
					{
						m_bButtonPressed=FALSE;
						m_bMouseWasOver=FALSE;
						if(m_nTimerToCheckButtonState!=0)
						{
							KillTimer(m_nTimerToCheckButtonState);
							m_nTimerToCheckButtonState=0;
						}
						RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_FRAME);
					}
					OnDropButton();
					return 0;
				}
			}
			break;
		}


	case WM_TIMER:
		{
			if(wParam==(WPARAM)m_nTimerToCheckButtonState)
			{
				if(m_bButtonPressed)
				{
					if(GetKeyState(VK_LBUTTON)<0)
					{
						CPoint ptCursor;
						::GetCursorPos(&ptCursor);
						if(HitButtonTest(ptCursor) && !m_bMouseWasOver)
						{
							m_bMouseWasOver=TRUE;
							RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_FRAME);
						}
						else if(!HitButtonTest(ptCursor) && m_bMouseWasOver)
						{
							m_bMouseWasOver=FALSE;
							RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_FRAME);
						}
					}
					else
					{
						m_bButtonPressed=FALSE;
						if(m_nTimerToCheckButtonState!=0)
						{
							KillTimer(m_nTimerToCheckButtonState);
							m_nTimerToCheckButtonState=0;
						}
						RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_FRAME);
					}
				}
				return 0;
			}
			break;
		}
	}

	LRESULT lResult=PARENTEDIT::WindowProc(message, wParam, lParam);

	if(message==WM_CREATE)
		m_bCreated=TRUE;

	return lResult;
}


template<class PARENTEDIT>
void COXDropEdit<PARENTEDIT>::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	_AFX_THREAD_STATE* pThreadState=AfxGetThreadState();
	// hook not already in progress
	if(pThreadState->m_pWndInit==NULL && !m_bInitializedDropEdit)
	{
		m_bInitializedDropEdit=TRUE;
		InitializeDropEdit();
		m_bForceToRecalc=TRUE;
	}
	
	PARENTEDIT::PreSubclassWindow();
}


template<class PARENTEDIT>
BOOL COXDropEdit<PARENTEDIT>::InitializeDropEdit()
{
	ASSERT(::IsWindow(GetSafeHwnd()));
	return TRUE;
}


template<class PARENTEDIT>
CRect COXDropEdit<PARENTEDIT>::CalcButtonRect() const
{
	ASSERT(::IsWindow(GetSafeHwnd()));

	CRect rect(0,0,0,0);

	if(IsButtonVisible())
	{
		GetClientRect(rect);
		if(GetButtonAlignment()==OXDROPEDIT_BUTTONRIGHT)
		{
			rect.left=rect.right;
			rect.right=rect.left+GetButtonWidth();
		}
		else
		{
			rect.right=rect.left;
			rect.left=rect.right-GetButtonWidth();
		}
	}

	return rect;
}


template<class PARENTEDIT>
void COXDropEdit<PARENTEDIT>::OnDropButton()
{
	if(m_pMenu!=NULL)
	{
		ASSERT((HMENU)*m_pMenu!=NULL);

		CRect rect;
		GetWindowRect(rect);
		CPoint ptOrigin=rect.BottomRight();
		UINT nFlags=TPM_RIGHTALIGN;
		if(GetButtonAlignment()==OXDROPEDIT_BUTTONLEFT)
		{
			ptOrigin.x=rect.left;
			nFlags=TPM_LEFTALIGN;
		}
		m_pMenu->TrackPopupMenu(nFlags,ptOrigin.x,ptOrigin.y,this);
		SetFocus();
	}
}


template<class PARENTEDIT>
void COXDropEdit<PARENTEDIT>::AssociateMenu(const CMenu* pMenu)
{
	if(pMenu!=NULL)
	{
		ASSERT((HMENU)*pMenu!=NULL);
	}

	m_pMenu=(CMenu*)pMenu;
}


template<class PARENTEDIT>
CRect COXDropEdit<PARENTEDIT>::DrawButtonFrame(CDC* pDC, CRect rect, BOOL bPressed)
{
	ASSERT(pDC!=NULL);

	COLORREF clrTopLeft=(bPressed ? ::GetSysColor(COLOR_BTNSHADOW) :
		::GetSysColor(COLOR_BTNHILIGHT));
	COLORREF clrBottomRight=(bPressed ? ::GetSysColor(COLOR_BTNHILIGHT) :
		::GetSysColor(COLOR_BTNSHADOW));
	pDC->Draw3dRect(rect,clrTopLeft,clrBottomRight);

	rect.DeflateRect(1,1);
	pDC->FillSolidRect(rect,::GetSysColor(COLOR_BTNFACE));

	return rect;
}


template<class PARENTEDIT>
void COXDropEdit<PARENTEDIT>::DrawButtonImage(CDC* pDC, CRect rect, BOOL bPressed)
{
	ASSERT(pDC!=NULL);

	int nOldBkMode=pDC->SetBkMode(TRANSPARENT);
	COLORREF clrText=::GetSysColor(COLOR_WINDOWTEXT);
	if(!IsWindowEnabled() || (GetStyle()&ES_READONLY))
		clrText=::GetSysColor(COLOR_GRAYTEXT);
	COLORREF clrOldText=pDC->SetTextColor(clrText);

	if(bPressed)
		rect.DeflateRect(1,1,0,0);
	CString sText=_T("...");
	pDC->DrawText(sText,rect,DT_CENTER|DT_BOTTOM|DT_SINGLELINE);

	pDC->SetBkMode(nOldBkMode);
	pDC->SetTextColor(clrOldText);
}


template<class PARENTEDIT>
BOOL COXDropEdit<PARENTEDIT>::HitButtonTest(CPoint ptTest)
{
	ASSERT(::IsWindow(GetSafeHwnd()));

	if(!IsButtonVisible())
		return FALSE;

	CRect rectButton=CalcButtonRect();
	ClientToScreen(rectButton);
	return rectButton.PtInRect(ptTest);
}


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_OXDROPEDIT_H__)
