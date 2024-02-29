#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID GetNewComponentTypeID()
{
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
    static_assert(std::is_base_of<Component, T>::value, "");
    static ComponentID typeID = GetNewComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
    public:
        Entity* entity;

        virtual void init() {}
        virtual void update() {}
        virtual void draw() {}

        virtual ~Component() {}
};

class Entity
{
    public:
        Entity(Manager& mManager) : manager(mManager) {}

        void update()
        {
            for(auto& c : components)
            {
                c->update();
            }
        }

        void draw()
        {
            for(auto& c : components)
            {
                c->draw();
            }
        }

        bool isActive() const
        {
            return active;
        }

        void destroy()
        {
            active = false;
        }

        bool HasGroup(Group mGroup)
        {
            return groupBitset[mGroup];
        }

        void AddGroup(Group mGroup);

        void DeleteGroup(Group mGroup)
        {
            groupBitset[mGroup] = false;
        }

        template <typename T> bool HasComponent()
        {
            return componentBitSet[GetComponentTypeID<T>()];
        }

        template <typename T, typename... TArgs>
        T& AddComponent(TArgs&&... MArgs)
        {
            T* c(new T(std::forward<TArgs>(MArgs)...));
            c->entity = this;
		    std::unique_ptr<Component>uPtr { c };
		    components.emplace_back(std::move(uPtr));

            componentArray[GetComponentTypeID<T>()] = c;
		    componentBitSet[GetComponentTypeID<T>()] = true;

		    c->init();
		    return *c;
        }

        template<typename T> T& GetComponent() const
	    {
            auto ptr(componentArray[GetComponentTypeID<T>()]);
            return *static_cast<T*>(ptr);
	    }

    private:
        Manager& manager;
        bool active = true;
        std::vector<std::unique_ptr<Component>> components;

        ComponentArray componentArray;
        ComponentBitSet componentBitSet;
        GroupBitset groupBitset;
};

class Manager
{
    public:
        void update()
        {
            for(auto& e : entities)
            {
                e->update();
            }
        }

        void draw()
        {
            for(auto& e : entities)
            {
                e->draw();
            }
        }

        void refresh()
        {
            for(auto i(0u); i < maxGroups; i++)
            {
                auto& v(groupedEntities[i]);
                v.erase(
                    std::remove_if(std::begin(v), std::end(v),
                    [i](Entity* mEntity)
                    {
                        return !mEntity->isActive() || !mEntity->HasGroup(i);
                    }),
                    std::end(v)
                );
            }

            entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity)
            {
                return !mEntity->isActive();
            }), std::end(entities));
        }

        void AddToGroup(Entity* mEntity, Group mGroup)
        {
            groupedEntities[mGroup].emplace_back(mEntity);
        }

        std::vector<Entity*>& GetGroup(Group mGroup)
        {
            return groupedEntities[mGroup];
        }

        Entity& AddEntity()
        {
            Entity *e = new Entity(*this);
            std::unique_ptr<Entity> uPtr {e};
            entities.emplace_back(std::move(uPtr));
            return *e;
        }
    
    private:
        std::vector<std::unique_ptr<Entity>> entities;
        std::array<std::vector<Entity*>, maxGroups> groupedEntities;
};