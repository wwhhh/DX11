#include "MaterialGeneratorDX11.h"
#include "BlendStateConfigDX11.h"
#include "DepthStencilStateConfigDX11.h"
#include "RasterizerStateConfigDX11.h"
#include "../Core/Resource/TextureLoader.h"

MaterialGeneratorDX11::MaterialGeneratorDX11()
{
}

MaterialPtr MaterialGeneratorDX11::GenerateBaseMaterial(RendererDX11& Renderer)
{
    MaterialPtr pMaterial = MaterialPtr(new MaterialDX11());

    RenderEffectDX11* pEffect = new RenderEffectDX11();
    pEffect->SetVertexShader(Renderer.LoadShader(VERTEX_SHADER,
        std::wstring(L"Base.hlsl"),
        std::wstring(L"VSMain"),
        std::wstring(L"vs_5_0")));

    pEffect->SetPixelShader(Renderer.LoadShader(PIXEL_SHADER,
        std::wstring(L"Base.hlsl"),
        std::wstring(L"PSMain"),
        std::wstring(L"ps_5_0")));

    Renderer.GetShader(pEffect->GetVertexShader())->GetReflection()->PrintShaderDetails();

    // 设置深度模板配置
    DepthStencilStateConfigDX11 DS;
    DS.DepthFunc = D3D11_COMPARISON_LESS;
    pEffect->m_iDepthStencilState = Renderer.CreateDepthStencilState(&DS);

    // 设置混合配置
    BlendStateConfigDX11 BS;
    pEffect->m_iBlendState = Renderer.CreateBlendState(&BS);

    // 设置光栅配置
    RasterizerStateConfigDX11 RS;
    //RS.FillMode = D3D11_FILL_WIREFRAME;
    RS.CullMode = D3D11_CULL_NONE;
    pEffect->m_iRasterizerState = Renderer.CreateRasterizerState(&RS);

    // 允许渲染并设置渲染参数
    pMaterial->Params[VT_PERSPECTIVE].bRender = true;
    pMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;

    return pMaterial;
}

MaterialPtr MaterialGeneratorDX11::GenerateBaseColorMaterial(RendererDX11& Renderer)
{
    MaterialPtr pMaterial = MaterialPtr(new MaterialDX11());

    RenderEffectDX11* pEffect = new RenderEffectDX11();
    pEffect->SetVertexShader(Renderer.LoadShader(VERTEX_SHADER,
        std::wstring(L"VertexColor.hlsl"),
        std::wstring(L"VSMain"),
        std::wstring(L"vs_5_0")));

    pEffect->SetPixelShader(Renderer.LoadShader(PIXEL_SHADER,
        std::wstring(L"VertexColor.hlsl"),
        std::wstring(L"PSMain"),
        std::wstring(L"ps_5_0")));

    //Renderer.GetShader(pEffect->GetVertexShader())->GetReflection()->PrintShaderDetails();

    // 设置深度模板配置
    DepthStencilStateConfigDX11 DS;
    DS.DepthFunc = D3D11_COMPARISON_LESS;
    pEffect->m_iDepthStencilState = Renderer.CreateDepthStencilState(&DS);

    // 设置混合配置
    BlendStateConfigDX11 BS;
    pEffect->m_iBlendState = Renderer.CreateBlendState(&BS);

    // 设置光栅配置
    RasterizerStateConfigDX11 RS;
    //RS.FillMode = D3D11_FILL_WIREFRAME;
    RS.CullMode = D3D11_CULL_NONE;
    pEffect->m_iRasterizerState = Renderer.CreateRasterizerState(&RS);

    // 允许渲染并设置渲染参数
    pMaterial->Params[VT_PERSPECTIVE].bRender = true;
    pMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;
    pMaterial->Params[VT_GBUFFER].bRender = true;
    pMaterial->Params[VT_GBUFFER].pEffect = pEffect;

    return pMaterial;
}

MaterialPtr MaterialGeneratorDX11::GenerateModelMaterial(RendererDX11& Renderer)
{
    MaterialPtr pMaterial = MaterialPtr(new MaterialDX11());

    RenderEffectDX11* pEffect = new RenderEffectDX11();
    pEffect->SetVertexShader(Renderer.LoadShader(VERTEX_SHADER,
        std::wstring(L"Model.hlsl"),
        std::wstring(L"VSMain"),
        std::wstring(L"vs_5_0")));

    pEffect->SetPixelShader(Renderer.LoadShader(PIXEL_SHADER,
        std::wstring(L"Model.hlsl"),
        std::wstring(L"PSMain"),
        std::wstring(L"ps_5_0")));

    //Renderer.GetShader(pEffect->GetVertexShader())->GetReflection()->PrintShaderDetails();

    // 设置深度模板配置
    DepthStencilStateConfigDX11 DS;
    DS.DepthFunc = D3D11_COMPARISON_LESS;
    pEffect->m_iDepthStencilState = Renderer.CreateDepthStencilState(&DS);

    // 设置混合配置
    BlendStateConfigDX11 BS;
    pEffect->m_iBlendState = Renderer.CreateBlendState(&BS);

    // 设置光栅配置
    RasterizerStateConfigDX11 RS;
    //RS.FillMode = D3D11_FILL_WIREFRAME;
    RS.CullMode = D3D11_CULL_NONE;
    pEffect->m_iRasterizerState = Renderer.CreateRasterizerState(&RS);

    // 允许渲染并设置渲染参数
    pMaterial->Params[VT_PERSPECTIVE].bRender = true;
    pMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;

    return pMaterial;
}

MaterialPtr MaterialGeneratorDX11::GeneratePhongMaterial(RendererDX11& Renderer)
{
    MaterialPtr pMaterial = MaterialPtr(new MaterialDX11());

    RenderEffectDX11* pEffect = new RenderEffectDX11();
    pEffect->SetVertexShader(Renderer.LoadShader(VERTEX_SHADER,
        std::wstring(L"phong.hlsl"),
        std::wstring(L"VSMain"),
        std::wstring(L"vs_5_0")));

    pEffect->SetPixelShader(Renderer.LoadShader(PIXEL_SHADER,
        std::wstring(L"phong.hlsl"),
        std::wstring(L"PSMain"),
        std::wstring(L"ps_5_0")));

    //Renderer.GetShader(pEffect->GetVertexShader())->GetReflection()->PrintShaderDetails();

    // 设置深度模板配置
    DepthStencilStateConfigDX11 DS;
    DS.DepthFunc = D3D11_COMPARISON_LESS;
    pEffect->m_iDepthStencilState = Renderer.CreateDepthStencilState(&DS);

    // 设置混合配置
    BlendStateConfigDX11 BS;
    pEffect->m_iBlendState = Renderer.CreateBlendState(&BS);

    // 设置光栅配置
    RasterizerStateConfigDX11 RS;
    //RS.FillMode = D3D11_FILL_WIREFRAME;
    RS.CullMode = D3D11_CULL_NONE;
    pEffect->m_iRasterizerState = Renderer.CreateRasterizerState(&RS);

    // 允许渲染并设置渲染参数
    pMaterial->Params[VT_PERSPECTIVE].bRender = true;
    pMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;
    pMaterial->Params[VT_GBUFFER].bRender = true;
    pMaterial->Params[VT_GBUFFER].pEffect = pEffect;

    return pMaterial;
}

MaterialPtr MaterialGeneratorDX11::GeneratePBRTestMaterial(RendererDX11& Renderer)
{
    MaterialPtr pMaterial = MaterialPtr(new MaterialDX11());

    RenderEffectDX11* pEffect = new RenderEffectDX11();
    pEffect->SetVertexShader(Renderer.LoadShader(VERTEX_SHADER,
        std::wstring(L"pbr.hlsl"),
        std::wstring(L"VSMain"),
        std::wstring(L"vs_5_0")));

    pEffect->SetPixelShader(Renderer.LoadShader(PIXEL_SHADER,
        std::wstring(L"pbr.hlsl"),
        std::wstring(L"PSMain"),
        std::wstring(L"ps_5_0")));

    //Renderer.GetShader(pEffect->GetVertexShader())->GetReflection()->PrintShaderDetails();

    // 设置深度模板配置
    DepthStencilStateConfigDX11 DS;
    DS.DepthFunc = D3D11_COMPARISON_LESS;
    pEffect->m_iDepthStencilState = Renderer.CreateDepthStencilState(&DS);

    // 设置混合配置
    BlendStateConfigDX11 BS;
    pEffect->m_iBlendState = Renderer.CreateBlendState(&BS);

    // 设置光栅配置
    RasterizerStateConfigDX11 RS;
    //RS.FillMode = D3D11_FILL_WIREFRAME;
    RS.CullMode = D3D11_CULL_NONE;
    pEffect->m_iRasterizerState = Renderer.CreateRasterizerState(&RS);

    // 允许渲染并设置渲染参数
    pMaterial->Params[VT_PERSPECTIVE].bRender = true;
    pMaterial->Params[VT_PERSPECTIVE].pEffect = pEffect;

    return pMaterial;
}

MaterialPtr MaterialGeneratorDX11::GenerateDeferredRendering(RendererDX11& Renderer)
{
    MaterialPtr pMaterial = MaterialPtr(new MaterialDX11());

    RenderEffectDX11* pEffectCompare = new RenderEffectDX11();
    pEffectCompare->SetVertexShader(Renderer.LoadShader(VERTEX_SHADER,
        std::wstring(L"phong.hlsl"),
        std::wstring(L"VSMain"),
        std::wstring(L"vs_5_0")));

    pEffectCompare->SetPixelShader(Renderer.LoadShader(PIXEL_SHADER,
        std::wstring(L"phong.hlsl"),
        std::wstring(L"PSMain"),
        std::wstring(L"ps_5_0")));

    // 创建并绑定 shader
    RenderEffectDX11* pEffect = new RenderEffectDX11();
    pEffect->SetVertexShader(Renderer.LoadShader(VERTEX_SHADER,
        std::wstring(L"DeferredRendering.hlsl"),
        std::wstring(L"VS"),
        std::wstring(L"vs_5_0")));

    pEffect->SetPixelShader(Renderer.LoadShader(PIXEL_SHADER,
        std::wstring(L"DeferredRendering.hlsl"),
        std::wstring(L"PS"),
        std::wstring(L"ps_5_0")));

    // 设置深度模板配置
    DepthStencilStateConfigDX11 DS;
    DS.DepthFunc = D3D11_COMPARISON_LESS;
    pEffectCompare->m_iDepthStencilState = Renderer.CreateDepthStencilState(&DS);

    // 设置混合配置
    BlendStateConfigDX11 BS;
    pEffectCompare->m_iBlendState = Renderer.CreateBlendState(&BS);

    // 设置光栅配置
    RasterizerStateConfigDX11 RS;
    //RS.FillMode = D3D11_FILL_WIREFRAME;
    RS.CullMode = D3D11_CULL_NONE;
    pEffectCompare->m_iRasterizerState = Renderer.CreateRasterizerState(&RS);

    pEffect->m_iDepthStencilState = Renderer.CreateDepthStencilState(&DS);
    pEffect->m_iBlendState = Renderer.CreateBlendState(&BS);
    //RS.FillMode = D3D11_FILL_WIREFRAME;
    RS.CullMode = D3D11_CULL_NONE;
    pEffect->m_iRasterizerState = Renderer.CreateRasterizerState(&RS);

    // 采样器
    D3D11_SAMPLER_DESC sampDesc;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.BorderColor[0] = sampDesc.BorderColor[1] = sampDesc.BorderColor[2] = sampDesc.BorderColor[3] = 0;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
    sampDesc.MaxAnisotropy = 16;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    sampDesc.MinLOD = 0.0f;
    sampDesc.MipLODBias = 0.0f;
    int samplerState = Renderer.CreateSamplerState(&sampDesc);
    
    // 设置参数
    pMaterial->Parameters.SetSamplerParameter(L"AnisoSampler", samplerState);
    pMaterial->Parameters.SetShaderResourceParameter(L"DiffuseMap", TextureLoader::Get()->LoadTexture(L"Hex.png"));
    
    // 允许渲染并设置渲染参数
    pMaterial->Params[VT_PERSPECTIVE].bRender = true;
    pMaterial->Params[VT_PERSPECTIVE].pEffect = pEffectCompare;
    // 允许渲染并设置渲染参数
    pMaterial->Params[VT_GBUFFER].bRender = true;
    pMaterial->Params[VT_GBUFFER].pEffect = pEffect;

    return pMaterial;
}