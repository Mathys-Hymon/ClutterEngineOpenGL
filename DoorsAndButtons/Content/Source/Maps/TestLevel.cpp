#include <Maps/TestLevel.h>
#include <Core/ActorComponent/Actor.h>
#include <Core/Assets/Assets.h>
#include <Input/Input.h>
#include <Core/ActorComponent/Components/Graphics/AnimatorComponent.h>
#include <Core/ActorComponent/Components/Collisions/AABBCollider.h>
#include <Core/ActorComponent/Components/Movements/PlayerController.h>
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>
#include <Core/ActorComponent/Components/Graphics/Camera/SpringArmComponent.h>
#include <Core/ActorComponent/Components/Physics/RigidBody2D.h>

clt::Actor* player;
clt::Actor* camera;
clt::Actor* block;
clt::Actor* crate;

TestLevel::TestLevel(std::string pName) : clt::Level(pName)
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::Load()
{
	std::vector<clt::Texture*> runAnim;
	std::vector<clt::Texture*> jumpAnim;

	runAnim.emplace_back(clt::Assets::Get().LoadTexture("Content/Resources/Sprites/0_playerWalk.png", "0_PlayerWalk", TextureFilter::NEAREST));
	runAnim.emplace_back(clt::Assets::Get().LoadTexture("Content/Resources/Sprites/1_playerWalk.png", "1_PlayerWalk", TextureFilter::NEAREST));

	for (int i = 0; i < 4; i++)
	{
		std::string tempPaths =  std::to_string(i) + "_playerjumpv2.png";
		jumpAnim.emplace_back(clt::Assets::Get().LoadTexture("Content/Resources/Sprites/" + tempPaths, std::to_string(i) +"_jump", TextureFilter::NEAREST));
	}

	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/tile.png", "tile", TextureFilter::NEAREST);
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/crate.png", "crate", TextureFilter::NEAREST);

	clt::Input::Get().MapKeysToAxis( EKey::A, EKey::D, "PlayerMovement");
	clt::Input::Get().MapKeyToAction(EKey::Space, "Jump", EInputState::Pressed);
	player = AddActor(new clt::Actor("player"));
	camera = AddActor(new clt::Actor("camera"));
	block = AddActor(new clt::Actor("block"));
	crate = AddActor(new clt::Actor("crate"));

	camera->AddComponent(new clt::CameraComponent());

	crate->AddComponent(new clt::AABBCollider({16,16}));
	crate->AddComponent(new clt::RigidBody2D());
	crate->AddComponent(new clt::SpriteComponent(clt::Assets::Get().GetTexture("crate")));
	crate->SetActorScale(4);
	crate->SetActorLocation({ 100, 0 });

	block->AddComponent(new clt::AABBCollider({16,16}));
	block->AddComponent(new clt::SpriteComponent(clt::Assets::Get().GetTexture("tile")));
	block->SetActorLocation({ 0, -300 });
	block->SetActorScale({50,3});

	player->AddComponent(new clt::AnimatorComponent("walk", runAnim));
	player->GetComponentOfType<clt::AnimatorComponent>()->AddNewAnim("jump", jumpAnim, false);
	player->GetComponentOfType<clt::AnimatorComponent>()->GetAnim("jump")->SetFlipbookFps(7);

	player->AddComponent(new clt::AABBCollider({16,16}));
	player->AddComponent(new clt::RigidBody2D());
	player->AddComponent(new clt::SpringArmComponent(camera, 10));
	player->AddComponent(new clt::PlayerController("PlayerMovement", "Jump", 10));

	player->SetActorScale(5);
}

void TestLevel::Update()
{
}

void TestLevel::Close()
{
}
