#include "play.hpp"
#include "../characters/player.hpp"
#include "../factory/objectcreator.hpp"

//Player* player = nullptr;
GameObject* oPlayer;

Play::Play()
{
}

bool Play::Init()
{
    TextureManager::GetInstance()->ParseTextures("assets/textures.xml");

    m_ctxt = Engine::GetInstance()->GetRenderer();

    if(!MapParser::GetInstance()->Load("assets/engineMap.tmx", "level1"))
    {
        cout << "ERROR: Failed to load map" << endl;
    }
    
    gameMap = MapParser::GetInstance()->GetMap("level1");

    //TileLayer* collisionLayer = (TileLayer*)gameMap->GetMapLayers().back();
    //CollisionHandler::GetInstance()->SetLayer(collisionLayer);

    //player = new Player(new Properties("player", 100, 200, 136, 96, SDL_FLIP_NONE));
    
    oPlayer = ObjectCreator::GetInstance()->CreateObject("Player", new Properties("player", 100, 200, 136, 96, SDL_FLIP_NONE));

    Camera::GetInstance()->SetTarget(oPlayer->GetOrigin());

    gameObjects.push_back(oPlayer);

    cout << "play initialized" << endl;

    return true;
}

void Play::Update()
{
    float deltaTime = Timer::GetInstance()->GetDeltaTime();

    //TileLayer* collisionLayer = (TileLayer*)gameMap->GetMapLayers().back();
    //CollisionHandler::GetInstance()->SetLayer(collisionLayer);

    //cout << "playing game" << endl;

    for(unsigned int i = 0; i != gameObjects.size(); i++)
    {
        gameObjects[i]->Update(deltaTime);
    }

    //player->Update(deltaTime);
    //oPlayer->Update(deltaTime);
    gameMap->Update();
    Camera::GetInstance()->Update(deltaTime);

    //Events();
}

void Play::Render()
{
    for(unsigned int i = 0; i != gameObjects.size(); i++)
    {
        gameObjects[i]->Draw();
    }
    //oPlayer->Draw();
    gameMap->Render();
}

void Play::Events()
{
}

bool Play::Exit()
{
    for(unsigned int i = 0; i != gameObjects.size(); i++)
    {
        gameObjects[i]->Clean();
    }
    //oPlayer->Clean();
    MapParser::GetInstance()->Clean();
    return false;
}