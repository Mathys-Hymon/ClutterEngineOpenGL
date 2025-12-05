#version 450

struct Particle 
{
    vec4 position;
    vec4 velocity;
    vec4 color;
};

layout(std430, binding = 0) buffer ParticleBuffer 
{
    Particle particles[];
};

uniform mat4 uViewProj;
uniform mat4 uWorldTransform;

out vec4 vColor;

void main() 
{
    Particle p = particles[gl_VertexID];

    if (p.position.w <= 0.0) 
    {
        gl_Position = vec4(-1000, -1000, 0, 0);
        return;
    }

    gl_Position = vec4(p.position.xyz, 1.0)* uWorldTransform * uViewProj;

    gl_PointSize = 20.0;

    float alpha = clamp(p.position.w, 0.0, 1.0);

    vColor = vec4(1.0, 0.5 + alpha * 0.5, 0.2, alpha);
}