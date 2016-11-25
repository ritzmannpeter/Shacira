'Author : 
'Dipl.-Ing. A. Traeger
'Traeger Industy Components
'WWW.TRAEGER.DE
'Am Steigacker 26
'D - 92694 Etzenricht
'Tel 0961/482300
'Fax 0961/48230 20
Attribute VB_Name = "PCS7EASY"
'
'/* PCS7EASY.BAS
'*/
'

Declare Function ES7OpenMPILan& Lib "PCS7EASY.DLL" (ByVal IPAdr as String, _
                                              ByVal RxTimeout&, _
                                              ByVal TxTimeout&, _
                                              ByVal ConnectTimeout&, _
											  ByVal SPSMPIAdr&, ByVal LocalMPIAdr&, ByVal SPSTyp&, ByVal MPIBaud&)
     
Declare Function ES7Open& Lib "PCS7EASY.DLL" (ByVal Com&, ByVal SPSMPIAdr&, ByVal LocalMPIAdr&, ByVal Baud&, ByVal SPSTyp&)
Declare Function ES7OpenEx& Lib "PCS7EASY.DLL" (ByVal Com&, ByVal SPSMPIAdr&, ByVal LocalMPIAdr&, ByVal Baud&, ByVal SPSTyp&, ByVal MPIBaud&)
Declare Function ES7Close& Lib "PCS7EASY.DLL" (ByVal Ref&)
Declare Function ES7RdW& Lib "PCS7EASY.DLL" (ByVal Ref&, ByVal Typ&, ByVal DBNr&, ByVal AbWort&, ByVal WortAnz&, Wert As Integer)
Declare Function ES7RdDW& Lib "PCS7EASY.DLL" (ByVal Ref&, ByVal Typ&, ByVal DBNr&, ByVal AbWort&, ByVal WortAnz&, Wert As Long)
Declare Function ES7RdB& Lib "PCS7EASY.DLL" (ByVal Ref&, ByVal Typ&, ByVal DBNr&, ByVal AbWort&, ByVal WortAnz&, Wert As Byte)
Declare Function ES7WrW& Lib "PCS7EASY.DLL" (ByVal Ref&, ByVal Typ&, ByVal DBNr&, ByVal AbWort&, ByVal WortAnz&, Wert As Integer)
Declare Function ES7WrDW& Lib "PCS7EASY.DLL" (ByVal Ref&, ByVal Typ&, ByVal DBNr&, ByVal AbWort&, ByVal WortAnz&, Wert As Long)
Declare Function ES7WrB& Lib "PCS7EASY.DLL" (ByVal Ref&, ByVal Typ&, ByVal DBNr&, ByVal AbWort&, ByVal WortAnz&, Wert As Byte)

Declare Function ES7RdBit& Lib "PCS7EASY.DLL" (ByVal Ref&, ByVal Typ&, ByVal DBNr&, ByVal ByteNr&, ByVal BitNr&, Wert As Byte)
Declare Function ES7SetBit& Lib "PCS7EASY.DLL" (ByVal Ref&, ByVal Typ&, ByVal DBNr&, ByVal ByteNr&, ByVal BitNr&)
Declare Function ES7ResetBit& Lib "PCS7EASY.DLL" (ByVal Ref&, ByVal Typ&, ByVal DBNr&, ByVal ByteNr&, ByVal BitNr&)
Declare Function ES7RdReal& Lib "PCS7EASY.DLL" (ByVal Ref&, ByVal Typ&, ByVal DBNr&, ByVal AbWort&, ByVal WortAnz&, Wert As Double)
Declare Function ES7WrReal& Lib "PCS7EASY.DLL" (ByVal Ref&, ByVal Typ&, ByVal DBNr&, ByVal AbWort&, ByVal WortAnz&, Wert As Double)
