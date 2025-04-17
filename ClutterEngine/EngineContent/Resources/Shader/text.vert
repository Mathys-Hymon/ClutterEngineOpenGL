#version 450 core

layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

out vec2 TexCoords;
void main()
{
   gl_Position = vec4(vertex.xy, 0.0, 1.0) * uWorldTransform * uViewProj;
   TexCoords = vertex.zw;
}
