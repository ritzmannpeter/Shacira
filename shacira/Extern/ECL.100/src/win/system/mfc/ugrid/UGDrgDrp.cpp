/***********************************************
	Ultimate Grid 97
	Copyright 1994 - 1997 Dundas Software Ltd.

	Class 
		CUGDropTarget
	Purpose
		This class handles the grid's drag and
		drop client operations.
	Details
		 An instance of this class is created 
		 inside of the main	grid class. This class 
		 then sends notifications to the main grid 
		 class then performs the appropriate actions 
		 based on the return value of the notification.
************************************************/

#pragma warning(disable:4100) /* Unreferenzierter formaler Parameter */

#include "../stdafx.h"
#include "UGCtrl.h"

#ifdef UG_ENABLE_DRAGDROP

/***************************************************
****************************************************/
CUGDropTarget::CUGDropTarget(){
}
/***************************************************
****************************************************/
CUGDropTarget::~CUGDropTarget(){
}

/***************************************************
****************************************************/
DROPEFFECT CUGDropTarget::OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point ){
	return m_ctrl->OnDragEnter(pDataObject);
}
/***************************************************
****************************************************/
DROPEFFECT CUGDropTarget::OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point ){
	int col;
	long row;
	m_ctrl->GetCellFromPoint(point.x,point.y,&col,&row);
	return m_ctrl->OnDragOver(pDataObject,col,row);
}
/***************************************************
****************************************************/
DROPEFFECT CUGDropTarget::OnDropEx( CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point ){

	int col;
	long row;
	int rt;
	m_ctrl->GetCellFromPoint(point.x,point.y,&col,&row);
	rt = m_ctrl->OnDragDrop(pDataObject,col,row);

	CString string;
	HGLOBAL global;

#ifdef _UNICODE
	// ask for CF_UNICODETEXT if we can and should handle it.
	if(rt != DROPEFFECT_NONE){
		if(pDataObject->IsDataAvailable(CF_UNICODETEXT,NULL))
			m_ctrl->GotoCell(col,row);
			LPTSTR   bufu;
			global = pDataObject->GetGlobalData(CF_UNICODETEXT,NULL);
			bufu = (LPTSTR)GlobalLock(global);
			string = bufu;
			
			m_ctrl->Paste(string);
			return rt;				// no need to go further..
	}
#endif

	// ask for CF_TEXT.  Assignment to CString should
	// convert if we have compiled for _UNICODE - leave
	// the LPSTR declarations!
	if(rt != DROPEFFECT_NONE){
		if(pDataObject->IsDataAvailable(CF_TEXT,NULL))
			m_ctrl->GotoCell(col,row);
			LPSTR   buf;
			global = pDataObject->GetGlobalData(CF_TEXT,NULL);
			buf = (LPSTR)GlobalLock(global);
			string = buf;
			
			m_ctrl->Paste(string);
	}

	return rt;
}


#endif               
// the next line must be put in so the MSVC++1.5x will not give an 
// unexpected end of file found error, MSVC++1.5x compiler does not
// compile properly if an #endif is the last line
#define UGDRGDRPCPP
