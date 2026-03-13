#pragma once
#include <vector>
#include "Area.hpp"

class CellNode {
    public:
        Area area;
        Area pathway;
        std::vector<Area> rooms;
        CellNode* left;
        CellNode* right;

        CellNode();
        ~CellNode();
};