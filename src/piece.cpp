#include "piece.hpp"

std::vector<position> Pawn::moves_possible()
{
    std::vector<position> list_moves{};
    if (color == white)
    {
        list_moves.emplace_back(piece_position.x - 8, piece_position.y); // emplace back = pushback
    }
    else if (color == black)
    {
        list_moves.emplace_back(piece_position.x + 8, piece_position.y);
    }
    return list_moves;
}

std::vector<position> Tower::moves_possible()
{
    std::vector<position> list_moves{};

    // Avance en ligne jusqu'à rencontrer une piece

    return list_moves;
}

std::vector<position> Bishop::moves_possible()
{
    std::vector<position> list_moves{};

    // Avance en diagonale jusqu'à rencontrer une piece

    return list_moves;
}

std::vector<position> Horse::moves_possible()
{
    std::vector<position> list_moves{};

    // Avance en L
    list_moves.emplace_back(piece_position.x + 3, piece_position.y + 1);
    list_moves.emplace_back(piece_position.x + 3, piece_position.y - 1);
    list_moves.emplace_back(piece_position.x - 3, piece_position.y + 1);
    list_moves.emplace_back(piece_position.x - 3, piece_position.y - 1);

    list_moves.emplace_back(piece_position.x + 1, piece_position.y + 3);
    list_moves.emplace_back(piece_position.x - 1, piece_position.y + 3);
    list_moves.emplace_back(piece_position.x + 1, piece_position.y - 3);
    list_moves.emplace_back(piece_position.x - 1, piece_position.y - 3);

    return list_moves;
}

std::vector<position> Queen::moves_possible()
{
    std::vector<position> list_moves{};

    // Avance en ligne et diagonale

    return list_moves;
}

std::vector<position> King::moves_possible()
{
    std::vector<position> list_moves{};

    // Avance de 1 dans toutes les directions
    list_moves.emplace_back(piece_position.x + 1, piece_position.y + 1);
    list_moves.emplace_back(piece_position.x - 1, piece_position.y - 1);
    list_moves.emplace_back(piece_position.x + 1, piece_position.y - 1);
    list_moves.emplace_back(piece_position.x - 1, piece_position.y + 1);
    list_moves.emplace_back(piece_position.x + 1, piece_position.y);
    list_moves.emplace_back(piece_position.x, piece_position.y + 1);
    list_moves.emplace_back(piece_position.x - 1, piece_position.y);
    list_moves.emplace_back(piece_position.x, piece_position.y - 1);

    return list_moves;
}