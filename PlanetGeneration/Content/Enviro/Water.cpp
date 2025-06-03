#include "Water.h"

Water::Water(clt::Level* pLevel, std::string pName) : clt::Actor(pLevel, pName)
{
	clt::ShaderProgram* waterShader = new clt::ShaderProgram();

	clt::Shader* waterFrag = new clt::Shader();
	waterFrag->Load("Content/Resources/Shaders/Wave/water.frag", clt::ShaderType::FRAGMENT);
	clt::Shader* waterTesc = new clt::Shader();
	waterTesc->Load("Content/Resources/Shaders/Sand/sand.tesc", clt::ShaderType::TESSELATION_CONTROL);
	clt::Shader* water = new clt::Shader();
	water->Load("Content/Resources/Shaders/Wave/water.tese", clt::ShaderType::TESSELATION_EVALUATION);
	clt::Shader* waterVert = new clt::Shader();
	waterVert->Load("Content/Resources/Shaders/Sand/sand.vert", clt::ShaderType::VERTEX);

	waterShader->Compose({ waterFrag , waterTesc ,water ,waterVert });

	

	AddComponent<clt::MeshComponent>(clt::Assets::Get().LoadMesh("Content/Resources/Mesh/plane.obj", "waterPlane", waterShader, true));
}
