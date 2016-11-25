/*
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstraße 3       D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-------------------------------+---------------------------------------+
  | Project     : API  ADDI-DATA  |     Compiler   : BORLANDC/MICROSOFT C |
  | Module name : INTER.H         |     Version    : 3.1     / 6.0        |
  |                               |                                       |
  |                               |                                       |
  +-------------------------------+---------------------------------------+
  | Author : Weber S.                      Date :17/12/1999               |
  +-----------------------------------------------------------------------+
  | Description   : Header file for the ADDI-DATA interrupt funtionality  |
  |		    driver                                                |
  +-----------------------------------------------------------------------+
  |                             UPDATES                                   |
  +----------+-----------+------------------------------------------------+
  |   Date   |   Author  |          Description of updates                |
  +----------+-----------+------------------------------------------------+
  | 06/11/00 | Guinot C. | 0800/0200 -> 0900/0210 BYTE instead of BOOL    |
  +----------+-----------+------------------------------------------------+
*/


#ifndef ADDIDATA_INTERRUPT_HEADER
   #define ADDIDATA_INTERRUPT_HEADER


   /*************************************************************************/
   /* Inter.c                                                               */
   /*************************************************************************/

   _BYTE_   b_ADDIDATA_SetFunctionalityIntRoutineWin32     (DWORD     dw_DriverHandle,
							    DWORD     dw_Functionality,
							    BYTE       b_UserCallingMode,
							    BYTE       b_SharedMemoryMode,
							    DWORD     dw_UserSharedMemorySize,
							    VOID **  ppv_UserSharedMemory,
							    VOID (WINAPI *v_FunctionName) (DWORD   dw_DriverHandle,
											   DWORD   dw_Functionality,
											   DWORD   dw_InterruptMask,
											   PBYTE   pb_ByteArray,
											   PWORD   pw_WordArray,
											   PDWORD pdw_DWordArray,
											   BYTE	    b_CallingMode,
											   PVOID   pv_UserSharedMemory));

   // Begin 31/01/01 CG 0800/0200 -> 0900/0210 : New function the Version 0400/0102B

   _BYTE_	b_ADDIDATA_TestInterrupt	(DWORD	 dw_DriverHandle,
					         PDWORD pdw_Functionality,
					         PDWORD	pdw_InterruptMask,
					         PBYTE   pb_ByteArray,
					         PWORD   pw_WordArray,
					         PDWORD pdw_DwordArray);
   // End 31/01/01 CG 0800/0200 -> 0900/0210 : New function the Version 0400/0102B

   _BYTE_   b_ADDIDATA_ResetFunctionalityIntRoutine	   (DWORD dw_DriverHandle,
							    DWORD dw_Functionality);
#endif
