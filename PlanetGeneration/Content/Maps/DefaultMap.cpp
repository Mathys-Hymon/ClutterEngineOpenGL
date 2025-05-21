#include "DefaultMap.h"  
#include <Core/All.h>

clt::Actor* camera;

clt::Actor* planet;

float basicTimer = 0;

DefaultMap::DefaultMap(std::string pName) : clt::Level(pName)
{
}

DefaultMap::~DefaultMap()
{
}

void DefaultMap::Load()
{
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/metalFloor.png", "floor", TextureFilter::NEAREST);

	clt::ShaderProgram* cubemapProgram = new clt::ShaderProgram();

	clt::Shader* skyboxFrag = new clt::Shader();
	skyboxFrag->Load("Content/Resources/Shaders/Mesh/Skybox/skybox.frag", clt::ShaderType::FRAGMENT);
	clt::Shader* skyboxTesc = new clt::Shader();
	skyboxTesc->Load("Content/Resources/Shaders/Mesh/Skybox/skybox.tesc", clt::ShaderType::TESSELATION_CONTROL);
	clt::Shader* skyboxTese = new clt::Shader();
	skyboxTese->Load("Content/Resources/Shaders/Mesh/Skybox/skybox.tese", clt::ShaderType::TESSELATION_EVALUATION);
	clt::Shader* skyboxVert = new clt::Shader();
	skyboxVert->Load("Content/Resources/Shaders/Mesh/Skybox/skybox.vert", clt::ShaderType::VERTEX);

	cubemapProgram->Compose({ skyboxFrag , skyboxTesc ,skyboxTese ,skyboxVert });

	clt::Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cubeMap", cubemapProgram, true);

	camera = AddActor<clt::Actor>("camera");
	camera->SetActorLocation({ 10, 0, -12 });
	camera->SetActorRotation({ 0,180,0 });

	camera->AddComponent<clt::CameraComponent>();
	camera->AddComponent < clt::FPSController > ();
	camera->SetActorLocation({ 0, 0, 5 });

	planet = AddActor<clt::Actor>("planet");

	planet->AddComponent<clt::MeshComponent>(clt::Assets::Get().GetMesh("cubeMap", true));

}

void DefaultMap::Update()
{
}

void DefaultMap::Close()
{
}
