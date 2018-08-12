#pragma once

#include "ShaderDX11.h"
#include "PipelineManagerDX11.h"

class PixelShaderDX11 : public ShaderDX11
{
public:
	PixelShaderDX11( ID3D11PixelShader* pShader );
	virtual ~PixelShaderDX11();

	virtual ShaderType GetType();

protected:
	ID3D11PixelShader*			m_pPixelShader;

	friend PixelStageDX11;
};