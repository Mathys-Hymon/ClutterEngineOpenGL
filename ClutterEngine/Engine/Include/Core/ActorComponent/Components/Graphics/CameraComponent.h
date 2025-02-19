#pragma once
#include <Core/ActorComponent/Component.h>
#include <glm/glm.hpp>

namespace clt
{
	enum class ProjectionMode { Orthographic, Perspective };

	class Level;
	class Renderer;

	class CLUTTER_API CameraComponent : public Component
	{
		glm::mat4 mView;
		glm::mat4 mProjection;
		ProjectionMode mProjectionMode;

		float mFov;
		float mNearPlane;
		float mFarPlane;

		Vector2 mViewSize;

		void UpdateViewMatrix();
		void UpdateProjectionMatrix();

		virtual void SetOwner(Actor* pOwner) override;

	public:

		CameraComponent(ProjectionMode pProjectionMode = ProjectionMode::Orthographic, float pFOV = 90.0f, float pNearPlane = 0.1f, float pFarPlane = 100.0f);

		virtual void Update() override;

		const glm::mat4& GetViewMatrix() const { return mView; }
		const glm::mat4& GetProjectionMatrix() const { return mProjection; }
	};
}