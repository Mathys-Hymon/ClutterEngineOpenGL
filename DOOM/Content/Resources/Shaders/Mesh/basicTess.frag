#version 450

in TESE_OUT{
   vec4 color;
   vec2 texCoord;

} frag_in;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
   FragColor = frag_in.color * texture(uTexture, frag_in.texCoord);
}
