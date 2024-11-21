#include "objectcreator.hpp"
#include <iostream>

using namespace std;

ObjectCreator* ObjectCreator::instance = nullptr;

GameObject* ObjectCreator::CreateObject(string type, Properties* props)
{
    GameObject* object = nullptr;
    auto it = typeRegistry.find(type);

    if(it != typeRegistry.end())
    {
        object = it->second(props);
    }

    return object;
}

void ObjectCreator::RegisterType(string className, function<GameObject* (Properties* props)> type)
{
    typeRegistry[className] = type;
}
