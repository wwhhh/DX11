#include "PCH.h"
#include "PixelShaderDX11.h"


PixelShaderDX11::PixelShaderDX11( ID3D11PixelShader* pShader )
{
	m_pPixelShader = pShader;
}

PixelShaderDX11::~PixelShaderDX11()
{
	SAFE_RELEASE( m_pPixelShader );
}

ShaderType PixelShaderDX11::GetType()
{
	return( PIXEL_SHADER );
}
