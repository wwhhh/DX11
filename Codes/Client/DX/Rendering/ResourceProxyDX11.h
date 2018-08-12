#pragma once

#include "PCH.h"

class BufferConfigDX11;
class Texture1dConfigDX11;
class Texture2dConfigDX11;
class Texture3dConfigDX11;
class DepthStencilViewConfigDX11;
class ShaderResourceViewConfigDX11;
class UnorderedAccessViewConfigDX11;
class RenderTargetViewConfigDX11;
class RendererDX11;

class ResourceProxyDX11
{
public:
    ResourceProxyDX11();
    ResourceProxyDX11(int ResourceID, BufferConfigDX11* pConfig, RendererDX11* pRenderer,
        ShaderResourceViewConfigDX11* pSRVConfig = 0,
        RenderTargetViewConfigDX11* pRTVConfig = 0,
        UnorderedAccessViewConfigDX11* pUAVConfig = 0);
    ResourceProxyDX11(int ResourceID, Texture1dConfigDX11* pConfig, RendererDX11* pRenderer,
        ShaderResourceViewConfigDX11* pSRVConfig = 0,
        RenderTargetViewConfigDX11* pRTVConfig = 0,
        UnorderedAccessViewConfigDX11* pUAVConfig = 0);
    ResourceProxyDX11(int ResourceID, Texture2dConfigDX11* pConfig, RendererDX11* pRenderer,
        ShaderResourceViewConfigDX11* pSRVConfig = 0,
        RenderTargetViewConfigDX11* pRTVConfig = 0,
        UnorderedAccessViewConfigDX11* pUAVConfig = 0,
        DepthStencilViewConfigDX11* pDSVConfig = 0);
    ResourceProxyDX11(int ResourceID, Texture3dConfigDX11* pConfig, RendererDX11* pRenderer,
        ShaderResourceViewConfigDX11* pSRVConfig = 0,
        RenderTargetViewConfigDX11* pRTVConfig = 0,
        UnorderedAccessViewConfigDX11* pUAVConfig = 0);

    virtual ~ResourceProxyDX11();

public:

    int						m_iResource;
    int						m_iResourceSRV;
    int						m_iResourceRTV;
    int						m_iResourceDSV;
    int						m_iResourceUAV;

    BufferConfigDX11*		        m_pBufferConfig;
    Texture1dConfigDX11*	        m_pTexture1dConfig;
    Texture2dConfigDX11*	        m_pTexture2dConfig;
    Texture3dConfigDX11*	        m_pTexture3dConfig;
    DepthStencilViewConfigDX11*     m_pDSVConfig;
    ShaderResourceViewConfigDX11*   m_pSRVConfig;
    RenderTargetViewConfigDX11*     m_pRTVConfig;
    UnorderedAccessViewConfigDX11*  m_pUAVConfig;

    friend RendererDX11;

protected:
    void CommonConstructor(unsigned int BindFlags, int ResourceID, RendererDX11* pRenderer,
        ShaderResourceViewConfigDX11* pSRVConfig,
        RenderTargetViewConfigDX11* pRTVConfig,
        UnorderedAccessViewConfigDX11* pUAVConfig,
        DepthStencilViewConfigDX11* pDSVConfig = 0);
};

typedef std::shared_ptr<ResourceProxyDX11> ResourcePtr;