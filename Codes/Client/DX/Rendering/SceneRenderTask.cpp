#include "PCH.h"
#include "SceneRenderTask.h"
#include "Events/EventManager.h"
#include "Objects/Entity3D.h"
#include "Objects/Node3D.h"
#include "Utils/Log.h"

SceneRenderTask::SceneRenderTask() :
    m_pEntity(nullptr),
    m_pScene(nullptr),
    m_iViewports(),
    m_uiViewportCount(1),
    ViewMatrix(),
    ProjMatrix(),
    m_BufferClearColor(0.0f, 0.0f, 0.0f, 1.0f),
    m_fDepthClearValue(1.0f),
    m_uiStencilClearValue(0),
    m_bEnableColorClear(true),
    m_bEnableDepthClear(true)
{
    ViewMatrix.MakeIdentity();
    ProjMatrix.MakeIdentity();
}

SceneRenderTask::~SceneRenderTask()
{
    
}

void SceneRenderTask::SetRenderParams(IParameterManager* pParamManager)
{
    pParamManager->SetViewMatrixParameter(&ViewMatrix);
    pParamManager->SetProjMatrixParameter(&ProjMatrix);
}

void SceneRenderTask::SetUsageParams(IParameterManager* pParamManager)
{

}

void SceneRenderTask::SetEntity(Entity3D* pEntity)
{
    m_pEntity = pEntity;
}

void SceneRenderTask::SetScene(Scene* pScene)
{
    m_pScene = pScene;
}

void SceneRenderTask::SetViewMatrix(const Matrix4f& matrix)
{
    ViewMatrix = matrix;
}

Matrix4f SceneRenderTask::GetViewMatrix()
{
    return(ViewMatrix);
}

void SceneRenderTask::SetProjMatrix(const Matrix4f& matrix)
{
    ProjMatrix = matrix;
}

Matrix4f SceneRenderTask::GetProjMatrix()
{
    return(ProjMatrix);
}

void SceneRenderTask::SetColorClearValue(const Vector4f& color)
{
    m_BufferClearColor = color;
}

void SceneRenderTask::SetDepthClearValue(const float depth)
{
    m_fDepthClearValue = depth;
}

void SceneRenderTask::SetStencilClearValue(const UINT stencil)
{
    m_uiStencilClearValue = stencil;
}

void SceneRenderTask::EnableColorClearing(const bool enable)
{
    m_bEnableColorClear = enable;
}

void SceneRenderTask::EnableDepthClearing(const bool enable)
{
    m_bEnableDepthClear = enable;
}

void SceneRenderTask::SetViewPort(int viewport, unsigned int index)
{
    assert(index < D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE);

    m_iViewports[index] = viewport;
}

void SceneRenderTask::SetViewPortCount(unsigned int count)
{
    assert(count < D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE);

    m_uiViewportCount = count;
}

void SceneRenderTask::ConfigureViewports(PipelineManagerDX11* pPipeline)
{

    pPipeline->RasterizerStage.DesiredState.ViewportCount.SetState(m_uiViewportCount);

    for (unsigned int i = 0; i < m_uiViewportCount; i++) {
        pPipeline->RasterizerStage.DesiredState.Viewports.SetState(i, m_iViewports[i]);
    }
}

const ViewPortDX11& SceneRenderTask::GetViewPort(unsigned int index)
{
    assert(index < m_uiViewportCount);

    return(RendererDX11::Get()->GetViewPort(m_iViewports[index]));
}