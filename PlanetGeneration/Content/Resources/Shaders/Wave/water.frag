#version 450 core

in TESE_OUT {
   vec2 texCoord;
   vec3 worldPos;
   vec3 normal;
} frag_in;

out vec4 outColor;

uniform sampler2D uTexture; // Texture diffuse
uniform sampler2D uNormalMap; // Normal map
uniform vec3 uLightDir; // Direction de la lumière
uniform vec3 uCameraPos; // Position de la caméra

void main()
{
   // Échantillonnage des textures
   vec4 diffuse = texture(uTexture, frag_in.texCoord);
   vec3 normalMap = texture(uNormalMap, frag_in.texCoord).rgb;
   
   // Conversion de la normal map [0,1] vers [-1,1]
   vec3 normal = normalize(normalMap * 2.0 - 1.0);
   
   // Combinaison avec la normale des vagues
   normal = normalize(frag_in.normal + normal);
   
   // Éclairage simple (Phong)
   vec3 viewDir = normalize(uCameraPos - frag_in.worldPos);
   vec3 reflectDir = reflect(-uLightDir, normal);
   
   float diff = max(dot(normal, uLightDir), 0.0);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
   
   vec3 ambient = diffuse.rgb * 0.1;
   vec3 diffuseColor = diffuse.rgb * diff;
   vec3 specular = vec3(0.2) * spec; // Couleur spéculaire de l'eau
   
   outColor = vec4(ambient + diffuseColor + specular, diffuse.a);
}