/*
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstraﬂe 3       D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-------------------------------+---------------------------------------+
  | Project   : -                 |     Compiler   : C                    |
  | Modulname : PA150.H           |     Version    : -                    |
  +-------------------------------+---------------------------------------+
  | Author : Weber S.                      Date :23/02/99                 |
  +-----------------------------------------------------------------------+
  | Description   : Driver PA150                                          |
  |                                                                       |
  +-----------------------------------------------------------------------+
  |                             UPDATES                                   |
  +----------+-----------+------------------------------------------------+
  |   Date   |   Author  |          Description of updates                |
  +----------+-----------+------------------------------------------------+
*/

#ifndef _INT_
   #include <windows.h>

   #define DLL_COMPILER_C          0
   #define DLL_COMPILER_PASCAL     1
   #define DLL_COMPILER_VB         2
   #define DLL_LABVIEW             3
   #define DLL_COMPILER_VB_5       4

   #ifdef _BORLANDC_
      #ifdef __cplusplus

	 /**********************/
	 /* Windows C++ define */
	 /**********************/

	 #define _INT_         extern "C"  _import int far _stdcall
	 #define _VOID_        extern "C"  _import void far _stdcall
      #else

	 /******************/
	 /* Windows define */
	 /******************/

	 #define _INT_         _import int far _stdcall
	 #define _VOID_        _import void far _stdcall
      #endif
   #else
      #ifdef __cplusplus

	 /**********************/
	 /* Windows C++ define */
	 /**********************/

	 #define _INT_         extern "C"  int far _stdcall
	 #define _VOID_        extern "C"  void far _stdcall
      #else

	 /******************/
	 /* Windows define */
	 /******************/

	 #define _INT_         int far _stdcall
	 #define _VOID_        void far _stdcall
      #endif
   #endif

   #define INT_      int
   #define UINT_     unsigned int
   #define BYTE_     unsigned char
   #define CHAR_     char
   #define LONG_     long
   #define ULONG_    unsigned long
   #define PINT_     INT_   *
   #define PUINT_    UINT_  *
   #define PBYTE_    BYTE_  *
   #define PCHAR_    CHAR_  *
   #define PLONG_    LONG_  *
   #define PULONG_   ULONG_ *
#endif

#ifndef      PA150
   #define      PA150
   #define      PA150_AND               2
   #define      PA150_OR                4
   #define      PA150_OR_PRIORITY       6
   #define      PA150_DISABLE           0
   #define      PA150_ENABLE            1
   #define      PA150_MAX_BOARD_NBR     10
   #define      PA150_8BIT              8
   #define      PA150_16BIT             16
   #define      PA150_TIMER             0
   #define      PA150_COUNTER           0x20
   #define      PA150_WATCHDOG          0
   #define      PA150_SINGLE            0
   #define      PA150_CONTINUOUS        0x80
   #define      PA150_SOFTWARE_TRIGGER  0x4
   #define      PA150_HARDWARE_TRIGGER  0x10
   #define      PA150_SOFTWARE_GATE     0
   #define      PA150_HARDWARE_GATE     0x8
   #define      PA150_8BIT              8
   #define      PA150_16BIT             16

   #define      PA150_SYNCHRONOUS_MODE      1
   #define      PA150_ASYNCHRONOUS_MODE     0


/*
+----------------------------------------------------------------------------+
|   GLOBAL PROTOTYPE FUNCTION                                                |
+----------------------------------------------------------------------------+
*/

   _INT_        i_PA150_SetBoardAddress            (UINT_  ui_Address,
						    PBYTE_ pb_BoardHandle);

   _INT_        i_PA150_CloseBoardHandle            (BYTE_ b_BoardHandle);

   /*
   +----------------------------------------------------------------------------+
   |   INPUT FUNCTION                                                           |
   +----------------------------------------------------------------------------+
   */

   _INT_        i_PA150_Read1DigitalInput         (BYTE_   b_BoardHandle,
						   BYTE_   b_Channel,
						   PBYTE_ pb_ChannelValue);

   _INT_        i_PA150_Read8DigitalInput         (BYTE_   b_BoardHandle,
						   BYTE_   b_Port,
						   PBYTE_ pb_PortValue);

   _INT_        i_PA150_Read16DigitalInput        (BYTE_   b_BoardHandle,
						    PLONG_ pl_InputValue);

   /*
   +----------------------------------------------------------------------------+
   |   OUTPUT FUNCTION                                                          |
   +----------------------------------------------------------------------------+
   */

   _INT_        i_PA150_Set1DigitalOutputOn       (BYTE_ b_BoardHandle,
						   BYTE_ b_Channel);

   _INT_        i_PA150_Set1DigitalOutputOff      (BYTE_ b_BoardHandle,
						   BYTE_ b_Channel);

   _INT_        i_PA150_Set8DigitalOutputOn       (BYTE_ b_BoardHandle,
						   BYTE_ b_Port,
						   BYTE_ b_Value);

   _INT_        i_PA150_Set8DigitalOutputOff      (BYTE_ b_BoardHandle,
						   BYTE_ b_Port,
						   BYTE_ b_Value);

   _INT_        i_PA150_Set16DigitalOutputOn      (BYTE_ b_BoardHandle,
						   LONG_ l_Value);

   _INT_        i_PA150_Set16DigitalOutputOff     (BYTE_ b_BoardHandle,
						   LONG_ l_Value);

   _INT_        i_PA150_SetOutputMemoryOn         (BYTE_ b_BoardHandle);

   _INT_        i_PA150_SetOutputMemoryOff        (BYTE_ b_BoardHandle);

#endif
