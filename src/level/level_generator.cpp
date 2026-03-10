#include "level_generator.hpp"
#include <stack>
#include "./bsp/BSP.hpp"


void fillArea(Vec2i size, TileType* tileIds, Area area) {
    for (int y = area.from.y; y < area.to.y; y++) {
        for (int x = area.from.x; x < area.to.x; x++) {
            tileIds[y * size.y + x] = TileType::FLOOR;
        }
    }
}

TileType* generateTiles(Vec2i size, CellNode* cellTree) {
    TileType* tileIds = new TileType[size.x * size.y];
    for (int i = 0; i < size.x * size.y; i++) {
        tileIds[0] = TileType::EMPTY;
    }
    CellNode* currentNode = cellTree;
    std::stack<CellNode*> stack;
    if (cellTree->right) {
        stack.push(cellTree->right);
    }
    if (cellTree->left) {
        stack.push(cellTree->left);
    }
    fillArea(size, tileIds, cellTree->pathway);
    while (!stack.empty()) {
        auto node = stack.top();
        stack.pop();
        if (node->right) {
            stack.push(node->right);
        }
        if (node->left) {
            stack.push(node->left);
        }
        if (!node->right && !node->left) {
            fillArea(size, tileIds, node->rooms[0]);
        }
        fillArea(size, tileIds, node->pathway);
    }
    return tileIds;
}