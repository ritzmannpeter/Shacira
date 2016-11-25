/*
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstraße 3       D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-------------------------------+---------------------------------------+
  | Project     : API  ADDI-DATA  |     Compiler   : BORLANDC/MICROSOFT C |
  | Module name : DEFINE.H        |     Version    : 3.1     / 6.0        |
  |                               |                                       |
  |                               |                                       |
  +-------------------------------+---------------------------------------+
  | Author : Weber S.                      Date :14/12/1999               |
  +-----------------------------------------------------------------------+
  | Description   : Header file for the ADDI-DATA error funtionality      |
  |                 driver                                                |
  +-----------------------------------------------------------------------+
  |                             UPDATES                                   |
  +----------+-----------+------------------------------------------------+
  |   Date   |   Author  |          Description of updates                |
  +----------+-----------+------------------------------------------------+
  |02/03/2000|R. Hilpert | Ana_out, Dig_out, Dig_inp + Old define for     |
  |          |           | old boards.                                    |
  +----------+-----------+------------------------------------------------+
  | 13/09/00 | C.Guinot  | 0800/0200 -> 0900/0210                         |
  |          |           | implementation of the analog measure           |
  |          |           | Implement change from the version 0400/0102B   |
  |          |           | and 1200/0205                                  |
  +----------+-----------+------------------------------------------------+
  |01/01/2001|R. Hilpert | Digital output interrupt.                      |
  |          |           | Digital input interrupt.                       |
  |          |           | 0800-0200 -> 1200-0205.                        |
  +----------+-----------+------------------------------------------------+
  |17/04/2001|R. Hilpert | Analog output time out.                        |
  |          |           | 0800/0200 -> 0900/0210.                        |
  +----------+-----------+------------------------------------------------+
  | 11/09/01 |R. HILPERT | 0801/0215 -> 0901/02151 (See To Do Liste 216). |
  |          |           | Problem by the define:                         |
  |          |           | ADDIDATA_ANALOG_MEASURE_TYPE_ENUMERATION,      |
  |          |           | ADDIDATA_FUNCTION_ENUMERATION and DOUBLE.      |
  +----------+-----------+------------------------------------------------+
  | 19/09/01 |R. HILPERT | 0901/02151 -> 0901/02152                       |
  |          |           | Ae000035_OpenWin32Driver_Test                  |
  +----------+-----------+------------------------------------------------+
  |09.10.2001| R. HILPERT| 0801-0216 -> 0801-0216                         |
  |	     |		 | (War och nicht freigegeben)                    |
  |	     |		 | b_ConfigurableResetMode implementation         |
  |	     |		 | for the APCI-035.                              |
  +----------+-----------+------------------------------------------------+
  |08.08.2002| S. Weber  |0302-0223 -> 2224-0602.                         |
  |	     |		 | Module number information implementation       |
  |	     |		 | (str_GetAnalogMesureInformation)               |
  +----------+-----------+------------------------------------------------+
  | 15/11/02 | C.Guinot  | 2224/0602 -> 2225/1102                         |
  |          |           | implementation of the FIFO overflow management |
  |          |           | by the interrupt asynchrone Mode               |
  +----------+-----------+------------------------------------------------+
  | 03/03/03 | C.Guinot  | Add define Error : Add the test of the digital |
  |          |           | input mask.                                    |
  +----------+-----------+------------------------------------------------+
  | 16/06/03 | S. Weber  | ADDIDATA_TRANSDUCER_PRIMARY_SHORT_CIRCUIT_OCCUR| 
  |          |           | implementation                                 |
  +----------+-----------+------------------------------------------------+
  | 16/06/03 | S. Weber  | ADDIDATA_REARM_TRANSDUCER_MODULE_PRIMARY_ /    |
  |          |           | SHORT_CIRCUIT_CONNECTION_TEST implementation   |
  +----------+-----------+------------------------------------------------+
*/



#ifndef ADDIDATA_DEFINE_HEADER
   #define ADDIDATA_DEFINE_HEADER

   /**************************************/
   /* Test if ADDI-DATA type declation ? */
   /**************************************/

   #ifndef ADDI_DATA_TYPE_DECLARATION

      #define ADDI_DATA_TYPE_DECLARATION

      #ifndef MAXPATH
	 #define MAXPATH 125
      #endif

      /********************************/
      /* Test if Dos or Windows 3.11 ? /
      /********************************/

      #ifndef _WIN32

         /*********************************************/
	 /* Type declaration for Dos and Windows 3.11 */
	 /*********************************************/

	 #if defined (__cplusplus)
	    #define __CPPARGS ...
	 #elif defined (__BORLANDC__)
	    #define __CPPARGS VOID
	 #else  // #if defined (__cplusplus)
	    #define __CPPARGS
	 #endif // #if defined (__cplusplus)

	 #define KS_Error int

	 #if defined (_Windows) | defined (_WINDOWS)

	    /*********************************/
	    /* Windows 3.11 type declaration */
	    /*********************************/

	    /******************************/
	    /* Include the windows.h file */
	    /******************************/

	    #include <windows.h>

	    typedef char            CHAR;
	    typedef int             INT;
	    typedef unsigned int    UINT;
	    typedef unsigned long   ULONG;
	    typedef void            VOID;
	    typedef double          DOUBLE;
	    typedef unsigned char * PBYTE;
	    typedef char          * PCHAR;
	    typedef unsigned int  * PUINT;
	    typedef long          * PLONG;
	    typedef unsigned long * PULONG;
	    typedef void          * PVOID;
	    typedef double        * PDOUBLE;
             

	    #ifdef __cplusplus
	       #define _INT_ extern "C"  INT  far _stdcall
 	       #define _BOOL_ extern "C" BOOL far _stdcall
	       #define _VOID_ extern "C" VOID far _stdcall
	       // 06/11/00 CG 0800/0200 -> 0900/0210
	       #define _BYTE_ extern "C" BYTE far _stdcall
	    #else  // #ifdef __cplusplus
	       #define _INT_  INT  far _stdcall
 	       #define _BOOL_ BOOL far _stdcall
	       #define _VOID_ VOID far _stdcall
	       // 06/11/00 CG 0800/0200 -> 0900/0210
	       #define _BYTE_ BYTE far _stdcall
	    #endif // #ifdef __cplusplus

	 #else // defined (_Windows) | defined (_WINDOWS)

	    #define TRUE  1
	    #define FALSE 0
	    #define _loadds
	    #define HANDLE WORD

	    /***********************/
	    /* Dos type decaration */
	    /***********************/

	    #if defined   (__TPASCAL__)
	       /**********************************/
	       /* Borland Pascal type decaration */
	       /**********************************/

	       typedef unsigned char   BOOL;
	       typedef unsigned char   BYTE;
	       typedef char            CHAR;
	       typedef int             INT;
	       typedef unsigned int    UINT;
	       typedef unsigned int    WORD;
	       typedef unsigned long   DWORD;
	       typedef long            LONG;
	       typedef unsigned long   ULONG;
	       typedef void            VOID;
	       typedef double          DOUBLE;
	       typedef unsigned char * PBOOL;
	       typedef unsigned char * PBYTE;
	       typedef char          * PCHAR;
	       typedef int           * PINT;
	       typedef unsigned int  * PUINT;
	       typedef unsigned int  * PWORD;
	       typedef unsigned long * PDWORD;
	       typedef long          * PLONG;
	       typedef unsigned long * PULONG;
	       typedef void          * PVOID;
	       typedef double        * PDOUBLE;

	       typedef INT  _INT_
	       typedef BOOL _BOOL_
	       typedef VOID _VOID_
      	       // 06/11/00 CG 0800/0200 -> 0900/0210
               typedef BYTE _BYTE_
	       #define WINAPI

	    #elif defined (__VBDOS__)
	       /********************************/
	       /* Microsoft VB type decaration */
	       /********************************/

	       typedef unsigned char        BOOL;
	       typedef unsigned char        BYTE;
	       typedef char                 CHAR;
	       typedef int                  INT;
	       typedef unsigned long        UINT;
	       typedef unsigned long        WORD;
	       typedef unsigned long        DWORD;
	       typedef long                 LONG;
	       typedef unsigned long        ULONG;
	       typedef void                 VOID;
	       typedef double               DOUBLE;
	       typedef unsigned char near * PBOOL;
	       typedef unsigned char near * PBYTE;
	       typedef char          near * PCHAR;
	       typedef int           near * PINT;
	       typedef unsigned long near * PUINT;
	       typedef unsigned long near * PWORD;
	       typedef unsigned long near * PDWORD;
	       typedef long          near * PLONG;
	       typedef unsigned long near * PULONG;
	       typedef void          near * PVOID;
	       typedef double        near * PDOUBLE;

	       typedef INT  _INT_
	       typedef BOOL _BOOL_
	       typedef VOID _VOID_
 	       // 06/11/00 CG 0800/0200 -> 0900/0210
	       typedef BYTE _BYTE_
               #define WINAPI
	    #else
	       /***********************************/
	       /* Borland/Microsoft C declaration */
	       /***********************************/

	       typedef unsigned char   BOOL;
	       typedef unsigned char   BYTE;
	       typedef char            CHAR;
	       typedef int             INT;
	       typedef unsigned int    UINT;
	       typedef unsigned int    WORD;
	       typedef unsigned long   DWORD;
	       typedef long            LONG;
	       typedef unsigned long   ULONG;
	       typedef void            VOID;
	       typedef double          DOUBLE;
	       typedef unsigned char * PBOOL;
	       typedef unsigned char * PBYTE;
	       typedef char          * PCHAR;
	       typedef int           * PINT;
	       typedef unsigned int  * PUINT;
	       typedef unsigned int  * PWORD;
	       typedef unsigned long * PDWORD;
	       typedef long          * PLONG;
	       typedef unsigned long * PULONG;
	       typedef void          * PVOID;
	       typedef double        * PDOUBLE;

	       #define _INT_  INT
	       #define _BOOL_ BOOL
	       #define _VOID_ VOID
       	       // 06/11/00 CG 0800/0200 -> 0900/0210
               #define _BYTE_ BYTE
	       #define WINAPI

	       /***********************/
	       /* Test if Microsoft C */
	       /***********************/

	       #ifndef __BORLANDC__
		  #define interrupt  _interrupt far
		  #define __CPPARGS
	       #endif
	    #endif
	 #endif // defined (_Windows) | defined (_WINDOWS)
      #else // #ifndef _WIN32

	 #define KS_Error Error
	 #include <windows.h>
// Begin Änderung 11/09/01 |R. HILPERT | 0801/0215 -> 0901/02151                        
//	 #ifdef __BORLANDC__
	    #define DOUBLE   double
	    #define PDOUBLE *double
//	 #endif
// End Änderung 11/09/01 |R. HILPERT | 0801/0215 -> 0901/02151                        


	 #define _loadds
	 #define __CPPARGS  PVOID pv_Args, PULONG pul_BoardInterruptCpt
	 #define interrupt
	 #define ADDIDATA_DEBUG
	 #define INT_      int
	 #define UINT_     unsigned int
	 #define BYTE_     unsigned char
	 #define CHAR_     char
	 #define LONG_     long
	 #define ULONG_    unsigned long
	 #define PINT_     int  *
	 #define PUINT_    unsigned int *
	 #define PUINT__   unsigned int *
	 #define PBYTE_    unsigned char *
	 #define PBYTE__   unsigned char *
	 #define PCHAR_    char  *
	 #define PLONG_    long *
	 #define PULONG_   unsigned long *
	 #define DLL_COMPILER_C          0
	 #define DLL_COMPILER_PASCAL     1
	 #define DLL_COMPILER_VB         2
	 #define DLL_LABVIEW             3
	 #define DLL_COMPILER_VB_5       4
	 
	 /**************************************/
	 /* Type declaration for Windows NT/9x */
	 /**************************************/

	 #ifdef __cplusplus
	    #define _INT_  extern "C" INT  WINAPI
	    #define _BOOL_ extern "C" BOOL WINAPI
	    #define _VOID_ extern "C" VOID WINAPI
            // 06/11/00 CG 0800/0200 -> 0900/0210
	    #define _BYTE_ extern "C" BYTE WINAPI
	 #else  // #ifdef __cplusplus
	    #define _INT_  INT  WINAPI
	    #define _BOOL_ BOOL WINAPI
	    #define _VOID_ VOID WINAPI
            // 06/11/00 CG 0800/0200 -> 0900/0210
	    #define _BYTE_ BYTE WINAPI

	 #endif // #ifdef __cplusplus

      #endif // #else #ifndef _WIN32
   #endif

   /****************************************************************************/
   /* Define the call level (Ring 0 or ring 3)                                 */
   /****************************************************************************/

   #define ADDIDATA_RING_3                         0
   #define ADDIDATA_RING_0                         1

   /****************************************************************************/
   /* Define the interrupt mask                                                */
   /****************************************************************************/

   /************************************************/
   /* Define interrupt enumeration for Temperature */
   /************************************************/

   #define              ADDIDATA_SINGLE_TEMPERATURE    0x10000UL
   #define		ADDIDATA_READ_MORE_TEMPERATURE 0x20000UL
   #define              ADDIDATA_SCAN_TEMPERATURE      0x200000UL
   #define              ADDIDATA_WARNING_TEMPERATURE   0x80000UL

   /*********************************************/
   /* Define interrupt enumeration for Pressure */
   /*********************************************/

   #define              ADDIDATA_SINGLE_PRESSURE       0x10000UL
   #define		ADDIDATA_READ_MORE_PRESSURE    0x20000UL
   #define              ADDIDATA_SCAN_PRESSURE         0x200000UL


   /***********************************************/
   /* Define interrupt enumeration for transducer */
   /***********************************************/

   #define              ADDIDATA_SINGLE_TRANSDUCER     0x10000UL
   #define		ADDIDATA_READ_MORE_TRANSDUCER  0x20000UL
   #define              ADDIDATA_PRIMARY_SHORT_CIRCUIT 0x800000UL
   #define              ADDIDATA_DMA                   0x100000UL
   #define              ADDIDATA_DMA_FIFO_OVERFLOW     0x400000UL

   /*************************************************/
   /* Define interrupt enumeration for Analog input */
   /*************************************************/
   // 27/09/00 CG 0800/0200 -> 0900/0210

   #define              ADDIDATA_SINGLE_ANALOG_INPUT_IRQ    0x10000UL
   #define		ADDIDATA_READ_MORE_ANALOG_INPUT_IRQ 0x20000UL
   #define              ADDIDATA_SCAN_ANALOG_INPUT_IRQ      0x200000UL  
   
   /***********************************************/
   /* Define interrupt enumeration for resistance */
   /***********************************************/
   // 27/09/00 CG 0800/0200 -> 0900/0210

   #define              ADDIDATA_SINGLE_RESISTANCE    0x10000UL
   #define		ADDIDATA_READ_MORE_RESISTANCE 0x20000UL
   #define              ADDIDATA_SCAN_RESISTANCE      0x200000UL  
   

   
   /****************************************************************************/
   /* Interrupt function mode                                                  */
   /****************************************************************************/

   #define              ADDIDATA_ASYNCHRONOUS_MODE      0
   #define              ADDIDATA_SYNCHRONOUS_MODE       1
   #define              ADDIDATA_VB_MODE                2

   /****************************************************************************/
   /* Shared memory define                                                     */
   /****************************************************************************/

   #define              ADDIDATA_SHARED_MEMORY_NOT_USED 0
   #define              ADDIDATA_NEW_SHARED_MEMORY      1
   #define              ADDIDATA_ALREADY_USED_SHARED_MEMORY  2

   /****************************************************************************/
   /* List of error message                                                    */
   /****************************************************************************/

   #define ADDIDATA_FUNCTIONALITY_NOT_AVAILABLE            -100
   #define ADDIDATA_FUNCTIONALITY_NO_RING_0                -101
   #define ADDIDATA_SYSTEM_ERROR                           -102
   #define ADDIDATA_NO_FREE_DRIVER_HANDLE_FOUND            -103
   #define ADDIDATA_DRIVER_SHARED_MEMORY_ERROR             -104
   #define ADDIDATA_DRIVER_OPENING_ERROR                   -105
   #define ADDIDATA_CURRENT_PROCESS_HDL_NOT_AVAIBLE        -106
   #define ADDIDATA_GET_SHARED_MEMORY_ERROR                -107
   #define ADDIDATA_DRIVER_HANDLE_ERROR                    -108
   #define ADDIDATA_DRIVER_NOT_OPEN                        -109
   #define ADDIDATA_ONE_OR_MORE_BOARDS_NOT_FOUND           -110
   #define ADDIDATA_DRIVER_ALREADY_OPEN                    -111
   // Begin 02/10/00 CG 0800/0200 -> 0900/0210 
   #define ADDIDATA_REGISTRY_PROBLEM                       -112
   #define ADDIDATA_ADDIDATA_SHARED_PATH_NOT_AVAILABLE     -113
   #define ADDIDATA_TEMPERATURE_CONVERT_FILE_ERROR         -114
   #define ADDIDATA_TEMPERATURE_BUFFER_SHARED_MEMORY_ERROR -115
   // End 02/10/00 CG 0800/0200 -> 0900/0210 
   // Begin 30/01/01 CG 0400/0102B -> 0900/0210 
   #define ADDIDATA_COMPILER_DEFINED_ERROR                 -116
   // End 30/01/01 CG 0400/0102B -> 0900/0210 
   // Begin 12/03/01 CG 0800/0200 -> 0900/0210
   #define ADDIDATA_MULTIPROCESS_NOT_AVAILABLE_IN_THIS_VERSION -117
   #define ADDIDATA_READY_BIT_TIMEOUT_OCCUR                -118
   #define ADDIDATA_ERROR_FILE_NOT_AVAILABLE		   -119
   #define ADDIDATA_ERROR_STRING_TOO_SMALL		   -120
   #define ADDIDATA_ERROR_STRING_NOT_FOUND		   -121
   #define ADDIDATA_REGISTRY_NOT_UPDATED                   -122
   #define ADDIDATA_DRIVER_FREE_SHARED_MEMORY_ERROR        -123
   #define ADDIDATA_DRIVER_RING_0_PREPARATION_ERROR        -124
   // Begin 27.11.2001 S.WEBER 1101-0218 -> 1101-0219
   #define ADDIDATA_DRIVER_MEMORY_MAP_ERROR                -125
   // End 27.11.2001 S.WEBER 1101-0218 -> 1101-0219
   // Begin 25/07/02 RH 2224-0602 -> 2225-0802
   #define ADDIDATA_REGISTRY_COULD_NOT_BE_TESTED           -126
   // End 25/07/02 RH 2224-0602 -> 2225-0802

   // Begin 06/11/02 RH PVCS -> PVCS
   #define ADDIDATA_ADDEVICEMAPPER_ALREADY_STARTED         -127
   // End 06/11/02 RH PVCS -> PVCS

   // Begin JK 08/10/02 2224-0602 -> 2225-1002 APCI 1500 Interrupt
   #define ADDIDATA_EXTERN_DRIVER_DLL_LOAD_ERROR           -128
   // End JK 08/10/02 2224-0602 -> 2225-1002 APCI 1500 Interrupt

   // Begin JK 20/11/02 2224-0602 -> 2225-1002 APCI 1500 Interrupt
   #define ADDIDATA_EXTERN_DRIVER_APCI_1500_DLL_NOT_FOUND     -129 
   #define ADDIDATA_EXTERN_DRIVER_APCI_1500_DLL_VERSION_ERROR -130
   // End JK 20/11/02 2224-0602 -> 2225-1002 APCI 1500 Interrupt      

   #define ADDIDATA_VIRTUAL_BOARD_FILE_NOT_FOUND              -131
   #define ADDIDATA_REALBOARD_XML_FILE_NOT_FOUND              -132
   #define ADDIDATA_REALBOARD_XML_FILE_BACKUP_ERROR           -133
   #define ADDIDATA_COPY_VIRTUAL_BOARD_FILE_ERROR             -134
   #define ADDIDATA_ADDEVICEMAPER_CALL_ERROR                  -135

   // End 12/03/01 CG 0800/0200 -> 0900/0210

   /*******************/
   /* Interrupt error */
   /*******************/

   #define ADDIDATA_INTERRUPT_USER_SHARED_MEMORY_SIZE_ERROR                        -150
   #define ADDIDATA_INTERRUPT_SHARED_MEMORY_MODE_ERROR                             -151
   #define ADDIDATA_INTERRUPT_USER_CALLING_MODE_ERROR                              -152
   #define ADDIDATA_INTERRUPT_FUNCTIONALITY_ALREADY_INSTALLED                      -153
   #define ADDIDATA_INTERRUPT_USER_SHARED_MEMORY_NOT_FOUND                         -154
   #define ADDIDATA_INTERRUPT_USER_SHARED_MEMORY_ALLOCATION_ERROR                  -155
   #define ADDIDATA_INTERRUPT_USER_INSTALLATION_FUNCTION_ERROR                     -156
   #define ADDIDATA_INTERRUPT_PREPARE_FUNCTIONALITY_INTERRUPT_FUNCTION_ERROR       -157
   #define ADDIDATA_INTERRUPT_PREPARE_API_INTERRUPT_FUNCTION_ERROR                 -158
   #define ADDIDATA_INTERRUPT_INSTALL_API_INTERRUPT_FUNCTION_ERROR                 -159
   #define ADDIDATA_INTERRUPT_NO_INDEX_AVAILABLE                                   -160
   #define ADDIDATA_INTERRUPT_INDEX_NUMBER_ERROR                                   -161
   #define ADDIDATA_INTERRUPT_FUNCTIONALITY_NUMBER_ERROR                           -162
   #define ADDIDATA_INTERRUPT_FUNCTIONALITY_NOT_INSTALLED                          -163
   #define ADDIDATA_INTERRUPT_END_FUNCTIONALITY_EXEC_ERROR                         -164
   #define ADDIDATA_INTERRUPT_API_UNINSTALL_ERROR                                  -165
   #define ADDIDATA_INTERRUPT_END_API_EXEC_ERROR                                   -166
   #define ADDIDATA_INTERRUPT_FUNCTIONALITY_SELECTION_ERROR                        -167
   #define ADDIDATA_INTERRUPT_API_THREAD_CREATION_ERROR                            -168
   #define ADDIDATA_INTERRUPT_API_EVENT_CREATION_ERROR                             -169
   // Begin 30/01/01 CG 0400/0102B -> 0900/0210
   #define ADDIDATA_INTERRUPT_NO_INTERRT_INITIALISED                               -170
   // End 30/01/01 CG 0400/0102B -> 0900/0210
   #define ADDIDATA_INTERRUPT_FLAG_ERROR					   -171

   // Begin JK 09/10/02 2224-0602 -> 2225-1002 APCI 1500 Interrupt
   #define ADDIDATA_ACPI_ACTIV_AND_USE_OF_WINDOWS_NT4                              -172
   #define ADDIDATA_PNP_OS_ACPI_AND_USE_OF_WINDOWS_NT4                             -173
   // End JK 09/10/02 2224-0602 -> 2225-1002 APCI 1500 Interrupt
   

   /***************/
   /* Timer error */
   /***************/

   #define ADDIDATA_TIMER_NUMBER_ERROR                                   -200
   #define ADDIDATA_TIMER_RELOAD_VALUE_ERROR                             -201
   #define ADDIDATA_TIMER_UNIT_ERROR                                     -202
   #define ADDIDATA_TIMER_MODE_ERROR                                     -203
   #define ADDIDATA_TIMER_INTERRUPT_FLAG_ERROR                           -204
   #define ADDIDATA_TIMER_HARDWARE_GATE_LEVEL_ERROR                      -205
   #define ADDIDATA_TIMER_HARDWARE_GATE_LEVEL_SELECTION_ERROR            -206
   #define ADDIDATA_TIMER_HARDWARE_GATE_FLAG_ERROR                       -207
   #define ADDIDATA_TIMER_HARDWARE_TRIGGER_LEVEL_ERROR                   -208
   #define ADDIDATA_TIMER_HARDWARE_TRIGGER_LEVEL_SELECTION_ERROR         -209
   #define ADDIDATA_TIMER_HARDWARE_TRIGGER_FLAG_ERROR                    -210
   #define ADDIDATA_TIMER_HARDWARE_OUTPUT_LEVEL_ERROR                    -211
   #define ADDIDATA_TIMER_HARDWARE_OUTPUT_LEVEL_SELECTION_ERROR          -212
   #define ADDIDATA_TIMER_HARDWARE_OUTPUT_FLAG_ERROR                     -213
   #define ADDIDATA_TIMER_ALREADY_USED                                   -214

   /*****************/
   /* Counter error */
   /*****************/

   #define ADDIDATA_COUNTER_NUMBER_ERROR                                   -800
   #define ADDIDATA_COUNTER_RELOAD_VALUE_ERROR                             -801
   #define ADDIDATA_COUNTER_COUNTER_UP_DOWN_FLAG_ERROR			   -802
   #define ADDIDATA_COUNTER_INPUT_LEVEL_ERROR			           -803
   #define ADDIDATA_COUNTER_INTERRUPT_FLAG_ERROR                           -804
   #define ADDIDATA_COUNTER_HARDWARE_GATE_LEVEL_ERROR                      -805
   #define ADDIDATA_COUNTER_HARDWARE_GATE_LEVEL_SELECTION_ERROR            -806
   #define ADDIDATA_COUNTER_HARDWARE_GATE_FLAG_ERROR                       -807
   #define ADDIDATA_COUNTER_HARDWARE_TRIGGER_LEVEL_ERROR                   -808
   #define ADDIDATA_COUNTER_HARDWARE_TRIGGER_LEVEL_SELECTION_ERROR         -809
   #define ADDIDATA_COUNTER_HARDWARE_TRIGGER_FLAG_ERROR                    -810
   #define ADDIDATA_COUNTER_HARDWARE_OUTPUT_LEVEL_ERROR                    -811
   #define ADDIDATA_COUNTER_HARDWARE_OUTPUT_LEVEL_SELECTION_ERROR          -812
   #define ADDIDATA_COUNTER_HARDWARE_OUTPUT_FLAG_ERROR                     -813
   #define ADDIDATA_COUNTER_ALREADY_USED                                   -814

   /******************/
   /* Watchdog error */
   /******************/

   #define ADDIDATA_WATCHDOG_NUMBER_ERROR                           -300
   #define ADDIDATA_WATCHDOG_DELAY_VALUE_ERROR                      -301
   #define ADDIDATA_WATCHDOG_UNIT_ERROR                             -302
   #define ADDIDATA_WATCHDOG_INTERRUPT_FLAG_ERROR                   -303
   #define ADDIDATA_WATCHDOG_HARDWARE_GATE_LEVEL_ERROR              -304
   #define ADDIDATA_WATCHDOG_HARDWARE_GATE_LEVEL_SELECTION_ERROR    -305
   #define ADDIDATA_WATCHDOG_HARDWARE_GATE_FLAG_ERROR               -306
   #define ADDIDATA_WATCHDOG_HARDWARE_TRIGGER_LEVEL_ERROR           -307
   #define ADDIDATA_WATCHDOG_HARDWARE_TRIGGER_LEVEL_SELECTION_ERROR -308
   #define ADDIDATA_WATCHDOG_HARDWARE_TRIGGER_FLAG_ERROR            -309
   #define ADDIDATA_WARNING_DELAY_VALUE_ERROR                       -310
   #define ADDIDATA_WARNING_UNIT_ERROR                              -311
   #define ADDIDATA_WATCHDOG_WARNING_RELAY_FLAG_ERROR               -312
   #define ADDIDATA_WATCHDOG_RESET_RELAY_FLAG_ERROR                 -313
   #define ADDIDATA_WATCHDOG_ALREADY_USED                           -314
//Begin :  |09.10.2001| R. HILPERT| 0801-0216 -> 0801-0216                         |
   #define ADDIDATA_WATCHDOG_INFORMATION_STRUCTURE_INVALID_SIZE     -315
   #define ADDIDATA_WATCHDOG_RESET_RELAY_MODE_SELECTION_ERROR       -316
//End :  |09.10.2001| R. HILPERT| 0801-0216 -> 0801-0216                         |

   /*************************************************************************/
   /* CG 13/09/00 0800/0200 -> 0900/0210                                    */  
   /* Temperature Error replace by Analog measure Error                     */    
   /*********************						    */
   /* Temperature error *						    */   
   /*********************						    */   
   /*									    */
   /*#define ADDIDATA_TEMPERATURE_NUMBER_ERROR                        -400  */
   /*#define ADDIDATA_TEMPERATURE_CONVERSION_STARTED                  -401  */
   /*#define ADDIDATA_TEMPERATURE_WARNING_FLAG_ERROR                  -402  */
   /*#define ADDIDATA_TEMPERATURE_CONVERSION_VALUE_ERROR              -403  */
   /*#define ADDIDATA_TEMPERATURE_CONVERSION_UNIT_ERROR               -404  */
   /*#define ADDIDATA_TEMPERATURE_INTERRUPT_FLAG_ERROR                -405  */
   /*#define ADDIDATA_TEMPERATURE_INTERRUPT_NOT_AVAILABLE             -406  */
   /*#define ADDIDATA_TEMPERATURE_WARNING_VALUE_ERROR                 -407  */
   /*#define ADDIDATA_TEMPERATURE_CHANNEL_ALREADY_USED                -408  */
   /*#define ADDIDATA_TEMPERATURE_WARNING_ALREADY_USED                -409  */
   /*************************************************************************/
   
   /************************/
   /* Analog Measure Error */
   /************************/
   #define ADDIDATA_ANALOG_MEASURE_CHANNEL_NUMBER_ERROR             -400  
   #define ADDIDATA_ANALOG_MEASURE_CONVERSION_STARTED               -401  
   #define ADDIDATA_ANALOG_MEASURE_WARNING_FLAG_ERROR               -402  
   #define ADDIDATA_ANALOG_MEASURE_CONVERTING_TIME_ERROR            -403  
   #define ADDIDATA_ANALOG_MEASURE_CONVERTING_TIME_UNIT_ERROR       -404  
   #define ADDIDATA_ANALOG_MEASURE_INTERRUPT_FLAG_ERROR             -405  
   #define ADDIDATA_ANALOG_MEASURE_INTERRUPT_NOT_AVAILABLE          -406  
   #define ADDIDATA_ANALOG_MEASURE_WARNING_VALUE_ERROR              -407
   #define ADDIDATA_ANALOG_MEASURE_CHANNEL_ALREADY_USED             -408  
   #define ADDIDATA_ANALOG_MEASURE_WARNING_ALREADY_USED             -409  
   #define ADDIDATA_ANALOG_MEASURE_GAIN_ERROR			    -410
   #define ADDIDATA_ANALOG_MEASURE_POLARITY_PARAMETER_ERROR	    -411
   #define ADDIDATA_ANALOG_MEASURE_OFFSET_RANGE_ERROR		    -412
   #define ADDIDATA_ANALOG_MEASURE_CHANNEL_NOT_INITIALISED	    -413
   #define ADDIDATA_ANALOG_MEASURE_POLARITY_MODE_NOT_AVAILABLE	    -414
   #define ADDIDATA_ANALOG_MEASURE_SCAN_MODE_NOT_AVAILABLE	    -415
   #define ADDIDATA_ANALOG_MEASURE_SCAN_MODE_PARAMETER_ERROR	    -416
   #define ADDIDATA_ANALOG_MEASURE_EXTERN_TRIGGER_MODE_NOT_AVAILABLE -417
   #define ADDIDATA_ANALOG_MEASURE_EXTERN_TRIGGER_NOT_AVAILABLE     -418
   #define ADDIDATA_ANALOG_MEASURE_EXTERN_TRIGGER_PARAMETER_ERROR   -419
   #define ADDIDATA_ANALOG_MEASURE_EXTERN_GATE_MODE_NOT_AVAILABLE   -420
   #define ADDIDATA_ANALOG_MEASURE_EXTERN_GATE_NOT_AVAILABLE        -421
   #define ADDIDATA_ANALOG_MEASURE_EXTERN_GATE_PARAMETER_ERROR      -422
   #define ADDIDATA_ANALOG_MEASURE_COMMON_GAIN_ERROR		    -423
   #define ADDIDATA_ANALOG_MEASURE_COMMON_POLARITY_ERROR	    -424
   #define ADDIDATA_ANALOG_MEASURE_COMMON_OFFSET_RANGE_ERROR	    -425
   #define ADDIDATA_ANALOG_MEASURE_SCAN_DELAY_NOT_AVAILABLE	    -426
   #define ADDIDATA_ANALOG_MEASURE_SCAN_DELAY_VALUE_ERROR	    -427
   #define ADDIDATA_ANALOG_MEASURE_INTERRUPT_NOT_INSTALLED	    -428
   #define ADDIDATA_ANALOG_MEASURE_SCAN_NOT_INITIALISED		    -429
   #define ADDIDATA_ANALOG_MEASURE_MODULE_NOT_AVAILABLE             -430
   #define ADDIDATA_ANALOG_MEASURE_SCAN_ALREADY_STARTED		    -431
   #define ADDIDATA_ANALOG_MEASURE_SCAN_COUNTER_VALUE_ERROR	    -432
   #define ADDIDATA_ANALOG_MEASURE_SCAN_NOT_STARTED		    -433
   #define ADDIDATA_ANALOG_MEASURE_SCAN_NOT_STOPPED		    -434
   #define ADDIDATA_ANALOG_MEASURE_SCAN_SAME_MODULE_REQUIRED	    -435
   #define ADDIDATA_ANALOG_MEASURE_SCAN_NOT_AVAILABLE		    -436
   #define ADDIDATA_ANALOG_MEASURE_SCAN_CHANNEL_SELECTION_ERROR	    -437
   #define ADDIDATA_ANALOG_MEASURE_SCAN_DELAY_MODE_NOT_AVAILABLE    -438  
   #define ADDIDATA_ANALOG_MEASURE_COUPLING_MODE_NOT_AVAILABLE	    -439
   #define ADDIDATA_ANALOG_MEASURE_COMMON_COUPLING_ERROR	    -440
   #define ADDIDATA_ANALOG_MEASURE_COUPLING_PARAMETER_ERROR	    -441
   #define ADDIDATA_ANALOG_MEASURE_HARDWARE_INDEX_ERROR		    -442
   #define ADDIDATA_ANALOG_MEASURE_CONVERSION_ERROR                 -443
   #define ADDIDATA_ANALOG_MEASURE_INVALID_STRUCTURE                -444
   #define ADDIDATA_ANALOG_MEASURE_SIGN_TEST_PARAMETER_ERROR        -445

   #define ADDIDATA_ANALOG_MEASURE_EXTERN_TRIGGER_FLAG_ERROR			-446
   #define ADDIDATA_ANALOG_MEASURE_EXTERN_TRIGGER_COUNTER_ERROR			-447
   #define ADDIDATA_ANALOG_MEASURE_EXTERN_TRIGGER_ALREADY_USED			-448
   #define ADDIDATA_ANALOG_MEASURE_EXTERN_TRIGGER_NOT_INITIALISED		-449

   #define ADDIDATA_ANALOG_MEASURE_SOFTWARE_TRIGGER_NOT_AVAILABLE		-450
   #define ADDIDATA_ANALOG_MEASURE_SOFTWARE_TRIGGER_MODE_NOT_AVAILABLE		-451
   #define ADDIDATA_ANALOG_MEASURE_SOFTWARE_TRIGGER_FLAG_ERROR			-452
   #define ADDIDATA_ANALOG_MEASURE_SOFTWARE_TRIGGER_ALREADY_USED		-453
   #define ADDIDATA_ANALOG_MEASURE_SOFTWARE_TRIGGER_NOT_INITIALISED		-454

   #define ADDIDATA_ANALOG_MEASURE_EXTERN_GATE_FLAG_ERROR			-455
   #define ADDIDATA_ANALOG_MEASURE_EXTERN_GATE_ALREADY_USED			-456
   #define ADDIDATA_ANALOG_MEASURE_EXTERN_GATE_NOT_INITIALISED			-457

   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_SAME_MODULE_REQUIRED		-458
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_DELAY_NOT_AVAILABLE			-459
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_DELAY_VALUE_ERROR			-460
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_DELAY_TIME_UNIT_ERROR	        -461
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_ALREADY_STARTED			-462
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_COUNTER_VALUE_ERROR			-463
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_INTERRUPT_COUNTER_VALUE_ERROR	-464
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_NOT_STARTED				-465
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_NOT_STOPPED				-466
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_CHANNEL_SELECTION_ERROR		-467
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_DELAY_MODE_NOT_AVAILABLE		-468  
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_NO_FREE_HANDLE_FOUND		-469  
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_MEMORY_ALLOCATION_ERROR		-470
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_DESCRIPTION_LIST_CREATION_ERROR	-471
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_HANDLE_ERROR			-472

   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_DELAY_MODE_SETTING_ERROR		-473
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_DESCRIPTION_LIST_SETTING_ERROR	-474
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_RESET_DESCRIPTION_LIST_ERROR	-475
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_ENABLE_TRANSFER_ERROR		-476
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_START_TRANSFER_ERROR		-477
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_STOP_TRANSFER_ERROR			-478
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_CONTINUE_TRANSFER_ERROR		-479
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_PAUSE_TRANSFER_ERROR		-480
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_ABORT_TRANSFER_ERROR		-481
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_ENABLE_TRANSFER_INTERRUPT_ERROR	-482
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_DISABLE_TRANSFER_INTERRUPT_ERROR	-483

   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_MODULE_INITIALISATION_ERROR		-484
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_MODULE_MODE_INITIALISATION_ERROR	-485
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_MODULE_MODE_CLEAR_INDEX_ERROR	-486
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_MODULE_START_ERROR			-487
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_MODULE_PAUSE_ERROR			-488
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_MODULE_STOP_ERROR			-489

   
   #define ADDIDATA_TRANSDUCER_TYPE_SELECTION_ERROR				-490
   #define ADDIDATA_TRANSDUCER_FREQUENCY_SELECTION_ERROR			-491
   #define ADDIDATA_TRANSDUCER_PRIMARY_MODULE_CONNECTION_TEST_ALREADY_USED	-492
   #define ADDIDATA_TRANSDUCER_PRIMARY_MODULE_CONNECTION_FLAG_ERROR		-493
   #define ADDIDATA_TRANSDUCER_NO_SENSOR_CONNECTED				-494
// Begin SW : 16.06.03 PVCS ADDIDATA_TRANSDUCER_PRIMARY_SHORT_CIRCUIT_OCCUR implementation
   #define ADDIDATA_TRANSDUCER_PRIMARY_SHORT_CIRCUIT_OCCUR			-497
// End SW : 16.06.03 PVCS ADDIDATA_TRANSDUCER_PRIMARY_SHORT_CIRCUIT_OCCUR implementation

   #define ADDIDATA_ANALOG_MEASURE_AUTO_REFRESH_NOT_STARTED		        -495
   #define ADDIDATA_ANALOG_MEASURE_AUTO_REFRESH_NOT_STOPPED		        -496
   #define ADDIDATA_ANALOG_MEASURE_SEQUENCE_SAME_FREQUENCY_REQUIRED             -498
   #define ADDIDATA_ANALOG_MEASURE_CONVERT_TIME_DIVISION_FACTOR_ALREADY_USED    -900
   #define ADDIDATA_ANALOG_MEASURE_CONVERT_TIME_DIVISION_FACTOR_VALUE_ERROR     -901
   #define ADDIDATA_ANALOG_MEASURE_CONVERT_TIME_DIVISION_FACTOR_NOT_INITIALISED -902


   

   /***********************/
   /* Digital input error */
   /***********************/

   #define ADDIDATA_DIGITAL_INPUT_CHANNEL_NUMBER_ERROR               -500
   #define ADDIDATA_DIGITAL_INPUT_PORT_NUMBER_ERROR                  -501
   #define ADDIDATA_DIGITAL_INPUT_ACCESS_ERROR                       -502
   // BEGIN 01/01/2001 RH 0800-0200 -> 1200-0205
   #define ADDIDATA_DIGITAL_INPUT_INTERRUPT_ALREADY_USED             -503
   #define ADDIDATA_DIGITAL_INPUT_INTERRUPT_ALREADY_RELEASED         -504
   #define ADDIDATA_DIGITAL_INPUT_INTERRUPT_FLAG_ERROR		     -505
   #define ADDIDATA_DIGITAL_INPUT_INTERRUPT_LOGIC_ERROR		     -506
   // END 01/01/2001 RH 0800-0200 -> 1200-0205

   // Begin 27.11.2001 S.WEBER 1101-0218 -> 1101-0219
   #define ADDIDATA_DIGITAL_INPUT_INFORMATION_STRUCTURE_INVALID_SIZE -507
   #define ADDIDATA_DIGITAL_INPUT_LEVEL_VALUE_SELECTION_ERROR        -508
   #define ADDIDATA_DIGITAL_INPUT_CHANNEL_ARRAY_SIZE_ERROR           -509
   #define ADDIDATA_DIGITAL_INPUT_CHANNEL_SELECTION_ERROR	     -510
   #define ADDIDATA_DIGITAL_INPUT_MODULE_SELECTION_ERROR             -511
   #define ADDIDATA_DIGITAL_INPUT_FILTER_UNIT_ERROR		     -512
   #define ADDIDATA_DIGITAL_INPUT_FILTER_DELAY_VALUE_ERROR	     -513
   #define ADDIDATA_DIGITAL_INPUT_FILTER_NOT_INITIALISED             -514
   #define ADDIDATA_DIGITAL_INPUT_FILTER_FLAG_ERROR                  -515
   #define ADDIDATA_DIGITAL_INPUT_LEVEL_FLAG_ERROR		     -516
   // End 27.11.2001 S.WEBER 1101-0218 -> 1101-0219
   
   // Begin 03/03/03 CG : Add the test of the digital input mask
   #define ADDIDATA_DIGITAL_INPUT_MASK_ERROR			     -517
   // End 03/03/03 CG : Add the test of the digital input mask

   /************************/
   /* Digital output error */
   /************************/

   #define ADDIDATA_DIGITAL_OUTPUT_CHANNEL_NUMBER_ERROR              -600
   #define ADDIDATA_DIGITAL_OUTPUT_PORT_NUMBER_ERROR                 -601
   #define ADDIDATA_DIGITAL_OUTPUT_VALUE_ERROR                       -602
   #define ADDIDATA_DIGITAL_OUTPUT_ACCESS_ERROR                      -603
   #define ADDIDATA_DIGITAL_OUTPUT_MEMORY_ALREADY_ENABLED            -604
   #define ADDIDATA_DIGITAL_OUTPUT_MEMORY_ALREADY_DISABLED           -605
   // BEGIN 01/01/2001 RH 0800-0200 -> 1200-0205
   #define ADDIDATA_DIGITAL_OUTPUT_INTERRUPT_ALREADY_USED            -606
   #define ADDIDATA_DIGITAL_OUTPUT_INTERRUPT_ALREADY_RELEASED        -607
   #define ADDIDATA_DIGITAL_OUTPUT_INTERRUPT_FLAG_ERROR		     -608
   // END 01/01/2001 RH 0800-0200 -> 1200-0205
   

   /***********************/
   /* Analog output error */
   /***********************/

   #define ADDIDATA_ANALOG_OUTPUT_CHANNEL_NUMBER_ERROR               -700
   #define ADDIDATA_ANALOG_OUTPUT_VOLTAGE_MODE_ERROR		         -701
   #define ADDIDATA_ANALOG_OUTPUT_POLARITY_ERROR                     -702
   #define ADDIDATA_ANALOG_OUTPUT_VALUE_ERROR                        -703
   #define ADDIDATA_ANALOG_OUTPUT_ENABLE_DISABLE_SYNC_ERROR          -704
   #define ADDIDATA_ANALOG_OUTPUT_ALREADY_USED                       -705
   // Begin 17/04/01 RH 0800/0200 -> 0900/0210
   #define ADDIDATA_ANALOG_OUTPUT_TIMEOUT                           -706
   #define ADDIDATA_ANALOG_OUTPUT_TIMEOUT_ERROR                     -707
      // Begin 30/01/01 CG 1200/0205 -> 0900/0210
   #define ADDIDATA_ANALOG_OUTPUT_ALREADY_RELEASED                   -708
      // End 30/01/01 CG 1200/0205 -> 0900/0210
   // End 17/04/01 RH 0800/0200 -> 0900/0210


   /****************************************************************************/
   /* CG 13/09/00 0800/0200 -> 0900/0210				       */ 
   /* replace the temperature enumeration by the analog measure enumeration    */
   /****************************************************************************/
   /* Temperature type enumeration                                             */
   /****************************************************************************/
   /*                                                                          */
   /*enum                                                                      */
   /*   {                                                                      */  
   /*   ADDIDATA_RTD,                                                          */   
   /*   ADDIDATA_CJC,                                                          */
   /*   ADDIDATA_THERMOCOUPLE,                                                 */ 
   /*   ADDIDATA_ON_BOARD                                                      */
   /*   }ADDIDATA_TEMPERATURE_TYPE_ENUMERATION;                                */
   /****************************************************************************/
   
   /****************************************************************************/
   /* Analog measure enumeration                                               */
   /****************************************************************************/
   enum
      {
      ADDIDATA_RTD,
      ADDIDATA_THERMOCOUPLE,
      ADDIDATA_TEMPERATURE_ON_BOARD,
      ADDIDATA_OHM,
      ADDIDATA_ANALOG_INPUT_V_OR_I,
      ADDIDATA_PRESSURE_CHANNEL,
      ADDIDATA_TRANSDUCER_CHANNEL
// Begin Änderung 11/09/01 |R. HILPERT | 0801/0215 -> 0901/02151                        
//      }ADDIDATA_ANALOG_MEASURE_TYPE_ENUMERATION;
      };
// End Änderung 11/09/01 |R. HILPERT | 0801/0215 -> 0901/02151                        
   
   #define ADDIDATA_THERMOCOUPLE_TYPE_B   0
   #define ADDIDATA_THERMOCOUPLE_TYPE_E   1
   #define ADDIDATA_THERMOCOUPLE_TYPE_J   2
   #define ADDIDATA_THERMOCOUPLE_TYPE_K   3
   #define ADDIDATA_THERMOCOUPLE_TYPE_N   4
   #define ADDIDATA_THERMOCOUPLE_TYPE_R   5
   #define ADDIDATA_THERMOCOUPLE_TYPE_S   6
   #define ADDIDATA_THERMOCOUPLE_TYPE_T   7

   #define ADDIDATA_RTD_TYPE_PT		  0
   #define ADDIDATA_RTD_TYPE_Ni		  1  

   #define ADDIDATA_ANALOG_INPUT_TYPE_V   0
   #define ADDIDATA_ANALOG_INPUT_TYPE_I   1


   

   /****************************************************************************/
   /* CG 13/09/00 0800/0200 -> 0900/0210                                       */
   /* Analog Measure Define                                                    */ 
   /****************************************************************************/
   #define ADDIDATA_SINGLE_SCAN		0
   #define ADDIDATA_DEFINED_SCAN_NUMBER 1
   #define ADDIDATA_CONTINUOUS_SCAN     2
   
   #define ADDIDATA_DELAY_NOT_USED	0
   #define ADDIDATA_DELAY_MODE1_USED	1
   #define ADDIDATA_DELAY_MODE2_USED    2  

   #define ADDIDATA_FIRST_LOW_EDGE_START_ALL_SCAN   1
   #define ADDIDATA_FIRST_HIGH_EDGE_START_ALL_SCAN  2
   #define ADDIDATA_FIRST_EDGE_START_ALL_SCAN	    3
   #define ADDIDATA_EACH_LOW_EDGE_START_A_SCAN	    4
   #define ADDIDATA_EACH_HIGH_EDGE_START_A_SCAN	    5
   #define ADDIDATA_EACH_EDGE_START_A_SCAN	    6
   #define ADDIDATA_EACH_LOW_EDGE_START_A_SINGLE_ACQUISITION	7
   #define ADDIDATA_EACH_HIGH_EDGE_START_A_SINGLE_ACQUISITION	8
   #define ADDIDATA_EACH_EDGE_START_A_SINGLE_ACQUISITION	9

   #define ADDIDATA_DC_COUPLING 0
   #define ADDIDATA_AC_COUPLING 1

   #define ADDIDATA_GREATER_THAN_TEST 0
   #define ADDIDATA_LESS_THAN_TEST 1

   #define ADDIDATA_TRIGGER_START_A_SINGLE_CONVERSION	0
   #define ADDIDATA_ONE_SHOT_TRIGGER			1
   #define ADDIDATA_TRIGGER_START_A_SEQUENCE_SERIES	2
   #define ADDIDATA_TRIGGER_START_A_SINGLE_SEQUENCE	3
   
   /****************************************************************************/
   /* Enable/disable define                                                    */
   /****************************************************************************/

   #define ADDIDATA_DISABLE        0
   #define ADDIDATA_ENABLE         1

   /****************************************************************************/
   /* Define the level                                                         */
   /****************************************************************************/

   #define ADDIDATA_LOW            1
   #define ADDIDATA_HIGH           2
   #define ADDIDATA_LOW_HIGH       3

   /****************************************************************************/
   /* Define the logic                                                         */
   /****************************************************************************/

   #define ADDIDATA_OR             1
   #define ADDIDATA_AND            2

   /****************************************************************************/
   /* Up/Down define                                                           */
   /****************************************************************************/

   #define ADDIDATA_DOWN           0
   #define ADDIDATA_UP             1

   /****************************************************************************/
   /* Define the user call back function mode                                  */
   /****************************************************************************/

   #define ADDIDATA_ASYNCHRONOUS   0
   #define ADDIDATA_SYNCHRONOUS    1
   #define ADDIDATA_VB             2

   /****************************************************************************/
   /* Function enumeration                                                     */
   /****************************************************************************/

   enum
      {
      /*******************************************************************/
      /* Init.c                                                          */
      /*******************************************************************/

      ADDIDATA_OPEN_WIN32_DRIVER = 10,
      ADDIDATA_CLOSE_WIN32_DRIVER,
// Begin  | 19/09/01 |R. HILPERT | 0901/02151 -> 0901/02152                       |
      ADDIDATA_GET_CURRENT_DRIVER_HANDLE = 14,
// End  | 19/09/01 |R. HILPERT | 0901/02151 -> 0901/02152                       |

      ADDIDATA_SET_FUNCTIONALITY_INT_ROUTINE = 50,
      ADDIDATA_TEST_INTERRUPT,
      ADDIDATA_RESET_FUNCTIONALITY_INT_ROUTINE,

      /*******************************************************************/
      /* Error.c                                                         */
      /*******************************************************************/

      ADDIDATA_GET_LAST_ERROR_MESSAGE = 100,
      ADDIDATA_ENABLE_ERROR_MESSAGE,
      ADDIDATA_DISABLE_ERROR_MESSAGE,
      // Begin 26/03/2001 CG 0800/0200 -> 0900/0210 : New function
      ADDIDATA_FORMAT_ERROR_MESSAGE,
      // End 26/03/2001 CG 0800/0200 -> 0900/0210 : New function

      /*******************************************************************/
      /* Timer.c                                                         */
      /*******************************************************************/

      ADDIDATA_GET_NUMBER_OF_TIMERS = 200,
      ADDIDATA_GET_TIMER_INFORMATION,
      ADDIDATA_INIT_TIMER,
      ADDIDATA_ENABLE_DISABLE_TIMER_INTERRUPT,
      ADDIDATA_START_TIMER,
      ADDIDATA_START_ALL_TIMERS,
      ADDIDATA_TRIGGER_TIMER,
      ADDIDATA_TRIGGER_ALL_TIMERS,
      ADDIDATA_STOP_TIMER,
      ADDIDATA_STOP_ALL_TIMERS,
      ADDIDATA_READ_TIMER_VALUE,
      ADDIDATA_READ_TIMER_STATUS,
      ADDIDATA_ENABLE_DISABLE_TIMER_HARDWARE_GATE,
      ADDIDATA_GET_TIMER_HARDWARE_GATE_STATUS,
      ADDIDATA_ENABLE_DISABLE_TIMER_HARDWARE_TRIGGER,
      ADDIDATA_GET_TIMER_HARDWARE_TRIGGER_STATUS,
      ADDIDATA_ENABLE_DISABLE_TIMER_HARDWARE_OUTPUT,
      ADDIDATA_GET_TIMER_HARDWARE_OUTPUT_STATUS,
      ADDIDATA_RELEASE_TIMER,
      // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
      ADDIDATA_TEST_TIMER_ASYNCHRONOUS_FIFO_FULL,
      // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management

      /*******************************************************************/
      /* Counter.c                                                       */
      /*******************************************************************/

      ADDIDATA_GET_NUMBER_OF_COUNTERS = 1000,
      ADDIDATA_GET_COUNTER_INFORMATION,
      ADDIDATA_INIT_COUNTER,
      ADDIDATA_COUNTER_DIRECTION,
      ADDIDATA_ENABLE_DISABLE_COUNTER_INTERRUPT,
      ADDIDATA_START_COUNTER,
      ADDIDATA_START_ALL_COUNTERS,
      ADDIDATA_CLEAR_COUNTER,
      ADDIDATA_TRIGGER_COUNTER,
      ADDIDATA_TRIGGER_ALL_COUNTERS,
      ADDIDATA_STOP_COUNTER,
      ADDIDATA_STOP_ALL_COUNTERS,
      ADDIDATA_READ_COUNTER_VALUE,
      ADDIDATA_READ_COUNTER_STATUS,
      ADDIDATA_ENABLE_DISABLE_COUNTER_HARDWARE_GATE,
      ADDIDATA_GET_COUNTER_HARDWARE_GATE_STATUS,
      ADDIDATA_ENABLE_DISABLE_COUNTER_HARDWARE_TRIGGER,
      ADDIDATA_GET_COUNTER_HARDWARE_TRIGGER_STATUS,
      ADDIDATA_ENABLE_DISABLE_COUNTER_HARDWARE_OUTPUT,
      ADDIDATA_GET_COUNTER_HARDWARE_OUTPUT_STATUS,
      ADDIDATA_RELEASE_COUNTER,
      // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
      ADDIDATA_TEST_COUNTER_ASYNCHRONOUS_FIFO_FULL,
      // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management

      /*******************************************************************/
      /* Watchdog.c                                                      */
      /*******************************************************************/

      ADDIDATA_GET_NUMBER_OF_WATCHDOGS = 300,
      ADDIDATA_GET_WATCHDOG_INFORMATION,
      ADDIDATA_INIT_WATCHDOG,
      ADDIDATA_ENABLE_DISABLE_WATCHDOG_INTERRUPT,
      ADDIDATA_START_WATCHDOG,
      ADDIDATA_START_ALL_WATCHDOGS,
      ADDIDATA_TRIGGER_WATCHDOG,
      ADDIDATA_TRIGGER_ALL_WATCHDOGS,
      ADDIDATA_STOP_WATCHDOG,
      ADDIDATA_STOP_ALL_WATCHDOGS,
      ADDIDATA_READ_WATCHDOG_STATUS,
      ADDIDATA_ENABLE_DISABLE_WATCHDOG_HARDWARE_GATE,
      ADDIDATA_GET_WATCHDOG_HARDWARE_GATE_STATUS,
      ADDIDATA_ENABLE_DISABLE_WATCHDOG_HARDWARE_TRIGGER,
      ADDIDATA_GET_WATCHDOG_HARDWARE_TRIGGER_STATUS,
      ADDIDATA_GET_WARNING_DELAY_INFORMATION,
      ADDIDATA_INIT_WARNING_DELAY,
      ADDIDATA_ENABLE_DISABLE_WATCHDOG_WARNING_RELAY,
      ADDIDATA_ENABLE_DISABLE_WATCHDOG_RESET_RELAY,
      ADDIDATA_RELEASE_WATCHDOG,
//Begin :  |09.10.2001| R. HILPERT| 0801-0216 -> 0801-0216                         |
      ADDIDATA_GET_WATCHDOG_INFORMATION_EX,
      ADDIDATA_SET_WATCHDOG_RESET_RELAY_MODE,
//End :  |09.10.2001| R. HILPERT| 0801-0216 -> 0801-0216                         |
      // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
      ADDIDATA_TEST_WATCHDOG_ASYNCHRONOUS_FIFO_FULL,
      // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management

      /*******************************************************************/
      /* Temperature.c                                                    */
      /*******************************************************************/

      // Begin CG 18/09/2000 0800/0200 -> 0900/0210
      ADDIDATA_INIT_TEMPERATURE_CHANNEL                       = 400,
      // End CG 18/09/2000 0800/0200 -> 0900/0210
      ADDIDATA_READ_1_TEMPERATURE_CHANNEL,
      // Begin CG 18/09/2000 0800/0200 -> 0900/0210
      ADDIDATA_GET_NUMBER_OF_TEMPERATURE_CHANNELS,
      ADDIDATA_CONVERT_DIGITAL_TO_REAL_TEMPERATURE_VALUE,
      ADDIDATA_GET_TEMPERATURE_CHANNEL_INFORMATION,
      // End CG 18/09/2000 0800/0200 -> 0900/0210
      ADDIDATA_INIT_TEMPERATURE_WARNING,
      ADDIDATA_ENABLE_DISABLE_TEMPERATURE_WARNING_CHANNEL,
      ADDIDATA_START_ALL_TEMPERATURE_WARNINGS,
      ADDIDATA_STOP_ALL_TEMPERATURE_WARNINGS,
      ADDIDATA_RELEASE_TEMPERATURE_WARNING,
      ADDIDATA_RELEASE_TEMPERATURE_CHANNEL,
      // Begin CG 18/09/2000 0800/0200 -> 0900/0210
      ADDIDATA_READ_MORE_TEMPERATURE_CHANNELS,
      ADDIDATA_INIT_TEMPERATURE_CHANNEL_SCAN,
      ADDIDATA_START_TEMPERATURE_CHANNEL_SCAN,
      ADDIDATA_GET_TEMPERATURE_CHANNEL_SCAN_STATUS,
      ADDIDATA_CONVERT_DIGITAL_TO_REAL_TEMPERATURE_VALUE_SCAN,
      ADDIDATA_STOP_TEMPERATURE_CHANNEL_SCAN,
      ADDIDATA_CLOSE_TEMPERATURE_CHANNEL_SCAN,
      ADDIDATA_INIT_TEMPERATURE_CHANNEL_VIA_INIT_FILE,
      ADDIDATA_GET_NUMBER_OF_TEMPERATURE_MODULES,
      ADDIDATA_GET_NUMBER_OF_TEMPERATURE_CHANNELS_FOR_THE_MODULE,
      ADDIDATA_CONVERT_DIGITAL_TO_REAL_TEMPERATURE_VALUE_WITH_CORRECTION_PARAMETERS,
      ADDIDATA_CONVERT_MORE_DIGITAL_TO_REAL_TEMPERATURE_VALUES,
      ADDIDATA_TEST_TEMPERATURE_CHANNEL_SHORT_CIRCUIT,
      ADDIDATA_TEST_TEMPERATURE_CHANNEL_CONNECTION,
      // End CG 18/09/2000 0800/0200 -> 0900/0210
      // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
      ADDIDATA_TEST_TEMPERATURE_ASYNCHRONOUS_FIFO_FULL,
      // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management




      /****************************************************************/
      /* Dig_inp.c                                                    */
      /****************************************************************/

      ADDIDATA_GET_NUMBER_OF_DIGITAL_INPUTS                    = 500,
      ADDIDATA_GET_DIGITAL_INPUT_INFORMATION,
      ADDIDATA_READ_1_DIGITAL_INPUT,
      ADDIDATA_READ_2_DIGITAL_INPUTS,
      ADDIDATA_READ_4_DIGITAL_INPUTS,
      ADDIDATA_READ_8_DIGITAL_INPUTS,
      ADDIDATA_READ_16_DIGITAL_INPUTS,
      ADDIDATA_READ_32_DIGITAL_INPUTS,
      // BEGIN 01/01/2001 RH 0800-0200 -> 1200-0205
      ADDIDATA_INIT_DIGITAL_INPUT_INTERRUPT,
      ADDIDATA_ENABLE_DISABLE_DIGITAL_INPUT_INTERRUPT,
      ADDIDATA_RELEASE_DIGITAL_INPUT_INTERRUPT,
      // END 01/01/2001 RH 0800-0200 -> 1200-0205
      
      // Begin 27.11.2001 S.WEBER 1101-0218 -> 1101-0219
      ADDIDATA_GET_DIGITAL_INPUT_INFORMATION_EX,
      ADDIDATA_INIT_1_DIGITAL_INPUT_LEVEL,
      ADDIDATA_READ_1_DIGITAL_INPUT_STATUS,
      ADDIDATA_READ_MORE_DIGITAL_INPUT_STATUS,
      ADDIDATA_READ_1_DIGITAL_INPUT_VALUE,
      ADDIDATA_READ_MORE_DIGITAL_INPUT_VALUE,
      ADDIDATA_CONVERT_1_DIGITAL_INPUT_VALUE,
      ADDIDATA_GET_DIGITAL_INPUT_MODULE_FILTER_INFORMATION,
      ADDIDATA_INIT_DIGITAL_INPUT_MODULE_FILTER,
      ADDIDATA_ENABLE_DISABLE_DIGITAL_INPUT_MODULE_FILTER,
      ADDIDATA_SET_DIGITAL_INPUT_MODULE_LEVEL_SELECTION,
      ADDIDATA_SAVE_DIGITAL_INPUT_MODULE_LEVEL,
      // End 27.11.2001 S.WEBER 1101-0218 -> 1101-0219
      // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
      ADDIDATA_TEST_DIGITAL_INPUT_ASYNCHRONOUS_FIFO_FULL,
      // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management

      /****************************************************************/
      /* Dig_out.c                                                    */
      /****************************************************************/

      ADDIDATA_GET_NUMBER_OF_DIGITAL_OUTPUTS                    = 600,
      ADDIDATA_GET_DIGITAL_OUTPUT_INFORMATION,
      ADDIDATA_SET_DIGITAL_OUTPUT_MEMORY_ON,
      ADDIDATA_SET_DIGITAL_OUTPUT_MEMORY_OFF,
      ADDIDATA_SET_1_DIGITAL_OUTPUT_ON,
      ADDIDATA_SET_2_DIGITAL_OUTPUTS_ON,
      ADDIDATA_SET_4_DIGITAL_OUTPUTS_ON,
      ADDIDATA_SET_8_DIGITAL_OUTPUTS_ON,
      ADDIDATA_SET_16_DIGITAL_OUTPUTS_ON,
      ADDIDATA_SET_32_DIGITAL_OUTPUTS_ON,
      ADDIDATA_SET_1_DIGITAL_OUTPUT_OFF,
      ADDIDATA_SET_2_DIGITAL_OUTPUTS_OFF,
      ADDIDATA_SET_4_DIGITAL_OUTPUTS_OFF,
      ADDIDATA_SET_8_DIGITAL_OUTPUTS_OFF,
      ADDIDATA_SET_16_DIGITAL_OUTPUTS_OFF,
      ADDIDATA_SET_32_DIGITAL_OUTPUTS_OFF,
      ADDIDATA_GET_1_DIGITAL_OUTPUT_STATUS,
      ADDIDATA_GET_2_DIGITAL_OUTPUT_STATUS,
      ADDIDATA_GET_4_DIGITAL_OUTPUT_STATUS,
      ADDIDATA_GET_8_DIGITAL_OUTPUT_STATUS,
      ADDIDATA_GET_16_DIGITAL_OUTPUT_STATUS,
      ADDIDATA_GET_32_DIGITAL_OUTPUT_STATUS,
      // BEGIN 01/01/2001 RH 0800-0200 -> 1200-0205
      ADDIDATA_SET_ALL_DIGITAL_OUTPUT_OFF,
      ADDIDATA_INIT_DIGITAL_OUTPUT_INTERRUPT,
      ADDIDATA_ENABLE_DISABLE_DIGITAL_OUTPUT_INTERRUPT,
      ADDIDATA_RELEASE_DIGITAL_OUTPUT_INTERRUPT,
      // END 01/01/2001 RH 0800-0200 -> 1200-0205
      // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
      ADDIDATA_TEST_DIGITAL_OUTPUT_ASYNCHRONOUS_FIFO_FULL,
      // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management

      /****************************************************************/
      /* Ana_out.c                                                    */
      /****************************************************************/

      ADDIDATA_GET_NUMBER_OF_ANALOG_OUTPUTS                    = 700,
      ADDIDATA_GET_ANALOG_OUTPUT_INFORMATION,
      ADDIDATA_INIT_1_ANALOG_OUTPUT,
      ADDIDATA_INIT_MORE_ANALOG_OUTPUTS,
      ADDIDATA_WRITE_1_ANALOG_OUTPUT,
      ADDIDATA_WRITE_MORE_ANALOG_OUTPUTS,
      ADDIDATA_RELEASE_1_ANALOG_OUTPUT,
      ADDIDATA_RELEASE_MORE_ANALOG_OUTPUTS,
      ADDIDATA_ENABLE_DISABLE_1_ANALOG_OUTPUT_SYNC,
      ADDIDATA_ENABLE_DISABLE_MORE_ANALOG_OUTPUTS_SYNC,
      ADDIDATA_TRIGGER_ANALOG_OUTPUT,

      /****************************************************************/
      /* Ana_inp.c                                                    */
      /****************************************************************/
      ADDIDATA_GET_NUMBER_OF_ANALOG_INPUTS             = 800,
      ADDIDATA_GET_NUMBER_OF_ANALOG_INPUT_MODULES,
      ADDIDATA_GET_NUMBER_OF_ANALOG_INPUTS_FOR_THE_MODULE,
      ADDIDATA_GET_ANALOG_INPUT_INFORMATION,
      ADDIDATA_INIT_ANALOG_INPUT,
      ADDIDATA_TEST_ANALOG_INPUT_SHORT_CIRCUIT,
      ADDIDATA_TEST_ANALOG_INPUT_CONNECTION,
      ADDIDATA_READ_1_ANALOG_INPUT,
      ADDIDATA_READ_MORE_ANALOG_INPUTS,
      ADDIDATA_CONVERT_DIGITAL_TO_REAL_ANALOG_VALUE,
      ADDIDATA_CONVERT_MORE_DIGITAL_TO_REAL_ANALOG_VALUES,
      ADDIDATA_INIT_ANALOG_INPUT_SCAN,
      ADDIDATA_START_ANALOG_INPUT_SCAN,
      ADDIDATA_GET_ANALOG_INPUT_SCAN_STATUS,
      ADDIDATA_CONVERT_DIGITAL_TO_REAL_ANALOG_VALUE_SCAN,
      ADDIDATA_STOP_ANALOG_INPUT_SCAN,
      ADDIDATA_CLOSE_ANALOG_INPUT_SCAN,
      ADDIDATA_RELEASE_ANALOG_INPUT,
      // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
      ADDIDATA_TEST_ANALOG_INPUT_ASYNCHRONOUS_FIFO_FULL,
      // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management

      // Begin SW 15/01/03 2226/1102 -> 2227-0103: New function implementation
      ADDIDATA_GET_ANALOG_INPUT_MODULE_NUMBER,
      ADDIDATA_GET_ANALOG_INPUT_MODULE_AUTO_REFRESH_ACQUISITION_INFORMATION,
      ADDIDATA_GET_ANALOG_INPUT_MODULE_SEQUENCE_ACQUISITION_INFORMATION,

      ADDIDATA_GET_ANALOG_INPUT_AUTO_REFRESH_CHANNEL_POINTER,
      ADDIDATA_GET_ANALOG_INPUT_AUTO_REFRESH_MODULE_POINTER,
      ADDIDATA_START_ANALOG_INPUT_AUTO_REFRESH,
      ADDIDATA_STOP_ANALOG_INPUT_AUTO_REFRESH,
      ADDIDATA_READ_1_ANALOG_INPUT_AUTO_REFRESH_VALUE,

      ADDIDATA_INIT_ANALOG_INPUT_SEQUENCE_ACQUISITION,
      ADDIDATA_START_ANALOG_INPUT_SEQUENCE_ACQUISITION,
      ADDIDATA_PAUSE_ANALOG_INPUT_SEQUENCE_ACQUISITION,
      ADDIDATA_STOP_ANALOG_INPUT_SEQUENCE_ACQUISITION,
      ADDIDATA_RELEASE_ANALOG_INPUT_SEQUENCE_ACQUISITION,
      ADDIDATA_CONVERT_DIGITAL_TO_REAL_ANALOG_VALUE_SEQUENCE,
      ADDIDATA_GET_ANALOG_INPUT_SEQUENCE_ACQUISITION_HANDLE_STATUS,

      ADDIDATA_GET_ANALOG_INPUT_HARDWARE_TRIGGER_INFORMATIONS,
      ADDIDATA_ENABLE_DISABLE_ANALOG_INPUT_HARDWARE_TRIGGER,
      ADDIDATA_GET_ANALOG_INPUT_HARDWARE_TRIGGER_STATUS,
      ADDIDATA_ENABLE_DISABLE_ANALOG_INPUT_SOFTWARE_TRIGGER,
      ADDIDATA_ANALOG_INPUT_SOFTWARE_TRIGGER,
      ADDIDATA_GET_ANALOG_INPUT_SOFTWARE_TRIGGER_STATUS,


      // End SW 15/01/03 2226/1102 -> 2227-0103: New function implementation
              
      /**************************************************************/
      /* Resis.c                                                    */
      /**************************************************************/
      ADDIDATA_GET_NUMBER_OF_RESISTANCE_CHANNELS             = 900,
      ADDIDATA_GET_NUMBER_OF_RESISTANCE_MODULES,
      ADDIDATA_GET_NUMBER_OF_RESISTANCE_CHANNELS_FOR_THE_MODULE,
      ADDIDATA_GET_RESISTANCE_CHANNEL_INFORMATION,
      ADDIDATA_INIT_RESISTANCE_CHANNEL,
      ADDIDATA_TEST_RESISTANCE_CHANNEL_SHORT_CIRCUIT,
      ADDIDATA_TEST_RESISTANCE_CHANNEL_CONNECTION,
      ADDIDATA_READ_1_RESISTANCE_CHANNEL,
      ADDIDATA_READ_MORE_RESISTANCE_CHANNELS,
      ADDIDATA_CONVERT_DIGITAL_TO_REAL_RESISTANCE_VALUE,
      ADDIDATA_CONVERT_MORE_DIGITAL_TO_REAL_RESISTANCE_VALUES,
      ADDIDATA_INIT_RESISTANCE_CHANNEL_SCAN,
      ADDIDATA_START_RESISTANCE_CHANNEL_SCAN,
      ADDIDATA_GET_RESISTANCE_CHANNEL_SCAN_STATUS,
      ADDIDATA_CONVERT_DIGITAL_TO_REAL_RESISTANCE_VALUE_SCAN,
      ADDIDATA_STOP_RESISTANCE_CHANNEL_SCAN,
      ADDIDATA_CLOSE_RESISTANCE_CHANNEL_SCAN,
      ADDIDATA_RELEASE_RESISTANCE_CHANNEL,
      // End CG 22/09/00 0800/0200 -> 0900/0210
      // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
      ADDIDATA_TEST_RESISTANCE_ASYNCHRONOUS_FIFO_FULL,
      // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management

      /****************************************************************/
      /* Pressure.c                                                   */
      /****************************************************************/
      ADDIDATA_GET_NUMBER_OF_PRESSURE_CHANNELS             = 1100,
      ADDIDATA_GET_NUMBER_OF_PRESSURE_MODULES,
      ADDIDATA_GET_NUMBER_OF_PRESSURE_CHANNELS_FOR_THE_MODULE,
      ADDIDATA_GET_PRESSURE_CHANNEL_INFORMATION,
      ADDIDATA_INIT_PRESSURE_CHANNEL,
      ADDIDATA_READ_1_PRESSURE_CHANNEL,
      ADDIDATA_READ_MORE_PRESSURE_CHANNELS,
      ADDIDATA_CONVERT_DIGITAL_TO_REAL_PRESSURE_VALUE,
      ADDIDATA_CONVERT_MORE_DIGITAL_TO_REAL_PRESSURE_VALUES,
      ADDIDATA_INIT_PRESSURE_SCAN,
      ADDIDATA_START_PRESSURE_SCAN,
      ADDIDATA_GET_PRESSURE_SCAN_STATUS,
      ADDIDATA_CONVERT_DIGITAL_TO_REAL_PRESSURE_SCAN,
      ADDIDATA_STOP_PRESSURE_SCAN,
      ADDIDATA_CLOSE_PRESSURE_SCAN,
      ADDIDATA_RELEASE_PRESSURE_CHANNEL,
      // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
      ADDIDATA_TEST_PRESSURE_ASYNCHRONOUS_FIFO_FULL,
      // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
      ADDIDATA_GET_PRESSURE_CHANNEL_REFERENCE_VOLTAGE,
      ADDIDATA_GET_PRESSURE_CHANNEL_GAIN_FACTOR,

      /****************************************************************/
      /* Transducer.c                                                 */
      /****************************************************************/
      ADDIDATA_GET_NUMBER_OF_TRANSDUCERS_CHANNELS             = 1200,
      ADDIDATA_GET_NUMBER_OF_TRANSDUCER_MODULES,
      ADDIDATA_GET_NUMBER_OF_TRANSDUCER_CHANNELS_FOR_THE_MODULE,
      ADDIDATA_GET_TRANSDUCER_CHANNEL_MODULE_NUMBER,
      ADDIDATA_GET_TRANSDUCER_MODULE_GENERAL_INFORMATION,
      ADDIDATA_GET_TRANSDUCER_MODULE_SINGLE_ACQUISITION_INFORMATION,
      ADDIDATA_GET_TRANSDUCER_MODULE_AUTO_REFRESH_ACQUISITION_INFORMATION,
      ADDIDATA_GET_TRANSDUCER_MODULE_SEQUENCE_ACQUISITION_INFORMATION,
      ADDIDATA_INIT_TRANSDUCER_CHANNEL,
      ADDIDATA_RELEASE_TRANSDUCER_CHANNEL,
      ADDIDATA_READ_1_TRANSDUCER_CHANNEL,
      ADDIDATA_CONVERT_DIGITAL_TO_REAL_METRIC_VALUE,
      ADDIDATA_READ_MORE_TRANSDUCER_CHANNELS,
      ADDIDATA_CONVERT_MORE_DIGITAL_TO_REAL_METRIC_VALUE,
      ADDIDATA_GET_TRANSDUCER_HARDWARE_TRIGGER_INFORMATIONS,
      ADDIDATA_ENABLE_DISABLE_TRANSDUCER_HARDWARE_TRIGGER,
      ADDIDATA_GET_TRANSDUCER_HARDWARE_TRIGGER_STATUS,
      ADDIDATA_ENABLE_DISABLE_TRANSDUCER_SOFTWARE_TRIGGER,
      ADDIDATA_TRANSDUCER_SOFTWARE_TRIGGER,
      ADDIDATA_GET_TRANSDUCER_SOFTWARE_TRIGGER_STATUS,
      ADDIDATA_GET_TRANSDUCER_HARDWARE_GATE_INFORMATIONS,
      ADDIDATA_ENABLE_DISABLE_TRANSDUCER_HARDWARE_GATE,
      ADDIDATA_GET_TRANSDUCER_HARDWARE_GATE_STATUS,
      ADDIDATA_TEST_TRANSDUCER_CHANNEL_SECONDARY_CONNECTION,
      ADDIDATA_ENABLE_DISABLE_TRANSDUCER_MODULE_PRIMARY_CONNECTION_TEST,
      ADDIDATA_TEST_TRANSDUCER_MODULE_PRIMARY_CONNECTION,
      ADDIDATA_ENABLE_DISABLE_TRANSDUCER_MODULE_PRIMARY_SHORT_CIRCUIT_INTERRUPT,
      ADDIDATA_INIT_TRANSDUCER_SEQUENCE_ACQUISITION,
      ADDIDATA_START_TRANSDUCER_SEQUENCE_ACQUISITION,
      ADDIDATA_PAUSE_TRANSDUCER_SEQUENCE_ACQUISITION,
      ADDIDATA_STOP_TRANSDUCER_SEQUENCE_ACQUISITION,
      ADDIDATA_RELEASE_TRANSDUCER_SEQUENCE_ACQUISITION,
      ADDIDATA_CONVERT_TRANSDUCER_SEQUENCE_DIGITAL_TO_REAL_METRIC_VALUE,
      ADDIDATA_GET_TRANSDUCER_SEQUENCE_ACQUISITION_HANDLE_STATUS,
      ADDIDATA_REARM_TRANSDUCER_MODULE_PRIMARY_SHORT_CIRCUIT_CONNECTION_TEST,
      ADDIDATA_GET_TRANSDUCER_MODULE_CONVERT_TIME_DIVISION_FACTOR_INFORMATION,
      ADDIDATA_INIT_TRANSDUCER_MODULE_CONVERT_TIME_DIVISION_FACTOR,
      ADDIDATA_RELEASE_TRANSDUCER_MODULE_CONVERT_TIME_DIVISION_FACTOR,
      ADDIDATA_GET_TRANSDUSER_AUTO_REFRESH_CHANNEL_POINTER,
      ADDIDATA_GET_TRANSDUSER_AUTO_REFRESH_MODULE_POINTER,
      ADDIDATA_GET_TRANSDUSER_AUTO_REFRESH_MODULE_COUNTER_POINTER,
      ADDIDATA_START_TRANSDUSER_AUTO_REFRESH,
      ADDIDATA_STOP_TRANSDUSER_AUTO_REFRESH
      };

   /****************************************************************************/
   /* Functionality enumeration                                                */
   /****************************************************************************/


   #define   ADDIDATA_DIGITAL_INPUT                        0
   #define   ADDIDATA_DIGITAL_OUTPUT                       1
   #define   ADDIDATA_ANALOG_INPUT                         2
   #define   ADDIDATA_ANALOG_OUTPUT                        3
   #define   ADDIDATA_TIMER                                4
   #define   ADDIDATA_WATCHDOG                             5
   #define   ADDIDATA_TEMPERATURE                          6
   #define   ADDIDATA_COUNTER                              7
   #define   ADDIDATA_BI_DIRECTIONAL                       8
   //CG 13/09/00 0800/0200 -> 0900/0210 
   #define   ADDIDATA_RESISTANCE			   9 

   #define   ADDIDATA_TIMER_COUNTER_WATCHDOG              10
   #define   ADDIDATA_PRESSURE                            11
   #define   ADDIDATA_TRANSDUCER                          12
   #define   ADDIDATA_NUMBER_OF_FUNCTIONALITY             13
   #define   ADDIDATA_CUSTOMER_INFORMATION              0x3F

   /***************************************************************************/
   /* Analog output type definition                                           */
   /***************************************************************************/

   #define ADDIDATA_NONE    	0
   #define ADDIDATA_UNIPOLAR    1
   #define ADDIDATA_BIPOLAR     2
   #define ADDIDATA_BOTH     	3

// Begin RH 0801-0215 -> 0801-0216
   #define ADDIDATA_RANGE_0    	0
   #define ADDIDATA_RANGE_1    	1
   #define ADDIDATA_RANGE_2    	2
   #define ADDIDATA_RANGE_3    	3
   #define ADDIDATA_RANGE_4    	4
// End RH 0801-0215 -> 0801-0216
   
   /****************************************************************************/
   /* Watchdog type enumaration                                                */
   /****************************************************************************/

   #define ADDIDATA_DIGITAL_OUTPUT_WATCHDOG     1
   #define ADDIDATA_ANALOG_OUTPUT_WATCHDOG      2
   #define ADDIDATA_ANA_DIG_OUTPUT_WATCHDOG     3
   #define ADDIDATA_SYSTEM_WATCHDOG             4

   // Begin 27.11.2001 S.WEBER 1101-0218 -> 1101-0219
   #define ADDIDATA_INVERTED			1
   #define ADDIDATA_NOT_INVERTED		0
   // End 27.11.2001 S.WEBER 1101-0218 -> 1101-0219

   /****************************************************************************/
   /* Compiler type enum                                                       */
   /****************************************************************************/

   #ifdef _WIN32
      enum ADDIDATA_COMPILER_TYPE_ENUM {
	    ADDIDATA_DLL_COMPILER_C,
	    ADDIDATA_DLL_COMPILER_PASCAL,
	    ADDIDATA_DLL_COMPILER_VB,
	    ADDIDATA_DLL_LABVIEW,
	    ADDIDATA_DLL_COMPILER_VB_5,
	    ADDIDATA_DLL_COMPILER_VB_6 = ADDIDATA_DLL_COMPILER_VB_5
	    };
   #else
      enum ADDIDATA_COMPILER_TYPE_ENUM {
	    ADDIDATA_DLL_COMPILER_C,
	    ADDIDATA_DLL_COMPILER_PASCAL,
	    ADDIDATA_DLL_COMPILER_VB,
	    ADDIDATA_DLL_LABVIEW
	    };
   #endif

// Begin :  |09.10.2001| R. HILPERT| 0801-0216 -> 0801-0216                         |

   typedef struct
      {
	   /*******************************/
	   /* Get the timiner time unit */
	   /*******************************/

	BYTE	b_WatchdogTimeUnit; //Available time unit

	   /*************************/
	   /* Reserve for Alignement*/
	   /*************************/

	BYTE    b_Reserved1;

	   /********************************/
	   /* Get the watchdog time step */
	   /********************************/

	WORD	w_WatchdogTimeStep; //Time step

	   /*******************************/
	   /* Get the watchdog resolution */
	   /*******************************/

	BYTE    b_Resolution; //Watchdog resolution 

	   /*************************/
	   /* Reserve for Alignement*/
	   /*************************/

	BYTE    b_Reserved2;

	   /*************************/
	   /* Reserve for Alignement*/
	   /*************************/

	WORD    w_Reserved3;

	   /***********************************/
	   /* Get the hardware gate availality */
	   /***********************************/

	DWORD    dw_HardwareGateAvailable;
					  //FALSE :Hardware gate not available
					  //TRUE : Hardware gate available 

	   /**************************************/
	   /* Get the hardware trigger availality */
	   /**************************************/

	DWORD    dw_HardwareTriggerAvailable;
					  //FALSE :Hardware trigger not available
					  //TRUE : Hardware trigger available

	   /************************************/
	   /* Get the warning relay availality */
	   /************************************/

	DWORD    dw_WarningRelayAvailable;
					  //FALSE : Warning relay not available
					  //TRUE : Warning relay available

	   /**********************************/
	   /* Get the reset relay availality */
	   /**********************************/

	DWORD    dw_ResetRelayAvailable;
					  //FALSE : Reset relay not available
					  //TRUE : Reset relay available

	   /********************************************/
	   /* Get the reset relay mode configurability */
	   /********************************************/

	BYTE    b_ResetRelayModeConfigurable;
					  // 0 : Reset Mode can not be configured
					  // 1 : Reset Mode can be configured

	   /*************************/
	   /* Reserve for Alignement*/
	   /*************************/

	BYTE    b_Reserved4;

	   /*************************/
	   /* Reserve for Alignement*/
	   /*************************/

	WORD    w_Reserved5;

	   /*********************************************/
	   /* Get the warning to reset delay availality */
	   /*********************************************/

	DWORD    dw_WarningDelayAvailable;
					  //FALSE : Warning to reset delay not available
					  //TRUE : Warning to reset delay available

      }str_GetWatchdogInformation,*pstr_GetWatchdogInformation; // SIZE = ADDIDATA_GET_WATCHDOG_INFORMATION_STUCT_SIZE_REV_1_0 = 32 BYTES


// End :  |09.10.2001| R. HILPERT| 0801-0216 -> 0801-0216                         |

   // Begin 17/10/00 CG 0800/0200 -> 0900/0210
   // define the get information structure 
   
   typedef struct
      {
	BYTE	b_InputsResolution;	    // Return the input resolution
					    // 8 : 8 Bit Resolution
					    // 16: 16 Bit Resolution, ...
	BYTE	b_CanUsedInterrupt;	    // 0 : No Interrupt can be generated
					    // 1 : Interrupt can be generated
	BYTE	b_UnipolarBipolarConfigurable;	// 0 : Unipolar/Bipolar hardware configurable
						// 1 : Unipolar/Bipolar configurable
	BYTE	b_UnipolarAvailable;	    // 0 : Can not configure to unipolar
					    // 1 : Can configure to unipolar
	BYTE	b_BipolarAvailable; 	    // 0 : Can not configure to bipolar
					    // 1 : Can configure to bipolar
	BYTE	b_SingleDifferenceSelected;	// 0 : Single mode selected
						// 1 : Difference mode selected
	BYTE	b_DCCouplingAvailable;	// 0 : Can not configure coupling DC
					// 1 : Can configure coupling DC
	BYTE    b_ACCouplingAvailable;	// 0 : Can not configure coupling AC
					// 1 : Can configure coupling AC
	BYTE	b_BufferAvailable;	// 0 : No hardware buffer available
					// 1 : Hardware buffer available
	BYTE	b_CanGerenatedWarning;	// 0 : Alarm not available
					// 1 : Alarm available
	BYTE	b_CurrentSourceSetBySoft;// 0 : The current source must not be activated by the software
			    	         // 1 : The current source must be activated by the software.
	BYTE	b_NbrOfGain;		// Return the number of gain value available

	// Begin 08.08.2002 SW 0302-0223 -> 2224-0602. Module number information implementation (str_GetAnalogMesureInformation)
        // DWORD   dw_Reserved1;
	DWORD   dw_ModuleNumber;
	// End 08.08.2002 SW 0302-0223 -> 2224-0602. Module number information implementation

	DOUBLE	d_GainAvailable[255]; 	// Define the available gain value
	BYTE	b_OffsetRangeAvailable;	// 0 : Offset not allowed
					// 1 : Offset allowed
	BYTE    b_Reserved2;
	WORD	w_OffsetRangeResolution;// Offset resolution
					    //8  : 8-bit resolution
					    //16 : 16-bit resolution, ...
	BYTE	b_OffsetRangeDenominator;	// Offset denominator step value
	BYTE	b_OffsetRangeNumerator;	        // Offset numerator step value
	BYTE	b_OpenInputDetection;	// 0 : Open input detection not available
				        // 1 : Open input detection available
	BYTE	b_ShortCircuitDetection;// 0 : Short-circuit detection not available
	                                // 1 : Short-circuit detection available
	DOUBLE  d_UMax;		// Return the maximal input voltage value in V or A
	DOUBLE  d_URef;		// Return the reference input voltage value in V or A
        BYTE    b_InputType;		// Selected user input type
					    // ADDIDATA_RTD
					    // ADDIDATA_THERMOCOUPLE
					    // ADDIDATA_TEMPERATURE_ON_BOARD
					    // ADDIDATA_OHM
					    // ADDIDATA_ANALOG_INPUT_V_OR_I
	BYTE	b_TypePrecision;	// Precision of the input
					    // ADDIDATA_THERMOCOUPLE_TYPE_B
					    // ADDIDATA_THERMOCOUPLE_TYPE_E
					    // ADDIDATA_THERMOCOUPLE_TYPE_J
					    // ADDIDATA_THERMOCOUPLE_TYPE_K
					    // ADDIDATA_THERMOCOUPLE_TYPE_N
					    // ADDIDATA_THERMOCOUPLE_TYPE_R
					    // ADDIDATA_THERMOCOUPLE_TYPE_S
					    // ADDIDATA_THERMOCOUPLE_TYPE_T
					    // or
					    // ADDIDATA_RTD_TYPE_PT
					    // ADDIDATA_RTD_TYPE_Ni

	WORD	w_InputTypeValue;  // if ADDIDATA_RTD
				   // AND ADDIDATA_RTD_TYPE_PT
				   // 100 -> PT100

        /***********************/        
        /* Module Informations */
        /***********************/        
	BYTE	b_AutoCalibration;		// 0 : Auto calibration not available
						// 1 : Auto calibration available
      	BYTE	b_CJCAvailable;			// 0 : Without CJC
						// 1 : Wtih CJC
	BYTE	b_ConversionMustSetting;	// 0 : The conversion time for a single
						//     acquisition is fixed via Hardware (jumper)
						// 1 : The conversion time for a single
						//     acquisition is fixed via Software
	BYTE	b_ConversionCalcType;		// 0 : Binary type
						//     (XX000,XX001,XX010,XX011,XX100)
						// 1 : Multiple type (60,120,240,480,960, ...)
	BYTE	b_ConversionUnitType;		// 0 : Time unity      (ns,æs,ms,s, ...)
						// 1 : Frequency unity (MHz,KHz,Hz,mHz, ...)
	BYTE	b_AvailableConversionUnit;	//For time unity :
						//D0: 	0 : ns not available
						//	1 : ns available
						//D1:	0 : æs not available
						//	1 : æs available
						//D2:	0 : ms not available
						//	1 : ms available
						//D3:	0 : s not available
						//	1 : s available
						//For frequency unity:
						//D0 : 	0 : MHz not available
						//	1 : MHz available
						//D1:	0 : KHz not available
						//	1 : KHz available
						//D2:	0 : Hz not available
						//	1 : Hz available
						//D3:	0 : mHz not available
						//	1 : mHz available
	WORD	w_ConversionResolution;		//  8 : 8-bit resolution
						//  16: 16-bit resolution, ...
	WORD	w_MinConversionTime;		//Minimum conversion time.
						//7000  : 7000(ns)
						//10000 : 10000(ns), ...
	WORD	w_ConversionStep;		//Conversion time steps
						//20 : 20 steps
						//50 : 50 steps, ...
	BYTE	b_SEQArrayAvailable;		// 0 : Sequence array not available
						// 1 : Sequence array available
	BYTE	b_SEQConfigurable;		// 0 : Sequence fixed
						// 1 : Sequence configurable
	BYTE	b_SEQHardwareTriggerAvailable;	// 0 : Hardware trigger not available
						// 1 : Hardware trigger available
	BYTE	b_SEQHardwareTriggerHighAvailable; // 0 : Hardware high trigger level not available
						   // 1 : Hardware high trigger level available
	BYTE	b_SEQHardwareTriggerLowAvailable;  // 0 : Hardware low trigger level not available
						   // 1 : Hardware low trigger level available
	BYTE	b_SEQHardwareTriggerAvailableMode; // 001 : External trigger start a 1 DMA cycle
						   // 010 : Each trigger start a sequence
						   // 100 : Each trigger start a DMA cycle
	BYTE	b_SEQHardwareGateAvailable;	// 0 : Hardware gate not available
						// 1 : Hardware gate available
	BYTE	b_SEQHardwareGateHighAvailable; // 0 : Hardware high gate level not available
						// 1 : Hardware high gate level available
	BYTE	b_SEQHardwareGateLowAvailable;  // 0 : Hardware low gate level not available
						// 1 : Hardware low gate level available
	BYTE	b_SEQClrIndexAvailable;	        // 0 : It is not possible to restart the
						// acquisition which the next selected channel from sequence
						// 1 : It's possible to restart the acquisition
						// which  the next selected channel from sequence
	WORD	w_SEQAcquisitionMode;		// 00 : The acquisition can work in Single mode
						// 01 : The acquisition can work in continuous mode
						// 11 : The acquisition can work in single and continuous mode
	BYTE	b_DMAAvailable;    		// 0 : Board can not used the DMA
						// 1 : Board can used the DMA
	BYTE	b_DualDMAChannel;		// 0 : Only 1 DMA channel used
						// 1 : Board can used 2 DMA channels
	BYTE	b_SEQCounterAvailable;		// 0 : DMA/conversion counter not available
						// 1 : DMA/conversion counter available
	BYTE	b_SEQCounterMode;		//01 : Counter can counter the number of sequence
						//10 : Counter can counter the number of DMA cycle
						//11 : Counter can counter the number of DMA cycle
						//     or the number of sequence
	BYTE	b_SEQCommonGain;		// Define if the gain can be different for each input
						// 0 : Gain is common on each input
						// 1 : Gain can be different for each input.
	BYTE	b_SEQCommonPolarity;		// Define if the polarity can be different for each input
						// 0 : Polarity is common on each input
						// 1 : Polarity can be different for each input.
	BYTE    b_SEQCommonOffsetRange;		// Define if the offset can be different for each input
						// 0 : Offset is common on each input
						// 1 : Offset can be different for each input.
	BYTE	b_SEQCommonCoupling;
	WORD	w_SEQCounterResolution;		// Counter resolution
						//8  : 8-bit resolution
						//16 : 16-bit resolution, ...
	BYTE	b_SEQDelayTimeConfigurable;	// 0 : Delay after each sequence not available
						// 1 : Delay after each sequence available
	BYTE    b_SEQDelayMode;
	BYTE	b_SEQDelayCalcType; 		// 0 : Binary type
						//         (XX000,XX001,XX010,XX011,XX100)
						// 1 : Multiple type (60,120,240,480,960, ...)
	BYTE	b_SEQDelayTimeUnitType;		// 0 : Time unity	(ns,æs,ms,s, ...)
						// 1 : Frequency unity (MHz,KHz,Hz,mHz, ...)
	BYTE	b_SEQDelayValueType;		// 0 : Value to write in the register is the value in s or in Hz
						// 1 : Value to write in the register is the step multiplier
	BYTE	b_SEQDelayTimeUnit;		//For time unity:
						//D0: 	0 : ns not available
						//	1 : ns available
						//D1:	0 : us not available
						//	1 : us available
						//D2:	0 : ms not available
						//	1 : ms available
						//D3:	0 : s not available
						//	1 : s available
						//For frequency unity:
						//D0 : 	0 : MHz not available
						//	1 : MHz available
						//D1:	0 : KHz not available
						//	1 : KHz available
						//D2:	0 : Hz not available
						//	1 : Hz available
						//D3:	0 : mHz not available
						//	1 : mHz available
	WORD	w_SEQDelayTimeResolution;	// Delay time resolution
						//8  : 8-bit resolution
						//16 : 16-bit resolution, ...
	WORD	w_SEQMinDelayTime;		//Min delay time.
						//7000  : 7000(ns)
						//10000 : 10000(ns), ...
	WORD	w_SEQDelayTimeStep;		//Conversion delay time steps
						//20 : 20 steps
						//50 : 50 steps, ...
	BYTE	b_SEQUnipolarBipolarConfigurable;// 0 : Unipolar/Bipolar hardware configurable
						 // 1 : Unipolar/Bipolar configurable
	BYTE	b_SEQUnipolarAvailable;		// 0 : Can not configurat to unipolar
						// 1 : Can configurat to unipolar
	BYTE	b_SEQBipolarAvailable; 		// 0 : Can not configurat to bipolar
						// 1 : Can configurat to bipolar
	BYTE    b_SEQDCCouplingAvailable;	// 0 : Can not configurate to DC Coupling
						// 1 : Can configurate DC Coupling
	BYTE	b_SEQACCouplingAvailable;	// 0 : Can not configurate to AC coupling
						// 1 : Can configurate AC coupling
	BYTE	b_SEQBufferAvailable;		// 0 : No hardware buffer available
						// 1 : Hardware buffer available
	BYTE	b_SEQNbrOfGain;			// Return the number of gain value available
	BYTE    b_Reserved3;
        WORD    w_Reserved4; 
	DWORD   dw_Reserved5;
	DOUBLE	d_SEQGainAvailable[255]; // Define the available gain value
	BYTE	b_SEQOffsetRangeAvailable;	// 0 : Offset not allowed
						// 1 : Offset allowed
        BYTE    b_Reserved6;
	WORD	w_SEQOffsetRangeResolution;	// Offset resolution
						//8  : 8-bit resolution
						//16 : 16-bit resolution, ...
	BYTE	b_SEQOffsetRangeDenominator;	// Offset denominator step value
	BYTE	b_SEQOffsetRangeNumerator;	// Offset numerator step value

	BYTE	b_SCANAvailable;		// 0 : SCAN not available
						// 1 : SCAN available
	BYTE	b_SCANConfigurable;		// 0 : SCAN fixed
						// 1 : SCAN configurable (The first and the last
						// channel can be given)
	BYTE	b_SCANHardwareTriggerAvailable; // 0 : Hardware trigger not available
						// 1 : Hardware trigger available
	BYTE	b_SCANHardwareTriggerHighAvailable; // 0 : Hardware high trigger level not available
						    // 1 : Hardware high trigger level available
	BYTE	b_SCANHardwareTriggerLowAvailable;  // 0 : Hardware low trigger level not available
						    // 1 : Hardware low trigger level available
	BYTE	b_SCANHardwareTriggerAvailableMode;
						// 0001 : External trigger start each acquisition from a SCAN
						// 0010 : Each trigger start each SCAN
						// 0100 : 
						// 1000 : First Trigger start the SCAN Cycle
	BYTE	b_SCANHardwareGateAvailable;	// 0 : Hardware gate not available
						// 1 : Hardware gate available
	BYTE	b_SCANHardwareGateHighAvailable;// 0 : Hardware high gate level not available
						// 1 : Hardware high gate level available
	BYTE	b_SCANHardwareGateLowAvailable; // 0 : Hardware low gate level not available
						// 1 : Hardware low gate level available
	BYTE	b_SCANClrIndexAvailable;	// 0 : It is not possible to restart the
						//         acquisition which the next selected channel from SCAN
						// 1 : It's possible to restart the acquisition
						//	   which  the next selected channel from SCAN
	WORD	w_SCANAcquisitionMode;		// 00 : The acquisition can work in Single mode
						// 01 : The acquisition can work in continuous mode
						// 11 : The acquisition can work in single and continuous mode
	BYTE	b_SCANCounterAvailable;		// 0 : SCAN/conversion counter not available
						// 1 : SCAN/conversion counter available
	BYTE	b_SCANCounterMode;		// 01 : Counter can counter the number of SCAN
	BYTE	b_SCANCommonGain;		// Define if the gain can be different for each input
						// 0 : Gain is common on each input
						// 1 : Gain can be different for each input.
	BYTE	b_SCANCommonPolarity;		// Define if the polarity can be different for each input
						// 0 : Polarity is common on each input
						// 1 : Polarity can be different for each input.
	BYTE	b_SCANCommonOffsetRange;	// Define if the offset can be different for each input
						// 0 : Offset is common on each input
						// 1 : Offset can be different for each input.
	BYTE	b_SCANCommonCoupling;
	WORD	w_SCANCounterResolution;	// Counter resolution
						//8  : 8-bit resolution
						//16 : 16-bit resolution, ...
	BYTE	b_SCANDelayTimeConfigurable;    // 0 : Delay after each sequence not available
						// 1 : Delay after each sequence available
	BYTE	b_SCANDelayMode;
	BYTE	b_SCANDelayCalcType; 		// 0 : Binary type
						//         (XX000,XX001,XX010,XX011,XX100)
						// 1 : Multiple type (60,120,240,480,960, ...)
	BYTE	b_SCANDelayTimeUnitType;	// 0 : Time unity	(ns,æs,ms,s, ...)
						// 1 : Frequency unity (MHz,KHz,Hz,mHz, ...)
	BYTE	b_SCANDelayValueType;		// 0 : Value to write in the register is the value in s or in Hz
						// 1 : Value to write in the register is the step multiplier
	BYTE	b_SCANDelayTimeUnit;		//For time unity:
						//D0: 	0 : ns not available
						//	1 : ns available
						//D1:	0 : us not available
						//	1 : us available
						//D2:	0 : ms not available
						//	1 : ms available
						//D3:	0 : s not available
						//	1 : s available
						//For frequency unity:
						//D0 : 	0 : MHz not available
						//	1 : MHz available
						//D1:	0 : KHz not available
						//	1 : KHz available
						//D2:	0 : Hz not available
						//	1 : Hz available
						//D3:	0 : mHz not available
						//	1 : mHz available
	WORD	w_SCANDelayTimeResolution;	// Delay time resolution
						//8  : 8-bit resolution
						//16 : 16-bit resolution, ...
	WORD	w_SCANMinDelayTime;		//Min delay time.
						//7000  : 7000(ns)
						//10000 : 10000(ns), ...
	WORD	w_SCANDelayTimeStep;		//Conversion delay time steps
						//20 : 20 steps
						//50 : 50 steps, ...
	BYTE	b_SCANUnipolarBipolarConfigurable;// 0 : Unipolar/Bipolar hardware configurable
						  // 1 : Unipolar/Bipolar configurable
	BYTE	b_SCANUnipolarAvailable;	// 0 : Can not configure to unipolar
						// 1 : Can configure to unipolar
	BYTE	b_SCANBipolarAvailable; 	// 0 : Can not configure to bipolar
						// 1 : Can configure to bipolar
	BYTE    b_SCANDCCouplingAvailable;	// 0 : Can not configurate to DC Coupling
						// 1 : Can configurate DC Coupling
	BYTE	b_SCANACCouplingAvailable;	// 0 : Can not configurate to AC coupling
						// 1 : Can configurate AC coupling
	BYTE	b_SCANBufferAvailable;		// 0 : No hardware buffer available
						// 1 : Hardware buffer available
	BYTE	b_SCANNbrOfGain;		// Return the number of gain value available
	BYTE    b_Reserved7;
        WORD    w_Reserved8;
	DOUBLE	d_SCANGainAvailable[255]; 	// Define the available gain value
	BYTE	b_SCANOffsetRangeAvailable;	// 0 : Offset not allowed
						// 1 : Offset allowed
        BYTE    b_Reserved9;
	WORD	w_SCANOffsetRangeResolution;	// Offset resolution
						//8  : 8-bit resolution
						//16 : 16-bit resolution, ...
	BYTE	b_SCANOffsetRangeDenominator;	// Offset denominator step value
	BYTE	b_SCANOffsetRangeNumerator;	// Offset numerator step value
	WORD    w_Reserved10;

      }str_GetAnalogMesureInformation,*pstr_GetAnalogMesureInformation;

   typedef struct
      {
      DOUBLE d_Gain;
      BYTE b_Polarity;
                  // ADDIDATA_UNIPOLAR    
                  // ADDIDATA_BIPOLAR     
      BYTE b_Reserved1;
      WORD w_OffsetRange;
      BYTE b_Coupling;
                  // ADDIDATA_DC_COUPLING 
                  // ADDIDATA_AC_COUPLING 
      BYTE b_Reserved2;
      WORD w_Reserved3;
      } str_InitAnalogInput,*pstr_InitAnalogInput;

   typedef struct
      {
      DOUBLE d_Gain;
      DOUBLE d_OffsetVoltage;
      DOUBLE d_SensorSensibility;
      } str_InitPressureChannel,*pstr_InitPressureChannel;

   typedef struct
      {
      DOUBLE d_Gain;
      BYTE b_Polarity;
                  // ADDIDATA_UNIPOLAR    
                  // ADDIDATA_BIPOLAR     
      BYTE b_Reserved1;
      WORD w_OffsetRange;
      BYTE b_Coupling;
                  // ADDIDATA_DC_COUPLING 
                  // ADDIDATA_AC_COUPLING 
      BYTE b_Reserved2;
      WORD w_Reserved3;
      } str_InitResistanceChannel,*pstr_InitResistanceChannel;

   typedef struct
      {
      WORD w_FirstChannel;
      WORD w_LastChannel;
      DWORD dw_ConversionTime;
      BYTE  b_ConversionTimeUnit;
      BYTE  b_SCANTimeMode;
                      // ADDIDATA_DELAY_NOT_USED	
                      // ADDIDATA_DELAY_MODE1_USED	
                      // ADDIDATA_DELAY_MODE2_USED    
      WORD  w_Reserved1;
      DWORD dw_SCANTime;
      BYTE  b_SCANTimeUnit;
      BYTE  b_SCANMode;
                      // ADDIDATA_SINGLE_SCAN
                      // ADDIDATA_DEFINED_SCAN_NUMBER 
                      // ADDIDATA_CONTINUOUS_SCAN     
      BYTE  b_ExternTriggerMode;
                      // ADDIDATA_FIRST_LOW_EDGE_START_ALL_SCAN   
                      // ADDIDATA_FIRST_HIGH_EDGE_START_ALL_SCAN  
                      // ADDIDATA_FIRST_EDGE_START_ALL_SCAN	    
                      // ADDIDATA_EACH_LOW_EDGE_START_A_SCAN	    
                      // ADDIDATA_EACH_HIGH_EDGE_START_A_SCAN	    
                      // ADDIDATA_EACH_EDGE_START_A_SCAN	    
                      // ADDIDATA_EACH_LOW_EDGE_START_A_SINGLE_ACQUISITION	
                      // ADDIDATA_EACH_HIGH_EDGE_START_A_SINGLE_ACQUISITION	
                      // ADDIDATA_EACH_EDGE_START_A_SINGLE_ACQUISITION	
      BYTE  b_ExternGateMode;
                      // ADDIDATA_DISABLE
		      // ADDIDATA_LOW           
                      // ADDIDATA_HIGH           
      DWORD dw_SCANCounter;
      } str_InitAnalogInputSCAN,*pstr_InitAnalogInputSCAN;

   typedef struct
      {
      WORD w_FirstChannel;
      WORD w_LastChannel;
      DWORD dw_ConversionTime;
      BYTE  b_ConversionTimeUnit;
      BYTE  b_SCANTimeMode;
                      // ADDIDATA_DELAY_NOT_USED	
                      // ADDIDATA_DELAY_MODE1_USED	
                      // ADDIDATA_DELAY_MODE2_USED    
      WORD  w_Reserved1;
      DWORD dw_SCANTime;
      BYTE  b_SCANTimeUnit;
      BYTE  b_SCANMode;
                      // ADDIDATA_SINGLE_SCAN
                      // ADDIDATA_DEFINED_SCAN_NUMBER 
                      // ADDIDATA_CONTINUOUS_SCAN     
      BYTE  b_ExternTriggerMode;
                      // ADDIDATA_FIRST_LOW_EDGE_START_ALL_SCAN   
                      // ADDIDATA_FIRST_HIGH_EDGE_START_ALL_SCAN  
                      // ADDIDATA_FIRST_EDGE_START_ALL_SCAN	    
                      // ADDIDATA_EACH_LOW_EDGE_START_A_SCAN	    
                      // ADDIDATA_EACH_HIGH_EDGE_START_A_SCAN	    
                      // ADDIDATA_EACH_EDGE_START_A_SCAN	    
                      // ADDIDATA_EACH_LOW_EDGE_START_A_SINGLE_ACQUISITION	
                      // ADDIDATA_EACH_HIGH_EDGE_START_A_SINGLE_ACQUISITION	
                      // ADDIDATA_EACH_EDGE_START_A_SINGLE_ACQUISITION	
      BYTE  b_ExternGateMode;
                      // ADDIDATA_DISABLE
		      // ADDIDATA_LOW           
                      // ADDIDATA_HIGH           
      DWORD dw_SCANCounter;
      } str_InitTemperatureChannelSCAN,*pstr_InitTemperatureChannelSCAN;

   typedef struct
      {
      WORD w_FirstChannel;
      WORD w_LastChannel;
      DWORD dw_ConversionTime;
      BYTE  b_ConversionTimeUnit;
      BYTE  b_SCANTimeMode;
		      // ADDIDATA_DELAY_NOT_USED
		      // ADDIDATA_DELAY_MODE1_USED
		      // ADDIDATA_DELAY_MODE2_USED
      WORD  w_Reserved1;
      DWORD dw_SCANTime;
      BYTE  b_SCANTimeUnit;
      BYTE  b_SCANMode;
		      // ADDIDATA_SINGLE_SCAN
		      // ADDIDATA_DEFINED_SCAN_NUMBER
		      // ADDIDATA_CONTINUOUS_SCAN
      BYTE  b_ExternTriggerMode;
		      // ADDIDATA_FIRST_LOW_EDGE_START_ALL_SCAN
		      // ADDIDATA_FIRST_HIGH_EDGE_START_ALL_SCAN
		      // ADDIDATA_FIRST_EDGE_START_ALL_SCAN
		      // ADDIDATA_EACH_LOW_EDGE_START_A_SCAN
		      // ADDIDATA_EACH_HIGH_EDGE_START_A_SCAN
		      // ADDIDATA_EACH_EDGE_START_A_SCAN
		      // ADDIDATA_EACH_LOW_EDGE_START_A_SINGLE_ACQUISITION
		      // ADDIDATA_EACH_HIGH_EDGE_START_A_SINGLE_ACQUISITION
		      // ADDIDATA_EACH_EDGE_START_A_SINGLE_ACQUISITION
      BYTE  b_ExternGateMode;
		      // ADDIDATA_DISABLE
		      // ADDIDATA_LOW
		      // ADDIDATA_HIGH
      DWORD dw_SCANCounter;
      } str_InitPressureSCAN,*pstr_InitPressureSCAN;

   typedef struct
      {
      WORD w_FirstChannel;
      WORD w_LastChannel;
      DWORD dw_ConversionTime;
      BYTE  b_ConversionTimeUnit;
      BYTE  b_SCANTimeMode;
		      // ADDIDATA_DELAY_NOT_USED
		      // ADDIDATA_DELAY_MODE1_USED
		      // ADDIDATA_DELAY_MODE2_USED
      WORD  w_Reserved1;
      DWORD dw_SCANTime;
      BYTE  b_SCANTimeUnit;
      BYTE  b_SCANMode;
		      // ADDIDATA_SINGLE_SCAN
		      // ADDIDATA_DEFINED_SCAN_NUMBER
		      // ADDIDATA_CONTINUOUS_SCAN
      BYTE  b_ExternTriggerMode;
                      // ADDIDATA_FIRST_LOW_EDGE_START_ALL_SCAN   
                      // ADDIDATA_FIRST_HIGH_EDGE_START_ALL_SCAN  
                      // ADDIDATA_FIRST_EDGE_START_ALL_SCAN	    
                      // ADDIDATA_EACH_LOW_EDGE_START_A_SCAN	    
                      // ADDIDATA_EACH_HIGH_EDGE_START_A_SCAN	    
                      // ADDIDATA_EACH_EDGE_START_A_SCAN	    
                      // ADDIDATA_EACH_LOW_EDGE_START_A_SINGLE_ACQUISITION	
                      // ADDIDATA_EACH_HIGH_EDGE_START_A_SINGLE_ACQUISITION	
                      // ADDIDATA_EACH_EDGE_START_A_SINGLE_ACQUISITION	
      BYTE  b_ExternGateMode;
                      // ADDIDATA_DISABLE
		      // ADDIDATA_LOW           
                      // ADDIDATA_HIGH           
      DWORD dw_SCANCounter;     
      } str_InitResistanceChannelSCAN,*pstr_InitResistanceChannelSCAN;

   // End 17/10/00 CG 0800/0200 -> 0900/0210

   // Begin 27.11.2001 S.WEBER 1101-0218 -> 1101-0219
   typedef struct
      {
      BYTE   b_DigitalInputType;		// Type of the selected input 
						//	0x00		Input type not defined
						//	1 - 15		5V type
						//	16 - 31	12 type
						//	32 - 47	24 type
						//	48 - 63	Level configurable type 
						//	64 - 255	Any other type
      BYTE   b_Reserved1 [7];			// Reserved
      DWORD dw_DigitalInputInterrupt;		// Available input interrupt
      DWORD dw_DigitalModuleNumber;		// Number from digital input module
      DWORD dw_MaxInputVoltageValue;		// Return the max input voltage value

//Begin JK 04.11.02 : 2224-0602 -> 2225-1002 APCI 1500 Interrupt
      BYTE   b_InterruptReturnInputNumber;      // 0 : Input number that generate the event can be return by the interrupt function
                                                // 1 : Input number that generate the event can't be return by the interrupt function
//End JK 04.11.02 : 2224-0602 -> 2225-1002 APCI 1500 Interrupt

//Begin JK 04.11.02 : 2224-0602 -> 2225-1002 APCI 1500 Interrupt
//      BYTE   b_Reserved2 [4];			// Reserved
      BYTE   b_Reserved2 [3];			// Reserved
//End JK 04.11.02 : 2224-0602 -> 2225-1002 APCI 1500 Interrupt
      BYTE   b_InputStatusAvailable;		// 0 : Input status information not available
						// 1 : Input status information available
      BYTE   b_InputStatusResolution;		// Return the resolution of the input status
      BYTE   b_InputAnalogValueAvailable;	// 0 : Input value not available
						// 1 : Input value available
      BYTE   b_InputAnalogValueResolution;	// Return the resolution of the input value
      BYTE   b_InputLevelSelection;		// 0 : Input level fixed via hardware
						// 1 : Module configuration level available
						// 2 : Channel configuration level available
      BYTE   b_InputLevelNbr;			// Return the number of input levels.
      BYTE   b_InputLevelResolution;		// Input Levels resolution
      BYTE   b_FilterSetting;			// 0 : Software configuration filter not available
						// 1 : Module software configuration filter available
						// 2 : Channel software configuration filter available
      BYTE   b_LogicSelection;			// 0 : Input level can not by inverted
						// 1 : Input level can by inverted.Selection make via the module configuration
						// 2 : Input level can by inverted.Selection make via the channel configuration
      BYTE   b_Reserved3 [7];			// Reserved
      DWORD dw_MaxCompareVoltageValue;		// Max compare voltage value
      BYTE   b_Reserved4 [4];			// Reserved
      }str_GetDigitalInputInformation, *pstr_GetDigitalInputInformation;

   typedef struct
      {
      BYTE 	b_FilterTimeUnit;		// Time units available.
						// D0: 	0 : ns not available
						//	1 : ns available
						// D1:	0 : us not available
						//	1 : us available
						// D2:	0 : ms not available
						//	1 : ms available
						// D3:	0 : s not available
						//	1 : s available
      BYTE      b_Reserved1 [7];		// Reserved
      WORD 	w_FilterTimeStep;		// Possible time steps
      BYTE      b_Reserved2 [6];		// Reserved
      BYTE	b_Resolution;			// Selection of the resolution 
      BYTE      b_Reserved3 [7];		// Reserved
   }str_DigitalInputModuleFilterInf, *pstr_DigitalInputModuleFilterInf;
   // End 27.11.2001 S.WEBER 1101-0218 -> 1101-0219

/****************************************************************************/
/* Begin SW 15/10/02 Transducer implementation                              */
/* 2224-0602 -> 2225-0802                                                   */
/****************************************************************************/

#define ADDIDATA_NOMINAL_TRANSDUCER_FREQUENCY							(0.0)

#define	ADDIDATA_GET_TRANSDUCER_MODULE_GENERAL_INFORMATION_STRUCT_SIZE_REV_1_0			((160 * 50) + 32)
#define	ADDIDATA_GET_TRANSDUCER_MODULE_SINGLE_ACQUISITION_INFORMATION_STRUCT_SIZE_REV_1_0	(8)
#define	ADDIDATA_GET_TRANSDUCER_MODULE_AUTO_REFRESH_ACQUISITION_INFORMATION_STRUCT_SIZE_REV_1_0	(8)
#define	ADDIDATA_GET_TRANSDUCER_MODULE_SEQUENCE_ACQUISITION_INFORMATION_STRUCT_SIZE_REV_1_0	(32)
#define ADDIDATA_INIT_SEQUENCE_ACQUISITION_STRUCT_SIZE_REV_1_0					(24)
#define ADDIDATA_GET_TRANSDUCER_MODULE_CONVERT_TIME_DIVISION_FACTOR_STRUCT_SIZE_REV_1_0		(16)

typedef struct
	{
	CHAR	c_TransducerType [104];			// Transducer type (name)
	DOUBLE	d_Range;				// Transducer range (mm)
	DOUBLE	d_Sensibility;				// Transducer sensibility (mv/V/mm)
	DOUBLE	d_NominalFrequency;			// Nominal frequency (Hz)
	DOUBLE	d_MinFrequency;				// Minimal frequency (Hz)
	DOUBLE	d_MaxFrequency;				// Maximal frequency (Hz)
	DOUBLE	d_PrimaryNominalVoltage;		// Primary nominal voltage (Veff)
	WORD	w_SelectionIndex;			// Transducer index selection for the initialisation function;
	WORD    w_Reserved [3];
	}str_TransducerInformation,*pstr_TransducerInformation;

typedef struct
	{
	BYTE	b_InputsResolution;			// Returns the input resolution
							// 8: 8-bit resolution
							// 16: 16-bit resolution, ... 
	BYTE	b_SingleAcquisition;			// 0 : Single acquisition not available
							// 1 : Single acquisition available
	BYTE	b_AutoRefreshAcquisition;		// 0 : Auto refresh acquisition not available
							// 1 : Auto refresh acquisition available
	BYTE	b_ScanAcquisition;			// 0 : Scan acquisition not available
							// 1 : Scan acquisition available
	BYTE	b_SequenceAcquisition;			// 0 : Sequence acquisition not available
							// 1 : Sequence acquisition available
	BYTE	b_PrimaryOpenInputDetection;		// 0: Primary circuit open input detection not available
							// 1: Primary circuit open input detection available
	BYTE	b_PrimaryShortCircuitDetection;		// 0: Primary circuit short-circuit detection not available
							// 1: Primary circuit short-circuit detection available
	BYTE	b_SecondaryOpenInputDetection;		// 0: Secondary circuit open input detection not available
							// 1: Secondary circuit open input detection available
	BYTE	b_SecondaryShortCircuitDetection;	// 0: Secondary circuit short-circuit detection not available
							// 1: Secondary circuit short-circuit detection available
	BYTE	b_PrimaryOpenInputDetectionIRQ;		// 0: Primary circuit open input detection interrupt not available
							// 1: Primary circuit open input detection interrupt available
	BYTE	b_PrimaryShortCircuitDetectionIRQ;	// 0: Primary circuit short-circuit detection interrupt not available
							// 1: Primary circuit short-circuit detection interrupt available
	BYTE	b_SecondaryOpenInputDetectionIRQ;	// 0: Secondary circuit open input detection interrupt not available
							// 1: Secondary circuit open input detection interrupt available
	BYTE	b_SecondaryShortCircuitDetectionIRQ;	// 0: Secondary circuit short-circuit detection interrupt not available
							// 1: Secondary circuit short-circuit detection interrupt available
	BYTE	b_Reserved1 [3];
	WORD    w_FirstChannelNumber;			// Return the number from first channel number
	WORD    w_LastChannelNumber;			// Return the number from last channel number
	BYTE	b_Reserved2 [4];

	BYTE	b_NumberOfAvailableTransducersType;	// Return the number of available transducers type.

	BYTE	b_Reserved3 [7];

	str_TransducerInformation s_TransducerInformation [50];
        }str_TransducerModuleInformation,*pstr_TransducerModuleInformation;

typedef struct
	{
	BYTE	b_SoftwareTrigger;			// 0 : Software trigger not available
							// 1 : Software trigger available
	BYTE	b_HardwareTrigger;			// 0 : Hardware trigger not available
							// 1 : Hardware trigger available
	BYTE	b_HardwareGate;				// 0 : Hardware gate not available
							// 1 : Hardware gate available
	BYTE	b_Interrupt;				// 0 : Interrupt can not by generated
							// 1 : Interrupt can by generated (EOC)
	BYTE	b_Reserved [4];
	}str_TransducerSingleAcquisitionInformation,*pstr_TransducerSingleAcquisitionInformation;

typedef struct
	{
	BYTE	b_SoftwareTrigger;			// 0 : Software trigger not available
							// 1 : Software trigger available
	BYTE	b_HardwareTrigger;			// 0 : Hardware trigger not available
							// 1 : Hardware trigger available
	BYTE	b_HardwareGate;				// 0 : Hardware gate not available
							// 1 : Hardware gate available
	BYTE	b_Interrupt;				// 0 : Interrupt can not by generated
							// 1 : Interrupt can by generated (EOC)
	BYTE    b_AccessMode;				// 8  : 8-bit access mode
							// 16 : 16-bit access mode
							// 32 : 32-bit access mode
	BYTE	b_Reserved [3];
	}str_TransducerAutoRefreshInformation,*pstr_TransducerAutoRefreshInformation;


typedef struct
	{
	BYTE    b_SequenceConfigurable;			// 0 : Sequence fixed. User muss pass the first and last channel
							// 1 : Sequence configurable
	BYTE	b_SoftwareTrigger;			// 0 : Software trigger not available
							// 1 : Software trigger available
	BYTE	b_HardwareTrigger;			// 0 : Hardware trigger not available
							// 1 : Hardware trigger available
	BYTE	b_HardwareGate;				// 0 : Hardware gate not available
							// 1 : Hardware gate available
	BYTE	b_DelayTimeConfigurable;		// 0 : Delay after each sequence not available
							// 1 : Delay after each sequence available
	BYTE    b_DelayAvailableMode;			// D0: 	0: Mode 1 not available
							//	1: Mode 1 available
							// D1: 	0: Mode 2 not available
							//	1: Mode 2 available
	BYTE	b_DelayCalcType; 			// 0: Binary type (XX000,XX001,XX010,XX011) 
							// 1: Multiple type (60,120,240,480,960, ...) 
	BYTE	b_DelayTimeUnitType;			// 0: Time unit (ns,µs,ms,s, ...) 
							// 1: Frequency unit (MHz,kHz,Hz,mHz, ...) 
	BYTE	b_DelayTimeUnit;			// For time unit: 
							// D0: 	0: ns not available
							//	1: ns available
							// D1:	0: µs not available
							//	1: µs available
							// D2:	0: ms not available
							//	1: ms available
							// D3:	0: s not available
							//	1: s available
							// For frequency unit: 
							// D0: 	0: MHz not available
							//	1: MHz available
							// D1:	0: kHz not available
							//	1: kHz available
							// D2:	0: Hz not available
							//	1: Hz available
							// D3:	0: mHz not available
							//	1: mHz available
	BYTE	b_Reserved1 [7];
	WORD	w_DelayTimeResolution;			// Delay time resolution
							// 8 : 8-bit resolution
							// 16: 16-bit resolution, ... 
	WORD	w_MinDelayTime;				// Minimum delay time. 
							// 7000 : 7000(ns) 
							// 10000: 10000(ns), ... 
	WORD	w_DelayTimeStep;			// Conversion delay time steps
							// 20: 20 steps
							// 50: 50 steps, ... 
	BYTE	b_Reserved2 [2];

	DWORD   dw_MaxNumberOfAcquisition;		// Return the max number of acauisition for the single acquisition sequence mode
	BYTE	b_Reserved3 [4];
	}str_TransducerSequenceInformation,*pstr_TransducerSequenceInformation;


typedef struct
	{
	BYTE   b_ConvertingTimeUnit;
	BYTE   b_DelayTimeMode;
	BYTE   b_DelayTimeUnit;
	BYTE   b_Reserved [5];
	DWORD dw_DelayTime;
	DWORD dw_ConvertingTime;
	DWORD dw_SequenceCounter;
	DWORD dw_InterruptSequenceCounter;
	}str_InitAnalogMeasureSequenceAcquisition,*pstr_InitAnalogMeasureSequenceAcquisition;


typedef struct
	{
	BYTE	b_Configurable;			        // 0 : Convert time division factor fix
							// 1 : Convert time division factor configurable
	BYTE    b_Steps;				// Steps
	BYTE    b_Initialised;				// 0 : Not initialised
							// 1 : Initialised

	BYTE    b_Reserved;
	DWORD  dw_InitialisationValue;
	DWORD  dw_MinDivisionFactor;			// Min division factor
	DWORD  dw_MaxDivisionFactor;			// Max division factor
	}str_TransducerConvertTimeDivisionFactorInformation,*pstr_TransducerConvertTimeDivisionFactorInformation;


/****************************************************************************/
/* End SW 15/10/02 Transducer implementation                                */
/* 2224-0602 -> 2225-0802                                                   */
/****************************************************************************/

/****************************************************************************/
/* Begin SW 15/01/03 2226/1102 -> 2227-0103: New function implementation    */
/****************************************************************************/

#define	ADDIDATA_GET_ANALOG_INPUT_MODULE_AUTO_REFRESH_ACQUISITION_INFORMATION_STRUCT_SIZE_REV_1_0	(960)
#define	ADDIDATA_GET_ANALOG_INPUT_MODULE_SEQUENCE_ACQUISITION_INFORMATION_STRUCT_SIZE_REV_1_0		(2072)


typedef struct
	{
	BYTE	b_SoftwareTrigger;			// 0 : Software trigger not available
							// 1 : Software trigger available
	BYTE	b_HardwareTrigger;			// 0 : Hardware trigger not available
							// 1 : Hardware trigger available
	BYTE	b_HardwareGate;				// 0 : Hardware gate not available
							// 1 : Hardware gate available
	BYTE	b_Interrupt;				// 0 : Interrupt can not by generated
							// 1 : Interrupt can by generated (EOC)
	BYTE    b_AccessMode;				// 8  : 8-bit access mode
							// 16 : 16-bit access mode
							// 32 : 32-bit access mode
	BYTE	b_Reserved1 [3];
	BYTE	b_NbrOfGain;				// Returns the number of gain values available
	BYTE	b_Reserved2 [3];
	DOUBLE  d_GainAvailable[255]; 			// Defines the available gain value
	}str_AnalogInputAutoRefreshInformation,*pstr_AnalogInputAutoRefreshInformation;


typedef struct
	{
	BYTE    b_SequenceConfigurable;			// 0 : Sequence fixed. User muss pass the first and last channel
							// 1 : Sequence configurable
	BYTE	b_SoftwareTrigger;			// 0 : Software trigger not available
							// 1 : Software trigger available
	BYTE	b_HardwareTrigger;			// 0 : Hardware trigger not available
							// 1 : Hardware trigger available
	BYTE	b_HardwareGate;				// 0 : Hardware gate not available
							// 1 : Hardware gate available
	
	BYTE	b_UnipolarBipolarConfigurable;		// 0: unipolar/bipolar hardware configurable
							// 1: Unipolar/bipolar configurable
	BYTE	b_UnipolarAvailable;			// 0: Cannot configure in unipolar
							// 1: Can configure in unipolar
	BYTE	b_BipolarAvailable; 			// 0: Cannot configure in bipolar
							// 1: Can configure in bipolar
	BYTE	b_NbrOfGain;				// Returns the number of gain values available
	DOUBLE  d_GainAvailable[255]; 			// Defines the available gain value

	BYTE	b_DelayTimeConfigurable;		// 0 : Delay after each sequence not available
							// 1 : Delay after each sequence available
	BYTE    b_DelayAvailableMode;			// D0: 	0: Mode 1 not available
							//	1: Mode 1 available
							// D1: 	0: Mode 2 not available
							//	1: Mode 2 available
	BYTE	b_DelayCalcType; 			// 0: Binary type (XX000,XX001,XX010,XX011) 
							// 1: Multiple type (60,120,240,480,960, ...) 
	BYTE	b_DelayTimeUnitType;			// 0: Time unit (ns,µs,ms,s, ...) 
							// 1: Frequency unit (MHz,kHz,Hz,mHz, ...) 
	BYTE	b_DelayTimeUnit;			// For time unit: 
							// D0: 	0: ns not available
							//	1: ns available
							// D1:	0: µs not available
							//	1: µs available
							// D2:	0: ms not available
							//	1: ms available
							// D3:	0: s not available
							//	1: s available
							// For frequency unit: 
							// D0: 	0: MHz not available
							//	1: MHz available
							// D1:	0: kHz not available
							//	1: kHz available
							// D2:	0: Hz not available
							//	1: Hz available
							// D3:	0: mHz not available
							//	1: mHz available
	BYTE	b_Reserved1 [3];
	WORD	w_DelayTimeResolution;			// Delay time resolution
							// 8 : 8-bit resolution
							// 16: 16-bit resolution, ... 
	WORD	w_MinDelayTime;				// Minimum delay time. 
							// 7000 : 7000(ns) 
							// 10000: 10000(ns), ... 
	WORD	w_DelayTimeStep;			// Conversion delay time steps
							// 20: 20 steps
							// 50: 50 steps, ... 
	BYTE	b_Reserved2 [2];

	DWORD   dw_MaxNumberOfAcquisition;		// Return the max number of acauisition for the single acquisition sequence mode
	BYTE	b_Reserved3 [4];
	}str_AnalogInputSequenceInformation,*pstr_AnalogInputSequenceInformation;

/****************************************************************************/
/* End SW 15/01/03 2226/1102 -> 2227-0103: New function implementation      */
/****************************************************************************/

#endif
