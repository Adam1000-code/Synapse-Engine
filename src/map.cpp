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

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
    std::fstream mapFile;
    mapFile.open(path);

    if(!mapFile.is_open())
    {
        std::cerr << "Error opening map file: " << path << std::endl;
        return;
    }

    int tile;
    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            mapFile >> tile;

            if(!mapFile)
            {
                std::cerr << "Error reading from map file: " << path << std::endl;
                mapFile.close();
                return;
            }

            int srcX = (tile % 8) * 32;
            int srcY = (tile / 8) * 32;

            Game::AddTile(srcX, srcY, x * 64, y * 64);
            mapFile.ignore();
        }
    }

    mapFile.close();
}