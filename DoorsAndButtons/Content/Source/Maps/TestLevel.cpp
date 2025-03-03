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
clt::Actor* block2;
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

	runAnim = clt::Assets::Get().BulkLoadTexture("Content/Resources/Sprites/", 1, "_playerWalk.png", "_PlayerWalk", TextureFilter::NEAREST);

	jumpAnim = clt::Assets::Get().BulkLoadTexture("Content/Resources/Sprites/", 4, "_playerjumpv2.png", "_jump", TextureFilter::NEAREST);

	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/tile.png", "tile", TextureFilter::NEAREST);
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/crate.png", "crate", TextureFilter::NEAREST);

	clt::Input::Get().MapKeysToAxis( EKey::A, EKey::D, "PlayerMovement");
	clt::Input::Get().MapKeyToAction(EKey::Space, "Jump", EInputState::Pressed);

	AddActor(new clt::Actor("player"));

	player = GetActorOfType<clt::Actor>();
	camera = AddActor(new clt::Actor("camera"));
	block  = AddActor(new clt::Actor("block"));
	block2 = AddActor(new clt::Actor("block2"));
	crate  = AddActor(new clt::Actor("crate"));

	camera->AddComponent<clt::CameraComponent>();

	crate->AddComponent<clt::AABBCollider>(Vector2(16, 16));
	crate->AddComponent<clt::RigidBody2D>();
	crate->AddComponent<clt::SpriteComponent>(clt::Assets::Get().GetTexture("crate"));
	crate->SetActorScale(4);
	crate->SetActorLocation({ 100, 0 });

	block->AddComponent<clt::AABBCollider>(Vector2(16, 16));
	block->AddComponent<clt::SpriteComponent>(clt::Assets::Get().GetTexture("tile"));
	block->SetActorLocation({ 0, -300 });
	block->SetActorScale({50,3});

	block2->AddComponent<clt::AABBCollider>(Vector2(16,16 ));
	block2->AddComponent<clt::SpriteComponent>(clt::Assets::Get().GetTexture("tile"));
	block2->SetActorLocation({ 50, -150 });
    block2->SetActorScale({ 5,3 });

	player->AddComponent<clt::AnimatorComponent>("walk", runAnim);
	player->GetComponentOfType<clt::AnimatorComponent>()->AddNewAnim("jump", jumpAnim, false);
	player->GetComponentOfType<clt::AnimatorComponent>()->GetAnim("jump")->SetFlipbookFps(7);

	player->AddComponent<clt::AABBCollider>(Vector2(16,16));
	player->GetComponentOfType<clt::AABBCollider>()->SetRelativePosition({0, -4});
	player->AddComponent<clt::RigidBody2D>();
	player->AddComponent<clt::SpringArmComponent>(camera, 10);
	player->AddComponent<clt::PlayerController>("PlayerMovement", "Jump", 25);

	player->SetActorScale(5);
}

void TestLevel::Update()
{
}

void TestLevel::Close()
{
}
