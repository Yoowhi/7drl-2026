#include "Level.hpp"
#include "level_generator.hpp"
#include "./bsp/BSP.hpp"
#include "Wall.hpp"
#include "tile_constants.hpp"

struct TileListResult {
    Tile* tileList;
    int size; 
};

struct WallListResult {
    Wall* wallList;
    int size;
};

TileListResult generateTileList(TileType* tileMap, Vec2i mapSize) {
    int arrayLength = mapSize.x * mapSize.y;
    int resultLength = 0;
    for (int i = 0; i < arrayLength; i++) {
        if (tileMap[i] == TileType::FLOOR) {
            resultLength++;
        }
    }
    Tile* tileList = new Tile[resultLength];
    int j = 0;
    for (int y = 0; y < mapSize.y; y++) {
        for (int x = 0; x < mapSize.x; x++) {
            int i = y * mapSize.y + x;
            if (tileMap[i] == TileType::FLOOR) {
                tileList[j] = Tile(TileType::FLOOR, {x, y});
                j++;
            }
        }
    }
    return {tileList, resultLength};
}

bool isTileEmpty(Vec2i position, Vec2i mapSize, TileType* tileMap) {
    if (position.x < 0 || position.y < 0) {
        return true;
    }
    if (position.x >= mapSize.x || position.y >= mapSize.y) {
        return true;
    }
    int index = position.y * mapSize.y + position.x;
    return tileMap[index] == TileType::EMPTY;
}

WallListResult generateWallList(Vec2i mapSize, TileType* tileMap) {
    int arrayLength = mapSize.x * mapSize.y;
    int wallListLength = 0;
    for (int y = 0; y < mapSize.y; y++) {
        for (int x = 0; x < mapSize.x; x++) {
            int i = y * mapSize.y + x;
            if (tileMap[i] == TileType::FLOOR) {
                if (isTileEmpty({x, y - 1}, mapSize, tileMap)) {
                    wallListLength += 1;
                }
                if (isTileEmpty({x + 1, y}, mapSize, tileMap)) {
                    wallListLength += 1;
                }
                if (isTileEmpty({x, y + 1}, mapSize, tileMap)) {
                    wallListLength += 1;
                }
                if (isTileEmpty({x - 1, y}, mapSize, tileMap)) {
                    wallListLength += 1;
                }
            }
        }
    }
    Wall* wallList = new Wall[wallListLength];
    int j = 0;
    for (int y = 0; y < mapSize.y; y++) {
        for (int x = 0; x < mapSize.x; x++) {
            int i = y * mapSize.y + x;
            if (tileMap[i] == TileType::FLOOR) {
                if (isTileEmpty({x, y - 1}, mapSize, tileMap)) {
                    wallList[j] = Wall({x, y}, WallDirection::SOUTH);
                    j++;
                }
                if (isTileEmpty({x + 1, y}, mapSize, tileMap)) {
                    wallList[j] = Wall({x, y}, WallDirection::WEST);
                    j++;
                }
                if (isTileEmpty({x, y + 1}, mapSize, tileMap)) {
                    wallList[j] = Wall({x, y}, WallDirection::NORTH);
                    j++;
                }
                if (isTileEmpty({x - 1, y}, mapSize, tileMap)) {
                    wallList[j] = Wall({x, y}, WallDirection::EAST);
                    j++;
                }
            }
        }
    }

    return {wallList, wallListLength};
}

Level* Level::createLevel(Vec2i size, Vec2i minSize) {
    Area dungeonArea = Area({0, 0}, {size.x, size.y});
    auto cellTree = genCellTree(dungeonArea, {minSize.x, minSize.y});
    auto tileMap = generateTiles(dungeonArea.size, cellTree);
    auto [ tileList, tileListSize ] = generateTileList(tileMap, dungeonArea.size);
    return new Level(tileMap, dungeonArea.size, cellTree, tileList, tileListSize);
}

Level::Level(TileType* tilesMap, Vec2i size, CellNode* cellTree, Tile* tileList, int tileListSize) 
    : tilesMap(tilesMap), size(size), cellTree(cellTree), tileList(tileList), tileListSize(tileListSize) 
{
    auto [wallList, wallListSize] = generateWallList(size, tilesMap);
    this->wallList = wallList;
    this->wallListSize = wallListSize;
};

Level::~Level() {
    delete tilesMap;
    delete cellTree;
    delete tileList;
}

