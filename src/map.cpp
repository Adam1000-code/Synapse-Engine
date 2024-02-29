#include "include/map.hpp"
#include "include/texturemanager.hpp"
#include "include/game.hpp"
#include <fstream>
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
    char c;
    std::fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;

    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            mapFile.get(c);
            srcY = atoi(&c) * 32;
            mapFile.get(c);
            srcX = atoi(&c) * 32;
            Game::AddTile(srcX, srcY, x * 64, y * 64);
            mapFile.ignore();
        }
    }

    mapFile.close();
}