#pragma once

#include "PCH.h"
#include "Task.h"
#include "RenderEffectDX11.h"
#include "ParameterContainer.h"
#include "SceneRenderTask.h"

struct MaterialParams
{
    bool					bRender;
    RenderEffectDX11*		pEffect;
    std::vector<Task*>		Tasks;
};

class MaterialDX11
{
public:
    MaterialDX11();
    virtual ~MaterialDX11();

    void Update(float time);
    void PreRender(RendererDX11* pRenderer, VIEWTYPE type);
    void SetRenderParams(IParameterManager* pParamManager, VIEWTYPE type);

    // 返回可能用到的所有vertex shader的id，用于生成input layout
    void GetAllVertexShaderIDs(std::vector<int>& idlist);

public:
    MaterialParams				Params[VT_NUM_VIEW_TYPES];
    ParameterContainer			Parameters;
};
typedef std::shared_ptr<MaterialDX11> MaterialPtr;