//## begin module%3EBF96A80213.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3EBF96A80213.cm

//## begin module%3EBF96A80213.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3EBF96A80213.cp

//## Module: cEventAdapter%3EBF96A80213; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Client\Adapters\cEventAdapter.cpp

//## begin module%3EBF96A80213.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3EBF96A80213.additionalIncludes

//## begin module%3EBF96A80213.includes preserve=yes
//## end module%3EBF96A80213.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"
// cObjectLock
#include "System/Objects/cObjectLock.h"
// cPtrList
#include "System/Memory/cPtrList.h"
// cEventControl
#include "Client/Adapters/cEventControl.h"
// cEventAdapter
#include "Client/Adapters/cEventAdapter.h"
//## begin module%3EBF96A80213.additionalDeclarations preserve=yes
//## end module%3EBF96A80213.additionalDeclarations


// Class cEventAdapter 






cEventAdapter::cEventAdapter()
  //## begin cEventAdapter::cEventAdapter%.hasinit preserve=no
      : _Controls(NULL)
  //## end cEventAdapter::cEventAdapter%.hasinit
  //## begin cEventAdapter::cEventAdapter%.initialization preserve=yes
  //## end cEventAdapter::cEventAdapter%.initialization
{
  //## begin cEventAdapter::cEventAdapter%.body preserve=yes
   _Controls = new cPtrList;
  //## end cEventAdapter::cEventAdapter%.body
}

cEventAdapter::cEventAdapter(const cEventAdapter &right)
  //## begin cEventAdapter::cEventAdapter%copy.hasinit preserve=no
      : _Controls(NULL)
  //## end cEventAdapter::cEventAdapter%copy.hasinit
  //## begin cEventAdapter::cEventAdapter%copy.initialization preserve=yes
  //## end cEventAdapter::cEventAdapter%copy.initialization
{
  //## begin cEventAdapter::cEventAdapter%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cEventAdapter::cEventAdapter%copy.body
}

cEventAdapter::cEventAdapter (CONST_STRING_T cell_name)
  //## begin cEventAdapter::cEventAdapter%1054828773.hasinit preserve=no
      : _Controls(NULL)
  //## end cEventAdapter::cEventAdapter%1054828773.hasinit
  //## begin cEventAdapter::cEventAdapter%1054828773.initialization preserve=yes
  //## end cEventAdapter::cEventAdapter%1054828773.initialization
{
  //## begin cEventAdapter::cEventAdapter%1054828773.body preserve=yes
   _Name = "EventAdapter";
   if (cell_name != NULL) {
      _CellName = cell_name;
      _Name += ".";
      _Name += cell_name;
   }
   _Controls = new cPtrList;
  //## end cEventAdapter::cEventAdapter%1054828773.body
}


cEventAdapter::~cEventAdapter()
{
  //## begin cEventAdapter::~cEventAdapter%.body preserve=yes
   DELETE_OBJECT(cPtrList, _Controls)
  //## end cEventAdapter::~cEventAdapter%.body
}



//## Other Operations (implementation)
void cEventAdapter::Object (cTransientObject *object)
{
  //## begin cEventAdapter::Object%1052744771.body preserve=yes
   cObjectLock __lock__(&_LockMutex);
   STRING_T name1 = _CellName.c_str();
   STRING_T name2 = object->get_CellName().c_str();
   if (_CellName.size() > 0 &&
      strcmp(name1.c_str(), name2.c_str()) != 0) {
      return;
   }
   if (_Controls == NULL) {
      return;
   }
   cPtrList::cConstIterator i = _Controls->Begin();
   if (i.First()) {
      do {
         cEventControl * control = (cEventControl*)i.Ptr();
         if (control != NULL) {
            control->Object(object);
         }
      } while (i.Next());
   }
  //## end cEventAdapter::Object%1052744771.body
}

void cEventAdapter::RegisterControl (cEventControl *event_control)
{
  //## begin cEventAdapter::RegisterControl%1052744772.body preserve=yes
   if (_Controls == NULL) {
      return;
   }
   _Controls->Add(event_control);
  //## end cEventAdapter::RegisterControl%1052744772.body
}

void cEventAdapter::UnRegisterControl (cEventControl *event_control)
{
  //## begin cEventAdapter::UnRegisterControl%1052744773.body preserve=yes
   if (_Controls == NULL) {
      return;
   }
   _Controls->Remove(event_control);
  //## end cEventAdapter::UnRegisterControl%1052744773.body
}

void cEventAdapter::Lock ()
{
  //## begin cEventAdapter::Lock%1088517102.body preserve=yes
   _LockMutex.request();
  //## end cEventAdapter::Lock%1088517102.body
}

void cEventAdapter::Unlock ()
{
  //## begin cEventAdapter::Unlock%1088517103.body preserve=yes
   _LockMutex.release();
  //## end cEventAdapter::Unlock%1088517103.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cEventAdapter::get_CellName () const
{
  //## begin cEventAdapter::get_CellName%3EBF975E02EE.get preserve=no
  return _CellName;
  //## end cEventAdapter::get_CellName%3EBF975E02EE.get
}

// Additional Declarations
  //## begin cEventAdapter%3EBF96A80213.declarations preserve=yes
  //## end cEventAdapter%3EBF96A80213.declarations

//## begin module%3EBF96A80213.epilog preserve=yes
//## end module%3EBF96A80213.epilog
