/*
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstraße 3       D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-------------------------------+---------------------------------------+
  | Project     : API  ADDI-DATA  |     Compiler   : BORLANDC/MICROSOFT C |
  | Module name : WATCHDOG.H      |     Version    : 3.1     / 6.0        |
  |                               |                                       |
  |                               |                                       |
  +-------------------------------+---------------------------------------+
  | Author : Weber S.                      Date :15/12/1999               |
  +-----------------------------------------------------------------------+
  | Description   : Header file for the ADDI-DATA watchdog funtionality   |
  |		    driver                                                |
  +-----------------------------------------------------------------------+
  |                             UPDATES                                   |
  +----------+-----------+------------------------------------------------+
  |   Date   |   Author  |          Description of updates                |
  +----------+-----------+------------------------------------------------+
  | 06/11/00 | Guinot C. | 0800/0200 -> 0900/0210                         |
  |          |           | _BYTE_ instead of _BOOL_                       |
  +----------+-----------+------------------------------------------------+
  |09.10.2001| R. HILPERT| 0801-0216 -> 0801-0216                         |
  |	     |		 | (War och nicht freigegeben)                    |
  |	     |		 | b_ConfigurableResetMode implementation         |
  |	     |		 | for the APCI-035.                              |
  +----------+-----------+------------------------------------------------+
  | 15/11/02 | C.Guinot  | 2224/0602 -> 2225/1102                         |
  |          |           | implementation of the FIFO overflow management |
  |          |           | by the interrupt asynchrone Mode               |
  +----------+-----------+------------------------------------------------+
*/


#ifndef ADDIDATA_WATCHDOG_HEADER
   #define ADDIDATA_WATCHDOG_HEADER

   /*************************************************************************/
   /* Error.c                                                               */
   /*************************************************************************/

   _BYTE_  b_ADDIDATA_GetNumberOfWatchdogs                  (DWORD dw_DriverHandle,
							    PBYTE pb_WatchdogNumber,
							    PBYTE pb_WatchdogType);

   _BYTE_  b_ADDIDATA_GetWatchdogInformation               (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber,
							    PBYTE pb_WatchdogTimeUnit,
							    PWORD pw_WatchdogTimeStep,
							    PBYTE pb_Resolution,
							    PDWORD pdw_HardwareGateAvailable,
							    PDWORD pdw_HardwareTriggerAvailable,
							    PDWORD pdw_WarningRelayAvailable,
							    PDWORD pdw_ResetRelayAvailable,
							    PDWORD pdw_WarningDelayAvailable);

//Begin :  |09.10.2001| R. HILPERT| 0801-0216 -> 0801-0216                         |
   _BYTE_  b_ADDIDATA_GetWatchdogInformationEx             (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber,
							    pstr_GetWatchdogInformation ps_WatchdogInformation,
							    DWORD dw_StructSize);
//End :  |09.10.2001| R. HILPERT| 0801-0216 -> 0801-0216                         |

   _BYTE_  b_ADDIDATA_InitWatchdog                         (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber,
							    BYTE   b_WatchdogTimeUnit,
							    DWORD dw_DelayValue);

   _BYTE_  b_ADDIDATA_ReleaseWatchdog                      (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber);

   _BYTE_  b_ADDIDATA_EnableDisableWatchdogInterrupt       (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber,
							    BYTE   b_InterruptFlag);

   _BYTE_  b_ADDIDATA_StartWatchdog                        (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber);

   _BYTE_  b_ADDIDATA_StartAllWatchdogs                     (DWORD dw_DriverHandle);

   _BYTE_  b_ADDIDATA_TriggerWatchdog                      (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber);

   _BYTE_  b_ADDIDATA_TriggerAllWatchdogs                   (DWORD dw_DriverHandle);

   _BYTE_  b_ADDIDATA_StopWatchdog                         (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber);

   _BYTE_  b_ADDIDATA_StopAllWatchdogs                      (DWORD dw_DriverHandle);

   _BYTE_  b_ADDIDATA_ReadWatchdogStatus                   (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber,
							    PBYTE pb_WatchdogStatus,
							    PBYTE pb_SoftwareTriggerStatus,
							    PBYTE pb_HardwareTriggerStatus);

   _BYTE_  b_ADDIDATA_EnableDisableWatchdogHardwareGate    (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber,
							    BYTE   b_HardwareGateFlag,
							    BYTE   b_HardwareGateLevel);

   _BYTE_  b_ADDIDATA_GetWatchdogHardwareGateStatus         (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber,
							    PBYTE pb_HardwareGateStatus);

   _BYTE_  b_ADDIDATA_EnableDisableWatchdogHardwareTrigger (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber,
							    BYTE   b_HardwareTriggerFlag,
							    BYTE   b_HardwareTriggerLevel);

   _BYTE_  b_ADDIDATA_GetWatchdogHardwareTriggerStatus      (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber,
							    PBYTE pb_HardwareTriggerStatus);

   _BYTE_  b_ADDIDATA_GetWarningDelayInformation    	   (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber,
							    PBYTE pb_WarningDelayTimeUnit,
							    PWORD pw_WarningDelayTimeStep,
							    PBYTE pb_WarningResolution);

   _BYTE_  b_ADDIDATA_InitWarningDelay                     (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber,
							    BYTE   b_DelayTimeUnit,
							    DWORD dw_DelayValue);

   _BYTE_  b_ADDIDATA_EnableDisableWatchdogWarningRelay    (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber,
							    BYTE   b_WarningFlag);

   _BYTE_  b_ADDIDATA_EnableDisableWatchdogResetRelay 	   (DWORD dw_DriverHandle,
							    BYTE   b_WatchdogNumber,
							    BYTE   b_ResetFlag);

//Begin :  |09.10.2001| R. HILPERT| 0801-0216 -> 0801-0216                         |
   _BYTE_  b_ADDIDATA_SetWatchdogResetRelayMode 	(DWORD dw_DriverHandle,
							 BYTE   b_WatchdogNumber,
							 BYTE   b_ResetRelayMode);
//End :  |09.10.2001| R. HILPERT| 0801-0216 -> 0801-0216                         |


   // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
   _BYTE_ b_ADDIDATA_TestWatchdogAsynchronousFIFOFull (DWORD dw_DriverHandle,PBYTE_ pb_Full);
   // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
#endif