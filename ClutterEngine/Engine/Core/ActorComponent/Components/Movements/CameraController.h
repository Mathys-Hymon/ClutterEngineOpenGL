#pragma once
#include <Core/ActorComponent/Components/Movements/PlayerController.h>

namespace clt
{
	class CLUTTER_API CameraController : public PlayerController
	{
	public:
		CameraController(std::string pMovementCallback, std::string pVerticalMovementCallback, float pSpeed = 2);
		~CameraController() = default;

		/**
 * @brief Handles player movement in a given direction.
 * @param pDirection The direction vector for movement.
 */
		void Movement(Vector2 pDirection);

		void MoveVertically(float pDirection);

		void Rotation(Vector2 pRotation);

		virtual void OnCollisionEnter(const hitResult& result) override {};
		virtual void OnCollisionStay(const hitResult& result)  override {};
		virtual void OnCollisionExit(const hitResult& result)  override {};
	};
}