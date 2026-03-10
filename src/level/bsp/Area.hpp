#pragma once
#include "../Vec2i.hpp"

class Area {
    public:
        Vec2i from;
        Vec2i to;
        Vec2i size;

        Area();
        Area(Vec2i from, Vec2i to);
};