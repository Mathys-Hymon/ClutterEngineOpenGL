#include <Maps/TestLevel.h>
#include <Core/ActorComponent/Actor.h>
#include <Core/Assets/Assets.h>
#include <Core/ActorComponent/Components/Graphics/FlipbookComponent.h>
#include <Core/ActorComponent/Components/Graphics/CameraComponent.h>

clt::Actor* player;
clt::Actor* cam;

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

	//player = 

	//clt::Assets::Get().LoadTexture("Content/Resources/Sprites/player.png", "theBlock", true);
	player = AddActor(new clt::Actor("test"));

	cam = AddActor(new clt::Actor("Camera"));

	cam->AddComponent(new clt::CameraComponent());
	player->AddComponent(new clt::FlipbookComponent(textures, true));

}

void TestLevel::Update()
{
	//player->AddActorLocationOffset({0.001f, 0});
	cam->AddActorLocationOffset({-0.2f, -0.2f});
	//std::cout << cam->GetRelativePosition().ToString() << std::endl;
}

void TestLevel::Close()
{
}
