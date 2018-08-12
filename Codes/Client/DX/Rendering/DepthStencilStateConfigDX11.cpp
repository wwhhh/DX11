#include "PCH.h"
#include "DepthStencilStateConfigDX11.h"

DepthStencilStateConfigDX11::DepthStencilStateConfigDX11()
{
	SetDefaults();
}

DepthStencilStateConfigDX11::~DepthStencilStateConfigDX11()
{
}

void DepthStencilStateConfigDX11::SetDefaults()
{
	// Set the state to the default configuration.  These are the D3D11 default
	// values as well.

	DepthEnable = true;
	DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthFunc = D3D11_COMPARISON_LESS;
	StencilEnable = FALSE;
	StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
		
	FrontFace.StencilFunc			= D3D11_COMPARISON_ALWAYS;
	FrontFace.StencilPassOp			= D3D11_STENCIL_OP_KEEP;
	FrontFace.StencilFailOp			= D3D11_STENCIL_OP_KEEP;
	FrontFace.StencilDepthFailOp	= D3D11_STENCIL_OP_KEEP;
	
	BackFace.StencilFunc			= D3D11_COMPARISON_NEVER;
	BackFace.StencilPassOp			= D3D11_STENCIL_OP_KEEP;
	BackFace.StencilFailOp			= D3D11_STENCIL_OP_KEEP;
	BackFace.StencilDepthFailOp		= D3D11_STENCIL_OP_KEEP;
}