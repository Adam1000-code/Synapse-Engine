#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "gamestate.hpp"

using namespace std;

class Menu : public GameState
{
    public:
        Menu();

        virtual bool Init() = 0;
        virtual bool Exit() = 0;

        virtual void Render() = 0;
        virtual void Update() = 0;

    private:
        static void StartGame();
        static void Settings();
        static void Editor();
        static void Quit();

        SDL_Renderer* m_ctxt;
};