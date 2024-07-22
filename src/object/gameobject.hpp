#pragma once

#include "iobject.hpp"
#include "../physics/transform.hpp"
#include "SDL2/SDL.h"
#include <iostream>
#include <string>

using namespace std;

struct Properties
{
    public:
        Properties(string textureID, int x, int y, int width, int height, SDL_RendererFlip flip)
        {
            p_x = x;
            p_y = y;
            p_width = width;
            p_height = height;
            p_flip = flip; // set this flip to none with SDL_FLIP_NONE
            p_textureID = textureID;
        }

    public:
        string p_textureID;
        int p_width, p_height;
        float p_x, p_y;
        SDL_RendererFlip p_flip;
};

class GameObject : public IObject
{
    public:
        GameObject(Properties* props) : m_textureID(props->p_textureID), m_width(props->p_width), m_height(props->p_height), m_flip(props->p_flip)
        {
            m_transform = new Transform(props->p_x, props->p_y);
        }

        virtual void Draw() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Clean() = 0;

    protected:
        Transform* m_transform;
        int m_width, m_height;
        string m_textureID;
        SDL_RendererFlip m_flip;
};