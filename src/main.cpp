#include <imgui.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <list>
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

int main()
{
    float value{0.f};

    Echequier echequier;

    quick_imgui::loop(
        "Chess",
        /* init: */ [&]() {},
        /* loop: */
        [&]() {
            ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!

            ImGui::Begin("Example");
            // std::cout << "33";

            echequier.initialize_array();
            echequier.draw(); // on creer l'echequier avec les bouton et les lettres

            // std::cout << "44";
            bool white_time_to_play{true};
            enable_white_or_black(white_time_to_play);
            if (!white_time_to_play) // black_time_to_play=true};
            {
                enable_white_or_black(white_time_to_play);
            }
            // std::cout << "55";

            // ImGui::SliderFloat("My Value", &value, 0.f, 3.f);

            //// A FAIRE MARCHER POUR RECUPERER LA LETTRE DE LA CASE POUR POUVOIR LA METTRE AUTRE PART
            // if (ImGui::Button("", ImVec2{50.f, 50.f}))
            //     std::cout << "Clicked button 1\n";
            // std::cout << "position button 1\n"
            //           << position_pawn;
            // std::cout << "lettre button 1\n"
            //           << letter_pawn;

            // ImGui::SameLine();

            ImGui::End();
        }
    );
}