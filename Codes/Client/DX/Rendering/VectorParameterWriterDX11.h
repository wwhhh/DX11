#pragma once

#include "ParameterWriter.h"

class VectorParameterWriterDX11 : public ParameterWriter
{
public:
	VectorParameterWriterDX11();
	virtual ~VectorParameterWriterDX11();

	void SetRenderParameterRef( VectorParameterDX11* pParam );
	void SetValue( const Vector4f& Value );
	Vector4f GetValue();

	virtual void WriteParameter( IParameterManager* pParamMgr );
	virtual void InitializeParameter( );

	virtual RenderParameterDX11* GetRenderParameterRef();

protected:
	VectorParameterDX11*			m_pParameter;
	Vector4f						m_Value;
};