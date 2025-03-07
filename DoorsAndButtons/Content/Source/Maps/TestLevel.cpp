#include <Maps/TestLevel.h>
#include <Core/ActorComponent/Actor.h>
#include <Core/Assets/Assets.h>
#include <Input/Input.h>
#include <Core/ActorComponent/Components/Graphics/Sprite/AnimatorComponent.h>
#include <Core/ActorComponent/Components/Collisions/OBBCollider.h>
#include <Core/ActorComponent/Components/Movements/PlayerController.h>
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>
#include <Core/ActorComponent/Components/Graphics/Camera/SpringArmComponent.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>
#include <Core/ActorComponent/Components/Physics/RigidBody.h>

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

	runAnim = clt::Assets::Get().BulkLoadTexture("Content/Resources/Sprites/", 1, "_playerWalk.png", "_PlayerWalk", TextureFilter::NEAREST);

	jumpAnim = clt::Assets::Get().BulkLoadTexture("Content/Resources/Sprites/", 4, "_playerjumpv2.png", "_jump", TextureFilter::NEAREST);

	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/theBlock.png", "tile", TextureFilter::NEAREST);
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/crate.png", "crate", TextureFilter::NEAREST);

	clt::Input::Get().MapKeysToAxis( EKey::A, EKey::D, "PlayerMovement");
	clt::Input::Get().MapKeyToAction(EKey::Space, "Jump", EInputState::Pressed);

	AddActor(new clt::Actor("player"));

	player = GetActorOfType<clt::Actor>();
	camera = AddActor(new clt::Actor("camera"));
	block  = AddActor(new clt::Actor("block"));
	crate  = AddActor(new clt::Actor("crate"));

	camera->AddComponent<clt::CameraComponent>();
	camera->SetActorLocation({ 0, 0, 5 });

	crate->AddComponent<clt::SpriteComponent>(clt::Assets::Get().GetTexture("crate"));
	crate->SetActorScale(75);
	crate->SetActorLocation({ 10, 0 });

	block->AddComponent<clt::MeshComponent>(clt::Assets::Get().GetTexture("tile"));
	//block->AddComponent<clt::OBBCollider>();
	//block->AddComponent<clt::RigidBody>();
}

void TestLevel::Update()
{
	//block->AddActorRotationOffset({ 0, 0, 1 });
	block->AddActorLocationOffset(block->getTransform().Up() / 10);
}

void TestLevel::Close()
{
}
