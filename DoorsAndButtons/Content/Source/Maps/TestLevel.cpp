#include <Maps/TestLevel.h>
#include <Core/ActorComponent/Actor.h>
#include <Core/Assets/Assets.h>
#include <Input/Input.h>
#include <Core/Maths/Color.h>
#include <Core/ActorComponent/Components/Graphics/Sprite/AnimatorComponent.h>
#include <Core/ActorComponent/Components/Collisions/OBBCollider.h>
#include <Core/ActorComponent/Components/Movements/PlayerController.h>
#include <Core/ActorComponent/Components/Movements/CameraController.h>
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>
#include <Core/ActorComponent/Components/Graphics/Camera/SpringArmComponent.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>
#include <Core/ActorComponent/Components/Physics/RigidBody.h>
#include <Graphics/UI/Elements/SpriteElement.h>

#include <Core/Debug/DebugDraw.h>

clt::Actor* player;
clt::Actor* camera;
clt::Actor* block;
clt::Actor* crate;
clt::Actor* floorActor;

TestLevel::TestLevel(std::string pName) : clt::Level(pName)
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::Load()
{
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/theBlock.png", "tile", TextureFilter::NEAREST);
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/crate.png", "crate", TextureFilter::NEAREST);

	clt::Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube");

	clt::Input::Get().MapKeysToVect( EKey::A, EKey::D, EKey::W, EKey::S, "PlayerMovement");
	clt::Input::Get().MapKeysToAxis(EKey::LeftShift, EKey::LeftControl, "MovementVertical");

	AddActor(new clt::Actor("player"));

	player = GetActorOfType<clt::Actor>();
	camera = AddActor(new clt::Actor("camera"));
	block  = AddActor(new clt::Actor("block"));
	crate  = AddActor(new clt::Actor("crate"));
	floorActor = AddActor(new clt::Actor("floor"));

	camera->AddComponent<clt::HUDComponent>()->
		CreateWidget<clt::UIPanel>("playerHUD")->
		CreateElement<clt::WidgetElement>("SpriteTest", "crate");

	camera->AddComponent<clt::CameraComponent>(70.0f);
	camera->SetActorLocation({ 0, 0, 5 });
	camera->AddComponent<clt::CameraController>("PlayerMovement", "MovementVertical");


	crate->AddComponent<clt::SpriteComponent>(clt::Assets::Get().GetTexture("crate"));

	floorActor->AddComponent<clt::MeshComponent>(clt::Assets::Get().GetMesh("cube"));
	floorActor->AddComponent<clt::OBBCollider>();
	floorActor->SetActorScale({ 5,0.5f,6 });
	floorActor->SetActorLocation({ 0, -2, 0 });

	block->AddComponent<clt::MeshComponent>(clt::Assets::Get().GetMesh("cube"));
	block->AddComponent<clt::OBBCollider>();
	block->AddComponent<clt::RigidBody>();
	block->SetActorScale(0.5f);

}

void TestLevel::Update()
{
}

void TestLevel::Close()
{
}
