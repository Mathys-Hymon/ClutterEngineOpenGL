#include "BowlingBall.h"

BowlingBall::BowlingBall(clt::Level* pLevel, std::string pName) : clt::Actor(pLevel, pName)
{
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/ballTexture.png", "ballTexture");
	clt::Assets::Get().LoadMesh("Content/Resources/Mesh/sphere.obj", "ball", "ballTexture", false);

	SetActorScale(0.2f);
	AddComponent<clt::MeshComponent>("ball");
	
	AddComponent<clt::SphereCollider>()->mFriction = 0.5f;
	AddComponent<clt::RigidBody>()->SetMass(1);
}

void BowlingBall::Update()
{
	Vector3 rot = GetComponentOfType<clt::RigidBody>()->GetVelocity();

	GetComponentOfType<clt::MeshComponent>()->AddRelativeRotation(Vector3{rot.z,0,rot.x } * clt::Timer::deltaTime);
}
