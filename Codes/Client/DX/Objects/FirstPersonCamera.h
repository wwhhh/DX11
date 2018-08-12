#pragma once

#include "Camera.h"
#include "Utils/Timer.h"

class FirstPersonCamera : public Camera
{
public:
    FirstPersonCamera();
	virtual ~FirstPersonCamera();
    
    virtual bool HandleEvent( EventPtr pEvent );
    virtual std::wstring GetName();

protected:

    void Update();        

    enum ControlKeys
    {
        ForwardKey = 0,
        BackKey,
        LeftKey,
        RightKey,
        UpKey,
        DownKey,
        SpeedUpKey,

        NumControlKeys
    };

    // Key bindings for camera movement
    static const UINT KeyBindings[NumControlKeys];

    bool m_bPressedKeys[NumControlKeys];        
    int m_iLastMouseX;
    int m_iLastMouseY;
    int m_iMouseDeltaX;
    int m_iMouseDeltaY;

    float m_fRotationX;
    float m_fRotationY;

    Utils::Timer timer;
};