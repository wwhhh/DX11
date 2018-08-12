#pragma once

#include "PCH.h"
#include "IEvent.h"
#include "IEventListener.h"

class EventManager
{
public:
    EventManager();
    virtual ~EventManager();

    bool AddEventListener(eEVENT EventID, IEventListener* pListener);
    bool DelEventListener(eEVENT EventID, IEventListener* pListener);

    bool ProcessEvent(EventPtr pEvent);

    static EventManager* Get();

private:
    std::vector< IEventListener* > m_EventHandlers[NUM_EVENTS];

    static EventManager* m_spEventManager;
};