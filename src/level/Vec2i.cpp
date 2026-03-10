#include <cmath>
#include "Vec2i.hpp"

Vec2i Vec2i::operator-(Vec2i b) const {
        return Vec2i {
            x - b.x, 
            y - b.y
        };
}

Vec2i Vec2i::operator+(Vec2i b) const {
        return Vec2i {
            x + b.x, 
            y + b.y
        };
}

Vec2i Vec2i::abs() const {
    return Vec2i {
        std::abs(x), 
        std::abs(y)
    };
}