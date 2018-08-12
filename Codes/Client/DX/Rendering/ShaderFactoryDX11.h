#pragma once

#include "PCH.h"
#include "ShaderDX11.h"

class ShaderFactoryDX11
{
public:
	~ShaderFactoryDX11();

	static ID3DBlob* GenerateShader( ShaderType type, std::wstring& filename, std::wstring& function,
        std::wstring& model, const D3D_SHADER_MACRO* pDefines, bool enablelogging = true );

	static ID3DBlob* GeneratePrecompiledShader( std::wstring& filename, std::wstring& function,
        std::wstring& model );

private:
	ShaderFactoryDX11();
};