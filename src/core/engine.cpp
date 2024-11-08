#include "engine.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../graphics/texturemanager.hpp"
#include "../physics/vector2D.hpp"
#include "../physics/transform.hpp"
#include "../characters/player.hpp"
#include "../object/gameobject.hpp"
#include "../input/input.hpp"
#include "../time/timer.hpp"
#include "../map/mapparser.hpp"
#include "../camera/camera.hpp"
#include <iostream>
#include <string>

using namespace std;

Engine* Engine::s_instance = nullptr;
Player* player = nullptr;

Engine::Engine()
{
}

bool Engine::Init(const char* title, int width, int height)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        SDL_Log("ERROR: Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(m_window == nullptr)
    {
        SDL_Log("ERROR: Failed to create window: %s", SDL_GetError());
        return false;
    }
    
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_renderer == nullptr)
    {
        SDL_Log("ERROR: Failed to create renderer: %s", SDL_GetError());
    }

    if(!MapParser::GetInstance()->Load())
    {
        cout << "ERROR: Failed to load map" << endl;
    }
    
    //MapParser::GetInstance()->Load();

    m_levelMap = MapParser::GetInstance()->GetMap("level1");

    //TextureManager::GetInstance()->Load("logo1", "assets/synapselogo1.png");
    TextureManager::GetInstance()->ParseTextures("assets/textures.xml");
    //TextureManager::GetInstance()->Load("player", "assets/Idle (32x32).png");
    //TextureManager::GetInstance()->Load("player_run", "assets/Run (32x32).png");
    //TextureManager::GetInstance()->Load("player_jump", "assets/Jump (32x32).png");
    player = new Player(new Properties("player", 100, 200, 136, 96, SDL_FLIP_NONE));

    Transform tf;
    tf.Log();

    Camera::GetInstance()->SetTarget(player->GetOrigin());
    return m_isRunning = true;
}

void Engine::Update()
{
    float deltaTime = Timer::GetInstance()->GetDeltaTime();
    m_levelMap->Update();
    player->Update(deltaTime);
    Camera::GetInstance()->Update(deltaTime);
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_renderer);

    //TextureManager::GetInstance()->Draw("logo1", 0, 0, 110, 100, SDL_FLIP_NONE);

    m_levelMap->Render();
    player->Draw();
    SDL_RenderPresent(m_renderer);
}

void Engine::Events()
{
    Input::GetInstance()->InputListen();
}

bool Engine::Clean()
{
    TextureManager::GetInstance()->Clean();
    MapParser::GetInstance()->Clean();
    SDL_DestroyRenderer(m_renderer);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit()
{
    m_isRunning = false;
}