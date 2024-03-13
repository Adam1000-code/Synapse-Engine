#pragma once

#include "../game.hpp"
#include "ECS.hpp"
#include "components.hpp"

/* This is for all of your controls' keybinds. Set and define them here */
class KeyboardController : public Component
{
    public:
        TransformComponent* transform;
        SpriteComponent* sprite;

        void init() override
        {
            transform = &entity->GetComponent<TransformComponent>();
            sprite = &entity->GetComponent<SpriteComponent>();
        }

        void update() override
        {
            if(Game::event.type == SDL_KEYDOWN)
            {
                switch(Game::event.key.keysym.sym)
                {
                    case SDLK_w:
                        transform->velocity.y = -1;
                        sprite->Play("Walk");
                        break;
                    case SDLK_a:
                        transform->velocity.x = -1;
                        sprite->Play("Walk");
                        sprite->spriteFlip = SDL_FLIP_NONE;
                        break;
                    case SDLK_d:
                        transform->velocity.x = 1;
                        sprite->Play("Walk");
                        break;
                    case SDLK_s:
                        transform->velocity.y = 1;
                        sprite->Play("Walk");
                        break;
                    default:
                        break;
                }
            }

            if(Game::event.type == SDL_KEYUP)
            {
                switch(Game::event.key.keysym.sym)
                {
                    case SDLK_w:
                        transform->velocity.y = 0;
                        sprite->Play("Idle");
                        break;
                    case SDLK_a:
                        transform->velocity.x = 0;
                        sprite->Play("Idle");
                        sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                        break;
                    case SDLK_d:
                        transform->velocity.x = 0;
                        sprite->Play("Idle");
                        break;
                    case SDLK_s:
                        transform->velocity.y = 0;
                        sprite->Play("Idle");
                        break;
                    case SDLK_ESCAPE:
                        Game::isRunning = false;
                    default:
                        break;
                }
            }
        }
};