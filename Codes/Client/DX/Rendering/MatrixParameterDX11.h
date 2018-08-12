#pragma once

#include "RenderParameterDX11.h"
#include "Maths/Matrix4f.h"

class MatrixParameterDX11 : public RenderParameterDX11
{
public:
	MatrixParameterDX11();
	MatrixParameterDX11( MatrixParameterDX11& copy );
	virtual ~MatrixParameterDX11();

	virtual void SetParameterData( void* pData, unsigned int threadID = 0 );
	//virtual void ResetParameterData( void* pData, unsigned int threadID = 0 );

	virtual const ParameterType GetParameterType();
	Matrix4f GetMatrix( unsigned int threadID = 0);

	//void UpdateValue( RenderParameterDX11* pParameter, unsigned int threadID = 0 );

protected:
	Matrix4f	m_Matrix[NUM_THREADS+1];
};