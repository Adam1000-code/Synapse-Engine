#pragma once

#include "../graphics/texturemanager.hpp"
#include "animation.hpp"

using namespace std;

class SpriteAnimation : public Animation
{
    public:
        public:
        SpriteAnimation(bool repeat = true);

        virtual void Update(float deltaTime);
        void Draw(float x, float y, int spriteWidth, int spriteHeight, float scaleX = 1, float scaleY = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void SetProperties(string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip m_flip = SDL_FLIP_NONE);

        int GetCurrentFrame()
        {
            return currentFrame;
        }
        int GetCurrentSpriteRow()
        {
            return spriteRow;
        }

        void SetSpriteRow(int row)
        {
            spriteRow = row;
        }
        void IncreaseSpriteRow()
        {
            spriteRow++;
        }
        void DecreaseSpriteRow()
        {
            spriteRow--;
        }
    
    private:
        int spriteRow;
        int frameCount;
        int animSpeed;
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        string textureID;
};