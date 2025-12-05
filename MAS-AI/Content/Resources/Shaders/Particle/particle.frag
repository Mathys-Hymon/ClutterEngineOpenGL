#version 450
in vec4 vColor;
out vec4 FragColor;

void main() 
{
    vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
    if (dot(circCoord, circCoord) > 1.0) {
        discard;
    }

    float alpha = 1.0 - dot(circCoord, circCoord);
    FragColor = vColor * alpha;
}