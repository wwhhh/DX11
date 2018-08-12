#include "RendererDX11.h"

class ShaderResourceViewConfigDX11
{
public:
    ShaderResourceViewConfigDX11();
    virtual ~ShaderResourceViewConfigDX11();

    void SetDefaults();

    void SetFormat( DXGI_FORMAT state );
    void SetViewDimensions( D3D11_SRV_DIMENSION state );        

    void SetBuffer( D3D11_BUFFER_SRV state );
    void SetBufferEx( D3D11_BUFFEREX_SRV state );
    void SetTexture1D( D3D11_TEX1D_SRV state );
    void SetTexture1DArray( D3D11_TEX1D_ARRAY_SRV state );
    void SetTexture2D( D3D11_TEX2D_SRV state );
    void SetTexture2DArray( D3D11_TEX2D_ARRAY_SRV state );
    void SetTexture2DMS( D3D11_TEX2DMS_SRV state );
    void SetTexture2DMSArray( D3D11_TEX2DMS_ARRAY_SRV state );
    void SetTexture3D( D3D11_TEX3D_SRV state );
    void SetTextureCube( D3D11_TEXCUBE_SRV state );
    void SetTextureCubeArray( D3D11_TEXCUBE_ARRAY_SRV state );

    D3D11_SHADER_RESOURCE_VIEW_DESC& GetSRVDesc();

protected:
    D3D11_SHADER_RESOURCE_VIEW_DESC 		m_State;

    friend RendererDX11;
};