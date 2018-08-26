#pragma once

#include "ShaderDX11.h"

class IParameterManager;

class RenderEffectDX11
{
public:
	RenderEffectDX11();
	virtual ~RenderEffectDX11();

	void SetVertexShader( int index );
	void SetHullShader( int index );
	void SetDomainShader( int index );
	void SetGeometryShader( int index );
	void SetPixelShader( int index );
	void SetComputeShader( int index );

	int GetVertexShader( );
	int GetHullShader( );
	int GetDomainShader( );
	int GetGeometryShader( );
	int GetPixelShader( );
	int GetComputeShader( );

	void ConfigurePipeline( PipelineManagerDX11* pPipeline, IParameterManager* pParamManager );

	int		m_iBlendState;
	int		m_iDepthStencilState;
	int		m_iRasterizerState;
    UINT    m_uStencilRef; 

protected:

	void UpdateConstantBufferList( );

	int					m_aiIndices[6];
	ShaderDX11*			m_apShaders[6];

	std::vector< RenderParameterDX11* > m_uniqueConstBuffers;
};