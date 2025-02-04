#pragma once

#include "layer.hpp"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Tileset
{
    int firstID, lastID;
    int rowCount, colCount;
    int tileCount, tileSize;
    string name, source;
};

using TilesetList = vector<Tileset>;
using TileMap = vector<vector<int>>;

class TileLayer : public Layer
{
    public:
        TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets);
        virtual void Render();
        virtual void Update();
        inline TileMap GetTileMap()
        {
            return m_tilemap;
        }
        inline int GetTileSize()
        {
            return m_tileSize;
        }
    
    private:
        int m_tileSize;
        int m_rowCount, m_colCount;

        TileMap m_tilemap;
        TilesetList m_tilesets;
};