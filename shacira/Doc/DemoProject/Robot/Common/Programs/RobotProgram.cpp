
#include "FirstHeader.h"
#include "System/Config/cConfigurationObject.h"
#include "System/Objects/cTransientObject.h"
#include "System/Database/cContext.h"
#include "System/Objects/cInfo.h"
#include "System/Objects/cAlarm.h"
#include "System/Objects/cDataChange.h"
#include "System/Objects/cJobEntry.h"
#include "System/Database/cVariable.h"
#include "RobotProgram.h"
#include "System/ApplicationInterface.h"

REGISTER_PROGRAM("RobotProgram", RobotProgram)

RobotProgram::RobotProgram (cConfigurationObject * config_obj, cContext *context)
      : cProgram(config_obj, context)
{
}

RobotProgram::~RobotProgram()
{
}

void RobotProgram::ExecuteCommand(ULONG_T command)
{
}

void RobotProgram::ProcessEvent (cTransientObject *object)
{
	UCHAR_T type = object->get_Type();
	if(type==OT_DATA_CHANGE){
		cDataChange* change = (cDataChange*)object;
		if(change->get_VarName()=="data_present"){
	
			cVariable * var = _Context->Variable("graphic_buffer");
			cVariable * var2 = _Context->Variable("curve_buf");
			BUF_T buf = 0;
			var2->Get(buf);
			int i = 0, j=0;
			UCHAR_T x=0;

			unsigned char mem[250] = {0};
			for (i=0; i<2; i++) {
				
				for(j=0;j<250;j++){
					
					x=buf[i*250+j];
					mem[j]=buf[i*250+j];
				}
				var->Set((CONST_BUF_T)mem, sizeof(mem), i);
			}
		}
	//}
		/*			UCHAR_T value = (UCHAR_T)atoi(change->get_Value().c_str() );
			int dum=0;

			cVariable * var = _Context->Variable("graphic_buffer");
			BUF_T buf = NULL;
			int i = 0;
			for (i=0; i<2; i++) {
//			var->Get(buf, i);
				unsigned char mem[250] = {0};
//				memset(mem, (i*30) + 50, sizeof(mem));
				int j = 0;
							//var->ValueSize() <-> 250
				for (j=0; j<250; j++) {
					mem[j] = (i*30) + 30 + (rand() % 20); 
				}
				var->Set((CONST_BUF_T)mem, sizeof(mem), i);
			}*/
		//}
		else if(change->get_VarName()=="curve_buf"){
			//UCHAR_T value = (UCHAR_T)atoi(change->get_Value().c_str() );
			//int dum=0;

			cVariable * var = _Context->Variable("graphic_buffer");
			BUF_T buf = change->get_BufPtr();
			int i = 0, j=0;
			
			unsigned char mem[250] = {0};
			for (i=0; i<2; i++) {
				
				for(j=0;j<250;j++){
					
					mem[j]=buf[i*250+j];
				}
				var->Set((CONST_BUF_T)mem, sizeof(mem), i);
			}
		}
	}
}

void RobotProgram::Cycle ()
{
	return;
///   cSystemUtils::AcousticSignal(50,50);
   cVariable * var = _Context->Variable("graphic_buffer");
   BUF_T buf = NULL;
   int i = 0;
   for (i=0; i<var->DimSize(0); i++) {
//      var->Get(buf, i);
      unsigned char mem[250] = {0};
//      memset(mem, (i*30) + 50, sizeof(mem));
      int j = 0;
					//var->ValueSize() <-> 250
      for (j=0; j<250; j++) {
         mem[j] = (i*30) + 30 + (rand() % 20); 
      }
      var->Set((CONST_BUF_T)mem, sizeof(mem), i);
   }
}

void RobotProgram::Initialize()
{
}

