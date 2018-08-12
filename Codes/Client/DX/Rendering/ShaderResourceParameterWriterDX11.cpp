#include "PCH.h"
#include "ShaderResourceParameterWriterDX11.h"

ShaderResourceParameterWriterDX11::ShaderResourceParameterWriterDX11()
{
}

ShaderResourceParameterWriterDX11::~ShaderResourceParameterWriterDX11()
{
}

void ShaderResourceParameterWriterDX11::SetRenderParameterRef( ShaderResourceParameterDX11* pParam )
{
	m_pParameter = pParam;
}

void ShaderResourceParameterWriterDX11::WriteParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetShaderResourceParameter( m_pParameter, m_Value );
}

void ShaderResourceParameterWriterDX11::SetValue( ResourcePtr Value )
{
	m_Value = Value;
}

void ShaderResourceParameterWriterDX11::InitializeParameter( )
{
	m_pParameter->InitializeParameterData( &m_Value->m_iResourceSRV );
}

RenderParameterDX11* ShaderResourceParameterWriterDX11::GetRenderParameterRef()
{
	return( m_pParameter );
}

