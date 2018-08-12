#include "PCH.h"
#include "RendererDX11.h"

#include "Utils/Log.h"

#include "VertexBufferDX11.h"
#include "IndexBufferDX11.h"
#include "ConstantBufferDX11.h"
#include "StructuredBufferDX11.h"
#include "ByteAddressBufferDX11.h"
#include "IndirectArgsBufferDX11.h"
#include "Texture1dDX11.h"
#include "Texture2dDX11.h"
#include "Texture3dDX11.h"
#include "ResourceDX11.h"
#include "SwapChainDX11.h"
#include "ViewPortDX11.h"

#include "BufferConfigDX11.h"
#include "Texture1dConfigDX11.h"
#include "Texture2dConfigDX11.h"
#include "Texture3dConfigDX11.h"
#include "SwapChainConfigDX11.h"

#include "ShaderResourceViewDX11.h"
#include "RenderTargetViewDX11.h"
#include "DepthStencilViewDX11.h"
#include "UnorderedAccessViewDX11.h"

#include "BlendStateConfigDX11.h"
#include "DepthStencilStateConfigDX11.h"
#include "RasterizerStateConfigDX11.h"

#include "VertexShaderDX11.h"
//#include "HullShaderDX11.h"
//#include "DomainShaderDX11.h"
#include "GeometryShaderDX11.h"
#include "PixelShaderDX11.h"
//#include "ComputeShaderDX11.h"
#include "ShaderFactoryDX11.h"
#include "ShaderReflectionDX11.h"
#include "ShaderReflectionFactoryDX11.h"

#include "VectorParameterDX11.h"
#include "MatrixParameterDX11.h"
#include "MatrixArrayParameterDX11.h"
#include "ShaderResourceParameterDX11.h"
#include "UnorderedAccessParameterDX11.h"
#include "ConstantBufferParameterDX11.h"
#include "SamplerParameterDX11.h"

#include "RenderEffectDX11.h"
//#include "GeometryDX11.h"
//#include "CommandListDX11.h"

#include "DXGIAdapter.h"
#include "DXGIOutput.h"

#include "ParameterManagerDX11.h"
#include "PipelineManagerDX11.h"

//#include "Task.h"

#include "Events/EventManager.h"
#include "Events/EvtErrorMessage.h"

#include "Utils/FileSystem.h"
#include "Process.h"

#include "Utils/D3DEnumConversion.h"

// Library imports
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "DXGI.lib" )
#pragma comment( lib, "DirectXTK.lib" )

#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"

using Microsoft::WRL::ComPtr;

RendererDX11* RendererDX11::m_spRenderer = 0;

RendererDX11::RendererDX11()
{
    if (m_spRenderer == 0)
        m_spRenderer = this;

    //	m_pDevice = 0;
    //	m_pDebugger = 0;
    m_driverType = D3D_DRIVER_TYPE_NULL;


    m_pParamMgr = 0;
    pImmPipeline = 0;

    m_FeatureLevel = D3D_FEATURE_LEVEL_9_1; // Initialize this to only support 9.1...
}

RendererDX11::~RendererDX11()
{
}

RendererDX11* RendererDX11::Get()
{
    return(m_spRenderer);
}

D3D_FEATURE_LEVEL RendererDX11::GetAvailableFeatureLevel(D3D_DRIVER_TYPE DriverType)
{
    D3D_FEATURE_LEVEL FeatureLevel;
    HRESULT hr;

    // If the device has already been created, simply return the feature level.
    // Otherwise perform a test with null inputs to get the returned feature level
    // without creating the device.  The application can then do whatever it needs
    // to for a given feature level.

    if (m_pDevice) {
        FeatureLevel = m_pDevice->GetFeatureLevel();
    }
    else {
        hr = D3D11CreateDevice(
            nullptr,
            DriverType,
            nullptr,
            0,
            nullptr,
            0,
            D3D11_SDK_VERSION,
            nullptr,
            &FeatureLevel,
            nullptr);

        if (FAILED(hr)) {
            Log::Get().Write(L"Failed to determine the available hardware feature level!");
        }

    }

    return(FeatureLevel);
}

D3D_FEATURE_LEVEL RendererDX11::GetCurrentFeatureLevel()
{
    return(m_FeatureLevel);
}

UINT64 RendererDX11::GetAvailableVideoMemory()
{
    // Acquire the DXGI device, then the adapter.
    // TODO: This method needs to be capable of checking on multiple adapters!

    ComPtr<IDXGIDevice> pDXGIDevice;
    ComPtr<IDXGIAdapter> pDXGIAdapter;

    HRESULT hr = m_pDevice.CopyTo(pDXGIDevice.GetAddressOf());
    pDXGIDevice->GetAdapter(pDXGIAdapter.GetAddressOf());

    // Use the adapter interface to get its description.  Then grab the available
    // video memory based on if there is dedicated or shared memory for the GPU.

    DXGI_ADAPTER_DESC AdapterDesc;
    pDXGIAdapter->GetDesc(&AdapterDesc);

    UINT64 availableVideoMem = 0;

    if (AdapterDesc.DedicatedVideoMemory)
        availableVideoMem = AdapterDesc.DedicatedVideoMemory;
    else
        availableVideoMem = AdapterDesc.SharedSystemMemory;

    return(availableVideoMem);
}

bool RendererDX11::Initialize(D3D_DRIVER_TYPE DriverType, D3D_FEATURE_LEVEL FeatureLevel)
{
    HRESULT hr = S_OK;

    ComPtr<IDXGIFactory1> pFactory;
    hr = CreateDXGIFactory1(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));

    ComPtr<IDXGIAdapter1> pCurrentAdapter;
    std::vector<ComPtr<IDXGIAdapter1>> vAdapters;

    while (pFactory->EnumAdapters1(static_cast<UINT>(vAdapters.size()), pCurrentAdapter.ReleaseAndGetAddressOf()) != DXGI_ERROR_NOT_FOUND)
    {
        vAdapters.push_back(pCurrentAdapter);

        DXGI_ADAPTER_DESC1 desc;
        pCurrentAdapter->GetDesc1(&desc);

        Utils::Log::Get().Write(desc.Description);
    }

    DeviceContextComPtr pContext;

    D3D_FEATURE_LEVEL level[] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_11_1,
    };

    D3D_FEATURE_LEVEL CreatedLevel;
    for (auto pAdapter : vAdapters)
    {
        hr = D3D11CreateDevice(
            0,
            DriverType,
            0,
            0,
            0,
            0,
            D3D11_SDK_VERSION,
            m_pDevice.GetAddressOf(),
            &CreatedLevel,
            pContext.GetAddressOf());

        if (hr == S_OK)
            break;
    }


    if (FAILED(hr))
        return false;

    // Get the debugger interface from the device.

    hr = m_pDevice.CopyTo(m_pDebugger.GetAddressOf());

    if (FAILED(hr))
    {
        Log::Get().Write(L"Unable to acquire the ID3D11Debug interface from the device!");
    }

    // Grab a copy of the feature level for use by the rest of the rendering system.

    m_FeatureLevel = m_pDevice->GetFeatureLevel();

    // Create the renderer components here, including the parameter manager, 
    // pipeline manager, and resource manager.

    m_pParamMgr = new ParameterManagerDX11(0);
    pImmPipeline = new PipelineManagerDX11();
    pImmPipeline->SetDeviceContext(pContext, m_FeatureLevel);

    // Rasterizer State (RS) - the first state will be index zero, so no need
    // to keep a copy of it here.

    RasterizerStateConfigDX11 RasterizerState;
    pImmPipeline->RasterizerStage.DesiredState.RasterizerState.SetState(CreateRasterizerState(&RasterizerState));

    // Depth Stencil State (DS) - the first state will be index zero, so no need
    // to keep a copy of it here.

    DepthStencilStateConfigDX11 DepthStencilState;
    pImmPipeline->OutputMergerStage.DesiredState.DepthStencilState.SetState(CreateDepthStencilState(&DepthStencilState));

    // Output Merger State (OM) - the first state will be index zero, so no need
    // to keep a copy of it here.

    BlendStateConfigDX11 BlendState;
    pImmPipeline->OutputMergerStage.DesiredState.BlendState.SetState(CreateBlendState(&BlendState));


    // Create the default resource views for each category.  This has the effect
    // of allowing the '0' index to be the default state.

    m_vShaderResourceViews.emplace_back(ShaderResourceViewComPtr());
    m_vUnorderedAccessViews.emplace_back(UnorderedAccessViewComPtr());
    m_vRenderTargetViews.emplace_back(RenderTargetViewComPtr());
    m_vDepthStencilViews.emplace_back(DepthStencilViewComPtr());


    // Create a query object to be used to gather statistics on the pipeline.

    D3D11_QUERY_DESC queryDesc;
    queryDesc.Query = D3D11_QUERY_PIPELINE_STATISTICS;
    queryDesc.MiscFlags = 0;

    for (int i = 0; i < PipelineManagerDX11::NumQueries; ++i)
    {
        hr = m_pDevice->CreateQuery(&queryDesc, &pImmPipeline->m_Queries[i]);

        if (FAILED(hr))
        {
            Log::Get().Write(L"Unable to create a query object!");
            Shutdown();
            return(false);
        }
    }

    D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS Options;
    m_pDevice->CheckFeatureSupport(D3D11_FEATURE_D3D10_X_HARDWARE_OPTIONS, &Options, sizeof(Options));
    if (Options.ComputeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x)
        Log::Get().Write(L"Device supports compute shaders plus raw and structured buffers via shader 4.x");


    D3D11_FEATURE_DATA_THREADING ThreadingOptions;
    m_pDevice->CheckFeatureSupport(D3D11_FEATURE_THREADING, &ThreadingOptions, sizeof(ThreadingOptions));

    // TODO: Enumerate all of the formats and quality levels available for the given format.
    //       It may be beneficial to allow this query from the user instead of enumerating
    //       all possible formats...
    UINT NumQuality;
    HRESULT hr1 = m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &NumQuality);

    return(true);
}

void RendererDX11::Shutdown()
{
    // Print some details about the renderer's status at shutdown.
    //LogObjectPtrVector<ShaderDX11*>(m_vShaders);

    // Shutdown all of the threads
    //for (int i = 0; i < NUM_THREADS; i++)
    //{
    //    g_aPayload[i].bComplete = true;
    //    g_aPayload[i].pTask = nullptr;

    //    SAFE_DELETE(g_aPayload[i].pParamManager);
    //    SAFE_DELETE(g_aPayload[i].pPipeline);
    //    SAFE_DELETE(g_aPayload[i].pList);

    //    CloseHandle(g_aThreadHandles[i]);
    //    CloseHandle(g_aBeginEventHandle[i]);
    //    CloseHandle(g_aEndEventHandle[i]);
    //}


    SAFE_DELETE(m_pParamMgr);
    SAFE_DELETE(pImmPipeline);

    // Since these are all managed with smart pointers, we just empty the
    // container and the objects will automatically be deleted.

    m_BlendStates.clear();
    m_DepthStencilStates.clear();
    m_RasterizerStates.clear();
    m_vSamplerStates.clear();
    m_vInputLayouts.clear();
    m_vViewPorts.clear();

    for (auto pShader : m_vShaders)
        delete pShader;

    m_vShaderResourceViews.clear();
    m_vRenderTargetViews.clear();
    m_vDepthStencilViews.clear();
    m_vUnorderedAccessViews.clear();

    for (auto pResource : m_vResources)
        delete pResource;

    for (auto pSwapChain : m_vSwapChains) {
        if (pSwapChain->m_pSwapChain != nullptr) {
            pSwapChain->m_pSwapChain->SetFullscreenState(false, NULL);
        }
        delete pSwapChain;
    }

    // Clear the context and the device

    //SAFE_RELEASE( m_pDevice );
    //SAFE_RELEASE( m_pDebugger );
}

void RendererDX11::Present(HWND hWnd, int SwapChain, UINT SyncInterval, UINT PresentFlags)
{
    // Present to the window

    unsigned int index = static_cast<unsigned int>(SwapChain);

    if (index < m_vSwapChains.size()) {
        SwapChainDX11* pSwapChain = m_vSwapChains[SwapChain];
        HRESULT hr = pSwapChain->m_pSwapChain->Present(SyncInterval, PresentFlags);
    }
    else {
        Log::Get().Write(L"Tried to present an invalid swap chain index!");
    }
}

int RendererDX11::CreateSwapChain(SwapChainConfigDX11* pConfig)
{
    // Attempt to create the DXGI Factory.

    ComPtr<IDXGIDevice> pDXGIDevice;
    HRESULT hr = m_pDevice.CopyTo(pDXGIDevice.GetAddressOf());

    ComPtr<IDXGIAdapter> pDXGIAdapter;
    hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void **>(pDXGIAdapter.GetAddressOf()));

    ComPtr<IDXGIFactory> pFactory;
    pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void **>(pFactory.GetAddressOf()));


    // Attempt to create the swap chain.

    ComPtr<IDXGISwapChain> pSwapChain;
    hr = pFactory->CreateSwapChain(m_pDevice.Get(), &pConfig->m_State, pSwapChain.GetAddressOf());


    // Release the factory regardless of pass or fail.

    if (FAILED(hr))
    {
        Log::Get().Write(L"Failed to create swap chain!");
        return(-1);
    }


    // Acquire the texture interface from the swap chain.

    Texture2DComPtr pSwapChainBuffer;
    hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast< void** >(pSwapChainBuffer.GetAddressOf()));

    if (FAILED(hr))
    {
        Log::Get().Write(L"Failed to get swap chain texture resource!");
        return(-1);
    }


    // Add the swap chain's back buffer texture and render target views to the internal data
    // structures to allow setting them later on.

    int ResourceID = StoreNewResource(new Texture2dDX11(pSwapChainBuffer));


    // If we get here, then we succeeded in creating our swap chain and it's constituent parts.
    // Now we create the wrapper object and store the result in our container.

    Texture2dConfigDX11 TextureConfig;
    pSwapChainBuffer->GetDesc(&TextureConfig.m_State);

    ResourcePtr Proxy(new ResourceProxyDX11(ResourceID, &TextureConfig, this));
    // With the resource proxy created, create the swap chain wrapper and store it.
    // The resource proxy can then be used later on by the application to get the
    // RTV or texture ID if needed.

    m_vSwapChains.push_back(new SwapChainDX11(pSwapChain, Proxy));

    return(m_vSwapChains.size() - 1);
}

ResourcePtr RendererDX11::CreateVertexBuffer(BufferConfigDX11* pConfig, D3D11_SUBRESOURCE_DATA* pData)
{
    // Create the buffer with the specified configuration.
    BufferComPtr pBuffer;
    HRESULT hr = m_pDevice->CreateBuffer(&pConfig->m_State, pData, pBuffer.GetAddressOf());

    if (pBuffer)
    {
        VertexBufferDX11* pVertexBuffer = new VertexBufferDX11(pBuffer);
        pVertexBuffer->SetDesiredDescription(pConfig->m_State);

        // Return an index with the lower 16 bits of index, and the upper
        // 16 bits to identify the resource type.

        int ResourceID = StoreNewResource(pVertexBuffer);
        ResourcePtr Proxy(new ResourceProxyDX11(ResourceID, pConfig, this));

        return(Proxy);
    }

    return(ResourcePtr(new ResourceProxyDX11()));
}

ResourcePtr RendererDX11::CreateIndexBuffer(BufferConfigDX11* pConfig, D3D11_SUBRESOURCE_DATA* pData)
{
    // Create the buffer with the specified configuration.

    BufferComPtr pBuffer;
    HRESULT hr = m_pDevice->CreateBuffer(&pConfig->m_State, pData, pBuffer.GetAddressOf());

    if (pBuffer)
    {
        IndexBufferDX11* pIndexBuffer = new IndexBufferDX11(pBuffer);
        pIndexBuffer->SetDesiredDescription(pConfig->m_State);

        // Return an index with the lower 16 bits of index, and the upper
        // 16 bits to identify the resource type.

        int ResourceID = StoreNewResource(pIndexBuffer);
        ResourcePtr Proxy(new ResourceProxyDX11(ResourceID, pConfig, this));

        return(Proxy);
    }

    return(ResourcePtr(new ResourceProxyDX11()));
}

ResourcePtr RendererDX11::CreateStructuredBuffer(BufferConfigDX11* pConfig, D3D11_SUBRESOURCE_DATA* pData)
{
    // Create the buffer with the specified configuration.

    BufferComPtr pBuffer;
    HRESULT hr = m_pDevice->CreateBuffer(&pConfig->m_State, pData, pBuffer.GetAddressOf());

    if (pBuffer)
    {
        StructuredBufferDX11* pStructuredBuffer = new StructuredBufferDX11(pBuffer);
        pStructuredBuffer->SetDesiredDescription(pConfig->m_State);

        // Return an index with the lower 16 bits of index, and the upper
        // 16 bits to identify the resource type.

        int ResourceID = StoreNewResource(pStructuredBuffer);
        ResourcePtr Proxy(new ResourceProxyDX11(ResourceID, pConfig, this));

        return(Proxy);
    }

    return(ResourcePtr(new ResourceProxyDX11()));
}

ResourcePtr RendererDX11::CreateByteAddressBuffer(BufferConfigDX11* pConfig, D3D11_SUBRESOURCE_DATA* pData)
{
    // Create the buffer with the specified configuration.

    BufferComPtr pBuffer;
    HRESULT hr = m_pDevice->CreateBuffer(&pConfig->m_State, pData, pBuffer.GetAddressOf());

    if (pBuffer)
    {
        ByteAddressBufferDX11* pByteAddressBuffer = new ByteAddressBufferDX11(pBuffer);
        pByteAddressBuffer->SetDesiredDescription(pConfig->m_State);

        // Return an index with the lower 16 bits of index, and the upper
        // 16 bits to identify the resource type.

        int ResourceID = StoreNewResource(pByteAddressBuffer);
        ResourcePtr Proxy(new ResourceProxyDX11(ResourceID, pConfig, this));

        return(Proxy);
    }

    return(ResourcePtr(new ResourceProxyDX11()));
}

ResourcePtr RendererDX11::CreateIndirectArgsBuffer(BufferConfigDX11* pConfig, D3D11_SUBRESOURCE_DATA* pData)
{
    // Create the buffer with the specified configuration.

    BufferComPtr pBuffer;
    HRESULT hr = m_pDevice->CreateBuffer(&pConfig->m_State, pData, pBuffer.GetAddressOf());

    if (pBuffer)
    {
        IndirectArgsBufferDX11* pIndirectArgsBuffer = new IndirectArgsBufferDX11(pBuffer);
        pIndirectArgsBuffer->SetDesiredDescription(pConfig->m_State);

        // Return an index with the lower 16 bits of index, and the upper
        // 16 bits to identify the resource type.

        int ResourceID = StoreNewResource(pIndirectArgsBuffer);
        ResourcePtr Proxy(new ResourceProxyDX11(ResourceID, pConfig, this));

        return(Proxy);
    }

    return(ResourcePtr(new ResourceProxyDX11()));
}

ResourcePtr RendererDX11::CreateConstantBuffer(BufferConfigDX11* pConfig, D3D11_SUBRESOURCE_DATA* pData, bool bAutoUpdate)
{
    // Set the constant buffer flag in addition to any other flags that
    // the user has set.

    BufferComPtr pBuffer;
    HRESULT hr = m_pDevice->CreateBuffer(&pConfig->m_State, pData, pBuffer.GetAddressOf());

    if (pBuffer)
    {
        ConstantBufferDX11* pConstantBuffer = new ConstantBufferDX11(pBuffer);
        pConstantBuffer->SetDesiredDescription(pConfig->m_State);
        pConstantBuffer->SetAutoUpdate(bAutoUpdate);

        // Return an index with the lower 16 bits of index, and the upper
        // 16 bits to identify the resource type.
        int ResourceID = StoreNewResource(pConstantBuffer);
        ResourcePtr Proxy(new ResourceProxyDX11(ResourceID, pConfig, this));

        return(Proxy);
    }

    return(ResourcePtr(new ResourceProxyDX11()));
}

ResourcePtr RendererDX11::CreateTexture1D(Texture1dConfigDX11* pConfig, D3D11_SUBRESOURCE_DATA* pData,
    ShaderResourceViewConfigDX11* pSRVConfig,
    RenderTargetViewConfigDX11* pRTVConfig,
    UnorderedAccessViewConfigDX11* pUAVConfig)
{
    Texture1DComPtr pTexture;
    HRESULT hr = m_pDevice->CreateTexture1D(&pConfig->m_State, pData, pTexture.GetAddressOf());

    if (pTexture)
    {
        Texture1dDX11* pTex = new Texture1dDX11(pTexture);
        pTex->SetDesiredDescription(pConfig->GetTextureDesc());

        // Return an index with the lower 16 bits of index, and the upper
        // 16 bits to identify the resource type.
        int ResourceID = StoreNewResource(pTex);
        ResourcePtr Proxy(new ResourceProxyDX11(ResourceID, pConfig, this, pSRVConfig, pRTVConfig, pUAVConfig));

        return(Proxy);
    }

    return(ResourcePtr(new ResourceProxyDX11()));
}

ResourcePtr RendererDX11::CreateTexture2D(Texture2dConfigDX11* pConfig, D3D11_SUBRESOURCE_DATA* pData,
    ShaderResourceViewConfigDX11* pSRVConfig,
    RenderTargetViewConfigDX11* pRTVConfig,
    UnorderedAccessViewConfigDX11* pUAVConfig,
    DepthStencilViewConfigDX11* pDSVConfig)
{
    Texture2DComPtr pTexture;
    HRESULT hr = m_pDevice->CreateTexture2D(&pConfig->m_State, pData, pTexture.GetAddressOf());

    if (pTexture)
    {
        Texture2dDX11* pTex = new Texture2dDX11(pTexture);
        pTex->SetDesiredDescription(pConfig->GetTextureDesc());

        // Return an index with the lower 16 bits of index, and the upper
        // 16 bits to identify the resource type.
        int ResourceID = StoreNewResource(pTex);
        ResourcePtr Proxy(new ResourceProxyDX11(ResourceID, pConfig, this, pSRVConfig, pRTVConfig, pUAVConfig, pDSVConfig));

        return(Proxy);
    }

    return(ResourcePtr(new ResourceProxyDX11()));
}

ResourcePtr RendererDX11::CreateTexture3D(Texture3dConfigDX11* pConfig, D3D11_SUBRESOURCE_DATA* pData,
    ShaderResourceViewConfigDX11* pSRVConfig,
    RenderTargetViewConfigDX11* pRTVConfig,
    UnorderedAccessViewConfigDX11* pUAVConfig)
{
    Texture3DComPtr pTexture;
    HRESULT hr = m_pDevice->CreateTexture3D(&pConfig->m_State, pData, pTexture.GetAddressOf());

    if (pTexture)
    {
        Texture3dDX11* pTex = new Texture3dDX11(pTexture);
        pTex->SetDesiredDescription(pConfig->GetTextureDesc());

        // Return an index with the lower 16 bits of index, and the upper
        // 16 bits to identify the resource type.
        int ResourceID = StoreNewResource(pTex);
        ResourcePtr Proxy(new ResourceProxyDX11(ResourceID, pConfig, this, pSRVConfig, pRTVConfig, pUAVConfig));

        return(Proxy);
    }

    return(ResourcePtr(new ResourceProxyDX11()));
}

int RendererDX11::CreateShaderResourceView(int ResourceID, D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc)
{
    ID3D11Resource* pRawResource = 0;
    ResourceDX11* pResource = GetResourceByIndex(ResourceID);

    if (pResource) {
        pRawResource = pResource->GetResource();

        if (pRawResource) {
            ShaderResourceViewComPtr pView;
            HRESULT hr = m_pDevice->CreateShaderResourceView(pRawResource, pDesc, pView.GetAddressOf());

            if (pView) {
                m_vShaderResourceViews.push_back(pView);
                return(m_vShaderResourceViews.size() - 1);
            }
        }
    }

    return(-1);
}

int RendererDX11::CreateRenderTargetView(int ResourceID, D3D11_RENDER_TARGET_VIEW_DESC* pDesc)
{
    ID3D11Resource* pRawResource = 0;
    ResourceDX11* pResource = GetResourceByIndex(ResourceID);

    if (pResource) {
        pRawResource = pResource->GetResource();

        if (pRawResource) {
            RenderTargetViewComPtr pView;
            HRESULT hr = m_pDevice->CreateRenderTargetView(pRawResource, pDesc, pView.GetAddressOf());

            if (pView) {
                m_vRenderTargetViews.push_back(pView);
                return(m_vRenderTargetViews.size() - 1);
            }
        }
    }

    return(-1);
}

int RendererDX11::CreateDepthStencilView(int ResourceID, D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc)
{
    ID3D11Resource* pRawResource = 0;
    ResourceDX11* pResource = GetResourceByIndex(ResourceID);

    if (pResource) {
        pRawResource = pResource->GetResource();

        if (pRawResource) {

            DepthStencilViewComPtr pView;
            HRESULT hr = m_pDevice->CreateDepthStencilView(pRawResource, pDesc, pView.GetAddressOf());

            if (pView) {
                m_vDepthStencilViews.push_back(pView);
                return(m_vDepthStencilViews.size() - 1);
            }
        }
    }

    return(-1);
}

int RendererDX11::CreateUnorderedAccessView(int ResourceID, D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc)
{
    ID3D11Resource* pRawResource = 0;
    ResourceDX11* pResource = GetResourceByIndex(ResourceID);

    if (pResource) {
        pRawResource = pResource->GetResource();

        if (pRawResource) {
            UnorderedAccessViewComPtr pView;
            HRESULT hr = m_pDevice->CreateUnorderedAccessView(pRawResource, pDesc, pView.GetAddressOf());

            if (pView) {
                m_vUnorderedAccessViews.push_back(pView);
                return(m_vUnorderedAccessViews.size() - 1);
            }
        }
    }

    return(-1);
}

int RendererDX11::LoadShader(ShaderType type, std::wstring filename, std::wstring function,
    std::wstring model, bool enablelogging)
{
    return LoadShader(type, filename, function, model, NULL, enablelogging);
}

int RendererDX11::LoadShader(ShaderType type, std::wstring filename, std::wstring function,
    std::wstring model, const D3D_SHADER_MACRO* pDefines, bool enablelogging)
{

    // Check the existing list of shader files to see if there are any matches
    // before trying to load it up again.  This will reduce the load times,
    // and should speed up rendering in many cases since the shader object won't 
    // have to be bound again.  
    //
    // In the case that there are any defines passed in, we skip returning the 
    // cached shader - we assume that something is different about the shader due
    // to the defines, so we can't just reuse a previously loaded one.

    for (unsigned int i = 0; i < m_vShaders.size(); i++)
    {
        ShaderDX11* pShader = m_vShaders[i];

        if (pShader->FileName.compare(filename) == 0
            && pShader->Function.compare(function) == 0
            && pShader->ShaderModel.compare(model) == 0
            && pDefines == nullptr)
        {
            return(i);
        }
    }

    HRESULT hr = S_OK;

    ID3DBlob* pCompiledShader = NULL;

    pCompiledShader = ShaderFactoryDX11::GenerateShader(type, filename, function, model, pDefines, enablelogging);
    //pCompiledShader = ShaderFactoryDX11::GeneratePrecompiledShader( filename, function, model );

    if (pCompiledShader == nullptr) {
        return(-1);
    }

    // Create the shader wrapper to house all of the information about its interface.

    ShaderDX11* pShaderWrapper = 0;

    switch (type)
    {
    case VERTEX_SHADER:
    {
        ID3D11VertexShader* pShader = 0;

        hr = m_pDevice->CreateVertexShader(
            pCompiledShader->GetBufferPointer(),
            pCompiledShader->GetBufferSize(),
            0, &pShader);

        pShaderWrapper = new VertexShaderDX11(pShader);
        break;
    }

    case GEOMETRY_SHADER:
    {
        ID3D11GeometryShader* pShader = 0;

        hr = m_pDevice->CreateGeometryShader(
            pCompiledShader->GetBufferPointer(),
            pCompiledShader->GetBufferSize(),
            0, &pShader);

        pShaderWrapper = new GeometryShaderDX11(pShader);
        break;
    }

    case PIXEL_SHADER:
    {
        ID3D11PixelShader* pShader = 0;

        hr = m_pDevice->CreatePixelShader(
            pCompiledShader->GetBufferPointer(),
            pCompiledShader->GetBufferSize(),
            0, &pShader);

        pShaderWrapper = new PixelShaderDX11(pShader);
        break;
    }
    }

    if (FAILED(hr))
    {
        Log::Get().Write(L"Failed to create shader!");
        pCompiledShader->Release();
        delete pShaderWrapper;
        return(-1);
    }

    pShaderWrapper->FileName = filename;
    pShaderWrapper->Function = function;
    pShaderWrapper->ShaderModel = model;

    m_vShaders.push_back(pShaderWrapper);




    // Store the compiled shader in the shader wrapper for use later on in creating
    // and checking input and output signatures.
    pShaderWrapper->m_pCompiledShader = pCompiledShader;


    ShaderReflectionDX11* pReflection = ShaderReflectionFactoryDX11::GenerateReflection(*pShaderWrapper);


    // Initialize the constant buffers of this shader, so that they aren't 
    // lazy created later on...

    pReflection->InitializeConstantBuffers(m_pParamMgr);

    pShaderWrapper->SetReflection(pReflection);

    //pReflection->PrintShaderDetails();


    // Return the index for future referencing.

    return(m_vShaders.size() - 1);

}

int RendererDX11::CreateInputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>& elements, int ShaderID)
{
    // Create array of elements here for the API call.
    D3D11_INPUT_ELEMENT_DESC* pElements = new D3D11_INPUT_ELEMENT_DESC[elements.size()];
    for (unsigned int i = 0; i < elements.size(); i++)
        pElements[i] = elements[i];

    // Attempt to create the input layout from the input information.
    ID3DBlob* pCompiledShader = m_vShaders[ShaderID]->m_pCompiledShader;
    InputLayoutComPtr pLayout;

    HRESULT hr = m_pDevice->CreateInputLayout(pElements, elements.size(),
        pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), pLayout.GetAddressOf());

    // Release the input elements array.
    delete[] pElements;

    // On failure, log the error and return an invalid index.
    if (FAILED(hr))
    {
        Log::Get().Write(L"Failed to create input layout!");
        return(-1);
    }

    m_vInputLayouts.push_back(pLayout);

    // Return the index for referencing later on.
    return(m_vInputLayouts.size() - 1);
}

int RendererDX11::CreateBlendState(BlendStateConfigDX11* pConfig)
{
    // If this state has already been created before, just return the index.

    auto entry = m_BlendStateLookup.find(*pConfig);

    if (entry != m_BlendStateLookup.end()) {
        return entry->second;
    }

    // If it hasn't been created before, create it, then store it, and return it.

    BlendStateComPtr pState;

    HRESULT hr = m_pDevice->CreateBlendState(dynamic_cast<D3D11_BLEND_DESC*>(pConfig), pState.GetAddressOf());

    if (FAILED(hr))
    {
        Log::Get().Write(L"Failed to create blend state!");
        return(-1);
    }

    m_BlendStates.push_back(pState);

    int id = m_BlendStates.size() - 1;
    m_BlendStateLookup[*pConfig] = id;

    return id;
}

int RendererDX11::CreateDepthStencilState(DepthStencilStateConfigDX11* pConfig)
{
    // If this state has already been created before, just return the index.

    auto entry = m_DepthStencilStateLookup.find(*pConfig);

    if (entry != m_DepthStencilStateLookup.end()) {
        return entry->second;
    }

    // If it hasn't been created before, create it, then store it, and return it.

    DepthStencilStateComPtr pState;

    HRESULT hr = m_pDevice->CreateDepthStencilState(dynamic_cast<D3D11_DEPTH_STENCIL_DESC*>(pConfig), pState.GetAddressOf());

    if (FAILED(hr))
    {
        Log::Get().Write(L"Failed to create depth stencil state!");
        return(-1);
    }

    m_DepthStencilStates.push_back(pState);

    int id = m_DepthStencilStates.size() - 1;
    m_DepthStencilStateLookup[*pConfig] = id;

    return id;
}

int RendererDX11::CreateRasterizerState(RasterizerStateConfigDX11* pConfig)
{
    // If this state has already been created before, just return the index.

    auto entry = m_RasterizerStateLookup.find(*pConfig);

    if (entry != m_RasterizerStateLookup.end()) {
        return entry->second;
    }

    // If it hasn't been created before, create it, then store it, and return it.

    RasterizerStateComPtr pState;

    HRESULT hr = m_pDevice->CreateRasterizerState(dynamic_cast<D3D11_RASTERIZER_DESC*>(pConfig), pState.GetAddressOf());

    if (FAILED(hr))
    {
        Log::Get().Write(L"Failed to create rasterizer state!");
        return(-1);
    }

    m_RasterizerStates.push_back(pState);

    int id = m_RasterizerStates.size() - 1;
    m_RasterizerStateLookup[*pConfig] = id;

    return id;
}

int RendererDX11::CreateSamplerState(D3D11_SAMPLER_DESC* pDesc)
{
    SamplerStateComPtr pState;

    HRESULT hr = m_pDevice->CreateSamplerState(pDesc, pState.GetAddressOf());

    if (FAILED(hr))
    {
        Log::Get().Write(L"Failed to create sampler state!");
        return(-1);
    }

    m_vSamplerStates.push_back(pState);

    return(m_vSamplerStates.size() - 1);
}

int RendererDX11::CreateViewPort(D3D11_VIEWPORT viewport)
{
    m_vViewPorts.emplace_back(viewport);

    return(m_vViewPorts.size() - 1);
}

ResourcePtr RendererDX11::GetSwapChainResource(int ID)
{
    unsigned int index = static_cast<unsigned int>(ID);

    if (index < m_vSwapChains.size())
        return(m_vSwapChains[index]->m_Resource);

    Log::Get().Write(L"Tried to get an invalid swap buffer index texture ID!");

    return(ResourcePtr(new ResourceProxyDX11()));
}

Vector2f RendererDX11::GetDesktopResolution()
{
    // Acquire the DXGI device, then the adapter, then the output...

    ComPtr<IDXGIDevice> pDXGIDevice;
    HRESULT hr = m_pDevice.CopyTo(pDXGIDevice.GetAddressOf());
    ComPtr<IDXGIAdapter> pDXGIAdapter;
    hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void **>(pDXGIAdapter.GetAddressOf()));

    // Take the first output in the adapter.

    ComPtr<IDXGIOutput> pDXGIOutput;
    pDXGIAdapter->EnumOutputs(0, pDXGIOutput.GetAddressOf());

    // Use the output interface to get the output description.

    DXGI_OUTPUT_DESC desc;
    pDXGIOutput->GetDesc(&desc);

    // Return the current output's resolution from the description.
    return(Vector2f(static_cast<float>(desc.DesktopCoordinates.right - desc.DesktopCoordinates.left),
        static_cast<float>(desc.DesktopCoordinates.bottom - desc.DesktopCoordinates.top)));
}

ResourcePtr RendererDX11::LoadTexture(std::wstring filename, bool sRGB)
{
    ComPtr<ID3D11Resource> pResource;

    FileSystem fs;
    filename = fs.GetTextureFolder() + filename;

    // Test whether this is a DDS file or not.
    std::wstring extension = filename.substr(filename.size() - 3, 3);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    HRESULT hr = S_OK;

    if (extension == L"dds")
    {
        hr = DirectX::CreateDDSTextureFromFile(
            m_pDevice.Get(),
            filename.c_str(),
            //0,
            //D3D11_USAGE_DEFAULT,
            //D3D11_BIND_SHADER_RESOURCE,
            //0,
            //0,
            //sRGB,
            pResource.GetAddressOf(),
            nullptr);
    }
    else
    {
        hr = DirectX::CreateWICTextureFromFileEx(
            m_pDevice.Get(),
            pImmPipeline->m_pContext.Get(),
            filename.c_str(),
            0,
            D3D11_USAGE_DEFAULT,
            D3D11_BIND_SHADER_RESOURCE,
            0,
            0,
            sRGB,
            pResource.GetAddressOf(),
            0);
    }



    if (FAILED(hr))
    {
        std::wstring str = L"Failed to load texture from file: " + filename;
        Log::Get().Write(str);
        return(ResourcePtr(new ResourceProxyDX11()));
    }

    ComPtr<ID3D11Texture2D> pTexture;
    pResource.CopyTo(pTexture.GetAddressOf());

    int ResourceID = StoreNewResource(new Texture2dDX11(pTexture));

    Texture2dConfigDX11 TextureConfig;
    pTexture->GetDesc(&TextureConfig.m_State);

    return(ResourcePtr(new ResourceProxyDX11(ResourceID, &TextureConfig, this)));
}

ResourcePtr RendererDX11::LoadTexture(void* pData, SIZE_T sizeInBytes/*, D3DX11_IMAGE_LOAD_INFO* pLoadInfo*/)
{
    ComPtr<ID3D11Resource> pResource;

    HRESULT hr = DirectX::CreateWICTextureFromMemory(
        m_pDevice.Get(),
        pImmPipeline->m_pContext.Get(),
        static_cast<uint8_t*>(pData),
        sizeInBytes,
        pResource.GetAddressOf(),
        0);

    if (FAILED(hr))
    {
        Log::Get().Write(L"Failed to load texture from memory!");
        return(ResourcePtr(new ResourceProxyDX11()));
    }

    ComPtr<ID3D11Texture2D> pTexture;
    pResource.CopyTo(pTexture.GetAddressOf());

    int ResourceID = StoreNewResource(new Texture2dDX11(pTexture));

    Texture2dConfigDX11 TextureConfig;
    pTexture->GetDesc(&TextureConfig.m_State);

    return(ResourcePtr(new ResourceProxyDX11(ResourceID, &TextureConfig, this)));
}

ResourcePtr RendererDX11::LoadTexture(ID3D11Texture2D* pTexture)
{
    // Add a reference to the texture to ensure it doesn't get destroyed while we 
    // are using it.

    // TODO: This method has to be double checked to ensure that the reference 
    //       counting functions properly with the externally created texture!

    ComPtr<ID3D11Texture2D> pTexturePtr(pTexture);

    int ResourceID = StoreNewResource(new Texture2dDX11(pTexture));

    Texture2dConfigDX11 TextureConfig;
    pTexture->GetDesc(&TextureConfig.m_State);

    return(ResourcePtr(new ResourceProxyDX11(ResourceID, &TextureConfig, this)));
}

BlendStateComPtr RendererDX11::GetBlendState(int index)
{
    // TODO: There should be a default blend state that can be returned which will
    //       put the blend state into the default D3D11 state...

    if (index >= 0)
        return(m_BlendStates[index]);
    else
        return(m_BlendStates[0]);
}

DepthStencilStateComPtr RendererDX11::GetDepthState(int index)
{
    // TODO: There should be a default blend state that can be returned which will
    //       put the blend state into the default D3D11 state...

    if (index >= 0)
        return(m_DepthStencilStates[index]);
    else
        return(m_DepthStencilStates[0]);
}

RasterizerStateComPtr RendererDX11::GetRasterizerState(int index)
{
    // TODO: There should be a default blend state that can be returned which will
    //       put the blend state into the default D3D11 state...

    if (index >= 0)
        return(m_RasterizerStates[index]);
    else
        return(m_RasterizerStates[0]);
}

const ViewPortDX11& RendererDX11::GetViewPort(int ID)
{
    unsigned int index = static_cast<unsigned int>(ID);

    assert(index < m_vViewPorts.size());

    return(m_vViewPorts[index]);
}

ResourceDX11* RendererDX11::GetResourceByIndex(int ID)
{
    ResourceDX11* pResource = 0;

    unsigned int index = ID & 0xffff;
    int innerID = (ID & 0xffff0000) >> 16;

    if (index < m_vResources.size()) {
        pResource = m_vResources[index];

        if (pResource->GetInnerID() != innerID) {
            Log::Get().Write(L"Inner ID doesn't match resource index!!!");
        }
    }

    return(pResource);
}

InputLayoutComPtr RendererDX11::GetInputLayout(int index)
{
    return(m_vInputLayouts[index]);
}

SamplerStateComPtr RendererDX11::GetSamplerState(int index)
{
    return(m_vSamplerStates[index]);
}

ShaderDX11* RendererDX11::GetShader(int ID)
{
    unsigned int index = static_cast<unsigned int>(ID);

    if (index < m_vShaders.size())
        return(m_vShaders[index]);
    else
        return(nullptr);
}

void RendererDX11::QueueTask(Task* pTask)
{
    m_vQueuedTasks.push_back(pTask);
}

Texture1dDX11* RendererDX11::GetTexture1DByIndex(int rid)
{
    Texture1dDX11* pResult = 0;

    ResourceDX11* pResource = GetResourceByIndex(rid);

    if (pResource != NULL) {
        if (pResource->GetType() != RT_TEXTURE1D) {
            Log::Get().Write(L"Trying to access a non-texture1D resource!!!!");
        }
        else {
            pResult = reinterpret_cast<Texture1dDX11*>(pResource);
        }
    }

    return(pResult);
}

Texture2dDX11* RendererDX11::GetTexture2DByIndex(int rid)
{
    Texture2dDX11* pResult = 0;

    ResourceDX11* pResource = GetResourceByIndex(rid);

    if (pResource != NULL) {
        if (pResource->GetType() != RT_TEXTURE2D) {
            Log::Get().Write(L"Trying to access a non-texture2D resource!!!!");
        }
        else {
            pResult = reinterpret_cast<Texture2dDX11*>(pResource);
        }
    }

    return(pResult);
}

Texture3dDX11* RendererDX11::GetTexture3DByIndex(int rid)
{
    Texture3dDX11* pResult = 0;

    ResourceDX11* pResource = GetResourceByIndex(rid);

    if (pResource != NULL) {
        if (pResource->GetType() != RT_TEXTURE3D) {
            Log::Get().Write(L"Trying to access a non-texture3D resource!!!!");
        }
        else {
            pResult = reinterpret_cast<Texture3dDX11*>(pResource);
        }
    }

    return(pResult);
}

SwapChainDX11* RendererDX11::GetSwapChainByIndex(int sid)
{
    return(m_vSwapChains[sid]);
}

BufferDX11* RendererDX11::GetGenericBufferByIndex(int rid)
{
    // This method returns a BufferDX11 pointer, which is useful for methods that
    // can operate on more than one type of buffer.  As long as the underlying
    // resource is not a texture, then the pointer is returned, otherwise null
    // is returned.

    BufferDX11* pResult = 0;

    ResourceDX11* pResource = GetResourceByIndex(rid);

    if (pResource != NULL) {
        if (pResource->GetType() == RT_TEXTURE1D || pResource->GetType() == RT_TEXTURE2D || pResource->GetType() == RT_TEXTURE3D) {
            Log::Get().Write(L"Trying to access a non-buffer resource!!!!");
        }
        else {
            pResult = reinterpret_cast<BufferDX11*>(pResource);
        }
    }

    return(pResult);
}

ConstantBufferDX11* RendererDX11::GetConstantBufferByIndex(int rid)
{
    ConstantBufferDX11* pResult = 0;

    ResourceDX11* pResource = GetResourceByIndex(rid);

    if (pResource != NULL) {
        if (pResource->GetType() != RT_CONSTANTBUFFER) {
            Log::Get().Write(L"Trying to access a non-vertex buffer resource!!!!");
        }
        else {
            pResult = reinterpret_cast<ConstantBufferDX11*>(pResource);
        }
    }

    return(pResult);
}

VertexBufferDX11* RendererDX11::GetVertexBufferByIndex(int rid)
{
    VertexBufferDX11* pResult = 0;

    ResourceDX11* pResource = GetResourceByIndex(rid);

    if (pResource != NULL) {
        if (pResource->GetType() != RT_VERTEXBUFFER) {
            Log::Get().Write(L"Trying to access a non-vertex buffer resource!!!!");
        }
        else {
            pResult = reinterpret_cast<VertexBufferDX11*>(pResource);
        }
    }

    return(pResult);
}

IndexBufferDX11* RendererDX11::GetIndexBufferByIndex(int rid)
{
    IndexBufferDX11* pResult = 0;

    ResourceDX11* pResource = GetResourceByIndex(rid);

    if (pResource != NULL) {
        if (pResource->GetType() != RT_INDEXBUFFER) {
            Log::Get().Write(L"Trying to access a non-index buffer resource!!!!");
        }
        else {
            pResult = reinterpret_cast<IndexBufferDX11*>(pResource);
        }
    }

    return(pResult);
}

ByteAddressBufferDX11* RendererDX11::GetByteAddressBufferByIndex(int rid)
{
    ByteAddressBufferDX11* pResult = 0;

    ResourceDX11* pResource = GetResourceByIndex(rid);

    if (pResource != NULL) {
        if (pResource->GetType() != RT_BYTEADDRESSBUFFER) {
            Log::Get().Write(L"Trying to access a non-byte address buffer resource!!!!");
        }
        else {
            pResult = reinterpret_cast<ByteAddressBufferDX11*>(pResource);
        }
    }

    return(pResult);
}

IndirectArgsBufferDX11*	RendererDX11::GetIndirectArgsBufferByIndex(int rid)
{
    IndirectArgsBufferDX11* pResult = 0;

    ResourceDX11* pResource = GetResourceByIndex(rid);

    if (pResource != NULL) {
        if (pResource->GetType() != RT_INDIRECTARGSBUFFER) {
            Log::Get().Write(L"Trying to access a non-indirect args buffer resource!!!!");
        }
        else {
            pResult = reinterpret_cast<IndirectArgsBufferDX11*>(pResource);
        }
    }

    return(pResult);
}

StructuredBufferDX11* RendererDX11::GetStructuredBufferByIndex(int rid)
{
    StructuredBufferDX11* pResult = 0;

    ResourceDX11* pResource = GetResourceByIndex(rid);

    if (pResource != NULL) {
        if (pResource->GetType() != RT_STRUCTUREDBUFFER) {
            Log::Get().Write(L"Trying to access a non-structured buffer resource!!!!");
        }
        else {
            pResult = reinterpret_cast<StructuredBufferDX11*>(pResource);
        }
    }

    return(pResult);
}

RenderTargetViewDX11& RendererDX11::GetRenderTargetViewByIndex(int rid)
{
    assert(rid >= 0);
    assert(rid < m_vRenderTargetViews.size());

    return(m_vRenderTargetViews[rid]);
}

DepthStencilViewDX11& RendererDX11::GetDepthStencilViewByIndex(int rid)
{
    assert(rid >= 0);
    assert(rid < m_vDepthStencilViews.size());

    return(m_vDepthStencilViews[rid]);
}

ShaderResourceViewDX11& RendererDX11::GetShaderResourceViewByIndex(int rid)
{
    assert(rid >= 0);
    assert(rid < m_vShaderResourceViews.size());

    return(m_vShaderResourceViews[rid]);
}

UnorderedAccessViewDX11& RendererDX11::GetUnorderedAccessViewByIndex(int rid)
{
    assert(rid >= 0);
    assert(rid < m_vUnorderedAccessViews.size());

    return(m_vUnorderedAccessViews[rid]);
}

int	RendererDX11::GetUnusedResourceIndex()
{
    // Initialize return index to -1.
    int index = -1;

    // Search for a NULL index location.
    for (unsigned int i = 0; i < m_vResources.size(); i++) {
        if (m_vResources[i] == NULL) {
            index = i;
            break;
        }
    }

    // Return either an empty location, or -1 if none exist.
    return(index);
}

int	RendererDX11::StoreNewResource(ResourceDX11* pResource)
{
    // This method either finds an empty spot in the list, or just appends the
    // resource to the end of it if none are available.

    int index = GetUnusedResourceIndex();

    if (index == -1) {
        m_vResources.push_back(pResource);
        index = m_vResources.size() - 1;
    }
    else {
        m_vResources[index] = pResource;
    }

    // Shift the inner ID to the upper 16 bits.
    int innerID = (int)pResource->GetInnerID() << 16;
    index = index + innerID;

    return(index);
}

void RendererDX11::DeleteResource(ResourcePtr ptr)
{
    // This is a convenience method that just passes the resource index to
    // the delete function.

    DeleteResource(ptr->m_iResource);
}

void RendererDX11::DeleteResource(int index)
{
    // Here the resource is looked up, then deleted if it was found.  After 
    // being deleted, it is 
    ResourceDX11* pResource = GetResourceByIndex(index);

    if (pResource != nullptr) {
        delete pResource;
        m_vResources[index & 0xffff] = nullptr;
    }
}

ID3D11Device* RendererDX11::GetDevice()
{
    return(m_pDevice.Get());
}

//template <class T>
//void LogObjectVector(std::vector<T> objects)
//{
//    for (auto object : objects)
//        Log::Get().Write(object.ToString());
//}
//
//template <class T>
//void LogObjectPtrVector(std::vector<T> objects)
//{
//    for (auto object : objects)
//        Log::Get().Write(object->ToString());
//}