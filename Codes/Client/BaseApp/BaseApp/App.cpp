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


#include "Objects/FirstPersonCamera.h"

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

    if (!m_pRenderer11->Initialize(D3D_DRIVER_TYPE_HARDWARE, D3D_FEATURE_LEVEL_10_0))
    {
        Log::Get().Write(L"Could not create hardware device, trying to create the reference device...");

        if (!m_pRenderer11->Initialize(D3D_DRIVER_TYPE_REFERENCE, D3D_FEATURE_LEVEL_10_0))
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

    m_Effect.SetVertexShader(m_pRenderer11->LoadShader(VERTEX_SHADER,
        std::wstring(L"RotatingCube.hlsl"),
        std::wstring(L"VSMain"),
        std::wstring(L"vs_4_0"),
        true));

    m_Effect.SetGeometryShader(m_pRenderer11->LoadShader(GEOMETRY_SHADER,
        std::wstring(L"RotatingCube.hlsl"),
        std::wstring(L"GSMain"),
        std::wstring(L"gs_4_0"),
        true));

    m_Effect.SetPixelShader(m_pRenderer11->LoadShader(PIXEL_SHADER,
        std::wstring(L"RotatingCube.hlsl"),
        std::wstring(L"PSMain"),
        std::wstring(L"ps_4_0"),
        true));

    m_pRenderer11->GetShader(m_Effect.GetVertexShader())->GetReflection()->PrintShaderDetails();

    DepthStencilStateConfigDX11 dsConfig;
    int iDepthStencilState = m_pRenderer11->CreateDepthStencilState(&dsConfig);
    if (iDepthStencilState == -1) {
        Log::Get().Write(L"Failed to create light depth stencil state");
        assert(false);
    }

    BlendStateConfigDX11 blendConfig;
    int iBlendState = m_pRenderer11->CreateBlendState(&blendConfig);
    if (iBlendState == -1) {
        Log::Get().Write(L"Failed to create light blend state");
        assert(false);
    }

    RasterizerStateConfigDX11 rsConfig;
    rsConfig.CullMode = D3D11_CULL_BACK;
    rsConfig.FillMode = D3D11_FILL_SOLID;
    int iRasterizerState = m_pRenderer11->CreateRasterizerState(&rsConfig);
    if (iRasterizerState == -1) {
        Log::Get().Write(L"Failed to create light rasterizer state");
        assert(false);
    }

    m_Effect.m_iBlendState = iBlendState;
    m_Effect.m_iDepthStencilState = iDepthStencilState;
    m_Effect.m_iRasterizerState = iRasterizerState;
    m_Effect.m_uStencilRef = iDepthStencilState;

    // create the vertex buffer layout descriptor (this is usually done by GeometryDX11)

    D3D11_INPUT_ELEMENT_DESC desc[] =
    {
        { "SV_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
    layout.push_back(desc[0]);
    layout.push_back(desc[1]);
    m_VertexLayout = m_pRenderer11->CreateInputLayout(layout, m_Effect.GetVertexShader());
    if (m_VertexLayout == -1) {
        Log::Get().Write(L"Failed to create vertex layout");
        assert(false);
    }

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
    // create the vertex buffer resource (this is usually done by GeometryDX11)
    {
        Vertex vertices[] =
        {
            { DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
        { DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
        { DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
        { DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
        { DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
        { DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
        { DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
        { DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
        };
        D3D11_SUBRESOURCE_DATA data;
        data.pSysMem = vertices;
        data.SysMemPitch = 0;
        data.SysMemSlicePitch = 0;

        BufferConfigDX11 vbConfig;
        vbConfig.SetDefaultVertexBuffer(8 * sizeof(Vertex), false);
        m_pVertexBuffer = m_pRenderer11->CreateVertexBuffer(&vbConfig, &data);
        if (m_pVertexBuffer->m_iResource == -1) {
            Log::Get().Write(L"Failed to create vertex buffer");
            assert(false);
        }
    }

    // create the index buffer resource (this is usually done by GeometryDX11)
    {
        UINT indices[] =
        {
            3,1,0,
            2,1,3,

            0,5,4,
            1,5,0,

            3,4,7,
            0,4,3,

            1,6,5,
            2,6,1,

            2,7,6,
            3,7,2,

            6,4,5,
            7,4,6,
        };
        D3D11_SUBRESOURCE_DATA data;
        data.pSysMem = indices;
        data.SysMemPitch = 0;
        data.SysMemSlicePitch = 0;

        BufferConfigDX11 vbConfig;
        vbConfig.SetDefaultIndexBuffer(sizeof(UINT) * 36, false);
        m_pIndexBuffer = m_pRenderer11->CreateIndexBuffer(&vbConfig, &data);
        if (m_pIndexBuffer->m_iResource == -1) {
            Log::Get().Write(L"Failed to create index buffer");
            assert(false);
        }
    }

    g_Camera = new FirstPersonCamera();
    g_Camera->SetEventManager(&EvtManager);
    g_Camera->SetProjectionParams(0.01f, 100.0f, m_pWindow->GetWidth() / m_pWindow->GetHeight(), DirectX::XM_PIDIV2);
    g_Camera->Spatial().SetTranslation(Vector3f(0.0f, 1.0f, -5.0f));

    m_WorldMatrix = Matrix4f::Identity();
    m_ViewMatrix = g_Camera->ViewMatrix();
    m_ProjMatrix = g_Camera->ProjMatrix();

    m_pRenderer11->m_pParamMgr->SetWorldMatrixParameter(&m_WorldMatrix);
    m_pRenderer11->m_pParamMgr->SetViewMatrixParameter(&m_ViewMatrix);
    m_pRenderer11->m_pParamMgr->SetProjMatrixParameter(&m_ProjMatrix);

    m_Texture = m_pRenderer11->LoadTexture(L"Outcrop.png");
    m_pRenderer11->m_pParamMgr->SetShaderResourceParameter(L"ColorMap00", m_Texture);
}

void App::Update() {
    m_pTimer->Update();

    g_Camera->Spatial().GetEntity()->Update(m_pTimer->Elapsed());
    EvtManager.ProcessEvent(EvtFrameStartPtr(new EvtFrameStart(m_pTimer->Elapsed())));

    m_pRenderer11->pImmPipeline->ClearBuffers(Vector4f(0.0f, 0.0f, 0.0f, 0.0f), 1.0f);

    // Update the object position in worldspace
    static DWORD dwTimeStart = 0;
    static float t = 0.0f;
    DWORD dwTimeCur = GetTickCount();
    if (dwTimeStart == 0)
        dwTimeStart = dwTimeCur;
    t = (dwTimeCur - dwTimeStart) / 1000.0f;

    m_WorldMatrix = Matrix4f::RotationMatrixY(t) * Matrix4f::RotationMatrixX(t);
    m_ViewMatrix = g_Camera->ViewMatrix();

    m_pRenderer11->m_pParamMgr->SetWorldMatrixParameter(&m_WorldMatrix);
    m_pRenderer11->m_pParamMgr->SetViewMatrixParameter(&m_ViewMatrix);

    // Perform the actual drawing

    UINT stride = sizeof(Vertex);
    m_pRenderer11->pImmPipeline->Draw(m_Effect, m_pVertexBuffer, m_pIndexBuffer, m_VertexLayout, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, stride, 36, m_pRenderer11->m_pParamMgr);

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