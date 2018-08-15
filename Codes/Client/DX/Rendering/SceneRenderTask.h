#pragma once

#include "Task.h"

class Entity3D;
class Scene;
class BoundsVisualizerActor;

enum VIEWTYPE
{
    VT_INVALID,
    VT_PERSPECTIVE,
    VT_LINEAR_DEPTH_NORMAL,
    VT_DUAL_PARABOLOID_ENVMAP,
    VT_GBUFFER,
    VT_LIGHTS,
    VT_FINALPASS,
    VT_SILHOUETTE,
    VT_NUM_VIEW_TYPES
};

class SceneRenderTask : public Task
{
public:

    SceneRenderTask();
    virtual ~SceneRenderTask();

    virtual void Resize(UINT width, UINT height) = 0;

    virtual void SetRenderParams(IParameterManager* pParamManager);
    virtual void SetUsageParams(IParameterManager* pParamManager);

    virtual void SetEntity(Entity3D* pEntity);

    virtual void SetScene(Scene* pScene);

    void SetViewPort(int viewport, unsigned int index = 0);
    void SetViewPortCount(unsigned int count);
    void ConfigureViewports(PipelineManagerDX11* pPipeline);
    const ViewPortDX11& GetViewPort(unsigned int index);


    virtual void SetColorClearValue(const Vector4f& color);
    virtual void SetDepthClearValue(const float depth);
    virtual void SetStencilClearValue(const UINT stencil);

    virtual void EnableColorClearing(const bool enable);
    virtual void EnableDepthClearing(const bool enable);

    virtual void SetViewMatrix(const Matrix4f& matrix);
    virtual void SetProjMatrix(const Matrix4f& matrix);
    Matrix4f GetViewMatrix();
    Matrix4f GetProjMatrix();

    void SetDebugViewEnabled(bool debug);
    bool IsDebugViewEnabled();

protected:

    Entity3D * m_pEntity;
    Scene* m_pScene;

    Vector4f		m_BufferClearColor;
    float			m_fDepthClearValue;
    UINT			m_uiStencilClearValue;
    bool			m_bEnableColorClear;
    bool			m_bEnableDepthClear;

    int				m_iViewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
    unsigned int	m_uiViewportCount;

    Matrix4f ViewMatrix;
    Matrix4f ProjMatrix;
};