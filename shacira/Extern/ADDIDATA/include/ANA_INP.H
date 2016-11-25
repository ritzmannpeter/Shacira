/*
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstraße 3       D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-------------------------------+---------------------------------------+
  | Project     : API  ADDI-DATA  |     Compiler   : BORLANDC/MICROSOFT C |
  | Module name : ANA_INP.H       |     Version    : 3.1     / 6.0        |
  |                               |                                       |
  |                               |                                       |
  +-------------------------------+---------------------------------------+
  | Author : Guinot C.                    Date :11/09/2000                |
  +-----------------------------------------------------------------------+
  | Description   : Header file for the ADDI-DATA analog input            |
  |		    funtionality driver                                   |
  +-----------------------------------------------------------------------+
  |                             UPDATES                                   |
  +----------+-----------+------------------------------------------------+
  |   Date   |   Author  |          Description of updates                |
  +----------+-----------+------------------------------------------------+
  |          |           |                                                |
  +----------+-----------+------------------------------------------------+
  | 15/11/02 | C.Guinot  | 2224/0602 -> 2225/1102                         |
  |          |           | implementation of the FIFO overflow management |
  |          |           | by the interrupt asynchrone Mode               |
  +----------+-----------+------------------------------------------------+
*/


#ifndef ADDIDATA_ANALOG_INPUT_HEADER
   #define ADDIDATA_ANALOG_INPUT_HEADER

   /*************************************************************************/
   /* Ana_inp.c                                                             */
   /*************************************************************************/

   _BYTE_ b_ADDIDATA_GetNumberOfAnalogInputs (DWORD dw_DriverHandle,
			                      PWORD pw_ChannelNbr);

   _BYTE_ b_ADDIDATA_GetNumberOfAnalogInputModules (DWORD dw_DriverHandle,
						    PWORD pw_ModuleNbr);

   _BYTE_ b_ADDIDATA_GetNumberOfAnalogInputsForTheModule (DWORD dw_DriverHandle,
						          WORD w_Module,
						          PWORD pw_ChannelNbr);

   _BYTE_ b_ADDIDATA_GetAnalogInputInformation (DWORD dw_DriverHandle,
	    					WORD w_Channel,
						pstr_GetAnalogMesureInformation ps_ChannelInformation,
						DWORD     dw_StructSize);

   _BYTE_ b_ADDIDATA_InitAnalogInput (DWORD dw_DriverHandle,
		  		      WORD w_Channel,
				      pstr_InitAnalogInput ps_InitParameters,
				      DWORD dw_StructSize);

   _BYTE_ b_ADDIDATA_TestAnalogInputShortCircuit  (DWORD dw_DriverHandle, 
   				  		   WORD    w_Channel,
						   BYTE    b_SignTest,
						   DOUBLE d_VoltageValue,
						   PBYTE   pb_ShortCircuit);

   _BYTE_ b_ADDIDATA_TestAnalogInputConnection  (DWORD dw_DriverHandle, 
                                                 WORD    w_Channel,
                                                 BYTE    b_SignTest,
                                                 DOUBLE d_VoltageValue,
                                                 PBYTE   pb_ConnectionStatus);

   _BYTE_ b_ADDIDATA_Read1AnalogInput (DWORD     dw_DriverHandle,
				       WORD       w_Channel,
				       DWORD     dw_ConversionTime,
				       BYTE       b_ConversionTimeUnit,
				       BYTE       b_InterruptFlag,
				       PDWORD   pdw_ChannelValue);

   _BYTE_ b_ADDIDATA_ReadMoreAnalogInputs (DWORD dw_DriverHandle,
					  WORD w_FirstChannel,
					  WORD w_LastChannel,
					  DWORD dw_ConversionTime,
					  BYTE b_ConversionTimeUnit,
					  BYTE b_InterruptFlag,
					  PDWORD pdw_ChannelArrayValue);

   _BYTE_ b_ADDIDATA_ConvertDigitalToRealAnalogValue (DWORD dw_DriverHandle,
                                                      WORD w_Channel,
                                                      PDWORD pdw_DigitalValue,
                                                      DOUBLE *pd_RealValue);
   
   _BYTE_ b_ADDIDATA_ConvertMoreDigitalToRealAnalogValues(DWORD dw_DriverHandle,
                                                          WORD w_FirstChannel,
						          WORD w_LastChannel,
                                                          PDWORD pdw_DigitalValue,
                                                          DOUBLE *pd_RealValue);

   _BYTE_ b_ADDIDATA_InitAnalogInputSCAN (DWORD dw_DriverHandle,
					  pstr_InitAnalogInputSCAN ps_InitParameters,
                                          DWORD dw_StructSize, 
					  PDWORD pdw_SCANHandle);

   _BYTE_ b_ADDIDATA_StartAnalogInputSCAN (DWORD dw_DriverHandle,
                                           DWORD dw_SCANHandle);

   _BYTE_ b_ADDIDATA_GetAnalogInputSCANStatus (DWORD dw_DriverHandle,
                                               DWORD dw_SCANHandle,
                                               PBYTE   pb_SCANStatus);

   _BYTE_ b_ADDIDATA_ConvertDigitalToRealAnalogValueSCAN (DWORD dw_DriverHandle,
                                                          DWORD dw_SCANHandle,
                                                          PDWORD pdw_DigitalValueArray,
                                                          DOUBLE *pd_RealValueArray);

   _BYTE_ b_ADDIDATA_StopAnalogInputSCAN (DWORD dw_DriverHandle,
                                          DWORD dw_SCANHandle);

   _BYTE_ b_ADDIDATA_CloseAnalogInputSCAN (DWORD dw_DriverHandle,
                                           DWORD dw_SCANHandle);

   _BYTE_ b_ADDIDATA_ReleaseAnalogInput	(DWORD dw_DriverHandle,
					 WORD	w_Channel);

   // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
   _BYTE_ b_ADDIDATA_TestAnalogInputAsynchronousFIFOFull (DWORD dw_DriverHandle,PBYTE_ pb_Full);
   // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management


   _BYTE_ b_ADDIDATA_GetAnalogInputModuleNumber			(DWORD     dw_DriverHandle,
								 WORD       w_Channel,
								 PWORD     pw_Module);

   _BYTE_ b_ADDIDATA_GetAnalogInputModuleAutoRefreshInformation	(DWORD                                  dw_DriverHandle,
								 WORD                                    w_Module,
								 pstr_AnalogInputAutoRefreshInformation ps_ModuleInformation,
								 DWORD                                  dw_StructSize);

   _BYTE_ b_ADDIDATA_GetAnalogInputModuleSequenceInformation	(DWORD                              dw_DriverHandle,
								 WORD                                w_Module,
								 pstr_AnalogInputSequenceInformation ps_ModuleInformation,
								 DWORD                              dw_StructSize);

   _BYTE_  b_ADDIDATA_GetAnalogInputAutoRefreshChannelPointer	(DWORD     dw_DriverHandle,
								 WORD       w_Channel,
								 VOID   **ppv_ApplicationLevelPointer,
								 VOID   **ppv_KernelLevelPointer);

   _BYTE_  b_ADDIDATA_GetAnalogInputAutoRefreshModulePointer	(DWORD     dw_DriverHandle,
								 WORD       w_Module,
								 VOID   **ppv_ApplicationLevelPointer,
								 VOID   **ppv_KernelLevelPointer);

   _BYTE_  b_ADDIDATA_StartAnalogInputAutoRefresh		(DWORD     dw_DriverHandle,
								 WORD       w_Module,
								 DWORD     dw_ConversionTime,
								 BYTE       b_ConversionTimeUnit);

   _BYTE_  b_ADDIDATA_StopAnalogInputAutoRefresh		(DWORD     dw_DriverHandle,
								 WORD       w_Module);

   _BYTE_  b_ADDIDATA_Read1AnalogInputAutoRefreshValue		(DWORD   dw_DriverHandle, 
								 WORD     w_Channel,
								 PDWORD pdw_ChannelValue);

   _BYTE_  b_ADDIDATA_InitAnalogInputSequenceAcquisition	(DWORD                                     dw_DriverHandle,
								 DWORD                                     dw_NbrOfChannel,
								 PWORD                                     pw_SequenceChannelArray,
								 pstr_InitAnalogMeasureSequenceAcquisition ps_InitParam,
								 DWORD                                     dw_StructSize,
								 PDWORD                                   pdw_SEQHandle);

   _BYTE_   b_ADDIDATA_StartAnalogInputSequenceAcquisition	(DWORD dw_DriverHandle,
								 DWORD dw_SEQHandle);

   _BYTE_   b_ADDIDATA_PauseAnalogInputSequenceAcquisition	(DWORD dw_DriverHandle,
								 DWORD dw_SEQHandle);

   _BYTE_   b_ADDIDATA_StopAnalogInputSequenceAcquisition	(DWORD dw_DriverHandle,
								 DWORD dw_SEQHandle);

   _BYTE_   b_ADDIDATA_ReleaseAnalogInputSequenceAcquisition	(DWORD dw_DriverHandle,
								 DWORD dw_SEQHandle);

   _BYTE_   b_ADDIDATA_ConvertDigitalToRealAnalogValueSequence	(DWORD   dw_DriverHandle,
								 DWORD   dw_SEQHandle,
								 PDWORD pdw_DigitalValue,
								 DOUBLE *pd_AnalogValue);

   _BYTE_   b_ADDIDATA_GetAnalogInputSequenceAcquisitionHandleStatus	(DWORD   dw_DriverHandle,
									 WORD    w_Module,
									 PBYTE   pb_InitialisationStatus,
									 PDWORD pdw_LastInitialisedSEQHandle,
									 PBYTE   pb_CurrentSEQStatus,
									 PDWORD pdw_CurrentSEQHandle);

   _BYTE_   b_ADDIDATA_GetAnalogInputHardwareTriggerInformation		(DWORD   dw_DriverHandle,
									 WORD     w_Module,
									 PBYTE   pb_LowLevelTrigger,
									 PBYTE   pb_HighLevelTrigger,
									 PBYTE   pb_HardwareTriggerCount,
									 PDWORD pdw_MaxTriggerCountValue);

   _BYTE_   b_ADDIDATA_EnableDisableAnalogInputHardwareTrigger		(DWORD   dw_DriverHandle,
									 WORD     w_Module,
									 BYTE     b_HardwareTriggerFlag,
									 BYTE     b_HardwareTriggerLevel,
									 BYTE     b_HardwareTriggerAction,
									 DWORD   dw_HardwareTriggerCount,
									 DWORD   dw_TimeOut);

   _BYTE_   b_ADDIDATA_GetAnalogInputHardwareTriggerStatus		(DWORD   dw_DriverHandle,
									 WORD     w_Module,
									 PBYTE   pb_HardwareTriggerFlag,
									 PBYTE   pb_HardwareTriggerStatus,
									 PDWORD pdw_HardwareTriggerCount,
									 PBYTE   pb_HardwareTriggerState);

   _BYTE_   b_ADDIDATA_EnableDisableAnalogInputSoftwareTrigger		(DWORD   dw_DriverHandle,
									 WORD     w_Module,
									 BYTE     b_SoftwareTriggerFlag,
									 BYTE     b_SoftwareTriggerAction);

   _BYTE_   b_ADDIDATA_AnalogInputSoftwareTrigger			(DWORD   dw_DriverHandle,
									 WORD     w_Module);

   _BYTE_   b_ADDIDATA_GetAnalogInputSoftwareTriggerStatus		(DWORD   dw_DriverHandle,
									 WORD     w_Module,
									 PBYTE   pb_SoftwareTriggerFlag,
									 PBYTE   pb_SoftwareTriggerStatus);
#endif
