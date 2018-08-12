#pragma once

#include "ParameterWriter.h"

class MatrixParameterWriterDX11 : public ParameterWriter
{
public:
	MatrixParameterWriterDX11();
	virtual ~MatrixParameterWriterDX11();

	void SetRenderParameterRef( MatrixParameterDX11* pParam );
	void SetValue( const Matrix4f& Value );

	virtual void WriteParameter( IParameterManager* pParamMgr );
	virtual void InitializeParameter( );

	virtual RenderParameterDX11* GetRenderParameterRef();

protected:
	MatrixParameterDX11*			m_pParameter;
	Matrix4f						m_Value;
};