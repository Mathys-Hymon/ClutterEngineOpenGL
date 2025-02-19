#include <Maps/TestLevel.h>
#include <Core/ActorComponent/Actor.h>
#include <Core/Assets/Assets.h>
//#include <Core/Assets/AssetsType/Texture.h>
#include <Core/ActorComponent/Components/Graphics/FlipbookComponent.h>

clt::Actor* player;

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
		
		textures.push_back(clt::Assets::Get().LoadTexture("Content/Resources/Sprites/" + tempPath, tempPath + "_playerjumpSprite", true));
	}

	//clt::Assets::Get().LoadTexture("Content/Resources/Sprites/player.png", "theBlock", true);
	player = AddActor(new clt::Actor("test"));

	player->AddComponent(new clt::FlipbookComponent(textures));
}

void TestLevel::Update()
{
	player->AddActorLocationOffset({ 0.1,1 });
	//std::cout << player->GetPosition().ToString() << std::endl;
}

void TestLevel::Close()
{
}
