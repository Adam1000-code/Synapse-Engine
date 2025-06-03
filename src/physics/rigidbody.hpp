#pragma once

#include "vector2D.hpp"

#define UNI_MASS 1.0f
#define GRAVITY 9.8f

#define FORWARD 1
#define BACKWARD -1

#define UPWARD -1
#define DOWNWARD 1

class RigidBody
{
    public:
        RigidBody()
        {
            m_mass = UNI_MASS;
            m_gravity = GRAVITY;
        }

        inline void SetMass(float mass)
        {
            m_mass = mass;
        }
        inline void SetGravity(float gravity)
        {
            m_gravity = gravity;
        }

        void ApplyForce(Vector2D f)
        {
            m_force = f;
        }
        void ApplyForceX(float fx)
        {
            m_force.X = fx;
        }
        void ApplyForceY(float fy)
        {
            m_force.Y = fy;
        }
        void EraseForce() // rename to RemoveForce later on
        {
            m_force = Vector2D(0, 0);
        }

        inline void ApplyFriction(Vector2D fr)
        {
            m_friction = fr;
        }
        inline void EraseFriction() // rename to RemoveFriction later on
        {
            m_friction = Vector2D(0, 0);
        }
        inline float GetMass()
        {
            return m_mass;
        }
        inline Vector2D Position()
        {
            return m_position;
        }
        inline Vector2D Velocity()
        {
            return m_velocity;
        }
        inline Vector2D Acceleration()
        {
            return m_acceleration;
        }

        void Update(float deltaTime)
        {
            m_acceleration.X = (m_force.X + m_friction.X) / m_mass;
            m_acceleration.Y = m_gravity + m_force.Y / m_mass;
            m_velocity += m_acceleration * deltaTime;
            m_position += m_velocity * deltaTime;
        }

    
    private:
        float m_mass;
        float m_gravity;

        Vector2D m_force;
        Vector2D m_friction;

        Vector2D m_position;
        Vector2D m_velocity;
        Vector2D m_acceleration;
};