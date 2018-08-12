#pragma once

#include "PipelineManagerDX11.h"

class DepthStencilViewDX11
{
public:
    DepthStencilViewDX11(DepthStencilViewComPtr pView);
    ~DepthStencilViewDX11();

protected:
    DepthStencilViewComPtr m_pDepthStencilView;

    friend OutputMergerStageDX11;
    friend PipelineManagerDX11;
    friend RendererDX11;
};