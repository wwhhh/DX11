#pragma once

#include "PCH.h"
#include "DrawExecutorDX11.h"
#include "TGrowableIndexBufferDX11.h"

template <class TVertex>
class DrawIndexedExecutorDX11 : public DrawExecutorDX11<TVertex>
{
public:
	DrawIndexedExecutorDX11( );
	virtual ~DrawIndexedExecutorDX11( );

	virtual void Execute( PipelineManagerDX11* pPipeline, IParameterManager* pParamManager );
	virtual void ResetGeometry();
	virtual void ResetIndices();

	void AddIndex( const unsigned int index );
	void AddIndices( const unsigned int i1, const unsigned int i2 );
	void AddIndices( const unsigned int i1, const unsigned int i2, const unsigned int i3 );

	unsigned int GetIndexCount();
	virtual unsigned int GetPrimitiveCount();

	void SetMaxIndexCount( unsigned int count );

protected:
	
	TGrowableIndexBufferDX11<unsigned int> IndexBuffer;
};

#include "DrawIndexedExecutorDX11.inl"