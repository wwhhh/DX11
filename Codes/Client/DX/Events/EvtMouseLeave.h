#pragma once

#include "EvtMouseMsg.h"

class EvtMouseLeave : public EvtMouseMsg
{
public:
	EvtMouseLeave( HWND hwnd, unsigned int wparam, long lparam );
	virtual ~EvtMouseLeave( );

	virtual std::wstring GetEventName( );
	virtual eEVENT GetEventType( );
};

typedef std::shared_ptr<EvtMouseLeave> EvtMouseLeavePtr;