#include "App.h"
#include <DirectXMath.h>

#include "Events/EvtFrameStart.h"

#include "Rendering/PipelineManagerDX11.h"
#include "Rendering/IParameterManager.h"

#include "Rendering/BlendStateConfigDX11.h"
#include "Rendering/BufferConfigDX11.h"
#include "Rendering/DepthStencilStateConfigDX11.h"
#include "Rendering/RasterizerStateConfigDX11.h"
#include "Rendering/SwapChainConfigDX11.h"
#include "Rendering/Texture2dConfigDX11.h"
#include "Rendering/MaterialGeneratorDX11.h"
#include "Rendering/GeometryGeneratorDX11.h"

#include "Objects/FirstPersonCamera.h"
#include "Objects/Actor.h"

struct Vertex
{
    DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT4 Color;
};

FirstPersonCamera* g_Camera;

App::App() {

}

App::~App() {

}

bool App::ConfigureEngineComponents() {
    // The application currently supplies the 
    int width = 640;
    int height = 480;

    std::wstring name = L"BaseApp";

    // Set the render window parameters and initialize the window
    m_pWindow = new Win32RenderWindow();
    m_pWindow->SetPosition(25, 25);
    m_pWindow->SetSize(width, height);
    m_pWindow->SetCaption(name);
    m_pWindow->Initialize(this);

    m_pRenderer11 = new RendererDX11();

    if (!m_pRenderer11->Initialize(D3D_DRIVER_TYPE_HARDWARE, D3D_FEATURE_LEVEL_11_0))
    {
        Log::Get().Write(L"Could not create hardware device, trying to create the reference device...");

        if (!m_pRenderer11->Initialize(D3D_DRIVER_TYPE_REFERENCE, D3D_FEATURE_LEVEL_11_0))
        {
            ShowWindow(m_pWindow->GetHandle(), SW_HIDE);
            MessageBox(m_pWindow->GetHandle(), L"Could not create a hardware or software Direct3D 11 device - the program will now abort!", L"Hieroglyph 3 Rendering", MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
            return(false);
        }

        // If using the reference device, utilize a fixed time step for any animations.
        m_pTimer->SetFixedTimeStep(1.0f / 10.0f);
    }

    // Create a swap chain for the window that we started out with.  This
    // demonstrates using a configuration object for fast and concise object
    // creation.

    SwapChainConfigDX11 Config;
    Config.SetWidth(m_pWindow->GetWidth());
    Config.SetHeight(m_pWindow->GetHeight());
    Config.SetOutputWindow(m_pWindow->GetHandle());
    m_iSwapChain = m_pRenderer11->CreateSwapChain(&Config);
    m_pWindow->SetSwapChain(m_iSwapChain);

    // We'll keep a copy of the render target index to use in later examples.

    m_RenderTarget = m_pRenderer11->GetSwapChainResource(m_iSwapChain);

    // Next we create a depth buffer for use in the traditional rendering
    // pipeline.

    Texture2dConfigDX11 DepthConfig;
    DepthConfig.SetDepthBuffer(width, height);
    m_DepthTarget = m_pRenderer11->CreateTexture2D(&DepthConfig, 0);

    // Bind the swap chain render target and the depth buffer for use in 
    // rendering.  

    m_pRenderer11->pImmPipeline->ClearRenderTargets();
    m_pRenderer11->pImmPipeline->OutputMergerStage.DesiredState.RenderTargetViews.SetState(0, m_RenderTarget->m_iResourceRTV);
    m_pRenderer11->pImmPipeline->OutputMergerStage.DesiredState.DepthTargetViews.SetState(m_DepthTarget->m_iResourceDSV);
    m_pRenderer11->pImmPipeline->ApplyRenderTargets();

    // Create a view port to use on the scene.  This basically selects the 
    // entire floating point area of the render target.

    D3D11_VIEWPORT viewport;
    viewport.Width = static_cast< float >(width);
    viewport.Height = static_cast< float >(height);
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 0.999f;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;

    int ViewPort = m_pRenderer11->CreateViewPort(viewport);
    m_pRenderer11->pImmPipeline->RasterizerStage.DesiredState.ViewportCount.SetState(1);
    m_pRenderer11->pImmPipeline->RasterizerStage.DesiredState.Viewports.SetState(0, ViewPort);
}

void App::ShutdownEngineComponents() {
    if (m_pRenderer11)
    {
        m_pRenderer11->Shutdown();
        delete m_pRenderer11;
    }

    if (m_pWindow)
    {
        m_pWindow->Shutdown();
        delete m_pWindow;
    }
}
Actor* pActorSpere;
void App::Initialize() {
    g_Camera = new FirstPersonCamera();
    g_Camera->SetEventManager(&EvtManager);
    g_Camera->SetProjectionParams(0.01f, 100.0f, m_pWindow->GetWidth() / m_pWindow->GetHeight(), DirectX::XM_PIDIV2);
    g_Camera->Spatial().SetTranslation(Vector3f(0.0f, 1.0f, -5.0f));

    m_ViewMatrix = g_Camera->ViewMatrix();
    m_ProjMatrix = g_Camera->ProjMatrix();

    m_pRenderer11->m_pParamMgr->SetViewMatrixParameter(&m_ViewMatrix);
    m_pRenderer11->m_pParamMgr->SetProjMatrixParameter(&m_ProjMatrix);

    pActorSpere = new Actor();
    Entity3D* pEntitySphere = pActorSpere->GetBody();
    Node3D* pSpereNode = pActorSpere->GetNode();
    pSpereNode->Transform.Position() = Vector3f(5.0f, 0.0f, 0.0f);
    MaterialPtr pMtlSphere = MaterialGeneratorDX11::GenerateBaseMaterial(*m_pRenderer11);
    pEntitySphere->Visual.SetMaterial(pMtlSphere);
    GeometryPtr pGeoSphere = GeometryPtr(new GeometryDX11());
    GeometryGeneratorDX11::GenerateSphere(pGeoSphere, 16, 9, 1.0f);
    pGeoSphere->LoadToBuffers();
    pEntitySphere->Visual.SetGeometry(pGeoSphere);

    m_pScene = new Scene();
    m_pScene->AddActor(pActorSpere);
    m_pScene->AddCamera(g_Camera);
}

void App::Update() {
    m_pTimer->Update();

    g_Camera->Spatial().GetEntity()->Update(m_pTimer->Elapsed());
    EvtManager.ProcessEvent(EvtFrameStartPtr(new EvtFrameStart(m_pTimer->Elapsed())));

    m_pRenderer11->pImmPipeline->ClearBuffers(Vector4f(0.0f, 0.0f, 0.0f, 0.0f), 1.0f);
    
    m_ViewMatrix = g_Camera->ViewMatrix();
    m_pRenderer11->m_pParamMgr->SetViewMatrixParameter(&m_ViewMatrix);

    m_pRenderer11->m_pParamMgr->SetWorldMatrixParameter(&pActorSpere->GetNode()->Transform.WorldMatrix());
    //pActorSpere->GetBody()->SetRenderParams(m_pRenderer11->m_pParamMgr);
    //pActorSpere->GetBody()->Render(m_pRenderer11->pImmPipeline, m_pRenderer11->m_pParamMgr, VIEWTYPE::VT_PERSPECTIVE);

    m_pScene->Render(m_pRenderer11);

    // Present the results
    m_pRenderer11->Present(m_pWindow->GetHandle(), m_pWindow->GetSwapChain());
}

void App::Shutdown() {
    std::wstringstream out;
    out << L"Max FPS: " << m_pTimer->MaxFramerate();

    std::wstring str = out.str();
    Log::Get().Write(str);
}

std::wstring App::GetName()
{
    return L"BaseApp";
}

bool App::HandleEvent(EventPtr pEvent)
{
    return(Application::HandleEvent(pEvent));
}