#pragma once

#include "ShaderDX11.h"
#include "PipelineManagerDX11.h"

class VertexShaderDX11 : public ShaderDX11
{
public:
	VertexShaderDX11( ID3D11VertexShader* pShader );
	virtual ~VertexShaderDX11();

	virtual ShaderType GetType();

protected:
	ID3D11VertexShader*			m_pVertexShader;

	friend VertexStageDX11;
};