#pragma once

#include "SceneRenderTask.h"

class ViewPerspective : public SceneRenderTask
{
public:
    ViewPerspective(RendererDX11& Renderer, ResourcePtr RenderTarget, ResourcePtr DepthTarget);
    ~ViewPerspective();

    virtual void Update(float fTime);
    virtual void QueuePreTasks(RendererDX11* pRenderer);
    virtual void ExecuteTask(PipelineManagerDX11* pPipelineManager, IParameterManager* pParamManager);
    virtual void Resize(UINT width, UINT height);

    void SetRenderTargets(ResourcePtr RenderTarget, ResourcePtr DepthTarget = nullptr);

    virtual std::wstring GetName();

protected:

    ResourcePtr		m_RenderTarget;
    ResourcePtr		m_DepthTarget;
};