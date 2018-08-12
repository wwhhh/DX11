#pragma once

#include "RendererDX11.h"

class RasterizerStateConfigDX11 : public D3D11_RASTERIZER_DESC
{
public:
	RasterizerStateConfigDX11();
	~RasterizerStateConfigDX11();

	void SetDefaults();

protected:

	friend RendererDX11;
};

inline bool operator==(const RasterizerStateConfigDX11& lhs, const RasterizerStateConfigDX11& rhs)
{
	return
		lhs.AntialiasedLineEnable == rhs.AntialiasedLineEnable &&
		lhs.CullMode == rhs.CullMode &&
		lhs.DepthBias == rhs.DepthBias &&
		lhs.DepthBiasClamp == rhs.DepthBiasClamp &&
		lhs.DepthClipEnable == rhs.DepthClipEnable &&
		lhs.FillMode == rhs.FillMode &&
		lhs.FrontCounterClockwise == rhs.FrontCounterClockwise &&
		lhs.MultisampleEnable == rhs.MultisampleEnable &&
		lhs.ScissorEnable == rhs.ScissorEnable &&
		lhs.SlopeScaledDepthBias == rhs.SlopeScaledDepthBias;
}

inline bool operator<(const RasterizerStateConfigDX11& lhs, const RasterizerStateConfigDX11& rhs)
{
	return memcmp(&lhs, &rhs, sizeof(lhs) ) < 0;
	//return
	//	lhs.AntialiasedLineEnable < rhs.AntialiasedLineEnable ||
	//	lhs.CullMode < rhs.CullMode ||
	//	lhs.DepthBias < rhs.DepthBias ||
	//	lhs.DepthBiasClamp < rhs.DepthBiasClamp ||
	//	lhs.DepthClipEnable < rhs.DepthClipEnable ||
	//	lhs.FillMode < rhs.FillMode ||
	//	lhs.FrontCounterClockwise < rhs.FrontCounterClockwise ||
	//	lhs.MultisampleEnable < rhs.MultisampleEnable ||
	//	lhs.ScissorEnable < rhs.ScissorEnable ||
	//	lhs.SlopeScaledDepthBias < rhs.SlopeScaledDepthBias;
}