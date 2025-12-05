#include "pch.h"
#include "ParticleComponent.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <random>

#include "Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h"
#include "Core/Assets/Assets.h" 

using namespace clt;

ParticleComponent::ParticleComponent(int pUpdateOrder)
    : Component(pUpdateOrder)
{
}

ParticleComponent::~ParticleComponent()
{
}

void ParticleComponent::Start()
{
    Component::Start();
    InitShader();
    InitBuffer();
}


void ParticleComponent::InitBuffer()
{
    std::vector<GPUParticle> initialParticles(mMaxParticles);
    for (auto& p : initialParticles)
    {
        p.Position = Vector4(0, 0, 0, -1.0f);
        p.Velocity = Vector4(0, 0, 0, 0);
        p.Color    = Color(1, 1, 1, 0);
    }

    if (mSSBO != 0) glDeleteBuffers(1, &mSSBO);

    glGenBuffers(1, &mSSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, mSSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, initialParticles.size() * sizeof(GPUParticle), initialParticles.data(), GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, mSSBO); 
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    if (mVAO == 0) glGenVertexArrays(1, &mVAO);
}

void ParticleComponent::InitShader()
{
    std::string computePath = "Content/Resources/Shaders/Particle/particle.comp";
    std::string vertPath    = "Content/Resources/Shaders/Particle/particle.vert";
    std::string fragPath    = "Content/Resources/Shaders/Particle/particle.frag";

    std::string computeCode = LoadShaderSource(computePath);
    std::string vertexCode  = LoadShaderSource(vertPath);
    std::string fragCode    = LoadShaderSource(fragPath);

    if (!computeCode.empty())
    {
        GLuint compObj = CompileShader(GL_COMPUTE_SHADER, computeCode.c_str());
        if (compObj != 0)
        {
            mComputeShader = CreateComputeProgram(compObj);
            glDeleteShader(compObj);
        }
    }
    else {
        std::cerr << "[ParticleSystem] Erreur: Code source Compute vide ou fichier introuvable." << std::endl;
    }

    if (!vertexCode.empty() && !fragCode.empty())
    {
        GLuint vertObj = CompileShader(GL_VERTEX_SHADER, vertexCode.c_str());
        GLuint fragObj = CompileShader(GL_FRAGMENT_SHADER, fragCode.c_str());

        if (vertObj != 0 && fragObj != 0)
        {
            mRenderShader = CreateShaderProgram(vertObj, fragObj);
            glDeleteShader(vertObj);
            glDeleteShader(fragObj);
        }
    }
    else {
        std::cerr << "[ParticleSystem] Erreur: Code source Vert/Frag vide." << std::endl;
    }
}


void ParticleComponent::Update()
{
    Component::Update();

    if (!IsActive()) return;

    float dt = 0.016f; 
    mElapsedTime += dt;

    if (!mIsLooping && mElapsedTime > (mDuration + 2.0f))
    {
        mIsActive = false;
        mOwner->RemoveComponent<ParticleComponent>();
        return;
    }

    if (mComputeShader == 0) return;

    glUseProgram(mComputeShader);

    Vector3 worldPos = GetWorldLocation();
    
    glUniform1f(glGetUniformLocation(mComputeShader, "deltaTime"), dt);
    glUniform3f(glGetUniformLocation(mComputeShader, "emitterPos"), worldPos.x, worldPos.y, worldPos.z);
    glUniform1f(glGetUniformLocation(mComputeShader, "time"), mElapsedTime);
    
    bool shouldSpawn = mIsLooping || (mElapsedTime < mDuration);
    glUniform1i(glGetUniformLocation(mComputeShader, "shouldSpawn"), shouldSpawn ? 1 : 0);
    glUniform1f(glGetUniformLocation(mComputeShader, "randomSeed"), (float)rand() / RAND_MAX);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, mSSBO);

    int groupCount = (mMaxParticles + 127) / 128; 
    glDispatchCompute(groupCount, 1, 1);

    glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT);
    
    if (mRenderShader == 0) return;

    glUseProgram(mRenderShader);

    auto activeCamera = CameraComponent::GetActiveCamera();
    if (activeCamera)
    {
        Matrix4Row viewProj = activeCamera->GetViewProjMatrices();
        glUniformMatrix4fv(glGetUniformLocation(mRenderShader, "uViewProj"), 1, GL_TRUE, viewProj.GetAsFloatPtr());
        
        Matrix4Row worldTransform = GetWorldTransform().GetMat4Transform();
        glUniformMatrix4fv(glGetUniformLocation(mRenderShader, "uWorldTransform"), 1, GL_TRUE, worldTransform.GetAsFloatPtr());
    }

    glBindVertexArray(mVAO);
    
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDepthMask(GL_FALSE);
    
    glDrawArrays(GL_POINTS, 0, mMaxParticles);
    
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glBindVertexArray(0);
    glUseProgram(0);
}

void ParticleComponent::Destroy()
{
    if (mSSBO) { glDeleteBuffers(1, &mSSBO); mSSBO = 0; }
    if (mVAO) { glDeleteVertexArrays(1, &mVAO); mVAO = 0; }
    
    if (mComputeShader) { glDeleteProgram(mComputeShader); mComputeShader = 0; }
    if (mRenderShader) { glDeleteProgram(mRenderShader); mRenderShader = 0; }
    
    Component::Destroy();
}

std::string ParticleComponent::LoadShaderSource(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        CLUTTER_WARNING(("shader files failed to load :" + filePath).c_str());
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint ParticleComponent::CompileShader(GLenum type, const char* source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success; 
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) 
    {
        char log[1024]; 
        glGetShaderInfoLog(shader, 1024, NULL, log);
        std::string typeStr = (type == GL_COMPUTE_SHADER ? "COMPUTE" : (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"));
        std::string l = log;
        CLUTTER_ERROR("ERROR COMPILATION SHADER [" + typeStr + "]:\n" + l);
        return 0;
    }
    return shader;
}

GLuint ParticleComponent::CreateComputeProgram(GLuint computeShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, computeShader);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetProgramInfoLog(program, 1024, NULL, log);
        std::string l = log;
        CLUTTER_ERROR("ERREUR LINK PROGRAM COMPUTE:\n" + l);
        return 0;
    }
    return program;
}

GLuint ParticleComponent::CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Vérification erreurs link
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetProgramInfoLog(program, 1024, NULL, log);
        std::string l = log;
        CLUTTER_ERROR("ERREUR LINK RENDER PROGRAM :\n" + l);
        return 0;
    }
    return program;
}

void ParticleComponent::SetMaxParticles(unsigned int pMaxParticles)
{
    mMaxParticles = pMaxParticles;
}

void ParticleComponent::SetLooping(bool pIsLooping)
{
    mIsLooping = pIsLooping;
}

void ParticleComponent::SetDuration(float pDuration)
{
    mDuration = pDuration;
}