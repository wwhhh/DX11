#pragma once

#include "PCH.h"
#include "TStateMonitor.h"
#include "TStateArrayMonitor.h"

class RasterizerStageStateDX11
{
public:
	RasterizerStageStateDX11();
	virtual ~RasterizerStageStateDX11();

	void SetFeautureLevel( D3D_FEATURE_LEVEL level );
	void ClearState( );
	void SetSisterState( RasterizerStageStateDX11* pState );
	void ResetUpdateFlags( );

	TStateMonitor< int > RasterizerState;
	TStateMonitor< int > ViewportCount;
	TStateArrayMonitor< int, D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE > Viewports;
	TStateMonitor< int > ScissorRectCount;
	TStateArrayMonitor< D3D11_RECT, D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE > ScissorRects;

protected:

	D3D_FEATURE_LEVEL				m_FeatureLevel;

	RasterizerStageStateDX11*		m_pSisterState;
};