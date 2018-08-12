#include "PCH.h"
#include "ShaderDX11.h"

ShaderDX11::ShaderDX11() :
	FileName(),
	Function(),
	ShaderModel(),
	ShaderText(),
	m_pCompiledShader( nullptr ),
	m_pReflection( nullptr )
{
}

ShaderDX11::~ShaderDX11()
{
	SAFE_RELEASE( m_pCompiledShader );
	SAFE_DELETE( m_pReflection );
}

void ShaderDX11::SetReflection( ShaderReflectionDX11* pReflection )
{
	m_pReflection = pReflection;
}

ShaderReflectionDX11* ShaderDX11::GetReflection( )
{
	return( m_pReflection );
}

std::wstring ShaderDX11::ToString()
{
	std::wstringstream s;

	s << L"[" << FileName << L"][" << Function << L"][" << ShaderModel << L"]";

	return( s.str() );
}

