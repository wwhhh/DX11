#pragma once

#include "ShaderStageDX11.h"

class GeometryStageDX11 : public ShaderStageDX11
{
public:
	GeometryStageDX11();
	virtual ~GeometryStageDX11();

protected:
	virtual ShaderType GetType();

	virtual void BindShaderProgram( ID3D11DeviceContext* );
	virtual void BindConstantBuffers( ID3D11DeviceContext* pContext, int count );
	virtual void BindSamplerStates( ID3D11DeviceContext* pContext, int count );
	virtual void BindShaderResourceViews( ID3D11DeviceContext* pContext, int count );
	virtual void BindUnorderedAccessViews( ID3D11DeviceContext* pContext, int count );
};