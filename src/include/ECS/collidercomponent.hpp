#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "components.hpp"
#include "ECS.hpp"

class ColliderComponent : public Component
{
    public:
        SDL_Rect collider;
        std::string tag;

	    TransformComponent* transform;

        ColliderComponent(std::string t)
        {
            tag = t;
        }

        void init() override
        {
            if(!entity->HasComponent<TransformComponent>())
            {
                entity->AddComponent<TransformComponent>();
            }

            transform = &entity->GetComponent<TransformComponent>();
            Game::colliders.push_back(this);
        }

        void update() override
        {
            collider.x = static_cast<int>(transform->position.x);
    		collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
        }
};