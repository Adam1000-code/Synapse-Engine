#pragma once

#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include <map>

using namespace std;

class TextureManager
{
    public:
        TextureManager();

        static TextureManager* GetInstance()
        {
            return s_instance = (s_instance != nullptr) ? s_instance : new TextureManager();
        }

        bool Load(string id, string filename);
        void Draw(string id, int x, int y, int width, int height, SDL_RendererFlip flip);
        void DrawFrame(string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip);
        void DrawTile(string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip);
        void Drop(string id);
        void Clean();

    private:
        map<string, SDL_Texture*> m_textureMap;
        static TextureManager* s_instance;
};