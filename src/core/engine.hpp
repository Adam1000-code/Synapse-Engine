#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../map/gamemap.hpp"

class Engine
{
    public:
        Engine();
        ~Engine();
        
        static Engine* GetInstance()
        {
            return s_instance = (s_instance != nullptr) ? s_instance : new Engine();
        }

        bool Init(const char* title, int width, int height);
        bool Clean();

        void Update();
        void Render();
        void Events();
        void Quit();

        inline bool isRunning()
        {
            return m_isRunning;
        }
        inline SDL_Renderer* GetRenderer()
        {
            return m_renderer;
        }
    
    private:
        bool m_isRunning;
        GameMap* m_levelMap;
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        static Engine* s_instance;
};