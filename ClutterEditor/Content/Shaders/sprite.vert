#version 460 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 coords;

out vec2 TexCoords;

uniform mat4 model;     // Position/rotation/scale of sprite
uniform mat4 view;      // CameraLocation
uniform mat4 projection; // Projection

void main()
{
    TexCoords = coords;
    gl_Position = model * vec4(pos.x, pos.y, 0.0f, 1.0f);
}