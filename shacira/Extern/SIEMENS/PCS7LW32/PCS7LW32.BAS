'  Modul       : PCS7LW32.BAS
'  Projekt     : Datenkopplung SIMATIC-S7 300/400 <----> IBM-PC
'                mit PC/MPI-Adapter
'
'  for changes and version notes see "version.txt"
'
                     


'------------------------------------------------------------
'---------------------Konstantendefinitionen-----------------
'------------------------------------------------------------


'--------------------- Fehlerarten --------------------------
         
Attribute VB_Name = "PCS7LW32"

Global Const S7_E_NOERR = 0               '/* alles OK */
Global Const S7_E_TIMEOUT = -1            '/* Zeitberlauf */
Global Const S7_E_BADBAUD = -2            '/* Baudrate ungltig */
Global Const S7_E_BADMPIADR = -3          '/* MPI-Adresse ungltig */
Global Const S7_E_NOBST = 2
Global Const S7_E_BSTLEN = 2              '/* Baustein ist zu kurz */
Global Const S7_E_NODATA = 2              '/* Datenbereich existiert nicht */
Global Const S7_E_BADADDRESS = 3          '//##MS 24.04.95
Global Const S7_E_BADCMD = 4              '//##ST 02.09.1995
Global Const S7_E_TOMANY = 7              '/* Anzahl der Datenmenge zu gross */
Global Const S7_E_SLAVEOUT = 8
Global Const S7_E_CMDLOCKED = 9
Global Const S7_E_NOCOM = -4              ' Com nicht vorhanden
Global Const S7_E_DEMOEND = &H1234

Global Const Com1 = 0
Global Const Com2 = 1
Global Const Com3 = 2
Global Const Com4 = 3
Global Const Com5 = 4
Global Const Com6 = 5
Global Const Com7 = 6
Global Const Com8 = 7
Global Const Com9 = 8
Global Const Com10 = 9
Global Const Com11 = 10
Global Const Com12 = 11
Global Const Com13 = 12
Global Const Com14 = 13
Global Const Com15 = 14
Global Const Com16 = 15
                          
'------------------------------------------------------------
'--------------------- Datentypendefinitionen ---------------
'------------------------------------------------------------

Type S7
  Com      As Integer
  bInit    As Byte
  
  DummyB1   As Byte
 
  DummyB2   As Integer
  Err      As Integer
  Internal(1 To 1600) As Byte
End Type
        
' ------------------------------------------------------------------
' --------------------- globale Funktionen -------------------------
' ------------------------------------------------------------------

        
Declare Function S7Init& Lib "PCS7LW32.dll" (pS7 As S7, ByVal Com%, ByVal SPSMPIAdr%, ByVal LocalMPIAdr%, ByVal Baud%)
Declare Function S7PPIInit& Lib "PCS7LW32.dll" (pS7 As S7, ByVal Com%, ByVal SPSMPIAdr%, ByVal LocalMPIAdr%, ByVal Baud%)
                   
Declare Function S7InitFastBaud& Lib "PCS7LW32.dll" (pS7 As S7,  ByVal Com%, ByVal SPSMPIAdr%, ByVal LocalMPIAdr%, ByVal Baud&)
'
'      Zweck:  S7InitFastBaud initialisiert das in pS7 beschriebene an pS7->Com 
'              angeschlossene AG und die dazugeh”rige Schnittstelle. 
'              pS7->Com muá COM1, COM2, COM3 ... COM16 sein. 
'              pS7->MPINr ist die MPI-Nummer 
'  
'  Parameter:  Name          Typ      Beschreibung
'                            
'              pS7           LPS7      Pointer auf den Speicher fr das angew„hlte 
'                                     AG 
'              SPSMPIAdr     WORD     MPI-Adresse des Partner (SPS)
'              LocalMPIAdr   WORD     eigen MPI-Adresse (normal 0)
'              Baud          DWORD     19200, 38400, 57600
' 
'     Return:  BOOL          TRUE    wenn erfolgreich, 
'                            FALSE   bei Fehler pS7->Err auswerten
'
' 

/*------------------------------------------------------------*/





Declare Function S7Exit& Lib "PCS7LW32.dll" (pS7 As S7)
'------------------------------------------------------------

Declare Function S7WrMW& Lib "PCS7LW32.dll" (pS7 As S7, ByVal ABWort%, ByVal WortAnz%, SrcBuf As Any)

' ------------------------------------------------------------------
              
Declare Function S7RdMW& Lib "PCS7LW32.dll" (pS7 As S7, ByVal ABWort%, ByVal WortAnz%, DstBuf As Any)

' ------------------------------------------------------------------
  
Declare Function S7WrEW& Lib "PCS7LW32.dll" (pS7 As S7, ByVal ABWort%, ByVal WortAnz%, SrcBuf As Any)

' ------------------------------------------------------------------
              
Declare Function S7RdEW& Lib "PCS7LW32.dll" (pS7 As S7, ByVal ABWort%, ByVal WortAnz%, DstBuf As Any)

' ------------------------------------------------------------------

Declare Function S7WrAW& Lib "PCS7LW32.dll" (pS7 As S7, ByVal ABWort%, ByVal WortAnz%, SrcBuf As Any)

' ------------------------------------------------------------------
              
Declare Function S7RdAW& Lib "PCS7LW32.dll" (pS7 As S7, ByVal ABWort%, ByVal WortAnz%, DstBuf As Any)

' ------------------------------------------------------------------

Declare Function S7WrMB& Lib "PCS7LW32.dll" (pS7 As S7, ByVal ABWort%, ByVal WortAnz%, SrcBuf As Any)

' ------------------------------------------------------------------
              
Declare Function S7RdMB& Lib "PCS7LW32.dll" (pS7 As S7, ByVal ABWort%, ByVal WortAnz%, DstBuf As Any)

' ------------------------------------------------------------------
  
Declare Function S7WrEB& Lib "PCS7LW32.dll" (pS7 As S7, ByVal ABWort%, ByVal WortAnz%, SrcBuf As Any)

' ------------------------------------------------------------------
              
Declare Function S7RdEB& Lib "PCS7LW32.dll" (pS7 As S7, ByVal ABWort%, ByVal WortAnz%, DstBuf As Any)

' ------------------------------------------------------------------

Declare Function S7WrAB& Lib "PCS7LW32.dll" (pS7 As S7, ByVal ABWort%, ByVal WortAnz%, SrcBuf As Any)

' ------------------------------------------------------------------
              
Declare Function S7RdAB& Lib "PCS7LW32.dll" (pS7 As S7, ByVal ABWort%, ByVal WortAnz%, DstBuf As Any)

' ------------------------------------------------------------------

Declare Function S7WrTimer& Lib "PCS7LW32.dll" (pS7 As S7, ByVal ABWort%, ByVal WortAnz%, SrcBuf As Long)

' ------------------------------------------------------------------
              
Declare Function S7RdTimer& Lib "PCS7LW32.dll" (pS7 As S7, ByVal ABWort%, ByVal WortAnz%, DstBuf As Long)

' ------------------------------------------------------------------

Declare Function S7WrCounter& Lib "PCS7LW32.dll" (pS7 As S7, ByVal ABWort%, ByVal WortAnz%, SrcBuf As Any)

' ------------------------------------------------------------------
              
Declare Function S7RdCounter& Lib "PCS7LW32.dll" (pS7 As S7, ByVal ABWort%, ByVal WortAnz%, DstBuf As Any)

' ------------------------------------------------------------------

Declare Function S7RdDB& Lib "PCS7LW32.dll" (pS7 As S7, ByVal DBNr%, ByVal ABWort%, ByVal WortAnz%, DstBuf As Any)

' ------------------------------------------------------------------
Declare Function S7WrDB& Lib "PCS7LW32.dll" (pS7 As S7, ByVal DBNr%, ByVal ABWort%, ByVal WortAnz%, DstBuf As Any)

                   

Declare Sub S7ExitAll Lib "PCS7LW32.dll" ()
