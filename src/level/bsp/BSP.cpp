#include "BSP.hpp"
#include "helpers.hpp"
#include "raylib.h"
#include "math.h"

struct DividedCell {
    Area left;
    Area right;
};

DividedCell divideCellVertically(Area cell, int intersection) {
    Vec2i leftFrom = cell.from;
    Vec2i leftTo = Vec2i {
        intersection - 1,
        cell.to.y
    };
    Area leftCell = Area(leftFrom, leftTo);
    Vec2i rightFrom = Vec2i {
        intersection,
        cell.from.y
    };
    Vec2i rightTo = cell.to;
    Area rightCell = Area(rightFrom, rightTo);
    return {leftCell, rightCell};
}

DividedCell divideCellHorizontally(Area cell, int intersection) {
    Vec2i upFrom = cell.from;
    Vec2i upTo = Vec2i {
        cell.to.x,
        intersection - 1
    };
    Area upCell = Area(upFrom, upTo);
    Vec2i downFrom = Vec2i {
        cell.from.x,
        intersection
    };
    Vec2i downTo = cell.to;
    Area downCell = Area(downFrom, downTo);
    return {upCell, downCell};
}

Area findVerticalPath(std::vector<Area> upRooms, std::vector<Area> downRooms) {
    // найти комнату с самым низким y в upRooms 
    Area upClosestRoom = upRooms[0];
    for (auto room : upRooms) {
        if (room.to.y > upClosestRoom.to.y) {
            upClosestRoom = room;
        }
    }
    // найти комнату с самым высоким y у которой стенки пересекаются с найденной комнатой по иксу
    Area downClosestRoom = downRooms[0];
    int x;
    bool found = false;
    for (auto room : downRooms) {
        int biggestFrom = std::max(room.from.x, upClosestRoom.from.x);
        int lowestTo = std::min(room.to.x, upClosestRoom.to.x);
        if (biggestFrom < lowestTo) {
            if (room.from.y <= downClosestRoom.from.y) {
                found = true;
                downClosestRoom = room;
                x = (biggestFrom + lowestTo) / 2;
            }
        }
    }
    Area path = Area({x, upClosestRoom.to.y}, {x + 1, downClosestRoom.from.y});
    return path;
}

Area findHorizontalPath(std::vector<Area> leftRooms, std::vector<Area> rightRooms) {
    Area leftClosestRoom = leftRooms[0];
    for (auto room : leftRooms) {
        if (room.to.x > leftClosestRoom.to.x) {
            leftClosestRoom = room;
        }
    }
    Area rightClosestRoom = rightRooms[0];
    int y;
    for (auto room : rightRooms) {
        int biggestFrom = std::max(room.from.y, leftClosestRoom.from.y);
        int lowestTo = std::min(room.to.y, leftClosestRoom.to.y);
        if (biggestFrom < lowestTo) {
            if (room.from.x <= rightClosestRoom.from.x) {
                rightClosestRoom = room;
                y = (biggestFrom + lowestTo) / 2;
            }
        }
    }
    Area path = Area({leftClosestRoom.to.x, y}, {rightClosestRoom.from.x, y + 1});
    return path;
}

CellNode* genCellTree(Area cell, Vec2i minSize) {
    CellNode* node = new CellNode();
    if (cell.size.x <= minSize.x && cell.size.y <= minSize.y) {
        Area room = Area({
            cell.from.x + 1,
            cell.from.y + 1,
        }, {
            cell.to.x - 1,
            cell.to.y - 1
        });
        // Area room = Area({
        //     cell.from.x,
        //     cell.from.y,
        // }, {
        //     cell.to.x,
        //     cell.to.y
        // });
        node->rooms.push_back(room);
        return node;
    }
    node->area = cell;
    if (cell.size.x > cell.size.y) { // vertical slice
        //int intersection = GetRandomValue(cell.from.x + 2, cell.to.x - 2);
        int intersection = (cell.from.x + cell.to.x) / 2 + GetRandomValue(-2, 2);
        auto [leftCell, rightCell] = divideCellVertically(cell, intersection);
        node->left = genCellTree(leftCell, minSize);
        node->right = genCellTree(rightCell, minSize);
        node->rooms = concatenate(node->left->rooms, node->right->rooms);
        node->pathway = findHorizontalPath(node->left->rooms, node->right->rooms);
    } else { // horizontal slice
        //int intersection = GetRandomValue(cell.from.y + 2, cell.to.y - 2);
        int intersection = (cell.from.y + cell.to.y) / 2 + GetRandomValue(-2, 2);
        auto [upCell, downCell] = divideCellHorizontally(cell, intersection);
        node->left = genCellTree(upCell, minSize);
        node->right = genCellTree(downCell, minSize);
        node->rooms = concatenate(node->left->rooms, node->right->rooms);
        node->pathway = findVerticalPath(node->left->rooms, node->right->rooms);
    }
    return node;
}


// заранее в кажду ноду собрать список всех комнат в этой ноде
//если разрез горизонтальный:
//      выбрать из верхнего списка комнату у которой Y стенка находится ниже всех
//      выбрать из нижнего списка комнату у которой Y стенка находится выше всех, а также from.x и to.x пересекается со стенкой from.x и to.x комнаты выше
//      в центре пересечения будет проход