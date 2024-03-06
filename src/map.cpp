#include "include/map.hpp"
#include "include/texturemanager.hpp"
#include "include/game.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Map::Map()
{
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
    std::fstream mapFile;
    char tile;
    int srcX, srcY;

    mapFile.open(path);

    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            mapFile.get(tile);
            srcY = atoi(&tile) * 32;
            mapFile.get();
            srcX = atoi(&tile) * 32;
            Game::AddTile(srcX, srcY, x * 64, y * 64);
            mapFile.ignore();
        }
    }

    mapFile.close();
}