#pragma once

#include "ParameterWriter.h"

class SamplerParameterWriterDX11 : public ParameterWriter
{
public:
	SamplerParameterWriterDX11();
	virtual ~SamplerParameterWriterDX11();

	void SetRenderParameterRef( SamplerParameterDX11* pParam );
	void SetValue( int Value );

	virtual void WriteParameter( IParameterManager* pParamMgr );
	virtual void InitializeParameter( );

	virtual RenderParameterDX11* GetRenderParameterRef();

protected:
	SamplerParameterDX11*	m_pParameter;
	int						m_Value;
};