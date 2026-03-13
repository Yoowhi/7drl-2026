#pragma once

#include "TileType.hpp"
#include "Vec2i.hpp"
#include "raylib.h"

class Tile {
    public:
        TileType type;
        Vec2i tilePosition;
        Vector3 position;

        Tile();
        Tile(TileType type, Vec2i coordinate);

};