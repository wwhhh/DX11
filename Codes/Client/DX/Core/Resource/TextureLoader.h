#pragma once

#include <map>
#include "Rendering/ResourceProxyDX11.h"

class TextureLoader
{
public:
    ResourcePtr LoadTexture(std::wstring name);

    static TextureLoader* Get();

private:
    TextureLoader() {}
    ~TextureLoader() {}

    static TextureLoader* m_pTextLoader;

    std::map<const wchar_t*, ResourcePtr> m_Textures;
};