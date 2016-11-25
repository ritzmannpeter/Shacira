/*
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstraﬂe 3       D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-------------------------------+---------------------------------------+
  | Project     : API  ADDI-DATA  |     Compiler   : BORLANDC/MICROSOFT C |
  | Module name : TRANSDUCER.H    |     Version    : 3.1     / 6.0        |
  |                               |                                       |
  |                               |                                       |
  +-------------------------------+---------------------------------------+
  | Author : S. Weber                     Date :15/10/2002                |
  +-----------------------------------------------------------------------+
  | Description   : Header file for the ADDI-DATA transducer              |
  |		    funtionality driver                                   |
  +-----------------------------------------------------------------------+
  |                             UPDATES                                   |
  +----------+-----------+------------------------------------------------+
  |   Date   |   Author  |          Description of updates                |
  +----------+-----------+------------------------------------------------+
  |          |           |                                                |
  +----------+-----------+------------------------------------------------+
*/


#ifndef ADDIDATA_TRANSDUCER_HEADER
   #define ADDIDATA_TRANSDUCER_HEADER

   /*************************************************************************/
   /* Transducer.c                                                          */
   /*************************************************************************/

   _BYTE_ b_ADDIDATA_GetNumberOfTransducerChannels				(DWORD dw_DriverHandle,
										 PWORD pw_ChannelNbr);

   _BYTE_ b_ADDIDATA_GetNumberOfTransducerModules				(DWORD dw_DriverHandle,
										 PWORD pw_ModuleNbr);

   _BYTE_ b_ADDIDATA_GetNumberOfTransducerChannelsForTheModule			(DWORD dw_DriverHandle,
										 WORD   w_Module,
										 PWORD pw_ChannelNbr);

   _BYTE_ b_ADDIDATA_GetTransducerChannelModuleNumber				(DWORD dw_DriverHandle,
										 WORD   w_Channel,
										 PWORD pw_Module);

   _BYTE_ b_ADDIDATA_GetTransducerModuleGeneralInformation			(DWORD                            dw_DriverHandle,
										 WORD                              w_Module,
										 pstr_TransducerModuleInformation ps_ModuleInformation,
										 DWORD                            dw_StructSize);

   _BYTE_ b_ADDIDATA_GetTransducerModuleSingleAcquisitionInformation		(DWORD                                       dw_DriverHandle,
										 WORD                                         w_Module,
										 pstr_TransducerSingleAcquisitionInformation ps_ModuleInformation,
										 DWORD                                       dw_StructSize);

   _BYTE_ b_ADDIDATA_GetTransducerModuleAutoRefreshInformation			(DWORD                                 dw_DriverHandle,
										 WORD                                   w_Module,
										 pstr_TransducerAutoRefreshInformation ps_ModuleInformation,
										 DWORD                                 dw_StructSize);

   _BYTE_ b_ADDIDATA_GetTransducerModuleSequenceInformation			(DWORD                              dw_DriverHandle,
										 WORD                                w_Module,
										 pstr_TransducerSequenceInformation ps_ModuleInformation,
										 DWORD                              dw_StructSize);

   _BYTE_ b_ADDIDATA_GetTransducerModuleConvertTimeDivisionFactorInformation    (DWORD                                               dw_DriverHandle,
                                                                                 WORD                                                 w_Module,
                                                                                 pstr_TransducerConvertTimeDivisionFactorInformation ps_ModuleInformation,
                                                                                 DWORD                                               dw_StructSize);

   _BYTE_ b_ADDIDATA_InitTransducerChannel					(DWORD     dw_DriverHandle,
										 WORD       w_Channel,
										 WORD       w_TransducerIndex,
										 DOUBLE     d_Frequency);

   _BYTE_ b_ADDIDATA_InitTransducerModuleConvertTimeDivisionFactor              (DWORD     dw_DriverHandle,
										 WORD       w_Module,
										 DWORD     dw_ConvertTimeDivisionFactor);

   _BYTE_ b_ADDIDATA_ReleaseTransducerChannel					(DWORD dw_DriverHandle,
										 WORD   w_Channel);


   _BYTE_ b_ADDIDATA_ReleaseTransducerModuleConvertTimeDivisionFactor		(DWORD dw_DriverHandle,
										 WORD   w_Module);

   _BYTE_ b_ADDIDATA_Read1TransducerChannel					(DWORD     dw_DriverHandle,
										 WORD       w_Channel,
										 BYTE       b_InterruptFlag,
										 PDWORD   pdw_ChannelValue);

   _BYTE_ b_ADDIDATA_ConvertDigitalToRealMetricValue				(DWORD    dw_DriverHandle,
										 WORD      w_ChannelNbr,
										 PDWORD  pdw_DigitalValue,
										 DOUBLE * pd_MetricValue);

   _BYTE_ b_ADDIDATA_ReadMoreTransducerChannels					(DWORD   dw_DriverHandle,
										 WORD     w_FirstChannel,
										 WORD     w_LastChannel,
										 BYTE     b_InterruptFlag,
										 PDWORD pdw_ChannelArrayValue);

   _BYTE_ b_ADDIDATA_ConvertMoreDigitalToRealMetricValue			(DWORD    dw_DriverHandle,
										 WORD      w_FirstChannel,
										 WORD      w_LastChannel,
										 PDWORD  pdw_DigitalValue,
										 DOUBLE * pd_MetricValue);

   _BYTE_ b_ADDIDATA_GetTransducerHardwareTriggerInformation			(DWORD   dw_DriverHandle,
										 WORD     w_Module,
										 PBYTE   pb_LowLevelTrigger,
										 PBYTE   pb_HighLevelTrigger,
										 PBYTE   pb_HardwareTriggerCount,
										 PDWORD pdw_MaxTriggerCountValue);

   _BYTE_ b_ADDIDATA_EnableDisableTransducerHardwareTrigger			(DWORD   dw_DriverHandle,
										 WORD     w_Module,
										 BYTE     b_HardwareTriggerFlag,
										 BYTE     b_HardwareTriggerLevel,
										 BYTE     b_HardwareTriggerAction,
										 DWORD   dw_HardwareTriggerCount,
										 DWORD   dw_TimeOut);

   _BYTE_ b_ADDIDATA_GetTransducerHardwareTriggerStatus				(DWORD   dw_DriverHandle,
										 WORD     w_Module,
										 PBYTE   pb_HardwareTriggerFlag,
										 PBYTE   pb_HardwareTriggerStatus,
										 PDWORD pdw_HardwareTriggerCount,
										 PBYTE   pb_HardwareTriggerState);

   _BYTE_ b_ADDIDATA_EnableDisableTransducerSoftwareTrigger			(DWORD   dw_DriverHandle,
										 WORD     w_Module,
										 BYTE     b_SoftwareTriggerFlag,
										 BYTE     b_SoftwareTriggerAction);

   _BYTE_ b_ADDIDATA_TransducerSoftwareTrigger					(DWORD   dw_DriverHandle,
										 WORD     w_Module);

   _BYTE_ b_ADDIDATA_GetTransducerSoftwareTriggerStatus				(DWORD   dw_DriverHandle,
										 WORD     w_Module,
										 PBYTE   pb_SoftwareTriggerFlag,
										 PBYTE   pb_SoftwareTriggerStatus);

   _BYTE_ b_ADDIDATA_GetTransducerHardwareGateInformation			(DWORD   dw_DriverHandle,
										 WORD     w_Module,
										 PBYTE   pb_LowLevelGate,
										 PBYTE   pb_HighLevelGate);

   _BYTE_ b_ADDIDATA_EnableDisableTransducerHardwareGate			(DWORD   dw_DriverHandle,
										 WORD     w_Module,
										 BYTE     b_HardwareGateFlag,
										 BYTE     b_HardwareGateLevel);

   _BYTE_ b_ADDIDATA_GetTransducerHardwareGateStatus				(DWORD   dw_DriverHandle,
										 WORD     w_Module,
										 PBYTE   pb_HardwareGateFlag,
										 PBYTE   pb_HardwareGateState);

   _BYTE_ b_ADDIDATA_TestTransducerChannelSecondaryConnection			(DWORD     dw_DriverHandle,
										 WORD       w_Channel,
										 PBYTE     pb_ShortCircuit,
										 PBYTE     pb_Connection);

   _BYTE_ b_ADDIDATA_EnableDisableTransducerModulePrimaryConnectionTest		(DWORD   dw_DriverHandle,
										 WORD     w_Module,
										 BYTE     b_TestFlag);

   _BYTE_ b_ADDIDATA_TestTransducerModulePrimaryConnection			(DWORD     dw_DriverHandle,
										 WORD       w_Module,
										 PBYTE     pb_TestFlag,
										 PBYTE     pb_ShortCircuit,
										 PBYTE     pb_Connection);

   _BYTE_ b_ADDIDATA_EnableDisableTransducerModulePrimaryShortCircuitInterrupt	(DWORD   dw_DriverHandle,
										 WORD     w_Module,
										 BYTE     b_InterruptFlag);

   _BYTE_ b_ADDIDATA_RearmTransducerModulePrimaryShortCircuitConnectionTest     (DWORD   dw_DriverHandle,
										 WORD     w_Module);

   _BYTE_ b_ADDIDATA_InitTransducerSequenceAcquisition				(DWORD                                     dw_DriverHandle,
										 DWORD                                     dw_NbrOfChannel,
										 PWORD                                     pw_SequenceChannelArray,
										 pstr_InitAnalogMeasureSequenceAcquisition ps_InitParam,
										 DWORD                                     dw_StructSize,
										 PDWORD                                   pdw_SEQHandle);

   _BYTE_ b_ADDIDATA_StartTransducerSequenceAcquisition				(DWORD dw_DriverHandle,
										 DWORD dw_SEQHandle);

   _BYTE_ b_ADDIDATA_PauseTransducerSequenceAcquisition				(DWORD dw_DriverHandle,
										 DWORD dw_SEQHandle);

   _BYTE_ b_ADDIDATA_StopTransducerSequenceAcquisition				(DWORD dw_DriverHandle,
										 DWORD dw_SEQHandle);

   _BYTE_ b_ADDIDATA_ReleaseTransducerSequenceAcquisition			(DWORD dw_DriverHandle,
										 DWORD dw_SEQHandle);

   _BYTE_ b_ADDIDATA_ConvertTransducerSequenceDigitalToRealMetricValue		(DWORD   dw_DriverHandle,
										 DWORD   dw_SEQHandle,
										 PDWORD pdw_DigitalValue,
										 DOUBLE *pd_MetricValue);

   _BYTE_   b_ADDIDATA_GetTransducerSequenceAcquisitionHandleStatus		(DWORD   dw_DriverHandle,
										 WORD    w_Module,
										 PBYTE   pb_InitialisationStatus,
										 PDWORD pdw_LastInitialisedSEQHandle,
										 PBYTE   pb_CurrentSEQStatus,
										 PDWORD pdw_CurrentSEQHandle);

   _BYTE_   b_ADDIDATA_GetTransducerAutoRefreshChannelPointer			(DWORD     dw_DriverHandle,
										 WORD       w_Channel,
										 VOID   **ppv_ApplicationLevelPointer,
										 VOID   **ppv_KernelLevelPointer);

   _BYTE_   b_ADDIDATA_GetTransducerAutoRefreshModulePointer			(DWORD     dw_DriverHandle,
										 WORD       w_Module,
										 VOID   **ppv_ApplicationLevelPointer,
										 VOID   **ppv_KernelLevelPointer);

   _BYTE_   b_ADDIDATA_GetTransducerAutoRefreshModuleCounterPointer		(DWORD     dw_DriverHandle,
										 WORD       w_Module,
										 VOID   **ppv_ApplicationLevelPointer,
										 VOID   **ppv_KernelLevelPointer);

   _BYTE_   b_ADDIDATA_StartTransducerAutoRefresh				(DWORD     dw_DriverHandle,
										 WORD       w_Module);


   _BYTE_   b_ADDIDATA_StopTransducerAutoRefresh				(DWORD     dw_DriverHandle,
										 WORD       w_Module);

#endif