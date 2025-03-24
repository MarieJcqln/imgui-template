#include "echequier.hpp"

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
}

void enable_white_or_black(bool white)
{
    // const bool itemHovered = ImGui::IsItemHoveredRect() && ImGui::IsWindowHovered();
    if (white == true)
    {
        // bool itemHovered = false;
        // Needs the ImRect (bb) and the ID (id):
        // ImGui::ButtonBehavior(bb, id, &itemHovered, NULL);
        // on "desactive" le jeu des noirs
        // on appelle la class pour pion blanc
        // enlever le hover des noirs
    }
    else
    {
        // on "desactive" le jeu des blancs
        // on appelle la class pour pion noir
        // enlever le hover des blancs
    }
}

void path_choice() {}

void Echequier::draw()
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{1.0f, 1.0f});

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 1.f}); // initialisation of the color of all buttons until we call ImGui::PopStyleColor(). There is also ImGuiCol_ButtonActive and ImGuiCol_ButtonHovered

    // ImGui::PushID(2); // When some ImGui items have the same label (for exemple the next two buttons are labeled "Yo") ImGui needs you to specify an ID so that it can distinguish them. It can be an int, a pointer, a string, etc.
    //  You will definitely run into this when you create a button for each of your chess pieces, so remember to give them an ID!
    // ImGui::Button("", ImVec2{50.f, 50.f});

    // ImGui::PopID(); // Then pop the id you pushed after you created the widget

    bool hasPushedColor = false; // Vérifier si on a push une couleur
    int  compteur{0};
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
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 1.f}); // Noir
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
                        // Position clicked_position = {x,y}
                        //  Elle devient sélectionné.
                        is_selected               = true;
                        selected_piece_position.x = x;
                        selected_piece_position.y = y;
                        // si clic droit => désélectionné
                        //  Affichage de la position de la pièce sélectionnée
                        std::cout << "Letter: " << tab_piece[y][x]->m_letter << std::endl;
                        std::cout << "Color: " << tab_piece[y][x]->m_color << std::endl;

                        // le bouton change de couleur (bleu foncé)

                        // ICI Marie du futur : il faut continuer les fonctions gérant les moves en faisant attention aux doubles dépendances (résolu par max)
                        //  path_choice(); // on montre les différents chemin possible pour le pion cliqué

                        // appeler moves possible
                    }

                    else
                    {
                        std::cout << "No pawn at this position" << std::endl;
                    }
                }
                else if (is_selected)
                {
                    if (tab_piece[y][x] == nullptr)
                    {
                        // si le move est ok
                        tab_piece[y][x] = std::move(tab_piece[selected_piece_position.y][selected_piece_position.x]);
                        //  si je click (  if (ImGui::Button(label.c_str(), ImVec2{50.f, 50.f}))) sur une case tab_piece[y][x] = nullptr et que le mouvement est OK
                        //  => La pièce en selected_piece_position bouge sur la case tab_piece[y][x] = nullptr (tab_piece[y][x] = std::move(tab_piece[selected_piece_position.y][selected_pice_position.x]))
                        tab_piece[selected_piece_position.y][selected_piece_position.x] = nullptr;
                        is_selected                                                     = false;
                    }
                    else if (x == selected_piece_position.x && y == selected_piece_position.y)
                    {
                        // Added: clicking same piece again deselects it
                        is_selected = false;
                    }
                }
            }

            ImGui::PopID();
            // pop la couleur de la case quand la case est pressée
            // on va donc voir la couleur apliqué initlament
            // if (tab_piece[y][x] != nullptr && is_selected && selected_piece_position.x == x && selected_piece_position.y == y)
            // {

            // }
            // Pop la couleur de la case (noir/blanc)
            ImGui::PopStyleColor();

            // hasPushedColor = false;

            if ((compteur + 1) % 8 != 0)
            {
                ImGui::SameLine();
            }
            compteur++;
        }
    }

    // ImGui::PopStyleColor();
    ImGui::PopStyleColor(); // Pop the initial button color
    ImGui::PopStyleVar();
}
