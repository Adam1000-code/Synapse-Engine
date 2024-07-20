#pragma once

#include <iostream>
#include <string>
#include "SDL2/SDL.h"

using namespace std;

class Animation
{
    public:
        Animation()
        {
        }

        void Draw(float x, float y, int spriteWidth, int spriteHeight);
        void Update();
        void SetProperties(string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip);
    
    private:
        int m_spriteRow, m_spriteFrame;
        int m_animSpeed, m_frameCount;
        string m_textureID;
        SDL_RendererFlip m_flip;
};