#pragma once
#include <vector>
#include "Area.hpp"

class CellNode {
    public:
        Area area;
        Area pathway;
        std::vector<Area> rooms;
        CellNode* left = nullptr;
        CellNode* right = nullptr;

        CellNode();
        ~CellNode();
};