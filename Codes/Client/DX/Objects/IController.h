#pragma once

#include "Utils/Timer.h"
#include <vector>

template <typename T>
class IController
{
public:
    IController();
    virtual ~IController();
    virtual void Update(float fTime) = 0;

    void SetEntity(T* pObject);
    T* GetEntity();

protected:
    T * m_pEntity;
};

template <typename T>
class ControllerPack
{
public:
    ControllerPack(T* host) : m_host(host) {};

    ~ControllerPack() {
        for (auto pController : m_Controllers)
            delete pController;
    };

    void Attach(IController<T>* pController) {
        if (pController) {
            m_Controllers.push_back(pController);
            pController->SetEntity(m_host);
        }
    };

    IController<T>* Get(unsigned int index) {
        if (m_Controllers.size() <= index)
            return(nullptr);

        return m_Controllers[index];
    };

    void Update(float time) {
        for (auto pController : m_Controllers) {
            pController->Update(time);
        }
    }

private:
    T * m_host;
    std::vector< IController<T>* > m_Controllers;
};

#include "IController.inl"