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
Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

vector<ColliderComponent*> Game::colliders;

auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

enum groupLabels : size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};

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

    map = new Map();

    Map::LoadMap("assets/map_16x16.map", 16, 16);

    player.AddComponent<TransformComponent>(1);
    player.AddComponent<SpriteComponent>("assets/player.png");
    player.AddComponent<KeyboardController>();
    player.AddComponent<ColliderComponent>("player");
    player.AddGroup(groupPlayers);

    wall.AddComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
    wall.AddComponent<SpriteComponent>("assets/dirt.png");
    wall.AddComponent<ColliderComponent>("wall");
    wall.AddGroup(groupMap);
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

    for(auto cc : colliders)
    {
        Collision::AABB(player.GetComponent<ColliderComponent>(), *cc);
    }
}

auto& tiles(manager.GetGroup(groupMap));
auto& players(manager.GetGroup(groupPlayers));
auto& enemies(manager.GetGroup(groupEnemies));

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

void Game::AddTile(int id, int x, int y)
{
    auto& tile(manager.AddEntity());
    tile.AddComponent<TileComponent>(x, y, 32, 32, id);
    tile.AddGroup(groupMap);
}