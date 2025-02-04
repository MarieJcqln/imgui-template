#pragma once
#include <imgui.h>
#include <algorithm>
#include <iostream>
#include <list>
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
    position    piece_position;
    std::string letter;

    enum Color { white,
                 black };
    Color color;

    // virtual Piece reset();
    virtual std::vector<position> moves_possible();

    virtual ~Piece() = default;
};
// moves : avance sauf si un pion de la même couleur est sur son chemin
class Pawn : public Piece {
    std::string           letter{"P"};
    std::vector<position> moves_possible() override;
};

class Tower : public Piece {
    std::string           letter{"T"};
    std::vector<position> moves_possible() override;
};

class Bishop : public Piece {
    std::string           letter{"B"};
    std::vector<position> moves_possible() override;
};

class Horse : public Piece {
    std::string           letter{"H"};
    std::vector<position> moves_possible() override;
};

class Queen : public Piece {
    std::string           letter{"Q"};
    std::vector<position> moves_possible() override;
};

class King : public Piece {
    std::string           letter{"B"};
    std::vector<position> moves_possible() override;
};
