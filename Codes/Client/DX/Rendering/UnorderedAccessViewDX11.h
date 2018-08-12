#pragma once

#include "PipelineManagerDX11.h"

class UnorderedAccessViewDX11
{
public:
	UnorderedAccessViewDX11( UnorderedAccessViewComPtr pView );
	~UnorderedAccessViewDX11();

protected:
	UnorderedAccessViewComPtr			m_pUnorderedAccessView;

    friend OutputMergerStageDX11;
    friend PipelineManagerDX11;
    friend RendererDX11;
};