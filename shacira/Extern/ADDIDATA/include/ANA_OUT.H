/*
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstraße 3       D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-------------------------------+---------------------------------------+
  | Project     : API  ADDI-DATA  |     Compiler   : BORLANDC/MICROSOFT C |
  | Module name : ANA_OUT.H       |     Version    : 3.1     / 6.0        |
  |                               |                                       |
  |                               |                                       |
  +-------------------------------+---------------------------------------+
  | Author : Hilpert R.                    Date :16/02/2000               |
  +-----------------------------------------------------------------------+
  | Description   : Header file for the ADDI-DATA analog output           |
  |		    funtionality driver                                   |
  +-----------------------------------------------------------------------+
  |                             UPDATES                                   |
  +----------+-----------+------------------------------------------------+
  |   Date   |   Author  |          Description of updates                |
  +----------+-----------+------------------------------------------------+
  | 06/11/00 | Guinot C. | 0800/0200 -> 0900/0210                         |
  |          |           | _BYTE_ instead of _BOOL_                       |
  |          |           | DWORD instead of BOOL (when used as parameter) |
  +----------+-----------+------------------------------------------------+
*/


#ifndef ADDIDATA_ANALOG_OUTPUT_HEADER
   #define ADDIDATA_ANALOG_OUTPUT_HEADER

   /*************************************************************************/
   /* Ana_out.c                                                             */
   /*************************************************************************/

   _BYTE_  b_ADDIDATA_GetNumberOfAnalogOutputs 	     	   (DWORD     dw_DriverHandle,
							    PWORD     pw_NumberOfChannels,
							    PBYTE     pb_AnalogOutputType);

   _BYTE_  b_ADDIDATA_GetAnalogOutputInformation     	   (DWORD     dw_DriverHandle,
							    WORD      w_ChannelNumber,
							    PBYTE     pb_NumberOfVoltageMode,
							    PBYTE     pb_HighRange,
							    PBYTE     pb_LowRange,
							    PBYTE     pb_SWPolarity,
							    PBYTE     pb_HWPolarity,
							    PBYTE     pb_Resolution,
							    PDWORD    pdw_Synchronisation);

   _BYTE_  b_ADDIDATA_Init1AnalogOutput     	   (DWORD     dw_DriverHandle,
						    WORD      w_ChannelNumber,
						    BYTE      b_VoltageMode,
						    BYTE      b_Polarity);

   _BYTE_  b_ADDIDATA_InitMoreAnalogOutputs     	   (DWORD     dw_DriverHandle,
						    WORD      w_NumberOfChannels,
						    PWORD     pw_ChannelNumber,
						    PBYTE     pb_VoltageMode,
						    PBYTE     pb_Polarity);

   _BYTE_  b_ADDIDATA_Write1AnalogOutput     	   (DWORD     dw_DriverHandle,
						    WORD      w_ChannelNumber,
						    DWORD     dw_ValueToWrite);

   _BYTE_  b_ADDIDATA_WriteMoreAnalogOutputs    	   (DWORD     dw_DriverHandle,
						    WORD      w_NumberOfChannels,
						    PWORD     pw_ChannelNumber,
						    PDWORD    pdw_ValueToWrite);

   _BYTE_  b_ADDIDATA_Release1AnalogOutput     	   (DWORD     dw_DriverHandle,
						    WORD      w_ChannelNumber);

   _BYTE_  b_ADDIDATA_ReleaseMoreAnalogOutputs  	   (DWORD     dw_DriverHandle,
						    WORD      w_NumberOfChannels,
						    PWORD     pw_ChannelNumber);

   _BYTE_  b_ADDIDATA_EnableDisable1AnalogOutputSync   (DWORD     dw_DriverHandle,
							WORD      w_ChannelNumber,
							DWORD      dw_EnableDisableSynchronisation);

   _BYTE_  b_ADDIDATA_EnableDisableMoreAnalogOutputsSync   (DWORD     dw_DriverHandle,
							  WORD      w_NumberOfChannels,
							  PWORD     pw_ChannelNumber,
							  PDWORD     pdw_EnableDisableSynchronisation);

   _BYTE_  b_ADDIDATA_TriggerAnalogOutput 	     	   (DWORD     dw_DriverHandle);

#endif