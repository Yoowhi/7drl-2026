#pragma once

#include "Tile.hpp"
#include "Vec2i.hpp"
#include "TileType.hpp"
#include "./bsp/CellNode.hpp"

class Level {
    public:
        TileType* tilesMap;
        Vec2i size;
        CellNode* cellTree;
        Tile* tileList;
        int tileListSize;

        
        static Level* createLevel(Vec2i size, Vec2i minSize);

        ~Level();
    private:
        Level(TileType* tilesMap, Vec2i size, CellNode* cellTree, Tile* tileList, int tileListSize);
        
};