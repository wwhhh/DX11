#include "PCH.h"
#include "EventManager.h"

EventManager* EventManager::m_spEventManager = 0;

EventManager::EventManager()
{
    if (!m_spEventManager)
        m_spEventManager = this;
}

EventManager::~EventManager()
{
    for (unsigned int e = 0; e < NUM_EVENTS; e++) {
        for (unsigned int i = 0; i < m_EventHandlers[e].size(); i++) {
            m_EventHandlers[e][i]->SetEventManager(nullptr);
        }
    }
}

EventManager* EventManager::Get()
{
    return(m_spEventManager);
}

bool EventManager::AddEventListener(eEVENT EventID, IEventListener* pListener)
{
    if (EventID >= NUM_EVENTS)
        return(false);

    m_EventHandlers[EventID].push_back(pListener);

    return(true);
}

bool EventManager::DelEventListener(eEVENT EventID, IEventListener* pListener)
{
    if (EventID >= NUM_EVENTS)
        return(false);

    bool bResult = false;

    int index = -1;
    for (std::vector< IEventListener* >::iterator it = m_EventHandlers[EventID].begin(); it != m_EventHandlers[EventID].end(); ++it)
    {
        if (*it == pListener)
        {
            m_EventHandlers[EventID].erase(it);
            bResult = true;
            break;
        }
    }


    return(bResult);
}

bool EventManager::ProcessEvent(EventPtr pEvent)
{
    if (!pEvent)
        return(false);

    eEVENT e = pEvent->GetEventType();
    unsigned int num = m_EventHandlers[e].size();

    bool bHandled = false;

    for (unsigned int i = 0; i < num; i++)
    {
        bHandled = m_EventHandlers[e][i]->HandleEvent(pEvent);
        if (bHandled)
            break;
    }

    return(bHandled);
}