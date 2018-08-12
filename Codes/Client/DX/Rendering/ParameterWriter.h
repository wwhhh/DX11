#pragma once

#include "RenderParameterDX11.h"
#include "IParameterManager.h"

class ParameterWriter
{
public:
	ParameterWriter();
	virtual ~ParameterWriter();

	virtual RenderParameterDX11* GetRenderParameterRef() = 0;

	// Writing a parameter directly sets the value of the referenced parameter,
	// using the provided parameter manager.  This will only be set for that
	// manager, allowing the same parameter object to be used in multiple
	// parameter managers simultaneously (allowing multi-threaded processing).
	
	virtual void WriteParameter( IParameterManager* pParamMgr ) = 0;

	// Initializing a parameter will set this writer's value into all of the
	// slots within the parameter.  Thus this should only be done at a high
	// processing level - i.e. at the scene or application level, since it 
	// will affect the value of the parameter in other parameter managers.

	virtual void InitializeParameter( ) = 0;

};