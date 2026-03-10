#include "Level.hpp"
#include "level_generator.hpp"
#include "./bsp/BSP.hpp"

struct TileListResult {
    Tile* tileList;
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
    // int j = 0;
    // for (int i = 0; i < arrayLength; i++) {
    //     if (tileMap[i] == TileType::FLOOR) {
    //         int x = i % mapSize.y;
    //         int y = (i - x) / mapSize.y;
    //         tileList[j] = Tile(TileType::FLOOR, {x, y});
    //         j++;
    //     }
    // }
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

};

Level::~Level() {
    delete tilesMap;
    delete cellTree;
    delete tileList;
}

