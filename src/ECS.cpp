#include "include/ECS/ECS.hpp"

void Entity::AddGroup(Group mGroup)
{
    groupBitset[mGroup] = true;
    manager.AddToGroup(this, mGroup);
}