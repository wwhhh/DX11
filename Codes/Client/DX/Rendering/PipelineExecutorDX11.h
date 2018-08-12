#pragma once

#include "PipelineExecutorDX11.h"
#include "MaterialDX11.h"

class PipelineManagerDX11;
class IParameterManager;

struct InputLayoutKey
{
	int shader;
	int layout;
};

class PipelineExecutorDX11
{
public:
	PipelineExecutorDX11();
	virtual ~PipelineExecutorDX11();

	virtual void Execute( PipelineManagerDX11* pPipeline, IParameterManager* pParamManager ) = 0;
	
	virtual void SetLayoutElements( unsigned int count, D3D11_INPUT_ELEMENT_DESC* pElements );
	virtual void GenerateInputLayout( int ShaderID );
	virtual int GetInputLayout( int ShaderID );

protected:

	// ¶¥µãÔªËØµÄÃèÊö
	std::vector<D3D11_INPUT_ELEMENT_DESC>	m_elements;
	std::map<int,InputLayoutKey*>			m_InputLayouts;

};

typedef std::shared_ptr<PipelineExecutorDX11> ExecutorPtr;