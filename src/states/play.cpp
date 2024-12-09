#include "play.hpp"

Play::Play()
{
}

bool Play::Init()
{
    cout << "play initialized" << endl;
    //TextureManager::GetInstance()->ParseTextures("assets/textures.xml");
    return true;
}

void Play::Update()
{
    cout << "playing game" << endl;
}

void Play::Render()
{
}

void Play::Events()
{
}

bool Play::Exit()
{
    return false;
}
