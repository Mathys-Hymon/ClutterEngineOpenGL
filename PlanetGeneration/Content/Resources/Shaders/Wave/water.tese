#version 450 core

layout(triangles, fractional_even_spacing, cw) in;

in TESC_OUT {
   vec2 texCoord;
   vec3 position;
} tese_in[];

out TESE_OUT {
   vec2 texCoord;
   float height;
} tese_out;

uniform float uTime;
uniform float uWaveStrength;
uniform sampler2D uNoise;

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2) {
   return gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;
}

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2) {
   return gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;
}

void main() {
   vec3 pos = interpolate3D(tese_in[0].position, tese_in[1].position, tese_in[2].position);
   vec2 uv = interpolate2D(tese_in[0].texCoord, tese_in[1].texCoord, tese_in[2].texCoord);

   float noise = texture(uNoise, uv + vec2(uTime * 0.05, uTime * 0.03)).r;
   pos.y += noise * uWaveStrength;

   gl_Position = vec4(pos, 1.0);
   tese_out.texCoord = uv;
   tese_out.height = pos.y;
}