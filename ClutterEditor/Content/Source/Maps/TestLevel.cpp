#include <Maps/TestLevel.h>
#include <Core/ActorComponent/Actor.h>
#include <Core/Assets/Assets.h>
#include <Input/Input.h>
#include <Core/ActorComponent/Components/Graphics/FlipbookComponent.h>
#include <Core/ActorComponent/Components/Collisions/AABBCollider.h>
#include <Core/ActorComponent/Components/Movements/PlayerController.h>
#include <Core/ActorComponent/Components/Graphics/CameraComponent.h>
#include <Core/ActorComponent/Components/Physics/RigidBody2D.h>

clt::Actor* player;
clt::Actor* camera;
clt::Actor* block;

TestLevel::TestLevel(std::string pName) : clt::Level(pName)
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::Load()
{
	std::vector<clt::Texture*> textures;


	textures.emplace_back(clt::Assets::Get().LoadTexture("Content/Resources/Sprites/0_playerWalk.png", "0_PlayerWalk", TextureFilter::NEAREST));
	textures.emplace_back(clt::Assets::Get().LoadTexture("Content/Resources/Sprites/1_playerWalk.png", "1_PlayerWalk", TextureFilter::NEAREST));


	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/theBlock32.png", "theBlock");

	clt::Input::Get().MapKeysToAxis( EKey::A, EKey::D, "PlayerMovement");
	clt::Input::Get().MapKeyToAction(EKey::Space, "Jump", EInputState::Pressed);
	player = AddActor(new clt::Actor("player"));
	camera = AddActor(new clt::Actor("camera"));
	block = AddActor(new clt::Actor("block"));

	camera->AddComponent(new clt::CameraComponent());

	block->AddComponent(new clt::AABBCollider());
	block->AddComponent(new clt::SpriteComponent(clt::Assets::Get().GetTexture("theBlock")));
	block->SetActorLocation({ 0, -300 });
	block->SetActorScale({20, 1});

	player->AddComponent(new clt::FlipbookComponent(textures, true));
	player->AddComponent(new clt::AABBCollider({64,64}));
	player->AddComponent(new clt::RigidBody2D());
	player->AddComponent(new clt::PlayerController("PlayerMovement", "Jump", 4));

	player->GetComponentOfType<clt::FlipbookComponent>()->SetRelativeScale({ 5, 5 });
}

void TestLevel::Update()
{
	
}

void TestLevel::Close()
{
}
