#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "gamestate.hpp"

using namespace std;

class Menu : public GameState
{
    public:
        Menu();

        virtual bool Init();
        virtual bool Exit();

        virtual void Render();
        virtual void Update();

    private:
        static void StartGame();
        static void Settings();
        static void Editor();
        static void Quit();

        SDL_Renderer* m_ctxt;
};