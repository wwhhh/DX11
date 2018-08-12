#include "PCH.h"
#include "SamplerParameterWriterDX11.h"

SamplerParameterWriterDX11::SamplerParameterWriterDX11()
{
	m_Value = -1;
}

SamplerParameterWriterDX11::~SamplerParameterWriterDX11()
{
}

void SamplerParameterWriterDX11::SetRenderParameterRef( SamplerParameterDX11* pParam )
{
	m_pParameter = pParam;
}

void SamplerParameterWriterDX11::WriteParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetSamplerParameter( m_pParameter, &m_Value );
}

void SamplerParameterWriterDX11::SetValue( int Value )
{
	m_Value = Value;
}

void SamplerParameterWriterDX11::InitializeParameter( )
{
	m_pParameter->InitializeParameterData( &m_Value );
}

RenderParameterDX11* SamplerParameterWriterDX11::GetRenderParameterRef()
{
	return( m_pParameter );
}

