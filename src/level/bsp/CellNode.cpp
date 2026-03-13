#include "CellNode.hpp"

CellNode::CellNode() : left(nullptr), right(nullptr) {
    
}

CellNode::~CellNode() {
    delete left;
    delete right;
}