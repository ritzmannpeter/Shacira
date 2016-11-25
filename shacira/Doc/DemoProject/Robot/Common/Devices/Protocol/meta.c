/*
 * author schneider
 *
 * This sofware may by copyright protected!
 * 
 */


/** \file
 */

#include "meta.h"


void SetCommunication(SendByte_f send_fkt , RecByte_f rec_fkt)
{
	SendByte=send_fkt;
	RecByte=rec_fkt;
}


void SendStream(UINT8* stream, UINT8 len)
{
	UINT8 i;
	SendByte(START);
	for(i=0;i<len;i++)
	{
		if( stream[i] == START || stream[i] == STOP || stream[i] == ESCAPE)
		{
			SendByte(ESCAPE);
			SendByte(stream[i]^0x80);
		}
		else
		{
			SendByte(stream[i]);
		}
	}
	SendByte(STOP);
}

void SendString(UINT8* stream)
{
	SendByte(START);
	while(*stream)
	{
		if( *stream == START || *stream == STOP || *stream == ESCAPE)
		{
			SendByte(ESCAPE);
			SendByte( *(stream++)^0x80 ); 
		}
		else
		{
			SendByte( *(stream++) );
		}
	}
	SendByte(STOP);
}



void SendError(UINT8 errorcode)
{
	UINT8 error[2];
	error[0] = ERROR_RESPONSE;
	error[1] = errorcode;
	SendStream(error,2);
}

void SendFromOutQueue()
{
	unsigned char *c,l;
	c=GetFromOutQueue(&l);
	if( (l) && (c) ) SendStream(c,l);
}
