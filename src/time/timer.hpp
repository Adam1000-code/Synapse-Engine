#pragma once

const int targetFPS = 60;
const float targetDeltaTime = 1.5f;

class Timer
{
    public:
        void Tick();
        inline float GetDeltaTime()
        {
            return m_deltaTime;
        }
        inline static Timer* GetInstance()
        {
            return s_instance = (s_instance != nullptr) ? s_instance : new Timer();
        }
    
    private:
        Timer();
        static Timer* s_instance;
        float m_deltaTime;
        float m_previousTime;
};