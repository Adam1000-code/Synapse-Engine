#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include "gamestate.hpp"
#include "../map/gamemap.hpp"
#include "../map/mapparser.hpp"
#include "../factory/objectcreator.hpp"
#include "../object/gameobject.hpp"
#include "../input/input.hpp"
#include "../physics/physics.hpp"
#include "../camera/camera.hpp"
//#include "../core/engine.hpp"
#include "../collision/collisionhandler.hpp"
#include "../animation/sequenceanimation.hpp"
#include "../animation/spriteanimation.hpp"
#include "../graphics/texturemanager.hpp"
#include "../time/timer.hpp"

using namespace std;

class Play : public GameState
{
    public:
        Play();

        void Events();

        virtual bool Init();
        virtual bool Exit();
        
        virtual void Update();
        virtual void Render();

    private:
        bool editMode;
        GameMap* gameMap;
        vector<GameObject*> gameObjects;
        SDL_Renderer* m_ctxt;
};