#pragma once

#include <map>
#include <string>
#include "gamemap.hpp"
#include "tilelayer.hpp"
#include "../vendor/TinyXML/tinyxml.h"

using namespace std;

class MapParser
{
    public:
        bool Load();
        void Clean(); 

        inline GameMap* GetMap(string id)
        {
            return m_mapDict[id];
        }
        inline static MapParser* GetInstance()
        {
            return s_instance = (s_instance != nullptr) ? s_instance : new MapParser();
        }
    
    private:
        MapParser()
        {
        }

        Tileset ParseTileset(TiXmlElement* xmlTileset);
        TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowCount, int colCount);
        
        bool Parse(string id, string source);
        static MapParser* s_instance;
        map<string, GameMap*> m_mapDict;
};