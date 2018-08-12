#pragma once

#include "ParameterWriter.h"

class UnorderedAccessParameterWriterDX11 : public ParameterWriter
{
public:
	UnorderedAccessParameterWriterDX11();
	virtual ~UnorderedAccessParameterWriterDX11();

	void SetRenderParameterRef( UnorderedAccessParameterDX11* pParam );
	void SetValue( ResourcePtr Value );
	void SetInitCount( unsigned int count );

	virtual void WriteParameter( IParameterManager* pParamMgr );
	virtual void InitializeParameter( );

	virtual RenderParameterDX11* GetRenderParameterRef();

protected:
	UnorderedAccessParameterDX11*	m_pParameter;
	ResourcePtr						m_Value;
	unsigned int					m_InitCount;
};