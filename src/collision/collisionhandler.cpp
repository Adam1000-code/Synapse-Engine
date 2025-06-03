#include "collisionhandler.hpp"
#include "../core/engine.hpp"

CollisionHandler* CollisionHandler::instance = nullptr;

CollisionHandler::CollisionHandler()
{
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool xOverlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool yOverlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return (xOverlaps && yOverlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a)
{
    int tileSize = 32;
    int rowCount = 20;
    int colCount = 60;

    int leftTile = a.x / tileSize;
    int rightTile = (a.x + a.w) / tileSize;

    int topTile =  a.y / tileSize;
    int bottomTile = (a.y + a.h) / tileSize;

    if(leftTile < 0)
    {
        leftTile = 0;
    }

    if(rightTile >= colCount)
    {
        rightTile = colCount - 1;
    }

    if(topTile < 0)
    {
        topTile = 0;
    }

    if(bottomTile >= rowCount)
    {
        bottomTile = rowCount - 1;
    }

    for(int i = leftTile; i <= rightTile; i++)
    {
        for(int j = topTile; j <= bottomTile; j++)
        {
            if(collisionTileMap[j][i] > 0)
            {
                return true;
            }
        }
    }

    return false;
}

void CollisionHandler::SetLayer(TileLayer* layer)
{
    if(layer)
    {
        collisionLayer = layer;
        collisionTileMap = collisionLayer->GetTileMap();
    }
    else
    {
        cout << "ERROR: Collision layer is null!" << endl;
    }
}