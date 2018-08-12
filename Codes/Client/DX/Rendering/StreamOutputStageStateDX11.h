#pragma once

#include "PCH.h"
#include "TStateMonitor.h"
#include "TStateArrayMonitor.h"

class StreamOutputStageStateDX11
{
public:
	StreamOutputStageStateDX11();
	virtual ~StreamOutputStageStateDX11();

	void SetFeautureLevel( D3D_FEATURE_LEVEL level );
	void ClearState( );
	void SetSisterState( StreamOutputStageStateDX11* pState );
	void ResetUpdateFlags( );

	int GetBufferCount() const;

	TStateArrayMonitor< int, 4 >  StreamBuffers;
	TStateArrayMonitor< unsigned int, 4 > StreamOffsets;

protected:

	D3D_FEATURE_LEVEL				m_FeatureLevel;

	StreamOutputStageStateDX11*		m_pSisterState;
};