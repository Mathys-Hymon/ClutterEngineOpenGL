#version 450 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 tintColor = vec3(1.0f, 1.0f, 1.0f);;

void main()
{    
    color = texture(image, TexCoords);
    color.rgb *= tintColor;

    if(color.a < 0.1) discard;
}