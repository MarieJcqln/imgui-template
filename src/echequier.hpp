#pragma once

#include <imgui.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <list>
#include <memory>
#include <utility>
#include <vector>
#include "Model3d.hpp"
#include "helper.hpp"
#include "piece.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include "texture.hpp"
#include "utils.hpp"


class Piece;
class Model3D;
class Texture;

/// ajout structure pour suivre les pieces 3D
struct Piece3DInfo {
    int  model_index;
    int  instance_index;
    bool on_board;
};

class Echequier {
private:
    Texture* texture;

public:
    void initialize_textures(); // initalise texture

    // tableau de pièces
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> tab_piece;
    void                                                 initialize_array();

    /////////// 3D
    /// tableau pour stocker les info 3D de chaque pièce
    // std::array<std::array<Piece3DInfo, 8>, 8> pieces_3d_info;
    // tableau de ointeur vers les modèles 3D
    // Model3D** models;

    //// fonctions pour synchro 3D
    // void initialize_3d_info();
    // initialiser les info des model 3D
    // void update_3d_models(int from_x, int from_y, int to_x, int to_y); // mettre à jour les modèles 3D après un mvt
    ////////////////

    // fonction draw
    void draw(std::vector<std::vector<int>> couleurs);

    // position de la pièce sélectionnée :
    position selected_piece_position;
    bool     is_selected = false;
    bool     white_turn  = true;
    position trap_position{};
    bool     check_end_game();
    bool     promotion_pending = false;
    position promotion_position{};
};
