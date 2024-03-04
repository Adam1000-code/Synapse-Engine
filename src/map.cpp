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
    char tile;
    std::fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;

    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            mapFile.get(tile);
            srcY = atoi(&tile) * 32;
            mapFile.get(tile);
            srcX = atoi(&tile) * 32;
            //mapFile.get(tile);
            Game::AddTile(srcX, srcY, x * 64, y * 64);
            mapFile.ignore();
        }
    }

    mapFile.close();
}