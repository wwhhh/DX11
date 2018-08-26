#pragma once

#include "PipelineManagerDX11.h"
#include "TGrowableBufferDX11.h"

template <class T>
class TGrowableIndexBufferDX11 : public TGrowableBufferDX11<T>
{
public:
	TGrowableIndexBufferDX11();
	virtual ~TGrowableIndexBufferDX11();

	virtual void UploadData( PipelineManagerDX11* pPipeline );
	virtual ResourcePtr GetBuffer();

protected:
    virtual void CreateResource( unsigned int elements );
    virtual void DeleteResource( );

private:
	ResourcePtr m_IB;
};

#include "TGrowableIndexBufferDX11.inl"