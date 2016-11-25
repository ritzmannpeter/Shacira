/*
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstraße 3       D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-------------------------------+---------------------------------------+
  | Project     : API  ADDI-DATA  |     Compiler   : BORLANDC/MICROSOFT C |
  | Module name : COUNTER.H       |     Version    : 3.1     / 6.0        |
  |                               |                                       |
  |                               |                                       |
  +-------------------------------+---------------------------------------+
  | Author : Weber S.                      Date :01/08/2001               |
  +-----------------------------------------------------------------------+
  | Description   : Header file for the ADDI-DATA counter funtionality    |
  |		    driver                                                |
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


#ifndef ADDIDATA_COUNTER_HEADER
   #define ADDIDATA_COUNTER_HEADER

   /*************************************************************************/
   /* Counter.c                                                             */
   /*************************************************************************/

   _BYTE_  b_ADDIDATA_GetNumberOfCounters                     (DWORD dw_DriverHandle,
							       PBYTE pb_CounterNumber);

   _BYTE_  b_ADDIDATA_GetCounterInformation                   (DWORD   dw_DriverHandle,
							       BYTE     b_CounterNumber,
							       PBYTE   pb_Resolution,
							       PBYTE   pb_InterruptAvailable,
                                                               PDWORD pdw_InputLevelSelection,
							       PDWORD pdw_HardwareGateAvailable,
							       PDWORD pdw_HardwareTriggerAvailable,
							       PDWORD pdw_OutputAvailable,
							       PDWORD pdw_UpDownSelection);

   _BYTE_  b_ADDIDATA_InitCounter                             (DWORD dw_DriverHandle,
							       BYTE   b_CounterNumber,
							       BYTE   b_LevelSelection,
							       DWORD dw_ReloadValue);

   _BYTE_  b_ADDIDATA_SetCounterDirection                     (DWORD dw_DriverHandle,
							       BYTE   b_CounterNumber,
							       BYTE   b_DirectionSelection);

   _BYTE_  b_ADDIDATA_ReleaseCounter                          (DWORD dw_DriverHandle,
							       BYTE   b_CounterNumber);

   _BYTE_  b_ADDIDATA_EnableDisableCounterInterrupt           (DWORD dw_DriverHandle,
							       BYTE   b_CounterNumber,
							       BYTE   b_InterruptFlag);

   _BYTE_  b_ADDIDATA_StartCounter                            (DWORD dw_DriverHandle,
							       BYTE   b_CounterNumber);

   _BYTE_  b_ADDIDATA_StartAllCounters                        (DWORD dw_DriverHandle);

   _BYTE_  b_ADDIDATA_ClearCounter			      (DWORD dw_DriverHandle,
							       BYTE  b_CounterNumber);

   _BYTE_  b_ADDIDATA_TriggerCounter                          (DWORD dw_DriverHandle,
							       BYTE   b_CounterNumber);

   _BYTE_  b_ADDIDATA_TriggerAllCounters                      (DWORD dw_DriverHandle);

   _BYTE_  b_ADDIDATA_StopCounter                             (DWORD dw_DriverHandle,
							       BYTE   b_CounterNumber);

   _BYTE_  b_ADDIDATA_StopAllCounters                         (DWORD dw_DriverHandle);

   _BYTE_  b_ADDIDATA_ReadCounterValue                        (DWORD   dw_DriverHandle,
							       BYTE     b_CounterNumber,
							       PDWORD pdw_CounterValue);

   _BYTE_  b_ADDIDATA_ReadCounterStatus                       (DWORD dw_DriverHandle,
                                                               BYTE   b_CounterNumber,
                                                               PBYTE pb_CounterStatus,
                                                               PBYTE pb_SoftwareTriggerStatus,
                                                               PBYTE pb_HardwareTriggerStatus,
                                                               PBYTE pb_SoftwareClearStatus);

   _BYTE_  b_ADDIDATA_EnableDisableCounterHardwareGate        (DWORD dw_DriverHandle,
							       BYTE   b_CounterNumber,
							       BYTE   b_HardwareGateFlag,
							       BYTE   b_HardwareGateLevel);

   _BYTE_  b_ADDIDATA_GetCounterHardwareGateStatus            (DWORD dw_DriverHandle,
							       BYTE   b_CounterNumber,
							       PBYTE pb_HardwareGateStatus);

   _BYTE_  b_ADDIDATA_EnableDisableCounterHardwareTrigger     (DWORD dw_DriverHandle,
							       BYTE   b_CounterNumber,
							       BYTE   b_HardwareTriggerFlag,
							       BYTE   b_HardwareTriggerLevel);

   _BYTE_  b_ADDIDATA_GetCounterHardwareTriggerStatus         (DWORD dw_DriverHandle,
							       BYTE   b_CounterNumber,
							       PBYTE pb_HardwareTriggerStatus);

   _BYTE_  b_ADDIDATA_EnableDisableCounterHardwareOutput      (DWORD dw_DriverHandle,
							       BYTE   b_CounterNumber,
							       BYTE   b_OutputFlag,
							       BYTE   b_OutputLevel);

   _BYTE_  b_ADDIDATA_GetCounterHardwareOutputStatus	      (DWORD dw_DriverHandle,
							       BYTE   b_CounterNumber,
							       PBYTE pb_HardwareOutputStatus);
   // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
   _BYTE_ b_ADDIDATA_TestCounterAsynchronousFIFOFull (DWORD dw_DriverHandle,PBYTE_ pb_Full);
   // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management

#endif