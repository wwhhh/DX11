#include "PCH.h"
#include "EvtMouseRButtonDown.h"

EvtMouseRButtonDown::EvtMouseRButtonDown( HWND hwnd, unsigned int wparam, long lparam )
: EvtMouseMsg( hwnd, wparam, lparam )
{
}

EvtMouseRButtonDown::~EvtMouseRButtonDown( )
{
}

std::wstring EvtMouseRButtonDown::GetEventName( )
{
	return( std::wstring( L"rbutton_down" ) );
}

eEVENT EvtMouseRButtonDown::GetEventType( )
{
	return( SYSTEM_RBUTTON_DOWN );
}