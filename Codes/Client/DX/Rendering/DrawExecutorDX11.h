#pragma once

#include "PCH.h"
#include "PipelineExecutorDX11.h"
#include "TGrowableVertexBufferDX11.h"

template <class TVertex>
class DrawExecutorDX11 : public PipelineExecutorDX11
{
public:
	DrawExecutorDX11( );
	virtual ~DrawExecutorDX11( );

	virtual void Execute( PipelineManagerDX11* pPipeline, IParameterManager* pParamManager );
	virtual void ResetGeometry();
	virtual void ResetVertices();

	void AddVertex( const TVertex& vertex );

	D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveType();
	void SetPrimitiveType( D3D11_PRIMITIVE_TOPOLOGY type );

	unsigned int GetVertexCount();
	virtual unsigned int GetPrimitiveCount();

	void SetMaxVertexCount( unsigned int count );

protected:

	// The type of primitives listed in the index buffer
	D3D11_PRIMITIVE_TOPOLOGY m_ePrimType;

	// Use a growable vertex buffer to hold the vertex data.
	TGrowableVertexBufferDX11<TVertex> VertexBuffer;
};

#include "DrawExecutorDX11.inl"