#pragma once

#include "character.hpp"
#include "../animation/animation.hpp"
#include "../physics/rigidbody.hpp"

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
        RigidBody* m_rigidbody;
        Animation* m_animation;
};