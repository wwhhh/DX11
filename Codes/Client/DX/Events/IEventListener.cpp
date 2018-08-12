#pragma once

#include "PCH.h"
#include "../Utils//Log.h"
#include "IEventListener.h"
#include "EventManager.h"

using namespace Utils;

IEventListener::IEventListener()
    :m_pEventManager(nullptr)
{
}

IEventListener::~IEventListener()
{
    SetEventManager(nullptr);
}

void IEventListener::RequestEvent(eEVENT e)
{
    bool bAlreadyRequested = false;

    for (auto requested : m_RequestedEvents)
    {
        if (requested == e)
            bAlreadyRequested = true;
    }

    if (bAlreadyRequested)
    {
        Log::Get().Write(L"WARNING: Trying to request an event that has already been added!!!");
    }
    else {
        m_RequestedEvents.push_back(e);

        if (m_pEventManager) {
            m_pEventManager->AddEventListener(e, this);
        }
    }

}

void IEventListener::UnRequestEvent(eEVENT e) 
{
    for (std::vector<eEVENT>::iterator it = m_RequestedEvents.begin(); it != m_RequestedEvents.end(); ++it)
    {
        if (*it == e)
        {
            it = m_RequestedEvents.erase(it);
        }
    }

    if (m_pEventManager)
    {
        m_pEventManager->DelEventListener(e, this);
    }
}

void IEventListener::SetEventManager(EventManager* pEventManager)
{
    if (m_pEventManager)
    {
        for (auto e : m_RequestedEvents)
        {
            m_pEventManager->DelEventListener(e, this);
        }
    }

    m_pEventManager = pEventManager;

    if (m_pEventManager)
    {
        for (auto e : m_RequestedEvents)
        {
            m_pEventManager->AddEventListener(e, this);
        }
    }
}