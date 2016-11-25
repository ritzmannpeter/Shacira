//## begin module%3FE7501801C5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FE7501801C5.cm

//## begin module%3FE7501801C5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FE7501801C5.cp

//## Module: cProgramFactory%3FE7501801C5; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cProgramFactory.cpp

//## begin module%3FE7501801C5.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3FE7501801C5.additionalIncludes

//## begin module%3FE7501801C5.includes preserve=yes
//## end module%3FE7501801C5.includes

// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cContext
#include "System/Database/cContext.h"
// cProgramFactory
#include "Control/Cell/cProgramFactory.h"
// cProgram
#include "Control/Cell/cProgram.h"
// cCell
#include "Control/Cell/cCell.h"
// cEM63Program
#include "Control/Cell/cEM63Program.h"
//## begin module%3FE7501801C5.additionalDeclarations preserve=yes
//## end module%3FE7501801C5.additionalDeclarations


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
_ASSERT_UNCOND
  //## end cProgramFactory::cProgramFactory%copy.body
}


cProgramFactory::~cProgramFactory()
{
  //## begin cProgramFactory::~cProgramFactory%.body preserve=yes
  //## end cProgramFactory::~cProgramFactory%.body
}



//## Other Operations (implementation)
cProgram * cProgramFactory::CreateProgram (cConfigurationObject *config_obj, cContext *context)
{
  //## begin cProgramFactory::CreateProgram%1072120971.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   STRING_T type_name = config_obj->PropertyValue("ProgramType", "", true);
   cProgram * program = NULL;
   if (IDENTIFIER_EQUAL(type_name.c_str(), "Gateway")) {
      program = new cGateway(config_obj, context);
   } else {
      program = CreateExternal(config_obj, context);
   }
   return program;
  //## end cProgramFactory::CreateProgram%1072120971.body
}

cProgram * cProgramFactory::CreateExternal (cConfigurationObject *config_obj, cContext *context)
{
  //## begin cProgramFactory::CreateExternal%1074705362.body preserve=yes
   PROG_FACTORY_T factory_func = cCustomFunctions::ProgramCreatorFuncAddress();
   if (factory_func != NULL) {
      cProgram * program = NULL;
      program = factory_func(config_obj, context);
      return program;
   } else {
      return NULL;
   }
  //## end cProgramFactory::CreateExternal%1074705362.body
}

// Additional Declarations
  //## begin cProgramFactory%3FE7501801C5.declarations preserve=yes
  //## end cProgramFactory%3FE7501801C5.declarations

//## begin module%3FE7501801C5.epilog preserve=yes
//## end module%3FE7501801C5.epilog
