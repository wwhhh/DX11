#include "PCH.h"
#include "App.h"

int WINAPI WinMain(HINSTANCE h_Inst, HINSTANCE h_PrevInst, LPSTR lpcmdline, int ncmdshow)
{
    Application* pApp = (Application*)new App();
    if (!pApp)
    {
        return -1;
    }

    if (!pApp->ConfigureCommandLine(lpcmdline))
    {
        Log::Get().Write(L"Failed to process the command line arguments!");
        return(-1);
    }

    if (!pApp->ConfigureEngineComponents())
    {
        pApp->ShutdownEngineComponents();
        return(false);
    }


    pApp->Initialize();
    pApp->MessageLoop();
    pApp->Shutdown();
    pApp->ShutdownEngineComponents();

    return(true);
}