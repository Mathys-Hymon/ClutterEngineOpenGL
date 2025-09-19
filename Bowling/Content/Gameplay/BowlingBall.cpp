#include "BowlingBall.h"

BowlingBall::BowlingBall(clt::Level* pLevel, std::string pName) : clt::Actor(pLevel, pName)
{
	clt::Assets::Get().LoadMesh("Content/Resources/Mesh/sphere.obj", "ball", false);

	SetActorScale(0.2f);
	auto ball = AddComponent<clt::MeshComponent>("ball");
	ball->SetTexture("BaseColor", clt::Assets::Get().LoadTexture("Content/Resources/Sprites/ballTexture.png", "ballTexture"));

	AddComponent<clt::BulletCollider>(ColliderShapeType::Sphere);
	AddComponent<clt::BulletRigidBody>();
}

void BowlingBall::Update()
{
	Vector3 rot = GetComponentOfType<clt::BulletRigidBody>()->GetVelocity();

	GetComponentOfType<clt::MeshComponent>()->AddRelativeRotation(Vector3{rot.z,0,rot.x });
}
