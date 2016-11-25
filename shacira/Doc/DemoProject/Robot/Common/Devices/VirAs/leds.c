/*
 * author schneider
 *
 * This sofware may by copyright protected!
 * 
 */

/** \file leds.c
 */
 
#include "leds.h"

void PrintLEDStatus(LEDStatus_T s)
{
	printf("\n Status der LEDS:");
	printf("\n=================");
	printf("\nFront       :\t %d", s.front);
	printf("\nStatus green:\t %d", s.status_gn);
	printf("\nStatus red  :\t %d", s.status_red);
	printf("\nBack left   :\t %d", s.back_l);
	printf("\nBack right  :\t %d\n", s.back_r);
}

LEDStatus_T SetLEDStatus(UINT8 r)
{
	LEDStatus_T tmp = {0};
	if(r & LED_FRONT_) tmp.front = 1;
	else tmp.front = 0;
	
	if(r & LED_STATUS_GN_) tmp.status_gn = 1;
	else tmp.status_gn = 0;
	
	if(r & LED_STATUS_RED_) tmp.status_red = 1;
	else tmp.status_red =0;
	
	if(r & LED_BACK_L_) tmp.back_l = 1;
	else tmp.back_l = 0;
	
	if(r & LED_BACK_R_) tmp.back_r = 1;
	else tmp.back_r = 0;
	
	return tmp;
}

UINT8 GetLEDStatus(LEDStatus_T s)
{
	UINT8 r = 0;
	if(s.front == 1) r += LED_FRONT_;
	if(s.status_gn == 1) r += LED_STATUS_GN_;
	if(s.status_red == 1) r += LED_STATUS_RED_;
	if(s.back_l == 1) r += LED_BACK_L_;
	if(s.back_r == 1) r += LED_BACK_R_;
	return r;
}
