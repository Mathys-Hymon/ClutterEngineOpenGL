#include "BowlingBall.h"

BowlingBall::BowlingBall(clt::Level* pLevel, std::string pName) : clt::Actor(pLevel, pName)
{
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/ballTexture.png", "ballTexture");
	clt::Assets::Get().LoadMesh("Content/Resources/Mesh/sphere.obj", "ball", "ballTexture", false);

	SetActorScale(0.2f);
	AddComponent<clt::MeshComponent>("ball");
	
	AddComponent<clt::OBBCollider>(Vector3{ 10, 10, 10 })->mFriction = 0.5f;
	AddComponent<clt::RigidBody>()->SetMass(1);
}

void BowlingBall::OnCollisionEnter(clt::ColliderComponent* collider, const hitResult& result)
{
}