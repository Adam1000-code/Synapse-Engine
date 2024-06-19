/*
 * Synapse Engine
 * Created on 11/26/23, by Adam1000
 * Overhaul began on 4/8/24
 */

#include <iostream>
#include <SDL2/SDL.h>
#include "core/engine.hpp"
#include "time/timer.hpp"

using namespace std;

/** Engine version **/
const float engineVer = 1.03;

int main()
{
    cout << "Synapse Engine Overhaul: Version " << engineVer << ", Created by Adam1000" << endl;
    
    Engine::GetInstance()->Init("Synapse Engine", 960, 640);

    while(Engine::GetInstance()->isRunning())
    {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();
    }

    Engine::GetInstance()->Clean();

    return 0;
}