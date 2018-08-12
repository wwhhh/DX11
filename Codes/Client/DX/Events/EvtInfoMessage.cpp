#include "PCH.h"
#include "EvtInfoMessage.h"

EvtInfoMessage::EvtInfoMessage(std::wstring& message)
{
    m_Message = message;
}

EvtInfoMessage::EvtInfoMessage(const wchar_t* pMessage)
{
    m_Message = std::wstring(pMessage);
}

EvtInfoMessage::~EvtInfoMessage()
{
}

std::wstring EvtInfoMessage::GetEventName()
{
    return(std::wstring(L"info_message"));
}

eEVENT EvtInfoMessage::GetEventType()
{
    return(INFO_MESSAGE);
}

std::wstring& EvtInfoMessage::GetInfoMessage()
{
    return(m_Message);
}