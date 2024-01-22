#pragma once

#include "game.hpp"

class GameObject
{
    public:
        GameObject(const char* textureSheet, int x, int y, int w, int h);
        ~GameObject();

        void Update();
        void Render();
    
    private:
        int xpos;
        int ypos;

        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;
};