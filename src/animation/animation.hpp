#pragma once

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

using namespace std;

class Animation
{
    public:
        Animation(bool m_repeat = true): repeat(m_repeat)
        {
            isEnded = false;
        }

        virtual void update(float deltaTime) = 0;
        inline bool IsEnded()
        {
            return isEnded;
        }

    protected:
        bool repeat;
        bool isEnded;
        int currentFrame;
};