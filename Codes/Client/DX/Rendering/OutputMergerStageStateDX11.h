#pragma once

#include "PCH.h"
#include "TStateMonitor.h"
#include "TStateArrayMonitor.h"

class OutputMergerStageStateDX11
{
public:
	OutputMergerStageStateDX11();
	virtual ~OutputMergerStageStateDX11();

	void SetFeautureLevel( D3D_FEATURE_LEVEL level );
	void ClearState( );
	void SetSisterState( OutputMergerStageStateDX11* pState );
	void ResetUpdateFlags( );

	int GetRenderTargetCount() const;

	TStateMonitor< int > BlendState;
	TStateMonitor< int > DepthStencilState;
	TStateMonitor< unsigned int > StencilRef;
	TStateArrayMonitor< int, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT > RenderTargetViews;
	TStateMonitor< int > DepthTargetViews;
	TStateArrayMonitor< int, D3D11_PS_CS_UAV_REGISTER_COUNT > UnorderedAccessViews;
	TStateArrayMonitor< unsigned int, D3D11_PS_CS_UAV_REGISTER_COUNT > UAVInitialCounts;

protected:

	D3D_FEATURE_LEVEL				m_FeatureLevel;

	OutputMergerStageStateDX11*		m_pSisterState;
};