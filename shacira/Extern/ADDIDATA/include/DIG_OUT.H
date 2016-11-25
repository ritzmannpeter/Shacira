/*
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstraße 3       D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-------------------------------+---------------------------------------+
  | Project     : API  ADDI-DATA  |     Compiler   : BORLANDC/MICROSOFT C |
  | Module name : DIG_OUT.H       |     Version    : 3.1     / 6.0        |
  |                               |                                       |
  |                               |                                       |
  +-------------------------------+---------------------------------------+
  | Author : Hilpert R.                    Date :16/02/2000               |
  +-----------------------------------------------------------------------+
  | Description   : Header file for the ADDI-DATA digital output          |
  |		    funtionality driver                                   |
  +-----------------------------------------------------------------------+
  |                             UPDATES                                   |
  +----------+-----------+------------------------------------------------+
  |   Date   |   Author  |          Description of updates                |
  +----------+-----------+------------------------------------------------+
  |01/01/2001|R. HILPERT | Update for access selected.                    |
  |          |           | Update for access one more boards.             |
  |          |           | Update for interrupt on digital output.        |
  |          |           | Update for hardware interface.                 |
  |          |           | 0800-0200 -> 1200-0205.                        |
  +----------+-----------+------------------------------------------------+
  |30/01/01  | C.Guinot  | 0800/0200 -> 0900/0210                         |
  |          |           | Use BYTE instead of BOOL                       |
  |          |           | Use DWORD instead of BOOL (when used as param.)| 
  +----------+-----------+------------------------------------------------+
  | 15/11/02 | C.Guinot  | 2224/0602 -> 2225/1102                         |
  |          |           | implementation of the FIFO overflow management |
  |          |           | by the interrupt asynchrone Mode               |
  +----------+-----------+------------------------------------------------+
*/


#ifndef ADDIDATA_DIGITAL_OUTPUT_HEADER
   #define ADDIDATA_DIGITAL_OUTPUT_HEADER

   /*************************************************************************/
   /* Dig_inp.c                                                             */
   /*************************************************************************/

   _BYTE_  b_ADDIDATA_GetNumberOfDigitalOutputs 	   (DWORD     dw_DriverHandle,
							    PWORD     pw_NumberOfChannels);

   _BYTE_  b_ADDIDATA_GetDigitalOutputInformation 	   (DWORD dw_DriverHandle,
							   WORD   w_DigitalOutputNumber,
							   PBYTE pb_DigitalOutputType,   
						       PBYTE pb_DigitalOutputInterrupt);

   _BYTE_  b_ADDIDATA_SetDigitalOutputMemoryOn 	     	   (DWORD     dw_DriverHandle);

   _BYTE_  b_ADDIDATA_SetDigitalOutputMemoryOff 	   (DWORD     dw_DriverHandle);

   _BYTE_  b_ADDIDATA_Set1DigitalOutputOn 	     	   (DWORD     dw_DriverHandle,
							    WORD       w_Channel);

   _BYTE_  b_ADDIDATA_Set1DigitalOutputOff 	     	   (DWORD     dw_DriverHandle,
							    WORD       w_Channel);

   _BYTE_  b_ADDIDATA_Set2DigitalOutputsOn 	     	   (DWORD     dw_DriverHandle,
							    BYTE      b_Port,
							    BYTE      b_PortValue);

   _BYTE_  b_ADDIDATA_Set2DigitalOutputsOff 	     	   (DWORD     dw_DriverHandle,
							    BYTE      b_Port,
							    BYTE      b_PortValue);

   _BYTE_  b_ADDIDATA_Set4DigitalOutputsOn 	     	   (DWORD     dw_DriverHandle,
							    BYTE      b_Port,
							    BYTE      b_PortValue);

   _BYTE_  b_ADDIDATA_Set4DigitalOutputsOff 	     	   (DWORD     dw_DriverHandle,
							    BYTE      b_Port,
							    BYTE      b_PortValue);

   _BYTE_  b_ADDIDATA_Set8DigitalOutputsOn 	     	   (DWORD     dw_DriverHandle,
							    BYTE      b_Port,
							    BYTE      b_PortValue);

   _BYTE_  b_ADDIDATA_Set8DigitalOutputsOff 	     	   (DWORD     dw_DriverHandle,
							    BYTE      b_Port,
							    BYTE      b_PortValue);

   _BYTE_  b_ADDIDATA_Set16DigitalOutputsOn 	     	   (DWORD     dw_DriverHandle,
							    BYTE      b_Port,
							    WORD      w_PortValue);

   _BYTE_  b_ADDIDATA_Set16DigitalOutputsOff 	     	   (DWORD     dw_DriverHandle,
							    BYTE      b_Port,
							    WORD      w_PortValue);

   _BYTE_  b_ADDIDATA_Set32DigitalOutputsOn 	     	   (DWORD     dw_DriverHandle,
							    BYTE       b_Port,
							    DWORD      dw_PortValue);

   _BYTE_  b_ADDIDATA_Set32DigitalOutputsOff 	     	   (DWORD     dw_DriverHandle,
							    BYTE       b_Port,
							    DWORD      dw_PortValue);

   _BYTE_  b_ADDIDATA_Get1DigitalOutputStatus 	     	   (DWORD     dw_DriverHandle,
							    WORD       w_Channel,
							    PBYTE      pb_ChannelStatus);

   _BYTE_  b_ADDIDATA_Get2DigitalOutputStatus 	     	   (DWORD     dw_DriverHandle,
							    BYTE       b_Port,
							    PBYTE      pb_PortValue);

   _BYTE_  b_ADDIDATA_Get4DigitalOutputStatus 	     	   (DWORD     dw_DriverHandle,
							    BYTE       b_Port,
							    PBYTE      pb_PortValue);

   _BYTE_  b_ADDIDATA_Get8DigitalOutputStatus 	     	   (DWORD     dw_DriverHandle,
							    BYTE       b_Port,
							    PBYTE      pb_PortValue);

   _BYTE_  b_ADDIDATA_Get16DigitalOutputStatus 	     	   (DWORD     dw_DriverHandle,
							    BYTE       b_Port,
							    PWORD      pw_PortValue);

   _BYTE_  b_ADDIDATA_Get32DigitalOutputStatus 	     	   (DWORD     dw_DriverHandle,
							    BYTE       b_Port,
							    PDWORD      pdw_PortValue);

// BEGIN 01/01/2001 RH 0800-0200 -> 1200-0205
   _BYTE_  b_ADDIDATA_InitDigitalOutputInterrupt	    (DWORD dw_DriverHandle,          
							    WORD     w_FirstDigitalOutput,
							    WORD     w_LastDigitalOutput,
							    BYTE 	b_CCInterruptFlag,			  
							    BYTE 	b_VCCInterruptFlag,			  
							    PDWORD pdw_DigitalOutputArrayForInterruptCC,	  
							    PDWORD pdw_DigitalOutputArrayForInterruptVCC);

   _BYTE_  b_ADDIDATA_ReleaseDigitalOutputInterrupt (DWORD dw_DriverHandle,
							    WORD     w_FirstDigitalOutput,
							    WORD     w_LastDigitalOutput);

   _BYTE_  b_ADDIDATA_EnableDisableDigitalOutputInterrupt 
				 		      (DWORD   dw_DriverHandle,          
				 		       WORD     w_FirstDigitalOutput,
				 		       WORD     w_LastDigitalOutput,
				 		       BYTE 	  b_VCCInterruptFlag,
				 		       BYTE 	  b_CCInterruptFlag);
   // END 01/01/2001 RH 0800-0200 -> 1200-0205

   // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
   _BYTE_ b_ADDIDATA_TestDigitalOutputAsynchronousFIFOFull (DWORD dw_DriverHandle,PBYTE_ pb_Full);
   // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management


#endif