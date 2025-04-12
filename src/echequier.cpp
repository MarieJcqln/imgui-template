#include "echequier.hpp"
#include <glm/gtc/matrix_transform.hpp> //pour glm::translate, rotate, scale
#include "helper.hpp"
#include "math.hpp"
#include "piece.hpp"
#include "utils.hpp"

// extern Texture texture;
// void           Echequier::initialize_textures()
// {
//     // Load toutes les texture de piece
//     texture->loadTexture("white_king", "../../textures/oscar_white.png");
//     texture->loadTexture("white_queen", "../../textures/golden_disk_black.png");
//     texture->loadTexture("white_bishop", "../../textures/grammy_white.png");
//     texture->loadTexture("white_knight", "../../textures/mtv_white.png");
//     texture->loadTexture("white_rook", "../../textures/golden_globe_white.png");
//     texture->loadTexture("white_pawn", "../../textures/golden_palm_white.png");

//     texture->loadTexture("black_king", "../../textures/oscar_black.png");
//     texture->loadTexture("black_queen", "../../textures/golden_disk_black.png");
//     texture->loadTexture("black_bishop", "../../textures/grammy_black.png");
//     texture->loadTexture("black_knight", "../../textures/mtv_black.png");
//     texture->loadTexture("black_rook", "../../textures/golden_globe_white.png");
//     texture->loadTexture("black_pawn", "../../textures/golden_palm_white.png");
// }

void Echequier::initialize_array()
{
    tab_piece[0][0] = std::make_unique<Tower>(Color::black);  // T
    tab_piece[0][1] = std::make_unique<Horse>(Color::black);  // C
    tab_piece[0][2] = std::make_unique<Bishop>(Color::black); // F
    tab_piece[0][3] = std::make_unique<King>(Color::black);   // K
    tab_piece[0][4] = std::make_unique<Queen>(Color::black);  // O
    tab_piece[0][5] = std::make_unique<Bishop>(Color::black); // F
    tab_piece[0][6] = std::make_unique<Horse>(Color::black);  // C
    tab_piece[0][7] = std::make_unique<Tower>(Color::black);  // T
    for (int i{0}; i < 8; i++)                                // Px8
    {
        tab_piece[1][i] = std::make_unique<Pawn>(Color::black);
    }
    for (int i{0}; i < 8; i++)
    {
        for (int y{2}; y < 6; y++) // Px8
        {
            tab_piece[y][i] = nullptr;
        }
    }
    for (int i{0}; i < 8; i++) // Px8
    {
        tab_piece[6][i] = std::make_unique<Pawn>(Color::white);
    }
    tab_piece[7][0] = std::make_unique<Tower>(Color::white);  // T
    tab_piece[7][1] = std::make_unique<Horse>(Color::white);  // C
    tab_piece[7][2] = std::make_unique<Bishop>(Color::white); // F
    tab_piece[7][3] = std::make_unique<King>(Color::white);   // K
    tab_piece[7][4] = std::make_unique<Queen>(Color::white);  // O
    tab_piece[7][5] = std::make_unique<Bishop>(Color::white); // F
    tab_piece[7][6] = std::make_unique<Horse>(Color::white);  // C
    tab_piece[7][7] = std::make_unique<Tower>(Color::white);  // T

    // Initialiser la position piégée
    trap_position = {.x = 3, .y = 3};
}

void path_choice() {}

// initialisation tab pieces_3d_info
// void Echequier::initialize_3d_info()
// {
//
//     for (int y = 0; y < 8; y++)
//     {
//         for (int x = 0; x < 8; x++)
//         {
//             pieces_3d_info[y][x] = {-1, -1, false}; // Pas de modèle, pas d'instance
//         }
//     }

//     // asignation des pieces initiale
//     // Tour
//     pieces_3d_info[0][0] = {6, 0, true}; // noir
//     pieces_3d_info[0][7] = {6, 1, true}; // noir
//     pieces_3d_info[7][0] = {6, 2, true}; // blanc
//     pieces_3d_info[7][7] = {6, 3, true}; // blanc

//     // Cavalier
//     pieces_3d_info[0][1] = {3, 0, true};
//     pieces_3d_info[0][6] = {3, 1, true};
//     pieces_3d_info[7][1] = {3, 2, true};
//     pieces_3d_info[7][6] = {3, 3, true};

//     // Fou
//     pieces_3d_info[0][2] = {2, 0, true};
//     pieces_3d_info[0][5] = {2, 1, true};
//     pieces_3d_info[7][2] = {2, 2, true};
//     pieces_3d_info[7][5] = {2, 3, true};

//     // Roi
//     pieces_3d_info[0][3] = {1, 0, true};
//     pieces_3d_info[7][3] = {1, 1, true};

//     // Reine
//     pieces_3d_info[0][4] = {4, 0, true};
//     pieces_3d_info[7][4] = {4, 1, true};

//     // Pion
//     for (int i = 0; i < 8; i++)
//     {
//         pieces_3d_info[1][i] = {5, i, true};     // noir
//         pieces_3d_info[6][i] = {5, i + 8, true}; // blanc
//     }
// }

// void Echequier::update_3d_models(int from_x, int from_y, int to_x, int to_y)
// {
//     if (!models)
//     {
//         std::cerr << "Le tableau models n'est pas initialisé!" << std::endl;
//         return;
//     }

//     // Vérifications pour la case de départ
//     if (from_y >= 0 && from_y < 8 && from_x >= 0 && from_x < 8 && pieces_3d_info[from_y][from_x].on_board)
//     {
//         int model_index    = pieces_3d_info[from_y][from_x].model_index;
//         int instance_index = pieces_3d_info[from_y][from_x].instance_index;

//         // Vérification plus stricte des index
//         if (model_index >= 1 && model_index <= 6)
//         {
//             if (models[model_index] != nullptr)
//             {
//                 // Si la case de départ contient une pièce avec des infos 3D

//                 if (pieces_3d_info[from_y][from_x].on_board)
//                 {
//                     // Récupérer les informations 3D de la pièce
//                     int model_index    = pieces_3d_info[from_y][from_x].model_index;
//                     int instance_index = pieces_3d_info[from_y][from_x].instance_index;

//                     if (model_index >= 1 && model_index <= 6 && models[model_index] != nullptr)
//                     { // on verifie que l'index est valide
//                         // verifie si c'est une piece blanche?
//                         bool is_white = from_y >= 6 || (from_y == 7); // Les pièces blanches commencent sur les rangées 6 et 7

//                         // Calculer la nouvelle position 3D
//                         float spacing = 1.0f;
//                         int   z_pos   = to_y;

//                         // symétrie sur l'axe z pour les blancs
//                         if (is_white)
//                         {
//                             z_pos = 7 - z_pos;
//                         }

//                         glm::vec3 position  = glm::vec3(to_x * spacing, 0.0f, z_pos * spacing);
//                         glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);

//                         // Rotation des blancs pour qu'ils soient face aux noirs
//                         if (is_white)
//                         {
//                             transform = glm::rotate(transform, glm::radians(180.0f), glm::vec3(0, 1, 0));
//                         }

//                         // Mettre à jour la matrice de transformation de l'instance
//                         models[model_index]->update_instance(instance_index, transform);

//                         // Mettre à jour les informations 3D
//                         pieces_3d_info[to_y][to_x]     = pieces_3d_info[from_y][from_x];
//                         pieces_3d_info[from_y][from_x] = {-1, -1, false};
//                     }
//                 }

//                 // Si une pièce était à la destination, elle a été capturée
//                 if (pieces_3d_info[to_y][to_x].on_board)
//                 {
//                     int captured_model_index    = pieces_3d_info[to_y][to_x].model_index;
//                     int captured_instance_index = pieces_3d_info[to_y][to_x].instance_index;

//                     if (captured_model_index >= 0 && captured_model_index < 7)
//                     {
//                         // Déplacer la pièce capturée hors de l'échiquier ou la rendre invisible
//                         // Par exemple, la déplacer sous le plateau
//                         glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, -5.0f, -10.0f));
//                         models[captured_model_index]->update_instance(captured_instance_index, transform);
//                     }
//                 }
//                 // Mise à jour des info 3D après avoir vérifié que tout est valide
//                 Piece3DInfo old_info           = pieces_3d_info[from_y][from_x];
//                 pieces_3d_info[to_y][to_x]     = old_info;
//                 pieces_3d_info[from_y][from_x] = {-1, -1, false};
//             }
//             else
//             {
//                 std::cerr << "Pointeur de modèle nul pour l'index " << model_index << std::endl;
//             }
//         }
//         else
//         {
//             std::cerr << "Index de modèle invalide: " << model_index << std::endl;
//         }
//     }
//     // Vérifications pour la case de destination (pièce capturée)
//     if (to_y >= 0 && to_y < 8 && to_x >= 0 && to_x < 8 && pieces_3d_info[to_y][to_x].on_board)
//     {
//         int captured_model_index    = pieces_3d_info[to_y][to_x].model_index;
//         int captured_instance_index = pieces_3d_info[to_y][to_x].instance_index;

//         if (captured_model_index >= 1 && captured_model_index <= 6)
//         {
//             if (models[captured_model_index] != nullptr)
//             {
//                 // Code pour la pièce capturée
//                 glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, -5.0f, -10.0f));
//                 models[captured_model_index]->update_instance(captured_instance_index, transform);
//             }
//             else
//             {
//                 std::cerr << "Pointeur de modèle nul pour la pièce capturée (index " << captured_model_index << ")" << std::endl;
//             }
//         }
//         else
//         {
//             std::cerr << "Index de modèle invalide pour la pièce capturée: " << captured_model_index << std::endl;
//         }
//     }
// }

void Echequier::draw(std::vector<std::vector<int>> couleurs)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{1.0f, 1.0f});

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 1.f}); // initialisation of the color of all buttons until we call ImGui::PopStyleColor(). There is also ImGuiCol_ButtonActive and ImGuiCol_ButtonHovered

    bool  hasPushedColor = false; // Vérifier si on a push une couleur
    int   compteur{0};
    Color promotion_color{};
    for (int y{0}; y < 8; y++)
    {                              // line
        for (int x{0}; x < 8; x++) // column
        {
            bool isWhite = (y + x) % 2 == 0;
            if (isWhite)
            {
                // fond balcn pour carrée blacn
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.f, 1.f, 1.f, 1.f});
            }
            else
            {
                // ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 1.f}); // Noir
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{static_cast<float>(couleurs[1][0]) / 255, static_cast<float>(couleurs[1][1]) / 255, static_cast<float>(couleurs[1][2]) / 255, 1.f});
            }

            ImGui::PushID(compteur);
            ///////////////:3D
            // on implemente la texture de la piece si y en a une sur cette case
            // GLuint textureID = 0;
            ///////////////

            std::string label = (tab_piece[y][x] ? tab_piece[y][x]->m_letter : ""); // si la case est nullptr on retourne un bouton vide, sinon on récupère m_lettre

            if (tab_piece[y][x] != nullptr && is_selected && selected_piece_position.x == x && selected_piece_position.y == y)
            {
                if (tab_piece[y][x]->m_color == Color::white)
                {
                    ImGui::PopStyleColor();                                              // Remove the black/white background
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.5f, 1.f}); // Blue for white pieces
                    hasPushedColor = true;
                }
                else
                {
                    ImGui::PopStyleColor();                                              // Remove the black/white background
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.9f, 1.f}); // Light blue for black pieces
                    hasPushedColor = true;
                }
            }

            if (is_selected)
            {
                if (ImGui::IsMouseClicked(1))
                {
                    is_selected = false;
                }
                afficher_moves_possible(tab_piece[selected_piece_position.y][selected_piece_position.x]->moves_possible(selected_piece_position, *this), x, y);
            }
            if (ImGui::Button(label.c_str(), ImVec2{50.f, 50.f}))
            {
                std::cout << "Clicked button " << y << "," << x << std::endl;

                // Si je click sur une pièce => is_selected = true;
                // Si is_selected = true, ET que je click sur une une case "nullptr" ET que le mouvement est "légal" => déplacement
                // si je sélectionne une pièce
                if (!is_selected) // si une piece sur la case actuelle est selectionnée // si l'affirmation dans la parenthese est vrai alors on rentre dans la condition
                {
                    if (tab_piece[y][x] != nullptr) // si case contient un pion
                    {
                        //  elle devient sélectionné.
                        is_selected               = true;
                        selected_piece_position.x = x;
                        selected_piece_position.y = y;

                        // si clic droit => désélectionné
                        //  Affichage de la position de la pièce sélectionnée
                        std::cout << "Letter: " << tab_piece[y][x]->m_letter << std::endl;
                        std::cout << "Color: " << tab_piece[y][x]->m_color << std::endl;
                    }

                    else
                    {
                        std::cout << "No pawn at this position" << std::endl;
                    }
                }
                else if (is_selected)
                {
                    auto Moves{tab_piece[selected_piece_position.y][selected_piece_position.x]->moves_possible(selected_piece_position, *this)};

                    // Affichage des mouvements possibles
                    std::cout << "Moves: ";
                    for (const auto& move : Moves)
                    {
                        std::cout << move << " "; // Utilise l'opérateur << surchargé pour position
                    }
                    std::cout << '\n';

                    if (tab_piece[y][x] == nullptr && verification(white_turn, Moves, tab_piece[selected_piece_position.y][selected_piece_position.x]->m_color == white, x, y))
                    {
                        /////////////3D
                        // /// enregistrement des positions initial et finale avant de deplacer la piece 3D
                        // int from_x {selected_piece_position.x};
                        // int from_y {selected_piece_position.y};
                        // int to_x {x};
                        // int to_y {y};
                        /////////////////////:
                        tab_piece[y][x] = std::move(tab_piece[selected_piece_position.y][selected_piece_position.x]);
                        //  si je click (  if (ImGui::Button(label.c_str(), ImVec2{50.f, 50.f}))) sur une case tab_piece[y][x] = nullptr et que le mouvement est OK
                        //  => La pièce en selected_piece_position bouge sur la case tab_piece[y][x] = nullptr (tab_piece[y][x] = std::move(tab_piece[selected_piece_position.y][selected_pice_position.x]))
                        tab_piece[selected_piece_position.y][selected_piece_position.x] = nullptr;
                        // Vérifier si un pion arrive au bout
                        if (tab_piece[y][x] && tab_piece[y][x]->m_letter == "P" && ((tab_piece[y][x]->m_color == Color::white && y == 0) || (tab_piece[y][x]->m_color == Color::black && y == 7)))
                        {
                            std::cout << "Le pion est arrivé au bout" << '/n';
                            promotion_pending  = true;
                            promotion_position = {.x = x, .y = y};
                            promotion_color    = tab_piece[y][x]->m_color;
                            // ImGui::OpenPopup("Promotion");
                        }

                        // On vérifie si la pièce est sur le piège
                        tab_piece[trap_position.y][trap_position.x] = nullptr;
                        std::cout << "Votre pièce est tombée dans le piège ! Pas de chance ..." << '\n';

                        is_selected = false;
                        white_turn  = !white_turn;

                        // Vérifier et déplacer la case piégée
                        std::pair<int, int> next_trap{};
                        next_trap       = next_markov_position(trap_position.x, trap_position.y, build_transition_matrix());
                        trap_position.x = next_trap.first;
                        trap_position.y = next_trap.second;
                        // fin du tour
                    }
                    else if (
                        tab_piece[y][x] != nullptr &&                                                                           // Il y a une pièce
                        tab_piece[y][x]->m_color != tab_piece[selected_piece_position.y][selected_piece_position.x]->m_color && // Elle est de l'autre couleur
                        verification(white_turn, Moves, tab_piece[selected_piece_position.y][selected_piece_position.x]->m_color == white, x, y)
                    ) // Le mouvement est valide
                    {
                        // Capture
                        tab_piece[y][x]                                                 = std::move(tab_piece[selected_piece_position.y][selected_piece_position.x]);
                        tab_piece[selected_piece_position.y][selected_piece_position.x] = nullptr;

                        // Vérifier si un pion arrive au bout
                        if (tab_piece[y][x] && tab_piece[y][x]->m_letter == "P" && ((tab_piece[y][x]->m_color == Color::white && y == 0) || (tab_piece[y][x]->m_color == Color::black && y == 7)))
                        {
                            std::cout << "Le pion est arrivé au bout" << '/n';
                            promotion_pending  = true;
                            promotion_position = {.x = x, .y = y};
                            promotion_color    = tab_piece[y][x]->m_color;
                            // ImGui::OpenPopup("Promotion");
                        }

                        tab_piece[trap_position.y][trap_position.x] = nullptr;
                        std::cout << "Votre pièce est tombée dans le piège ! Pas de chance ..." << '\n';

                        is_selected = false;
                        white_turn  = !white_turn;

                        // Vérifier et déplacer la case piégée
                        std::pair<int, int> next_trap{};
                        next_trap       = next_markov_position(trap_position.x, trap_position.y, build_transition_matrix());
                        trap_position.x = next_trap.first;
                        trap_position.y = next_trap.second;
                        // fin du tour
                    }

                    else if (x == selected_piece_position.x && y == selected_piece_position.y)
                    {
                        // si la même case est selectionnée => on eneleve la selection et donc la couleur
                        is_selected = false;
                    }
                }
            }

            ImGui::PopID();

            ImGui::PopStyleColor();

            if ((compteur + 1) % 8 != 0)
            {
                ImGui::SameLine();
            }
            compteur++;
        }
    }

    if (promotion_pending)
    {
        ImGui::OpenPopup("Promotion");
    }
    if (ImGui::BeginPopupModal("Promotion", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Choisissez une pièce pour la promotion :");

        if (ImGui::Button("Reine"))
        {
            tab_piece[promotion_position.y][promotion_position.x] = std::make_unique<Queen>(promotion_color);
            promotion_pending                                     = false;
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::Button("Fou"))
        {
            tab_piece[promotion_position.y][promotion_position.x] = std::make_unique<Bishop>(promotion_color);
            promotion_pending                                     = false;
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::Button("Cavalier"))
        {
            tab_piece[promotion_position.y][promotion_position.x] = std::make_unique<Horse>(promotion_color);
            promotion_pending                                     = false;
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::Button("Tour"))
        {
            tab_piece[promotion_position.y][promotion_position.x] = std::make_unique<Tower>(promotion_color);
            promotion_pending                                     = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    //  ImGui::PopStyleColor();
    ImGui::PopStyleColor(); // Pop the initial button color
    ImGui::PopStyleVar();
    if (check_end_game())
    {
        ImGui::OpenPopup("Fin de Partie");
    }
    ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_Always);
    if (ImGui::BeginPopupModal("Fin de Partie", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("%s", "Fin de Partie");
        if (ImGui::Button("Fermer"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

bool Echequier::check_end_game()
{
    bool whiteKingFound = false;
    bool blackKingFound = false;

    for (const auto& row : tab_piece)
    {
        for (const auto& piece : row)
        {
            if (piece)
            {
                if (piece->m_letter == "K" && piece->m_color == Color::white)
                    whiteKingFound = true;
                else if (piece->m_letter == "K" && piece->m_color == Color::black)
                    blackKingFound = true;
            }
        }
    }

    if (!whiteKingFound)
    {
        std::cout << "Le roi blanc est tombé. Victoire des noirs !" << std::endl;
        return true;
    }

    if (!blackKingFound)
    {
        std::cout << "Le roi noir est tombé. Victoire des blancs !" << std::endl;
        return true;
    }

    return false; // Les deux rois sont encore là
}
