#pragma once

#include <iostream>
#include <SDL2/SDL.h>

class Input
{
    public:
        static Input* GetInstance()
        {
            return s_instance = (s_instance != nullptr) ? s_instance : new Input();
        }

        void InputListen();
        bool GetKeyDown(SDL_Scancode key);
    
    private:
        Input();
        void KeyUp();
        void KeyDown();

        const Uint8* m_keyStates;
        static Input* s_instance;
};