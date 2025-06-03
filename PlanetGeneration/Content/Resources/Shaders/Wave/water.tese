#version 450 core

layout(triangles, fractional_even_spacing, cw) in;

uniform sampler2D uNoiseTexture; // Texture de bruit pour les vagues
uniform float uTime; // Temps pour l'animation
uniform float uWaveStrength; // Force des vagues
uniform float uWaveScale; // Échelle des vagues

in TESC_OUT {
   vec2 texCoord;
   vec3 worldPos;
} tese_in[];

out TESE_OUT {
   vec2 texCoord;
   vec3 worldPos;
   vec3 normal;
} tese_out;

vec3 calculateNormal(vec3 pos) {
   // Échantillonnage du bruit pour calculer les normales
   float offset = 0.01;
   float h = texture(uNoiseTexture, pos.xz * 0.1 + vec2(uTime * 0.05)).r;
   float hx = texture(uNoiseTexture, (pos.xz + vec2(offset, 0.0)) * 0.1 + vec2(uTime * 0.05)).r;
   float hz = texture(uNoiseTexture, (pos.xz + vec2(0.0, offset)) * 0.1 + vec2(uTime * 0.05)).r;
   
   vec3 normal = normalize(vec3(h - hx, offset, h - hz));
   return normal;
}

void main(void)
{
   // Interpolation normale
   vec3 worldPos = (gl_TessCoord.x * tese_in[0].worldPos +
                   gl_TessCoord.y * tese_in[1].worldPos +
                   gl_TessCoord.z * tese_in[2].worldPos);
   
   // Application du bruit pour les vagues
   vec2 noiseCoord = worldPos.xz * uWaveScale + vec2(uTime * 0.1);
   float noise = texture(uNoiseTexture, noiseCoord).r;
   worldPos.y += noise * uWaveStrength;
   
   // Calcul de la normale
   tese_out.normal = calculateNormal(worldPos);
   
   // Position finale
   tese_out.worldPos = worldPos;
   tese_out.texCoord = interpolate2D(tese_in[0].texCoord, tese_in[1].texCoord, tese_in[2].texCoord);
   gl_Position = vec4(worldPos, 1.0) * uViewProj;
}