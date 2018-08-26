#pragma once

#include "PCH.h"
#include "SpriteFontDX11.h"

class SpriteFontLoaderDX11
{

public:

	SpriteFontLoaderDX11();
	~SpriteFontLoaderDX11();

	static SpriteFontPtr LoadFont( std::wstring& fontName, float fontSize, UINT fontStyle, bool antiAliased );

protected:

	static std::vector< SpriteFontPtr > FontList;
};