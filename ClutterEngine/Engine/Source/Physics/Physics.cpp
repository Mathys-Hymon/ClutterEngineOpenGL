#include "pch.h"
#include <Physics/Physics.h>

using namespace clt;

void Physics::AddCollider(Collider2DComponent* pCollider)
{
	mColliders.emplace_back(pCollider);
}

void Physics::RemoveCollider(Collider2DComponent* pCollider)
{
	std::vector<Collider2DComponent*>::iterator gc;
	gc = std::find(mColliders.begin(), mColliders.end(), pCollider);
	mColliders.erase(gc);
}

void Physics::Update()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		std::vector<Collider2DComponent*> collisionCollider;

		for (int j = 0; j < mColliders.size(); j++)
		{
			Collider2DComponent* tempCollider = mColliders[j];

			if (j != i && mColliders[i]->CheckCollision(tempCollider))
			{
				collisionCollider.push_back(tempCollider);
			}
		}
		mColliders[i]->CollisionEnter(collisionCollider);

	}
}
