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

// // Fonction d'initialisation OpenGL
// void initOpenGL()
// {
//     std::cout << "Initialisation OpenGL..." << std::endl;

//     // Activer le test de profondeur
//     glEnable(GL_DEPTH_TEST);

//     // Création d'un VAO (Vertex Array Object)
//     glGenVertexArrays(1, &vao);
//     glBindVertexArray(vao);

//     // Création d'un VBO (Vertex Buffer Object)
//     glGenBuffers(1, &vbo);
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);

//     // Exemple de données pour un simple triangle (à remplacer par ton échiquier 3D)
//     float vertices[] = {
//         -0.5f, -0.5f, 0.0f, // Bas gauche
//         0.5f, -0.5f, 0.0f,  // Bas droit
//         0.0f, 0.5f, 0.0f    // Haut
//     };

//     // Charger les données dans le VBO
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     // Activer et spécifier l'attribut de position (index 0)
//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

//     glBindVertexArray(0); // Débind
// }

// Fonction de rendu OpenGL
void drawOpenGL()
{
    glClearColor(0.847f, 0.82f, 0.929f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Nettoyage écran
    glEnable(GL_DEPTH_TEST);
}

void place_piece(Model3D& model, int x, int z, float spacing = 1.0f)
{
    glm::vec3 position  = glm::vec3(x * spacing, 0.0f, z * spacing);
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
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

                // model1.load_mesh("grammy_award_6/grammy_award_6.obj", "grammy_award_6"); // ne le faire qu'une fois pour chaque type de pièce
                // model2.load_mesh("golden_ball/golden_ball.obj", "golden_ball");
                model1.load_mesh("oscar_award/oscar_award.obj", "oscar_award");
                model2.load_mesh("grammy_award/grammy_award.obj", "grammy_award");
                model3.load_mesh("mtv_award/mtv.obj", "mtv_award");
                // model4.load_mesh("golden_raspberry/golden_raspberry.obj", "golden_raspberry");
                model4.load_mesh("golden_disk/golden_disk.obj", "golden_disk");
                model5.load_mesh("golden_palm/golden_palm.obj", "golden_palm");
                model6.load_mesh("golden_globe/golden_globe.obj", "golden_globe");

                model1.setup_buffers();
                model2.setup_buffers();
                model3.setup_buffers();
                model4.setup_buffers();
                model5.setup_buffers();
                model6.setup_buffers();
                ///////////////

                float spacing = 1.0f; /// distance entre les cases

                // placmeent des pions (ligne 1 pour les noirs, ligne 6 pour lesblancs)
                for (int i = 0; i < 8; ++i)
                {
                    place_piece(model5, i, 1); // noir
                    place_piece(model5, i, 6); // blanc
                }

                // TOURS (model6)
                place_piece(model6, 0, 0); // noir
                place_piece(model6, 7, 0); // noir
                place_piece(model6, 0, 7);
                place_piece(model6, 7, 7);

                // CAVALIERS (model3)
                place_piece(model3, 1, 0); // noir
                place_piece(model3, 6, 0); // noir
                place_piece(model3, 1, 7);
                place_piece(model3, 6, 7);

                // FOUS (model2)
                place_piece(model2, 2, 0); // noir
                place_piece(model2, 5, 0); // noir
                place_piece(model2, 2, 7);
                place_piece(model2, 5, 7);

                // REINES (model4)
                place_piece(model4, 3, 0); // noirs
                place_piece(model4, 3, 7); // blanc

                // ROIS (model1)
                place_piece(model1, 4, 0); // noir
                place_piece(model1, 4, 7); // blanc
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
                /////////////////////////////
/////////
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
