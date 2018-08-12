#include "PCH.h"
#include "EvtFrameStart.h"
#include "../Utils/Timer.h"

EvtFrameStart::EvtFrameStart( float dt )
{
	m_fDelta = dt;
}

EvtFrameStart::~EvtFrameStart( )
{
}

std::wstring EvtFrameStart::GetEventName( )
{
	return( std::wstring( L"frame_start" ) );
}

eEVENT EvtFrameStart::GetEventType( )
{
	return( RENDER_FRAME_START );
}

float EvtFrameStart::GetElapsed()
{
	return( m_fDelta );
}