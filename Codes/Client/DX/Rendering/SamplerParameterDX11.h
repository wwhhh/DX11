#pragma once

#include "RenderParameterDX11.h"

class SamplerParameterDX11 : public RenderParameterDX11
{
public:
	SamplerParameterDX11();
	SamplerParameterDX11( SamplerParameterDX11& copy );
	virtual ~SamplerParameterDX11();

	virtual void SetParameterData( void* pData, unsigned int threadID = 0 );
	//virtual void ResetParameterData( void* pData, unsigned int threadID = 0 );

	virtual const ParameterType GetParameterType();
	int GetIndex( unsigned int threadID );

	//void UpdateValue( RenderParameterDX11* pParameter, unsigned int threadID = 0 );

protected:
	int		m_iSampler[NUM_THREADS+1];
};