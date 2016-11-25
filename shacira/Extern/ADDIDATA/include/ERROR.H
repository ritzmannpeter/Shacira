/*
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstraße 3       D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-------------------------------+---------------------------------------+
  | Project     : API  ADDI-DATA  |     Compiler   : BORLANDC/MICROSOFT C |
  | Module name : ERROR.H         |     Version    : 3.1     / 6.0        |
  |                               |                                       |
  |                               |                                       |
  +-------------------------------+---------------------------------------+
  | Author : Weber S.                      Date :14/12/1999               |
  +-----------------------------------------------------------------------+
  | Description   : Header file for the ADDI-DATA error funtionality      |
  |		    driver                                                |
  +-----------------------------------------------------------------------+
  |                             UPDATES                                   |
  +----------+-----------+------------------------------------------------+
  |   Date   |   Author  |          Description of updates                |
  +----------+-----------+------------------------------------------------+
  | 08/11/00 | Guinot C. | 0800/0200 -> 0900/0210                         |
  |          |           | use _BYTE_ instead of _BOOL_
  +----------+-----------+------------------------------------------------+
*/


#ifndef ADDIDATA_ERROR_HEADER
   #define ADDIDATA_ERROR_HEADER

   /*************************************************************************/
   /* Error.c                                                               */
   /*************************************************************************/

   _INT_   i_ADDIDATA_GetLastError	      (DWORD dw_DriverHandle,
					       PWORD pw_FunctionNumber,
					       PINT  pi_ErrorCode,
					       PBYTE pb_ErrorLevel);

   _INT_   i_ADDIDATA_GetLastErrorAndSource   (DWORD   dw_DriverHandle,
                                               PWORD   pw_FunctionNumber,
                                               PINT    pi_ErrorCode,
                                               PBYTE   pb_ErrorLevel,
                                               PDWORD pdw_ErrorSource);

   _BYTE_  b_ADDIDATA_EnableErrorMessage      (DWORD  dw_DriverHandle,
					       HANDLE  h_WndHandle,
					       WORD    w_Message);

   _BYTE_  b_ADDIDATA_DisableErrorMessage     (DWORD dw_DriverHandle);

   _BYTE_ b_ADDIDATA_FormatErrorMessage (DWORD dw_DriverHandle,
                                         INT i_ErrorNumber,
                     		         PCHAR pc_ErrorString,
                              	         WORD w_ErrorStringSize,
                          	         WORD w_FunctionNumber,
                             	         PCHAR pc_FunctionName,
                          	         WORD w_FunctionStringSize);

#endif