/*
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstraße 3       D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-------------------------------+---------------------------------------+
  | Project     : API  ADDI-DATA  |     Compiler   : BORLANDC/MICROSOFT C |
  | Module name : ANA_INP.H       |     Version    : 3.1     / 6.0        |
  |                               |                                       |
  |                               |                                       |
  +-------------------------------+---------------------------------------+
  | Author : S. Weber                     Date :25/03/2002                |
  +-----------------------------------------------------------------------+
  | Description   : Header file for the ADDI-DATA pressure                |
  |		    funtionality driver                                   |
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


#ifndef ADDIDATA_PRESSURE_HEADER
   #define ADDIDATA_PRESSURE_HEADER

   /*************************************************************************/
   /* Pressure.c                                                            */
   /*************************************************************************/

   _BYTE_ b_ADDIDATA_GetNumberOfPressureChannels         (DWORD dw_DriverHandle,
							  PWORD pw_ChannelNbr);

   _BYTE_ b_ADDIDATA_GetNumberOfPressureModules          (DWORD dw_DriverHandle,
							  PWORD pw_ModuleNbr);

   _BYTE_ b_ADDIDATA_GetNumberOfPressureChannelsForTheModule (DWORD dw_DriverHandle,
							      WORD w_Module,
							      PWORD pw_ChannelNbr);

   _BYTE_ b_ADDIDATA_GetPressureChannelInformation       (DWORD dw_DriverHandle,
							  WORD w_Channel,
							  pstr_GetAnalogMesureInformation ps_ChannelInformation,
							  DWORD     dw_StructSize);

   _BYTE_ b_ADDIDATA_InitPressureChannel                 (DWORD dw_DriverHandle,
							  WORD w_Channel,
							  pstr_InitPressureChannel ps_InitParameters,
							  DWORD dw_StructSize);

   _BYTE_ b_ADDIDATA_Read1PressureChannel                (DWORD     dw_DriverHandle,
							  WORD       w_Channel,
							  DWORD     dw_ConversionTime,
							  BYTE       b_ConversionTimeUnit,
							  BYTE       b_InterruptFlag,
							  PDWORD   pdw_ChannelValue);

   _BYTE_ b_ADDIDATA_ReadMorePressureChannels            (DWORD dw_DriverHandle,
							  WORD w_FirstChannel,
							  WORD w_LastChannel,
							  DWORD dw_ConversionTime,
							  BYTE b_ConversionTimeUnit,
							  BYTE b_InterruptFlag,
							  PDWORD pdw_ChannelArrayValue);

   _BYTE_ b_ADDIDATA_ConvertDigitalToRealPressureValue    (DWORD	   dw_DriverHandle, 
							   WORD	            w_Channel,
							   PDWORD	  pdw_DigitalValue,
							   DOUBLE	*  pd_RealValue);

   _BYTE_ b_ADDIDATA_ConvertMoreDigitalToRealPressureValues (DWORD	 dw_DriverHandle, 
				                             WORD 	  w_FirstChannel,
				                             WORD 	  w_LastChannel,
				                             PDWORD	pdw_DigitalValue,
				                             DOUBLE	*pd_RealValue);

   _BYTE_ b_ADDIDATA_InitPressureSCAN                    (DWORD dw_DriverHandle,
							  pstr_InitPressureSCAN ps_InitParameters,
							  DWORD dw_StructSize,
							  PDWORD pdw_SCANHandle);

   _BYTE_ b_ADDIDATA_StartPressureSCAN                  (DWORD dw_DriverHandle,
							  DWORD dw_SCANHandle);

   _BYTE_ b_ADDIDATA_GetPressureSCANStatus               (DWORD dw_DriverHandle,
							  DWORD dw_SCANHandle,
							  PBYTE   pb_SCANStatus);

   _BYTE_ b_ADDIDATA_ConvertDigitalToRealPressureValueSCAN (DWORD	 dw_DriverHandle, 
				                            DWORD	 dw_SCANHandle,
				                            PDWORD	pdw_DigitalValueArray,
				                            DOUBLE*	 pd_RealValueArray);


   _BYTE_ b_ADDIDATA_StopPressureSCAN                    (DWORD dw_DriverHandle,
							  DWORD dw_SCANHandle);

   _BYTE_ b_ADDIDATA_ClosePressureSCAN                   (DWORD dw_DriverHandle,
							  DWORD dw_SCANHandle);

   _BYTE_ b_ADDIDATA_ReleasePressureChannel	         (DWORD dw_DriverHandle,
							  WORD	w_Channel);

   _BYTE_ b_ADDIDATA_ConvertBarToPa			 (DOUBLE	 d_BarValue,
				 	                  DOUBLE*	pd_PaValue);

   _BYTE_ b_ADDIDATA_ConvertBarToPsi	                 (DOUBLE	 d_BarValue,
				 	                  DOUBLE*	pd_PsiValue);

   // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
   _BYTE_ b_ADDIDATA_TestPressureAsynchronousFIFOFull (DWORD dw_DriverHandle,PBYTE_ pb_Full);
   // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management

   _BYTE_ b_ADDIDATA_GetPressureChannelReferenceVoltage  (DWORD   dw_DriverHandle,
                                                          WORD     w_Channel,
                                                          DOUBLE *pd_RefVoltage);

   _BYTE_ b_ADDIDATA_GetPressureChannelGainFactor	 (DWORD   dw_DriverHandle,
							  WORD     w_Channel,
							  DOUBLE *pd_GainFactor);


#endif