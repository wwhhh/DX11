#include "PCH.h"
#include "GeometryShaderDX11.h"

GeometryShaderDX11::GeometryShaderDX11( ID3D11GeometryShader* pShader )
{
	m_pGeometryShader = pShader;
}

GeometryShaderDX11::~GeometryShaderDX11()
{
	SAFE_RELEASE( m_pGeometryShader );
}

ShaderType GeometryShaderDX11::GetType()
{
	return( GEOMETRY_SHADER );
}