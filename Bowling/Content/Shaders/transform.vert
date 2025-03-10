#version 460 core

in vec3 pos;
in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

out vec2 TexCoords;
void main()
{
   gl_Position = vec4(pos, 1.0)* uWorldTransform * uViewProj;
   TexCoords = texCoord;
}
