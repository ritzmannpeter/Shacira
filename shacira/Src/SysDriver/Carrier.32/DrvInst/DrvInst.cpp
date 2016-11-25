//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("DrvInst.res");
USEFORM("DrvInstFormImpl.cpp", DrvInst);
USEUNIT("..\Interface\CarItf.c");
USEUNIT("cWinSystem.cpp");
USEUNIT("..\Driver\Carrier.c");
USEUNIT("..\Driver\CarSim.c");
USEUNIT("cWinRegistry.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TDrvInst), &DrvInst);
       Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
