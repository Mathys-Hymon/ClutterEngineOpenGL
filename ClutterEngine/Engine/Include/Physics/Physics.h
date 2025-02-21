#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Components/Collisions/Collider2DComponent.h>
#include <unordered_map>

namespace clt
{
	class CLUTTER_API Physics
	{
		std::vector<Collider2DComponent*> mColliders;

	public:
		Physics();
		~Physics();

		void AddCollider(Collider2DComponent* pCollider);
		void RemoveCollider(Collider2DComponent* pCollider);

		void Update();
	};
}