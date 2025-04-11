#version 330 core

//vertex shader lie données du sommet contenu dans le VBO via in vec3 pos etc.
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

//vextex shader passe les infos au fragment shader (qui va les tuiliser pour colorier chaque pixel)
out vec3 FragPos; //on lui passe la position
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0)); // Coordonnée du fragment dans l'espace monde
    Normal = mat3(transpose(inverse(model))) * aNormal; // Transformation correcte des normales
    TexCoords = aTexCoords;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}
