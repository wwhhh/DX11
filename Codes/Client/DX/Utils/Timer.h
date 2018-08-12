#pragma once

namespace Utils
{
    class Timer
    {
    public:
        Timer();
        ~Timer();

        void Update();
        void Reset();
        float Runtime();
        float Elapsed();
        int Framerate();
        int MaxFramerate();
        int FrameCount();
        float Frametime();

        void SetFixedTimeStep(float step);

    private:
        float m_fDelta;
        int m_iFramesPerSecond;
        int m_iMaxFramesPerSecond;
        int m_iFrameCount;

        float m_fFixedDelta;
        bool m_bUseFixedStep;

        unsigned __int64 m_TicksPerSecond64;
        unsigned __int64 m_StartupTicks64;
        unsigned __int64 m_CurrentTicks64;
        unsigned __int64 m_OneSecTicks64;
        unsigned __int64 m_LastTicks64;
    };
}