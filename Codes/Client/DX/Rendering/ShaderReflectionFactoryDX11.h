#pragma once

#include "PCH.h"
#include "ShaderDX11.h"
#include "ShaderReflectionDX11.h"

class ShaderReflectionFactoryDX11
{
public:
	~ShaderReflectionFactoryDX11();

	static ShaderReflectionDX11* GenerateReflection( ShaderDX11& shader );

private:
	ShaderReflectionFactoryDX11();
};