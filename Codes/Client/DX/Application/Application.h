#pragma once

#include "PCH.h"
#include "Utils/Log.h"
#include "Utils/Timer.h"
#include "IWindowProc.h"
#include "Events/IEventListener.h"
#include "Events/EventManager.h"

class Application : public IWindowProc, public IEventListener
{
public:
    Application();
    virtual ~Application();

    // Initialization functions
    static Application* GetApplication();

    virtual void MessageLoop();
    virtual LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
    virtual void BeforeRegisterWindowClass(WNDCLASSEX &wc);

    // Overloadable functions for end user
    virtual bool ConfigureCommandLine(LPSTR lpcmdline);
    virtual bool ConfigureEngineComponents() = 0;
    virtual void ShutdownEngineComponents() = 0;
    virtual void Initialize() = 0;
    virtual void Update() = 0;
    virtual void Shutdown() = 0;

    virtual bool HandleEvent(EventPtr pEvent);

    // Helpers
    Utils::Timer* m_pTimer;

    // Engine Components
    EventManager EvtManager;

    bool m_bLoop;

protected:
    // Application pointer to ensure single instance
    static Application* ms_pApplication;
};