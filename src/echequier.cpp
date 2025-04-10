#include "echequier.hpp"
#include "helper.hpp"
#include "math.hpp"
#include "piece.hpp"
#include "utils.hpp"

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

void Echequier::draw(std::vector<std::vector<int>> couleurs)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{1.0f, 1.0f});

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 1.f}); // initialisation of the color of all buttons until we call ImGui::PopStyleColor(). There is also ImGuiCol_ButtonActive and ImGuiCol_ButtonHovered

    // ImGui::PushID(2); // When some ImGui items have the same label (for exemple the next two buttons are labeled "Yo") ImGui needs you to specify an ID so that it can distinguish them. It can be an int, a pointer, a string, etc.
    //  You will definitely run into this when you create a button for each of your chess pieces, so remember to give them an ID!
    // ImGui::Button("", ImVec2{50.f, 50.f});

    // ImGui::PopID(); // Then pop the id you pushed after you created the widget

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
                // Apply white background for the white squares
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.f, 1.f, 1.f, 1.f});
            }
            else
            {
                // ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 1.f}); // Noir
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{static_cast<float>(couleurs[1][0]) / 255, static_cast<float>(couleurs[1][1]) / 255, static_cast<float>(couleurs[1][2]) / 255, 1.f});
            }

            // Si on a fait un PushStyleColor(), on fait un PopStyleColor()
            // if (hasPushedColor)
            // {
            //     ImGui::PopStyleColor();
            //     hasPushedColor = false;
            // }

            ImGui::PushID(compteur);

            std::string label = (tab_piece[y][x] ? tab_piece[y][x]->m_letter : ""); // si la case est nullptr on retourne un bouton vide, sinon on récupère m_lettre

            // Verifie qu'une piece est sur cette case et on lui applique une couleur a cette case correpondant a la couleur du pion
            // pour l'instant on ne voit pas cette couleur

            // if (tab_piece[y][x] != nullptr)
            // {
            //     ImVec4 color = (tab_piece[y][x]->m_color == white) ? ImVec4(0.0f, 0.0f, 0.5f, 1.0f)  // Bleu foncé
            //                                                        : ImVec4(0.0f, 0.0f, 0.9f, 1.0f); // Bleu clair
            //     ImGui::PushStyleColor(ImGuiCol_Button, color);
            //     ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.x + 0.1f, color.y + 0.1f, color.z + 0.1f, 1.0f));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.x + 0.2f, color.y + 0.2f, color.z + 0.2f, 1.0f));
            // }

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
                        //  Elle devient sélectionné.
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
