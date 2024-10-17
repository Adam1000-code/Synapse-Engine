#include "player.hpp"
#include "../physics/rigidbody.hpp"
#include "../graphics/texturemanager.hpp"
#include "../input/input.hpp"
#include "../camera/camera.hpp"
#include "../collision/collisionhandler.hpp"
#include <SDL2/SDL.h>

Player::Player(Properties* props) : Character(props)
{
    jumpForce = JUMP_FORCE;
    jumpTime = JUMP_TIME;

    m_rigidbody = new RigidBody();
    m_rigidbody->SetGravity(3.0f);

    m_animation = new Animation();

    m_collider = new Collider();
    m_collider->SetBuffer(-60, -20, 0, 0);
    
    m_animation->SetProperties(m_textureID, 1, 6, 100, m_flip);

    m_width = 32;
    m_height = 32;
}

void Player::Draw()
{
    m_animation->Draw(m_transform->X, m_transform->Y, m_width, m_height);

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Player::Update(float deltaTime)
{
    m_rigidbody->EraseForce();

    m_animation->SetProperties("player", 1, 6, 100, m_flip);

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

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && isGrounded)
    {
        isJumping = true;
        isGrounded = false;
        m_rigidbody->ApplyForceY(UPWARD * jumpForce);
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && isJumping && jumpTime > 0)
    {
        jumpTime -= deltaTime;
        m_rigidbody->ApplyForceY(UPWARD * jumpForce);
    }
    else
    {
        isJumping = false;
        jumpTime = JUMP_TIME;
    }

    // move on x axis
    lastSafePos.X = m_transform->X;
    m_transform->X += m_rigidbody->Position().X;
    m_collider->Set(m_transform->X, m_transform->Y, 96, 96);

    if(CollisionHandler::GetInstance()->MapCollision(m_collider->Get()))
    {
        m_transform->X = lastSafePos.X;
    }

    // move on y axis
    lastSafePos.Y = m_transform->Y;
    m_transform->Y += m_rigidbody->Position().Y;
    m_collider->Set(m_transform->X, m_transform->Y, 96, 96);

    if(CollisionHandler::GetInstance()->MapCollision(m_collider->Get()))
    {
        isGrounded = true;
        m_transform->Y = lastSafePos.Y;
    }
    else
    {
        isGrounded = false;
    }

    if(isJumping || !isGrounded)
    {
        m_animation->SetProperties("player_jump", 1, 1, 150, m_flip);
    }

    // old/unused physics code
    //m_transform->TranslateX(m_rigidbody->Position().X);
    //m_transform->TranslateY(m_rigidbody->Position().Y);

    m_origin->X = m_transform->X + m_width / 2;
    m_origin->Y = m_transform->Y + m_height / 2;

    m_rigidbody->Update(deltaTime);
    m_animation->Update();
}

void Player::Clean()
{
    TextureManager::GetInstance()->Drop(m_textureID);
}