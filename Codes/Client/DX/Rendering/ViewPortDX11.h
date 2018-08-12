#pragma once

#include "RendererDX11.h"
#include "RasterizerStageDX11.h"

class ViewPortDX11
{
public:
	ViewPortDX11();
	ViewPortDX11( D3D11_VIEWPORT viewport );
	~ViewPortDX11();

	float GetWidth() const;
	float GetHeight() const;
	Vector2f GetClipSpacePosition( const Vector2f& screen ) const;
	Vector2f GetScreenSpacePosition( const Vector2f& clip ) const;

protected:
	D3D11_VIEWPORT			m_ViewPort;

	friend RasterizerStageDX11;
	friend RendererDX11;
};