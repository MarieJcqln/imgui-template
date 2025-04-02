#include <GLFW/glfw3.h> // Fenêtre
#include <glad/glad.h>  // OpenGL
#include <imgui.h>
#include <algorithm>
#include <array>
#include <glm/glm.hpp>
#include <iostream>
#include <list>
#include "Camera.hpp"
#include "Model3D.hpp"
#include "Shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
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
    glClearColor(0.847f, 0.82f, 0.929f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Nettoyage écran
    glEnable(GL_DEPTH_TEST);
    // Dessiner un simple triangle (remplace ça par ton échiquier)
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

int main()
{
    // CHARGER LES MODEL 3D
    int           window_width  = 1280;
    int           window_height = 720;
    glmax::Shader shader;
    glmax::Camera camera{true};

    Model3D model;
    ////
    Echequier echequier;

    quick_imgui::loop(
        "Chess 3D",
        {
            .init = [&]() {
                std::cout << "Init OpenGL et Échiquier\n";
                // initOpenGL();                 // appel fonction initOpenGL()
                echequier.initialize_array(); // initialisation échiquier
                //////// CHARGER LES MODEL 3D//////:
                shader.load_shader("model.vs.glsl", "model.fs.glsl");
                // model.load_mesh("creeper/creeper.obj", "creeper");
                model.load_mesh("pawn/pawn.obj", "pawn");
                model.setup_buffers();
                ///////////////
            },
            .loop = [&]() {
                drawOpenGL(); // affiche rendu OpenGL
                ///////3D models////////////////:
                glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);

                shader.use();
                
                //MVP
                shader.set_uniform_matrix_4fv("model", glm::mat4(1.0f));
                shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
                shader.set_uniform_matrix_4fv("projection", projection);

                //LIGHT SETTINGS
                shader.set_uniform_3fv("lightPos", glm::vec3(5.0f, 5.0f, 5.0f));
                shader.set_uniform_3fv("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
                
                //CAMERA SETTINGS
                shader.set_uniform_3fv("viewPos", camera.get_position());
                
                //MODEL RENDER
                model.render(shader); 
                /////////////////////////////
/////////
                // Dessin de l'échiquier
                echequier.draw();

                // Gestion du tour du joueur
                bool white_time_to_play{true};
                enable_white_or_black(white_time_to_play);
                if (!white_time_to_play)
                {
                    enable_white_or_black(white_time_to_play);
                }

                // Interface ImGui
                ImGui::Begin("Options");
                ImGui::Text("Interface de gestion du jeu");
                ImGui::End(); },

            .key_callback          = [](int key, int scancode, int action, int mods) { std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << " Mods: " << mods << '\n'; },
            .mouse_button_callback = [](int button, int action, int mods) { std::cout << "Button: " << button << " Action: " << action << " Mods: " << mods << '\n'; },
            // .cursor_position_callback = [](double xpos, double ypos) { std::cout << "Position: " << xpos << ' ' << ypos << '\n'; },
            .cursor_position_callback = [&](double xpos, double ypos) { camera.track_ball_move_callback(xpos, ypos); },
            .scroll_callback          = [&](double xoffset, double yoffset) { camera.process_scroll(yoffset); },
            // .scroll_callback          = [](double xoffset, double yoffset) { std::cout << "Scroll: " << xoffset << ' ' << yoffset << '\n'; },
            .window_size_callback = [](int width, int height) { std::cout << "Resized: " << width << ' ' << height << '\n'; },
        }
    );

    return 0;
}
