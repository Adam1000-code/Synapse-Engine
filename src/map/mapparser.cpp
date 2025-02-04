#include "mapparser.hpp"
#include "../graphics/texturemanager.hpp"
#include <string>

using namespace std;

MapParser* MapParser::s_instance = nullptr;

bool MapParser::Load(string path, string id)
{
    if(!Parse(id, path))
    {
        return false;
    }

    return true;
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

    root->Attribute("width", &colCount);
    root->Attribute("height", &rowCount);
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
    /*Tileset tileset;
    tileset.name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid", &tileset.firstID);
    xmlTileset->Attribute("tilecount", &tileset.tileCount);
    tileset.lastID = (tileset.firstID + tileset.tileCount) - 1;

    xmlTileset->Attribute("columns", &tileset.colCount);
    tileset.rowCount = tileset.tileCount / tileset.colCount;
    xmlTileset->Attribute("tilewidth", &tileset.tileSize);

    TiXmlElement* image = xmlTileset->FirstChildElement();
    tileset.source = image->Attribute("source");
    return tileset;*/

    Tileset tileset;
    TilesetList tilesets;

    if(xmlTileset->Attribute("name")) 
    {
        tileset.name = xmlTileset->Attribute("name");
    }
    else 
    {
        cerr << "ERROR: Tileset missing 'name' attribute." << endl;
        return Tileset();
    }

    if(xmlTileset->Attribute("firstgid", &tileset.firstID)) 
    {
        tileset.firstID = atoi(xmlTileset->Attribute("firstgid"));
    } 
    else 
    {
        cerr << "ERROR: Tileset missing 'firstgid' attribute." << endl;
        return Tileset();
    }

    TiXmlElement* imageElement = xmlTileset->FirstChildElement("image");

    if(imageElement && imageElement->Attribute("source")) 
    {
        tileset.source = imageElement->Attribute("source");
    }
    else 
    {
        cerr << "ERROR: Tileset image missing 'source' attribute." << endl;
        return Tileset();
    }

    /*if(xmlTileset->FirstChildElement()->Value() == string("image"))
    {
        tileset.source = xmlTileset->FirstChildElement("image")->Attribute("source");
    }
	else
    {
        tileset.source = xmlTileset->Attribute("source");
    }*/ // comment this out

    if(xmlTileset->Attribute("tilewidth", &tileset.tileSize)) 
    {
        tileset.tileSize = atoi(xmlTileset->Attribute("tilewidth"));
    }
    else 
    {
        cerr << "ERROR: Tileset missing 'tilewidth' attribute." << endl;
        return Tileset();
    }

    /*if(xmlTileset->Attribute("tileheight", &tileset.tileSize)) 
    {
        tileset.tileSize = atoi(xmlTileset->Attribute("tileheight"));
    }*/
    /*else 
    {
        cerr << "ERROR: Tileset missing 'tileheight' attribute." << endl;
        return Tileset();
    }*/ //leave this commented out

    if(xmlTileset->Attribute("columns", &tileset.colCount)) 
    {
        tileset.colCount = atoi(xmlTileset->Attribute("columns"));
    } 
    else 
    {
        cerr << "WARNING: Tileset missing 'columns' attribute, defaulting to 0." << endl;
        tileset.colCount = 0;
    }

    if(xmlTileset->Attribute("tilecount", &tileset.tileCount)) 
    {
        tileset.tileCount = atoi(xmlTileset->Attribute("tilecount"));
    }
    else 
    {
        cerr << "WARNING: Tileset missing 'tilecount' attribute, defaulting to 0." << endl;
        tileset.tileCount = 0;
    }

    for(unsigned int i = 0; i < tilesets.size(); i++)
    {
        TextureManager::GetInstance()->Load(tilesets[i].name, "assets/" + tilesets[i].source);
    }

    tileset.lastID = (tileset.firstID + tileset.tileCount) - 1;

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

    /*for(auto& pair : m_mapDict)
    {
        delete pair.second;
        pair.second = nullptr;
    }*/

    m_mapDict.clear();
}