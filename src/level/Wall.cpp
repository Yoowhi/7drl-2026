#include "Wall.hpp"
#include "tile_constants.hpp"

Wall::Wall(Vec2i tilePosition, WallDirection direction) : tilePosition(tilePosition) {
    switch (direction)
    {
    case WallDirection::NORTH:
        this->direction = DIRECTION_NORTH;
        position = Vector3{(float)(tilePosition.x * TILE_SIZE_X), TILE_SIZE_X / 2.0f, TILE_SIZE_Z / 2.0f + tilePosition.y * TILE_SIZE_Z};
        break;
    case WallDirection::EAST:
        this->direction = DIRECTION_EAST;
        position = Vector3{-(TILE_SIZE_X / 2.0f) + (tilePosition.x * TILE_SIZE_X), TILE_SIZE_X / 2.0f, (float)(tilePosition.y * TILE_SIZE_Z)};
        break;
    case WallDirection::SOUTH:
        this->direction = DIRECTION_SOUTH;
        position = Vector3{(float)(tilePosition.x * TILE_SIZE_X), TILE_SIZE_X / 2.0f, -(TILE_SIZE_Z / 2.0f) + tilePosition.y * TILE_SIZE_Z};
        break;
    case WallDirection::WEST:
        this->direction = DIRECTION_WEST;
        position = Vector3{(TILE_SIZE_X / 2.0f) + (tilePosition.x * TILE_SIZE_X), TILE_SIZE_X / 2.0f, (float)(tilePosition.y * TILE_SIZE_Z)};
        break;
    
    default:
        throw "This should not happen";
    }
    

}

Wall::Wall() {
    
}