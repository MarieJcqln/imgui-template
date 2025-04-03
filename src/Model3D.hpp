#pragma once
#include <string>
#include "Mesh.hpp"
#include "Shader.hpp"
#include "buffers/EBO.hpp"
#include "buffers/VAO.hpp"
#include "buffers/VBO.hpp"

/// UTiliser GLM pour ne pas avoir a trouver les matrice de rotation pour la cam vers un certain objet (on aura suelement a renseigné la cam et l'objet a regarder)

class Model3D {
public:
    void load_mesh(const std::string& path, const std::string& name); // 1 ///une mesh par style de piece different donc 7
    void setup_buffers();                                             // 2
    void render(glmax::Shader& shader) const;                         // 3
    // void model_matice();

private:
    // single mesh
    glmax::Mesh m_mesh;
    // glmax::Mesh model_matrice_pawn{glm::mat4(1.0f)}; /// FAIRE MODEL MATRICE (pour les trandformation) ///une matirce par pièce ! donc 12 pour les pions
    // glmax::Mesh model_matrice_tower;
    // glmax::Mesh model_matrice_bishop;
    // glmax::Mesh model_matrice_horse;
    // glmax::Mesh model_matrice_queen;
    // glmax::Mesh model_matrice_king;
    //
    // Buffers
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
};