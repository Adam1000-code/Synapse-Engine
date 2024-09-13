#include "mapparser.hpp"
#include <string>

using namespace std;

MapParser* MapParser::s_instance = nullptr;

bool MapParser::Load()
{
    return Parse("level1", "assets/engineMap1.tmx");
}

bool MapParser::Parse(string id, string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);

    if(/*!xml.LoadFile(source) || */xml.Error())
    {
        cerr << "ERROR: Failed to load: " << source << endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    int rowCount, colCount, tileSize = 0;

    root->Attribute("width", &rowCount);
    root->Attribute("height", &colCount);
    root->Attribute("tilewidth", &tileSize);

    TilesetList tilesets;

    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == string("tileset"))
        {
            tilesets.push_back(ParseTileset(e));
        }
    }

    GameMap* gamemap = new GameMap;

    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == string("layer"))
        {
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tileSize, rowCount, colCount);
            gamemap->m_mapLayers.push_back(tilelayer);
        }
    }

    m_mapDict[id] = gamemap;

    return true;
}

Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset)
{
    Tileset tileset;
    tileset.name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid", &tileset.firstID);
    xmlTileset->Attribute("tilecount", &tileset.tileCount);
    tileset.lastID = (tileset.firstID + tileset.tileCount) - 1;

    xmlTileset->Attribute("columns", &tileset.colCount);
    tileset.rowCount = tileset.tileCount / tileset.colCount;
    xmlTileset->Attribute("tilewidth", &tileset.tileSize);

    TiXmlElement* image = xmlTileset->FirstChildElement();
    tileset.source = image->Attribute("source");
    return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowCount, int colCount)
{
    TiXmlElement* data = nullptr;

    for(TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == string("data"))
        {
            data = e;
            break;
        }
    }

    string matrix(data->GetText());
    stringstream iss(matrix);
    string id;

    TileMap tilemap(rowCount, vector<int>(colCount, 0));

    for(int row = 0; row < rowCount; row++)
    {
        for(int col = 0; col < colCount; col++)
        {
            getline(iss, id, ',');
            stringstream converter(id);
            converter >> tilemap[row][col];

            if(!iss.good())
            {
                break;
            }
        }
    }

    return (new TileLayer(tilesize, rowCount, colCount, tilemap, tilesets));
}

void MapParser::Clean()
{
    map<string, GameMap*>::iterator it;

    for(it = m_mapDict.begin(); it != m_mapDict.end(); it++)
    {
        it->second = nullptr;
        //delete it->second;
    }

    m_mapDict.clear();
}