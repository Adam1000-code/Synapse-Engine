#include "player.hpp"
#include "../physics/rigidbody.hpp"
#include "../graphics/texturemanager.hpp"
#include "../input/input.hpp"
#include "SDL2/SDL.h"

Player::Player(Properties* props) : Character(props)
{
    m_rigidbody = new RigidBody();
    m_animation = new Animation();
    
    m_animation->SetProperties(m_textureID, 1, 6, 100, m_flip);

    m_width = 32;
    m_height = 32;
}

void Player::Draw()
{
    m_animation->Draw(m_transform->X, m_transform->Y, m_width, m_height);
}

void Player::Update(float deltaTime)
{
    m_rigidbody->Update(deltaTime);
    m_rigidbody->EraseForce();

    m_animation->SetProperties("player", 1, 6, 100, m_flip);

    m_transform->TranslateX(m_rigidbody->Position().X);
    //m_transform->TranslateY(m_rigidbody->Position().Y);

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        m_rigidbody->ApplyForceX(3 * FORWARD);
        m_animation->SetProperties("player_run", 1, 6, 100, m_flip);
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        m_rigidbody->ApplyForceX(3 * BACKWARD);
        m_animation->SetProperties("player_run", 1, 6, 100, SDL_FLIP_HORIZONTAL);
    }

    m_animation->Update();
}

void Player::Clean()
{
    TextureManager::GetInstance()->Clean();
}