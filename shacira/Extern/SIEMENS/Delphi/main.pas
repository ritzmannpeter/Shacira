unit main;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Mask, StdCtrls, ComCtrls, ExtCtrls, PCS7EASY;

const
   SRC_COUNT = 511;

type
  TInternetDemo = class(TForm)
    ButtonInit: TButton;
    ButtonExit: TButton;
    EditStatus: TEdit;
    Panel7: TPanel;
    Logo: TImage;
    PageControl1: TPageControl;
    TabSheet3: TTabSheet;
    Panel1: TPanel;
    Label1: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    ButtonDBLesen: TButton;
    Memo2: TMemo;
    ComboBoxDBLesen: TComboBox;
    MaskEditAbWortLesen: TMaskEdit;
    MaskEditAnzahlLesen: TMaskEdit;
    MaskEditDBLesen: TMaskEdit;
    Panel2: TPanel;
    Label5: TLabel;
    MaskEditWert: TMaskEdit;
    ComboBoxDBSchreiben: TComboBox;
    ButtonDBSchreiben: TButton;
    MaskEditDBSchreiben: TMaskEdit;
    MaskEditAbWortSchreiben: TMaskEdit;
    TabSheet4: TTabSheet;
    Panel3: TPanel;
    Label8: TLabel;
    Label7: TLabel;
    ButtonAWLesen: TButton;
    MaskEditAWLesen: TMaskEdit;
    MaskEditAWAusgabe: TMaskEdit;
    Panel4: TPanel;
    Label10: TLabel;
    Label12: TLabel;
    MaskEditAWWert: TMaskEdit;
    ButtonAWSchreiben: TButton;
    MaskEditAWSchreiben: TMaskEdit;
    Panel6: TPanel;
    Label9: TLabel;
    Label11: TLabel;
    MaskEditEWAusgabe: TMaskEdit;
    ButtonEWLesen: TButton;
    MaskEditEWLesen: TMaskEdit;
    Label13: TLabel;
    ComboBoxCom: TComboBox;
    ComboBoxLocalMPIAdr: TComboBox;
    ComboBoxBaud: TComboBox;
    ComboBoxSPSTyp: TComboBox;
    ComboBoxSPSMPIAdr: TComboBox;
    Label15: TLabel;
    Label16: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    Label2: TLabel;
    Label6: TLabel;
    ComboBoxMPIBaud: TComboBox;

    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure ButtonDBLesenClick(Sender: TObject);
    procedure MaskEditDBLesenExit(Sender: TObject);
    procedure MaskEditAnzahlLesenExit(Sender: TObject);
    procedure ButtonDBSchreibenClick(Sender: TObject);
    procedure ButtonAWLesenClick(Sender: TObject);
    procedure ButtonAWSchreibenClick(Sender: TObject);
    procedure ButtonEWLesenClick(Sender: TObject);
    procedure ButtonInitClick(Sender: TObject);
    procedure ButtonExitClick(Sender: TObject);
  private
    { Private-Deklarationen }
    procedure Hex1(var Zeichen: char);
    function  Hex(Wert : Word): String;
    function  SPSInit: Boolean;
    function  IsWord(sWord: string): Boolean;
    function  CheckMinMax(wWert, wMinWert, wMaxWert: word): Boolean;
    function  GetBinStr(wWert: word): string;
    function  FillUpLeft(sString: string; iAnzahl: integer; Zeichen: Char): string;
    function  BinStrToWord(sBinStr: string): word;
    function  HexStrToWord(sHexStr: string): word;
    procedure ShowErr;
    procedure ShowStatus (Msg : string);
    function  IsEven (W: WORD): Boolean;
    procedure EnableComboBoxes (bEn : Boolean);
    procedure SetWaitCursor;
    procedure SetNormalCursor;

  public
    { Public-Deklarationen }
    Buffer : array [0..SRC_COUNT] of WORD;
    Ref : LongInt;
    Fehler : LongInt;
    Com, SPSMPIAdr, LocalMPIAdr, Baud, SPSTyp : LongWord;
  end;

var
  InternetDemo: TInternetDemo;
implementation

{$R *.DFM}

procedure TInternetDemo.SetWaitCursor;
begin
  Screen.Cursor := crHourglass;    { Cursor als Sanduhr }
end;

procedure TInternetDemo.SetNormalCursor;
begin
  Screen.Cursor := crDefault;    { Cursor als normal }
end;
procedure TInternetDemo.EnableComboBoxes (bEn : Boolean);
begin
  ComboBoxCom.Enabled := bEn;
  ComboBoxSPSMPIAdr.Enabled := bEn;
  ComboBoxLocalMPIAdr.Enabled := bEn;
  ComboBoxBaud.Enabled := bEn;
  ComboBoxSPSTyp.Enabled := bEn;
  ComboBoxMPIBaud.Enabled := bEn;
end;

function TInternetDemo.SPSInit: Boolean;
begin
  EditStatus.Update;

  Com := ComboBoxCom.ItemIndex;
  SPSMPIAdr := ComboBoxSPSMPIAdr.ItemIndex;
  LocalMPIAdr := ComboBoxLocalMPIAdr.ItemIndex;
  Baud := 19200;
  case ComboBoxBaud.ItemIndex of
    0: Baud := 19200;
    1: Baud := 38400;
    2: Baud := 57600;
    3: Baud := 9600;

  end;
  SPSTyp := 300;
  case ComboBoxSPSTyp.ItemIndex of
    0: SPSTyp := 300;
    1: SPSTyp := 200;
  end;

  Ref :=  ES7OpenEx (Com, SPSMPIAdr, LocalMPIAdr, Baud, SPSTyp, ComboBoxMPIBaud.ItemIndex);
  if Ref < 0 then
  begin
    ShowMessage ('Achtung: Fehler bei "ES7Open"! / Error by "ES7Open"');
    Fehler := Ref;
    Result := False;
  end
  else
  begin
    Result := True;
  end;

  ButtonDBSchreiben.Enabled := Result;
  ButtonInit.Enabled := not Result;
  ButtonExit.Enabled := Result;

  ButtonDBLesen.Enabled := Result;
  ButtonDBSchreiben.Enabled := Result;
  ButtonAWLesen.Enabled := Result;
  ButtonAWSchreiben.Enabled := Result;
  ButtonEWLesen.Enabled := Result;
  EnableComboBoxes (not Result);


  ShowErr;
  Fehler := 0;

end;



procedure TInternetDemo.Hex1(var Zeichen: char);
var
   X : integer;
begin
   X := integer (Zeichen);
   if (X <= 9) then
   begin
     X := X + $30;
   end
   else
   begin
     X := X + $37;
   end;
   Zeichen := char (X);
end;

{ ------------------------------------------------------------------ }

function TInternetDemo.Hex(Wert : Word):String;
var
  i : integer;
  HexStr : String;
begin
  SetLength(HexStr,4);

  HexStr[4] := char  (Wert and $000F);
  HexStr[3] := char ((Wert shr 4 ) and $000F);
  HexStr[2] := char ((Wert shr 8 ) and $000F);
  HexStr[1] := char ((Wert shr 12) and $000F);

  for i := 1 to 4 do
    Hex1(HexStr[i]);
  Hex := HexStr;
end;

{ ------------------------------------------------------------------ }


procedure TInternetDemo.FormCreate(Sender: TObject);
begin
  ComboBoxDBSchreiben.ItemIndex := 0;
  ComboBoxDBLesen.ItemIndex := 0;
  ComboBoxCom.ItemIndex := 0;
  ComboBoxSPSMPIAdr.ItemIndex := 2;
  ComboBoxLocalMPIAdr.ItemIndex := 0;
  ComboBoxBaud.ItemIndex := 0;
  ComboBoxSPSTyp.ItemIndex := 0;
  ComboBoxMPIBaud.ItemIndex := 0;
  Ref := -1;

  Logo.Picture.LoadFromFile (ExtractFilePath(Application.EXEName) + 'OEM.BMP');
end;

procedure TInternetDemo.FormDestroy (Sender: TObject);
begin
 Fehler := ES7Close (Ref);
end;


{ ------------------------------------------------------------------ }

procedure TInternetDemo.ButtonDBLesenClick(Sender: TObject);
var
wDB,wAbWort,wAnzahl : WORD;
wX: WORD;
begin
  if IsWord(Trim(MaskEditDBLesen.Text)) and
     IsWord(Trim(MaskEditAbWortLesen.Text)) and
     IsWord(Trim(MaskEditAnzahlLesen.Text)) then
  begin
    wDB := StrToInt(Trim(MaskEditDBLesen.Text));
    wAbWort := StrToInt(Trim(MaskEditAbWortLesen.Text));
    wAnzahl := StrToInt(Trim(MaskEditAnzahlLesen.Text));
    if (IsEven (wAbWort) = False) then  exit;
    FillChar(Buffer, sizeof(Buffer), 0);
    ShowStatus (Format ('lese/reading DB %d ab/from DW %d, %d Worte/words', [wDB, wAbWort, wAnzahl]));
    SetWaitCursor;
    Fehler := ES7RdW (Ref, Longword ('D'),wDB,wAbWort div 2,wAnzahl,@Buffer);
    SetNormalCursor;
    if Fehler = 0 then
    begin
      Memo2.Clear;

      case ComboBoxDBLesen.ItemIndex of
        0: begin  {dezimal}
           for wX := 0 to wAnzahl - 1 do
             Memo2.Lines.Add(Format ('DW %3d: %6d (dez)', [wAbwort+wX,Buffer[wX]]));
        end;
        1: begin   {hexadezimal}
           for wX := 0 to wAnzahl - 1 do
             Memo2.Lines.Add(Format ('DW %3d: %4x (hex)', [wAbwort+wX,Buffer[wX]]));
        end;
        2: begin   {binär}
           for wX := 0 to wAnzahl - 1 do
             Memo2.Lines.Add(Format ('DW %3d: %s (bin)', [wAbwort+wX,GetBinStr(Buffer[wX])]));
        end;
      end;
    end
  end;
  ShowErr;
end;

{ ------------------------------------------------------------------ }

function TInternetDemo.IsWord(sWord: string): Boolean;
var
bOk: Boolean;
begin
  bOk := False;
  if sWord = '' then
  sWord := '0';
  try
    try
      StrToInt(sWord);
      bOk := True;
    except on Error:Exception do
    end;
  finally
    Result := bOk;
  end;
end;

{ ------------------------------------------------------------------ }

procedure TInternetDemo.MaskEditDBLesenExit(Sender: TObject);

(*var
wWord: WORD;
sw : String;
*)
begin
(*
  sw :=TMaskEdit(Sender).Text;
  if IsWord(Trim(TMaskEdit(Sender).Text)) then
  begin
    if TMaskEdit(Sender).Text = '' then
      TMaskEdit(Sender).Text := '0';
    wWord := StrToInt(Trim(TMaskEdit(Sender).Text));
    TMaskEdit(Sender).Text := FillUpLeft(Trim(TMaskEdit(Sender).Text),3,'0');
    if not CheckMinMax(wWord,0,256) then
      TMaskEdit(Sender).SetFocus;
  end;
  *)
end;

{ ------------------------------------------------------------------ }

function TInternetDemo.CheckMinMax(wWert, wMinWert, wMaxWert: Word): Boolean;
begin
  Result := False;
  if (wWert >= wMinWert) and (wWert <= wMaxWert) then
    Result := True
  else
    ShowMessage('Nur Werte zwischen '+
                 IntToStr(wMinWert)+' und '+
                 IntToStr(wMaxWert)+' zulässig!/allowed');
end;

{ ------------------------------------------------------------------ }

procedure TInternetDemo.MaskEditAnzahlLesenExit(Sender: TObject);
var
wWord: WORD;
begin
  if IsWord(Trim(TMaskEdit(Sender).Text)) then
  begin
    wWord := StrToInt(Trim(TMaskEdit(Sender).Text));
    TMaskEdit(Sender).Text := FillUpLeft(Trim(TMaskEdit(Sender).Text),3,'0');
    if not CheckMinMax(wWord,1,256) then
      TMaskEdit(Sender).SetFocus;
  end;

end;

{ ------------------------------------------------------------------ }

function TInternetDemo.GetBinStr(wWert: word): string;
var
sResult: string;
iRest, iWert: integer;
begin
  Result := '';
  iWert := wWert;
  While iWert > 0 do
  begin
    iRest := iWert mod 2;
    sResult := IntToStr(iRest) + sResult;
    iWert := Trunc(iWert / 2);
  end;

  Result := FillUpLeft(sResult,16,'0');
end;

{ ------------------------------------------------------------------ }

function TInternetDemo.FillUpLeft(sString: string; iAnzahl: integer; 
   Zeichen: Char): string;
var
i: integer;
sResult: string;
begin
  Result := sString;
  sResult := sString;
  for i := 1 to iAnzahl do
  begin
    if Length(sResult) < iAnzahl then
    begin
      sResult := Zeichen + sResult;
    end
    else
      Break;
  end;
  Result := sResult;
end;

{ ------------------------------------------------------------------ }

procedure TInternetDemo.ButtonDBSchreibenClick(Sender: TObject);
var
sWert: string;
wWert, wDB, wAbWort: WORD;
begin
  if IsWord(Trim(MaskEditDBSchreiben.Text)) and
     IsWord(Trim(MaskEditAbWortSchreiben.Text)) then
  begin
    wDB := StrToInt(Trim(MaskEditDBSchreiben.Text));
    wAbWort := StrToInt(Trim(MaskEditAbWortSchreiben.Text));
    if (IsEven (wAbWort) = False) then  exit;
    sWert := MaskEditWert.Text;
    wWert := 0;
    case ComboBoxDBSchreiben.ItemIndex of
      0: begin
         if IsWord(Trim(sWert)) then
           wWert := StrToInt(Trim(sWert));
      end;
      1: wWert := HexStrToWord(Trim(sWert));

      2: wWert := BinStrToWord(Trim(sWert));
    end;
    FillChar(Buffer, sizeof(Buffer), 0);
    Buffer[0] := wWert;

    ShowStatus (Format ('schreibe/writting DB %d ab/from DW %d, 1 Wort/word', [wDB, wAbWort]));
    SetWaitCursor;
    Fehler := ES7WrW(Ref,Longword ('D'), wDB,wAbWort div 2,1,@Buffer);
    SetNormalCursor;
    ShowErr;
  end;
end;

{ ------------------------------------------------------------------ }

function TInternetDemo.BinStrToWord(sBinStr: string): word;
var
iWert, iX, iLaenge: integer;
wResult: word;
begin
  iWert := 1;
  wResult := 0;
  iLaenge := Length(sBinStr);
  for iX := iLaenge downto 1 do
  begin
    if sBinStr[iX] = '1' then
      wResult := wResult + iWert;

    iWert := iWert * 2;
  end;

  Result := wResult;
end;

{ ------------------------------------------------------------------ }

function TInternetDemo.HexStrToWord(sHexStr: string): word;
var
iWert, iX, iLaenge: integer;
wResult: word;
cHexChar: Char;
begin
  iWert := 1;
  wResult := 0;
  SetLength(sHexStr,4);
  sHexStr := UpperCase(sHexStr);
  iLaenge := Length(sHexStr);
  for iX := iLaenge downto 1 do
  begin
    cHexChar := sHexStr[iX];
    case cHexChar of
      '0'..'9': wResult := wResult + (iWert * StrToInt(sHexStr[iX]));
      'A': wResult := wResult + (iWert * 10);
      'B': wResult := wResult + (iWert * 11);
      'C': wResult := wResult + (iWert * 12);
      'D': wResult := wResult + (iWert * 13);
      'E': wResult := wResult + (iWert * 14);
      'F': wResult := wResult + (iWert * 15);
    end;
    iWert := iWert * 16;
  end;

  Result := wResult;
end;

{ ------------------------------------------------------------------ }

procedure TInternetDemo.ButtonAWLesenClick(Sender: TObject);
var
wAW: WORD;
begin
  MaskEditAWAusgabe.Text := '';
  if IsWord(Trim(MaskEditAWLesen.Text)) then
  begin
    wAW := StrToInt(Trim(MaskEditAWLesen.Text));
    if (wAW mod 2 <> 0) then
    begin
      ShowMessage ('Es sind nur gerade Wortangaben möglich!');
      exit
    end;
    if IsEven (wAW) then
    begin
      FillChar(Buffer, sizeof(Buffer), 0);
      ShowStatus (Format ('lese AW %d', [wAW]));
      SetWaitCursor;
      Fehler := ES7RdW (Ref, Longword ('A'), 0, wAW div 2,1, @Buffer);
      SetNormalCursor;
      if Fehler = 0 then
        MaskEditAWAusgabe.Text := GetBinStr(Buffer[0]);
      ShowErr;
    end;
  end;
end;

{ ------------------------------------------------------------------ }

procedure TInternetDemo.ButtonAWSchreibenClick(Sender: TObject);
var
sWert: string;
wWert, wAW: WORD;
begin
  if IsWord(Trim(MaskEditAWSchreiben.Text)) then
  begin
    wAW := StrToInt(Trim(MaskEditAWSchreiben.Text));
    sWert := MaskEditAWWert.Text;
    wWert := BinStrToWord(Trim(sWert));
    if IsEven (wAW) then
    begin
      FillChar(Buffer, sizeof(Buffer), 0);
      Buffer[0] := wWert;
      ShowStatus (Format ('schreibe AW %d', [wAW]));
      SetWaitCursor;
      ES7WrW (Ref, LongWord ('A'), 0, wAW div 2,1,@Buffer);
      SetNormalCursor;
      ShowErr;
    end;
  end;

end;

{ ------------------------------------------------------------------ }

procedure TInternetDemo.ButtonEWLesenClick(Sender: TObject);
var
wEW: WORD;
begin
  MaskEditEWAusgabe.Text := '';
  if IsWord(Trim(MaskEditEWLesen.Text)) then
  begin
    wEW := StrToInt(Trim(MaskEditEWLesen.Text));
    if IsEven (wEW) then
    begin
      FillChar(Buffer, sizeof(Buffer), 0);
      ShowStatus (Format ('lese EW %d', [wEW]));
      SetWaitCursor;
      Fehler := ES7RdW(Ref,Longword ('E'), 0, wEW div 2,1,@Buffer);
      SetNormalCursor;
      if Fehler = 0 then
        MaskEditEWAusgabe.Text := GetBinStr(Buffer[0]);
      ShowErr
    end;
  end;
end;

{ ------------------------------------------------------------------ }

procedure TInternetDemo.ButtonInitClick(Sender: TObject);
begin
SPSInit;
end;

procedure TInternetDemo.ButtonExitClick(Sender: TObject);
begin
  ES7Close (Ref);
  ButtonDBSchreiben.Enabled := False;
  ButtonInit.Enabled := True;
  ButtonExit.Enabled := False;

  ButtonDBLesen.Enabled     := False;
  ButtonDBSchreiben.Enabled := False;
  ButtonAWLesen.Enabled     := False;
  ButtonAWSchreiben.Enabled := False;
  ButtonEWLesen.Enabled     := False;

  EnableComboBoxes (True);
  ShowErr;

end;

procedure TInternetDemo.ShowErr;
var
Msg : string;
begin
  if Fehler = 0 then
    Msg := 'Aktion erfolgreich / action OK'
  else
    Msg := 'Fehler:/error:';

  if Fehler = -1 then
    Msg := 'Zeitüberlauf / timeout';

  if Fehler  = 2  then
    Msg := 'Datenbereich in der SPS nicht vorhanden / data area in PLC not available';

  if Fehler  = 4660  then
    Msg := 'Demozeit abgelaufen! / demo time is over';
  if Fehler  = -4  then
    Msg := 'COM belegt oder nicht vorhanden! / Com not available';
  Msg := Msg + Format(' %d ', [Fehler]);
  ShowStatus (Msg);
end;


procedure TInternetDemo.ShowStatus (Msg : string);
begin
  EditStatus.Text := Msg;
  EditStatus.Update;
end;

function  TInternetDemo.IsEven (W: WORD): Boolean;
begin
  if W mod 2 = 0 then
     Result := True
  else
  begin
    ShowMessage ('Es sind nur gerade Werte zulässig (0,2,4,...) / only even values allowed');
    Result := False
  end;
end;
end.
