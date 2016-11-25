/*
 * author schneider
 *
 * This sofware may by copyright protected!
 * 
 */
/** \file asuro_v.c
 */
 

#include "object_defs.h"
#include "../Protocol/meta.h"
#include <stdio.h>

const char LED_FRONT_DESCR[] = "LED_front";
const char LED_BACK_RIGHT_DESCR[] = "led_back_right";
const char LED_BACK_LEFT_DESCR[] = "led_back_left";
const char ENGINE_LEFT_DIR_DESCR[] = "engine_left_dir";
const char ENGINE_LEFT_SPEED_DESCR[] = "engine_left_speed";
const char ENGINE_LEFT_DESCR[] = "engine_left";

const char ENGINE_RIGHT_DIR_DESCR[] = "engine_right_dir";
const char ENGINE_RIGHT_SPEED_DESCR[] = "engine_right_speed";
const char ENGINE_RIGHT_DESCR[] = "engine_right";

Virtual_Asuro_T asuro;

void PrintAsuroStatus(){
	printf("\n Asuro Status:");
	printf("\n Front-LED      : %u ", asuro.front_led);
	printf("\n Status LED     : %u ", asuro.status_led);
	printf("\n Back lft       : %u ", asuro.back_l_led);
	printf("\n Back rght      : %u ", asuro.back_r_led);
	printf("\n lft Eng.Dir    : %u ", asuro.left_engine.dir);
	printf("\n rght Eng.Dir   : %u ", asuro.right_engine.dir);
	printf("\n lft Eng.Speed  : %u ", asuro.left_engine.speed);
	printf("\n rght Eng.Speed : %u ", asuro.right_engine.speed);
	printf("\n left line      : %d ", asuro.left_line.data);
	printf("\n right line     : %d ", asuro.right_line.data);
	printf("\n left odome     : %d ", asuro.left_odo.data);
	printf("\n right odo      : %d ", asuro.right_odo.data);
	printf("\n");
}

void SetAsuro(unsigned char* data, unsigned char len)
{
//	int* int_ptr;
	if(!len){
		SendError(ERR_INCOMPLETE_FRAME);
		return;
	}
	
	switch (data[0]) {
		case LED_FRONT:
			if(len > 0) asuro.front_led = data[1];
			else SendError(ERR_INCOMPLETE_FRAME);
			break;
		case LED_STATUS:
			if(len > 0) asuro.status_led = data[1];
			else SendError(ERR_INCOMPLETE_FRAME);
			break;
		case LED_BACK_LEFT:
			if(len > 0) asuro.back_l_led = data[1];
			else SendError(ERR_INCOMPLETE_FRAME);
			break;
		case LED_BACK_RIGHT:
			if(len > 0) asuro.back_r_led = data[1];
			else SendError(ERR_INCOMPLETE_FRAME);
			break;
		case ENGINE_LEFT:
			if(len > 1){ 
				asuro.left_engine.dir = data[1];
				asuro.left_engine.speed = data[2];
			}
			else SendError(ERR_INCOMPLETE_FRAME);
			break;
		case ENGINE_RIGHT:
			if(len > 1){ 
				asuro.right_engine.dir = data[1];
				asuro.right_engine.speed = data[2];
			}
			else SendError(ERR_INCOMPLETE_FRAME);
			break;
			
		case ENGINE_LEFT_DIR:
			if(len > 1){ 
				asuro.left_engine.dir = data[1];
				//asuro.left_engine.speed = data[2];
			}
			else SendError(ERR_INCOMPLETE_FRAME);
			break;
		case ENGINE_RIGHT_DIR:
			if(len > 1){ 
				asuro.right_engine.dir = data[1];
				//asuro.right_engine.speed = data[2];
			}
			else SendError(ERR_INCOMPLETE_FRAME);
			break;
			
		case ENGINE_LEFT_SPEED:
			if(len > 1){ 
				//asuro.left_engine.dir = data[1];
				asuro.left_engine.speed = data[1];
			}
			else SendError(ERR_INCOMPLETE_FRAME);
			break;
		case ENGINE_RIGHT_SPEED:
			if(len > 1){ 
				//asuro.right_engine.dir = data[1];
				asuro.right_engine.speed = data[1];
			}
			else SendError(ERR_INCOMPLETE_FRAME);
			break;
			
		
			
		case LINE_DATA:
			if(len > 1){
				asuro.left_line.data = *(int*)&(data[1]);
				asuro.right_line.data = *(int*)&(data[3]);
				//asuro.right_line.data = data[1];
				//asuro.right_engine.speed = data[2];
			}
			else SendError(ERR_INCOMPLETE_FRAME);
			break;
		default:
			SendError(ERR_UNKNOWN_COMMAND);
			break;
	}
}

void GetAsuro( unsigned char what , unsigned char* data, unsigned char len)
{
//	int *int_ptr;
//	unsigned char *byte_ptr;
	data[0] = what;
	switch (what) {
		case LED_FRONT:
			data[1]=asuro.front_led;
			break;
		case LED_STATUS:
			data[1] = asuro.status_led;
			break;
		case LED_BACK_LEFT:
			data[1] = asuro.back_l_led;
			break;
		case LED_BACK_RIGHT:
			data[1] = asuro.back_r_led;
			break;
		case ENGINE_LEFT:
			data[1] = asuro.left_engine.dir;
			data[2] = asuro.left_engine.speed;
			break;
		case ENGINE_RIGHT:
			data[1] = asuro.right_engine.dir;
			data[2] = asuro.right_engine.speed;
			break;
			
		case ENGINE_LEFT_DIR:
			data[1] = asuro.left_engine.dir;
			//data[2] = asuro.left_engine.speed;
			break;
		case ENGINE_RIGHT_DIR:
			data[1] = asuro.right_engine.dir;
			//data[2] = asuro.right_engine.speed;
			break;
			
		case ENGINE_LEFT_SPEED:
			//data[1] = asuro.left_engine.dir;
			data[1] = asuro.left_engine.speed;
			break;
		case ENGINE_RIGHT_SPEED:
			//data[1] = asuro.right_engine.dir;
			data[1] = asuro.right_engine.speed;
			break;
//		case ODOMETRIE_DATA_LEFT:
//			byte_ptr = (unsigned char*)&asuro.left_odo.data;
//			data[1] = byte_ptr[0];
//			data[2] = byte_ptr[1];
//			break;
//		case ODOMETRIE_DATA_RIGHT:
//			byte_ptr = (unsigned char*)&asuro.right_odo.data;
//			data[1] = byte_ptr[0];
//			data[2] = byte_ptr[1];
//			break;
//		case LINE_DATA_LEFT:
//			byte_ptr = (unsigned char*)&asuro.left_line.data;
//			data[1] = byte_ptr[0];
//			data[2] = byte_ptr[1];
//			break;
//		case LINE_DATA_RIGHT:
//			byte_ptr = (unsigned char*)&asuro.right_line.data;
//			data[1] = byte_ptr[0];
//			data[2] = byte_ptr[1];
//			break;
		case SWITCH_STATUS:
			data[1] = asuro.switches;
			break;
		default:
			break;
	}
}

void InitAsuro()
{
	asuro.back_l_led = 0;
	asuro.back_r_led = 0;
	asuro.status_led = LED_GN;
	asuro.front_led = 0;
	asuro.left_engine.dir = ENG_BRK;
	asuro.left_engine.speed = 0;
	asuro.right_engine.dir = ENG_BRK;
	asuro.right_engine.speed = 0;
}
Variable_Data_T InitVD_(unsigned char* name , unsigned char size , DataGatherer_f fkt)
{
	Variable_Data_T tmp;
	tmp._ByteSize = size;
	size=0;
	while(size<4) tmp._DataBuffer[size++]=0;

	for(size=0;size<VAR_NAME_LEN;size++)
	{
		//if(!name[size]) break;
		tmp._Name[size]=0;
		tmp._Name[size]=name[size];
	}
	tmp._GetData = fkt;

	return tmp;
}

short WriteIDDescription(unsigned char id, unsigned char* adr,unsigned char max_len)
{
	unsigned short i=0;
	unsigned char* t_p=0;
	switch (id) {
		case LED_FRONT:
			t_p=(unsigned char*)&LED_FRONT_DESCR[0];
			break;
		case LED_BACK_LEFT:
			t_p=(unsigned char*)&LED_BACK_LEFT_DESCR[0];
			break;
		case LED_BACK_RIGHT:
			t_p=(unsigned char*)&LED_BACK_RIGHT_DESCR[0];
			break;
		case LED_STATUS:
			
			break;
		case ENGINE_LEFT_DIR:
			t_p=(unsigned char*)ENGINE_LEFT_DIR_DESCR;
			break;
		case ENGINE_LEFT_SPEED:
			t_p=(unsigned char*)ENGINE_LEFT_SPEED_DESCR;
			break;
		case ENGINE_LEFT:
			t_p=(unsigned char*)ENGINE_LEFT_DESCR;
			break;
		case ENGINE_RIGHT_DIR:
			t_p=(unsigned char*)ENGINE_RIGHT_DIR_DESCR;
			break;
		case ENGINE_RIGHT_SPEED:
			t_p=(unsigned char*)ENGINE_RIGHT_SPEED_DESCR;
			break;
		case ENGINE_RIGHT:
			t_p=(unsigned char*)ENGINE_RIGHT_DESCR;
			break;
		default:
			break;
	}
	if(!t_p) return 0;
	while(i<max_len)
	{
		adr[i]=t_p[i++];
		if( !(char)t_p[i] ) break;
	}
	return i;
}
