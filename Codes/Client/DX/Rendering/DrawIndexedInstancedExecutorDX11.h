#pragma once

#include "PCH.h"
#include "DrawIndexedExecutorDX11.h"

template <class TVertex, class TInstance>
class DrawIndexedInstancedExecutorDX11 : public DrawIndexedExecutorDX11<TVertex>
{
public:
	DrawIndexedInstancedExecutorDX11( );
	virtual ~DrawIndexedInstancedExecutorDX11( );

	virtual void Execute( PipelineManagerDX11* pPipeline, IParameterManager* pParamManager );
	virtual void ResetGeometry();
	virtual void ResetInstances();

	void AddInstance( const TInstance& data );
	unsigned int GetInstanceCount();

	void SetInstanceRange( unsigned int start, unsigned int end );

protected:
	
	TGrowableVertexBufferDX11<TInstance> InstanceBuffer;
	unsigned int m_uiStart;
	unsigned int m_uiCount;
};

#include "DrawIndexedInstancedExecutorDX11.inl"