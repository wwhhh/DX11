#pragma once

#include "PCH.h"
#include "ResourceProxyDX11.h"
#include "OutputMergerStageStateDX11.h"

class PipelineManagerDX11;

class OutputMergerStageDX11
{
public:
	OutputMergerStageDX11();
	virtual ~OutputMergerStageDX11();

	void SetFeautureLevel( D3D_FEATURE_LEVEL level );

	void ClearDesiredState( );
	void ClearCurrentState( );
	void ApplyDesiredRenderTargetStates( ID3D11DeviceContext* pContext );
	void ApplyDesiredBlendAndDepthStencilStates( ID3D11DeviceContext* pContext );
	void ApplyDesiredState( ID3D11DeviceContext* pContext );

	const OutputMergerStageStateDX11& GetCurrentState() const;

	// The desired state is a public member that will allow the user of this
	// class to configure the state as desired before applying the state.

	OutputMergerStageStateDX11		DesiredState;

protected:

	D3D_FEATURE_LEVEL				m_FeatureLevel;

	// The current state of the API is used to allow for caching and elimination
	// of redundant API calls.  This should make it possible to minimize the number
	// of settings that need to be performed.

	OutputMergerStageStateDX11		CurrentState;

	friend PipelineManagerDX11;
};