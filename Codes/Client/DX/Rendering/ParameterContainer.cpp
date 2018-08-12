#include "PCH.h"
#include "ParameterContainer.h"
#include "Utils/Log.h"
#include "RenderParameterDX11.h"
#include "IParameterManager.h"

using namespace Utils;

ParameterContainer::ParameterContainer()
{
}

ParameterContainer::~ParameterContainer()
{
	for ( auto pParameter : m_RenderParameters )
		delete pParameter;
}

void ParameterContainer::AddRenderParameter( ParameterWriter* pWriter )
{
	// �洢���ݽ�����ָ��

	if ( pWriter )
	{
		// �����ж��Ƿ��Ѵ���
		ParameterWriter* pCurr = 0;

		for ( unsigned int i = 0; i < m_RenderParameters.size(); i++ )
		{
			if ( pWriter->GetRenderParameterRef()->GetName() == m_RenderParameters[i]->GetRenderParameterRef()->GetName() )
			{
				pCurr = m_RenderParameters[i];
				break;
			}
		}

		if ( !pCurr )
		{
			m_RenderParameters.push_back( pWriter );
		}
		else
		{
			Log::Get().Write( L"Tried to add a parameter to an entity that was already there!" );
		}
	}
}

ParameterWriter* ParameterContainer::GetRenderParameter( const std::wstring& name )
{
	ParameterWriter* pResult = nullptr;

	for ( auto pParameterWriter : m_RenderParameters )
	{
		RenderParameterDX11* pParameter = pParameterWriter->GetRenderParameterRef();
		if ( pParameter != nullptr ) {
			if ( name.compare( pParameter->GetName() ) == 0 ) {
				pResult = pParameterWriter;
				break;
			}
		}
	}

	return( pResult );
}

ConstantBufferParameterWriterDX11* ParameterContainer::GetConstantBufferParameterWriter( const std::wstring& name )
{
	ParameterWriter* pWriter = nullptr;
	ConstantBufferParameterWriterDX11* pConstantBufferWriter = nullptr;

	// �ж�д�����Ƿ����.
	pWriter = GetRenderParameter( name );

	if ( nullptr != pWriter )
	{
		// ��ȡ������Ȼ���ж�����
		RenderParameterDX11* pParameter = pWriter->GetRenderParameterRef();

		if ( nullptr != pParameter )
		{
			// ������ȷ�Ļ�������ֵ
			if ( pParameter->GetParameterType() == CBUFFER ) {
				pConstantBufferWriter = dynamic_cast<ConstantBufferParameterWriterDX11*>( pWriter );
			} else {
				Log::Get().Write( L"ERROR: Trying to access a constant buffer in a non-CB parameter writer!!!" );
			}
		} else {
			Log::Get().Write( L"ERROR: Trying to access a parameter writer without any reference set!!!" );
		}
	}

	return( pConstantBufferWriter );
}

MatrixArrayParameterWriterDX11* ParameterContainer::GetMatrixArrayParameterWriter( const std::wstring& name )
{
	ParameterWriter* pWriter = nullptr;
	MatrixArrayParameterWriterDX11* pMatrixArrayWriter = nullptr;

	// �ж�д�����Ƿ����.
	pWriter = GetRenderParameter( name );

	if ( nullptr != pWriter )
	{
		// ��ȡ������Ȼ���ж�����
		RenderParameterDX11* pParameter = pWriter->GetRenderParameterRef();

		if ( nullptr != pParameter )
		{
			// ������ȷ�Ļ�������ֵ
			if ( pParameter->GetParameterType() == MATRIX_ARRAY ) {
				pMatrixArrayWriter = dynamic_cast<MatrixArrayParameterWriterDX11*>( pWriter );
			} else {
				Log::Get().Write( L"ERROR: Trying to access a matrix array in a non-matrix array parameter writer!!!" );
			}
		} else {
			Log::Get().Write( L"ERROR: Trying to access a parameter writer without any reference set!!!" );
		}
	}

	return( pMatrixArrayWriter );
}

MatrixParameterWriterDX11* ParameterContainer::GetMatrixParameterWriter( const std::wstring& name )
{
	ParameterWriter* pWriter = nullptr;
	MatrixParameterWriterDX11* pMatrixWriter = nullptr;

	// �ж�д�����Ƿ����.
	pWriter = GetRenderParameter( name );

	if ( nullptr != pWriter )
	{
		// ��ȡ������Ȼ���ж�����
		RenderParameterDX11* pParameter = pWriter->GetRenderParameterRef();

		if ( nullptr != pParameter )
		{
			// ������ȷ�Ļ�������ֵ
			if ( pParameter->GetParameterType() == MATRIX ) {
				pMatrixWriter = dynamic_cast<MatrixParameterWriterDX11*>( pWriter );
			} else {
				Log::Get().Write( L"ERROR: Trying to access a matrix in a non-matrix parameter writer!!!" );
			}
		} else {
			Log::Get().Write( L"ERROR: Trying to access a parameter writer without any reference set!!!" );
		}
	}

	return( pMatrixWriter );
}

SamplerParameterWriterDX11* ParameterContainer::GetSamplerParameterWriter( const std::wstring& name )
{
	ParameterWriter* pWriter = nullptr;
	SamplerParameterWriterDX11* pSamplerWriter = nullptr;

	// �ж�д�����Ƿ����.
	pWriter = GetRenderParameter( name );

	if ( nullptr != pWriter )
	{
		// ��ȡ������Ȼ���ж�����
		RenderParameterDX11* pParameter = pWriter->GetRenderParameterRef();

		if ( nullptr != pParameter )
		{
			// ������ȷ�Ļ�������ֵ
			if ( pParameter->GetParameterType() == SAMPLER ) {
				pSamplerWriter = dynamic_cast<SamplerParameterWriterDX11*>( pWriter );
			} else {
				Log::Get().Write( L"ERROR: Trying to access a sampler in a non-sampler parameter writer!!!" );
			}
		} else {
			Log::Get().Write( L"ERROR: Trying to access a parameter writer without any reference set!!!" );
		}
	}

	return( pSamplerWriter );
}

ShaderResourceParameterWriterDX11* ParameterContainer::GetShaderResourceParameterWriter( const std::wstring& name )
{
	ParameterWriter* pWriter = nullptr;
	ShaderResourceParameterWriterDX11* pShaderResourceWriter = nullptr;

	// �ж�д�����Ƿ����.
	pWriter = GetRenderParameter( name );

	if ( nullptr != pWriter )
	{
		// ��ȡ������Ȼ���ж�����
		RenderParameterDX11* pParameter = pWriter->GetRenderParameterRef();

		if ( nullptr != pParameter )
		{
			// ������ȷ�Ļ�������ֵ
			if ( pParameter->GetParameterType() == SHADER_RESOURCE ) {
				pShaderResourceWriter = dynamic_cast<ShaderResourceParameterWriterDX11*>( pWriter );
			} else {
				Log::Get().Write( L"ERROR: Trying to access a shader resource in a non-shader resource parameter writer!!!" );
			}
		} else {
			Log::Get().Write( L"ERROR: Trying to access a parameter writer without any reference set!!!" );
		}
	}

	return( pShaderResourceWriter );
}

UnorderedAccessParameterWriterDX11* ParameterContainer::GetUnorderedAccessParameterWriter( const std::wstring& name )
{
	ParameterWriter* pWriter = nullptr;
	UnorderedAccessParameterWriterDX11* pUnorderedAccessWriter = nullptr;

	// �ж�д�����Ƿ����.
	pWriter = GetRenderParameter( name );

	if ( nullptr != pWriter )
	{
		// ��ȡ������Ȼ���ж�����
		RenderParameterDX11* pParameter = pWriter->GetRenderParameterRef();

		if ( nullptr != pParameter )
		{
			// ������ȷ�Ļ�������ֵ
			if ( pParameter->GetParameterType() == UNORDERED_ACCESS ) {
				pUnorderedAccessWriter = dynamic_cast<UnorderedAccessParameterWriterDX11*>( pWriter );
			} else {
				Log::Get().Write( L"ERROR: Trying to access a unordered access view in a non-UAV parameter writer!!!" );
			}
		} else {
			Log::Get().Write( L"ERROR: Trying to access a parameter writer without any reference set!!!" );
		}
	}

	return( pUnorderedAccessWriter );
}

VectorParameterWriterDX11* ParameterContainer::GetVectorParameterWriter( const std::wstring& name )
{
	ParameterWriter* pWriter = nullptr;
	VectorParameterWriterDX11* pVectorWriter = nullptr;

	// �ж�д�����Ƿ����.
	pWriter = GetRenderParameter( name );

	if ( nullptr != pWriter )
	{
		// ��ȡ������Ȼ���ж�����
		RenderParameterDX11* pParameter = pWriter->GetRenderParameterRef();

		if ( nullptr != pParameter )
		{
			// ������ȷ�Ļ�������ֵ
			if ( pParameter->GetParameterType() == VECTOR) {
				pVectorWriter = dynamic_cast<VectorParameterWriterDX11*>( pWriter );
			} else {
				Log::Get().Write( L"ERROR: Trying to access a vector in a non-vector parameter writer!!!" );
			}
		} else {
			Log::Get().Write( L"ERROR: Trying to access a parameter writer without any reference set!!!" );
		}
	}

	return( pVectorWriter );
}

void ParameterContainer::SetRenderParams( IParameterManager* pParamManager )
{
	// �������е�д���࣬Ȼ��д�����
	for ( auto pParamWriter : m_RenderParameters )
		pParamWriter->WriteParameter( pParamManager );
}

void ParameterContainer::InitRenderParams( )
{
	// �������е�д���࣬��ʼ��ֵ
	for ( auto pParamWriter : m_RenderParameters )
		pParamWriter->InitializeParameter( );
}

ConstantBufferParameterWriterDX11* ParameterContainer::SetConstantBufferParameter( const std::wstring& name, const ResourcePtr& value )
{
	// �ж�д�����Ƿ����
	ConstantBufferParameterWriterDX11* pConstantBufferWriter = GetConstantBufferParameterWriter( name );

	// ��������ڣ�����һ��
	if ( nullptr == pConstantBufferWriter ) {
		pConstantBufferWriter = new ConstantBufferParameterWriterDX11();
		pConstantBufferWriter->SetRenderParameterRef( RendererDX11::Get()->m_pParamMgr->GetConstantBufferParameterRef( name ) );
		AddRenderParameter( pConstantBufferWriter );
	}

	// ���ò���
	pConstantBufferWriter->SetValue( value );

	return( pConstantBufferWriter );
}

MatrixArrayParameterWriterDX11* ParameterContainer::SetMatrixArrayParameter( const std::wstring& name, Matrix4f* values, int count )
{
	// �ж�д�����Ƿ����
	MatrixArrayParameterWriterDX11* pMatrixArrayWriter = GetMatrixArrayParameterWriter( name );

	// ��������ڣ�����һ��
	if ( nullptr == pMatrixArrayWriter ) {
		pMatrixArrayWriter = new MatrixArrayParameterWriterDX11();
		pMatrixArrayWriter->SetRenderParameterRef( RendererDX11::Get()->m_pParamMgr->GetMatrixArrayParameterRef( name, count ) );
		AddRenderParameter( pMatrixArrayWriter );
	}

	// ���ò���
	pMatrixArrayWriter->SetValue( values );

	return( pMatrixArrayWriter );
}

MatrixParameterWriterDX11* ParameterContainer::SetMatrixParameter( const std::wstring& name, const Matrix4f& value )
{
	// �ж�д�����Ƿ����
	MatrixParameterWriterDX11* pMatrixWriter = GetMatrixParameterWriter( name );

	// ��������ڣ�����һ��
	if ( nullptr == pMatrixWriter ) {
		pMatrixWriter = new MatrixParameterWriterDX11();
		pMatrixWriter->SetRenderParameterRef( RendererDX11::Get()->m_pParamMgr->GetMatrixParameterRef( name ) );
		AddRenderParameter( pMatrixWriter );
	}

	// ���ò���
	pMatrixWriter->SetValue( value );

	return( pMatrixWriter );
}

SamplerParameterWriterDX11* ParameterContainer::SetSamplerParameter( const std::wstring& name, int value )
{
	// �ж�д�����Ƿ����
	SamplerParameterWriterDX11* pSamplerWriter = GetSamplerParameterWriter( name );

	// ��������ڣ�����һ��
	if ( nullptr == pSamplerWriter ) {
		pSamplerWriter = new SamplerParameterWriterDX11();
		pSamplerWriter->SetRenderParameterRef( RendererDX11::Get()->m_pParamMgr->GetSamplerStateParameterRef( name ) );
		AddRenderParameter( pSamplerWriter );
	}

	// ���ò���
	pSamplerWriter->SetValue( value );

	return( pSamplerWriter );
}

ShaderResourceParameterWriterDX11* ParameterContainer::SetShaderResourceParameter( const std::wstring& name, const ResourcePtr& value )
{
	// �ж�д�����Ƿ����
	ShaderResourceParameterWriterDX11* pShaderResourceWriter = GetShaderResourceParameterWriter( name );

	// ��������ڣ�����һ��
	if ( nullptr == pShaderResourceWriter ) {
		pShaderResourceWriter = new ShaderResourceParameterWriterDX11();
		pShaderResourceWriter->SetRenderParameterRef( RendererDX11::Get()->m_pParamMgr->GetShaderResourceParameterRef( name ) );
		AddRenderParameter( pShaderResourceWriter );
	}

	// ���ò���
	pShaderResourceWriter->SetValue( value );

	return( pShaderResourceWriter );
}

UnorderedAccessParameterWriterDX11* ParameterContainer::SetUnorderedAccessParameter( const std::wstring& name, const ResourcePtr& value )
{
	// �ж�д�����Ƿ����
	UnorderedAccessParameterWriterDX11* pUnorderedAccessWriter = GetUnorderedAccessParameterWriter( name );

	// ��������ڣ�����һ��
	if ( nullptr == pUnorderedAccessWriter ) {
		pUnorderedAccessWriter = new UnorderedAccessParameterWriterDX11();
		pUnorderedAccessWriter->SetRenderParameterRef( RendererDX11::Get()->m_pParamMgr->GetUnorderedAccessParameterRef( name ) );
		AddRenderParameter( pUnorderedAccessWriter );
	}

	// ���ò���
	pUnorderedAccessWriter->SetValue( value );

	return( pUnorderedAccessWriter );
}

VectorParameterWriterDX11* ParameterContainer::SetVectorParameter( const std::wstring& name, const Vector4f& value )
{
	// �ж�д�����Ƿ����
	VectorParameterWriterDX11* pVectorWriter = GetVectorParameterWriter( name );

	// ��������ڣ�����һ��
	if ( nullptr == pVectorWriter ) {
		pVectorWriter = new VectorParameterWriterDX11();
		pVectorWriter->SetRenderParameterRef( RendererDX11::Get()->m_pParamMgr->GetVectorParameterRef( name ) );
		AddRenderParameter( pVectorWriter );
	}

	// ���ò���
	pVectorWriter->SetValue( value );

	return( pVectorWriter );
}

