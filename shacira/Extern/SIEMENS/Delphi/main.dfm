object InternetDemo: TInternetDemo
  Left = 280
  Top = 159
  Width = 577
  Height = 534
  Caption = 'PC-S7-LINK-Demo (Easy)Delphi'
  Color = clMenu
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Label13: TLabel
    Left = 8
    Top = 328
    Width = 33
    Height = 13
    Caption = 'Status:'
  end
  object Label15: TLabel
    Left = 8
    Top = 448
    Width = 64
    Height = 13
    Caption = 'PC-MPI-Addr:'
  end
  object Label16: TLabel
    Left = 152
    Top = 448
    Width = 71
    Height = 13
    Caption = 'SPS/PLC-Addr'
  end
  object Label18: TLabel
    Left = 152
    Top = 416
    Width = 73
    Height = 13
    Caption = 'SPS/PLC-Type'
  end
  object Label6: TLabel
    Left = 8
    Top = 480
    Width = 47
    Height = 13
    Caption = 'MPI-Baud'
  end
  object Panel7: TPanel
    Left = 328
    Top = 328
    Width = 233
    Height = 121
    Caption = 'Panel7'
    TabOrder = 3
    object Logo: TImage
      Left = 16
      Top = 8
      Width = 201
      Height = 105
    end
  end
  object ButtonInit: TButton
    Left = 152
    Top = 472
    Width = 73
    Height = 25
    Caption = 'IPS7Open'
    TabOrder = 0
    OnClick = ButtonInitClick
  end
  object ButtonExit: TButton
    Left = 232
    Top = 472
    Width = 73
    Height = 25
    Caption = 'IPS7Close'
    Enabled = False
    TabOrder = 1
    OnClick = ButtonExitClick
  end
  object EditStatus: TEdit
    Left = 8
    Top = 344
    Width = 305
    Height = 57
    AutoSize = False
    TabOrder = 2
  end
  object PageControl1: TPageControl
    Left = 7
    Top = 7
    Width = 554
    Height = 312
    ActivePage = TabSheet3
    TabOrder = 4
    TabWidth = 140
    object TabSheet3: TTabSheet
      Caption = 'DB / data block'
      object Panel1: TPanel
        Left = 7
        Top = 7
        Width = 330
        Height = 273
        BevelInner = bvLowered
        BevelOuter = bvLowered
        TabOrder = 0
        object Label1: TLabel
          Left = 49
          Top = 17
          Width = 51
          Height = 13
          Caption = 'DB Nr./No'
        end
        object Label3: TLabel
          Left = 9
          Top = 49
          Width = 89
          Height = 13
          Caption = 'AbWort/Start word'
        end
        object Label4: TLabel
          Left = 31
          Top = 81
          Width = 70
          Height = 13
          Caption = 'Anzahl / count'
        end
        object ButtonDBLesen: TButton
          Left = 160
          Top = 73
          Width = 75
          Height = 20
          Caption = 'Lesen/read'
          Enabled = False
          TabOrder = 4
          OnClick = ButtonDBLesenClick
        end
        object Memo2: TMemo
          Left = 16
          Top = 112
          Width = 233
          Height = 143
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
          ReadOnly = True
          ScrollBars = ssVertical
          TabOrder = 3
        end
        object ComboBoxDBLesen: TComboBox
          Left = 161
          Top = 10
          Width = 76
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 2
          Items.Strings = (
            'Dez / dec'
            'Hex'
            'Bin')
        end
        object MaskEditAbWortLesen: TMaskEdit
          Left = 108
          Top = 40
          Width = 26
          Height = 21
          EditMask = '!999;0;_'
          MaxLength = 3
          TabOrder = 0
          Text = '0'
        end
        object MaskEditAnzahlLesen: TMaskEdit
          Left = 108
          Top = 74
          Width = 27
          Height = 21
          EditMask = '!999;0;_'
          MaxLength = 3
          TabOrder = 1
          Text = '1'
          OnExit = MaskEditAnzahlLesenExit
        end
        object MaskEditDBLesen: TMaskEdit
          Left = 108
          Top = 10
          Width = 26
          Height = 21
          EditMask = '!999;0;_'
          MaxLength = 3
          TabOrder = 5
          Text = '1'
        end
      end
      object Panel2: TPanel
        Left = 361
        Top = 8
        Width = 177
        Height = 273
        BevelInner = bvLowered
        BevelOuter = bvLowered
        TabOrder = 1
        object Label5: TLabel
          Left = 34
          Top = 119
          Width = 60
          Height = 13
          Caption = 'Wert / value'
        end
        object Label19: TLabel
          Left = 41
          Top = 25
          Width = 51
          Height = 13
          Caption = 'DB Nr./No'
        end
        object Label2: TLabel
          Left = 9
          Top = 49
          Width = 89
          Height = 13
          Caption = 'AbWort/Start word'
        end
        object MaskEditWert: TMaskEdit
          Left = 33
          Top = 135
          Width = 117
          Height = 21
          MaxLength = 16
          TabOrder = 3
          Text = '0'
        end
        object ComboBoxDBSchreiben: TComboBox
          Left = 57
          Top = 81
          Width = 75
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 2
          Items.Strings = (
            'Dez'
            'Hex'
            'Bin')
        end
        object ButtonDBSchreiben: TButton
          Left = 41
          Top = 182
          Width = 104
          Height = 20
          Caption = 'Schreiben/write'
          Enabled = False
          TabOrder = 4
          OnClick = ButtonDBSchreibenClick
        end
        object MaskEditDBSchreiben: TMaskEdit
          Left = 105
          Top = 18
          Width = 26
          Height = 21
          EditMask = '!999;0;_'
          MaxLength = 3
          TabOrder = 0
          Text = '1'
          OnExit = MaskEditDBLesenExit
        end
        object MaskEditAbWortSchreiben: TMaskEdit
          Left = 105
          Top = 50
          Width = 27
          Height = 21
          EditMask = '!999;0;_'
          MaxLength = 3
          TabOrder = 1
          Text = '0'
          OnExit = MaskEditDBLesenExit
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Ein -Ausgang/input - output'
      object Panel3: TPanel
        Left = 7
        Top = 7
        Width = 146
        Height = 273
        BevelInner = bvLowered
        BevelOuter = bvLowered
        TabOrder = 0
        object Label8: TLabel
          Left = 11
          Top = 61
          Width = 128
          Height = 13
          Caption = 'Ausgangswort/output word'
        end
        object Label7: TLabel
          Left = 11
          Top = 106
          Width = 104
          Height = 13
          Caption = 'Wert Binär / value bin'
        end
        object ButtonAWLesen: TButton
          Left = 11
          Top = 168
          Width = 118
          Height = 21
          Caption = 'Lesen/read'
          Enabled = False
          TabOrder = 2
          OnClick = ButtonAWLesenClick
        end
        object MaskEditAWLesen: TMaskEdit
          Left = 11
          Top = 78
          Width = 35
          Height = 21
          EditMask = '!999;0;_'
          MaxLength = 3
          TabOrder = 0
          Text = '0'
          OnExit = MaskEditDBLesenExit
        end
        object MaskEditAWAusgabe: TMaskEdit
          Left = 11
          Top = 124
          Width = 117
          Height = 21
          MaxLength = 16
          ReadOnly = True
          TabOrder = 1
          Text = '0000000000000000'
        end
      end
      object Panel4: TPanel
        Left = 155
        Top = 7
        Width = 146
        Height = 273
        BevelInner = bvLowered
        BevelOuter = bvLowered
        TabOrder = 1
        OnExit = MaskEditDBLesenExit
        object Label10: TLabel
          Left = 11
          Top = 106
          Width = 101
          Height = 13
          Caption = 'Wert Binär /value bin'
        end
        object Label12: TLabel
          Left = 11
          Top = 61
          Width = 128
          Height = 13
          Caption = 'Ausgangswort/output word'
        end
        object MaskEditAWWert: TMaskEdit
          Left = 11
          Top = 124
          Width = 117
          Height = 21
          MaxLength = 16
          TabOrder = 1
          Text = '00000000000000000'
        end
        object ButtonAWSchreiben: TButton
          Left = 11
          Top = 169
          Width = 118
          Height = 20
          Caption = 'Schreiben/write'
          Enabled = False
          TabOrder = 2
          OnClick = ButtonAWSchreibenClick
        end
        object MaskEditAWSchreiben: TMaskEdit
          Left = 11
          Top = 78
          Width = 35
          Height = 21
          EditMask = '!999;0;_'
          MaxLength = 3
          TabOrder = 0
          Text = '0'
          OnExit = MaskEditDBLesenExit
        end
      end
      object Panel6: TPanel
        Left = 304
        Top = 7
        Width = 146
        Height = 273
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = 'Panel6'
        TabOrder = 2
        OnExit = MaskEditDBLesenExit
        object Label9: TLabel
          Left = 11
          Top = 106
          Width = 104
          Height = 13
          Caption = 'Wert Binär / value bin'
        end
        object Label11: TLabel
          Left = 11
          Top = 61
          Width = 118
          Height = 13
          Caption = 'Eingangswort/input word'
        end
        object MaskEditEWAusgabe: TMaskEdit
          Left = 11
          Top = 124
          Width = 117
          Height = 21
          MaxLength = 16
          ReadOnly = True
          TabOrder = 1
          Text = '000000000000000000'
        end
        object ButtonEWLesen: TButton
          Left = 11
          Top = 169
          Width = 118
          Height = 20
          Caption = 'Lesen/read'
          Enabled = False
          TabOrder = 2
          OnClick = ButtonEWLesenClick
        end
        object MaskEditEWLesen: TMaskEdit
          Left = 11
          Top = 78
          Width = 35
          Height = 21
          EditMask = '!999;0;_'
          MaxLength = 3
          TabOrder = 0
          Text = '0'
          OnExit = MaskEditDBLesenExit
        end
      end
    end
  end
  object ComboBoxCom: TComboBox
    Left = 9
    Top = 410
    Width = 64
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 5
    Items.Strings = (
      'COM1'
      'COM2'
      'COM3'
      'COM4')
  end
  object ComboBoxLocalMPIAdr: TComboBox
    Left = 81
    Top = 442
    Width = 64
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 6
    Items.Strings = (
      '0'
      '1'
      '2 '
      '3'
      '4'
      '5'
      '6'
      '7'
      '8'
      '9'
      '10'
      '11'
      '12'
      '13'
      '14'
      '15'
      '16'
      '17'
      '18'
      '19'
      '20'
      '21'
      '22'
      '23'
      '24'
      '25'
      '26'
      '27'
      '28'
      '29'
      '30'
      '31'
      '32'
      '33'
      '34'
      '35'
      '36'
      '37'
      '38'
      '39'
      '40'
      '41'
      '42'
      '43'
      '44'
      '45'
      '45'
      '47'
      '48'
      '49'
      '50'
      '51'
      '52'
      '53'
      '54'
      '55'
      '56'
      '57'
      '58'
      '59'
      '60'
      '61'
      '62')
  end
  object ComboBoxBaud: TComboBox
    Left = 81
    Top = 410
    Width = 64
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 7
    Items.Strings = (
      '19200'
      '38400'
      '57600'
      '9600')
  end
  object ComboBoxSPSTyp: TComboBox
    Left = 232
    Top = 410
    Width = 81
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 8
    Items.Strings = (
      'S7 300/400'
      'S7 200')
  end
  object ComboBoxSPSMPIAdr: TComboBox
    Left = 232
    Top = 442
    Width = 81
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 9
    Items.Strings = (
      '0'
      '1'
      '2 '
      '3'
      '4'
      '5'
      '6'
      '7'
      '8'
      '9'
      '10'
      '11'
      '12'
      '13'
      '14'
      '15'
      '16'
      '17'
      '18'
      '19'
      '20'
      '21'
      '22'
      '23'
      '24'
      '25'
      '26'
      '27'
      '28'
      '29'
      '30'
      '31'
      '32'
      '33'
      '34'
      '35'
      '36'
      '37'
      '38'
      '39'
      '40'
      '41'
      '42'
      '43'
      '44'
      '45'
      '45'
      '47'
      '48'
      '49'
      '50'
      '51'
      '52'
      '53'
      '54'
      '55'
      '56'
      '57'
      '58'
      '59'
      '60'
      '61'
      '62')
  end
  object ComboBoxMPIBaud: TComboBox
    Left = 81
    Top = 474
    Width = 64
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 10
    Items.Strings = (
      '187,5 kBit/s'
      '19,2 kBit/s'
      '1,5 MBit/2')
  end
end
