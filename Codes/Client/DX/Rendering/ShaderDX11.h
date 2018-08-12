#pragma once

#include "PCH.h"
#include "ShaderReflectionDX11.h"

class ShaderDX11
{
public:
	ShaderDX11();
	virtual ~ShaderDX11();

	virtual ShaderType GetType() = 0;
	

	void SetReflection( ShaderReflectionDX11* pReflection );
	ShaderReflectionDX11* GetReflection( );

	std::wstring ToString();

public:
	std::wstring							FileName;
	std::wstring							Function;
	std::wstring							ShaderModel;
	std::string								ShaderText;
	ID3DBlob*								m_pCompiledShader;
	ShaderReflectionDX11*					m_pReflection;
};