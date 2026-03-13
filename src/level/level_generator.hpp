#pragma once
#include "Vec2i.hpp"
#include "./bsp/CellNode.hpp"
#include "TileType.hpp"

TileType* generateTiles(Vec2i size, CellNode* cellTree);
