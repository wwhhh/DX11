#pragma once

#include "ParameterWriter.h"

class ShaderResourceParameterWriterDX11 : public ParameterWriter
{
public:
	ShaderResourceParameterWriterDX11();
	virtual ~ShaderResourceParameterWriterDX11();

	void SetRenderParameterRef( ShaderResourceParameterDX11* pParam );
	void SetValue( ResourcePtr Value );

	virtual void WriteParameter( IParameterManager* pParamMgr );
	virtual void InitializeParameter( );

	virtual RenderParameterDX11* GetRenderParameterRef();

protected:
	ShaderResourceParameterDX11*	m_pParameter;
	ResourcePtr						m_Value;
};