#pragma once

#include <SDL2/SDL.h>

class Collider
{
    public:
        inline SDL_Rect Get()
        {
            return box;
        }
        inline void SetBuffer(int x, int y, int w, int h)
        {
            buffer = {x, y, w, h};
        }

        void Set(int x, int y, int w, int h)
        {
            box = {
                x - buffer.x,
                y - buffer.y,
                w - buffer.w,
                h - buffer.h
            };
        }
    
    private:
        SDL_Rect box;
        SDL_Rect buffer;
};