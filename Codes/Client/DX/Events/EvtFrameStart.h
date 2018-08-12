#pragma once

#include "IEvent.h"

class Timer;

class EvtFrameStart : public IEvent
{
public:
	EvtFrameStart( float dt );
	virtual ~EvtFrameStart( );

	virtual std::wstring GetEventName( );
	virtual eEVENT GetEventType( );

	float GetElapsed();

protected:
	float m_fDelta;
};

typedef std::shared_ptr<EvtFrameStart> EvtFrameStartPtr;