#pragma once

#include "IController.h"
#include "../Rendering/VectorParameterWriterDX11.h"

template <typename T>
class PositionExtractorController : public IController<T>
{
public:
	PositionExtractorController( );
	virtual ~PositionExtractorController( );

	virtual void Update( float fTime );

	void SetParameterWriter( VectorParameterWriterDX11* pWriter );

protected:
	VectorParameterWriterDX11*		m_pWriter;
};

#include "PositionExtractorController.inl"