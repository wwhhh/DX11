#include "DepthStencilViewDX11.h"

DepthStencilViewDX11::DepthStencilViewDX11(DepthStencilViewComPtr pView)
{
    m_pDepthStencilView = pView;
}

DepthStencilViewDX11::~DepthStencilViewDX11()
{
}