#include "Area.hpp"

Area::Area(Vec2i from, Vec2i to) : from(from), to(to) {
    size = (to - from).abs();
}

Area::Area() {
    
}