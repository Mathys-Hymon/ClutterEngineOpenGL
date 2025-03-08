#pragma once
#include <Core/ActorComponent/Components/Movements/PlayerController.h>

namespace clt
{
	class CLUTTER_API CameraController : public PlayerController
	{
	public:
		CameraController(std::string pMovementCallback, std::string pVerticalCallback, std::string pRotationCallback, float pSpeed = 2);
		~CameraController() = default;

		/**
 * @brief Handles player movement in a given direction.
 * @param pDirection The direction vector for movement.
 */
		virtual void Movement(Vector2 pDirection);

		virtual void MoveVertically(float pDirection);

		virtual void Rotation(Vector2 pRotation);
	};
}