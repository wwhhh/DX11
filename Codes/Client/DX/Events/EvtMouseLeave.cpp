#include "PCH.h"
#include "EvtMouseLeave.h"

EvtMouseLeave::EvtMouseLeave(  HWND hwnd, unsigned int wparam, long lparam  )
: EvtMouseMsg( hwnd, wparam, lparam )
{
}

EvtMouseLeave::~EvtMouseLeave( )
{
}

std::wstring EvtMouseLeave::GetEventName( )
{
	return( std::wstring( L"mouse_leave" ) );
}

eEVENT EvtMouseLeave::GetEventType( )
{
	return( SYSTEM_MOUSE_LEAVE );
}