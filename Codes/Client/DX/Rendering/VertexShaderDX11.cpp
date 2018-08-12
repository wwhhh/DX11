#include "PCH.h"
#include "VertexShaderDX11.h"

VertexShaderDX11::VertexShaderDX11( ID3D11VertexShader* pShader )
{
	m_pVertexShader = pShader;
}

VertexShaderDX11::~VertexShaderDX11()
{
	SAFE_RELEASE( m_pVertexShader );
}

ShaderType VertexShaderDX11::GetType()
{
	return( VERTEX_SHADER );
}