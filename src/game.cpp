#include "include/game.hpp"
#include "include/texturemanager.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "include/map.hpp"
#include "include/ECS/components.hpp"
#include "include/vector2D.hpp"

using namespace std;

Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.addEntity());

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;

    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "Subsystems initialised\n";

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if(window)
        {
            cout << "Window created\n";
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "Renderer created\n";
        }

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    map = new Map();

    player.addComponent<TransformComponent>(0, 100);
    player.addComponent<SpriteComponent>("assets/player.png");
}

void Game::handleEvents()
{
    SDL_Event event;

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
    //cnt++;
    //cout << cnt << endl;
    manager.refresh();
    manager.update();
    player.getComponent<TransformComponent>().position.Add(Vector2D(5, 0));

    if(player.getComponent<TransformComponent>().position.x > 200)
    {
        player.getComponent<SpriteComponent>().setTex("assets/enemy.png");
    }

    //cout << player.getComponent<TransformComponent>().position.x << endl;
}

void Game::render()
{
    SDL_RenderClear(renderer);
    map->DrawMap();
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game cleaned\n";
}
