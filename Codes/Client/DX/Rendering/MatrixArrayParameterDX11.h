#pragma once

#include "RenderParameterDX11.h"
#include "Maths/Matrix4f.h"

class MatrixArrayParameterDX11 : public RenderParameterDX11
{
public:
	MatrixArrayParameterDX11( int count );
	MatrixArrayParameterDX11( MatrixArrayParameterDX11& copy );
	MatrixArrayParameterDX11& operator=( MatrixArrayParameterDX11& parameter );
	virtual ~MatrixArrayParameterDX11();

	virtual void SetParameterData( void* pData, unsigned int threadID = 0 );
	//virtual void ResetParameterData( void* pData, unsigned int threadID = 0 );

	virtual const ParameterType GetParameterType();
	int GetMatrixCount();
	Matrix4f* GetMatrices( unsigned int threadID = 0 );

	//void UpdateValue( RenderParameterDX11* pParameter, unsigned int threadID = 0 );

protected:
	int				m_iMatrixCount;
	Matrix4f*		m_pMatrices[NUM_THREADS+1];
};