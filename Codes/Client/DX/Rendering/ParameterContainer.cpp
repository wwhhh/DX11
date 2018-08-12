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
	// 存储传递进来的指针

	if ( pWriter )
	{
		// 遍历判断是否已存在
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

	// 判断写入类是否存在.
	pWriter = GetRenderParameter( name );

	if ( nullptr != pWriter )
	{
		// 获取参数，然后判断类型
		RenderParameterDX11* pParameter = pWriter->GetRenderParameterRef();

		if ( nullptr != pParameter )
		{
			// 类型正确的话，设置值
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

	// 判断写入类是否存在.
	pWriter = GetRenderParameter( name );

	if ( nullptr != pWriter )
	{
		// 获取参数，然后判断类型
		RenderParameterDX11* pParameter = pWriter->GetRenderParameterRef();

		if ( nullptr != pParameter )
		{
			// 类型正确的话，设置值
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

	// 判断写入类是否存在.
	pWriter = GetRenderParameter( name );

	if ( nullptr != pWriter )
	{
		// 获取参数，然后判断类型
		RenderParameterDX11* pParameter = pWriter->GetRenderParameterRef();

		if ( nullptr != pParameter )
		{
			// 类型正确的话，设置值
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

	// 判断写入类是否存在.
	pWriter = GetRenderParameter( name );

	if ( nullptr != pWriter )
	{
		// 获取参数，然后判断类型
		RenderParameterDX11* pParameter = pWriter->GetRenderParameterRef();

		if ( nullptr != pParameter )
		{
			// 类型正确的话，设置值
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

	// 判断写入类是否存在.
	pWriter = GetRenderParameter( name );

	if ( nullptr != pWriter )
	{
		// 获取参数，然后判断类型
		RenderParameterDX11* pParameter = pWriter->GetRenderParameterRef();

		if ( nullptr != pParameter )
		{
			// 类型正确的话，设置值
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

	// 判断写入类是否存在.
	pWriter = GetRenderParameter( name );

	if ( nullptr != pWriter )
	{
		// 获取参数，然后判断类型
		RenderParameterDX11* pParameter = pWriter->GetRenderParameterRef();

		if ( nullptr != pParameter )
		{
			// 类型正确的话，设置值
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

	// 判断写入类是否存在.
	pWriter = GetRenderParameter( name );

	if ( nullptr != pWriter )
	{
		// 获取参数，然后判断类型
		RenderParameterDX11* pParameter = pWriter->GetRenderParameterRef();

		if ( nullptr != pParameter )
		{
			// 类型正确的话，设置值
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
	// 遍历所有的写入类，然后写入参数
	for ( auto pParamWriter : m_RenderParameters )
		pParamWriter->WriteParameter( pParamManager );
}

void ParameterContainer::InitRenderParams( )
{
	// 遍历所有的写入类，初始化值
	for ( auto pParamWriter : m_RenderParameters )
		pParamWriter->InitializeParameter( );
}

ConstantBufferParameterWriterDX11* ParameterContainer::SetConstantBufferParameter( const std::wstring& name, const ResourcePtr& value )
{
	// 判断写入类是否存在
	ConstantBufferParameterWriterDX11* pConstantBufferWriter = GetConstantBufferParameterWriter( name );

	// 如果不存在，创建一个
	if ( nullptr == pConstantBufferWriter ) {
		pConstantBufferWriter = new ConstantBufferParameterWriterDX11();
		pConstantBufferWriter->SetRenderParameterRef( RendererDX11::Get()->m_pParamMgr->GetConstantBufferParameterRef( name ) );
		AddRenderParameter( pConstantBufferWriter );
	}

	// 设置参数
	pConstantBufferWriter->SetValue( value );

	return( pConstantBufferWriter );
}

MatrixArrayParameterWriterDX11* ParameterContainer::SetMatrixArrayParameter( const std::wstring& name, Matrix4f* values, int count )
{
	// 判断写入类是否存在
	MatrixArrayParameterWriterDX11* pMatrixArrayWriter = GetMatrixArrayParameterWriter( name );

	// 如果不存在，创建一个
	if ( nullptr == pMatrixArrayWriter ) {
		pMatrixArrayWriter = new MatrixArrayParameterWriterDX11();
		pMatrixArrayWriter->SetRenderParameterRef( RendererDX11::Get()->m_pParamMgr->GetMatrixArrayParameterRef( name, count ) );
		AddRenderParameter( pMatrixArrayWriter );
	}

	// 设置参数
	pMatrixArrayWriter->SetValue( values );

	return( pMatrixArrayWriter );
}

MatrixParameterWriterDX11* ParameterContainer::SetMatrixParameter( const std::wstring& name, const Matrix4f& value )
{
	// 判断写入类是否存在
	MatrixParameterWriterDX11* pMatrixWriter = GetMatrixParameterWriter( name );

	// 如果不存在，创建一个
	if ( nullptr == pMatrixWriter ) {
		pMatrixWriter = new MatrixParameterWriterDX11();
		pMatrixWriter->SetRenderParameterRef( RendererDX11::Get()->m_pParamMgr->GetMatrixParameterRef( name ) );
		AddRenderParameter( pMatrixWriter );
	}

	// 设置参数
	pMatrixWriter->SetValue( value );

	return( pMatrixWriter );
}

SamplerParameterWriterDX11* ParameterContainer::SetSamplerParameter( const std::wstring& name, int value )
{
	// 判断写入类是否存在
	SamplerParameterWriterDX11* pSamplerWriter = GetSamplerParameterWriter( name );

	// 如果不存在，创建一个
	if ( nullptr == pSamplerWriter ) {
		pSamplerWriter = new SamplerParameterWriterDX11();
		pSamplerWriter->SetRenderParameterRef( RendererDX11::Get()->m_pParamMgr->GetSamplerStateParameterRef( name ) );
		AddRenderParameter( pSamplerWriter );
	}

	// 设置参数
	pSamplerWriter->SetValue( value );

	return( pSamplerWriter );
}

ShaderResourceParameterWriterDX11* ParameterContainer::SetShaderResourceParameter( const std::wstring& name, const ResourcePtr& value )
{
	// 判断写入类是否存在
	ShaderResourceParameterWriterDX11* pShaderResourceWriter = GetShaderResourceParameterWriter( name );

	// 如果不存在，创建一个
	if ( nullptr == pShaderResourceWriter ) {
		pShaderResourceWriter = new ShaderResourceParameterWriterDX11();
		pShaderResourceWriter->SetRenderParameterRef( RendererDX11::Get()->m_pParamMgr->GetShaderResourceParameterRef( name ) );
		AddRenderParameter( pShaderResourceWriter );
	}

	// 设置参数
	pShaderResourceWriter->SetValue( value );

	return( pShaderResourceWriter );
}

UnorderedAccessParameterWriterDX11* ParameterContainer::SetUnorderedAccessParameter( const std::wstring& name, const ResourcePtr& value )
{
	// 判断写入类是否存在
	UnorderedAccessParameterWriterDX11* pUnorderedAccessWriter = GetUnorderedAccessParameterWriter( name );

	// 如果不存在，创建一个
	if ( nullptr == pUnorderedAccessWriter ) {
		pUnorderedAccessWriter = new UnorderedAccessParameterWriterDX11();
		pUnorderedAccessWriter->SetRenderParameterRef( RendererDX11::Get()->m_pParamMgr->GetUnorderedAccessParameterRef( name ) );
		AddRenderParameter( pUnorderedAccessWriter );
	}

	// 设置参数
	pUnorderedAccessWriter->SetValue( value );

	return( pUnorderedAccessWriter );
}

VectorParameterWriterDX11* ParameterContainer::SetVectorParameter( const std::wstring& name, const Vector4f& value )
{
	// 判断写入类是否存在
	VectorParameterWriterDX11* pVectorWriter = GetVectorParameterWriter( name );

	// 如果不存在，创建一个
	if ( nullptr == pVectorWriter ) {
		pVectorWriter = new VectorParameterWriterDX11();
		pVectorWriter->SetRenderParameterRef( RendererDX11::Get()->m_pParamMgr->GetVectorParameterRef( name ) );
		AddRenderParameter( pVectorWriter );
	}

	// 设置参数
	pVectorWriter->SetValue( value );

	return( pVectorWriter );
}

