#pragma once
#include "helpers.hpp"
#include "Area.hpp"
#include "CellNode.hpp"
#include <memory>

CellNode* genCellTree(Area cell, Vec2i minSize);