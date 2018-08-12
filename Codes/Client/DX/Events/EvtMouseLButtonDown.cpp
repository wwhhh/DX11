#include "PCH.h"
#include "EvtMouseLButtonDown.h"

EvtMouseLButtonDown::EvtMouseLButtonDown( HWND hwnd, unsigned int wparam, long lparam )
: EvtMouseMsg( hwnd, wparam, lparam )
{
}

EvtMouseLButtonDown::~EvtMouseLButtonDown( )
{
}

std::wstring EvtMouseLButtonDown::GetEventName( )
{
	return( std::wstring( L"lbutton_down" ) );
}

eEVENT EvtMouseLButtonDown::GetEventType( )
{
	return( SYSTEM_LBUTTON_DOWN );
}