#include "PCH.h"
#include "Application.h"

class RenderApplication
{
public:
    RenderApplication();
    virtual ~RenderApplication();

public:
    virtual bool ConfigureRenderingEngineComponents(UINT width, UINT height, D3D_FEATURE_LEVEL desiredLevel, D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE);
    virtual bool ConfigureRenderingSetup();

    virtual void ShutdownRenderingEngineComponents();
    virtual void ShutdownRenderingSetup();

    virtual void HandleWindowResize(HWND handle, UINT width, UINT height);
    virtual bool HandleEvent(EventPtr pEvent);

protected:
    UINT					m_iWidth;
    UINT					m_iHeight;
};