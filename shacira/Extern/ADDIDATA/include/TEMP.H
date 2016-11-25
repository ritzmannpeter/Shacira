/*
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstraße 3       D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-------------------------------+---------------------------------------+
  | Project     : API  ADDI-DATA  |     Compiler   : BORLANDC/MICROSOFT C |
  | Module name : TEMP.H          |     Version    : 3.1     / 6.0        |
  |                               |                                       |
  |                               |                                       |
  +-------------------------------+---------------------------------------+
  | Author : Weber S.                      Date :16/12/1999               |
  +-----------------------------------------------------------------------+
  | Description   : Header file for the ADDI-DATA temperature funtionality|
  |		    driver                                                |
  +-----------------------------------------------------------------------+
  |                             UPDATES                                   |
  +----------+-----------+------------------------------------------------+
  |   Date   |   Author  |          Description of updates                |
  +----------+-----------+------------------------------------------------+
  | 18/09/00 | Guinot C. | 0800/0200 -> 0900/0210                         |
  |          |           | New functions _BYTE_ instead of _BOOL_         |
  +----------+-----------+------------------------------------------------+
  | 15/11/02 | C.Guinot  | 2224/0602 -> 2225/1102                         |
  |          |           | implementation of the FIFO overflow management |
  |          |           | by the interrupt asynchrone Mode               |
  +----------+-----------+------------------------------------------------+
  */

#ifndef ADDIDATA_TEMPERATURE_HEADER
   #define ADDIDATA_TEMPERATURE_HEADER

   /*************************************************************************/
   /* Temp.c                                                                */
   /*************************************************************************/
   _BYTE_ b_ADDIDATA_GetNumberOfTemperatureChannels (DWORD dw_DriverHandle,
                          			     PWORD pw_ChannelNbr);

   _BYTE_ b_ADDIDATA_GetNumberOfTemperatureModules (DWORD dw_DriverHandle,
    			                            PWORD pw_ModuleNbr);

   _BYTE_ b_ADDIDATA_GetNumberOfTemperatureChannelsForTheModule (DWORD dw_DriverHandle,
							         WORD w_Module,
							         PWORD pw_ChannelNbr);

   _BYTE_ b_ADDIDATA_GetTemperatureChannelInformation (DWORD dw_DriverHandle,
	    					       WORD w_Channel,
						       pstr_GetAnalogMesureInformation ps_ChannelInformation,
						       DWORD     dw_StructSize);

   _BYTE_ b_ADDIDATA_InitTemperatureChannel (DWORD dw_DriverHandle,
					     WORD w_Channel,
					     WORD w_Gain,
					     BYTE b_Polarity,
					     WORD w_OffsetRange);


   _BYTE_ b_ADDIDATA_TestTemperatureChannelShortCircuit  (DWORD dw_DriverHandle, 
                                                          WORD    w_Channel,
                                                          BYTE    b_SignTest,
                                                          DOUBLE d_VoltageValue,
                                                          PBYTE   pb_ShortCircuit);

   _BYTE_ b_ADDIDATA_TestTemperatureChannelConnection  (DWORD dw_DriverHandle, 
                                                     WORD    w_Channel,
                                                     BYTE    b_SignTest,
                                                     DOUBLE d_VoltageValue,
                                                     PBYTE   pb_ConnectionStatus);


   _BYTE_  b_ADDIDATA_Read1TemperatureChannel 	     	   (DWORD     dw_DriverHandle,
							    WORD       w_Channel,
							    DWORD     dw_ConversionTime,
							    BYTE       b_ConversionTimeUnit,
							    BYTE       b_InterruptFlag,
							    PDWORD   pdw_ChannelValue);

   _BYTE_ b_ADDIDATA_ReadMoreTemperatureChannel (DWORD dw_DriverHandle,
						 WORD w_FirstChannel,
						 WORD w_LastChannel,
						 DWORD dw_ConversionTime,
						 BYTE b_ConversionTimeUnit,
						 BYTE b_InterruptFlag,
						 PDWORD pdw_ChannelArrayValue);


   _BYTE_  b_ADDIDATA_ConvertDigitalToRealTemperatureValue (DWORD   dw_DriverHandle,
							    WORD    w_Channel,
							    DWORD   dw_DigitalValue,
							    DOUBLE *pd_RealValue);

   _BYTE_ b_ADDIDATA_ConvertDigitalToRealTemperatureValueWithCorrectionParameters (DWORD dw_DriverHandle,
                                                                                WORD w_Channel,
                                                                                PDWORD pdw_DigitalValue,
                                                                                DOUBLE *pd_RealValue);
   
   _BYTE_ b_ADDIDATA_ConvertMoreDigitalToRealTemperatureValues (DWORD dw_DriverHandle,
                                                                WORD w_FirstChannel,
						      	        WORD w_LastChannel,
                                                                PDWORD pdw_DigitalValue,
                                                                DOUBLE *pd_RealValue);


   _BYTE_ b_ADDIDATA_InitTemperatureChannelSCAN (DWORD dw_DriverHandle,
		       			         pstr_InitTemperatureChannelSCAN ps_InitParameters,
                                                 DWORD dw_StructSize, 
					         PDWORD pdw_SCANHandle);

   _BYTE_ b_ADDIDATA_StartTemperatureChannelSCAN (DWORD dw_DriverHandle,
                                                  DWORD dw_SCANHandle);

   _BYTE_ b_ADDIDATA_GetTemperatureChannelSCANStatus (DWORD dw_DriverHandle,
                                                      DWORD dw_SCANHandle,
                                                      PBYTE   pb_SCANStatus);

   _BYTE_ b_ADDIDATA_ConvertDigitalToRealTemperatureValueSCAN (DWORD dw_DriverHandle,
                                                               DWORD dw_SCANHandle,
                                                               PDWORD pdw_DigitalValueArray,
                                                               DOUBLE *pd_RealValueArray);
   
   _BYTE_ b_ADDIDATA_StopTemperatureChannelSCAN (DWORD dw_DriverHandle,
                                                 DWORD dw_SCANHandle);

   _BYTE_ b_ADDIDATA_CloseTemperatureChannelSCAN (DWORD dw_DriverHandle,
                                                  DWORD dw_SCANHandle);


   _BYTE_  b_ADDIDATA_InitTemperatureWarning		   (DWORD dw_DriverHandle,
							    WORD   w_Channel,
							    WORD   w_Gain,
							    BYTE   b_Polarity,
							    WORD   w_Offset,
							    DOUBLE d_WarningValue);

   
   _BYTE_  b_ADDIDATA_ReleaseTemperatureWarning		   (DWORD dw_DriverHandle,
							    WORD   w_Channel);


   _BYTE_	b_ADDIDATA_ReleaseTemperatureChannel	(DWORD dw_DriverHandle,
												 WORD	w_Channel);
   
   _BYTE_  b_ADDIDATA_EnableDisableTemperatureWarningChannel (DWORD dw_DriverHandle,
							      WORD	  w_Channel,
							      BYTE	  b_WarningFlag);

   _BYTE_  b_ADDIDATA_StartAllTemperatureWarnings	     (DWORD dw_DriverHandle);

   _BYTE_  b_ADDIDATA_StopAllTemperatureWarnings		     (DWORD dw_DriverHandle);


   _BYTE_ b_ADDIDATA_ConvertDegreeToFahrenheit (DOUBLE d_DegreeValue,
					        DOUBLE *pd_FahrenheitValue);

   _BYTE_ b_ADDIDATA_ConvertDegreeToKelvin (DOUBLE d_DegreeValue,
					    DOUBLE *pd_KelvinValue);

   


   // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
   _BYTE_ b_ADDIDATA_TestTemperatureAsynchronousFIFOFull (DWORD dw_DriverHandle,PBYTE_ pb_Full);
   // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management


#endif