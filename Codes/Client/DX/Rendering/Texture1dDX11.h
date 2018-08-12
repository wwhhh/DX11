#pragma once

#include "ResourceDX11.h"

class Texture1dDX11 : public ResourceDX11
{
public:
	explicit Texture1dDX11( Microsoft::WRL::ComPtr<ID3D11Texture1D> pTex );
	virtual ~Texture1dDX11();

	D3D11_TEXTURE1D_DESC		GetActualDescription();
	D3D11_TEXTURE1D_DESC		GetDesiredDescription();
	void						SetDesiredDescription( D3D11_TEXTURE1D_DESC description );

	virtual ResourceType				GetType();
	virtual ID3D11Resource*				GetResource();

	virtual UINT						GetEvictionPriority();
	virtual void						SetEvictionPriority( UINT EvictionPriority );

protected:
	Microsoft::WRL::ComPtr<ID3D11Texture1D>			m_pTexture;
	D3D11_TEXTURE1D_DESC							m_DesiredDesc;
	D3D11_TEXTURE1D_DESC							m_ActualDesc;

};