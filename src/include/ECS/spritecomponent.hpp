#pragma once

#include <iostream>
#include "components.hpp"
#include "transformcomponent.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "../texturemanager.hpp"
#include "animation.hpp"
#include <map>

class SpriteComponent : public Component
{
    public:
        int animIndex = 0;

        std::map<const char*, Animation> animations;

        SpriteComponent() = default;

        SpriteComponent(const char* path)
        {
            setTex(path);
        }

        SpriteComponent(const char* path, bool isAnimated)
        {
            animated = isAnimated;

            Animation idle = Animation(0, 3, 100);
            Animation walk = Animation(1, 8, 100);

            animations.emplace("Idle", idle);
            animations.emplace("Walk", walk);

            Play("Idle");

            setTex(path);
        }

        ~SpriteComponent()
        {
            SDL_DestroyTexture(texture);
        }

        void setTex(const char* path)
        {
            texture = TextureManager::LoadTexture(path);
        }

        void init() override
        {
            transform = &entity->GetComponent<TransformComponent>();

            srcRect.x = srcRect.y = 0;
            srcRect.w = transform->width;
            srcRect.h = transform->height;
        }

        void update() override
        {
            if(animated)
            {
                srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
            }

            srcRect.y = animIndex * transform->height;

            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);
            destRect.w = transform->width * transform->scale;
		    destRect.h = transform->height * transform->scale;
        }

        void draw() override
        {
            TextureManager::Draw(texture, srcRect, destRect);
        }

        void Play(const char* animName)
        {
            frames = animations[animName].frames;
            animIndex = animations[animName].index;
            speed = animations[animName].speed;
        }
    
    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect srcRect, destRect;
        bool animated = false;
        int frames = 0;
        int speed = 100;
};