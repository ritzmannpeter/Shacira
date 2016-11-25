/** \file leds.h
 */
 
/*
 * author schneider
 *
 * This sofware may by copyright protected!
 * 
 */

#ifndef LEDS_H_
#define LEDS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "defs.h"
#include <stdio.h>
#include "object_defs.h"

#define LED_FRONT_ 1
#define LED_STATUS_RED_ 2
#define LED_STATUS_GN_ 4
#define LED_BACK_L_ 8
#define LED_BACK_R_ 16


typedef struct{
	UINT8 front;
	UINT8 status_gn;
	UINT8 status_red;
	UINT8 back_l;
	UINT8 back_r;
}LEDStatus_T;

void PrintLEDStatus(LEDStatus_T);

LEDStatus_T SetLEDStatus(UINT8);

UINT8 GetLEDStatus(LEDStatus_T);

#ifdef __cplusplus
}
#endif

#endif /*LEDS_H_*/
