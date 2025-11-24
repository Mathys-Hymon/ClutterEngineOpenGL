#version 450 core

in vec2 fragTexCoord;
out vec4 outColor;

uniform sampler2D uBaseColor;

void main()
{
   outColor = texture(uBaseColor, fragTexCoord);

   if(outColor.a < 0.1) discard;
}
