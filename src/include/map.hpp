#pragma once

#include "game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Map
{
    public:
        Map();
        ~Map();

        static void LoadMap(std::string path, int sizeX, int sizeY);

    private:
};