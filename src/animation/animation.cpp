#include "animation.hpp"
#include <SDL2/SDL.h>
#include "../graphics/texturemanager.hpp"

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight)
{
    TextureManager::GetInstance()->DrawFrame(m_textureID, x, y, spriteWidth, spriteHeight, m_spriteRow, m_spriteFrame, m_flip);
}

void Animation::Update()
{
    m_spriteFrame = (SDL_GetTicks() / m_animSpeed) % m_frameCount;
}

void Animation::SetProperties(string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip)
{
    m_textureID = textureID;
    m_spriteRow = spriteRow;
    m_frameCount = frameCount;
    m_animSpeed = animSpeed;
    m_flip = flip;
}