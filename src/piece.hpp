#pragma once
#include <imgui.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <utility>
#include "echequier.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include "utils.hpp"

enum Color { white,
             black };

class Echequier;
void moves_straight(position piece_position, std::vector<position>& list_moves, Echequier& echequier);
void moves_diagonal(position piece_position, std::vector<position>& list_moves, Echequier& echequier);

class Piece {
public:
    // Position
    // position    piece_position;
    std::string m_letter;

    Color m_color;

    // virtual Piece reset();
    virtual std::vector<position> moves_possible(position piece_position, Echequier& echequier) = 0;

    Piece() = default;
    Piece(std::string l, Color c)
        : m_letter(std::move(l)), m_color(c) {};

    virtual ~Piece() = default;
};

// moves : avance sauf si un pion de la même couleur est sur son chemin
class Pawn : public Piece {
public:
    // std::string           letter{"P"};
    Pawn(Color c)
        : Piece("P", c)
    {}

    std::vector<position> moves_possible(position piece_position, Echequier& echequier) override;
};

class Tower : public Piece {
public:
    // std::string           letter{"T"};
    Tower(Color c)
        : Piece("T", c)
    {}

    std::vector<position> moves_possible(position piece_position, Echequier& echequier) override;
};

class Bishop : public Piece {
public:
    // std::string           letter{"B"};
    Bishop(Color c)
        : Piece("B", c)
    {}

    std::vector<position> moves_possible(position piece_position, Echequier& echequier) override;
};

class Horse : public Piece {
public:
    // std::string           letter{"H"};
    Horse(Color c)
        : Piece("H", c)
    {}

    std::vector<position> moves_possible(position piece_position, Echequier& echequier) override;
};

class Queen : public Piece {
public:
    // std::string           letter{"Q"};
    Queen(Color c)
        : Piece("Q", c)
    {}

    std::vector<position> moves_possible(position piece_position, Echequier& echequier) override;
};

class King : public Piece {
public:
    // std::string           letter{"K"};
    King(Color c)
        : Piece("K", c)
    {}

    std::vector<position> moves_possible(position piece_position, Echequier& echequier) override;
};

void afficher_moves_possible(const std::vector<position>& list_moves, int x, int y);
