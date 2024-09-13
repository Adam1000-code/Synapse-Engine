#include "tilelayer.hpp"
#include "../graphics/texturemanager.hpp"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets) : m_tileSize(tilesize), m_colCount(colcount), m_rowCount(rowcount), m_tilemap(tilemap), m_tilesets(tilesets)
{
    /*m_rowCount = rowcount;
    m_colCount = colcount;
    m_tilemap = tilemap;
    m_tilesets = tilesets;*/

    for(unsigned int i = 0; i < m_tilesets.size(); i++)
    {
        TextureManager::GetInstance()->Load(m_tilesets[i].name, "assets/" + m_tilesets[i].source);
    }
}

void TileLayer::Render()
{
    for(unsigned int x = 0; x < m_rowCount; x++)
    {
        for(unsigned int y = 0; y < m_colCount; y++)
        {
            int tileID = m_tilemap[x][y];
            //int temp = tileID;

            if(tileID == 0)
            {
                continue;
            }
            else
            {
                int index = 0;
                if(m_tilesets.size() > 1)
                {
                    for(unsigned int i = 1; i < m_tilesets.size(); i++)
                    {
                        if(tileID > m_tilesets[i].firstID && tileID < m_tilesets[i].lastID)
                        {
                            //tileID = tileID + m_tilesets[i].tileCount - m_tilesets[i].lastID;
                            tileID = tileID - m_tilesets[i].firstID + 1;
                            index = i;
                            break;
                        }
                    }
                }

                Tileset ts = m_tilesets[index];
                int tileRow = tileID / ts.colCount;
                int tileCol = tileID - tileRow * ts.colCount - 1;

                if(tileID % ts.colCount == 0)
                {
                    tileRow--;
                    tileCol = ts.colCount - 1;
                }

                TextureManager::GetInstance()->DrawTile(ts.name, ts.tileSize, y * ts.tileSize, x * ts.tileSize, tileRow, tileCol);
            }
        }
    }
}

void TileLayer::Update()
{
}