#pragma once

#include "../object/gameobject.hpp"
#include <iostream>
#include <string>

class Character : public GameObject
{
    public:
        Character(Properties* props) : GameObject(props)
        {
        }

        virtual void Draw() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Clean() = 0;
    
    protected:
        string m_name;
};