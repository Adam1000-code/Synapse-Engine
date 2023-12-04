#pragma once

#include "components.hpp"
#include "../vector2D.hpp"

class TransformComponent : public Component
{
    public:
        Vector2D position;
	    Vector2D velocity;

        TransformComponent()
        {
            position.x = 0.0f;
		    position.y = 0.0f;
        }

        TransformComponent(float x, float y)
        {
		    position.x = x;
		    position.y = y;
        }

        void update() override
        {
        }
};