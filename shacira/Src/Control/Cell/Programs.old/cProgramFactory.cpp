//## begin module%3E154E8A0100.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E154E8A0100.cm

//## begin module%3E154E8A0100.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3E154E8A0100.cp

//## Module: cProgramFactory%3E154E8A0100; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Control\Cell\Programs\cProgramFactory.cpp

//## begin module%3E154E8A0100.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E154E8A0100.additionalIncludes

//## begin module%3E154E8A0100.includes preserve=yes
//## end module%3E154E8A0100.includes

// cUSSProgram
#include "Control/Cell/Programs/cUSSProgram.h"
// cStandardProgram
#include "Control/Cell/Programs/cStandardProgram.h"
// cAirbagProgram
#include "Control/Cell/Programs/cAirbagProgram.h"
// cProgramFactory
#include "Control/Cell/Programs/cProgramFactory.h"
// cProgram
#include "Control/Cell/Programs/cProgram.h"
//## begin module%3E154E8A0100.additionalDeclarations preserve=yes
//## end module%3E154E8A0100.additionalDeclarations


// Class cProgramFactory 

cProgramFactory::cProgramFactory()
  //## begin cProgramFactory::cProgramFactory%.hasinit preserve=no
  //## end cProgramFactory::cProgramFactory%.hasinit
  //## begin cProgramFactory::cProgramFactory%.initialization preserve=yes
  //## end cProgramFactory::cProgramFactory%.initialization
{
  //## begin cProgramFactory::cProgramFactory%.body preserve=yes
  //## end cProgramFactory::cProgramFactory%.body
}

cProgramFactory::cProgramFactory(const cProgramFactory &right)
  //## begin cProgramFactory::cProgramFactory%copy.hasinit preserve=no
  //## end cProgramFactory::cProgramFactory%copy.hasinit
  //## begin cProgramFactory::cProgramFactory%copy.initialization preserve=yes
  //## end cProgramFactory::cProgramFactory%copy.initialization
{
  //## begin cProgramFactory::cProgramFactory%copy.body preserve=yes
  //## end cProgramFactory::cProgramFactory%copy.body
}


cProgramFactory::~cProgramFactory()
{
  //## begin cProgramFactory::~cProgramFactory%.body preserve=yes
  //## end cProgramFactory::~cProgramFactory%.body
}



//## Other Operations (implementation)
INT_T cProgramFactory::TypeCode (CONST_STRING_T type_name)
{
  //## begin cProgramFactory::TypeCode%1041583344.body preserve=yes
   TYPE_CODE(type_name,PGM_STD)
   TYPE_CODE(type_name,PGM_AIRBAG)
   TYPE_CODE(type_name,PGM_USS)
   TYPE_CODE(type_name,PGM_IMM)
   TYPE_CODE(type_name,PGM_SPS)
   throw cError(FACTORY_INVALID_VALUE, 0, type_name, "cProgramFactory");
  //## end cProgramFactory::TypeCode%1041583344.body
}

CONST_STRING_T cProgramFactory::TypeName (INT_T type_code)
{
  //## begin cProgramFactory::TypeName%1041583345.body preserve=yes
   TYPE_NAME(type_code,PGM_STD)
   TYPE_NAME(type_code,PGM_AIRBAG)
   TYPE_NAME(type_code,PGM_USS)
   TYPE_NAME(type_code,PGM_IMM)
   TYPE_NAME(type_code,PGM_SPS)
   throw cError(FACTORY_INVALID_VALUE, 0, cConvUtils::StringValue(type_code).c_str(), "cProgramFactory");
  //## end cProgramFactory::TypeName%1041583345.body
}

cProgram * cProgramFactory::CreateProgram (cConfigurationObject *config_obj, cCell *cell)
{
  //## begin cProgramFactory::CreateProgram%1041583346.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   STRING_T type_name = config_obj->PropertyValue("ProgramType", "", true);
   int type = TypeCode(type_name.c_str());
   cProgram * program = NULL;
   switch (type) {
   case PGM_STD:
      program = new cStandardProgram(cell, config_obj);
      break;
#ifdef PORTED
   case PGM_AIRBAG:
      program = new cAirbagProgram(cell, config_obj);
      break;
   case PGM_USS:
      program = new cUSSProgram(cell, config_obj);
      break;
   case PGM_IMM:
      program = new cIMMachineProgram(cell, config_obj);
      break;
   case PGM_SPS:
      program = new cSPSProgram(cell, config_obj);
      break;
#endif
   default:
      throw cError(FACTORY_INVALID_VALUE, 0, type_name.c_str(), "cProgram");
   }
   return program;
  //## end cProgramFactory::CreateProgram%1041583346.body
}

// Additional Declarations
  //## begin cProgramFactory%3E154E8A0100.declarations preserve=yes
  //## end cProgramFactory%3E154E8A0100.declarations

//## begin module%3E154E8A0100.epilog preserve=yes
//## end module%3E154E8A0100.epilog
