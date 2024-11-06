#pragma once

#include <iostream>
#include <string>
#include "../vendor/TinyXML/tinyxml.h"
#include <SDL2/SDL.h>
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
        bool ParseTextures(string source);
        void Draw(string id, int x, int y, int width, int height, float scaleX = 1, float scaleY = 1, float scrollRatio = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawFrame(string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawTile(string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void Drop(string id);
        void Clean();

    private:
        map<string, SDL_Texture*> m_textureMap;
        static TextureManager* s_instance;
};