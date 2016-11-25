/*
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstraße 3       D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-------------------------------+---------------------------------------+
  | Project     : API  ADDI-DATA  |     Compiler   : BORLANDC/MICROSOFT C |
  | Module name : TIMER.H         |     Version    : 3.1     / 6.0        |
  |                               |                                       |
  |                               |                                       |
  +-------------------------------+---------------------------------------+
  | Author : Weber S.                      Date :14/12/1999               |
  +-----------------------------------------------------------------------+
  | Description   : Header file for the ADDI-DATA timer funtionality      |
  |		    driver                                                |
  +-----------------------------------------------------------------------+
  |                             UPDATES                                   |
  +----------+-----------+------------------------------------------------+
  |   Date   |   Author  |          Description of updates                |
  +----------+-----------+------------------------------------------------+
  | 06/11/00 | Guinot C. | 0800/0200 -> 0900/0210                         |
  |          |           | _BYTE_ instead of _BOOL_                       |
  +----------+-----------+------------------------------------------------+
  | 15/11/02 | C.Guinot  | 2224/0602 -> 2225/1102                         |
  |          |           | implementation of the FIFO overflow management |
  |          |           | by the interrupt asynchrone Mode               |
  +----------+-----------+------------------------------------------------+
 */


#ifndef ADDIDATA_TIMER_HEADER
   #define ADDIDATA_TIMER_HEADER

   /*************************************************************************/
   /* Error.c                                                               */
   /*************************************************************************/

   _BYTE_  b_ADDIDATA_GetNumberOfTimers                     (DWORD dw_DriverHandle,
							    PBYTE pb_TimerNumber);

   _BYTE_  b_ADDIDATA_GetTimerInformation                  (DWORD dw_DriverHandle,
							    BYTE   b_TimerNumber,
							    PBYTE pb_TimerMode,
							    PBYTE pb_TimerTimeUnit,
							    PWORD pw_TimerTimeStep,
							    PBYTE pb_Resolution,
							    PDWORD pdw_HardwareGateAvailable,
							    PDWORD pdw_HardwareTriggerAvailable,
							    PDWORD pdw_OutputAvailable);

   _BYTE_  b_ADDIDATA_InitTimer                            (DWORD dw_DriverHandle,
							    BYTE   b_TimerNumber,
							    BYTE   b_TimerMode,
							    BYTE   b_TimerTimeUnit,
							    DWORD dw_ReloadValue);

   _BYTE_  b_ADDIDATA_ReleaseTimer                         (DWORD dw_DriverHandle,
							    BYTE   b_TimerNumber);

   _BYTE_  b_ADDIDATA_EnableDisableTimerInterrupt          (DWORD dw_DriverHandle,
							    BYTE   b_TimerNumber,
							    BYTE   b_InterruptFlag);

   _BYTE_  b_ADDIDATA_StartTimer                           (DWORD dw_DriverHandle,
							    BYTE   b_TimerNumber);

   _BYTE_  b_ADDIDATA_StartAllTimers                        (DWORD dw_DriverHandle);

   _BYTE_  b_ADDIDATA_TriggerTimer                         (DWORD dw_DriverHandle,
							    BYTE   b_TimerNumber);

   _BYTE_  b_ADDIDATA_TriggerAllTimers                      (DWORD dw_DriverHandle);

   _BYTE_  b_ADDIDATA_StopTimer                            (DWORD dw_DriverHandle,
							    BYTE   b_TimerNumber);

   _BYTE_  b_ADDIDATA_StopAllTimers                         (DWORD dw_DriverHandle);

   _BYTE_  b_ADDIDATA_ReadTimerValue                       (DWORD   dw_DriverHandle,
							    BYTE     b_TimerNumber,
							    PDWORD pdw_TimerValue);

   _BYTE_  b_ADDIDATA_ReadTimerStatus                      (DWORD dw_DriverHandle,
							    BYTE   b_TimerNumber,
							    PBYTE pb_TimerStatus,
							    PBYTE pb_SoftwareTriggerStatus,
							    PBYTE pb_HardwareTriggerStatus);

   _BYTE_  b_ADDIDATA_EnableDisableTimerHardwareGate       (DWORD dw_DriverHandle,
							    BYTE   b_TimerNumber,
							    BYTE   b_HardwareGateFlag,
							    BYTE   b_HardwareGateLevel);

   _BYTE_  b_ADDIDATA_GetTimerHardwareGateStatus            (DWORD dw_DriverHandle,
							    BYTE   b_TimerNumber,
							    PBYTE pb_HardwareGateStatus);

   _BYTE_  b_ADDIDATA_EnableDisableTimerHardwareTrigger    (DWORD dw_DriverHandle,
							    BYTE   b_TimerNumber,
							    BYTE   b_HardwareTriggerFlag,
							    BYTE   b_HardwareTriggerLevel);

   _BYTE_  b_ADDIDATA_GetTimerHardwareTriggerStatus         (DWORD dw_DriverHandle,
							    BYTE   b_TimerNumber,
							    PBYTE pb_HardwareTriggerStatus);

   _BYTE_  b_ADDIDATA_EnableDisableTimerHardwareOutput             (DWORD dw_DriverHandle,
							    BYTE   b_TimerNumber,
							    BYTE   b_OutputFlag,
							    BYTE   b_OutputLevel);

   _BYTE_  b_ADDIDATA_GetTimerHardwareOutputStatus	   (DWORD dw_DriverHandle,
							    BYTE   b_TimerNumber,
							    PBYTE pb_HardwareOutputStatus);
   
   // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
   _BYTE_ b_ADDIDATA_TestTimerAsynchronousFIFOFull (DWORD dw_DriverHandle,PBYTE_ pb_Full);
   // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
#endif