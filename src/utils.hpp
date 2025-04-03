#pragma once
#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

struct position {
    int x;
    int y;

    bool operator==(position p) const
    {
        return this->x == p.x && this->y == p.y;
    };
};
std::ostream& operator<<(std::ostream& os, const position& pos);
#endif