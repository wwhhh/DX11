#pragma once

#include "PCH.h"
#include "ConstantBufferParameterWriterDX11.h"
#include "MatrixArrayParameterWriterDX11.h"
#include "MatrixParameterWriterDX11.h"
#include "SamplerParameterWriterDX11.h"
#include "ShaderResourceParameterWriterDX11.h"
#include "UnorderedAccessParameterWriterDX11.h"
#include "VectorParameterWriterDX11.h"

class ParameterContainer
{
public:
	ParameterContainer( );
	virtual ~ParameterContainer( );

	// ���һ������д����
	void AddRenderParameter( ParameterWriter* pWriter );

	// ȡ��һ������д����
    // TODO: û�еĻ�����nullptr
	ParameterWriter* GetRenderParameter( const std::wstring& name );
	ConstantBufferParameterWriterDX11* GetConstantBufferParameterWriter( const std::wstring& name );
	MatrixArrayParameterWriterDX11* GetMatrixArrayParameterWriter( const std::wstring& name );
	MatrixParameterWriterDX11* GetMatrixParameterWriter( const std::wstring& name );
	SamplerParameterWriterDX11* GetSamplerParameterWriter( const std::wstring& name );
	ShaderResourceParameterWriterDX11* GetShaderResourceParameterWriter( const std::wstring& name );
	UnorderedAccessParameterWriterDX11* GetUnorderedAccessParameterWriter( const std::wstring& name );
	VectorParameterWriterDX11* GetVectorParameterWriter( const std::wstring& name );

	// �������з����Զ����ò���
	ConstantBufferParameterWriterDX11* SetConstantBufferParameter( const std::wstring& name, const ResourcePtr& value );
	MatrixArrayParameterWriterDX11* SetMatrixArrayParameter( const std::wstring& name, Matrix4f* values, int count );
	MatrixParameterWriterDX11* SetMatrixParameter( const std::wstring& name, const Matrix4f& value );
	SamplerParameterWriterDX11* SetSamplerParameter( const std::wstring& name, int value );
	ShaderResourceParameterWriterDX11* SetShaderResourceParameter( const std::wstring& name, const ResourcePtr& value );
	UnorderedAccessParameterWriterDX11* SetUnorderedAccessParameter( const std::wstring& name, const ResourcePtr& value );
	VectorParameterWriterDX11* SetVectorParameter( const std::wstring& name, const Vector4f& value );

	// ����ǰ���������еĲ������õ�������������
	void SetRenderParams( IParameterManager* pParamManager );
	void InitRenderParams( );

protected:

	std::vector< ParameterWriter* > m_RenderParameters;
};