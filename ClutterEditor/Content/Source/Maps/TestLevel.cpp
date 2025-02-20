#include <Maps/TestLevel.h>
#include <Core/ActorComponent/Actor.h>
#include <Core/Assets/Assets.h>
#include <Input/Input.h>
#include <Core/ActorComponent/Components/Graphics/FlipbookComponent.h>
#include <Core/ActorComponent/Components/Graphics/CameraComponent.h>

clt::Actor* player;
clt::Actor* camera;

TestLevel::TestLevel(std::string pName) : clt::Level(pName)
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::Load()
{
	std::vector<clt::Texture*> textures;

	for (int i = 0; i <= 4; i++)
	{
		std::string tempPath = std::to_string(i) + "_playerjumpv2.png";
		
		textures.push_back(clt::Assets::Get().LoadTexture("Content/Resources/Sprites/" + tempPath, tempPath + "_playerjumpSprite", clt::TextureFilter::NEAREST));
	}

	clt::Input::Get().MapKeysToAxis(clt::EKey::W, clt::EKey::S, "Vertical");

	clt::Input::Get().RegisterAxisCallback("Vertical", [this](float value) { this->TestMovement(value); });

	player = AddActor(new clt::Actor("test"));
	camera = AddActor(new clt::Actor("camera"));

	camera->AddComponent(new clt::CameraComponent());
	player->AddComponent(new clt::FlipbookComponent(textures, true));

}

void TestLevel::Update()
{
	
}

void TestLevel::Close()
{
}

void TestLevel::TestMovement(float value)
{
	player->AddActorLocationOffset({ 0, value });
}
