#pragma once

#include <iostream>
#include <string>
#include "../factory/objectcreator.hpp"

using namespace std;

class Parser
{
    public:
        static Parser* GetInstance()
        {
            return instance = (instance != nullptr) ? instance : new Parser();
        }

        bool LoadMap(string path, string id);
        bool ParseMap(string id, string source);
        void ParseGameObjects(string source, ObjectVec* target);

    private:
        static Parser* instance;
};