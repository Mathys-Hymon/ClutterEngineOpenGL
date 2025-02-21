#include <Maps/TestLevel.h>
#include <Core/ActorComponent/Actor.h>
#include <Core/Assets/Assets.h>
#include <Input/Input.h>
#include <Core/ActorComponent/Components/Graphics/FlipbookComponent.h>
#include <Core/ActorComponent/Components/Movements/PlayerController.h>
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

	textures.emplace_back(clt::Assets::Get().LoadTexture("Content/Resources/Sprites/0_playerWalk.png", "0_PlayerWalk", clt::TextureFilter::NEAREST));
	textures.emplace_back(clt::Assets::Get().LoadTexture("Content/Resources/Sprites/1_playerWalk.png", "1_PlayerWalk", clt::TextureFilter::NEAREST));

	clt::Input::Get().MapKeysToVect( EKey::A, EKey::D,EKey::W, EKey::S, "PlayerMovement");

	player = AddActor(new clt::Actor("player"));
	camera = AddActor(new clt::Actor("camera"));

	camera->AddComponent(new clt::CameraComponent());

	player->AddComponent(new clt::FlipbookComponent(textures, true));
	player->AddComponent(new clt::PlayerController("PlayerMovement"));

	player->GetComponentOfType<clt::FlipbookComponent>()->SetRelativeScale({ 5, 5 });
}

void TestLevel::Update()
{
	
}

void TestLevel::Close()
{
}
