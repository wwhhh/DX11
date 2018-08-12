#pragma once

#include "IEvent.h"

class EvtInfoMessage : public IEvent
{
public:
    EvtInfoMessage(std::wstring& message);
    EvtInfoMessage(const wchar_t* message);
    virtual ~EvtInfoMessage();

    virtual std::wstring GetEventName();
    virtual eEVENT GetEventType();

    std::wstring& GetInfoMessage();

protected:
    std::wstring m_Message;
};

typedef std::shared_ptr<EvtInfoMessage> EvtInfoMessagePtr;