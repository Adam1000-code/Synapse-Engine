#pragma once

#include <map>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "animation.hpp"

using namespace std;

struct Sequence
{
    int speed;
    int frameCount;
    int width, height;
    vector<string> textureIDs;
};

class SequenceAnimation : public Animation
{
    public:
        SequenceAnimation(bool repeat = true);

        virtual void Update(float deltaTime);
        void Parse(string source);
        void SetCurrentSequence(string sequenceID);
        void SetRepeat(bool m_repeat)
        {
            repeat = m_repeat;
        }
        void DrawFrame(float x, float y, float scaleX = 1, float scaleY = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        Sequence currentSequence;
        map<string, Sequence> sequenceMap;
};