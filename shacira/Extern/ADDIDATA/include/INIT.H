/*
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstraße 3       D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-------------------------------+---------------------------------------+
  | Project     : API  ADDI-DATA  |     Compiler   : BORLANDC/MICROSOFT C |
  | Module name : INIT.H          |     Version    : 3.1     / 6.0        |
  |                               |                                       |
  |                               |                                       |
  +-------------------------------+---------------------------------------+
  | Author : Weber S.                      Date :21/12/1999               |
  +-----------------------------------------------------------------------+
  | Description   : Header file for the ADDI-DATA initialisation          |
  |		    funtionality driver                                   |
  +-----------------------------------------------------------------------+
  |                             UPDATES                                   |
  +----------+-----------+------------------------------------------------+
  |   Date   |   Author  |          Description of updates                |
  +----------+-----------+------------------------------------------------+
  | 08/11/00 | Guinot C. | 0800/0200 -> 0900/0210                         |
  |          |           | use _BYTE_ instead of _BOOL_                   |
  +----------+-----------+------------------------------------------------+
  | 19/09/01 |R. HILPERT | 0901/02151 -> 0901/02152                       |
  |          |           | Ae000035_OpenWin32Driver_Test                  |
  +----------+-----------+------------------------------------------------+
*/


#ifndef ADDIDATA_INITIALISATION_HEADER
   #define ADDIDATA_INITIALISATION_HEADER

   /*************************************************************************/
   /* Init.c                                                                */
   /*************************************************************************/

   _INT_   i_ADDIDATA_LoadVirtualBoard		(CHAR * pc_VirtualBoard);

   _INT_   i_ADDIDATA_OpenWin32Driver		(BYTE    b_CompilerDefine,
						 PDWORD pd_DriverHandle);

   _VOID_  v_ADDIDATA_GetDriverVersion (PDWORD pdw_DriverVersion);

// Begin  | 19/09/01 |R. HILPERT | 0901/02151 -> 0901/02152                       |
   _INT_   i_ADDIDATA_GetCurrentDriverHandle	(PDWORD pdw_DriverHandle);
// End  | 19/09/01 |R. HILPERT | 0901/02151 -> 0901/02152                       |

   _BYTE_  b_ADDIDATA_CloseWin32Driver		(DWORD	dw_DriverHandle);

   _BOOL_	b_TestSimulateInterrupt		(VOID);

#endif

