#pragma once
#include <imgui.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <list>
#include <utility>
#include "helper.hpp"
#include "piece.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include "utils.hpp"

class Piece;

class Echequier {
public:
    // tableau de pièces
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> tab_piece;
    void                                                 initialize_array();

    // fonction draw
    void draw();

    // Position de la pièce sélectionnée :
    position selected_piece_position;
    bool     is_selected = false;
    bool     white_turn  = true;
    position trap_position{};
};
