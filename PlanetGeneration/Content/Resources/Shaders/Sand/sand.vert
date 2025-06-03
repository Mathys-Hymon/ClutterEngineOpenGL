#version 450 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform vec2 uTiling;
uniform float uTime; // Ajout pour l'animation

out VS_OUT {
   vec2 texCoord;
   vec3 worldPos; // On passe la position au monde aux étapes suivantes
} vs_out;

void main()
{
   vec4 worldPos = vec4(pos, 1.0) * uWorldTransform;
   vs_out.texCoord = texCoord * uTiling;
   vs_out.worldPos = worldPos.xyz;
   gl_Position = worldPos * uViewProj;
}