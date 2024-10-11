#include "texturemanager.hpp"
#include "../core/engine.hpp"
#include <iostream>
#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

TextureManager* TextureManager::s_instance = nullptr;

TextureManager::TextureManager()
{
}

bool TextureManager::Load(string id, string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr)
    {
        SDL_Log("ERROR: Failed to load texture: %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if(texture == nullptr)
    {
        SDL_Log("ERROR: Failed to create texture from surface: %s", SDL_GetError());
        return false;
    }

    m_textureMap[id] = texture;
    return true;
}

void TextureManager::Draw(string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect datRect = {x, y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_textureMap[id], &srcRect, &datRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {width * frame, height * (row - 1), width, height};
    SDL_Rect dstRect = {x, y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_textureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect dstRect = {x, y, tilesize, tilesize};
    SDL_Rect srcRect = {tilesize * frame, tilesize * row, tilesize, tilesize}; // changed (row - 1) to row to avoid skipping the first row
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_textureMap[tilesetID], &srcRect, &dstRect, 0, 0, flip = SDL_FLIP_NONE);
}

void TextureManager::Drop(string id)
{
    SDL_DestroyTexture(m_textureMap[id]);
    m_textureMap.erase(id);
}

void TextureManager::Clean()
{
    map<string, SDL_Texture*>::iterator it;
    for(it = m_textureMap.begin(); it != m_textureMap.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }

    m_textureMap.clear();
    SDL_Log("Texture map cleaned successfully");
}