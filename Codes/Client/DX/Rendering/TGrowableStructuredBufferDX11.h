#pragma once

#include "PipelineManagerDX11.h"
#include "TGrowableBufferDX11.h"

template <class T>
class TGrowableStructuredBufferDX11 : public TGrowableBufferDX11<T>
{
public:
	TGrowableStructuredBufferDX11();
	virtual ~TGrowableStructuredBufferDX11();

	virtual void UploadData( PipelineManagerDX11* pPipeline );
	virtual ResourcePtr GetBuffer();

protected:
    virtual void CreateResource( unsigned int elements );
    virtual void DeleteResource( );

private:
	ResourcePtr m_CPUBuffer;
	ResourcePtr m_GPUBuffer;
};

#include "TGrowableStructuredBufferDX11.inl"