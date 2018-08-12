#include "PCH.h"
#include "EvtErrorMessage.h"

EvtErrorMessage::EvtErrorMessage(std::wstring& message)
{
    m_Message = message;
}

EvtErrorMessage::EvtErrorMessage(const wchar_t* pMessage)
{
    m_Message = std::wstring(pMessage);
}

EvtErrorMessage::~EvtErrorMessage()
{
}

std::wstring EvtErrorMessage::GetEventName()
{
    return(std::wstring(L"info_message"));
}

eEVENT EvtErrorMessage::GetEventType()
{
    return(ERROR_MESSAGE);
}

std::wstring& EvtErrorMessage::GetErrorMessage()
{
    return(m_Message);
}