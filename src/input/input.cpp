#include "input.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include "../core/engine.hpp"

Input* Input::s_instance = nullptr;

Input::Input()
{
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::InputListen()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                Engine::GetInstance()->Quit();
                break;
            case SDL_KEYDOWN:
                KeyDown();
                break;
            case SDL_KEYUP:
                KeyUp();
                break;
        }
    }
}

bool Input::GetKeyDown(SDL_Scancode key)
{
    if(m_keyStates[key] == 1)
    {
        return true;
    }

    return false;
}

void Input::KeyUp()
{
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown()
{
    m_keyStates = SDL_GetKeyboardState(nullptr);
}