#pragma once

#include <map>
#include <string>
#include <memory>
#include "../object/gameobject.hpp"

using namespace std;

class ObjectCreator
{
    public:
        GameObject* CreateObject(string type, Properties* props);
        void RegisterType(string className, function<GameObject*(Properties* props)> type);
        static ObjectCreator* GetInstance()
        {
            return instance = (instance != nullptr) ? instance : new ObjectCreator();
        }
    
    private:
        ObjectCreator()
        {
        }

        static ObjectCreator* instance;
        map<string, function<GameObject*(Properties* props)>> typeRegistry;
};

template<class Type>
class ObjectRegister
{
    public:
        ObjectRegister(string className)
        {
            ObjectCreator::GetInstance()->RegisterType(className, [](Properties* props)->GameObject* {return new Type(props);});
        }
};