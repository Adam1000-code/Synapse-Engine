#include "include/gameobject.hpp"
#include "include/game.hpp"
#include "include/texturemanager.hpp"
#include <SDL2/SDL.h>

GameObject::GameObject(const char* texturesheet, int x, int y, int w, int h)
{
    objTexture = TextureManager::LoadTexture(texturesheet);

    srcRect.w = w;
    srcRect.h = h;

    xpos = x;
    ypos = y;
}

void GameObject::Update()
{
    xpos++;
    ypos++;

    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}