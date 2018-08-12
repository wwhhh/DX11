#pragma once

#include "PipelineManagerDX11.h"

class RenderTargetViewDX11
{
public:
    RenderTargetViewDX11(RenderTargetViewComPtr pView);
    ~RenderTargetViewDX11();

    ID3D11RenderTargetView* GetRTV();

protected:
    RenderTargetViewComPtr m_pRenderTargetView;

    friend OutputMergerStageDX11;
    friend PipelineManagerDX11;
    friend RendererDX11;
};