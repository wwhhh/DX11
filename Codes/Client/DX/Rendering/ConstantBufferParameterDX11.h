#pragma once

#include "RenderParameterDX11.h"

class ConstantBufferParameterDX11 : public RenderParameterDX11
{
public:
	ConstantBufferParameterDX11();
	ConstantBufferParameterDX11( ConstantBufferParameterDX11& copy );
	virtual ~ConstantBufferParameterDX11();

	virtual void SetParameterData( void* pData, unsigned int threadID = 0 );
	//virtual void ResetParameterData( void* pData, unsigned int threadID = 0 );

	virtual const ParameterType GetParameterType();

	//virtual void UpdateValue( RenderParameterDX11* pParameter, unsigned int threadID = 0 );

	int GetIndex( unsigned int threadID );

protected:
	int		m_iCBuffer[NUM_THREADS+1];
};
