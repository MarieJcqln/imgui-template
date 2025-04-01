// #include <imgui.h>
// #include <algorithm>
// #include <array>
// #include <iostream>
// #include <list>
// #include "piece.hpp"
// #include "quick_imgui/quick_imgui.hpp"

// void recuperer_lettre(int& y, int& x, std::array<std::array<std::string, 8>, 8>& tab)
// {
//     std::cout << tab[y][x] << std::endl;
// }

// void supprimer_lettre(int& y, int& x, std::array<std::array<std::string, 8>, 8>& tab)
// {
// }
// void ajouter_lettre(int& y, int& x, std::array<std::array<std::string, 8>, 8>& tab)
// {
// }

// int main()
// {
//     float value{0.f};

//     Echequier echequier;

//     quick_imgui::loop(
//         "Chess",
//         /* init: */ [&]() {},
//         /* loop: */
//         [&]() {
//             ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!

//             ImGui::Begin("Example");
//             // std::cout << "33";

//             echequier.initialize_array();
//             echequier.draw(); // on creer l'echequier avec les bouton et les lettres

//             // std::cout << "44";
//             bool white_time_to_play{true};
//             enable_white_or_black(white_time_to_play);
//             if (!white_time_to_play) // black_time_to_play=true};
//             {
//                 enable_white_or_black(white_time_to_play);
//             }
//             // std::cout << "55";

//             // ImGui::SliderFloat("My Value", &value, 0.f, 3.f);

//             ImGui::End();
//         }
//     );
// }

#include <GLFW/glfw3.h> // Fenêtre
#include <glad/glad.h>  // OpenGL
#include <imgui.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <list>
#include "piece.hpp"
#include "quick_imgui/quick_imgui.hpp"

// Variables OpenGL
GLuint vao, vbo; // Pour stocker les objets OpenGL

// Fonction d'initialisation OpenGL
void initOpenGL()
{
    std::cout << "Initialisation OpenGL..." << std::endl;

    // Activer le test de profondeur
    glEnable(GL_DEPTH_TEST);

    // Création d'un VAO (Vertex Array Object)
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Création d'un VBO (Vertex Buffer Object)
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Exemple de données pour un simple triangle (à remplacer par ton échiquier 3D)
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // Bas gauche
        0.5f, -0.5f, 0.0f,  // Bas droit
        0.0f, 0.5f, 0.0f    // Haut
    };

    // Charger les données dans le VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Activer et spécifier l'attribut de position (index 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0); // Débind
}

// Fonction de rendu OpenGL
void drawOpenGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Nettoyage écran

    // Dessiner un simple triangle (remplace ça par ton échiquier)
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

int main()
{
    Echequier echequier;

    quick_imgui::loop(
        "Chess 3D",
        {
            .init = [&]() {
                std::cout << "Init OpenGL et Échiquier\n";
                initOpenGL();                 // appel fonction initOpenGL()
                echequier.initialize_array(); // initialisation échiquier
            },
            .loop = [&]() {
                drawOpenGL(); // affiche rendu OpenGL

                // Dessin de l'échiquier
                echequier.draw();

                // Gestion du tour du joueur
                bool white_time_to_play{true};
                enable_white_or_black(white_time_to_play);
                if (!white_time_to_play) {
                    enable_white_or_black(white_time_to_play);
                }

                // Interface ImGui
                ImGui::Begin("Options");
                ImGui::Text("Interface de gestion du jeu");
                ImGui::End(); },

            .key_callback             = [](int key, int scancode, int action, int mods) { std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << " Mods: " << mods << '\n'; },
            .mouse_button_callback    = [](int button, int action, int mods) { std::cout << "Button: " << button << " Action: " << action << " Mods: " << mods << '\n'; },
            .cursor_position_callback = [](double xpos, double ypos) { std::cout << "Position: " << xpos << ' ' << ypos << '\n'; },
            .scroll_callback          = [](double xoffset, double yoffset) { std::cout << "Scroll: " << xoffset << ' ' << yoffset << '\n'; },
            .window_size_callback     = [](int width, int height) { std::cout << "Resized: " << width << ' ' << height << '\n'; },
        }
    );

    return 0;
}
