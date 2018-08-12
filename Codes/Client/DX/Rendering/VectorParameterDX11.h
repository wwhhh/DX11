#pragma once

#include "RenderParameterDX11.h"
#include "Maths/Vector4f.h"

class VectorParameterDX11 : public RenderParameterDX11
{
public:
	VectorParameterDX11();
	VectorParameterDX11( VectorParameterDX11& copy );
	virtual ~VectorParameterDX11();

	virtual void SetParameterData( void* pData, unsigned int threadID = 0 );
	//virtual void ResetParameterData( void* pData, unsigned int threadID = 0 );
	virtual const ParameterType GetParameterType();
	
	Vector4f GetVector( unsigned int threadID = 0 );
	void SetVector( Vector4f v, unsigned int threadID = 0 );

	//void UpdateValue( RenderParameterDX11* pParameter, unsigned int threadID = 0 );

protected:
	Vector4f	m_Vector[NUM_THREADS+1];
};