/*
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstraße 3       D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-------------------------------+---------------------------------------+
  | Project     : API  ADDI-DATA  |     Compiler   : BORLANDC/MICROSOFT C |
  | Module name : RESIS.H         |     Version    : 3.1     / 6.0        |
  |                               |                                       |
  |                               |                                       |
  +-------------------------------+---------------------------------------+
  | Author : Guinot C.                    Date :22/09/2000                |
  +-----------------------------------------------------------------------+
  | Description   : Header file for the ADDI-DATA Resistance              |
  |	            funtionality driver                                   |
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


#ifndef ADDIDATA_RESISTANCE_HEADER
   #define ADDIDATA_RESISTANCE_HEADER

   /*************************************************************************/
   /* Resis.c                                                               */
   /*************************************************************************/
   _BYTE_ b_ADDIDATA_GetNumberOfResistanceChannels (DWORD dw_DriverHandle,
		                                    PWORD pw_ChannelNbr);

   _BYTE_ b_ADDIDATA_GetNumberOfResistanceModules (DWORD dw_DriverHandle,
						   PWORD pw_ModuleNbr);

   _BYTE_ b_ADDIDATA_GetNumberOfResistanceChannelsForTheModule (DWORD dw_DriverHandle,
							        WORD w_Module,
							        PWORD pw_ChannelNbr);
   
   _BYTE_ b_ADDIDATA_GetResistanceChannelInformation (DWORD dw_DriverHandle,
	    					      WORD w_Channel,
						      pstr_GetAnalogMesureInformation ps_ChannelInformation,
						      DWORD     dw_StructSize);

   _BYTE_ b_ADDIDATA_InitResistanceChannel (DWORD dw_DriverHandle,
					    WORD w_Channel,
					    pstr_InitResistanceChannel  ps_InitParameters,
					    DWORD dw_StructSize);
   
   _BYTE_ b_ADDIDATA_TestResistanceChannelShortCircuit  (DWORD dw_DriverHandle, 
                                                         WORD    w_Channel,
                                                         BYTE    b_SignTest,
                                                         DOUBLE d_VoltageValue,
                                                         PBYTE   pb_ShortCircuit);

   _BYTE_ b_ADDIDATA_TestResistanceChannelConnection  (DWORD dw_DriverHandle, 
                                                       WORD    w_Channel,
                                                       BYTE    b_SignTest,
                                                       DOUBLE d_VoltageValue,
                                                       PBYTE   pb_ConnectionStatus);

  
   _BYTE_ b_ADDIDATA_Read1ResistanceChannel (DWORD     dw_DriverHandle,
					     WORD       w_Channel,
					     DWORD     dw_ConversionTime,
					     BYTE       b_ConversionTimeUnit,
					     BYTE       b_InterruptFlag,
					     PDWORD   pdw_ChannelValue);

   _BYTE_ b_ADDIDATA_ReadMoreResistanceChannel (DWORD dw_DriverHandle,
					        WORD w_FirstChannel,
					        WORD w_LastChannel,
					        DWORD dw_ConversionTime,
					        BYTE b_ConversionTimeUnit,
					        BYTE b_InterruptFlag,
					        PDWORD pdw_ChannelArrayValue);

   _BYTE_ b_ADDIDATA_ConvertDigitalToRealResistanceValue (DWORD dw_DriverHandle,
                                                          WORD w_Channel,
                                                          PDWORD pdw_DigitalValue,
                                                          DOUBLE *pd_RealValue);

   _BYTE_ b_ADDIDATA_ConvertMoreDigitalToRealResistanceValues (DWORD dw_DriverHandle,
                                                               WORD w_FirstChannel,
					  		       WORD w_LastChannel,
                                                               PDWORD pdw_DigitalValue,
                                                               DOUBLE *pd_RealValue);

   _BYTE_ b_ADDIDATA_InitResistanceChannelSCAN (DWORD dw_DriverHandle,
					        pstr_InitResistanceChannelSCAN ps_InitParameters,
                                                DWORD dw_StructSize, 
					        PDWORD pdw_SCANHandle);

   _BYTE_ b_ADDIDATA_StartResistanceChannelSCAN (DWORD dw_DriverHandle,
                                                 DWORD dw_SCANHandle);

   _BYTE_ b_ADDIDATA_GetResistanceChannelSCANStatus (DWORD dw_DriverHandle,
                                                     DWORD dw_SCANHandle,
                                                     PBYTE   pb_SCANStatus);

   _BYTE_ b_ADDIDATA_ConvertDigitalToRealResistanceValueSCAN (DWORD dw_DriverHandle,
                                                              DWORD dw_SCANHandle,
                                                              PDWORD pdw_DigitalValueArray,
                                                              DOUBLE *pd_RealValueArray);

   _BYTE_ b_ADDIDATA_StopResistanceChannelSCAN (DWORD dw_DriverHandle,
                                                DWORD dw_SCANHandle);

   _BYTE_ b_ADDIDATA_CloseResistanceChannelSCAN (DWORD dw_DriverHandle,
                                                 DWORD dw_SCANHandle);

   _BYTE_ b_ADDIDATA_ReleaseResistanceChannel	(DWORD dw_DriverHandle,
						 WORD	w_Channel);


   // Begin CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
   _BYTE_ b_ADDIDATA_TestResistanceAsynchronousFIFOFull (DWORD dw_DriverHandle,PBYTE_ pb_Full);
   // End CG 15/11/02 2224/0602 -> 2225/1102 : FIFO Full Management
#endif