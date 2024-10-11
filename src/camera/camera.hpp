#pragma once

#include "../physics/point.hpp"
#include "../physics/vector2D.hpp"
#include "../core/engine.hpp"
#include <SDL2/SDL.h>

using namespace std;

class Camera
{
    public:
        static Camera* GetInstance()
        {
            return instance = (instance != nullptr) ? instance : new Camera();
        }

        inline SDL_Rect GetViewPort()
        {
            return viewPort;
        }
        inline Vector2D GetPosition()
        {
            return position;
        }
        inline void SetTarget(Point* m_target)
        {
            target = m_target;
        }

        void Update(float deltaTime);
    
    private:
        Camera()
        {
            viewPort = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        }

        SDL_Rect viewPort;
        Point* target;
        Vector2D position;
        static Camera* instance;
};