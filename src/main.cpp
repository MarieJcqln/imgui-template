#include <imgui.h>
#include <iostream>
#include "quick_imgui/quick_imgui.hpp"

class Piece {
    // Position
    float position_x;
    float position_y;

    enum Color { white,
                 black };

    virtual Piece reset();
    virtual Piece moves();
    ~Piece();
};

class Pawn : public Piece {
};

void echequier()
{
    // Draw the next ImGui widget on the same line as the previous one. Otherwise it would be below it

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{1.0f, 1.0f});

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 1.f}); // Changes the color of all buttons until we call ImGui::PopStyleColor(). There is also ImGuiCol_ButtonActive and ImGuiCol_ButtonHovered

    // ImGui::PushID(2); // When some ImGui items have the same label (for exemple the next two buttons are labeled "Yo") ImGui needs you to specify an ID so that it can distinguish them. It can be an int, a pointer, a string, etc.
    //  You will definitely run into this when you create a button for each of your chess pieces, so remember to give them an ID!
    // ImGui::Button("", ImVec2{50.f, 50.f});

    // ImGui::PopID(); // Then pop the id you pushed after you created the widget

    for (int i{0}; i < 64; i++)
    {
        int const y = i / 8;
        int const x = i % 8;
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

        ImGui::PushID(i);
        if (y == 1 || y == 6)
        {
            ImGui::Button("P", ImVec2{50.f, 50.f});
        }
        else if (y == 0 || y == 7)
        {
            if (x == 0 || x == 7)
            {
                ImGui::Button("T", ImVec2{50.f, 50.f});
            }
            if (x == 1 || x == 6)
            {
                ImGui::Button("C", ImVec2{50.f, 50.f});
            }
            if (x == 2 || x == 5)
            {
                ImGui::Button("F", ImVec2{50.f, 50.f});
            }
            if (x == 3)
            {
                ImGui::Button("K", ImVec2{50.f, 50.f});
            }
            if (x == 4)
            {
                ImGui::Button("Q", ImVec2{50.f, 50.f});
            }
        }
        else
        {
            ImGui::Button("", ImVec2{50.f, 50.f});
        }
        ImGui::PopID();
        if ((i + 1) % 8 != 0)
        {
            ImGui::SameLine();
        }
        ImGui::PopStyleColor();
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 1.f});
    }

    /* ImGui::SameLine();
    ImGui::PushID(3);
    if (ImGui::Button("Yo", ImVec2{50.f, 50.f}))
        std::cout << "Clicked button 3\n";
    ImGui::PopID(); */
    ImGui::PopStyleVar();

    ImGui::PopStyleColor();
}

void enable_disable_white(bool couleur)
{
}

int main()
{
    float value{0.f};

    quick_imgui::loop(
        "Chess",
        /* init: */ [&]() {},
        /* loop: */
        [&]() {
            ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!

            ImGui::Begin("Example");

            echequier(); // on creer l'echequier avec les bouton et les lettres
            bool white_time_to_play{true};
            enable_disable_white(white_time_to_play);
            if (!white_time_to_play)
            {
                white_time_to_play = false; // black_time_to_play=true};
                enable_disable_white(white_time_to_play);
            }

            // ImGui::SliderFloat("My Value", &value, 0.f, 3.f);

            /* if (ImGui::Button("", ImVec2{50.f, 50.f}))
                std::cout << "Clicked button 1\n";
            ImGui::SameLine();  */

            ImGui::End();
        }
    );
}