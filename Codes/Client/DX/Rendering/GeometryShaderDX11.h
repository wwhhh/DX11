#pragma once

#include "ShaderDX11.h"
#include "PipelineManagerDX11.h"

class GeometryShaderDX11 : public ShaderDX11
{
public:
	GeometryShaderDX11( ID3D11GeometryShader* pShader );
	virtual ~GeometryShaderDX11();

	virtual ShaderType GetType();

protected:
	ID3D11GeometryShader*			m_pGeometryShader;

	friend GeometryStageDX11;
};