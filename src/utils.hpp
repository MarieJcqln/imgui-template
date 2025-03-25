#pragma once

struct position {
    int x;
    int y;

    bool operator==(position p) const
    {
        return this->x == p.x && this->y == p.y;
    };
};