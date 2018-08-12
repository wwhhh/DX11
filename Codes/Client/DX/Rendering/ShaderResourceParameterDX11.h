#pragma once

#include "RenderParameterDX11.h"

class ShaderResourceParameterDX11 : public RenderParameterDX11
{
public:
	ShaderResourceParameterDX11();
	ShaderResourceParameterDX11( ShaderResourceParameterDX11& copy );
	virtual ~ShaderResourceParameterDX11();

	virtual void SetParameterData( void* pData, unsigned int threadID = 0 );
	//virtual void ResetParameterData( void* pData, unsigned int threadID = 0 );

	virtual const ParameterType GetParameterType();
	int GetIndex( unsigned int threadID );

	//void UpdateValue( RenderParameterDX11* pParameter, unsigned int threadID = 0 );

protected:
	int		m_iShaderResourceView[NUM_THREADS+1];
};