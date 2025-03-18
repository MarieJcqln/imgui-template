#include <imgui.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <list>
#include "echequier.hpp"
#include "piece.hpp"
#include "quick_imgui/quick_imgui.hpp"

void recuperer_lettre(int& y, int& x, std::array<std::array<std::string, 8>, 8>& tab)
{
    std::cout << tab[y][x] << std::endl;
}

void supprimer_lettre(int& y, int& x, std::array<std::array<std::string, 8>, 8>& tab)
{
}
void ajouter_lettre(int& y, int& x, std::array<std::array<std::string, 8>, 8>& tab)
{
}

void path_choice() {}

void echequier(std::array<std::array<std::unique_ptr<Piece>, 8>, 8>& tab_piece)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{1.0f, 1.0f});

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 1.f}); // initialisation of the color of all buttons until we call ImGui::PopStyleColor(). There is also ImGuiCol_ButtonActive and ImGuiCol_ButtonHovered

    // // ImGui::PushID(2); // When some ImGui items have the same label (for exemple the next two buttons are labeled "Yo") ImGui needs you to specify an ID so that it can distinguish them. It can be an int, a pointer, a string, etc.
    // //  You will definitely run into this when you create a button for each of your chess pieces, so remember to give them an ID!
    // // ImGui::Button("", ImVec2{50.f, 50.f});

    // ImGui::PopID(); // Then pop the id you pushed after you created the widget
    int compteur{0};
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

    //         ImGui::PushID(compteur);

    //         std::string label = (tab_piece[y][x] ? tab_piece[y][x]->m_letter : ""); // si la case est nullptr on retourne un bouton vide, sinon on récupère m_lettre

            // Verifie qu'une piece est sur cette case et on lui applique une couleur a cette case correpondant a la couleur du pion
            // pour l'instant on ne voit pas cette couleur
            if (tab_piece[y][x] != nullptr)
            {
                // Change color based on piece color
                if (tab_piece[y][x]->m_color == white)
                {
                    // si piece blanche, bouton devient bleu donce
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.3f, 1.f}); // bleu foncé
                }
                else
                {
                    // si pice noire bouton devient bleu clair
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.9f, 1.f}); // bleu clair
                }
            }
            // if (tab_piece[y][x] != nullptr)
            // {
            //     ImVec4 color = (tab_piece[y][x]->m_color == white) ? ImVec4(0.0f, 0.0f, 0.5f, 1.0f)  // Bleu foncé
            //                                                        : ImVec4(0.0f, 0.0f, 0.9f, 1.0f); // Bleu clair
            //     ImGui::PushStyleColor(ImGuiCol_Button, color);
            //     ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.x + 0.1f, color.y + 0.1f, color.z + 0.1f, 1.0f));
            //     ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.x + 0.2f, color.y + 0.2f, color.z + 0.2f, 1.0f));
            // }

            if (ImGui::Button(label.c_str(), ImVec2{50.f, 50.f}))
            {
                std::cout << "Clicked button " << y << "," << x << std::endl;

                if (tab_piece[y][x] != nullptr)
                {
                    std::cout << "Letter: " << tab_piece[y][x]->m_letter << std::endl;
                    std::cout << "Color: " << tab_piece[y][x]->m_color << std::endl;
                    // le bouton cliqué change de couleur (bleu foncé)

                    path_choice(); // on montre les différents chemin possible pour le pion cliqué
                }

                else
                {
                    std::cout << "No pawn at this position" << std::endl;
                }
            }
            // pop la couleur de la case quand la case est pressée
            // on va donc voir la couleur apliqué initlament
            if (tab_piece[y][x] != nullptr)
            {
                ImGui::PopStyleColor();
            }

            ImGui::PopID();

            // Pop the button color style if it was pushed
            if (isWhite)
            {
                ImGui::PopStyleColor();
            }

            if ((compteur + 1) % 8 != 0)
            {
                ImGui::SameLine();
            }
            // ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 1.f});
            compteur++;
        }
    }

    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}

// void enable_white_or_black(bool white)
// {
//     // const bool itemHovered = ImGui::IsItemHoveredRect() && ImGui::IsWindowHovered();
//     if (white == true)
//     {
//         // bool itemHovered = false;
//         // Needs the ImRect (bb) and the ID (id):
//         // ImGui::ButtonBehavior(bb, id, &itemHovered, NULL);
//         // on "desactive" le jeu des noirs
//         // on appelle la class pour pion blanc
//         // enlever le hover des noirs
//     }
//     else
//     {
//         // on "desactive" le jeu des blancs
//         // on appelle la class pour pion noir
//         // enlever le hover des blancs
//     }
// }

int main()
{
    float value{0.f};
    bool  white{true};

    // std::array<std::array<std::unique_ptr<Piece>, 8>, 8> tab_piece{
    //     std::array<std::string, 8>{std::make_unique<Tower>(Color::black), "C", "F", "K", "O", "F", "C", "T"},
    //     std::array<std::string, 8>{"P", "P", "P", "P", "P", "P", "P", "P"},
    //     std::array<std::string, 8>{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    //     std::array<std::string, 8>{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    //     std::array<std::string, 8>{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    //     std::array<std::string, 8>{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    //     std::array<std::string, 8>{"P", "P", "P", "P", "P", "P", "P", "P"},
    //     std::array<std::string, 8>{"T", "C", "F", "K", "O", "F", "C", "T"},
    // };
    // std::cout << "11";
    // std::array<std::array<std::unique_ptr<Piece>, 8>, 8> tab_piece{};
    // tab_piece[0][0] = std::make_unique<Tower>(Color::black);  // T
    // tab_piece[0][1] = std::make_unique<Horse>(Color::black);  // C
    // tab_piece[0][2] = std::make_unique<Bishop>(Color::black); // F
    // tab_piece[0][3] = std::make_unique<King>(Color::black);   // K
    // tab_piece[0][4] = std::make_unique<Queen>(Color::black);  // O
    // tab_piece[0][5] = std::make_unique<Bishop>(Color::black); // F
    // tab_piece[0][6] = std::make_unique<Horse>(Color::black);  // C
    // tab_piece[0][7] = std::make_unique<Tower>(Color::black);  // T
    // for (int i{0}; i < 8; i++)                                // Px8
    // {
    //     tab_piece[1][i] = std::make_unique<Pawn>(Color::black);
    // }
    // for (int i{0}; i < 8; i++)
    // {
    //     for (int y{2}; y < 6; y++) // Px8
    //     {
    //         tab_piece[y][i] = nullptr;
    //     }
    // }
    // for (int i{0}; i < 8; i++) // Px8
    // {
    //     tab_piece[6][i] = std::make_unique<Pawn>(Color::white);
    // }
    // tab_piece[7][0] = std::make_unique<Tower>(Color::white);  // T
    // tab_piece[7][1] = std::make_unique<Horse>(Color::white);  // C
    // tab_piece[7][2] = std::make_unique<Bishop>(Color::white); // F
    // tab_piece[7][3] = std::make_unique<King>(Color::white);   // K
    // tab_piece[7][4] = std::make_unique<Queen>(Color::white);  // O
    // tab_piece[7][5] = std::make_unique<Bishop>(Color::white); // F
    // tab_piece[7][6] = std::make_unique<Horse>(Color::white);  // C
    // tab_piece[7][7] = std::make_unique<Tower>(Color::white);  // T
    // // std::cout << "22";
    // quick_imgui::loop(
    //     "Chess",
    //     /* init: */ [&]() {},
    //     /* loop: */
    //     [&]() {
    //         ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!

            ImGui::Begin("Example");
            // std::cout << "33";
            echequier(tab_piece); // on creer l'echequier avec les bouton et les lettres
            // drawChessboard(tab_piece);
            // std::cout << "44";
            bool white_time_to_play{true};
            enable_white_or_black(white_time_to_play);
            if (!white_time_to_play) // black_time_to_play=true};
            {
                enable_white_or_black(white_time_to_play);
            }
            // std::cout << "55";

    //         // On voit quel est le clic
    //         // On vérifie que c'est son tour de jouer
    //         // On appelle moves_possible de la pièce
    //         // On voit si le joueur clic sur un move_possible
    //         // On change la position de la pièce
    //         // On change la valeur bool white

    //         // bool white_time_to_play{true};
    //         // enable_white_or_black(white_time_to_play);
    //         // if (!white_time_to_play) // black_time_to_play=true};
    //         // {
    //         //     enable_white_or_black(white_time_to_play);
    //         // }

    //         // ImGui::SliderFloat("My Value", &value, 0.f, 3.f);

    //         //// A FAIRE MARCHER POUR RECUPERER LA LETTRE DE LA CASE POUR POUVOIR LA METTRE AUTRE PART
    //         // if (ImGui::Button("", ImVec2{50.f, 50.f}))
    //         //     std::cout << "Clicked button 1\n";
    //         // std::cout << "position button 1\n"
    //         //           << position_pawn;
    //         // std::cout << "lettre button 1\n"
    //         //           << letter_pawn;
    //         ImGui::SameLine();

    //         ImGui::End();
    //     }
    // );
}