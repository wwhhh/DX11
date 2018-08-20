#pragma once

#include "GeometryDX11.h"
#include <string>

class GeometryLoaderDX11
{
public:	
	static GeometryPtr loadMS3DFile2( std::wstring filename );		

    static GeometryPtr loadObj(std::wstring filename);

private:
	GeometryLoaderDX11();
};