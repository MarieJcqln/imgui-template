#pragma once
#include <string>
#include "Mesh.hpp"
#include "Shader.hpp"
#include "buffers/EBO.hpp"
#include "buffers/VAO.hpp"
#include "buffers/VBO.hpp"

class Model3D {
public:
    void load_mesh(const std::string& path, const std::string& name); // 1 ///une mesh par style de piece different donc 7
    void setup_buffers();                                             // 2
    void render(glmax::Shader& shader) const;                         // 3
    /// FAIRE MODEL MATRICE (pour les trandformation) ///une matirce par pièce ! donc 12 pour les pions

private:
    // single mesh
    glmax::Mesh m_mesh;
    //
    // Buffers
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
};