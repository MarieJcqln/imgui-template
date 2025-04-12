// #include "texture.hpp"
// #include <iostream>
// #include "piece.hpp" // pour utilisation de Piece

// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

// Texture::~Texture()
// {
//     for (auto& pair : textures)
//     {
//         glDeleteTextures(1, &pair.second);
//     }
// }

// bool Texture::loadTexture(const std::string& key, const std::string& filepath)
// {
//     GLuint textureID;
//     glGenTextures(1, &textureID);

//     int            width, height, channels;
//     unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

//     if (!data)
//     {
//         std::cerr << "Failed to load texture: " << filepath << std::endl;
//         std::cerr << "STB Error: " << stbi_failure_reason() << std::endl;
//         return false;
//     }

//     GLenum format;
//     if (channels == 1)
//         format = GL_RED;
//     else if (channels == 3)
//         format = GL_RGB;
//     else if (channels == 4)
//         format = GL_RGBA;
//     else
//     {
//         std::cerr << "Unsupported number of channels: " << channels << std::endl;
//         stbi_image_free(data);
//         return false;
//     }

//     glBindTexture(GL_TEXTURE_2D, textureID);
//     glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

//     // Set texture parameters
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//     stbi_image_free(data);

//     textures[key] = textureID;
//     return true;
// }

// GLuint Texture::getTexture(const std::string& key) const
// {
//     auto it = textures.find(key);
//     if (it != textures.end())
//     {
//         return it->second;
//     }
//     return 0; // si texture invalide
// }

// GLuint Texture::getPieceTexture(const Piece* piece) const
// {
//     if (!piece)
//         return 0;

//     std::string color = (piece->m_color == Color::white) ? "white_" : "black_";
//     std::string type;

//     if (dynamic_cast<const King*>(piece))
//     {
//         type = "king";
//     }
//     else if (dynamic_cast<const Queen*>(piece))
//     {
//         type = "queen";
//     }
//     else if (dynamic_cast<const Bishop*>(piece))
//     {
//         type = "bishop";
//     }
//     else if (dynamic_cast<const Horse*>(piece))
//     {
//         type = "knight";
//     }
//     else if (dynamic_cast<const Tower*>(piece))
//     {
//         type = "rook";
//     }
//     else if (dynamic_cast<const Pawn*>(piece))
//     {
//         type = "pawn";
//     }
//     else
//     {
//         return 0;
//     }

//     return getTexture(color + type);
// }