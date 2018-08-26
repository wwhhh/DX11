#include "TextureLoader.h"
#include "RendererDX11.h"

TextureLoader* TextureLoader::m_pTextLoader = nullptr;

TextureLoader* TextureLoader::Get()
{
    if (m_pTextLoader == 0)
    {
        m_pTextLoader = new TextureLoader();
    }

    return m_pTextLoader;
}

ResourcePtr TextureLoader::LoadTexture(std::wstring name)
{
    if (m_Textures.size() > 0)
    {
        std::map<const wchar_t*, ResourcePtr>::iterator iter = m_Textures.begin();
        while (iter != m_Textures.end())
        {
            if (name.compare(iter->first) == 0)
            {
                return iter->second;
            }
            iter++;
        }
    }

    ResourcePtr res = RendererDX11::Get()->LoadTexture(name);
    m_Textures.insert(std::pair<const wchar_t*, ResourcePtr>(name.c_str(), res));
    return m_Textures[name.c_str()];
}