#include "Tile.hpp"
#include "level/tile_constants.hpp"

Tile::Tile(TileType type, Vec2i coordinate) : type(type), tilePosition(coordinate) {
    float x = coordinate.x * TILE_SIZE_X;
    float z = coordinate.y * TILE_SIZE_Z;
    position = {
        x,
        0,
        z
    };
}

Tile::Tile() {
    
};