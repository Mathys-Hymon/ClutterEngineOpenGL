#pragma once

#include <Core/CCommon.h>

#include <Core/ActorComponent/Actor.h>
#include <Core/ActorComponent/Component.h>

#include <Core/ActorComponent/Components/Collisions/2D/AABBCollider.h>
#include <Core/ActorComponent/Components/Collisions/2D/CircleCollider.h>
#include <Core/ActorComponent/Components/Collisions/ColliderComponent.h>
#include <Core/ActorComponent/Components/Collisions/HitResult.h>
#include <Core/ActorComponent/Components/Collisions/OBBCollider.h>
#include <Core/ActorComponent/Components/Collisions/SphereCollider.h>

#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>
#include <Core/ActorComponent/Components/Graphics/Camera/SpringArmComponent.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>
#include <Core/ActorComponent/Components/Graphics/Sprite/AnimatorComponent.h>
#include <Core/ActorComponent/Components/Graphics/UI/HUDComponent.h>

#include <Core/ActorComponent/Components/Movements/CameraController.h>
#include <Core/ActorComponent/Components/Movements/FpsController.h>
#include <Core/ActorComponent/Components/Movements/PlayerController2D.h>

#include <Core/ActorComponent/Components/Physics/RigidBody.h>

#include <Core/ActorComponent/ChildActors/CubeActor.h>

#include <Core/Assets/Assets.h>

#include <Core/Debug/DebugDraw.h>
#include <Core/Debug/CLog/CLog.h>

#include <Core/Levels/LevelManager.h>
#include <Core/Levels/Level.h>

#include <Core/Maths/Color.h>
#include <Core/Maths/CRectangle.h>
#include <Core/Maths/Maths.h>
#include <Core/Maths/Matrix/Matrix4.h>
#include <Core/Maths/Matrix/Matrix4Row.h>
#include <Core/Maths/Quaternion.h>
#include <Core/Maths/Transforms/Transform.h>
#include <Core/Maths/Transforms/Transform2D.h>
#include <Core/Maths/Vectors/Vector2.h>
#include <Core/Maths/Vectors/Vector3.h>
#include <Core/Maths/Vectors/Vector4.h>

#include <Core/Timer.h>

#include <Input/Input.h>

#include <Graphics/UI/Elements/AnimatorElement.h>
#include <Graphics/UI/Elements/TextElement.h>