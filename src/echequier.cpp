#include "echequier.hpp"

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

void Echequier::draw()
{
    quick_imgui::loop(
        "Chess",
        /* init: */ [&]() {},
        /* loop: */
        [&]() {
            ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!

            ImGui::Begin("Example");
            // std::cout << "33";
            // echequier(tab_piece); // on creer l'echequier avec les bouton et les lettres

            // Draw the next ImGui widget on the same line as the previous one. Otherwise it would be below it

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{1.0f, 1.0f});

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 1.f}); // Changes the color of all buttons until we call ImGui::PopStyleColor(). There is also ImGuiCol_ButtonActive and ImGuiCol_ButtonHovered

            // ImGui::PushID(2); // When some ImGui items have the same label (for exemple the next two buttons are labeled "Yo") ImGui needs you to specify an ID so that it can distinguish them. It can be an int, a pointer, a string, etc.
            //  You will definitely run into this when you create a button for each of your chess pieces, so remember to give them an ID!
            // ImGui::Button("", ImVec2{50.f, 50.f});

            // ImGui::PopID(); // Then pop the id you pushed after you created the widget
            int compteur{0};
            for (int y{0}; y < 8; y++)     // ligne
                for (int x{0}; x < 8; x++) // colonne
                {
                    // int const y = i / 8;
                    // int const x = i % 8;
                    if (y % 2 == 0)
                    {
                        if (x % 2 == 0)
                        {
                            ImGui::PopStyleColor();
                            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.f, 1.f, 1.f, 1.f});
                        }
                    }
                    else if (x % 2 != 0)
                    {
                        ImGui::PopStyleColor();
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.f, 1.f, 1.f, 1.f});
                    }

                    ImGui::PushID(compteur);

                    std::string label = (tab_piece[y][x] ? tab_piece[y][x]->m_letter : ""); // si la case est nullptr on retourne un bouton vide, sinon on récupère m_lettre

                    if (ImGui::Button(label.c_str(), ImVec2{50.f, 50.f}))
                    {
                        std::cout << "Clicked button " << y << "," << x << std::endl;
                        // Si je click sur une pièce => is_selected = true;
                        // Si is_selected = true, ET que je click sur une une case "nullptr" ET que le mouvement est "légal" => déplacement
                        // si je sélectionne une pièce
                        if (!is_selected)
                        {
                            if (tab_piece[y][x] != nullptr)
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
                            }
                        }
                    }

                    ImGui::PopID();
                    if ((compteur + 1) % 8 != 0) /// ou if (x != 7)
                    {
                        ImGui::SameLine();
                    }
                    ImGui::PopStyleColor();
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 1.f});
                    compteur++;
                }

            /* ImGui::SameLine();
            ImGui::PushID(3);
            if (ImGui::Button("Yo", ImVec2{50.f, 50.f}))
                std::cout << "Clicked button 3\n";
            ImGui::PopID(); */
            ImGui::PopStyleVar();

            ImGui::PopStyleColor();

            // std::cout << "44";
            bool white_time_to_play{true};
            enable_white_or_black(white_time_to_play);

            if (!white_time_to_play) // black_time_to_play=true};
            {
                enable_white_or_black(white_time_to_play);
            }
            // std::cout << "55";

            // On voit quel est le clic
            // On vérifie que c'est son tour de jouer
            // On appelle moves_possible de la pièce
            // On voit si le joueur clic sur un move_possible
            // On change la position de la pièce
            // On change la valeur bool white

            // bool white_time_to_play{true};
            // enable_white_or_black(white_time_to_play);
            // if (!white_time_to_play) // black_time_to_play=true};
            // {
            //     enable_white_or_black(white_time_to_play);
            // }

            // ImGui::SliderFloat("My Value", &value, 0.f, 3.f);

            //// A FAIRE MARCHER POUR RECUPERER LA LETTRE DE LA CASE POUR POUVOIR LA METTRE AUTRE PART
            // if (ImGui::Button("", ImVec2{50.f, 50.f}))
            //     std::cout << "Clicked button 1\n";
            // std::cout << "position button 1\n"
            //           << position_pawn;
            // std::cout << "lettre button 1\n"
            //           << letter_pawn;
            ImGui::SameLine();

            ImGui::End();
        }
    );
}
