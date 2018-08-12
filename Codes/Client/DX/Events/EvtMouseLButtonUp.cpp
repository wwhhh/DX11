#include "PCH.h"
#include "EvtMouseLButtonUp.h"

EvtMouseLButtonUp::EvtMouseLButtonUp( HWND hwnd, unsigned int wparam, long lparam )
: EvtMouseMsg( hwnd, wparam, lparam )
{
}

EvtMouseLButtonUp::~EvtMouseLButtonUp( )
{
}

std::wstring EvtMouseLButtonUp::GetEventName( )
{
	return( std::wstring( L"lbutton_up" ) );
}

eEVENT EvtMouseLButtonUp::GetEventType( )
{
	return( SYSTEM_LBUTTON_UP );
}