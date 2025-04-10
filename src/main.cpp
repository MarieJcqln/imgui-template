#include <GLFW/glfw3.h> // Fenêtre
#include <glad/glad.h>  // OpenGL
#include <imgui.h>
#include <algorithm>
#include <array>
#include <chrono> // Pour le chrono
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //pour glm::translate, rotate, scale
#include <glm/gtc/type_ptr.hpp>         //pour passage de smatrice au shader
#include <iostream>
#include <list>
#include <string>
#include "Camera.hpp"
#include "Model3D.hpp"
#include "Shader.hpp"
#include "echequier.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "math.hpp"
#include "piece.hpp"
#include "quick_imgui/quick_imgui.hpp"

// Variables OpenGL
GLuint vao, vbo; // Pour stocker les objets opengl

// pour le chrono
float                                              timer_by_person = 30.0f; // 30 sec par tour
float                                              current_time    = 30.0f; // Temps restant
std::chrono::time_point<std::chrono::steady_clock> last_frame_time;
bool                                               timer_initialized = false;

void drawOpenGL()
{
    glClearColor(0.847f, 0.82f, 0.929f, 1.f); // fond blanc cassé
    // glClearColor(0.1f, 0.1f, 0.1f, 1.0f);//fond noir
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

void update_timer(bool& last_turn_state, bool current_turn_state)
{
    // on verifie que le tour a changé
    if (last_turn_state != current_turn_state)
    {
        // on remet chrono à 30 sec
        current_time    = timer_by_person;
        last_turn_state = current_turn_state;
    }

    // update valeur du temps actuel (decrescendo)
    auto current_frame_time = std::chrono::steady_clock::now();
    if (timer_initialized)
    {
        float delta_time = std::chrono::duration<float>(current_frame_time - last_frame_time).count();
        current_time -= delta_time;

        // empecher timer d aller under zero
        if (current_time < 0.0f)
        {
            current_time = 0.0f;
        }
    }
    else
    {
        timer_initialized = true;
    }
    last_frame_time = current_frame_time;
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

    init_random();
    std::vector<std::vector<int>> couleurs{tirage_couleur()};

    // variable pour detecter changement de tour plus tard
    bool last_turn_state = echequier.white_turn;

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

                // mettre a jour le chrono
                update_timer(last_turn_state, echequier.white_turn);

                ///////3D models////////////////:
                glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);

                shader.use();

                // MVP camera
                shader.set_uniform_matrix_4fv("model", glm::mat4(1.0f));
                shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
                shader.set_uniform_matrix_4fv("projection", projection);

                // LIGHT SETTINGS
                // light blanche au milieu
                shader.set_uniform_3fv("lightPos", glm::vec3(5.0f, 5.0f, 5.0f));
                shader.set_uniform_3fv("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

                // Postions des deux lumières de chaque côté de l’échequier
                // light à gauche (joeur noir)
                glm::vec3 lightPos1 = glm::vec3(-8.0f, 10.0f, 15.0f); //-5;5;0
                // light a drote (joeur blanc)
                glm::vec3 lightPos2 = glm::vec3(8.0f, 10.0f, -15.0f); // 13;5;0 //+chiffre du milieu grand + ca eclair

                shader.use();
                shader.set_uniform_3fv("lightPos1", lightPos1);
                shader.set_uniform_3fv("lightColor1", glm::vec3(1.0f, 0.8f, 0.9f)); // lumiere roug caire
                // shader.set_uniform_1i("lightActive1", !is_white_turn); // lumiere rouge si c'est au noir ed jouer
                shader.set_uniform_1i("lightActive1", !echequier.white_turn); // acces aattribut white_turn su objet echequier

                shader.set_uniform_3fv("lightPos2", lightPos2);
                shader.set_uniform_3fv("lightColor2", glm::vec3(0.8f, 0.9f, 1.0f)); // lumiere bleu clair
                // shader.set_uniform_1i("lightActive2", is_white_turn); // lumiere bleu si c'est au blanc de jouer
                shader.set_uniform_1i("lightActive2", echequier.white_turn);

                // CAMERA SETTINGS
                shader.set_uniform_3fv("viewPos", camera.get_position());

                // MODEL RENDER
                model1.render(shader);
                model2.render(shader);
                model3.render(shader);
                model4.render(shader);
                model5.render(shader);
                model6.render(shader);
                model7.render(shader);
                /////////////////////////////

                // Dessin de l'échiquier
                echequier.draw(couleurs);

                // Interface ImGui
                // ImGui::Begin("Options");
                // ImGui::Text("Interface de gestion du jeu");
                // ImGui::End();
               

                ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground;

                // Position fenêtre
                // ImGui::SetNextWindowPos(ImVec2(200, 100)); //creer pb qaund on reduit la taille de la fenetre
                // ImGui::SetNextWindowSize(ImVec2(window_width, 100)); //creer pb qaund on reduit la taille de la fenetre
                ImGui::Begin("TILE", nullptr, window_flags);
              
                //// TITRE
                ImGui::SetCursorPosY(10); // Position Y du titre
                ImVec4 title_color { ImVec4(0.6f, 0.5f, 0.0f, 1.0f) }; //doré  : 255, 215, 0

                const char* title{"CHESS AWARD"};
                float title_width { ImGui::CalcTextSize(title).x};
                ImGui::SetCursorPosX((window_width - title_width) * 0.5f);
                ImGui::PushStyleColor(ImGuiCol_Text, title_color);
                ImGui::Text("%s", title);  //%s pour lire une chaine de caractrer
                ImGui::PopStyleColor();

                /////chronomètre///
                ImGui::SetCursorPosY(40); // Position Y du chronomètre

                // formater le tps au format MM:SS
                int minutes {static_cast<int>(current_time) / 60};
                int seconds  {static_cast<int>(current_time) % 60};
                std::string time_str {std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds)};

                // couluer texte change si reste 10 sec pour jouer
                ImVec4 timer_color { (current_time <= 10.0f) ? ImVec4(1.0f, 0.0f, 0.0f, 1.0f) : // Rouge si moins de 10 secondes
                                            ImVec4(0.0f, 0.0f, 0.0f, 1.0f)};                        // Noir sinon

                // affiche a qui est le tour et le chrono
                std::string turn_text  {echequier.white_turn ? "Tour des Blancs: " : "Tour des Noirs: "};
                float timer_width {ImGui::CalcTextSize((turn_text + time_str).c_str()).x};

                ImGui::PushStyleColor(ImGuiCol_Text, timer_color);
                ImGui::SetCursorPosX((window_width - timer_width) * 0.5f);
                ImGui::Text("%s%s", turn_text.c_str(), time_str.c_str());
                ///////
                ImGui::PopStyleColor();

                // // Barre de progression pour le temps
                // ImGui::SetCursorPosY(65);
                // float progress_width = 200.0f; // Largeur de la barre de progression
                // ImGui::SetCursorPosX((window_width - progress_width) * 0.5f);
                // ImGui::PushStyleColor(ImGuiCol_PlotHistogram, timer_color);
                // ImGui::ProgressBar(current_time / timer_by_person, ImVec2(progress_width, 10.0f));
                // ImGui::PopStyleColor();
               
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
