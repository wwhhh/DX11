#pragma once

#include "EvtMouseMsg.h"

class EvtMouseRButtonDown : public EvtMouseMsg
{
public:
	EvtMouseRButtonDown( HWND hwnd, unsigned int wparam, long lparam );
	virtual ~EvtMouseRButtonDown( );

	virtual std::wstring GetEventName( );
	virtual eEVENT GetEventType( );
};

typedef std::shared_ptr<EvtMouseRButtonDown> EvtMouseRButtonDownPtr;