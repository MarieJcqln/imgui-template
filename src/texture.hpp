// #pragma once

// #include <GLFW/glfw3.h>
// #include <glad/glad.h>
// #include <map> //pour std::map pour texture
// #include <memory>
// #include <string>
// #include "Model3d.hpp"
// #include "helper.hpp"
// #include "piece.hpp"

// class Piece; // pour tuiliser getPieceTexture
// // class Echequier;

// class Texture {
// private:
//     std::map<std::string, GLuint> textures;

// public:
//     Texture() = default;
//     ~Texture();

//     // load la texture puis assocue a key
//     bool loadTexture(const std::string& key, const std::string& filepath);

//
//     GLuint getTexture(const std::string& key) const;

//
//     GLuint getPieceTexture(const Piece* piece) const;
// };