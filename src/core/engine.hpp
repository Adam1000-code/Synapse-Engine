#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../map/gamemap.hpp"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

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
        inline GameMap* GetMap()
        {
            return m_levelMap;
        }
    
    private:
        bool m_isRunning;
        GameMap* m_levelMap;
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        static Engine* s_instance;
};