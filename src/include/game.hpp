#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
    public:
        Game();
        ~Game();

        void init(const char* title, int width, int height, bool fullscreen);

        void handleEvents();
        void update();
        bool running() { return isRunning; }
        void render();
        void clean();

        static void AddTile(int srcX, int srcY, int xpos, int ypos);
        static SDL_Renderer *renderer;
        static SDL_Event event;
        static std::vector<ColliderComponent*> colliders;
    
    private:
        //int cnt = 0;
        bool isRunning;
        SDL_Window* window;
};
