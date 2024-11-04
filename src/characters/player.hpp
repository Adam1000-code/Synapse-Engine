#pragma once

#include "character.hpp"
#include "../animation/animation.hpp"
#include "../physics/rigidbody.hpp"
#include "../physics/collider.hpp"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 10.0f
#define RUN_FORCE 4.0f

class Player : public Character
{
    public:
        Player(Properties* props);

        virtual void Draw();
        virtual void Update(float deltaTime);
        virtual void Clean();
    
    private:
        //int m_row, m_frame, m_frameCount;
        //int m_animSpeed;
        bool isJumping;
        bool isGrounded;

        float jumpForce;
        float jumpTime;

        Collider* m_collider;
        RigidBody* m_rigidbody;
        Animation* m_animation;
        Vector2D lastSafePos;
};