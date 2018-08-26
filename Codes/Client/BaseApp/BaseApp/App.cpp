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
#include "Rendering/ViewPerspective.h"
#include "Rendering/GeometryLoaderDX11.h"

#include "Objects/FirstPersonCamera.h"
#include "Objects/Actor.h"
#include "Objects/PointLight.h"

#include "Events\EvtKeyDown.h"

struct Vertex
{
    DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT4 Color;
};

FirstPersonCamera* g_Camera;

App::App() {
    EvtManager.AddEventListener(SYSTEM_KEYBOARD_KEYDOWN, this);
}

App::~App() {

}

bool App::ConfigureEngineComponents() {
    int width = 1280;
    int height = 960;

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

void App::Initialize() {

    // 场景和相机
    ViewPerspective* pCameraView = new ViewPerspective(*m_pRenderer11, m_RenderTarget, m_DepthTarget);
    g_Camera = new FirstPersonCamera();
    g_Camera->SetCameraView(pCameraView);
    g_Camera->SetEventManager(&EvtManager);
    g_Camera->SetProjectionParams(0.01f, 100.0f, m_pWindow->GetWidth() / m_pWindow->GetHeight(), DirectX::XM_PIDIV2);
    g_Camera->Spatial().SetTranslation(Vector3f(0.0f, 10.0f, -5.0f));

    m_pScene = new Scene();
    m_pScene->AddCamera(g_Camera);

    // ---------------------------------------------一些资源声明----------------------------------------------------
    // 纹理
    ResourcePtr pTexHex = m_pRenderer11->LoadTexture(std::wstring(L"Hex.png"));
    // 采样器
    D3D11_SAMPLER_DESC sampDesc;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.BorderColor[0] = sampDesc.BorderColor[1] = sampDesc.BorderColor[2] = sampDesc.BorderColor[3] = 0;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    sampDesc.Filter = D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT;
    sampDesc.MaxAnisotropy = 16;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    sampDesc.MinLOD = 0.0f;
    sampDesc.MipLODBias = 0.0f;
    int samplerState = m_pRenderer11->CreateSamplerState(&sampDesc);
    // -------------------------------------------------------------------------------------------------------------

    PointLight* pPointLight = new PointLight();
    Entity3D* pEntitySphere = pPointLight->GetBody();
    pEntitySphere->SetName(L"PointLight");
    Node3D* pSpereNode = pPointLight->GetNode();
    pSpereNode->Transform.Position() = Vector3f(0.0f, 5.0f, 0.0f);
    MaterialPtr pMtlSphere = MaterialGeneratorDX11::GenerateBaseMaterial(*m_pRenderer11);
    pEntitySphere->Visual.SetMaterial(pMtlSphere);
    GeometryPtr pGeoSphere = GeometryPtr(new GeometryDX11());
    GeometryGeneratorDX11::GenerateSphere(pGeoSphere, 16, 9, 0.2f);
    pGeoSphere->LoadToBuffers();
    pEntitySphere->Visual.SetGeometry(pGeoSphere);
    m_pScene->AddLight(pPointLight);

    // 默认画一个轴
    Actor* pActorAxis = new Actor();
    pActorAxis->GetNode()->Transform.Scale() = Vector3f(10.0f, 10.0f, 10.0f);
    Entity3D* pEntityAxis = pActorAxis->GetBody();
    pEntityAxis->SetName(L"Axis");
    MaterialPtr pMtlAxis = MaterialGeneratorDX11::GenerateBaseColorMaterial(*m_pRenderer11);
    pEntityAxis->Visual.SetMaterial(pMtlAxis);
    GeometryPtr pGeoAxis = GeometryPtr(new GeometryDX11());
    GeometryGeneratorDX11::GenerateAxisGeometry(pGeoAxis);
    pGeoAxis->LoadToBuffers();
    pEntityAxis->Visual.SetGeometry(pGeoAxis);
    m_pScene->AddActor(pActorAxis);

    // 默认画一个平台
    Actor* pActorScene = new Actor();
    pActorScene->GetNode()->Transform.Scale() = Vector3f(20.0f, 20.0f, 20.0f);
    Entity3D* pEntityScene = pActorScene->GetBody();
    pEntityScene->SetName(L"Sample_Scene");
    MaterialPtr pMtlScene = MaterialGeneratorDX11::GeneratePhongMaterial(*m_pRenderer11);
    pMtlScene->Parameters.SetShaderResourceParameter(L"ModelTexture", pTexHex);
    pMtlScene->Parameters.SetSamplerParameter(L"ModelSampler", samplerState);
    pEntityScene->Visual.SetMaterial(pMtlScene);
    GeometryPtr pGeoScene = GeometryLoaderDX11::loadMS3DFile2(L"Plane.ms3d");
    pGeoScene->LoadToBuffers();
    pEntityScene->Visual.SetGeometry(pGeoScene);
    m_pScene->AddActor(pActorScene);

    for (size_t i = 0; i < 10; i++)
    {
        Actor* pActorSphere = new Actor();
        pActorSphere->GetNode()->Transform.Position() = Vector3f(i % 2 * 4.0f, 0.0f, i / 2 * 4.0f);
        Entity3D* pEntitySphere = pActorSphere->GetBody();
        pEntitySphere->SetName(L"Sphere");
        MaterialPtr pMtlScene = MaterialGeneratorDX11::GeneratePhongMaterial(*m_pRenderer11);
        pMtlScene->Parameters.SetShaderResourceParameter(L"ModelTexture", pTexHex);
        pMtlScene->Parameters.SetSamplerParameter(L"ModelSampler", samplerState);
        pEntitySphere->Visual.SetMaterial(pMtlScene);
        GeometryPtr pGeoSphere = GeometryLoaderDX11::loadMS3DFile2(L"Sphere.ms3d");
        pGeoSphere->LoadToBuffers();
        pGeoSphere->ComputeTangentFrame();
        pEntitySphere->Visual.SetGeometry(pGeoSphere);
        m_pScene->AddActor(pActorSphere);
    }
}

void App::Update() {
    m_pTimer->Update();

    float duration = m_pTimer->Elapsed();

    g_Camera->Spatial().GetEntity()->Update(duration);
    EvtManager.ProcessEvent(EvtFrameStartPtr(new EvtFrameStart(duration)));

    m_pRenderer11->pImmPipeline->ClearBuffers(Vector4f(0.0f, 0.0f, 0.0f, 0.0f), 1.0f);
    m_ViewMatrix = g_Camera->ViewMatrix();
    m_pRenderer11->m_pParamMgr->SetViewMatrixParameter(&m_ViewMatrix);

    m_pScene->Update(duration);
    m_pScene->Render(m_pRenderer11);

    // 交换 swapchain 展示结果
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
    eEVENT e = pEvent->GetEventType();
    if (e == SYSTEM_KEYBOARD_KEYDOWN)
    {
        Light* pLight = m_pScene->GetLight(0);

        EvtKeyDownPtr pKeyDown = std::static_pointer_cast<EvtKeyDown>(pEvent);
        UINT key = pKeyDown->GetCharacterCode();
        if (key == 37)
        {
            pLight->GetNode()->Transform.Position().x -= 0.5f;
        }
        else if (key == 38)
        {
            pLight->GetNode()->Transform.Position().z += 0.5f;
        }
        else if (key == 39)
        {
            pLight->GetNode()->Transform.Position().x += 0.5f;
        }
        else if (key == 40)
        {
            pLight->GetNode()->Transform.Position().z -= 0.5f;
        }
        else if (key == 49)
        {
            pLight->GetNode()->Transform.Position().y += 0.5f;
        }
        else if (key == 50)
        {
            pLight->GetNode()->Transform.Position().y -= 0.5f;
        }
    }

    return(Application::HandleEvent(pEvent));
}