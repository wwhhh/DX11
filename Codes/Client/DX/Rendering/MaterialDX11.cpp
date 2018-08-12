#include "MaterialDX11.h"

MaterialDX11::MaterialDX11()
{
    for (int i = 0; i < VT_NUM_VIEW_TYPES; i++)
    {
        Params[i].bRender = false;
        Params[i].pEffect = nullptr;
    }
}

MaterialDX11::~MaterialDX11()
{
    for (int i = 0; i < VT_NUM_VIEW_TYPES; i++)
        SAFE_DELETE(Params[i].pEffect);
}

void MaterialDX11::Update(float time)
{
    for (int i = 0; i < VT_NUM_VIEW_TYPES; i++)
    {
        if (Params[i].bRender)
        {
            for (auto pView : Params[i].Tasks)
                pView->Update(time);
        }
    }
}

void MaterialDX11::PreRender(RendererDX11* pRenderer, VIEWTYPE type)
{
    //## Update the render views that are needed before a view of 'type' can be
    // processed.  We will always try to update the view, but it may limit if it
    // is updated based on the maximum recurrence allowed. 

    for (auto pView : Params[type].Tasks)
        pView->QueuePreTasks(pRenderer);
}

void MaterialDX11::SetRenderParams(IParameterManager* pParamManager, VIEWTYPE type)
{
    // 当前渲染 pass 所需要的参数
    for (auto pView : Params[type].Tasks)
        pView->SetUsageParams(pParamManager);

    // 设置与渲染类型无关的额外的渲染参数
    Parameters.SetRenderParams(pParamManager);
}

void MaterialDX11::GetAllVertexShaderIDs(std::vector<int>& idlist)
{
    for (unsigned int i = 0; i < VT_NUM_VIEW_TYPES; i++)
    {
        if (Params[i].pEffect != nullptr)
        {
            int ID = Params[i].pEffect->GetVertexShader();

            if (ID != -1)
                idlist.push_back(ID);
        }
    }
}