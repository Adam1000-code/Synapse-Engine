#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "../map/tilelayer.hpp"
#include "../map/gamemap.hpp"

class CollisionHandler
{
    public:
        bool CheckCollision(SDL_Rect a, SDL_Rect b);
        bool MapCollision(SDL_Rect a);

        inline static CollisionHandler* GetInstance()
        {
            return instance = (instance != nullptr) ? instance : new CollisionHandler();
        }

    private:
        CollisionHandler();
        TileMap collisionTileMap;
        TileLayer* collisionLayer;
        static CollisionHandler* instance;
};