#pragma once

#include "PipelineManagerDX11.h"

class ShaderResourceViewDX11
{
public:
	ShaderResourceViewDX11( ShaderResourceViewComPtr pView );
	~ShaderResourceViewDX11();

	ID3D11ShaderResourceView* GetSRV();

protected:
	ShaderResourceViewComPtr		m_pShaderResourceView;

    friend OutputMergerStageDX11;
    friend PipelineManagerDX11;
    friend RendererDX11;
};