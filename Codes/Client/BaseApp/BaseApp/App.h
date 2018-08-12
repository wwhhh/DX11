#include "Application\Win32RenderWindow.h"
#include "Application\Application.h"
#include "Rendering\RendererDX11.h"
#include "Rendering\RenderEffectDX11.h"
#include "Maths\Matrix4f.h"

class App : public Application
{
public:
    App();
    ~App();

    virtual bool ConfigureEngineComponents();
    virtual void ShutdownEngineComponents();
    virtual void Initialize();
    virtual void Update();
    virtual void Shutdown();

    virtual std::wstring GetName();
    virtual bool HandleEvent(EventPtr pEvent);

protected:

    RendererDX11*           m_pRenderer11;
    Win32RenderWindow*		m_pWindow;

    ResourcePtr				m_Texture;

    int						m_iSwapChain;
    ResourcePtr				m_RenderTarget;
    ResourcePtr				m_DepthTarget;

    ResourcePtr             m_pVertexBuffer;
    int                     m_VertexLayout;
    ResourcePtr             m_pIndexBuffer;
    RenderEffectDX11		m_Effect;

    Matrix4f m_WorldMatrix;
    Matrix4f m_ViewMatrix;
    Matrix4f m_ProjMatrix;
};