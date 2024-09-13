#pragma once

#include "layer.hpp"
#include "../physics/vector2D.hpp"
#include <iostream>
#include <vector>

using namespace std;

class GameMap
{
    public:
        void Render()
        {
            for(unsigned int i = 0; i < m_mapLayers.size(); i++)
            {
                m_mapLayers[i]->Render();
            }
        }
        void Update()
        {
            for(unsigned int i = 0; i < m_mapLayers.size(); i++)
            {
                m_mapLayers[i]->Update();
            }
        }

        vector<Layer*> GetMapLayers()
        {
            return m_mapLayers;
        }
    
    private:
        friend class MapParser;
        vector<Layer*> m_mapLayers;
};