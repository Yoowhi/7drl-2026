#include "CellNode.hpp"

CellNode::CellNode() {
    
}

CellNode::~CellNode() {
    delete left;
    delete right;
}