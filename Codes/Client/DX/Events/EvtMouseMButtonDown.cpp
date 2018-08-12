#include "PCH.h"
#include "EvtMouseMButtonDown.h"

EvtMouseMButtonDown::EvtMouseMButtonDown( HWND hwnd, unsigned int wparam, long lparam )
: EvtMouseMsg( hwnd, wparam, lparam )
{
}

EvtMouseMButtonDown::~EvtMouseMButtonDown( )
{
}

std::wstring EvtMouseMButtonDown::GetEventName( )
{
	return( std::wstring( L"mbutton_down" ) );
}

eEVENT EvtMouseMButtonDown::GetEventType( )
{
	return( SYSTEM_MBUTTON_DOWN );
}