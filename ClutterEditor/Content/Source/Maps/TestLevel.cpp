#include <Maps/TestLevel.h>
#include <Core/ActorComponent/Actor.h>
#include <Core/Assets/Assets.h>
#include <Core/ActorComponent/Components/Graphics/SpriteComponent.h>

TestLevel::TestLevel(std::string pName) : clt::Level(pName)
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::Load()
{
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/theBlock.png", "theBlock");
	auto* player = AddActor(new clt::Actor("test"));

	player->AddComponent(new clt::SpriteComponent(player, *clt::Assets::Get().GetTexture("theBlock")));
	player->SetActorLocation({ 250,250 });

}

void TestLevel::Update()
{
}

void TestLevel::Close()
{
}
