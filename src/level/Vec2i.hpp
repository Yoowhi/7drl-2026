#pragma once

struct Vec2i {
    int x;
    int y;

    Vec2i operator-(Vec2i b) const;
    Vec2i operator+(Vec2i b) const;
    Vec2i abs() const;
};