#pragma once

#include "PCH.h"
#include "ResourceProxyDX11.h"
#include "TStateMonitor.h"
#include "TStateArrayMonitor.h"

class ShaderStageStateDX11
{
public:
	ShaderStageStateDX11();
	virtual ~ShaderStageStateDX11();

	void SetFeautureLevel( D3D_FEATURE_LEVEL level );

	
	void ClearState( );

	void SetSisterState( ShaderStageStateDX11* pState );
	void ResetUpdateFlags( );

	TStateMonitor< int > ShaderProgram;
	TStateArrayMonitor< ID3D11Buffer*, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT >  ConstantBuffers;
	TStateArrayMonitor< ID3D11SamplerState*, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT > SamplerStates;
	TStateArrayMonitor< ID3D11ShaderResourceView*, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT > ShaderResourceViews;
	TStateArrayMonitor< ID3D11UnorderedAccessView*, D3D11_PS_CS_UAV_REGISTER_COUNT > UnorderedAccessViews;
	TStateArrayMonitor< unsigned int, D3D11_PS_CS_UAV_REGISTER_COUNT > UAVInitialCounts;

protected:

	D3D_FEATURE_LEVEL			m_FeatureLevel;

	ShaderStageStateDX11*		m_pSisterState;

};