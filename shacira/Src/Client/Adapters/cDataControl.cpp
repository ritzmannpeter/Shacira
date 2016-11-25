//## begin module%3D0775C501BC.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D0775C501BC.cm

//## begin module%3D0775C501BC.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3D0775C501BC.cp

//## Module: cDataControl%3D0775C501BC; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Client\Adapters\cDataControl.cpp

//## begin module%3D0775C501BC.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3D0775C501BC.additionalIncludes

//## begin module%3D0775C501BC.includes preserve=yes
//## end module%3D0775C501BC.includes

// cVarRef
#include "System/Database/cVarRef.h"
// cDataControl
#include "Client/Adapters/cDataControl.h"
//## begin module%3D0775C501BC.additionalDeclarations preserve=yes
//## end module%3D0775C501BC.additionalDeclarations


// Class cDataControl 


cDataControl::cDataControl()
  //## begin cDataControl::cDataControl%.hasinit preserve=no
      : _VarRef(NULL)
  //## end cDataControl::cDataControl%.hasinit
  //## begin cDataControl::cDataControl%.initialization preserve=yes
  //## end cDataControl::cDataControl%.initialization
{
  //## begin cDataControl::cDataControl%.body preserve=yes
_ASSERT_UNCOND
  //## end cDataControl::cDataControl%.body
}

cDataControl::cDataControl(const cDataControl &right)
  //## begin cDataControl::cDataControl%copy.hasinit preserve=no
      : _VarRef(NULL)
  //## end cDataControl::cDataControl%copy.hasinit
  //## begin cDataControl::cDataControl%copy.initialization preserve=yes
  //## end cDataControl::cDataControl%copy.initialization
{
  //## begin cDataControl::cDataControl%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cDataControl::cDataControl%copy.body
}

cDataControl::cDataControl (cVarRef *var_ref)
  //## begin cDataControl::cDataControl%1043914507.hasinit preserve=no
      : _VarRef(NULL)
  //## end cDataControl::cDataControl%1043914507.hasinit
  //## begin cDataControl::cDataControl%1043914507.initialization preserve=yes
  //## end cDataControl::cDataControl%1043914507.initialization
{
  //## begin cDataControl::cDataControl%1043914507.body preserve=yes
_ASSERT_COND(var_ref != NULL)
   _VarRef = var_ref;
   /// PR 24.05.05 - AddControl may not be called here
   ///             - it must be called in derived classes
   /*
   _VarRef->AddControl(this);
   */
  //## end cDataControl::cDataControl%1043914507.body
}


cDataControl::~cDataControl()
{
  //## begin cDataControl::~cDataControl%.body preserve=yes
  //## end cDataControl::~cDataControl%.body
}



//## Other Operations (implementation)
void cDataControl::NewValue (CONST_STRING_T value, ULONG_T time_offset, UCHAR_T data_type, ULONG_T size, ULONG_T data_set)
{
  //## begin cDataControl::NewValue%1023899454.body preserve=yes
   throw cError(VIRTUAL_METHOD_NOT_IMPLEMENTED, 0, "cDataControl::NewValue", "cDataControl");
  //## end cDataControl::NewValue%1023899454.body
}

void cDataControl::NewValue (BUF_T buf, ULONG_T time_offset, UCHAR_T data_type, ULONG_T size, ULONG_T data_set)
{
  //## begin cDataControl::NewValue%1073907456.body preserve=yes
   throw cError(VIRTUAL_METHOD_NOT_IMPLEMENTED, 0, "cDataControl::NewValue", "cDataControl");
  //## end cDataControl::NewValue%1073907456.body
}

void cDataControl::UpdateValue ()
{
  //## begin cDataControl::UpdateValue%1043914506.body preserve=yes
   throw cError(VIRTUAL_METHOD_NOT_IMPLEMENTED, 0, "cDataControl::UpdateValue", "cDataControl");
  //## end cDataControl::UpdateValue%1043914506.body
}

void * cDataControl::Widget() const
{
   return NULL;
}

STRING_T cDataControl::Name() const
{
   return "unknown";
}

// Additional Declarations
  //## begin cDataControl%3D0775C501BC.declarations preserve=yes
  //## end cDataControl%3D0775C501BC.declarations

//## begin module%3D0775C501BC.epilog preserve=yes
//## end module%3D0775C501BC.epilog
