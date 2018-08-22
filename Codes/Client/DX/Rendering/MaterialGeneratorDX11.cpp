#include "MaterialGeneratorDX11.h"
#include "BlendStateConfigDX11.h"
#include "DepthStencilStateConfigDX11.h"
#include "RasterizerStateConfigDX11.h"

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

    return pMaterial;
}