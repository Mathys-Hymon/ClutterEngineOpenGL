#include <Maps/TestLevel.h>
#include <Core/ActorComponent/Actor.h>
#include <Core/Assets/Assets.h>
#include <Core/ActorComponent/Components/GraphicComponent.h>

TestLevel::TestLevel(std::string pName) : clt::Level(pName)
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::Load()
{
	//clt::Assets::Get().LoadTexture("Content/Sprites/theBlock.png", "theBlock");
	auto* player = AddActor(new clt::Actor("zizi"));

	player->AddComponent(new clt::GraphicComponent(player));

}

void TestLevel::Update()
{
}

void TestLevel::Close()
{
}
