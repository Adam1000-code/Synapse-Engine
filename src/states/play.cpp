#include "play.hpp"
#include "../characters/player.hpp"

Player* player = nullptr;

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

    //MapParser::GetInstance()->Load("assets/engineMap.tmx", "level1");
    gameMap = Engine::GetInstance()->GetMap();
    gameMap = MapParser::GetInstance()->GetMap("level1");

    //TileLayer* collisionLayer = (TileLayer*) gameMap->GetMapLayers().back();
    //int tileSize = collisionLayer->GetTileSize();

    player = new Player(new Properties("player", 100, 200, 136, 96, SDL_FLIP_NONE));

    Camera::GetInstance()->SetTarget(player->GetOrigin());

    //gameObjects.push_back(player);

    cout << "play initialized" << endl;

    return true;
}

void Play::Update()
{
    gameMap = Engine::GetInstance()->GetMap();
    gameMap = MapParser::GetInstance()->GetMap("level1");
    
    float deltaTime = Timer::GetInstance()->GetDeltaTime();

    cout << "playing game" << endl;

    player->Update(deltaTime);
    gameMap->Update();
    Camera::GetInstance()->Update(deltaTime);

    Events();
}

void Play::Render()
{
    player->Draw();
    gameMap->Render();
}

void Play::Events()
{
}

bool Play::Exit()
{
    MapParser::GetInstance()->Clean();
    return false;
}
