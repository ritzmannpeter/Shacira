
#include "FirstHeader.h"
#include "System/Config/cConfigurationObject.h"
#include "System/Database/cContext.h"
#include "cDemoProgram.h"
#include "EM63Program.h"

extern "C" {

cProgram * _CreateProgram(cConfigurationObject * config_obj, cContext * context)
{
   STRING_T program_type = config_obj->PropertyValue("ProgramType", "", true);
   if (IDENTIFIER_EQUAL(program_type.c_str(), "DemoProgram")) {
      return new cDemoProgram(config_obj, context);
   } else if (IDENTIFIER_EQUAL(program_type.c_str(), "EM63Program")) {
      return new EM63Program(config_obj, context); 	
   } else {
      return NULL;
   }
}

}
