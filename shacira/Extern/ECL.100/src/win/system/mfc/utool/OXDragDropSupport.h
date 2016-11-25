// ====================================================================================
//								Class Specification : 
//						COXSHBDropSource & COXSHBDropTarget
// ====================================================================================

// Header file : OXDragDropSupport.h

// Copyright © Dundas Software Ltd. 1997 - 2000, All Rights Reserved
//////////////////////////////////////////////////////////////////////////////
                         
#if !defined(_OX_DRAGDROPSUPPORT_)
#define _OX_DRAGDROPSUPPORT_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"
#include "OXMainRes.h"

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#define __AFXTEMPL_H__
#endif

#ifndef __AFXOLE_H__
#include <afxole.h>         // MFC OLE classes
#define __AFXOLE_H__
#endif

// All folowing notifications has to do with OLE drag and drop. Refer to the 
// documentation on COleDropSource and COleDropTarget to get full description of
// drag and drop operation.
//
// COleDropTarget based notifications
//
// These notifications can be sent by child windows and shortcut bar. lParam of 
// NMSHORTCUTBAR always points to SHBDROPTARGETACTION structure which is described later.
// If you handle these notifications and don't want to run the default implementation 
// of them then you must return non-zero value and set result element of 
// SHBDROPTARGETACTION structure to corresponding value which is depend on the 
// particular notification.
// You can distinguish the sender of the notification by hGroup element of NMSHORTCUTBAR
// structure: if sender is shortcut bar then hGroup will be set to NULL; if sender is 
// child window then hGroup will be set to corresponding child window parent group.
// 
//
// Sent to parent window to notify that the cursor is first dragged into the window.
// Set result element of SHBDROPTARGETACTION to the effect that would result if a drop 
// were attempted at the location specified by point element of SHBDROPTARGETACTION. 
// It can be one or more of the following:
//
//		DROPEFFECT_NONE		A drop would not be allowed.
//		DROPEFFECT_COPY		A copy operation would be performed.
//		DROPEFFECT_MOVE		A move operation would be performed.
//		DROPEFFECT_LINK		A link from the dropped data to the original data would 
//							be established.
//		DROPEFFECT_SCROLL   A drag scroll operation is about to occur or is occurring 
//							in the target. 
//
// Next elements of SHBDROPTARGETACTION are filled: pWnd, pDataObject, dwKeyState, point
//
//SHBN_DRAGENTER				
//
// Sent to parent window to notify that the cursor leaves the window while a dragging 
// operation is in effect.
// Next elements of SHBDROPTARGETACTION are filled: pWnd
//
//SHBN_DRAGLEAVE				
//
// Sent to parent window to notify that the cursor is dragged over the window. This 
// notification should be handled to allow drop operations to occur in the window. The 
// default implementation returns DROPEFFECT_NONE by default. Because this notification is 
// called frequently during a drag-and-drop operation, it should be optimized as much 
// as possible. Set result element of SHBDROPTARGETACTION to the effect that would 
// result if a drop were attempted at the location specified by point element of 
// SHBDROPTARGETACTION. It can be one or more of the following:
//
//		DROPEFFECT_NONE		A drop would not be allowed.
//		DROPEFFECT_COPY		A copy operation would be performed.
//		DROPEFFECT_MOVE		A move operation would be performed.
//		DROPEFFECT_LINK		A link from the dropped data to the original data would 
//							be established.
//		DROPEFFECT_SCROLL   A drag scroll operation is about to occur or is occurring 
//							in the target. 
//
// Next elements of SHBDROPTARGETACTION are filled: pWnd, pDataObject, dwKeyState, point
//
//SHBN_DRAGOVER				
//
// Sent to parent window before sending SHBN_DRAGENTER or SHBN_DRAGOVER notifications 
// to determine whether point is in the scrolling region. Handle this notification when 
// you want to provide special behavior for this event. The default implementation  
// returns DROPEFFECT_NONE and scrolls the window when the cursor is dragged into the 
// scroll region inside the border of the window. Set result element of 
// SHBDROPTARGETACTION to the effect that would result if a drop were attempted at 
// the location specified by point element of SHBDROPTARGETACTION. It can be one or 
// more of the following:
//
//		DROPEFFECT_NONE		A drop would not be allowed.
//		DROPEFFECT_COPY		A copy operation would be performed.
//		DROPEFFECT_MOVE		A move operation would be performed.
//		DROPEFFECT_LINK		A link from the dropped data to the original data would 
//							be established.
//		DROPEFFECT_SCROLL   A drag scroll operation is about to occur or is occurring 
//							in the target. 
//
// Next elements of SHBDROPTARGETACTION are filled: pWnd, dwKeyState, point.
//
//SHBN_DRAGSCROLL				
//
// Sent to parent window to notify that a drop operation is about to occur. Set result 
// element of SHBDROPTARGETACTION to the TRUE if drop operation was successful or 
// FALSE otherwise.
// Next elements of SHBDROPTARGETACTION are filled: pWnd, pDataObject, point, dropEffect
//
//SHBN_DROP					
//
// Sent to parent window to notify that a drop operation is about to occur. This 
// notification will be sent before SHBDTM_DROP. If you does not handle it, then 
// SHBN_DROP notification will be sent. Typically, you will handle SHBN_DROPEX to 
// support right mouse-button drag and drop. Typically, SHBN_DROP notification is used 
// to handle the case of support for simple drag and drop.
// By default, we simply return a dummy value to indicate the SHBN_DROP notification 
// should be sent. Set result element of SHBDROPTARGETACTION to the drop effects that 
// describe the action associated with a drop operation. See the following list of 
// drop effects:
//
//		DROPEFFECT_NONE		A drop would not be allowed.
//		DROPEFFECT_COPY		A copy operation would be performed.
//		DROPEFFECT_MOVE		A move operation would be performed.
//		DROPEFFECT_LINK		A link from the dropped data to the original data would 
//							be established.
//		DROPEFFECT_SCROLL   A drag scroll operation is about to occur or is occurring 
//							in the target. 
//
// Next elements of SHBDROPTARGETACTION are filled: pWnd, pDataObject, point, 
//													dropEffect, dropList.
//SHBN_DROPEX					
//
//
// COleDropSource based notifications
//
// These notifications can be sent only by child windows. lParam of NMSHORTCUTBAR 
// always points to SHBDROPSOURCEACTION structure which is described later.
// If you handle these notifications and don't want to run the default implementation 
// of them then you must return non-zero value and set result element of 
// SHBDROPSOURCEACTION structure to corresponding value which is depend on the 
// particular notification.
// 
//
// Handle SHBN_GIVEFEEDBACK notification to provide feedback to the user about what 
// would happen if a drop occurred at this point. The default implementation uses 
// the OLE default cursors. For more information on drag-and-drop operations using 
// OLE, see the article Drag and Drop (OLE) in Visual C++ Programmer's Guide.
// Set result element of SHBDROPSOURCEACTION to the DRAGDROP_S_USEDEFAULTCURSORS if 
// dragging is in progress, NOERROR if it is not. 
// Next elements of SHBDROPSOURCEACTION are filled: dropEffect.
//
//SHBN_GIVEFEEDBACK			
//
// SHBN_BEGINDRAG notification is sent to the parent window when an event occurs that 
// could begin a drag operation, such as pressing the left mouse button. Handle this 
// notification if you want to modify the way the dragging process is started. The default 
// implementation captures the mouse and stays in drag mode until the user clicks the 
// left or right mouse button or hits ESC, at which time it releases the mouse. 
// Set result element of SHBDROPSOURCEACTION to TRUE if dragging is allowed, 
// otherwise FALSE. 
// Next elements of SHBDROPSOURCEACTION are filled: pWnd.
// SHBN_BEGINDRAG		
//
// SHBN_QUERYCONTINUEDRAG notification is sent to the parent window after dragging has 
// begun, this notification will be sent repeatedly until the drag operation is either 
// canceled or completed. Handle this notification if you want to change the point at 
// which dragging is canceled or a drop occurs. The default implementation initiates 
// the drop or cancels the drag as follows. It cancels a drag operation when the ESC 
// key or the right mouse button is pressed. It initiates a drop operation when the 
// left mouse button is raised after dragging has started. Otherwise, it returns 
// S_OK and performs no further operations. Because this notification is called frequently,
// it should be optimized as much as possible.
// Set result element of SHBDROPSOURCEACTION to DRAGDROP_S_CANCEL if the ESC key or 
// right button is pressed, or left button is raised before dragging starts, 
// to DRAGDROP_S_DROP if a drop operation should occur, or otherwise to S_OK.
// Next elements of SHBDROPSOURCEACTION are filled: bEscapePressed, dwKeyState .
//SHBN_QUERYCONTINUEDRAG		


// Structure that is used in messages sending from COXSHBDropTarget object
// to its owner window
//
typedef struct _tagSHBDROPTARGETACTION
{
	//
	// Points to the window the cursor is currently over
	CWnd* pWnd;
	//
	// Points to the data object that contains the data to be dropped
	COleDataObject* pDataObject;
	//
	// Contains the state of the modifier keys. This is a combination of any number of 
	// the following: 
	//			MK_CONTROL
	//			MK_SHIFT
	//			MK_ALT
	//			MK_LBUTTON
	//			MK_MBUTTON
	//			MK_RBUTTON
	//
	DWORD dwKeyState;
	//
	// Contains the current location of the cursor in client coordinates.
	CPoint point;
	//
	// The effect that the user chose for the drop operation. It can be one or more of 
	// the following:
	//
	//			DROPEFFECT_COPY			A copy operation would be performed.
	//			DROPEFFECT_MOVE			A move operation would be performed.
	//			DROPEFFECT_LINK			A link from the dropped data to the original 
	//									data would be established.
	//			DROPEFFECT_NONE			A drop would not be allowed.
	//			DROPEFFECT_SCROLL		Indicates that a drag scroll operation is about 
	//									to occur or is occurring in the target. 
	//
	DROPEFFECT dropEffect;
	//
	// A list of the drop effects that the drop source supports. Drop effect values 
	// can be combined using the bitwise OR (|) operation. Drop effects are discussed 
	// above
	DROPEFFECT dropList;
	//
	// result of message handling (differ for different messages)
	LRESULT result;

	_tagSHBDROPTARGETACTION()
	{
		ZeroMemory(this,sizeof(_tagSHBDROPTARGETACTION));
	}

} SHBDROPTARGETACTION, * LPSHBDROPTARGETACTION;


// Following messages are sent to any window that registered as drop target object
// using our COXSHBDropTarget class. For every message wParam is set to NULL and 
// lParam points to SHBDROPTARGETACTION structure. Return TRUE if you handle the
// message and FALSE if you want to run the default implementation. 
//
// Sent to owner window to notify that the cursor is first dragged into the window.
// Set result element of SHBDROPTARGETACTION to the effect that would result if a drop 
// were attempted at the location specified by point element of SHBDROPTARGETACTION. 
// It can be one or more of the following:
//
//		DROPEFFECT_NONE		A drop would not be allowed.
//		DROPEFFECT_COPY		A copy operation would be performed.
//		DROPEFFECT_MOVE		A move operation would be performed.
//		DROPEFFECT_LINK		A link from the dropped data to the original data would 
//							be established.
//		DROPEFFECT_SCROLL   A drag scroll operation is about to occur or is occurring 
//							in the target. 
//
// Next elements of SHBDROPTARGETACTION are filled: pWnd, pDataObject, dwKeyState, point
//
//SHBDTM_DRAGENTER			
//
// Sent to owner window to notify that the cursor leaves the window while a dragging 
// operation is in effect.
// Next elements of SHBDROPTARGETACTION are filled: pWnd
//
//SHBDTM_DRAGLEAVE			
//
// Sent to owner window to notify that the cursor is dragged over the window. This 
// message should be handled to allow drop operations to occur in the window. The 
// default implementation returns DROPEFFECT_NONE by default. Because this message is 
// called frequently during a drag-and-drop operation, it should be optimized as much 
// as possible. Set result element of SHBDROPTARGETACTION to the effect that would 
// result if a drop were attempted at the location specified by point element of 
// SHBDROPTARGETACTION. It can be one or more of the following:
//
//		DROPEFFECT_NONE		A drop would not be allowed.
//		DROPEFFECT_COPY		A copy operation would be performed.
//		DROPEFFECT_MOVE		A move operation would be performed.
//		DROPEFFECT_LINK		A link from the dropped data to the original data would 
//							be established.
//		DROPEFFECT_SCROLL   A drag scroll operation is about to occur or is occurring 
//							in the target. 
//
// Next elements of SHBDROPTARGETACTION are filled: pWnd, pDataObject, dwKeyState, point
//
//SHBDTM_DRAGOVER				
//
// Sent to owner window before sending SHBDTM_DRAGENTER or SHBDTM_DRAGOVER messages 
// to determine whether point is in the scrolling region. Handle this message when 
// you want to provide special behavior for this event. The default implementation  
// returns DROPEFFECT_NONE and scrolls the window when the cursor is dragged into the 
// scroll region inside the border of the window. Set result element of 
// SHBDROPTARGETACTION to the effect that would result if a drop were attempted at 
// the location specified by point element of SHBDROPTARGETACTION. It can be one or 
// more of the following:
//
//		DROPEFFECT_NONE		A drop would not be allowed.
//		DROPEFFECT_COPY		A copy operation would be performed.
//		DROPEFFECT_MOVE		A move operation would be performed.
//		DROPEFFECT_LINK		A link from the dropped data to the original data would 
//							be established.
//		DROPEFFECT_SCROLL   A drag scroll operation is about to occur or is occurring 
//							in the target. 
//
// Next elements of SHBDROPTARGETACTION are filled: pWnd, dwKeyState, point.
//
//SHBDTM_DRAGSCROLL			
//
// Sent to owner window to notify that a drop operation is about to occur. Set result 
// element of SHBDROPTARGETACTION to the TRUE if drop operation was successful or 
// FALSE otherwise.
// Next elements of SHBDROPTARGETACTION are filled: pWnd, pDataObject, point, dropEffect
//
//SHBDTM_DROP					
//
// Sent to owner window to notify that a drop operation is about to occur. This 
// message will be sent before SHBDTM_DROP. If you does not handle it, then 
// SHBDTM_DROP message will be sent. Typically, you will handle SHBDTM_DROPEX in 
// your child window class to support right mouse-button drag and drop. Typically, 
// SHBDTM_DROP message is used to handle the case of support for simple drag and drop.
// By default, we simply return a dummy value to indicate the SHBDTM_DROP message 
// should be sent. Set result element of SHBDROPTARGETACTION to the drop effects that 
// describe the action associated with a drop operation. See the following list of 
// drop effects:
//
//		DROPEFFECT_NONE		A drop would not be allowed.
//		DROPEFFECT_COPY		A copy operation would be performed.
//		DROPEFFECT_MOVE		A move operation would be performed.
//		DROPEFFECT_LINK		A link from the dropped data to the original data would 
//							be established.
//		DROPEFFECT_SCROLL   A drag scroll operation is about to occur or is occurring 
//							in the target. 
//
// Next elements of SHBDROPTARGETACTION are filled: pWnd, pDataObject, point, 
//													dropEffect, dropList.
//SHBDTM_DROPEX				


// Structure that is used in messages sending from COXSHBDropSource object
// to its owner window
//
typedef struct _tagSHBDROPSOURCEACTION
{
	//
	// Points to the window that contains the selected data.
	CWnd* pWnd;
	//
	// Contains the state of the modifier keys. This is a combination of any number of 
	// the following: 
	//			MK_CONTROL
	//			MK_SHIFT
	//			MK_ALT
	//			MK_LBUTTON
	//			MK_MBUTTON
	//			MK_RBUTTON
	//
	DWORD dwKeyState;
	//
	// Used only with SHBDS_QUERYCONTINUEDRAG and states whether the ESC key has been 
	// pressed since the last time this message was sent.
	BOOL bEscapePressed;
	//
	// The effect you would like to display to the user, usually indicating what 
	// would happen if a drop occurred at this point with the selected data. It can 
	// be one or more of the following:
	//
	//			DROPEFFECT_COPY			A copy operation would be performed.
	//			DROPEFFECT_MOVE			A move operation would be performed.
	//			DROPEFFECT_LINK			A link from the dropped data to the original 
	//									data would be established.
	//			DROPEFFECT_NONE			A drop would not be allowed.
	//			DROPEFFECT_SCROLL		Indicates that a drag scroll operation is about 
	//									to occur or is occurring in the target. 
	//
	DROPEFFECT dropEffect;
	//
	// result of message handling (differ for different messages)
	LRESULT result;

	_tagSHBDROPSOURCEACTION()
	{
		ZeroMemory(this,sizeof(_tagSHBDROPSOURCEACTION));
	}

} SHBDROPSOURCEACTION, * LPSHBDROPSOURCEACTION;


// Following messages are sent to any window that uses COXSHBDropSource class in 
// its drag'n'drop operations. For every message wParam is set to NULL and 
// lParam points to SHBDROPSOURCEACTION structure. Return TRUE if you handle the
// message and FALSE if you want to run the default implementation. 
//
// Handle SHBDSM_GIVEFEEDBACK message to provide feedback to the user about what 
// would happen if a drop occurred at this point. The default implementation uses 
// the OLE default cursors. For more information on drag-and-drop operations using 
// OLE, see the article Drag and Drop (OLE) in Visual C++ Programmer's Guide.
// Set result element of SHBDROPSOURCEACTION to the DRAGDROP_S_USEDEFAULTCURSORS if 
// dragging is in progress, NOERROR if it is not. 
// Next elements of SHBDROPSOURCEACTION are filled: dropEffect.
//
//SHBDSM_GIVEFEEDBACK			
//
// SHBDSM_BEGINDRAG message is sent to the owner window when an event occurs that 
// could begin a drag operation, such as pressing the left mouse button. Handle this 
// message if you want to modify the way the dragging process is started. The default 
// implementation captures the mouse and stays in drag mode until the user clicks the 
// left or right mouse button or hits ESC, at which time it releases the mouse. 
// Set result element of SHBDROPSOURCEACTION to TRUE if dragging is allowed, 
// otherwise FALSE. 
// Next elements of SHBDROPSOURCEACTION are filled: pWnd.
//SHBDSM_BEGINDRAG			
//
// SHBDSM_QUERYCONTINUEDRAG message is sent to the owner window after dragging has 
// begun, this message will be sent repeatedly until the drag operation is either 
// canceled or completed. Handle this message if you want to change the point at 
// which dragging is canceled or a drop occurs. The default implementation initiates 
// the drop or cancels the drag as follows. It cancels a drag operation when the ESC 
// key or the right mouse button is pressed. It initiates a drop operation when the 
// left mouse button is raised after dragging has started. Otherwise, it returns 
// S_OK and performs no further operations. Because this message is called frequently,
// it should be optimized as much as possible.
// Set result element of SHBDROPSOURCEACTION to DRAGDROP_S_CANCEL if the ESC key or 
// right button is pressed, or left button is raised before dragging starts, 
// to DRAGDROP_S_DROP if a drop operation should occur, or otherwise to S_OK.
// Next elements of SHBDROPSOURCEACTION are filled: bEscapePressed, dwKeyState .
//
//SHBDSM_QUERYCONTINUEDRAG	


/////////////////////////////////////////////////////////////////////////////
// COXSHBDropSource 

/*

COXSHBDropSource is designed to provide a standard way of handling OLE drag and drop
operation in any window. COXSHBDropSource is derived from standard COleDropSource class,
and you can use it as common COleDropSource object in COleDataSource::DoDragDrop 
function. The only thing you have to do is to register the window that launch drag and 
drop operation as COXSHBDropSource owner window using 
COXSHBDropSource::SetOwner(CWnd* pWnd) function:

	CWnd* SetOwner(CWnd* pWnd);
	// --- In  :	pWnd	-	pointer to the window which will be the recipient 
	//							of all COXSHBDropSource specific messages
	// --- Out : 
	// --- Returns: pointer to the previous recipient window
	// --- Effect : 
  

As long as window is registered as COXSHBDropSource owner and as soon as the drag and 
drop operation has been started our COXSHBDropSource class will send to this window
(we call it recipient window) next messages:

		SHBDSM_GIVEFEEDBACK
		SHBDSM_BEGINDRAG
		SHBDSM_QUERYCONTINUEDRAG

For every message wParam is set to NULL and lParam points to SHBDROPSOURCEACTION 
structure. Return TRUE if you handle the message and FALSE if you want to run the 
default implementation. 

Structure that is used in messages sending from COXSHBDropSource object is defined 
as follows:

typedef struct _tagSHBDROPSOURCEACTION
{
	//
	// Points to the window that contains the selected data.
	CWnd* pWnd;
	//
	// Contains the state of the modifier keys. This is a combination of any number of 
	// the following: 
	//			MK_CONTROL
	//			MK_SHIFT
	//			MK_ALT
	//			MK_LBUTTON
	//			MK_MBUTTON
	//			MK_RBUTTON
	//
	DWORD dwKeyState;
	//
	// Used only with SHBDS_QUERYCONTINUEDRAG and states whether the ESC key has been 
	// pressed since the last time this message was sent.
	BOOL bEscapePressed;
	//
	// The effect you would like to display to the user, usually indicating what 
	// would happen if a drop occurred at this point with the selected data. It can 
	// be one or more of the following:
	//
	//			DROPEFFECT_COPY			A copy operation would be performed.
	//			DROPEFFECT_MOVE			A move operation would be performed.
	//			DROPEFFECT_LINK			A link from the dropped data to the original 
	//									data would be established.
	//			DROPEFFECT_NONE			A drop would not be allowed.
	//			DROPEFFECT_SCROLL		Indicates that a drag scroll operation is about 
	//									to occur or is occurring in the target. 
	//
	DROPEFFECT dropEffect;
	//
	// result of message handling (differ for different messages)
	LRESULT result;

	. . . . . . . . . .  . . 

} SHBDROPSOURCEACTION, * LPSHBDROPSOURCEACTION;


Below you will find detailed description of all messages sent by COXSHBDropSource:


/////////////////////////
	SHBDSM_GIVEFEEDBACK
//
//
// Handle SHBDSM_GIVEFEEDBACK message to provide feedback to the user about what 
// would happen if a drop occurred at this point. The default implementation uses 
// the OLE default cursors. For more information on drag-and-drop operations using 
// OLE, see the article Drag and Drop (OLE) in Visual C++ Programmer's Guide.
// Set result element of SHBDROPSOURCEACTION to the DRAGDROP_S_USEDEFAULTCURSORS if 
// dragging is in progress, NOERROR if it is not. 
// Next elements of SHBDROPSOURCEACTION are filled: dropEffect.

/////////////////////////
	SHBDSM_BEGINDRAG
//
//
// SHBDSM_BEGINDRAG message is sent to the owner window when an event occurs that 
// could begin a drag operation, such as pressing the left mouse button. Handle this 
// message if you want to modify the way the dragging process is started. The default 
// implementation captures the mouse and stays in drag mode until the user clicks the 
// left or right mouse button or hits ESC, at which time it releases the mouse. 
// Set result element of SHBDROPSOURCEACTION to TRUE if dragging is allowed, 
// otherwise FALSE. 
// Next elements of SHBDROPSOURCEACTION are filled: pWnd.

/////////////////////////
	SHBDSM_QUERYCONTINUEDRAG
//
//
// SHBDSM_QUERYCONTINUEDRAG message is sent to the owner window after dragging has 
// begun, this message will be sent repeatedly until the drag operation is either 
// canceled or completed. Handle this message if you want to change the point at 
// which dragging is canceled or a drop occurs. The default implementation initiates 
// the drop or cancels the drag as follows. It cancels a drag operation when the ESC 
// key or the right mouse button is pressed. It initiates a drop operation when the 
// left mouse button is raised after dragging has started. Otherwise, it returns 
// S_OK and performs no further operations. Because this message is called frequently,
// it should be optimized as much as possible.
// Set result element of SHBDROPSOURCEACTION to DRAGDROP_S_CANCEL if the ESC key or 
// right button is pressed, or left button is raised before dragging starts, 
// to DRAGDROP_S_DROP if a drop operation should occur, or otherwise to S_OK.
// Next elements of SHBDROPSOURCEACTION are filled: bEscapePressed, dwKeyState .


You can handle whatever messages you would like to, unhandled messages will be 
handled using default implementation.

*/

class OX_CLASS_DECL COXSHBDropSource : public COleDropSource
{
public:
	// --- In  :
	// --- Out : 
	// --- Returns:
	// --- Effect : Constructor of the object
	COXSHBDropSource() : m_pOwnerWnd(NULL) {};

protected:
	// pointer to the window that owns this object
	CWnd* m_pOwnerWnd;

public:
	// --- In  :	pWnd	-	pointer to the window which will be the recipient 
	//							of all COXSHBDropSource specific messages
	// --- Out : 
	// --- Returns: pointer to the previous recipient window
	// --- Effect : sets recipient window for drop operation
	CWnd* SetOwner(CWnd* pWnd)
	{
		ASSERT(pWnd);
		// owner window (recipient window) must exist at that moment
		ASSERT(::IsWindow(pWnd->GetSafeHwnd()));

		CWnd* pOldWnd=m_pOwnerWnd;
		m_pOwnerWnd=pWnd;

		// return old owner window
		return pOldWnd;
	}


	// --- In  :	
	// --- Out : 
	// --- Returns: pointer to the recipient window
	// --- Effect : retrieves a pointer to the recipient window for drop operation
	inline CWnd* GetOwner() const { return m_pOwnerWnd;	}


	// --- In  :	nMsgID			-	message ID to send to recipient window
	//				pSHBDSAction	-	pointer to SHBDROPSOURCEACTION structure
	// --- Out : 
	// --- Returns:	result of handling of the message
	// --- Effect : Sends COXSHBDropSource specific message to its recipient window
	LRESULT SendSHBDSMessage(UINT nMsgID, LPSHBDROPSOURCEACTION pSHBDSAction)
	{
		ASSERT(m_pOwnerWnd);
		ASSERT(::IsWindow(m_pOwnerWnd->GetSafeHwnd()));
		ASSERT(pSHBDSAction!=NULL);

		// send message to drop target owner window using NMSHBDROPTARGET structure
		// as lParam. Let the owner (recipient) window to handle the message
		return m_pOwnerWnd->SendMessage(nMsgID,(WPARAM)0,(LPARAM)pSHBDSAction);
	}

	// Overrides
	//
	// See DRAG and DROP section of OLE classes reference and 
	// COleDragTarget reference
	//
	virtual SCODE QueryContinueDrag(BOOL bEscapePressed, DWORD dwKeyState)
	{
		ASSERT_VALID(this);

		// send corresponding message to the owner window
		SHBDROPSOURCEACTION SHBDSAction;
		SHBDSAction.bEscapePressed=bEscapePressed;
		SHBDSAction.dwKeyState=dwKeyState;

		if(SendSHBDSMessage(SHBDSM_QUERYCONTINUEDRAG,&SHBDSAction))
			return (SCODE)SHBDSAction.result;

		// Call the base class implementation
		return COleDropSource::QueryContinueDrag(bEscapePressed,dwKeyState);
	}

	virtual SCODE GiveFeedback(DROPEFFECT dropEffect)
	{
		ASSERT_VALID(this);

		// send corresponding message to the owner window
		SHBDROPSOURCEACTION SHBDSAction;
		SHBDSAction.dropEffect=dropEffect;

		if(SendSHBDSMessage(SHBDSM_GIVEFEEDBACK,&SHBDSAction))
			return (SCODE)SHBDSAction.result;

		// Call the base class implementation
		return COleDropSource::GiveFeedback(dropEffect);
	}

	virtual BOOL OnBeginDrag(CWnd* pWnd)
	{
		ASSERT_VALID(this);

		// send corresponding message to the owner window
		SHBDROPSOURCEACTION SHBDSAction;
		SHBDSAction.pWnd=pWnd;

		if(SendSHBDSMessage(SHBDSM_BEGINDRAG,&SHBDSAction))
			return (BOOL)SHBDSAction.result;

		// Call the base class implementation
		return COleDropSource::OnBeginDrag(pWnd);
	}
	//
	////////////////////////////////////////////////////////////////////
};

/////////////////////////////////////////////////////////////////////////////
// COXSHBDropTarget 

/*

COXSHBDropTarget is designed to provide a standard way of handling OLE drag and drop
operation in any window. COXSHBDropTarget is derived from standard COleDropTarget class,
so the only thing you need to do to make it work for you is just to register whatever 
window you need as drop target using COleDropTarget::Register(CWnd* pWnd) function  
(you can do it for example in this window OnCreate function). 

As long as window is registered as drop target and as soon as any OLE object will be 
dragged on that window our COXSHBDropTarget class will send to this window( we call 
it owner window) next messages:

		SHBDTM_DRAGENTER
		SHBDTM_DRAGLEAVE
		SHBDTM_DRAGOVER
		SHBDTM_DRAGSCROLL
		SHBDTM_DROP
		SHBDTM_DROPEX

For every message wParam is set to NULL and lParam points to SHBDROPTARGETACTION 
structure. Return TRUE if you handle the message and FALSE if you want to run the 
default implementation. 

Structure that is used in messages sending from COXSHBDropTarget object is defined 
as follows:

typedef struct _tagSHBDROPTARGETACTION
{
	//
	// Points to the window the cursor is currently over
	CWnd* pWnd;
	//
	// Points to the data object that contains the data to be dropped
	COleDataObject* pDataObject;
	//
	// Contains the state of the modifier keys. This is a combination of any number of 
	// the following: 
	//			MK_CONTROL
	//			MK_SHIFT
	//			MK_ALT
	//			MK_LBUTTON
	//			MK_MBUTTON
	//			MK_RBUTTON
	//
	DWORD dwKeyState;
	//
	// Contains the current location of the cursor in client coordinates.
	CPoint point;
	//
	// The effect that the user chose for the drop operation. It can be one or more of 
	// the following:
	//
	//			DROPEFFECT_COPY			A copy operation would be performed.
	//			DROPEFFECT_MOVE			A move operation would be performed.
	//			DROPEFFECT_LINK			A link from the dropped data to the original 
	//									data would be established.
	//			DROPEFFECT_NONE			A drop would not be allowed.
	//			DROPEFFECT_SCROLL		Indicates that a drag scroll operation is about 
	//									to occur or is occurring in the target. 
	//
	DROPEFFECT dropEffect;
	//
	// A list of the drop effects that the drop source supports. Drop effect values 
	// can be combined using the bitwise OR (|) operation. Drop effects are discussed 
	// above
	DROPEFFECT dropList;
	//
	// result of message handling (differ for different messages)
	LRESULT result;

	. . . . . . . . . . . . . . . . . . . 

} SHBDROPTARGETACTION, * LPSHBDROPTARGETACTION;



Below you will find detailed description of all messages sent by COXSHBDropTarget:


/////////////////////////
	SHBDTM_DRAGENTER
//
//
// Sent to owner window to notify that the cursor is first dragged into the window.
// Set result element of SHBDROPTARGETACTION to the effect that would result if a drop 
// were attempted at the location specified by point element of SHBDROPTARGETACTION. 
// It can be one or more of the following:
//
//		DROPEFFECT_NONE		A drop would not be allowed.
//		DROPEFFECT_COPY		A copy operation would be performed.
//		DROPEFFECT_MOVE		A move operation would be performed.
//		DROPEFFECT_LINK		A link from the dropped data to the original data would 
//							be established.
//		DROPEFFECT_SCROLL   A drag scroll operation is about to occur or is occurring 
//							in the target. 
//
// Next elements of SHBDROPTARGETACTION are filled: pWnd, pDataObject, dwKeyState, point

/////////////////////////
	SHBDTM_DRAGLEAVE
//
//
// Sent to owner window to notify that the cursor leaves the window while a dragging 
// operation is in effect.
// Next elements of SHBDROPTARGETACTION are filled: pWnd

/////////////////////////
	SHBDTM_DRAGOVER
//
//
// Sent to owner window to notify that the cursor is dragged over the window. This 
// message should be handled to allow drop operations to occur in the window. The 
// default implementation returns DROPEFFECT_NONE by default. Because this message is 
// called frequently during a drag-and-drop operation, it should be optimized as much 
// as possible. Set result element of SHBDROPTARGETACTION to the effect that would 
// result if a drop were attempted at the location specified by point element of 
// SHBDROPTARGETACTION. It can be one or more of the following:
//
//		DROPEFFECT_NONE		A drop would not be allowed.
//		DROPEFFECT_COPY		A copy operation would be performed.
//		DROPEFFECT_MOVE		A move operation would be performed.
//		DROPEFFECT_LINK		A link from the dropped data to the original data would 
//							be established.
//		DROPEFFECT_SCROLL   A drag scroll operation is about to occur or is occurring 
//							in the target. 
//
// Next elements of SHBDROPTARGETACTION are filled: pWnd, pDataObject, dwKeyState, point

/////////////////////////
	SHBDTM_DRAGSCROLL
//
//
// Sent to owner window before sending SHBDTM_DRAGENTER or SHBDTM_DRAGOVER messages 
// to determine whether point is in the scrolling region. Handle this message when 
// you want to provide special behavior for this event. The default implementation  
// returns DROPEFFECT_NONE and scrolls the window when the cursor is dragged into the 
// scroll region inside the border of the window. Set result element of 
// SHBDROPTARGETACTION to the effect that would result if a drop were attempted at 
// the location specified by point element of SHBDROPTARGETACTION. It can be one or 
// more of the following:
//
//		DROPEFFECT_NONE		A drop would not be allowed.
//		DROPEFFECT_COPY		A copy operation would be performed.
//		DROPEFFECT_MOVE		A move operation would be performed.
//		DROPEFFECT_LINK		A link from the dropped data to the original data would 
//							be established.
//		DROPEFFECT_SCROLL   A drag scroll operation is about to occur or is occurring 
//							in the target. 
//
// Next elements of SHBDROPTARGETACTION are filled: pWnd, dwKeyState, point.

/////////////////////////
	SHBDTM_DROP
//
//
// Sent to owner window to notify that a drop operation is about to occur. Set result 
// element of SHBDROPTARGETACTION to the TRUE if drop operation was successful or 
// FALSE otherwise.
// Next elements of SHBDROPTARGETACTION are filled: pWnd, pDataObject, point, dropEffect

/////////////////////////
	SHBDTM_DROPEX
//
//
// Sent to owner window to notify that a drop operation is about to occur. This 
// message will be sent before SHBDTM_DROP. If you does not handle it, then 
// SHBDTM_DROP message will be sent. Typically, you will handle SHBDTM_DROPEX in 
// your child window class to support right mouse-button drag and drop. Typically, 
// SHBDTM_DROP message is used to handle the case of support for simple drag and drop.
// By default, we simply return a dummy value to indicate the SHBDTM_DROP message 
// should be sent. Set result element of SHBDROPTARGETACTION to the drop effects that 
// describe the action associated with a drop operation. See the following list of 
// drop effects:
//
//		DROPEFFECT_NONE		A drop would not be allowed.
//		DROPEFFECT_COPY		A copy operation would be performed.
//		DROPEFFECT_MOVE		A move operation would be performed.
//		DROPEFFECT_LINK		A link from the dropped data to the original data would 
//							be established.
//		DROPEFFECT_SCROLL   A drag scroll operation is about to occur or is occurring 
//							in the target. 
//
// Next elements of SHBDROPTARGETACTION are filled: pWnd, pDataObject, point, 
//													dropEffect, dropList.



You can handle whatever messages you would like to, unhandled messages will be 
handled using default implementation.

An example of using of this class can be found in the source code of our COXSHBListCtrl
and COXShortcutBar classes. 

COXSHBListCtrl uses COXSHBDropTarget to provide drag and drop of its items and handle 
next messages: SHBDTM_DRAGENTER, SHBDTM_DRAGLEAVE, SHBDTM_DRAGOVER, SHBDTM_DROP

COXShortcutBar uses COXSHBDropTarget to support any drag and drop operation and handle 
next messages: SHBDTM_DRAGLEAVE, SHBDTM_DRAGOVER


*/

class OX_CLASS_DECL COXSHBDropTarget : public COleDropTarget
{
// Construction
public:
	// --- In  :
	// --- Out : 
	// --- Returns:
	// --- Effect : Constructor of the object
	COXSHBDropTarget() {};  

// Implementation
public:
	// --- In  :
	// --- Out : 
	// --- Returns:
	// --- Effect : Destructor of object
	virtual ~COXSHBDropTarget() {};


	// --- In  :	nMsgID			-	message ID to send to owner window
	//				pSHBDTAction	-	pointer to SHBDROPTARGETACTION structure
	// --- Out : 
	// --- Returns:	result of handling of the message
	// --- Effect : Sends COXSHBDropTarget specific message to its owner window
	LRESULT SendSHBDTMessage(UINT nMsgID, LPSHBDROPTARGETACTION pSHBDTAction)
	{
		ASSERT(pSHBDTAction->pWnd);
		ASSERT(::IsWindow(pSHBDTAction->pWnd->GetSafeHwnd()));
		ASSERT(pSHBDTAction!=NULL);

		// send message to the pSHBDTAction->pWnd window which is registered as drop 
		// target using NMSHBDROPTARGET structure as lParam. 
		return pSHBDTAction->pWnd->SendMessage(nMsgID,(WPARAM)0,(LPARAM)pSHBDTAction);
	}


// Overridables

	//
	// These members can be overridden for an OLE drop target
	// See DRAG and DROP section of OLE classes reference and COleDragTarget reference
	//
	virtual DROPEFFECT OnDragScroll(CWnd* pWnd, DWORD dwKeyState, CPoint point)
	{
		ASSERT_VALID(this);

		// notify pWnd about DragScroll event
		SHBDROPTARGETACTION SHBDTAction;
		SHBDTAction.pWnd=pWnd;
		SHBDTAction.dwKeyState=dwKeyState;
		SHBDTAction.point=point;

		SendSHBDTMessage(SHBDTM_DRAGSCROLL,&SHBDTAction);

		// DROPEFFECT_SCROLL means do the default
		if((DROPEFFECT)SHBDTAction.result!=DROPEFFECT_SCROLL)
		{
			return (DROPEFFECT)SHBDTAction.result;
		}

		if(pWnd->IsKindOf(RUNTIME_CLASS(CView)))
		{
			return COleDropTarget::OnDragScroll(pWnd,dwKeyState,point);
		}

		// get client rectangle of destination window
		CRect rectClient;
		pWnd->GetClientRect(&rectClient);
		CRect rect=rectClient;

		// hit-test against inset region
		UINT nTimerID=MAKEWORD(-1, -1);
		rect.InflateRect(-nScrollInset, -nScrollInset);
		if(rectClient.PtInRect(point) && !rect.PtInRect(point))
		{
			// check if need to scroll
			BOOL bHasScrollHorz=((pWnd->GetStyle()&WS_HSCROLL)==WS_HSCROLL);
			BOOL bHasScrollVert=((pWnd->GetStyle()&WS_VSCROLL)==WS_VSCROLL);
			SCROLLINFO scrollInfo={ sizeof(SCROLLINFO) };
			
			if(pWnd->GetScrollInfo(SB_HORZ,&scrollInfo))
			{
				if(bHasScrollHorz)
				{
					if(scrollInfo.nMax==0 || scrollInfo.nPage==0 || 
						scrollInfo.nMax<(int)scrollInfo.nPage)
					{
						bHasScrollHorz=FALSE;
					}
				}
				else
				{
					if(scrollInfo.nMax>0 && scrollInfo.nPage>0 &&
						scrollInfo.nMax>=(int)scrollInfo.nPage)
					{
						bHasScrollHorz=TRUE;
					}
				}
			}

			if(pWnd->GetScrollInfo(SB_VERT,&scrollInfo))
			{
				if(bHasScrollVert)
				{
					if(scrollInfo.nMax==0 || scrollInfo.nPage==0 || 
						scrollInfo.nMax<(int)scrollInfo.nPage)
					{
						bHasScrollVert=FALSE;
					}
				}
				else
				{
					if(scrollInfo.nMax>0 && scrollInfo.nPage>0 &&
						scrollInfo.nMax>=(int)scrollInfo.nPage)
					{
						bHasScrollVert=TRUE;
					}
				}
			}
		
			// determine which way to scroll along both X & Y axis
			if(bHasScrollHorz && point.x<rect.left)
			{
				nTimerID=MAKEWORD(LOBYTE(nTimerID),SB_LINEUP);
			}
			else if(bHasScrollHorz && point.x>=rect.right)
			{
				nTimerID=MAKEWORD(LOBYTE(nTimerID), SB_LINEDOWN);
			}
			if(bHasScrollVert && point.y<rect.top)
			{
				nTimerID=MAKEWORD(SB_LINEUP,HIBYTE(nTimerID));
			}
			else if(bHasScrollVert && point.y>=rect.bottom)
			{
				nTimerID=MAKEWORD(SB_LINEDOWN,HIBYTE(nTimerID));
			}
		}

		if(nTimerID==MAKEWORD(-1,-1))
		{
			if(m_nTimerID!=MAKEWORD(-1,-1))
			{
				// send fake OnDragEnter when transition from scroll->normal
				COleDataObject dataObject;
				dataObject.Attach(m_lpDataObject,FALSE);
				OnDragEnter(pWnd,&dataObject,dwKeyState,point);
				m_nTimerID=MAKEWORD(-1,-1);
			}
			return DROPEFFECT_NONE;
		}

		// save tick count when timer ID changes
		DWORD dwTick=GetTickCount();
		if(nTimerID!=m_nTimerID)
		{
			m_dwLastTick=dwTick;
			m_nScrollDelay=nScrollDelay;
		}

		// scroll if necessary
		if((dwTick-m_dwLastTick)>m_nScrollDelay)
		{
			BOOL bScrollHorz=(LOBYTE(nTimerID)==-1);
			if(bScrollHorz)
			{
				pWnd->SendMessage(
					WM_HSCROLL,MAKEWPARAM(HIBYTE(nTimerID),0),(LPARAM)NULL);
			}
			else
			{
				pWnd->SendMessage(
					WM_VSCROLL,MAKEWPARAM(LOBYTE(nTimerID),0),(LPARAM)NULL);
			}
			m_dwLastTick=dwTick;
			m_nScrollDelay=nScrollInterval;
		}
		if (m_nTimerID == MAKEWORD(-1, -1))
		{
			// send fake OnDragLeave when transitioning from normal->scroll
			OnDragLeave(pWnd);
		}

		m_nTimerID=nTimerID;
		// check for force link
		if((SHBDTAction.dwKeyState & (MK_CONTROL|MK_SHIFT))==(MK_CONTROL|MK_SHIFT))
		{
			SHBDTAction.result=(LRESULT)(DROPEFFECT_SCROLL|DROPEFFECT_LINK);
		}
		// check for force copy
		else if((SHBDTAction.dwKeyState & MK_CONTROL)==MK_CONTROL)
		{
			SHBDTAction.result=(LRESULT)(DROPEFFECT_SCROLL|DROPEFFECT_COPY);
		}
		// check for force move
		else if((SHBDTAction.dwKeyState & MK_ALT)==MK_ALT ||
			(SHBDTAction.dwKeyState & MK_SHIFT)==MK_SHIFT)
		{
			SHBDTAction.result=(LRESULT)(DROPEFFECT_SCROLL|DROPEFFECT_MOVE);
		}
		// default
		else
		{
			SHBDTAction.result=(LRESULT)(DROPEFFECT_SCROLL|DROPEFFECT_NONE);
		}

		return (DROPEFFECT)SHBDTAction.result;
	}


	virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, 
		DWORD dwKeyState, CPoint point)
	{   
		ASSERT_VALID(this);

		// notify pWnd about DragEnter event
		SHBDROPTARGETACTION SHBDTAction;
		SHBDTAction.pWnd=pWnd;
		SHBDTAction.pDataObject=pDataObject;
		SHBDTAction.dwKeyState=dwKeyState;
		SHBDTAction.point=point;
		SHBDTAction.dropEffect=DROPEFFECT_NONE;

		if(SendSHBDTMessage(SHBDTM_DRAGENTER,&SHBDTAction))
			return (DROPEFFECT)SHBDTAction.result;

		// default implementation
		return DROPEFFECT_NONE;
	} 


	virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, 
		DWORD dwKeyState, CPoint point)
	{
		ASSERT_VALID(this);

		// notify pWnd about DragOver event
		SHBDROPTARGETACTION SHBDTAction;
		SHBDTAction.pWnd=pWnd;
		SHBDTAction.pDataObject=pDataObject;
		SHBDTAction.dwKeyState=dwKeyState;
		SHBDTAction.point=point;
		SHBDTAction.dropEffect=DROPEFFECT_NONE;

		if(SendSHBDTMessage(SHBDTM_DRAGOVER,&SHBDTAction))
			return (DROPEFFECT)SHBDTAction.result;

		// default implementation
		return DROPEFFECT_NONE;
	}


	virtual void OnDragLeave(CWnd* pWnd)
	{
		ASSERT_VALID(this);

		// notify pWnd about DragLeave event
		SHBDROPTARGETACTION SHBDTAction;
		SHBDTAction.pWnd=pWnd;

		if(SendSHBDTMessage(SHBDTM_DRAGLEAVE,&SHBDTAction))
			return;

		// Call base class implementation
		COleDropTarget::OnDragLeave(pWnd);
	}


	virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject, 
		DROPEFFECT dropEffect, CPoint point)
	{ 
		ASSERT_VALID(this);

		// notify pWnd about Drop event
		SHBDROPTARGETACTION SHBDTAction;
		SHBDTAction.pWnd=pWnd;
		SHBDTAction.pDataObject=pDataObject;
		SHBDTAction.point=point;
		SHBDTAction.dropEffect=dropEffect;

		if(SendSHBDTMessage(SHBDTM_DROP,&SHBDTAction))
			return (BOOL)SHBDTAction.result;

		// default implementation
		return FALSE;
	}

	virtual DROPEFFECT OnDropEx(CWnd* pWnd, COleDataObject* pDataObject, 
		DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point)
	{
		ASSERT_VALID(this);

		// notify pWnd about DropEx event
		SHBDROPTARGETACTION SHBDTAction;
		SHBDTAction.pWnd=pWnd;
		SHBDTAction.pDataObject=pDataObject;
		SHBDTAction.point=point;
		SHBDTAction.dropEffect=dropDefault;
		SHBDTAction.dropList=dropList;

		if(SendSHBDTMessage(SHBDTM_DROPEX,&SHBDTAction))
			return (DROPEFFECT)SHBDTAction.result;

		// Call base class implementation
		return COleDropTarget::OnDropEx(pWnd,pDataObject,dropDefault,dropList,point);
	}
	//
	//////////////////////////////////////////////////
};


/////////////////////////////////////////////////////////////////////////////
// COXBaseDragDropWnd window

template<class PARENTWND>
class OX_CLASS_DECL COXBaseDragDropWnd : public PARENTWND
{
// Construction
public:
	COXBaseDragDropWnd();

// Attributes
protected:
	// default COleDropSource for drag'n'drop operation
	COXSHBDropSource m_oleDropSource;
	// default COleDropTarget for drag'n'drop operation
	COXSHBDropTarget m_oleDropTarget;
	// flag that specifies if any drag and drop operation is undergoing
	BOOL m_bDragDropOperation;
	// flag that specifies whether this object launched current drag'n'drop 
	// operation or not
	BOOL m_bDragDropOwner;


// Operations
public:
	// --- In  :	
	// --- Out : 
	// --- Returns:	A pointer to internal COleDropSource object
	// --- Effect : Retrieves a pointer to internal COleDropSource object that will
	//				allow this object to handle drag'n'drop operation
	virtual COleDropSource* GetDropSource() 
	{ 
		// owner window must exist at that moment
		ASSERT(::IsWindow(GetSafeHwnd()));
		m_oleDropSource.SetOwner(this);
		return &m_oleDropSource; 
	}

	// --- In  :	
	// --- Out : 
	// --- Returns:	TRUE if this object has started current drag'n'drop operation;
	//				otherwise FALSE
	// --- Effect : Retrieves the flag that specifies whether this object has 
	//				started current drag'n'drop operation 
	inline BOOL IsDragDropOwner() const { return m_bDragDropOwner; }

	// --- In  :	
	// --- Out : 
	// --- Returns:	A pointer to internal COleDropTarget object
	// --- Effect : Retrieves a pointer to internal COleDropTarget object that will
	//				allow this object to handle drag'n'drop operation
	virtual COleDropTarget* GetDropTarget() { return &m_oleDropTarget; }


	// registers control as drop target
	virtual void RegisterAsDropTarget();


protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXBaseDragDropWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COXBaseDragDropWnd();

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	// drag and drop support
	virtual LONG OnDragScroll(WPARAM wParam, LPARAM lParam);
	virtual LONG OnDragEnter(WPARAM wParam, LPARAM lParam);
	virtual LONG OnDragOver(WPARAM wParam, LPARAM lParam);
	virtual LONG OnDragLeave(WPARAM wParam, LPARAM lParam);
	virtual LONG OnDrop(WPARAM wParam, LPARAM lParam);

	// drop files support
	virtual void OnDropFiles(HDROP hDropInfo);
};

////////////////////////////////////////////////////////////////////////////

template<class PARENTWND> 
COXBaseDragDropWnd<PARENTWND>::COXBaseDragDropWnd() : 
	m_bDragDropOperation(FALSE),
	m_bDragDropOwner(FALSE)
{
	// has to be derived from CWnd or its derivates
	if(!IsKindOf(RUNTIME_CLASS(CWnd)))
	{
		TRACE(_T("COXBaseDragDropWnd has to be derived from CWnd or its derivates\n"));
		AfxThrowNotSupportedException();
	}
}


template<class PARENTWND> 
COXBaseDragDropWnd<PARENTWND>::~COXBaseDragDropWnd()
{
}


template<class PARENTWND> 
LRESULT COXBaseDragDropWnd<PARENTWND>::WindowProc(UINT message, 
												  WPARAM wParam, 
												  LPARAM lParam)
{
#if defined (_WINDLL)
#if defined (_AFXDLL)
	AFX_MANAGE_STATE(AfxGetAppModuleState());
#else
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
#endif

	LRESULT lResult=0;
	
	switch(message)
	{
	case SHBDTM_DRAGSCROLL:
		{
			lResult=OnDragScroll(wParam,lParam);
		}
		break;

	case SHBDTM_DRAGENTER:
		{
			// set flag that specifies that drag'n'drop operation is active
			m_bDragDropOperation=TRUE;
			lResult=OnDragEnter(wParam,lParam);
		}
		break;

	case SHBDTM_DRAGLEAVE:
		{
			lResult=OnDragLeave(wParam,lParam);
			// reset flag that specifies that drag'n'drop operation is active
			m_bDragDropOperation=FALSE;
		}
		break;

	case SHBDTM_DRAGOVER:
		{
			lResult=OnDragOver(wParam,lParam);
		}
		break;

	case SHBDTM_DROP:
		{
			lResult=OnDrop(wParam,lParam);
			if(!IsDragDropOwner())
			{
				// reset flag that specifies that drag'n'drop operation is active
				m_bDragDropOperation=FALSE;
			}
		}
		break;

	case WM_DROPFILES:
		{
			OnDropFiles((HDROP)wParam);
			lResult=0;
		}
		break;

	default:
		{
			lResult=PARENTWND::WindowProc(message,wParam,lParam);
		}
		break;
	}

	return lResult;
}


template<class PARENTWND> 
LONG COXBaseDragDropWnd<PARENTWND>::OnDragScroll(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	return FALSE;
}


template<class PARENTWND> 
LONG COXBaseDragDropWnd<PARENTWND>::OnDragEnter(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	return FALSE;
}


template<class PARENTWND> 
LONG COXBaseDragDropWnd<PARENTWND>::OnDragOver(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	return FALSE;
}


template<class PARENTWND> 
LONG COXBaseDragDropWnd<PARENTWND>::OnDragLeave(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	return FALSE;
}


template<class PARENTWND> 
LONG COXBaseDragDropWnd<PARENTWND>::OnDrop(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	return FALSE;
}


template<class PARENTWND> 
void COXBaseDragDropWnd<PARENTWND>::RegisterAsDropTarget()
{
	COleDropTarget* pOleDropTarget=GetDropTarget();
	ASSERT(pOleDropTarget!=NULL);
	if(!pOleDropTarget->Register(this))
	{
		TRACE(_T("COXBaseDragDropWnd::RegisterAsDropTarget: failed to register with COleDropTarget object. You've probably forgotten to initialize OLE libraries using AfxOleInit() function\n"));
	}
}


template<class PARENTWND> 
void COXBaseDragDropWnd<PARENTWND>::OnDropFiles(HDROP hDropInfo)
{
	UNREFERENCED_PARAMETER(hDropInfo);
}


/////////////////////////////////////////////////////////////////////


#ifndef OXDROPDOWNTREE_AUTOEXPAND_TIMER_ID
#define OXDROPDOWNTREE_AUTOEXPAND_TIMER_ID				238
#endif
#ifndef OXDROPDOWNTREE_AUTOEXPAND_TIMER_DELAY
#define OXDROPDOWNTREE_AUTOEXPAND_TIMER_DELAY			1500
#endif

/////////////////////////////////////////////////////////////////////////////
// COXBaseDragDropTree window

template<class PARENTTREE>
class OX_CLASS_DECL COXBaseDragDropTree : public COXBaseDragDropWnd<PARENTTREE>
{
// Construction
public:
	COXBaseDragDropTree();

// Attributes
protected:
	// timer id for autoexpansion as a result of drag'n'drop operation
	UINT m_nAutoExpandTimer;

// Operations
protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXBaseDragDropTree)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COXBaseDragDropTree();

protected:
	// drag and drop support
	virtual LONG OnDragScroll(WPARAM wParam, LPARAM lParam);
	virtual LONG OnDragEnter(WPARAM wParam, LPARAM lParam);
	virtual LONG OnDragOver(WPARAM wParam, LPARAM lParam);
	virtual LONG OnDragLeave(WPARAM wParam, LPARAM lParam);
	virtual LONG OnDrop(WPARAM wParam, LPARAM lParam);

	// drop files support
	virtual void OnDropFiles(HDROP hDropInfo);

	// drop overridables
	virtual BOOL CanAcceptDrop(HTREEITEM hItem, HTREEITEM hParentItem, 
		BOOL bDropAfter, LPSHBDROPTARGETACTION pSHBDTAction);
	virtual void AcceptDrop(HTREEITEM hItem, HTREEITEM hParentItem, 
		BOOL bDropAfter, LPSHBDROPTARGETACTION pSHBDTAction);
	virtual BOOL CanAcceptDropFiles(HTREEITEM hItem, HTREEITEM hParentItem, 
		BOOL bDropAfter, HDROP hDropInfo);
	virtual void AcceptDropFiles(HTREEITEM hItem, HTREEITEM hParentItem, 
		BOOL bDropAfter, HDROP hDropInfo);

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};


////////////////////////////////////////////////////////////////////////////

template<class PARENTTREE> 
COXBaseDragDropTree<PARENTTREE>::COXBaseDragDropTree() : 
	m_nAutoExpandTimer(0)
{
}


template<class PARENTTREE> 
COXBaseDragDropTree<PARENTTREE>::~COXBaseDragDropTree()
{
}


template<class PARENTTREE> 
LRESULT COXBaseDragDropTree<PARENTTREE>::WindowProc(UINT message, 
													WPARAM wParam, 
													LPARAM lParam)
{
#if defined (_WINDLL)
#if defined (_AFXDLL)
	AFX_MANAGE_STATE(AfxGetAppModuleState());
#else
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif
#endif

	LRESULT lResult=0;
	
	switch(message)
	{
	case WM_TIMER:
		{
			if(wParam==m_nAutoExpandTimer)
			{
				HTREEITEM hDropItem=GetDropHilightItem();
				if(hDropItem!=NULL)
				{
					// check if mouse is still over the drop highlighted item
					CPoint ptMouse;
					::GetCursorPos(&ptMouse);
					ScreenToClient(&ptMouse);
					UINT uiFlags=0;
					HTREEITEM hHitTestItem=HitTest(ptMouse,&uiFlags);
					if(hHitTestItem==hDropItem && (uiFlags & TVHT_ONITEM ))
					{
						// reset timer
						VERIFY(KillTimer(m_nAutoExpandTimer));
						m_nAutoExpandTimer=0;
						// expand node
						VERIFY(Expand(hDropItem,TVE_EXPAND));
					}
				}
				lResult=0;
			}
			else
			{
				lResult=COXBaseDragDropWnd<PARENTTREE>::WindowProc(
					message,wParam,lParam);
			}
		}
		break;

	default:
		{
			lResult=COXBaseDragDropWnd<PARENTTREE>::WindowProc(message,wParam,lParam);
		}
		break;
	}

	return lResult;
}


template<class PARENTTREE> 
LONG COXBaseDragDropTree<PARENTTREE>::OnDragScroll(WPARAM wParam, LPARAM lParam)
{
	if(COXBaseDragDropWnd<PARENTTREE>::OnDragScroll(wParam,lParam))
	{
		return TRUE;
	}

	// lParam is the pointer to SHBDROPTARGETACTION structure
	LPSHBDROPTARGETACTION pSHBDTAction=(LPSHBDROPTARGETACTION)lParam;
	ASSERT(pSHBDTAction!=NULL);

	ASSERT(pSHBDTAction->pWnd);
	ASSERT(pSHBDTAction->pWnd->GetSafeHwnd()==GetSafeHwnd());

	pSHBDTAction->result=(LRESULT)DROPEFFECT_SCROLL;

	return TRUE;
}


template<class PARENTTREE> 
LONG COXBaseDragDropTree<PARENTTREE>::OnDragEnter(WPARAM wParam, LPARAM lParam)
{
	if(COXBaseDragDropWnd<PARENTTREE>::OnDragEnter(wParam,lParam))
	{
		return TRUE;
	}

	return OnDragOver(wParam,lParam);
}


template<class PARENTTREE> 
LONG COXBaseDragDropTree<PARENTTREE>::OnDragOver(WPARAM wParam, LPARAM lParam)
{
	if(COXBaseDragDropWnd<PARENTTREE>::OnDragOver(wParam,lParam))
	{
		return TRUE;
	}

	// lParam is the pointer to SHBDROPTARGETACTION structure
	LPSHBDROPTARGETACTION pSHBDTAction=(LPSHBDROPTARGETACTION)lParam;
	ASSERT(pSHBDTAction!=NULL);

	ASSERT(pSHBDTAction->pWnd);
	ASSERT(pSHBDTAction->pWnd->GetSafeHwnd()==GetSafeHwnd());

	// Check if the control key was pressed          
	if((pSHBDTAction->dwKeyState & MK_CONTROL)==MK_CONTROL)
	{
		pSHBDTAction->result=(LRESULT)DROPEFFECT_COPY;
	}
	else
	{
		pSHBDTAction->result=(LRESULT)DROPEFFECT_MOVE; 
	}

	BOOL bAcceptDrop=FALSE;

	UINT uFlags=0;
	// get the item that is below cursor
	HTREEITEM hDropItem=HitTest(pSHBDTAction->point,&uFlags);
	if(hDropItem!=NULL)
	{
		HTREEITEM hOldDropItem=GetDropHilightItem();
		if(hOldDropItem!=hDropItem)
		{
			// reset the timer for autoexpansion
			if(m_nAutoExpandTimer!=0)
			{
				KillTimer(m_nAutoExpandTimer);
				m_nAutoExpandTimer=0;
			}

			// highlight it
			SelectDropTarget(hDropItem);

			if((GetItemState(hDropItem,TVIS_EXPANDED) & TVIS_EXPANDED)==0 &&
				ItemHasChildren(hDropItem))
			{
				m_nAutoExpandTimer=SetTimer(OXDROPDOWNTREE_AUTOEXPAND_TIMER_ID,
					OXDROPDOWNTREE_AUTOEXPAND_TIMER_DELAY,NULL);
				ASSERT(m_nAutoExpandTimer==OXDROPDOWNTREE_AUTOEXPAND_TIMER_ID);
			}
		}

		// check if this item accepts drop operation
		HTREEITEM hParentItem=GetParentItem(hDropItem);
		CRect rectItem;
		GetItemRect(hDropItem,rectItem,FALSE);
		bAcceptDrop=CanAcceptDrop(hDropItem,hParentItem,
			(pSHBDTAction->point.y > rectItem.top+rectItem.Height()/2),pSHBDTAction);
	} 
	else 
	{ 
		// no item to drop on, ask root item to insert as last child
		bAcceptDrop=CanAcceptDrop(TVI_LAST,TVI_ROOT,TRUE,pSHBDTAction);
	}

	if(!bAcceptDrop)
	{
		pSHBDTAction->result=(LRESULT)DROPEFFECT_NONE;
	}

	return bAcceptDrop;
}


template<class PARENTTREE> 
LONG COXBaseDragDropTree<PARENTTREE>::OnDragLeave(WPARAM wParam, LPARAM lParam)
{
	if(COXBaseDragDropWnd<PARENTTREE>::OnDragLeave(wParam,lParam))
	{
		return TRUE;
	}

	SelectDropTarget(NULL);

	return TRUE;
}


template<class PARENTTREE> 
LONG COXBaseDragDropTree<PARENTTREE>::OnDrop(WPARAM wParam, LPARAM lParam)
{
	if(COXBaseDragDropWnd<PARENTTREE>::OnDrop(wParam,lParam))
	{
		return TRUE;
	}

	// lParam is the pointer to SHBDROPTARGETACTION structure
	LPSHBDROPTARGETACTION pSHBDTAction=(LPSHBDROPTARGETACTION)lParam;
	ASSERT(pSHBDTAction!=NULL);

	ASSERT(pSHBDTAction->pWnd);
	ASSERT(pSHBDTAction->pWnd->GetSafeHwnd()==GetSafeHwnd());

	pSHBDTAction->result=(LRESULT)FALSE;

	// if dragged item is to be copied or moved
	if((pSHBDTAction->dropEffect&DROPEFFECT_COPY)!=0 || 
		(pSHBDTAction->dropEffect&DROPEFFECT_MOVE)!=0)
	{
		UINT uFlags=0;
		HTREEITEM hDropItem=HitTest(pSHBDTAction->point,&uFlags);
		if(hDropItem!=NULL)
		{
			ASSERT(hDropItem==GetDropHilightItem());

			// remove highlight
			SelectDropTarget(NULL);

			// check if this item accepts drop operation
			HTREEITEM hParentItem=GetParentItem(hDropItem);
			CRect rectItem;
			GetItemRect(hDropItem,rectItem,FALSE);
			if(CanAcceptDrop(hDropItem,hParentItem,
				(pSHBDTAction->point.y > rectItem.top+rectItem.Height()/2),
				pSHBDTAction))
			{
				AcceptDrop(hDropItem,hParentItem,
					(pSHBDTAction->point.y > rectItem.top+rectItem.Height()/2),
					pSHBDTAction);
			}
		}
		else
		{
			// no item to drop on, ask root item to insert as last child
			if(CanAcceptDrop(TVI_LAST,TVI_ROOT,TRUE,pSHBDTAction))
			{
				AcceptDrop(TVI_LAST,TVI_ROOT,TRUE,pSHBDTAction);
			}
		}
	}

	return TRUE;
}


template<class PARENTTREE> 
void COXBaseDragDropTree<PARENTTREE>::OnDropFiles(HDROP hDropInfo)
{
	// retrieve number of files
	UINT nFileCount=::DragQueryFile(hDropInfo,(UINT)-1,NULL,0);

	if(nFileCount>0)
	{
		CPoint ptDrop;
		if(::DragQueryPoint(hDropInfo,&ptDrop))
		{
			// analyze drop position
			UINT uFlags=0;
			HTREEITEM hDropItem=HitTest(ptDrop,&uFlags);
			if(hDropItem!=NULL)
			{
				// check if this item accepts drop operation
				HTREEITEM hParentItem=GetParentItem(hDropItem);
				CRect rectItem;
				GetItemRect(hDropItem,rectItem,FALSE);
				if(CanAcceptDropFiles(hDropItem,hParentItem,
					(ptDrop.y > rectItem.top+rectItem.Height()/2),hDropInfo))
				{
					AcceptDropFiles(hDropItem,hParentItem,
						(ptDrop.y > rectItem.top+rectItem.Height()/2),hDropInfo);
				}
			} 
			else
			{
				// no item to drop on, ask root item to insert as last child
				if(CanAcceptDropFiles(TVI_LAST,TVI_ROOT,TRUE,hDropInfo))
				{
					AcceptDropFiles(TVI_LAST,TVI_ROOT,TRUE,hDropInfo);
				}
			}
		}
	}

	::DragFinish(hDropInfo);
}


template<class PARENTTREE> 
BOOL COXBaseDragDropTree<PARENTTREE>::CanAcceptDrop(HTREEITEM hItem, 
													HTREEITEM hParentItem, 
													BOOL bDropAfter, 
													LPSHBDROPTARGETACTION pSHBDTAction)
{
	UNREFERENCED_PARAMETER(hItem);
	UNREFERENCED_PARAMETER(hParentItem);
	UNREFERENCED_PARAMETER(bDropAfter);
	UNREFERENCED_PARAMETER(pSHBDTAction);
	
	return FALSE;
}


template<class PARENTTREE> 
void COXBaseDragDropTree<PARENTTREE>::AcceptDrop(HTREEITEM hItem, 
												 HTREEITEM hParentItem, 
												 BOOL bDropAfter, 
												 LPSHBDROPTARGETACTION pSHBDTAction)
{
	UNREFERENCED_PARAMETER(hItem);
	UNREFERENCED_PARAMETER(hParentItem);
	UNREFERENCED_PARAMETER(bDropAfter);
	UNREFERENCED_PARAMETER(pSHBDTAction);
}


template<class PARENTTREE> 
BOOL COXBaseDragDropTree<PARENTTREE>::CanAcceptDropFiles(HTREEITEM hItem, 
														 HTREEITEM hParentItem, 
														 BOOL bDropAfter, 
														 HDROP hDropInfo)
{
	UNREFERENCED_PARAMETER(hItem);
	UNREFERENCED_PARAMETER(hParentItem);
	UNREFERENCED_PARAMETER(bDropAfter);
	UNREFERENCED_PARAMETER(hDropInfo);
	
	return FALSE;
}


template<class PARENTTREE> 
void COXBaseDragDropTree<PARENTTREE>::AcceptDropFiles(HTREEITEM hItem, 
													  HTREEITEM hParentItem, 
													  BOOL bDropAfter, 
													  HDROP hDropInfo)
{
	UNREFERENCED_PARAMETER(hItem);
	UNREFERENCED_PARAMETER(hParentItem);
	UNREFERENCED_PARAMETER(bDropAfter);
	UNREFERENCED_PARAMETER(hDropInfo);
}


//////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// COXBaseDragDropList window

template<class PARENTLIST>
class OX_CLASS_DECL COXBaseDragDropList : public COXBaseDragDropWnd<PARENTLIST>
{
// Construction
public:
	COXBaseDragDropList();

// Attributes
protected:

// Operations
protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXBaseDragDropList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COXBaseDragDropList();

protected:
	// drag and drop support
	virtual LONG OnDragScroll(WPARAM wParam, LPARAM lParam);
	virtual LONG OnDragEnter(WPARAM wParam, LPARAM lParam);
	virtual LONG OnDragOver(WPARAM wParam, LPARAM lParam);
	virtual LONG OnDragLeave(WPARAM wParam, LPARAM lParam);
	virtual LONG OnDrop(WPARAM wParam, LPARAM lParam);

	// drop files support
	virtual void OnDropFiles(HDROP hDropInfo);

	// drop overridables
	virtual BOOL CanAcceptDrop(
		int nItemIndex, BOOL bDropAfter, LPSHBDROPTARGETACTION pSHBDTAction);
	virtual void AcceptDrop(
		int nItemIndex, BOOL bDropAfter, LPSHBDROPTARGETACTION pSHBDTAction);
	virtual BOOL CanAcceptDropFiles(
		int nItemIndex, BOOL bDropAfter, HDROP hDropInfo);
	virtual void AcceptDropFiles(
		int nItemIndex, BOOL bDropAfter, HDROP hDropInfo);
};


////////////////////////////////////////////////////////////////////////////

template<class PARENTLIST> 
COXBaseDragDropList<PARENTLIST>::COXBaseDragDropList()
{
}


template<class PARENTLIST> 
COXBaseDragDropList<PARENTLIST>::~COXBaseDragDropList()
{
}


template<class PARENTLIST> 
LONG COXBaseDragDropList<PARENTLIST>::OnDragScroll(WPARAM wParam, LPARAM lParam)
{
	if(COXBaseDragDropWnd<PARENTLIST>::OnDragScroll(wParam,lParam))
	{
		return TRUE;
	}

	// lParam is the pointer to SHBDROPTARGETACTION structure
	LPSHBDROPTARGETACTION pSHBDTAction=(LPSHBDROPTARGETACTION)lParam;
	ASSERT(pSHBDTAction!=NULL);

	ASSERT(pSHBDTAction->pWnd);
	ASSERT(pSHBDTAction->pWnd->GetSafeHwnd()==GetSafeHwnd());

	pSHBDTAction->result=(LRESULT)DROPEFFECT_SCROLL;

	return TRUE;
}


template<class PARENTLIST> 
LONG COXBaseDragDropList<PARENTLIST>::OnDragEnter(WPARAM wParam, LPARAM lParam)
{
	if(COXBaseDragDropWnd<PARENTLIST>::OnDragEnter(wParam,lParam))
	{
		return TRUE;
	}

	return OnDragOver(wParam,lParam);
}


template<class PARENTLIST> 
LONG COXBaseDragDropList<PARENTLIST>::OnDragOver(WPARAM wParam, LPARAM lParam)
{
	if(COXBaseDragDropWnd<PARENTLIST>::OnDragOver(wParam,lParam))
	{
		return TRUE;
	}

	// lParam is the pointer to SHBDROPTARGETACTION structure
	LPSHBDROPTARGETACTION pSHBDTAction=(LPSHBDROPTARGETACTION)lParam;
	ASSERT(pSHBDTAction!=NULL);

	ASSERT(pSHBDTAction->pWnd);
	ASSERT(pSHBDTAction->pWnd->GetSafeHwnd()==GetSafeHwnd());

	// Check if the control key was pressed          
	if((pSHBDTAction->dwKeyState & MK_CONTROL)==MK_CONTROL)
	{
		pSHBDTAction->result=(LRESULT)DROPEFFECT_COPY;
	}
	else
	{
		pSHBDTAction->result=(LRESULT)DROPEFFECT_MOVE; 
	}

	BOOL bAcceptDrop=FALSE;

	UINT uFlags=0;
	// get the item that is below cursor
	int nItemIndex=HitTest(pSHBDTAction->point,&uFlags);
	if(nItemIndex!=-1)
	{
		int nDropItemIndex=GetNextItem(-1,LVNI_DROPHILITED);
		if(nDropItemIndex!=nItemIndex)
		{
			SetItemState(nDropItemIndex,0,LVIS_DROPHILITED);
			SetItemState(nItemIndex,LVIS_DROPHILITED,LVIS_DROPHILITED);
		}

		CRect rectItem;
		GetItemRect(nItemIndex,rectItem,LVIR_BOUNDS);
		bAcceptDrop=CanAcceptDrop(nItemIndex,
			(pSHBDTAction->point.y > rectItem.top+rectItem.Height()/2),pSHBDTAction);
	} 
	else 
	{ 
		// no item to drop on, ask to insert as last item
		bAcceptDrop=CanAcceptDrop(GetItemCount(),FALSE,pSHBDTAction);
	}

	if(!bAcceptDrop)
	{
		pSHBDTAction->result=(LRESULT)DROPEFFECT_NONE;
	}

	return bAcceptDrop;
}


template<class PARENTLIST> 
LONG COXBaseDragDropList<PARENTLIST>::OnDragLeave(WPARAM wParam, LPARAM lParam)
{
	if(COXBaseDragDropWnd<PARENTLIST>::OnDragLeave(wParam,lParam))
	{
		return TRUE;
	}

	int nDropItemIndex=GetNextItem(-1,LVNI_DROPHILITED);
	if(nDropItemIndex!=-1)
	{
		// remove highlight
		SetItemState(nDropItemIndex,0,LVIS_DROPHILITED);
	}

	return TRUE;
}


template<class PARENTLIST> 
LONG COXBaseDragDropList<PARENTLIST>::OnDrop(WPARAM wParam, LPARAM lParam)
{
	if(COXBaseDragDropWnd<PARENTLIST>::OnDrop(wParam,lParam))
	{
		return TRUE;
	}

	// lParam is the pointer to SHBDROPTARGETACTION structure
	LPSHBDROPTARGETACTION pSHBDTAction=(LPSHBDROPTARGETACTION)lParam;
	ASSERT(pSHBDTAction!=NULL);

	ASSERT(pSHBDTAction->pWnd);
	ASSERT(pSHBDTAction->pWnd->GetSafeHwnd()==GetSafeHwnd());

	pSHBDTAction->result=(LRESULT)FALSE;

	// if dragged item is to be copied or moved
	if((pSHBDTAction->dropEffect&DROPEFFECT_COPY)!=0 || 
		(pSHBDTAction->dropEffect&DROPEFFECT_MOVE)!=0)
	{
		UINT uFlags=0;
		int nDropItemIndex=HitTest(pSHBDTAction->point,&uFlags);
		if(nDropItemIndex!=-1)
		{
			ASSERT(nDropItemIndex==GetNextItem(-1,LVNI_DROPHILITED));
			// remove highlight
			SetItemState(nDropItemIndex,0,LVIS_DROPHILITED);

			// check if this item accepts drop operation
			CRect rectItem;
			GetItemRect(nDropItemIndex,rectItem,LVIR_BOUNDS);
			if(CanAcceptDrop(nDropItemIndex,
				(pSHBDTAction->point.y > rectItem.top+rectItem.Height()/2),
				pSHBDTAction))
			{
				AcceptDrop(nDropItemIndex,
					(pSHBDTAction->point.y > rectItem.top+rectItem.Height()/2),
					pSHBDTAction);
			}
		}
		else
		{
			// no item to drop on, ask to insert as last item
			if(CanAcceptDrop(GetItemCount(),FALSE,pSHBDTAction))
			{
				AcceptDrop(GetItemCount(),FALSE,pSHBDTAction);
			}
		}
	}

	return TRUE;
}


template<class PARENTLIST> 
void COXBaseDragDropList<PARENTLIST>::OnDropFiles(HDROP hDropInfo)
{
	// retrieve number of files
	UINT nFileCount=::DragQueryFile(hDropInfo,(UINT)-1,NULL,0);

	if(nFileCount>0)
	{
		CPoint ptDrop;
		if(::DragQueryPoint(hDropInfo,&ptDrop))
		{
			// analyze drop position
			UINT uFlags=0;
			int nDropItemIndex=HitTest(ptDrop,&uFlags);
			if(nDropItemIndex!=-1)
			{
				// check if this item accepts drop operation
				CRect rectItem;
				GetItemRect(nDropItemIndex,rectItem,LVIR_BOUNDS);
				if(CanAcceptDropFiles(nDropItemIndex,
					(ptDrop.y > rectItem.top+rectItem.Height()/2),hDropInfo))
				{
					AcceptDropFiles(nDropItemIndex,
						(ptDrop.y > rectItem.top+rectItem.Height()/2),hDropInfo);
				}
			}
			else
			{
				// no item to drop on, ask to insert as last item
				if(CanAcceptDropFiles(GetItemCount(),FALSE,hDropInfo))
				{
					AcceptDropFiles(GetItemCount(),FALSE,hDropInfo);
				}
			}
		}
	}

	::DragFinish(hDropInfo);
}


template<class PARENTLIST> 
BOOL COXBaseDragDropList<PARENTLIST>::CanAcceptDrop(int nItemIndex, 
													BOOL bDropAfter,
													LPSHBDROPTARGETACTION pSHBDTAction)
{
	UNREFERENCED_PARAMETER(nItemIndex);
	UNREFERENCED_PARAMETER(bDropAfter);
	UNREFERENCED_PARAMETER(pSHBDTAction);

	return FALSE;
}


template<class PARENTLIST> 
void COXBaseDragDropList<PARENTLIST>::AcceptDrop(int nItemIndex, 
												 BOOL bDropAfter, 
												 LPSHBDROPTARGETACTION pSHBDTAction)
{
	UNREFERENCED_PARAMETER(nItemIndex);
	UNREFERENCED_PARAMETER(bDropAfter);
	UNREFERENCED_PARAMETER(pSHBDTAction);
}


template<class PARENTLIST> 
BOOL COXBaseDragDropList<PARENTLIST>::CanAcceptDropFiles(int nItemIndex, 
														 BOOL bDropAfter,
														 HDROP hDropInfo)
{
	UNREFERENCED_PARAMETER(nItemIndex);
	UNREFERENCED_PARAMETER(bDropAfter);
	UNREFERENCED_PARAMETER(hDropInfo);

	return FALSE;
}


template<class PARENTLIST> 
void COXBaseDragDropList<PARENTLIST>::AcceptDropFiles(int nItemIndex, 
													  BOOL bDropAfter, 
													  HDROP hDropInfo)
{
	UNREFERENCED_PARAMETER(nItemIndex);
	UNREFERENCED_PARAMETER(bDropAfter);
	UNREFERENCED_PARAMETER(hDropInfo);
}


//////////////////////////////////////////////////////////////////////////////


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_OX_DRAGDROPSUPPORT_)
