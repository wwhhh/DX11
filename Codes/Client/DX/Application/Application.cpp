#include "PCH.h"
#include "Application.h"

// Keyboard Events
#include "Events/EvtKeyUp.h"
#include "Events/EvtKeyDown.h"

// Mouse Events
#include "Events/EvtMouseWheel.h"
#include "Events/EvtMouseMove.h"
#include "Events/EvtMouseLeave.h"
#include "Events/EvtMouseLButtonUp.h"
#include "Events/EvtMouseLButtonDown.h"
#include "Events/EvtMouseMButtonUp.h"
#include "Events/EvtMouseMButtonDown.h"
#include "Events/EvtMouseRButtonUp.h"
#include "Events/EvtMouseRButtonDown.h"

Application* Application::ms_pApplication = NULL;

Application::Application() :
    m_bLoop(true)
{
    ms_pApplication = this;

    SetEventManager(&EvtManager);

    m_pTimer = new Utils::Timer();
    m_pTimer->Update();

    Utils::Log::Get().Open();
}

Application::~Application()
{
    if (m_pTimer != NULL)
        delete m_pTimer;

    Utils::Log::Get().Close();
}

Application* Application::GetApplication()
{
    return ms_pApplication;
}

bool Application::HandleEvent(EventPtr pEvent)
{
    return(false);
}

void Application::MessageLoop()
{
    MSG msg;

    while (true)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                return;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        Update();
    }
}

LRESULT Application::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {

    case WM_CREATE:
    {

        return(0);
    } break;

    case WM_PAINT:
    {

    } break;

    case WM_CLOSE:
    {

    } break;

    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return(0);
    } break;
    case WM_LBUTTONUP:
    {
        EvtMouseLButtonUpPtr pEvent = EvtMouseLButtonUpPtr(new EvtMouseLButtonUp(hwnd, wparam, lparam));
        EvtManager.ProcessEvent(pEvent);
    } break;

    case WM_LBUTTONDOWN:
    {
        EvtMouseLButtonDownPtr pEvent = EvtMouseLButtonDownPtr(new EvtMouseLButtonDown(hwnd, wparam, lparam));
        EvtManager.ProcessEvent(pEvent);
    } break;

    case WM_MBUTTONUP:
    {
        EvtMouseMButtonUpPtr pEvent = EvtMouseMButtonUpPtr(new EvtMouseMButtonUp(hwnd, wparam, lparam));
        EvtManager.ProcessEvent(pEvent);
    } break;

    case WM_MBUTTONDOWN:
    {
        EvtMouseMButtonDownPtr pEvent = EvtMouseMButtonDownPtr(new EvtMouseMButtonDown(hwnd, wparam, lparam));
        EvtManager.ProcessEvent(pEvent);
    } break;

    case WM_RBUTTONUP:
    {
        EvtMouseRButtonUpPtr pEvent = EvtMouseRButtonUpPtr(new EvtMouseRButtonUp(hwnd, wparam, lparam));
        EvtManager.ProcessEvent(pEvent);
    } break;

    case WM_RBUTTONDOWN:
    {
        EvtMouseRButtonDownPtr pEvent = EvtMouseRButtonDownPtr(new EvtMouseRButtonDown(hwnd, wparam, lparam));
        EvtManager.ProcessEvent(pEvent);
    } break;

    case WM_MOUSEMOVE:
    {
        EvtMouseMovePtr pEvent = EvtMouseMovePtr(new EvtMouseMove(hwnd, wparam, lparam));
        EvtManager.ProcessEvent(pEvent);
    } break;

    case WM_MOUSEWHEEL:
    {
        EvtMouseWheelPtr pEvent = EvtMouseWheelPtr(new EvtMouseWheel(hwnd, wparam, lparam));
        EvtManager.ProcessEvent(pEvent);
    } break;

    case WM_KEYDOWN:
    {
        EvtKeyDownPtr pEvent = EvtKeyDownPtr(new EvtKeyDown(hwnd, wparam, lparam));
        EvtManager.ProcessEvent(pEvent);
    } break;

    case WM_KEYUP:
    {
        EvtKeyUpPtr pEvent = EvtKeyUpPtr(new EvtKeyUp(hwnd, wparam, lparam));
        EvtManager.ProcessEvent(pEvent);
    } break;

    }
    return(DefWindowProc(hwnd, msg, wparam, lparam));
}

bool Application::ConfigureCommandLine(LPSTR lpcmdline)
{
    return(true);
}

void Application::BeforeRegisterWindowClass(WNDCLASSEX &wc) 
{

}