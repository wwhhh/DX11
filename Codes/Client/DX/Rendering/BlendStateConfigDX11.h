#pragma once

#include "RendererDX11.h"

class BlendStateConfigDX11 : public D3D11_BLEND_DESC
{
public:
	BlendStateConfigDX11();
	~BlendStateConfigDX11();

	void SetDefaults();

protected:

	friend RendererDX11;
};

// Global comparison operators

inline bool operator==(const BlendStateConfigDX11& lhs, const BlendStateConfigDX11& rhs)
{
	bool result = false;

	for ( size_t index = 0; index < 8; index++ )
	{
		result = result &&
			lhs.RenderTarget[index].BlendEnable == rhs.RenderTarget[index].BlendEnable &&
			lhs.RenderTarget[index].BlendOp == rhs.RenderTarget[index].BlendOp &&
			lhs.RenderTarget[index].BlendOpAlpha == rhs.RenderTarget[index].BlendOpAlpha &&
			lhs.RenderTarget[index].DestBlend == rhs.RenderTarget[index].DestBlend &&
			lhs.RenderTarget[index].DestBlendAlpha == rhs.RenderTarget[index].DestBlendAlpha &&
			lhs.RenderTarget[index].RenderTargetWriteMask == rhs.RenderTarget[index].RenderTargetWriteMask &&
			lhs.RenderTarget[index].SrcBlend == rhs.RenderTarget[index].SrcBlend &&
			lhs.RenderTarget[index].SrcBlendAlpha == rhs.RenderTarget[index].SrcBlendAlpha;
	}

	result = result && 
		lhs.AlphaToCoverageEnable == rhs.AlphaToCoverageEnable &&
		lhs.IndependentBlendEnable == rhs.IndependentBlendEnable;

	return result;
}

inline bool operator<(const BlendStateConfigDX11& lhs, const BlendStateConfigDX11& rhs)
{
	return memcmp( &lhs, &rhs, sizeof(lhs) ) < 0;
	bool result = false;

	for ( size_t index = 0; index < 8; index++ )
	{
		result = result ||
			lhs.RenderTarget[index].BlendEnable < rhs.RenderTarget[index].BlendEnable ||
			lhs.RenderTarget[index].BlendOp < rhs.RenderTarget[index].BlendOp ||
			lhs.RenderTarget[index].BlendOpAlpha < rhs.RenderTarget[index].BlendOpAlpha ||
			lhs.RenderTarget[index].DestBlend < rhs.RenderTarget[index].DestBlend ||
			lhs.RenderTarget[index].DestBlendAlpha < rhs.RenderTarget[index].DestBlendAlpha ||
			lhs.RenderTarget[index].RenderTargetWriteMask < rhs.RenderTarget[index].RenderTargetWriteMask ||
			lhs.RenderTarget[index].SrcBlend < rhs.RenderTarget[index].SrcBlend ||
			lhs.RenderTarget[index].SrcBlendAlpha < rhs.RenderTarget[index].SrcBlendAlpha;
	}

	result = result ||
		lhs.AlphaToCoverageEnable < rhs.AlphaToCoverageEnable ||
		lhs.IndependentBlendEnable < rhs.IndependentBlendEnable;

	return result;
}