#pragma once
#include "Core/ActorComponent/Component.h"
#include "Core/Maths/Vectors/Vector4.h"
#include "Core/Maths/Color.h"

namespace clt
{
    struct GPUParticle
    {
        Vector4 Position; // x, y, z, w (lifetime)
        Vector4 Velocity; // vx, vy, vz, vw (padding)
        Color Color;      // r, g, b, a
    };

    class CLUTTER_API ParticleComponent : public Component
    {
        unsigned int mMaxParticles = 100000;
        bool mIsLooping = true;
        float mDuration = 5.0f;
        float mElapsedTime = 0.0f;

        GLuint mSSBO = 0; 
        GLuint mVAO = 0;    
        GLuint mComputeShader = 0;
        GLuint mRenderShader = 0;
        
        void InitShader();
        void InitBuffer();
        
        // Helpers OpenGL
        std::string LoadShaderSource(const std::string& filePath);
        GLuint CompileShader(GLenum type, const char* source);
        GLuint CreateComputeProgram(GLuint computeShader);
        GLuint CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader);
        
    public:
        ParticleComponent(int pUpdateOrder = 0);
        virtual ~ParticleComponent();

        void Start() override;
        void Update() override;
        void Destroy() override;

        // Setters
        void SetMaxParticles(unsigned int pMaxParticles);
        void SetLooping(bool pIsLooping);
        void SetDuration(float pDuration);
        
    };
}