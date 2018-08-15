#include "ViewPerspective.h"
#include "Texture2dDX11.h"
#include "Texture2dConfigDX11.h"
#include "Objects\Entity3D.h"
#include "Objects\Scene.h"
#include "Objects\SceneGraph.h"

ViewPerspective::ViewPerspective(RendererDX11& Renderer, ResourcePtr RenderTarget, ResourcePtr DepthTarget)
{
    SetRenderTargets(RenderTarget, DepthTarget);
}

ViewPerspective::~ViewPerspective()
{
}

void ViewPerspective::SetRenderTargets(ResourcePtr RenderTarget, ResourcePtr DepthTarget)
{
    m_RenderTarget = RenderTarget;

    if (nullptr != m_DepthTarget) {
        RendererDX11::Get()->DeleteResource(m_DepthTarget);
        m_DepthTarget = nullptr;
    }

    if (nullptr != m_RenderTarget)
    {
        ResourceDX11* pResource = RendererDX11::Get()->GetResourceByIndex(m_RenderTarget->m_iResource);

        if (pResource->GetType() == RT_TEXTURE2D)
        {
            Texture2dDX11* pTexture = (Texture2dDX11*)pResource;
            D3D11_TEXTURE2D_DESC desc = pTexture->GetActualDescription();

            if (DepthTarget != NULL) {
                m_DepthTarget = DepthTarget;
            }
            else {
                Texture2dConfigDX11 DepthConfig;
                DepthConfig.SetDepthBuffer(desc.Width, desc.Height);
                m_DepthTarget = RendererDX11::Get()->CreateTexture2D(&DepthConfig, 0);
            }

            // 创建一个 viewport 给场景使用
            D3D11_VIEWPORT viewport;
            viewport.Width = static_cast< float >(desc.Width);
            viewport.Height = static_cast< float >(desc.Height);
            viewport.MinDepth = 0.0f;
            viewport.MaxDepth = 1.0f;
            viewport.TopLeftX = 0;
            viewport.TopLeftY = 0;

            SetViewPort(RendererDX11::Get()->CreateViewPort(viewport));
        }
    }
}

void ViewPerspective::Update(float fTime)
{
}

void ViewPerspective::QueuePreTasks(RendererDX11* pRenderer)
{
    if (m_pEntity != NULL)
    {
        Matrix4f view = m_pEntity->Transform.GetView();
        SetViewMatrix(view);
    }

    pRenderer->QueueTask(this);

    if (m_pScene)
    {
        m_pScene->PreRender(pRenderer, VT_PERSPECTIVE);
    }
}

void ViewPerspective::ExecuteTask(PipelineManagerDX11* pPipelineManager, IParameterManager* pParamManager)
{
    if (m_pScene)
    {
        pPipelineManager->ClearRenderTargets();
        pPipelineManager->OutputMergerStage.DesiredState.RenderTargetViews.SetState(0, m_RenderTarget->m_iResourceRTV);
        pPipelineManager->OutputMergerStage.DesiredState.DepthTargetViews.SetState(m_DepthTarget->m_iResourceDSV);
        pPipelineManager->ApplyRenderTargets();

        if (m_bEnableColorClear) { pPipelineManager->ClearColorBuffers(m_BufferClearColor); }
        if (m_bEnableDepthClear) { pPipelineManager->ClearDepthStencilBuffers(m_fDepthClearValue); }

        ConfigureViewports(pPipelineManager);

        SetRenderParams(pParamManager);

        //if (m_pScene->GetLightCount() > 0) {
        //    m_pScene->GetLight(0)->Parameters.SetRenderParams(pParamManager);
        //}

        pPipelineManager->ClearPipelineResources();

        std::vector<Entity3D*> entity_list;
        GetAllEntities(m_pScene->GetRoot(), entity_list);

        auto const transparent_check = [](Entity3D* entity) {
            return entity->Visual.iPass != Renderable::ALPHA;
        };

        auto const iter_first_alpha = std::stable_partition(begin(entity_list), end(entity_list), transparent_check);

        for (auto& entity : entity_list) {
            entity->Render(pPipelineManager, pParamManager, VT_PERSPECTIVE);
        }
    }
}

void ViewPerspective::Resize(UINT width, UINT height)
{
    //RendererDX11::Get()->ResizeTexture(m_DepthTarget, width, height);
    //RendererDX11::Get()->ResizeViewport(m_iViewports[0], width, height);
}

std::wstring ViewPerspective::GetName()
{
    return(L"ViewPerspective");
}