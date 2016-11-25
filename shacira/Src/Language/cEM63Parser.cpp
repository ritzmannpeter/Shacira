//## begin module%438055180281.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%438055180281.cm

//## begin module%438055180281.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%438055180281.cp

//## Module: cEM63Parser%438055180281; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Language\cEM63Parser.cpp

//## begin module%438055180281.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%438055180281.additionalIncludes

//## begin module%438055180281.includes preserve=yes
//## end module%438055180281.includes

// cVarRef
#include "System/Database/cVarRef.h"
// cContext
#include "System/Database/cContext.h"
// cEM63Session
#include "Control/Device/EM63/cEM63Session.h"
// cEM63Job
#include "Control/Device/EM63/cEM63Job.h"
// cEM63Parser
#include "Language/cEM63Parser.h"
//## begin module%438055180281.additionalDeclarations preserve=yes
//## end module%438055180281.additionalDeclarations


// Class cEM63Parser 





cEM63Parser::cEM63Parser()
  //## begin cEM63Parser::cEM63Parser%.hasinit preserve=no
      : _Line(-1), _Column(-1)
  //## end cEM63Parser::cEM63Parser%.hasinit
  //## begin cEM63Parser::cEM63Parser%.initialization preserve=yes
  //## end cEM63Parser::cEM63Parser%.initialization
{
  //## begin cEM63Parser::cEM63Parser%.body preserve=yes
  //## end cEM63Parser::cEM63Parser%.body
}

cEM63Parser::cEM63Parser(const cEM63Parser &right)
  //## begin cEM63Parser::cEM63Parser%copy.hasinit preserve=no
      : _Line(-1), _Column(-1)
  //## end cEM63Parser::cEM63Parser%copy.hasinit
  //## begin cEM63Parser::cEM63Parser%copy.initialization preserve=yes
  //## end cEM63Parser::cEM63Parser%copy.initialization
{
  //## begin cEM63Parser::cEM63Parser%copy.body preserve=yes
  //## end cEM63Parser::cEM63Parser%copy.body
}


cEM63Parser::~cEM63Parser()
{
  //## begin cEM63Parser::~cEM63Parser%.body preserve=yes
  //## end cEM63Parser::~cEM63Parser%.body
}


//## Get and Set Operations for Class Attributes (implementation)

STRING_T cEM63Parser::get_File () const
{
  //## begin cEM63Parser::get_File%43A7EE330224.get preserve=no
  return _File;
  //## end cEM63Parser::get_File%43A7EE330224.get
}

int cEM63Parser::get_Line () const
{
  //## begin cEM63Parser::get_Line%43A7EE330234.get preserve=no
  return _Line;
  //## end cEM63Parser::get_Line%43A7EE330234.get
}

int cEM63Parser::get_Column () const
{
  //## begin cEM63Parser::get_Column%43A7EE330235.get preserve=no
  return _Column;
  //## end cEM63Parser::get_Column%43A7EE330235.get
}

STRING_T cEM63Parser::get_ErrorText () const
{
  //## begin cEM63Parser::get_ErrorText%43A7EEAE0040.get preserve=no
  return _ErrorText;
  //## end cEM63Parser::get_ErrorText%43A7EEAE0040.get
}

// Additional Declarations
  //## begin cEM63Parser%438055180281.declarations preserve=yes
  //## end cEM63Parser%438055180281.declarations

//## begin module%438055180281.epilog preserve=yes
//## end module%438055180281.epilog
