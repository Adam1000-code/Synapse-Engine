#pragma once

#include "components.hpp"
#include "transformcomponent.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "../texturemanager.hpp"

class SpriteComponent : public Component
{
    public:
        SpriteComponent() = default;
        SpriteComponent(const char* path)
        {
            setTex(path);
        }

        void setTex(const char* path)
        {
            texture = TextureManager::LoadTexture(path);
        }

        void init() override
        {
            transform = &entity->getComponent<TransformComponent>();

            srcRect.x = srcRect.y = 0;
            srcRect.w = srcRect.h = 32;
            destRect.w = destRect.h = 64;
        }

        void update() override
        {
            destRect.x = (int)transform->position.x;
            destRect.y = (int)transform->position.y;
        }

        void draw() override
        {
            TextureManager::Draw(texture, srcRect, destRect);
        }
    
    private:
        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;
};