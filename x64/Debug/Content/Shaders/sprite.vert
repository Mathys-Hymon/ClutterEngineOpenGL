#version 460 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 coords;

out vec2 TexCoords;

uniform mat4 model; // Matrice modèle
uniform mat4 view;  // Matrice de vue (optionnelle)
uniform mat4 projection; // Matrice de projection (optionnelle)

void main()
{
    TexCoords = coords;
    gl_Position = projection * view * model * vec4(position, 0.0f, 1.0f);
}