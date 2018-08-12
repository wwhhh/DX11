#pragma once

#include "RenderParameterDX11.h"

struct UAVParameterData
{
	int				m_iUnorderedAccessView;
	unsigned int	m_iInitialCount;
};

class UnorderedAccessParameterDX11 : public RenderParameterDX11
{
public:
	UnorderedAccessParameterDX11();
	UnorderedAccessParameterDX11( UnorderedAccessParameterDX11& copy );
	virtual ~UnorderedAccessParameterDX11();

	virtual void SetParameterData( void* pData, unsigned int threadID = 0 );
	//virtual void ResetParameterData( void* pData, unsigned int threadID = 0 );

	virtual const ParameterType GetParameterType();
	int GetIndex( unsigned int threadID );
	unsigned int GetInitialCount( unsigned int threadID );

	//void UpdateValue( RenderParameterDX11* pParameter, unsigned int threadID = 0 );

protected:
	UAVParameterData m_ParameterData[NUM_THREADS+1];
};