#include "PCH.h"
#include "PipelineExecutorDX11.h"
#include "RendererDX11.h"

PipelineExecutorDX11::PipelineExecutorDX11( )
{
}

PipelineExecutorDX11::~PipelineExecutorDX11()
{
	std::map<int, InputLayoutKey*>::iterator it = m_InputLayouts.begin();
	for( ; it != m_InputLayouts.end(); it++ )
        SAFE_DELETE( (*it).second );
}

int PipelineExecutorDX11::GetInputLayout( int ShaderID )
{
	int layout = -1;

	// 不存在的话自动生成 layout
	if ( m_InputLayouts[ShaderID] == 0 )
		GenerateInputLayout( ShaderID );
	
	layout = m_InputLayouts[ShaderID]->layout;

	return( layout );
}

void PipelineExecutorDX11::GenerateInputLayout( int ShaderID )
{
	// 为给定的 shader index 创建 input layout
	RendererDX11* pRenderer = RendererDX11::Get();
	if ( m_InputLayouts[ShaderID] == 0 )
	{
		InputLayoutKey* pKey = new InputLayoutKey();
		pKey->shader = ShaderID;
		pKey->layout = pRenderer->CreateInputLayout( m_elements, ShaderID );
		m_InputLayouts[ShaderID] = pKey;
	}
}

void PipelineExecutorDX11::SetLayoutElements( unsigned int count, D3D11_INPUT_ELEMENT_DESC* pElements )
{
	for ( unsigned int i = 0; i < count; i++ )
	{
		m_elements.push_back( pElements[i] );
	}
}