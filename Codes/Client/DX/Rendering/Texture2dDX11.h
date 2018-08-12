#pragma once

#include "ResourceDX11.h"

class Texture2dDX11 : public ResourceDX11
{
public:
    explicit Texture2dDX11(Microsoft::WRL::ComPtr<ID3D11Texture2D> pTex);
    virtual ~Texture2dDX11();

    D3D11_TEXTURE2D_DESC		GetActualDescription();
    D3D11_TEXTURE2D_DESC		GetDesiredDescription();
    void						SetDesiredDescription(D3D11_TEXTURE2D_DESC description);

    void						CreateTexture(void* pData);

    virtual ResourceType				GetType();
    virtual ID3D11Resource*				GetResource();

    virtual UINT						GetEvictionPriority();
    virtual void						SetEvictionPriority(UINT EvictionPriority);

protected:
    Microsoft::WRL::ComPtr<ID3D11Texture2D>			m_pTexture;
    D3D11_TEXTURE2D_DESC							m_DesiredDesc;
    D3D11_TEXTURE2D_DESC							m_ActualDesc;
};