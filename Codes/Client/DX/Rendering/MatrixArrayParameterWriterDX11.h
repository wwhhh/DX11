#pragma once

#include "ParameterWriter.h"

class MatrixArrayParameterWriterDX11 : public ParameterWriter
{
public:
	MatrixArrayParameterWriterDX11();
	virtual ~MatrixArrayParameterWriterDX11();

	void SetRenderParameterRef( MatrixArrayParameterDX11* pParam );
	void SetValue( Matrix4f* Value );
	void SetCount( int count );

	virtual void WriteParameter( IParameterManager* pParamMgr );
	virtual void InitializeParameter( );

	virtual RenderParameterDX11* GetRenderParameterRef();

protected:
	MatrixArrayParameterDX11*		m_pParameter;
	Matrix4f*						m_pValue;
	int								m_iCount;
};