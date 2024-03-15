#include "include/game.hpp"
#include "include/texturemanager.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "include/map.hpp"
#include "include/ECS/components.hpp"
#include "include/ECS/ECS.hpp"
#include "include/vector2D.hpp"
#include "include/collision.hpp"

using namespace std;

Manager manager;
Map* mapManager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, 800, 640 };

vector<ColliderComponent*> Game::colliders;

auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

bool Game::isRunning = false;

const char* mapTexture = "assets/terrain_ss.png";

enum groupLabels : size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};

auto& tiles(manager.GetGroup(groupMap));
auto& players(manager.GetGroup(groupPlayers));
auto& enemies(manager.GetGroup(groupEnemies));

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
    #pragma region Init Window
    int flags = 0;

    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        //cout << "Subsystems initialised\n";

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        /*if(window)
        {
            cout << "Window created\n";
        }*/

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            //cout << "Renderer created\n";
        }

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }
    #pragma endregion Init Window

    mapManager = new Map();

    mapManager->LoadMap("assets/map.map", 20, 25);

    player.AddComponent<TransformComponent>(3);
    player.AddComponent<SpriteComponent>("assets/player_anims.png", true);
    player.AddComponent<KeyboardController>();
    player.AddComponent<ColliderComponent>("player");
    player.AddGroup(groupPlayers);
}

void Game::handleEvents()
{
    SDL_PollEvent(&event);

    switch(event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update()
{
    manager.update();
    manager.refresh();

    /*Vector2D playerVelocity = player.GetComponent<TransformComponent>().velocity;
    int playerSpeed = player.GetComponent<TransformComponent>().speed;

    for(auto t : tiles)
    {
        t->GetComponent<TileComponent>().destRect.x += -(playerVelocity.x * playerSpeed);
        t->GetComponent<TileComponent>().destRect.y += -(playerVelocity.y * playerSpeed);
    }*/

    camera.x = player.GetComponent<TransformComponent>().position.x - 400;
    camera.y = player.GetComponent<TransformComponent>().position.y - 320;

    if(camera.x < 0)
    {
        camera.x = 0;
    }

    if(camera.y < 0)
    {
        camera.y = 0;
    }

    if(camera.x > camera.w)
    {
        camera.x = camera.w;
    }

    if(camera.y > camera.h)
    {
        camera.y = camera.h;
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    for(auto& t : tiles)
    {
        t->draw();
    }
    for(auto& p : players)
    {
        p->draw();
    }
    for(auto& e : enemies)
    {
        e->draw();
    }

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    //cout << "Game cleaned\n";
}

void Game::AddTile(int srcX, int srcY, int xpos, int ypos)
{
    auto& tile(manager.AddEntity());
    tile.AddComponent<TileComponent>(srcX, srcY, xpos, ypos, mapTexture);
    tile.AddGroup(groupMap);
}