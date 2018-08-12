#include "PCH.h"
#include "MatrixParameterWriterDX11.h"

MatrixParameterWriterDX11::MatrixParameterWriterDX11()
{
	m_Value.MakeIdentity();
}

MatrixParameterWriterDX11::~MatrixParameterWriterDX11()
{
}

void MatrixParameterWriterDX11::SetRenderParameterRef( MatrixParameterDX11* pParam )
{
	m_pParameter = pParam;
}

void MatrixParameterWriterDX11::WriteParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetMatrixParameter( m_pParameter, &m_Value );
}

void MatrixParameterWriterDX11::SetValue( const Matrix4f& Value )
{
	m_Value = Value;
}

void MatrixParameterWriterDX11::InitializeParameter( )
{
	m_pParameter->InitializeParameterData( &m_Value );
}

RenderParameterDX11* MatrixParameterWriterDX11::GetRenderParameterRef()
{
	return( m_pParameter );
}

