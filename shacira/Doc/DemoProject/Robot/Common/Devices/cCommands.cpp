// cCommands.cpp: Implementierung der Klasse cCommands.
//
//////////////////////////////////////////////////////////////////////

#include "cCommands.h"

#include "Protocol/defs.h"
//#include "Protocol/meta.h"
//#include "Protocol/queue_handle.h"
//#include "Protocol/state_machine.h"

#include "VirAs/object_defs.h"
#include <string.h>
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

cCommands::cCommands()
{

}

cCommands::~cCommands()
{

}

unsigned char* cCommands::GetCommand(char* com_in)
{
	
	char* pToken=0;
	int i;
	for(i=0;i<80;i++) _ComandBuffer[i] = 0;
	i=0;
	pToken = strtok(com_in, " ");
	while ( pToken )
	{
	    switch (i) {
			case 0:
				if(!strcmp(pToken,"set")){
					//printf("\n SET commando");
					_ComandBuffer[i] = SET_COMMAND;
					//prepare set command
				}
				else if(!strcmp(pToken,"get")){
//					printf("\n REQ commando");
					_ComandBuffer[i]= REQ_COMMAND;
					//prepare request command
				}
				else ; //\todo failure
				break;
			case 1:
				if(!strcmp(pToken,"frontled")){
					_ComandBuffer[i]=LED_FRONT;
				}
				else if(!strcmp(pToken,"statusled")){
					_ComandBuffer[i]=LED_STATUS;
				}
				else if(!strcmp(pToken,"backled_l")){
					_ComandBuffer[i]=LED_BACK_LEFT;
				}
				else if(!strcmp(pToken,"backled_r")){
					_ComandBuffer[i]=LED_BACK_RIGHT;
				}
				else if(!strcmp(pToken,"engine_l")){
					_ComandBuffer[i]=ENGINE_LEFT;
				}
				else if(!strcmp(pToken,"engine_r")){
					_ComandBuffer[i]=ENGINE_RIGHT;
				}
				else if( (!strcmp(pToken,"odo") ) && _ComandBuffer[0]==REQ_COMMAND){
					printf("\nodo\n");
					_ComandBuffer[i]=ODOMETRIE_DATA;
				}
				else if( (!strcmp(pToken,"line-data") ) && _ComandBuffer[0]==REQ_COMMAND){
					_ComandBuffer[i]=LINE_DATA;
				}
				else if( (!strcmp(pToken,"switches") ) && _ComandBuffer[0]==REQ_COMMAND){
					_ComandBuffer[i]=SWITCH_STATUS;
				}
				else ; //\todo failure
				
				break;
			default:
					if(_ComandBuffer[0] == SET_COMMAND){
					int in;
					int params=sscanf(pToken,"%d",&in);
					*(int*)&(_ComandBuffer[i]) = in;
					//printf("\n%u\n",str1[i]);
					
					}
				
				break;
		}
	    i++;
	    pToken = strtok(NULL, " ");
	}
	_BufferLen = --i;
	_Fkt(_ComandBuffer , (unsigned char)_BufferLen);
	return _ComandBuffer;
}

void cCommands::SetFkt(ComputeFrame_f f)
{
	_Fkt = f;
}