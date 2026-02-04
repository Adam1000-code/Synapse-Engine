#include "camera.hpp"

using namespace std;

Camera* Camera::instance = nullptr;

Camera::Camera()
{
    viewPort = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

void Camera::Update(float deltaTime)
{
    if(target != nullptr)
    {
        viewPort.x = static_cast<int>(target->X) - SCREEN_WIDTH / 2;
        viewPort.y = static_cast<int>(target->Y) - SCREEN_HEIGHT / 2;

        if(viewPort.x < 0)
        {
            viewPort.x = 0;
        }

        if(viewPort.y < 0)
        {
            viewPort.y = 0;
        }

        if(viewPort.x > (2 * sceneWidth - viewPort.w))
        {
            viewPort.x = (2 * sceneWidth - viewPort.w);
        }

        if(viewPort.y > (sceneHeight - viewPort.h))
        {
            viewPort.y = (sceneHeight - viewPort.h);
        }

        position = Vector2D(viewPort.x, viewPort.y);
    }
    else
    {
        SDL_Log("Camera target is null");
    }
}