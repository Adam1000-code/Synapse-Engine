#include "include/map.hpp"
#include "include/texturemanager.hpp"
#include "include/game.hpp"
#include <fstream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Map::Map()
{
}

Map::~Map()
{
}

void Map::LoadMap(const char* path, int sizeX, int sizeY)
{
    char tile;
    std::fstream mapFile; 
    int srcX, srcY;

    mapFile.open(path);

    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            int tileValue;
            mapFile >> tileValue;

            if(tileValue >= 10)
            {
                srcY = (tileValue / 10) * 32;
                srcX = (tileValue % 10) * 32;
            }
            else
            {
                srcY = 0;
                srcX = tileValue * 32;
            }

            Game::AddTile(srcX, srcY, x * 64, y * 64);
        }
    }

    mapFile.close();
}