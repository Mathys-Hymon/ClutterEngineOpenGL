#include "pch.h"
#include <Core/ActorComponent/ChildActors/EditorCamera.h>
#include <Core/ActorComponent/Components/Movements/EditorController.h>
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>

using namespace clt;

EditorCamera::EditorCamera(Level* pLevel) : Actor(pLevel, "EditorCamera")
{
	AddComponent<CameraComponent>();
	AddComponent<EditorController>();
}
