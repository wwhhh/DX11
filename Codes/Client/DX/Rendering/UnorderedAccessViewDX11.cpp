#include "PCH.h"
#include "UnorderedAccessViewDX11.h"

UnorderedAccessViewDX11::UnorderedAccessViewDX11( UnorderedAccessViewComPtr pView )
{
	m_pUnorderedAccessView = pView;
}

UnorderedAccessViewDX11::~UnorderedAccessViewDX11()
{
}