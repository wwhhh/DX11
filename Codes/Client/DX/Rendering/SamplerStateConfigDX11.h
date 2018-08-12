#pragma once

#include "RendererDX11.h"

class SamplerStateConfigDX11 : public D3D11_SAMPLER_DESC
{
public:
	SamplerStateConfigDX11();
	~SamplerStateConfigDX11();

	void SetDefaults();

protected:

	friend RendererDX11;
};
