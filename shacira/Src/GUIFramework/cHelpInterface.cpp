//## begin module%41500F2C0222.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41500F2C0222.cm

//## begin module%41500F2C0222.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41500F2C0222.cp

//## Module: cHelpInterface%41500F2C0222; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\GUIFramework\QTFramework\cHelpInterface.cpp

//## begin module%41500F2C0222.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%41500F2C0222.additionalIncludes

//## begin module%41500F2C0222.includes preserve=yes
//## end module%41500F2C0222.includes

// cHelpInterface
#include "cHelpInterface.h"
//## begin module%41500F2C0222.additionalDeclarations preserve=yes
//## end module%41500F2C0222.additionalDeclarations


// Class cHelpInterface 


cHelpInterface::cHelpInterface()
  //## begin cHelpInterface::cHelpInterface%.hasinit preserve=no
      : _Active(false)
  //## end cHelpInterface::cHelpInterface%.hasinit
  //## begin cHelpInterface::cHelpInterface%.initialization preserve=yes
  //## end cHelpInterface::cHelpInterface%.initialization
{
  //## begin cHelpInterface::cHelpInterface%.body preserve=yes
  //## end cHelpInterface::cHelpInterface%.body
}

cHelpInterface::cHelpInterface(const cHelpInterface &right)
  //## begin cHelpInterface::cHelpInterface%copy.hasinit preserve=no
      : _Active(false)
  //## end cHelpInterface::cHelpInterface%copy.hasinit
  //## begin cHelpInterface::cHelpInterface%copy.initialization preserve=yes
  //## end cHelpInterface::cHelpInterface%copy.initialization
{
  //## begin cHelpInterface::cHelpInterface%copy.body preserve=yes
  //## end cHelpInterface::cHelpInterface%copy.body
}


cHelpInterface::~cHelpInterface()
{
  //## begin cHelpInterface::~cHelpInterface%.body preserve=yes
  //## end cHelpInterface::~cHelpInterface%.body
}



//## Other Operations (implementation)
void cHelpInterface::Show ()
{
  //## begin cHelpInterface::Show%1095771619.body preserve=yes
   _Active = true;
  //## end cHelpInterface::Show%1095771619.body
}

void cHelpInterface::Hide ()
{
  //## begin cHelpInterface::Hide%1095771620.body preserve=yes
   _Active = false;
  //## end cHelpInterface::Hide%1095771620.body
}

BOOL_T cHelpInterface::Active ()
{
  //## begin cHelpInterface::Active%1095771621.body preserve=yes
   return _Active;
  //## end cHelpInterface::Active%1095771621.body
}

bool cHelpInterface::ShowHelp (const QString & help_id1, const QString & help_id2)
{
  //## begin cHelpInterface::ShowHelp%1095765931.body preserve=yes
  //## end cHelpInterface::ShowHelp%1095765931.body
   return true;
}

bool cHelpInterface::ExistHelpFile(const QString & help_id1, const QString & help_id2)
{
  //## begin cHelpInterface::ShowHe preserve=yes
  //## end cHelpInterface::ShowHelp
   return true;
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cHelpInterface::get_Active () const
{
  //## begin cHelpInterface::get_Active%415272280203.get preserve=no
  return _Active;
  //## end cHelpInterface::get_Active%415272280203.get
}

void cHelpInterface::set_Active (BOOL_T value)
{
  //## begin cHelpInterface::set_Active%415272280203.set preserve=no
  _Active = value;
  //## end cHelpInterface::set_Active%415272280203.set
}

STRING_T cHelpInterface::get_AdditionalPath () const
{
  return _AdditionalPath;
}

void cHelpInterface::set_AdditionalPath (STRING_T value)
{
  _AdditionalPath = value;
}

// Additional Declarations
  //## begin cHelpInterface%41500F2C0222.declarations preserve=yes
  //## end cHelpInterface%41500F2C0222.declarations

//## begin module%41500F2C0222.epilog preserve=yes
//## end module%41500F2C0222.epilog
