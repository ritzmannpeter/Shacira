/*
 * author schneider
 *
 * This sofware may by copyright protected!
 * 
 */


/** \file
 */

/*The state machine for the framed protokol*/

#include "state_machine.h"

/** \typedef struct Buffer_T
 * 
 *  Buffer Structure!
 */
typedef struct buffer_t{
	/** real size of the data
	 */
	UINT8 buf_ptr;
	/** data array
	 */
	UINT8 data[Data_Len_in_Queue];
}Buffer_T;


/** Local buffer for the state machine
 */
static Buffer_T buffer;
/** holds the actual state of the state machine
 */
static unsigned char _STATE_;
/** locally used pointer to the function used to compute the data of an complete frame
 * 
 * \note Set with InitStateMachine()
 */
static ComputeFrame_f compute_framedata;

/** locally used to reset the buffer
 */
static void ResetBuffer()
{
	UINT8 i;
	buffer.buf_ptr = 0;
	for (i = 0; i < Data_Len_in_Queue; i++) {
	buffer.data[i] = 0;
	}
}

/**	Funktions Pointer zu sende, empfangs routine
 * buffer resetten
 * */

void InitStateMachine(ComputeFrame_f out_q)
{
	compute_framedata = out_q;
	_STATE_ = STATE_IDLE;	
	ResetBuffer();
	
}

#include <stdarg.h>
#include <windows.h>

void DebugConsolePrintf (const char* fmt_str, ... )
{
  //## begin cSystemUtils::DebugConsolePrintf%1076931337.body preserve=yes
#if defined(_WIN32)
   char text[1024] = {0};
//   try {
      va_list args;
      va_start(args, fmt_str);
      vsprintf(text, fmt_str, args);
      va_end(args);
      OutputDebugString(text);
  // } catch (...) {
   //}
#endif
  //## end cSystemUtils::DebugConsolePrintf%1076931337.body
}

int ComputeByte(unsigned char input)
{	
	UINT8 i = 0;
	DebugConsolePrintf("[%0.2X]",(int)input);
	//static Queue_Element_T tmp; not needed get pinter to function which computes complete frame
	switch (_STATE_) {
		case STATE_IDLE:
			if(input == START){
				_STATE_ = STATE_DATA;
				ResetBuffer(buffer);
			}
			break;
			
		case STATE_DATA:
			if(input == START){
				ResetBuffer(buffer);
				break;
			}
			else if(input == ESCAPE){
				_STATE_ = STATE_ESCAPE;
				break;
			}
			else if(input == STOP){
				_STATE_ = STATE_BUSY;
				break;
			}
			else if(buffer.buf_ptr<Data_Len_in_Queue){
				buffer.data[buffer.buf_ptr++] = input;
				i++;
				break; 
			}
			else if(buffer.buf_ptr >= Data_Len_in_Queue){
				_STATE_ = STATE_OVERFLOW;
				break;
			}
			break;
			
		case STATE_ESCAPE:
			if( input == START ){
				ResetBuffer(buffer);
				_STATE_ = STATE_DATA;
				break;
			}
			else if( input == ESCAPE ) break;
			else if(buffer.buf_ptr<Data_Len_in_Queue){
				buffer.data[buffer.buf_ptr++] = input^0x80;/*XOR!!!*/
				
				_STATE_ = STATE_DATA;
				break; 
			}
			else if(buffer.buf_ptr >= Data_Len_in_Queue){
				_STATE_ = STATE_OVERFLOW;
				break;
			}
			break;
		
		case STATE_BUSY:
			SendError(ERR_BUSY);
			/*TO DO*/
			break;
		
		case STATE_OVERFLOW:
			/*SendError*/
			SendError(ERR_BUFFER_OVERFLOW);
			_STATE_ = STATE_IDLE;
			break;
			
		case STATE_TIMEOUT:
			/*SEND ERROR*/
			SendError(ERR_TIMEOUT);
			_STATE_ = STATE_IDLE;
			break;
		default:
			break;

	}
			
	if( _STATE_ == STATE_BUSY){
		/** VERARBEITUNG + _STATE_ = STATE_IDLE
		 * 
		 * buffer in queue einreihen
		 */
		compute_framedata(buffer.data,buffer.buf_ptr);
		ResetBuffer();
//		for(i=0; i < Data_Len_in_Queue ;i++){
//			tmp.Data[i] = buffer->data[i];
//		}
//		AddQueueElement(q,tmp);
		_STATE_ = STATE_IDLE;
	}
	if ( _STATE_ == STATE_TIMEOUT) return -1;/*ERROR*/;
	if ( _STATE_ == STATE_OVERFLOW) return -2;/*ERROR*/;
	return 0;
}
