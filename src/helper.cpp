#include "helper.hpp"
#include "utils.hpp"

// vérifier si les moves sont valides
bool verification(bool white_turn, std::vector<position> moves, bool white_color, int x, int y)
{
    position pos{x, y};
    return white_turn == white_color && std::find(moves.begin(), moves.end(), pos) != moves.end();
}