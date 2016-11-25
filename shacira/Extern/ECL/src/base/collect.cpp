// ===========================================================================
// base/collect.cpp                                             ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================

#include "base/collect.h"




namespace ecl {

   
   
   
// Implementierung cPlex
// ===========================================================================

cPlex* cPlex::Create(cPlex*& pHead, unsigned int nMax, unsigned int cbElement)
{
   // like 'calloc' but no zero fill
   // may throw memory exceptions

	__ECL_ASSERT__(nMax > 0 && cbElement > 0, cBase::dbgBase|cBase::dbgError|cBase::dbgAssert);
	cPlex* p = (cPlex*) new0 unsigned char[sizeof(cPlex) + nMax * cbElement];
			// may throw exception
	p->pNext = pHead;
	pHead = p;  // change head (adds in reverse order for simplicity)
	return p;
}

void cPlex::FreeDataChain()     // free this one and links
{
	cPlex* p = this;
	while (p != 0)
	{
		unsigned char* bytes = (unsigned char*) p;
		cPlex* pNext = p->pNext;
		delete[] bytes;
		p = pNext;
	}
}




}; // namespace ecl

