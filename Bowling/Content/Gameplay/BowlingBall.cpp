#include "BowlingBall.h"

BowlingBall::BowlingBall(clt::Level* pLevel, std::string pName) : clt::Actor(pLevel, pName)
{
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/ballTexture.png", "ballTexture");
	clt::Assets::Get().LoadMesh("Content/Resources/Mesh/sphere.obj", "ball", "ballTexture", false);

	SetActorScale(0.1f);
	AddComponent<clt::MeshComponent>("ball");
}

void BowlingBall::OnCollisionEnter(clt::ColliderComponent* collider, const hitResult& result)
{

}
