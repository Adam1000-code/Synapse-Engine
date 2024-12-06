#pragma once

class GameState
{
    public:
        virtual bool Init() = 0;
        virtual bool Exit() = 0;

        virtual void Update() = 0;
        virtual void Render() = 0;
};