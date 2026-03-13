#pragma once
#include "Vec2i.hpp"
#include "raylib.h"
#include "WallDirection.hpp"

class Wall {
    public:
        Vec2i tilePosition;
        Vector3 position;
        Quaternion direction;

        Wall(Vec2i tilePosition, WallDirection direction);
        Wall();
};