#pragma once

#include "PipelineManagerDX11.h"
#include "TGrowableBufferDX11.h"

template <class T>
class TGrowableVertexBufferDX11 : public TGrowableBufferDX11<T>
{
public:
	TGrowableVertexBufferDX11();
	virtual ~TGrowableVertexBufferDX11();

	virtual void UploadData( PipelineManagerDX11* pPipeline );
	virtual ResourcePtr GetBuffer();

protected:
    virtual void CreateResource( unsigned int elements );
    virtual void DeleteResource( );

private:
	ResourcePtr m_VB;
};

#include "TGrowableVertexBufferDX11.inl"