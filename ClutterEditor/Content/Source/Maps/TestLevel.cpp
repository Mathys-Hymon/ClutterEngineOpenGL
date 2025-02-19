#include <Maps/TestLevel.h>
#include <Core/ActorComponent/Actor.h>
#include <Core/Assets/Assets.h>
#include <Core/ActorComponent/Components/Graphics/SpriteComponent.h>

clt::Actor* player;

TestLevel::TestLevel(std::string pName) : clt::Level(pName)
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::Load()
{
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/player.png", "theBlock", true);
	player = AddActor(new clt::Actor("test"));

	player->AddComponent(new clt::SpriteComponent(*clt::Assets::Get().GetTexture("theBlock")));


}

void TestLevel::Update()
{
	player->AddActorLocationOffset({ 0.1,1 });
	//std::cout << player->GetPosition().ToString() << std::endl;
}

void TestLevel::Close()
{
}
