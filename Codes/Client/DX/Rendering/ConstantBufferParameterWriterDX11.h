#pragma once

#include "ParameterWriter.h"

class ConstantBufferParameterWriterDX11 : public ParameterWriter
{
public:
	ConstantBufferParameterWriterDX11();
	virtual ~ConstantBufferParameterWriterDX11();

	void SetRenderParameterRef( ConstantBufferParameterDX11* pParam );
	void SetValue( ResourcePtr Value );

	virtual void WriteParameter( IParameterManager* pParamMgr );
	virtual void InitializeParameter( );

	virtual RenderParameterDX11* GetRenderParameterRef();

protected:
	ConstantBufferParameterDX11*	m_pParameter;
	ResourcePtr						m_Value;
};