#include "include/map.hpp"
#include "include/texturemanager.hpp"
#include "include/game.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
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
    std::ifstream mapFile(path);
    std::string line;
    std::vector<std::vector<int>> mapData;

    while(std::getline(mapFile, line))
    {
        std::istringstream ss(line);
        std::vector<int> row;
        std::string value;

        while(std::getline(ss, value, ','))
        {
            row.push_back(std::stoi(value));
        }

        mapData.push_back(row);
    }

    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            if(y < mapData.size() && x < mapData[y].size())
            {
                int tileCode = mapData[y][x];
                int srcX = tileCode % 10;
                int srcY = tileCode / 10;
                Game::AddTile(srcX * 32, srcY * 32, x * 64, y * 64);
            }
            /*else
            {
                std::cout << "Warning: Insufficient data for tile at (" << x << ", " << y << ")" << std::endl;
            }*/
        }
    }
}