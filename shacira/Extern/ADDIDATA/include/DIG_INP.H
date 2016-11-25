/*
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstraße 3       D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-------------------------------+---------------------------------------+
  | Project     : API  ADDI-DATA  |     Compiler   : BORLANDC/MICROSOFT C |
  | Module name : DIG_INP.H       |     Version    : 3.1     / 6.0        |
  |                               |                                       |
  |                               |                                       |
  +-------------------------------+---------------------------------------+
  | Author : Hilpert R.                    Date :16/02/2000               |
  +-----------------------------------------------------------------------+
  | Description   : Header file for the ADDI-DATA digital input           |
  |		    funtionality driver                                   |
  +-----------------------------------------------------------------------+
  |                             UPDATES                                   |
  +----------+-----------+------------------------------------------------+
  |   Date   |   Author  |          Description of updates                |
  +----------+-----------+------------------------------------------------+
  |01/01/2001|R. HILPERT | Update for access selected.                    |
  |          |           | Update for access one more boards.             |
  |          |           | Update for interrupt on digital input.         |
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


#ifndef ADDIDATA_DIGITAL_INPUT_HEADER
   #define ADDIDATA_DIGITAL_INPUT_HEADER

   /*************************************************************************/
   /* Dig_inp.c                                                             */
   /*************************************************************************/

   _BYTE_  b_ADDIDATA_GetNumberOfDigitalInputs 	     	   (DWORD     dw_DriverHandle,
							    PWORD     pw_NumberOfChannels);

   _BYTE_  b_ADDIDATA_GetDigitalInputInformation 	   (DWORD dw_DriverHandle,
							   WORD   w_DigitalInputNumber,
							   PBYTE pb_DigitalInputType,
							   PDWORD pdw_DigitalInputInterrupt);

   _BYTE_  b_ADDIDATA_Read1DigitalInput 	     	   (DWORD     dw_DriverHandle,
							    WORD       w_Channel,
							    PBYTE      pb_ChannelStatus);

   _BYTE_  b_ADDIDATA_Read2DigitalInputs 	     	   (DWORD     dw_DriverHandle,
							    BYTE       b_Port,
							    PBYTE      pb_PortValue);

   _BYTE_  b_ADDIDATA_Read4DigitalInputs 	     	   (DWORD     dw_DriverHandle,
							    BYTE       b_Port,
							    PBYTE      pb_PortValue);

   _BYTE_  b_ADDIDATA_Read8DigitalInputs 	     	   (DWORD     dw_DriverHandle,
							    BYTE       b_Port,
							    PBYTE      pb_PortValue);

   _BYTE_  b_ADDIDATA_Read16DigitalInputs 	     	   (DWORD     dw_DriverHandle,
							    BYTE       b_Port,
							    PWORD      pw_PortValue);

   _BYTE_  b_ADDIDATA_Read32DigitalInputs 	     	   (DWORD     dw_DriverHandle,
							    BYTE       b_Port,
							    PDWORD      pdw_PortValue);


// BEGIN 01/01/2001 RH 0800-0200 -> 1200-0205
   _BYTE_  b_ADDIDATA_InitDigitalInputInterrupt       (DWORD   dw_DriverHandle,          
				 		       WORD     w_FirstDigitalInput,
				 		       WORD     w_LastDigitalInput,
				 		       BYTE     b_InterruptLogic,
				 		       PDWORD pdw_InterruptMaskMode1,  
				 		       PDWORD pdw_InterruptMaskMode2);

   _BYTE_  b_ADDIDATA_ReleaseDigitalInputInterrupt (DWORD dw_DriverHandle,
						    WORD   w_FirstDigitalInput,
						    WORD   w_LastDigitalInput);

   _BYTE_  b_ADDIDATA_EnableDisableDigitalInputInterrupt 
				 		     (DWORD dw_DriverHandle,          
						      WORD   w_FirstDigitalInput,
						      WORD   w_LastDigitalInput,
						      BYTE   b_InterruptFlag);

// END 01/01/2001 RH 0800-0200 -> 1200-0205

   _BYTE_  b_ADDIDATA_GetDigitalInputInformationEx		(DWORD                            dw_DriverHandle,
								 WORD                             w_DigitalInputNumber,      
								 pstr_GetDigitalInputInformation  ps_DigitalInputInformation,
								 DWORD                            dw_StructSize);

   _BYTE_  b_ADDIDATA_Init1DigitalInputLevel			(DWORD   dw_DriverHandle,
								 WORD     w_DigitalInput,   
								 DOUBLE *pd_VoltageValueArray);

   _BYTE_  b_ADDIDATA_SaveDigitalInputModuleLevel               (DWORD   dw_DriverHandle,
                                                                 DWORD   dw_ModuleNumber);

   _BYTE_  b_ADDIDATA_Read1DigitalInputStatus			(DWORD dw_DriverHandle,
								 WORD   w_Channel,
								 PWORD pw_ChannelStatus);

   _BYTE_  b_ADDIDATA_ReadMoreDigitalInputStatus		(DWORD dw_DriverHandle,
								 WORD   w_NbrOfChannel,
								 PWORD pw_ChannelArray,
								 PWORD pw_ChannelStatusArray);

   _BYTE_  b_ADDIDATA_Read1DigitalInputValue			(DWORD   dw_DriverHandle,
								 WORD     w_Channel,
								 PWORD   pw_ChannelStatus,
								 PDWORD pdw_ChannelValue);

   _BYTE_  b_ADDIDATA_ReadMoreDigitalInputValue			(DWORD   dw_DriverHandle,
								 WORD     w_NbrOfChannel, 
								 PWORD   pw_ChannelArray,
								 PWORD   pw_ChannelStatusArray,
								 PDWORD pdw_ChannelValueArray);

   _BYTE_  b_ADDIDATA_Convert1DigitalInputValueInAnalogValue	(DWORD   dw_DriverHandle,
								 WORD     w_Channel,
								 DWORD   dw_DigitalValue,
								 DOUBLE *pd_AnalogValue);

   _BYTE_  b_ADDIDATA_GetDigitalInputModuleFilterInformation	(DWORD                           dw_DriverHandle,
								 DWORD                           dw_ModuleNumber,
								 DWORD                           dw_StructSize,
								 pstr_DigitalInputModuleFilterInf ps_DigitalInputModuleFilterInf);

   _BYTE_  b_ADDIDATA_InitDigitalInputModuleFilter		(DWORD dw_DriverHandle,
								 DWORD dw_ModuleNumber,
								 BYTE   b_DelayTimeUnit,
								 DWORD dw_DelayValue);

   _BYTE_  b_ADDIDATA_EnableDisableDigitalInputModuleFilter	(DWORD dw_DriverHandle,
								 DWORD dw_ModuleNumber,
								 BYTE   b_FilterFlag);

   _BYTE_  b_ADDIDATA_SetDigitalInputModuleLevelSelection	(DWORD dw_DriverHandle,
								 DWORD dw_ModuleNumber,
								 BYTE   b_LevelFlag);
   
   // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
   _BYTE_ b_ADDIDATA_TestDigitalInputAsynchronousFIFOFull (DWORD dw_DriverHandle,PBYTE_ pb_Full);
   // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management

#endif