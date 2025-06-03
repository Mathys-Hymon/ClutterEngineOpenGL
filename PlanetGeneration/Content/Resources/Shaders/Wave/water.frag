#version 450 core

in TESE_OUT {
   vec2 texCoord;
   float height;
} frag_in;

out vec4 outColor;

uniform sampler2D uTexture;
uniform vec3 uFoamColor;
uniform float uFoamThreshold;

void main() {
   vec4 baseColor = texture(uTexture, frag_in.texCoord);

   // Ajoute un peu d’écume en haut des vagues
   float foamFactor = smoothstep(uFoamThreshold - 0.1, uFoamThreshold + 0.1, frag_in.height);
   vec3 finalColor = mix(baseColor.rgb, uFoamColor, foamFactor);

   outColor = vec4(finalColor, 1.0);
}
