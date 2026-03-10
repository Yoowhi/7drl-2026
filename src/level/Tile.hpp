#pragma once

#include "TileType.hpp"
#include "Vec2i.hpp"

class Tile {
    public:
        TileType type;
        Vec2i coordinate;

        Tile();
        Tile(TileType type, Vec2i coordinate);

};