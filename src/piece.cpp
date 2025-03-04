#include "piece.hpp"

void moves_straight(position piece_position, std::vector<position>& list_moves)
{
    // std::vector<position> list_moves{};

    // Avance en ligne jusqu'à rencontrer une piece
    int i{0};
    while ("pas de pièce au dessus et sur le plateau")
    {
        list_moves.emplace_back(piece_position.x, piece_position.y + i);
        i++;
    }
    while ("pas de pièce en dessous")
    {
        list_moves.emplace_back(piece_position.x, piece_position.y - i);
        i++;
    }
    while ("pas de pièce a droite")
    {
        list_moves.emplace_back(piece_position.x + i, piece_position.y);
        i++;
    }
    while ("pas de pièce a gauche")
    {
        list_moves.emplace_back(piece_position.x - i, piece_position.y);
        i++;
    }

    // return list_moves;
}

void moves_diagonal(position piece_position, std::vector<position>& list_moves)
{
    // std::vector<position> list_moves{};

    // Avance en diagonale jusqu'à rencontrer une piece
    int i{0};
    int j{0};
    while ("pas de pièce au dessus à droite")
    {
        list_moves.emplace_back(piece_position.x + i, piece_position.y + j);
        i++;
        j++;
    }
    while ("pas de pièce au dessus à gauche")
    {
        list_moves.emplace_back(piece_position.x - i, piece_position.y + j);
        i++;
        j++;
    }
    while ("pas de pièce en dessous à droite")
    {
        list_moves.emplace_back(piece_position.x + i, piece_position.y - j);
        i++;
        j++;
    }
    while ("pas de pièce en dessous à gauche")
    {
        list_moves.emplace_back(piece_position.x - i, piece_position.y - j);
        i++;
        j++;
    }

    // return list_moves;
}

std::vector<position> Pawn::moves_possible(position piece_position)
{
    std::vector<position> list_moves{};
    if (m_color == white)
    {
        list_moves.emplace_back(piece_position.x - 8, piece_position.y); // emplace back = pushback
    }
    else if (m_color == black)
    {
        list_moves.emplace_back(piece_position.x + 8, piece_position.y);
    }
    return list_moves;
}

std::vector<position> Tower::moves_possible(position piece_position)
{
    std::vector<position> list_moves{};
    moves_straight(piece_position, list_moves);
    return list_moves;
}

std::vector<position> Bishop::moves_possible(position piece_position)
{
    std::vector<position> list_moves{};
    moves_diagonal(piece_position, list_moves);
    return list_moves;
}

std::vector<position> Horse::moves_possible(position piece_position)
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

std::vector<position> Queen::moves_possible(position piece_position)
{
    std::vector<position> list_moves{};

    // Avance en ligne et diagonale
    moves_diagonal(piece_position, list_moves);
    moves_straight(piece_position, list_moves);

    return list_moves;
}

std::vector<position> King::moves_possible(position piece_position)
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