#include "PCH.h"
#include "EvtMouseMButtonUp.h"

EvtMouseMButtonUp::EvtMouseMButtonUp( HWND hwnd, unsigned int wparam, long lparam )
: EvtMouseMsg( hwnd, wparam, lparam )
{
}

EvtMouseMButtonUp::~EvtMouseMButtonUp( )
{
}

std::wstring EvtMouseMButtonUp::GetEventName( )
{
	return( std::wstring( L"mbutton_up" ) );
}

eEVENT EvtMouseMButtonUp::GetEventType( )
{
	return( SYSTEM_MBUTTON_UP );
}