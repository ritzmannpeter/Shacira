// cCommands.h: Schnittstelle für die Klasse cCommands.
//
//////////////////////////////////////////////////////////////////////

#include "Protocol/defs.h"

#if !defined(AFX_CCOMMANDS_H__B6335E44_31F6_4CBA_B599_ED3A70BA7F38__INCLUDED_)
#define AFX_CCOMMANDS_H__B6335E44_31F6_4CBA_B599_ED3A70BA7F38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class cCommands  
{
public:
	cCommands();
	virtual ~cCommands();
	unsigned char* GetCommand(char*);
	void SetFkt(ComputeFrame_f);
private:
	unsigned char _ComandBuffer[80];
	int _BufferLen;
	ComputeFrame_f _Fkt;

};

#endif // !defined(AFX_CCOMMANDS_H__B6335E44_31F6_4CBA_B599_ED3A70BA7F38__INCLUDED_)
