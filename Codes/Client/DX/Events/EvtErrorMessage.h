#pragma once

#include "IEvent.h"

class EvtErrorMessage : public IEvent
{
public:
    EvtErrorMessage(std::wstring& message);
    EvtErrorMessage(const wchar_t* message);
    virtual ~EvtErrorMessage();

    virtual std::wstring GetEventName();
    virtual eEVENT GetEventType();

    std::wstring& GetErrorMessage();

protected:
    std::wstring m_Message;
};

typedef std::shared_ptr<EvtErrorMessage> EvtErrorMessagePtr;