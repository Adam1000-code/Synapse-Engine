#include "player.hpp"
#include "../physics/rigidbody.hpp"
#include "../graphics/texturemanager.hpp"
#include "../input/input.hpp"
#include "../camera/camera.hpp"
#include "../collision/collisionhandler.hpp"
#include "../factory/objectcreator.hpp"
#include <SDL2/SDL.h>

static ObjectRegister<Player> m_register("Player");

Player::Player(Properties* props) : Character(props)
{
    isGrounded = false;
    isJumping = false;

    jumpForce = JUMP_FORCE;
    jumpTime = JUMP_TIME;

    m_rigidbody = new RigidBody();
    m_rigidbody->SetGravity(3.0f);

    //bool loopAnim = true;

    m_animation = new SpriteAnimation();
    
    m_animation->SetProperties(m_textureID, 1, 6, 100, m_flip);

    m_width = 32;
    m_height = 32;

    m_collider = new Collider();
    m_collider->SetBuffer(-60, -20, 0, 0);
}

void Player::Draw()
{
    m_animation->Draw(m_transform->X, m_transform->Y, m_width, m_height, m_flip);

    /*Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);*/
}

void Player::Update(float deltaTime)
{
    m_rigidbody->EraseForce();

    m_animation->SetProperties("playerIdle", 1, 6, 100, m_flip);

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        m_animation->SetProperties("playerRun", 1, 6, 100, m_flip);
        m_rigidbody->ApplyForceX(3 * FORWARD);
        m_flip = SDL_FLIP_NONE;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        m_animation->SetProperties("playerRun", 1, 6, 100, m_flip);
        m_rigidbody->ApplyForceX(3 * BACKWARD);
        m_flip = SDL_FLIP_HORIZONTAL;
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

    m_rigidbody->Update(deltaTime);

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
        m_animation->SetProperties("playerJump", 1, 1, 150, m_flip);
    }

    // old/unused physics code
    //m_transform->TranslateX(m_rigidbody->Position().X);
    //m_transform->TranslateY(m_rigidbody->Position().Y);

    m_origin->X = m_transform->X + m_width / 2;
    m_origin->Y = m_transform->Y + m_height / 2;

    m_animation->Update(deltaTime);
}

void Player::Clean()
{
    TextureManager::GetInstance()->Drop(m_textureID);
}