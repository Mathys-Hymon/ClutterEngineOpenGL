#version 400

layout(vertices = 1) out;

uniform float tessLevelInner = 5;
uniform float tessLevelOuter = 5;

void main()
{
    gl_TessLevelInner[0] = tessLevelInner;
    gl_TessLevelOuter[0] = tessLevelOuter;
    gl_TessLevelOuter[1] = tessLevelOuter;
    gl_TessLevelOuter[2] = tessLevelOuter;
    gl_TessLevelOuter[3] = tessLevelOuter;
}
