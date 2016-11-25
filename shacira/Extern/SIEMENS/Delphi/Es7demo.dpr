program ES7DEMO;

uses
  Forms,
  main in 'main.pas' {InternetDemo},
  PCS7EASY in 'PCS7EASY.PAS';

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'PC-S7-LINK (Easy) Demo < -- > S7';
  Application.CreateForm(TInternetDemo, InternetDemo);
  Application.Run;
end.
