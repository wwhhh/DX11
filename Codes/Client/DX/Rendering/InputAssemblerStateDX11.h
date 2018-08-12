#pragma once

#include "PCH.h"
#include "TStateMonitor.h"
#include "TStateArrayMonitor.h"

class InputAssemblerStateDX11
{
public:
	InputAssemblerStateDX11();
	virtual ~InputAssemblerStateDX11();

	void SetFeautureLevel( D3D_FEATURE_LEVEL level );
	void ClearState( );
	void SetSisterState( InputAssemblerStateDX11* pState );
	void ResetUpdateFlags( );

	unsigned int GetAvailableSlotCount();

	TStateMonitor< int > IndexBuffer;
	TStateMonitor< DXGI_FORMAT > IndexBufferFormat;
	TStateArrayMonitor< int, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT > VertexBuffers;
	TStateArrayMonitor< unsigned int, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT > VertexBufferStrides;
	TStateArrayMonitor< unsigned int, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT > VertexBufferOffsets;
	TStateMonitor< int > InputLayout;
	TStateMonitor< D3D11_PRIMITIVE_TOPOLOGY > PrimitiveTopology;

protected:

	D3D_FEATURE_LEVEL				m_FeatureLevel;

	InputAssemblerStateDX11*		m_pSisterState;

	unsigned int					AvailableSlotCount;
};