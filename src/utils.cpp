#include "utils.hpp"

std::ostream& operator<<(std::ostream& os, const position& pos)
{
    os << "(" << pos.x << ", " << pos.y << ")";
    return os;
}