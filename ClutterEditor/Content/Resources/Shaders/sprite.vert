#version 450 core

layout(location = 0) in vec3 pos;
layout(location = 2) in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform bool uFlipX;
uniform bool uFlipY;

out vec2 TexCoords;
void main()
{
   gl_Position = vec4(pos, 1.0) * uWorldTransform * uViewProj;
   TexCoords = vec2(texCoord.x, 1.0 - texCoord.y);

   if (uFlipX)
    TexCoords.x = 1.0 - TexCoords.x;

if (uFlipY)
    TexCoords.y = 1.0 - TexCoords.y;
}
