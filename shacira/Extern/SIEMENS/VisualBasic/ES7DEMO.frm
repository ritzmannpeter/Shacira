VERSION 5.00
Begin VB.Form EasyDemo 
   Caption         =   "PC-S7-EASY Demo  Visual Basic 6.0"
   ClientHeight    =   6705
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7290
   LinkTopic       =   "Form1"
   ScaleHeight     =   6705
   ScaleWidth      =   7290
   StartUpPosition =   3  'Windows-Standard
   Begin VB.ComboBox MPIBaudBox 
      Height          =   315
      ItemData        =   "ES7DEMO.frx":0000
      Left            =   960
      List            =   "ES7DEMO.frx":0011
      Style           =   2  'Dropdown-Liste
      TabIndex        =   27
      ToolTipText     =   "MPI-Baudrate (187,5 kBit/s - 19,2 kBit/s - 1,5 MBit/s)"
      Top             =   1200
      Width           =   1335
   End
   Begin VB.CommandButton ES7RdRealCmd 
      Caption         =   "ES7Rd&Real (),REAL lesen / read REAL-Datatype"
      Height          =   615
      Left            =   4080
      TabIndex        =   26
      ToolTipText     =   "Liest von der SPS ab Startadresse Anzahl Worte"
      Top             =   3960
      Width           =   2895
   End
   Begin VB.CommandButton ES7RdDWCmd 
      Caption         =   "ES7Rd&DW (), Doppelworte lesen / read doublewords"
      Height          =   615
      Left            =   4080
      TabIndex        =   25
      ToolTipText     =   "Liest von der SPS ab Startadresse Anzahl Worte"
      Top             =   3240
      Width           =   2895
   End
   Begin VB.PictureBox Logo 
      Height          =   1695
      Left            =   4080
      ScaleHeight     =   1635
      ScaleWidth      =   2835
      TabIndex        =   24
      Top             =   4800
      Width           =   2895
   End
   Begin VB.TextBox DBNrEingabe 
      Alignment       =   1  'Rechts
      Height          =   315
      Left            =   1320
      MaxLength       =   5
      TabIndex        =   22
      Text            =   "1"
      Top             =   3000
      Width           =   735
   End
   Begin VB.CommandButton ES7RdWCmd 
      Caption         =   "ES7Rd&W (), Worte lesen / read words"
      Height          =   375
      Left            =   4080
      TabIndex        =   21
      ToolTipText     =   "Liest von der SPS ab Startadresse Anzahl Worte"
      Top             =   2760
      Width           =   2895
   End
   Begin VB.CommandButton ES7RdBCmd 
      Caption         =   "ES7Rd&B (), Bytes lesen / read bytes"
      Height          =   375
      Left            =   4080
      TabIndex        =   17
      ToolTipText     =   "Liest von der SPS ab Startadresse Anzahl Bytes"
      Top             =   2280
      Width           =   2895
   End
   Begin VB.TextBox AnzahlEingabe 
      Alignment       =   1  'Rechts
      BeginProperty DataFormat 
         Type            =   1
         Format          =   "0,0;(0,0)"
         HaveTrueFalseNull=   0
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
         LCID            =   1031
         SubFormatType   =   1
      EndProperty
      Height          =   315
      Left            =   3000
      TabIndex        =   16
      Text            =   "Anzahl"
      Top             =   3000
      Width           =   735
   End
   Begin VB.TextBox StartAdresseEingabe 
      Alignment       =   1  'Rechts
      Height          =   315
      Left            =   2160
      TabIndex        =   15
      Text            =   "Start"
      Top             =   3000
      Width           =   735
   End
   Begin VB.ComboBox DatenArtBox 
      Height          =   315
      ItemData        =   "ES7DEMO.frx":003C
      Left            =   240
      List            =   "ES7DEMO.frx":0052
      Style           =   2  'Dropdown-Liste
      TabIndex        =   14
      Top             =   3000
      Width           =   975
   End
   Begin VB.TextBox StatusBox 
      BackColor       =   &H00FFFFFF&
      Height          =   885
      Left            =   240
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      TabIndex        =   13
      Text            =   "ES7DEMO.frx":0094
      ToolTipText     =   "Status der ausgeführten Funktion bzw.Fehlernummer / status of function - error info"
      Top             =   1560
      Width           =   3495
   End
   Begin VB.ListBox DataList 
      BeginProperty DataFormat 
         Type            =   1
         Format          =   "0,0000%"
         HaveTrueFalseNull=   0
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
         LCID            =   1031
         SubFormatType   =   5
      EndProperty
      Height          =   3180
      Left            =   240
      TabIndex        =   12
      ToolTipText     =   "Ergebnis der Leseoperation"
      Top             =   3360
      Width           =   3495
   End
   Begin VB.CommandButton ES7CloseCmd 
      Caption         =   "ES7&Close (Ref)"
      Height          =   375
      Left            =   4080
      TabIndex        =   11
      ToolTipText     =   "Schließt die mit ES7Open geöffnete Verbindung"
      Top             =   1800
      Width           =   2895
   End
   Begin VB.CommandButton ES7OpenCmd 
      Caption         =   "Ref = ES7&Open (...)"
      Height          =   375
      Left            =   4080
      TabIndex        =   10
      ToolTipText     =   "Öffnet eine Verbindung mit den gewünschten Parametern"
      Top             =   1320
      Width           =   2895
   End
   Begin VB.ComboBox SPSMPIAdrBox 
      Height          =   315
      ItemData        =   "ES7DEMO.frx":00C5
      Left            =   5640
      List            =   "ES7DEMO.frx":013F
      Style           =   2  'Dropdown-Liste
      TabIndex        =   8
      ToolTipText     =   "Die MPI-Adresse der SPS wählen"
      Top             =   720
      Width           =   1335
   End
   Begin VB.ComboBox EigeneMPIAdrBox 
      Height          =   315
      ItemData        =   "ES7DEMO.frx":01C4
      Left            =   5640
      List            =   "ES7DEMO.frx":023E
      Style           =   2  'Dropdown-Liste
      TabIndex        =   6
      ToolTipText     =   "Eigene MPI-Adresse wählen"
      Top             =   120
      Width           =   1335
   End
   Begin VB.ComboBox SPSTypBox 
      Height          =   315
      ItemData        =   "ES7DEMO.frx":02C3
      Left            =   960
      List            =   "ES7DEMO.frx":02D1
      Style           =   2  'Dropdown-Liste
      TabIndex        =   5
      ToolTipText     =   "SPS-Typ wählen (S7300/400 oder S7 200)"
      Top             =   840
      Width           =   1335
   End
   Begin VB.ComboBox BaudBox 
      Height          =   315
      ItemData        =   "ES7DEMO.frx":02E9
      Left            =   960
      List            =   "ES7DEMO.frx":0310
      Style           =   2  'Dropdown-Liste
      TabIndex        =   3
      ToolTipText     =   "gewünschte Baudrate wählen / chose baudrate"
      Top             =   480
      Width           =   1335
   End
   Begin VB.ComboBox ComBox 
      Height          =   315
      ItemData        =   "ES7DEMO.frx":0337
      Left            =   960
      List            =   "ES7DEMO.frx":0353
      Style           =   2  'Dropdown-Liste
      TabIndex        =   1
      ToolTipText     =   "COM-Schnittstelle wählen"
      Top             =   90
      Width           =   1335
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Rechts
      Caption         =   "MPI-Baud:"
      Height          =   255
      Left            =   0
      TabIndex        =   28
      Top             =   1200
      Width           =   855
   End
   Begin VB.Label Label4 
      Caption         =   "DBNr: DBNo:"
      Height          =   495
      Left            =   1320
      TabIndex        =   23
      Top             =   2520
      Width           =   855
   End
   Begin VB.Label Label7 
      Caption         =   "Anzahl: Count:"
      Height          =   495
      Left            =   3000
      TabIndex        =   20
      Top             =   2520
      Width           =   735
   End
   Begin VB.Label Label6 
      Caption         =   "Startadr.: Startaddr.:"
      Height          =   495
      Left            =   2160
      TabIndex        =   19
      Top             =   2520
      Width           =   735
   End
   Begin VB.Label Label5 
      Caption         =   "Datenart Data type"
      Height          =   495
      Left            =   240
      TabIndex        =   18
      Top             =   2520
      Width           =   855
   End
   Begin VB.Label Label10 
      Alignment       =   1  'Rechts
      Caption         =   "SPS-MPI-Adr: PLC-MPI-Addr:"
      Height          =   495
      Left            =   4200
      TabIndex        =   9
      Top             =   720
      Width           =   1095
   End
   Begin VB.Label Label8 
      Alignment       =   1  'Rechts
      Caption         =   "Eigene MPI-Adr. MPI-Addr of PC:"
      Height          =   495
      Left            =   3720
      TabIndex        =   7
      Top             =   120
      Width           =   1575
   End
   Begin VB.Label Label9 
      Alignment       =   1  'Rechts
      Caption         =   "SPS-Type:"
      Height          =   255
      Left            =   0
      TabIndex        =   4
      Top             =   840
      Width           =   855
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Rechts
      Caption         =   "Baudrate:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   480
      Width           =   735
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Rechts
      Caption         =   "COM:"
      Height          =   255
      Left            =   360
      TabIndex        =   0
      Top             =   120
      Width           =   495
   End
End
Attribute VB_Name = "EasyDemo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim Com As Long
Dim SPSMPIAdr As Long
Dim EigeneMPIAdr As Long
Dim Baudrate As Long
Dim SPSArt As Long
Dim Ref As Long
Dim SPSTyp As Long



Dim ErrText As String
Dim DBNr As Long
Dim StartAdresse As Long
Dim DatenArt As Long
Dim Anzahl As Long
Dim Res As Long
Dim ByteBuffer(0 To 2048) As Byte
Dim WordBuffer(0 To 2048) As Integer
Dim DoubleBuffer(0 To 2048) As Double
Dim DWordBuffer(0 To 2048) As Long



Private Function GetErrText(Res As Long) As String
ErrText = "Fehler:"
ErrText = Switch(Res = 0, "Lesen OK / read OK", _
          Res = -1, "Kabel oder SPS nicht vorhanden / cable or PLC missing", _
          Res = -2, "Keine Resourcen mehr frei / no resource available", _
          Res = -3, "Referenz war nicht geöffnet / reference was not opened", _
          Res = 2, "Datenbereich zu klein oder nicht vorhanden / data space to small or missing", _
          Res = -5, "allgemeiner Fehler / general error", _
          Res = -10, "Datentyp wird nicht unterstützt, data type is not supported", _
          Res = -99, "Referenznummer falsch / ref no. invalid", _
          Res = 4660, "Demozeit abgelaufen / demo time is over")

StatusBox.Text = ErrText
If Res <> 0 Then
  StatusBox.BackColor = &H8080FF
Else
  StatusBox.BackColor = &H80000005
End If

If Res <> 0 Then
  MsgBox "Es ist ein Fehler aufgetreten:" + ErrText, vbOKOnly
End If
GetErrText = ErrText

End Function

Private Function GetErrTextOnOpen(Res As Long) As String
ErrText = "Fehler:"
ErrText = Switch(Res >= 0, "Verbindung ist geöffnet / connection is open", _
          Res = -1, "Keine Resourcen mehr frei / no resource available", _
          Res = -2, "Die Baudrate ist falsch angegeben /inavlid baudrate", _
          Res = -3, "falsche lokale MPI-Adresse / invalid local MPI-Addr", _
          Res = -4, "COM-nicht vorhanden, oder bereits belegt / COM not available", _
          Res = -5, "allgemeiner Fehler / general error", _
          Res = -99, "Referenznummer falsch / ref no. invalid", _
          Res = 4660, "Demozeit abgelaufen / demo time is over")
          
StatusBox.Text = ErrText
If Res < 0 Then
  StatusBox.BackColor = &H8080FF
Else
  StatusBox.BackColor = &H80000005
End If
GetErrTextOnOpen = ErrText
End Function



Private Sub ES7CloseCmd_Click()
ES7Close (Ref)
ES7RdBCmd.Enabled = False
ES7RdWCmd.Enabled = False
ES7CloseCmd.Enabled = False
ES7OpenCmd.Enabled = True
Ref = -1
StatusBox.Text = "Bitte Funktion wählen / seletc function"
StatusBox.BackColor = &H80000005

End Sub

Private Function GetData(bWord As Boolean) As Boolean
GetData = False
DBNr = DBNrEingabe.Text
StartAdresse = StartAdresseEingabe.Text
Anzahl = AnzahlEingabe.Text
DatenArt = Asc(DatenArtBox.Text)

If DatenArt = Asc("Z") Then
  bWord = False
End If
If Anzahl <= 0 Or Anzahl > 2048 Then
  MsgBox "Anzahl ist ungültig: Eingabe 1 .. 2048", vbOKOnly
Exit Function
End If

If DBNr < 0 Or DBNr > 65535 Then
  MsgBox "Datenbausteinnumer ist ungültig: Eingabe 0 .. 65535", vbOKOnly
Exit Function
End If

If StartAdresse < 0 Or StartAdresse > 65535 Then
  MsgBox "Startadresse ist ungültig: Eingabe 0 .. 65535", vbOKOnly
Exit Function
End If
If bWord = True Then
  If StartAdresse Mod 2 <> 0 Then
    MsgBox "Es sind nur gerade Startadressen zugelassen: Eingabe 0, 2,4 .", vbOKOnly
  End If
End If
GetData = True
End Function
Private Sub ES7OpenCmd_Click()
Com = ComBox.ItemData(ComBox.ListIndex)
SPSMPIAdr = SPSMPIAdrBox.ItemData(SPSMPIAdrBox.ListIndex)
EigeneMPIAdr = EigeneMPIAdrBox.ItemData(EigeneMPIAdrBox.ListIndex)
SPSTyp = SPSTypBox.ItemData(SPSTypBox.ListIndex)
Baudrate = BaudBox.ItemData(BaudBox.ListIndex)
Ref = ES7OpenEx(Com, SPSMPIAdr, EigeneMPIAdr, Baudrate, SPSTyp, MPIBaudBox.ListIndex)
GetErrTextOnOpen (Ref)
If Ref >= 0 Then
  ES7OpenCmd.Enabled = False
  ES7RdBCmd.Enabled = True
  ES7RdWCmd.Enabled = True
  ES7CloseCmd.Enabled = True
End If
End Sub

Private Sub ES7RdBCmd_Click()
Dim Help As String
Dim i As Integer
Dim ListText As String

If GetData(False) = True Then
  Screen.MousePointer = vbHourglass
  Res = ES7RdB(Ref, DatenArt, DBNr, StartAdresse, Anzahl, ByteBuffer(0))
  Screen.MousePointer = vbDefault
  GetErrText (Res)
  If Res = 0 Then
    DataList.Clear
    Help = Switch(DatenArt = Asc("M"), "MB", _
            DatenArt = Asc("E"), "EB", _
            DatenArt = Asc("A"), "AB", _
            DatenArt = Asc("D"), "DB")
    
    For i = 0 To Anzahl - 1
    ListText = Help + Format(i + StartAdresse, "#####0000") + "=" + Format(ByteBuffer(i), "######00000")
    DataList.AddItem (ListText)
    Next i
    'Liste füllen und anzeigen
  End If
End If
End Sub

Private Sub ES7RdDWCmd_Click()
Dim Help As String
Dim ListText As String
Dim Faktor As Integer

Dim i As Integer
If GetData(False) = True Then
  Screen.MousePointer = vbHourglass
  Res = ES7RdDW(Ref, DatenArt, DBNr, StartAdresse, Anzahl, DWordBuffer(0))
  Screen.MousePointer = vbDefault
  GetErrText (Res)
  Faktor = 2
  If Res = 0 Then
    DataList.Clear
    Help = Switch(DatenArt = Asc("M"), "MW", _
            DatenArt = Asc("E"), "EW", _
            DatenArt = Asc("A"), "AW", _
            DatenArt = Asc("T"), "T", _
            DatenArt = Asc("D"), "DB" + Format(DBNr, "###") + ".DBDW")
    
    If DatenArt = Asc("T") Then
      Faktor = 1
    End If
    For i = 0 To Anzahl - 1
    ListText = Help + Format(i * Faktor + StartAdresse, "#######0000") + "=" + Format(DWordBuffer(i), "######00000")
    DataList.AddItem (ListText)
    Next i
  End If
End If

End Sub

Private Sub ES7RdRealCmd_Click()
Dim Help As String
Dim ListText As String
Dim i As Integer
If GetData(False) = True Then
  Screen.MousePointer = vbHourglass
  Res = ES7RdReal(Ref, DatenArt, DBNr, StartAdresse, Anzahl, DoubleBuffer(0))
   
  Screen.MousePointer = vbDefault
  GetErrText (Res)
  
  If Res = 0 Then
    DataList.Clear
    Help = Switch(DatenArt = Asc("M"), "ab MB", _
            DatenArt = Asc("E"), "ab EB", _
            DatenArt = Asc("A"), "ab ", _
            DatenArt = Asc("D"), "ab DB" + Format(DBNr, "###") + ".DBB")
    For i = 0 To Anzahl - 1
      ListText = Help + Format(i * 4 + StartAdresse, "#####0000") + "=" + Format(DoubleBuffer(i), "#.#0.00000")
      DataList.AddItem (ListText)
    Next i
  End If
End If

End Sub

Private Sub ES7RdWCmd_Click()
Dim Help As String
Dim ListText As String
Dim i As Integer
Dim Faktor As Integer
Faktor = 2
If GetData(True) = True Then
  Screen.MousePointer = vbHourglass
  If DatenArt = Asc("Z") Then
      Res = ES7RdW(Ref, DatenArt, DBNr, StartAdresse, Anzahl, WordBuffer(0))
  Else
    Res = ES7RdW(Ref, DatenArt, DBNr, StartAdresse / 2, Anzahl, WordBuffer(0))
  End If
  Screen.MousePointer = vbDefault
  GetErrText (Res)
  
  If Res = 0 Then
    DataList.Clear
    Help = Switch(DatenArt = Asc("M"), "MW", _
            DatenArt = Asc("E"), "EW", _
            DatenArt = Asc("A"), "AW", _
            DatenArt = Asc("Z"), "Z", _
            DatenArt = Asc("D"), "DB" + Format(DBNr, "###") + ".DBW")
    
    If (DatenArt = Asc("Z")) Then
      Faktor = 1
    End If
    
    
    For i = 0 To Anzahl - 1
    ListText = Help + Format(i * Faktor + StartAdresse, "#####0000") + "=" + Format(WordBuffer(i), "######00000")
    DataList.AddItem (ListText)
    Next i
  End If
End If
End Sub

Private Sub Form_Load()
Dim Fs As Object
Set Fs = CreateObject("Scripting.FileSystemObject")
If (Fs.FileExists(App.Path + "\OEM.BMP") = True) Then
  Logo.Picture = LoadPicture(App.Path + "\OEM.BMP")
End If
ComBox.ListIndex = 0
BaudBox.ListIndex = 2
SPSTypBox.ListIndex = 0
SPSMPIAdrBox.ListIndex = 2
EigeneMPIAdrBox.ListIndex = 0
DatenArtBox.ListIndex = 0
StartAdresseEingabe.Text = 0
AnzahlEingabe.Text = 1
MPIBaudBox.ListIndex = 0
ES7RdBCmd.Enabled = False
ES7RdWCmd.Enabled = False
ES7CloseCmd.Enabled = False
Ref = -1
End Sub

