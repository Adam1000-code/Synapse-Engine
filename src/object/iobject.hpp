#pragma once

class IObject
{
    public:
        virtual void Draw() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Clean() = 0;
};