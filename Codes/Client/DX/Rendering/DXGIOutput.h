#pragma once

#include "PCH.h"

class DXGIOutput
{
public:
	DXGIOutput( Microsoft::WRL::ComPtr<IDXGIOutput> pOutput );
	virtual ~DXGIOutput();

protected:
	Microsoft::WRL::ComPtr<IDXGIOutput>	m_pOutput;

	friend class RendererDX11;
};