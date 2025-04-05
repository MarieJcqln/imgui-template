#include <GLFW/glfw3.h> // Fenêtre
#include <glad/glad.h>  // OpenGL
#include <imgui.h>
#include <algorithm>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //pour glm::translate, rotate, scale
#include <glm/gtc/type_ptr.hpp>         //pour passage de smatrice au shader
#include <iostream>
#include <list>
#include "Camera.hpp"
#include "Model3D.hpp"
#include "Shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "math.hpp"
#include "piece.hpp"
#include "quick_imgui/quick_imgui.hpp"

// Variables OpenGL
GLuint vao, vbo; // Pour stocker les objets OpenGL

void drawOpenGL()
{
    glClearColor(0.847f, 0.82f, 0.929f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Nettoyage écran
    glEnable(GL_DEPTH_TEST);
}

void place_piece(Model3D& model, int x, int z, bool is_white = false, float spacing = 1.0f)
{
    // symétrie sur l'axe Z pour les blancs
    if (is_white)
    {
        z = 7 - z;
    }

    glm::vec3 position  = glm::vec3(x * spacing, 0.0f, z * spacing);
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);

    // rotation des blancs pour qu’ils soient face aux noirs
    if (is_white)
    {
        transform = glm::rotate(transform, glm::radians(180.0f), glm::vec3(0, 1, 0));
    }

    model.add_instance(transform);
}

int main()
{
    // CHARGER LES MODEL 3D
    int           window_width  = 1280;
    int           window_height = 720;
    glmax::Shader shader;
    glmax::Camera camera{true};

    Model3D model1;
    Model3D model2;
    Model3D model3;
    Model3D model4;
    Model3D model5;
    Model3D model6;
    Model3D model7;
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

                model1.load_mesh("oscar_award/oscar_award.obj", "oscar_award");
                model2.load_mesh("grammy_award/grammy_award.obj", "grammy_award"); // FOUS
                model3.load_mesh("mtv_award/mtv.obj", "mtv_award");                // CAVALIERS
                // model4.load_mesh("golden_raspberry/golden_raspberry.obj", "golden_raspberry");
                model4.load_mesh("golden_disk/golden_disk.obj", "golden_disk");
                model5.load_mesh("golden_palm/golden_palm.obj", "golden_palm");
                model6.load_mesh("golden_globe/golden_globe.obj", "golden_globe"); // TOURS
                model7.load_mesh("chessboard/chessboard.obj", "chessboard");

                model1.setup_buffers();
                model2.setup_buffers();
                model3.setup_buffers();
                model4.setup_buffers();
                model5.setup_buffers();
                model6.setup_buffers();
                model7.setup_buffers();
                ///////////////
                model7.add_instance(glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, -0.0, 3.5f))); // si on le met pas ca n'affiche pas le plateau // le 0 sert pour descendre ou monter le plateau dans l'axe des z //3.5 pour centrer le plateau 7/2 = 3.5

                float spacing = 1.0f; /// distance entre les cases

                // placmeent des pions (ligne 1 pour les noirs, ligne 6 pour lesblancs)
                for (int i = 0; i < 8; ++i)
                {
                    place_piece(model5, i, 1);       // noir
                    place_piece(model5, i, 1, true); // blanc (symetrie de ligne 1 = ligne 6)
                }
                // charge un seul modele par type de pièce, puis on instanci plusieurs fois à différentes
                // psoition sur l’echequier en utilisant  matrice de transforamtion

                // TOURS (model6)
                place_piece(model6, 0, 0); // noir
                place_piece(model6, 7, 0); // noir
                place_piece(model6, 0, 0, true);
                place_piece(model6, 7, 0, true);

                // CAVALIERS (model3)
                place_piece(model3, 1, 0); // noir
                place_piece(model3, 6, 0); // noir
                place_piece(model3, 1, 0, true);
                place_piece(model3, 6, 0, true);

                // FOUS (model2)
                place_piece(model2, 2, 0); // noir
                place_piece(model2, 5, 0); // noir
                place_piece(model2, 2, 0, true);
                place_piece(model2, 5, 0, true);

                // REINES (model4)
                place_piece(model4, 3, 0); // noir
                place_piece(model4, 3, 0, true);

                // ROIS (model1)
                place_piece(model1, 4, 0);       // noir
                place_piece(model1, 4, 0, true); //
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
                model1.render(shader); 
                model2.render(shader); 
                model3.render(shader); 
                model4.render(shader); 
                model5.render(shader); 
                model6.render(shader); 
                model7.render(shader); 
                /////////////////////////////

                // Dessin de l'échiquier
                echequier.draw();


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

    // Test des fonctions
    std::cout << "Loi uniforme (0, 1) : " << random_uniform(0.0, 1.0) << std::endl;
    std::cout << "Loi normale (moyenne = 0, écart-type = 1) : " << random_normal(0.0, 1.0) << std::endl;
    std::cout << "Loi exponentielle (lambda = 1.0) : " << random_exponential(1.0) << std::endl;

    return 0;
}
