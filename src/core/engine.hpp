#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../map/gamemap.hpp"
#include "../states/gamestate.hpp"
#include "../object/gameobject.hpp"
#include "../characters/character.hpp"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

#define PSP_SCREEN_WIDTH 480
#define PSP_SCREEN_HEIGHT 272

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

        /*void PopState();
        void PushState(GameState* current);
        void ChangeState(GameState* target);*/

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
        //vector<GameState*> m_states;
        //vector<GameObject*> m_objects;
        //vector<Character*> m_characters;
};