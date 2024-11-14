#include "sequenceanimation.hpp"
#include "../graphics/texturemanager.hpp"
#include "../vendor/TinyXML/tinyxml.h"
#include <iostream>

using namespace std;

SequenceAnimation::SequenceAnimation(bool repeat): Animation(repeat)
{
}

void SequenceAnimation::Update(float deltaTime)
{
    if(repeat || !isEnded)
    {
        isEnded = false;
        currentFrame = (SDL_GetTicks() / currentSequence.speed) % currentSequence.frameCount;
    }

    if(!repeat && currentFrame == (currentSequence.frameCount - 1))
    {
        isEnded = true;
        currentFrame = (currentSequence.frameCount - 1);
    }
}

void SequenceAnimation::Parse(string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);

    if(/*!xml.LoadFile(source) || */xml.Error())
    {
        cerr << "ERROR: Failed to load animation file: " << source << endl;
    }

    TiXmlElement* root = xml.RootElement();

    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == string("sequence"))
        {
            Sequence seq;
            string seqID = e->Attribute("id");
            e->Attribute("speed", &seq.speed);
            e->Attribute("width", &seq.width);
            e->Attribute("height", &seq.height);
            e->Attribute("frameCount", &seq.frameCount);

            for(TiXmlElement* frame = e->FirstChildElement(); frame != nullptr; frame = frame->NextSiblingElement())
            {
                seq.textureIDs.push_back(frame->Attribute("textureID"));
            }

            sequenceMap[seqID] = seq;
        }
    }
}

void SequenceAnimation::SetCurrentSequence(string sequenceID)
{
    if(sequenceMap.count(sequenceID) > 0)
    {
        currentSequence = sequenceMap[sequenceID];
    }
    else
    {
        cout << "WARNING: The given sequence animation is not matching: " << sequenceID << endl;
    }
}

void SequenceAnimation::DrawFrame(float x, float y, float scaleX, float scaleY, SDL_RendererFlip flip)
{
    TextureManager::GetInstance()->Draw(currentSequence.textureIDs[currentFrame], x, y, currentSequence.width, currentSequence.height, scaleX, scaleY, flip);
}