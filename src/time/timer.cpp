#include "timer.hpp"
#include "SDL2/SDL.h"

Timer* Timer::s_instance = nullptr;

Timer::Timer()
{
}

void Timer::Tick()
{
    m_deltaTime = (SDL_GetTicks() - m_previousTime) * (targetFPS / 1000.0f);

    if(m_deltaTime > targetDeltaTime)
    {
        m_deltaTime = targetDeltaTime;
    }

    m_previousTime = SDL_GetTicks();
}