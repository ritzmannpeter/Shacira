/*
 * author schneider
 *
 * This sofware may by copyright protected!
 * 
 */
/** \file object_defs.h
 */
 

#ifndef OBJECT_DEFS_H_
#define OBJECT_DEFS_H_

#include "..\Protocol\defs.h"

typedef struct
{
	unsigned char dir;
	unsigned char speed;
}Engine_T;

typedef struct
{
	int data;
}Odometrie_T;

typedef struct
{
	unsigned short data;
}Line_T;
/*
typedef struct
{
	unsigned char sw1;
	unsigned char sw2;
	unsigned char sw3;
	unsigned char sw4;
	unsigned char sw5;
	unsigned char sw6;
}Switches_T;
*/
typedef struct va
{
	unsigned char front_led;
	unsigned char status_led;
	unsigned char back_l_led;
	unsigned char back_r_led;
	
	Engine_T left_engine;
	Engine_T right_engine;
	
	Line_T left_line;
	Line_T right_line;
	
	Odometrie_T left_odo;
	Odometrie_T right_odo;
	
	unsigned char switches;
}Virtual_Asuro_T;

/*Requestable and setable IDs*/

#define LED_FRONT 0x02						// 1/0
//#define LED_FRONT_DESCR "FrontLED"
//extern char* LED_FRONT_DESCR;//[] = "FrontLED";
#define LED_STATUS 0x04						// rd/gn/off
#define LED_BACK_LEFT 0x06					// 1/0
#define LED_BACK_RIGHT 0x08					// 1/0

#define ENGINE_LEFT 0x2A					// - F/R/B - SPEED - 
#define ENGINE_LEFT_DIR 0x2C
#define ENGINE_LEFT_SPEED 0x2D

#define ENGINE_RIGHT 0x3A					// - F/R/B - SPEED -
#define ENGINE_RIGHT_DIR 0x3C
#define ENGINE_RIGHT_SPEED 0x3D
 
#define	ODOMETRIE_DATA 0x0E			// REQ_ONLY 16BIT
#define LINE_DATA 0x10					// REQ_ONLY 16BIT
//#define	ODOMETRIE_DATA_RIGHT 0x12			// REQ_ONLY 16BIT
//#define LINE_DATA_RIGHT 0x14				// REQ_ONLY 16BIT
#define SWITCH_STATUS 0x16					// REQ_ONLY

#define SEQUENCE_START 0xA8
#define SEQUENCE_STOP 0xAE
#define SEQUENCE_DESCR 0xAD

#define VARIABLE_DATA 0xD0
#define VARIABLE_DATA_DESCR 0xDD 




#define ENG_FWD 0xF2 //Fwd
#define ENG_RWD 0xD2 //rwD
#define ENG_BRK 0xB2 // Brake

#define LED_RED 0xD5
#define LED_GN 0x25

void SetAsuro(unsigned char* data, unsigned char len);
void GetAsuro( unsigned char what , unsigned char* data, unsigned char len);
void InitAsuro();
void PrintAsuroStatus();

typedef void (*DataGatherer_f)(void*);

#define VAR_NAME_LEN 15

typedef struct{
	char _Name[VAR_NAME_LEN]; //> Name of Data 
	unsigned char _ByteSize; //> Size in Bytes 1,2,4
	unsigned char _DataBuffer[4];	//> Buffer
	DataGatherer_f _GetData; //> Call: X._GetData(X._Data);
	unsigned char *_Known_ptr; //> Usable?
}Variable_Data_T;

Variable_Data_T InitVD_(unsigned char* name , unsigned char size , DataGatherer_f fkt);
/*{
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
} */

short WriteIDDescription(unsigned char , unsigned char* ,unsigned char);

#endif /*OBJECT_DEFS_H_*/
