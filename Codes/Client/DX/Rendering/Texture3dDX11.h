#include "ResourceDX11.h"

class Texture3dDX11 : public ResourceDX11
{
public:
	explicit Texture3dDX11( Microsoft::WRL::ComPtr<ID3D11Texture3D> pTex );
	virtual ~Texture3dDX11();

	D3D11_TEXTURE3D_DESC		GetActualDescription();
	D3D11_TEXTURE3D_DESC		GetDesiredDescription();
	void						SetDesiredDescription( D3D11_TEXTURE3D_DESC description );

	virtual ResourceType				GetType();
	virtual ID3D11Resource*				GetResource();

	virtual UINT						GetEvictionPriority();
	virtual void						SetEvictionPriority( UINT EvictionPriority );

protected:
	Microsoft::WRL::ComPtr<ID3D11Texture3D>		m_pTexture;
	D3D11_TEXTURE3D_DESC						m_DesiredDesc;
	D3D11_TEXTURE3D_DESC						m_ActualDesc;

};