#version 400

layout(quads, equal_spacing, cw) in;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // Tessellation coordinates
    vec4 p0 = gl_TessCoord.x * gl_in[0].gl_Position;
    vec4 p1 = gl_TessCoord.y * gl_in[1].gl_Position;
    vec4 p2 = gl_TessCoord.z * gl_in[2].gl_Position;

    // Pour les quads, gl_TessCoord.z est utilisé pour le troisième sommet
    vec4 p3 = (1.0 - gl_TessCoord.x - gl_TessCoord.y - gl_TessCoord.z) * gl_in[3].gl_Position;

    vec4 position = p0 + p1 + p2 + p3;

    // Normalize to create a sphere
    position.xyz = normalize(position.xyz);

    gl_Position = projection * view * model * position;
}
