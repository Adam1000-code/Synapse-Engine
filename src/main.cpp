/**
 * Synapse Engine
 * 11/26/23
 * Created by Adam1000
 */

#include "include/game.hpp"
#include <iostream>

using namespace std;

Game* game = nullptr;

/** Engine version **/
//float engineVer = 0.43;

int main()
{
    const int FPS = 50;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();

    //cout << "Made with Synapse\n";
    //cout << "Synapse Engine beta " << engineVer << ": Created by Adam1000\n";

    game->init("Synapse Engine", 800, 640, false);

    while(game->running())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game->clean();

    return 0;
}