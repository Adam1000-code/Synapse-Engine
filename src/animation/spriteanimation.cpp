#include "spriteanimation.hpp"
#include <SDL2/SDL.h>
#include "../graphics/texturemanager.hpp"

using namespace std;

SpriteAnimation::SpriteAnimation(bool repeat): Animation(repeat)
{
}

void SpriteAnimation::Draw(float x, float y, int spriteWidth, int spriteHeight, float scaleX, float scaleY, SDL_RendererFlip flip)
{
    TextureManager::GetInstance()->DrawFrame(textureID, x, y, spriteWidth, spriteHeight, spriteRow, currentFrame, flip);
}

void SpriteAnimation::Update(float Deltatime)
{
    currentFrame = (SDL_GetTicks() / animSpeed) % frameCount;
}

void SpriteAnimation::SetProperties(string m_textureID, int m_spriteRow, int m_frameCount, int m_animSpeed, SDL_RendererFlip m_flip)
{
    textureID = m_textureID;
    spriteRow = m_spriteRow;
    frameCount = m_frameCount;
    animSpeed = m_animSpeed;
    flip = m_flip;
}