#pragma once

#include "../physics/point.hpp"
#include "../physics/vector2D.hpp"
#include "../core/engine.hpp"
#include <SDL2/SDL.h>

using namespace std;

class Camera
{
    public:
        inline static Camera* GetInstance()
        {
            return instance = (instance != nullptr) ? instance : new Camera();
        }

        inline int GetSceneWidth()
        {
            return sceneWidth;
        }
        inline int GetSceneHeight()
        {
            return sceneHeight;
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
        inline void MoveX(float x)
        {
            position.X = x;
        }
        inline void MoveY(float y)
        {
            position.Y = y;
        }

        inline void SetSceneLimit(int width, int height)
        {
            sceneWidth = width;
            sceneHeight = height;
        }

        void Update(float deltaTime);
    
    private:
        Camera();

        SDL_Rect viewPort;
        Point* target;
        Vector2D position;
        int sceneWidth, sceneHeight;
        static Camera* instance;
};