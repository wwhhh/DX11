#include "PCH.h"
#include "UnorderedAccessParameterWriterDX11.h"

UnorderedAccessParameterWriterDX11::UnorderedAccessParameterWriterDX11()
{
	m_InitCount = -1;
}

UnorderedAccessParameterWriterDX11::~UnorderedAccessParameterWriterDX11()
{
}

void UnorderedAccessParameterWriterDX11::SetRenderParameterRef( UnorderedAccessParameterDX11* pParam )
{
	m_pParameter = pParam;
}

void UnorderedAccessParameterWriterDX11::WriteParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetUnorderedAccessParameter( m_pParameter, m_Value, m_InitCount );
}

void UnorderedAccessParameterWriterDX11::SetValue( ResourcePtr Value )
{
	m_Value = Value;
}

void UnorderedAccessParameterWriterDX11::SetInitCount( unsigned int count )
{
	m_InitCount = count;
}

void UnorderedAccessParameterWriterDX11::InitializeParameter( )
{
	m_pParameter->InitializeParameterData( &m_Value->m_iResourceUAV );
}

RenderParameterDX11* UnorderedAccessParameterWriterDX11::GetRenderParameterRef()
{
	return( m_pParameter );
}

