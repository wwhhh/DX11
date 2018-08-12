#include "PCH.h"
#include "RenderTargetViewDX11.h"

RenderTargetViewDX11::RenderTargetViewDX11(RenderTargetViewComPtr pView)
{
    m_pRenderTargetView = pView;
}

RenderTargetViewDX11::~RenderTargetViewDX11()
{
}

ID3D11RenderTargetView* RenderTargetViewDX11::GetRTV()
{
    return(m_pRenderTargetView.Get());
}