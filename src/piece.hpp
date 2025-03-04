#pragma once
#include <imgui.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <utility>
#include "quick_imgui/quick_imgui.hpp"

struct position {
    int x;
    int y;
};
void moves_straight(position piece_position, std::vector<position>& list_moves);
void moves_diagonal(position piece_position, std::vector<position>& list_moves);

class Piece {
public:
    // Position
    // position    piece_position;
    std::string m_letter;

    enum Color { white,
                 black };
    Color m_color;

    // virtual Piece reset();
    virtual std::vector<position> moves_possible(position piece_position) = 0;

    Piece() = default;
    Piece(std::string l, Color c)
        : m_letter(std::move(l)), m_color(c) {};

    virtual ~Piece() = default;
};
// moves : avance sauf si un pion de la même couleur est sur son chemin
class Pawn : public Piece {
    // std::string           letter{"P"};
    Pawn(Color c)
        : Piece("P", c)
    {}

    std::vector<position> moves_possible(position piece_position) override;
};

class Tower : public Piece {
    // std::string           letter{"T"};
    Tower(Color c)
        : Piece("T", c)
    {}

    std::vector<position> moves_possible(position piece_position) override;
};

class Bishop : public Piece {
    // std::string           letter{"B"};
    Bishop(Color c)
        : Piece("B", c)
    {}

    std::vector<position> moves_possible(position piece_position) override;
};

class Horse : public Piece {
    // std::string           letter{"H"};
    Horse(Color c)
        : Piece("H", c)
    {}

    std::vector<position> moves_possible(position piece_position) override;
};

class Queen : public Piece {
    // std::string           letter{"Q"};
    Queen(Color c)
        : Piece("Q", c)
    {}

    std::vector<position> moves_possible(position piece_position) override;
};

class King : public Piece {
    // std::string           letter{"K"};
    King(Color c)
        : Piece("K", c)
    {}

    std::vector<position> moves_possible(position piece_position) override;
};
