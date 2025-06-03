#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Actor.h>

namespace clt
{
	class CLUTTER_API EditorCamera : public Actor
	{
	public :
		EditorCamera(Level* pLevel);
		~EditorCamera() = default;
	};
}