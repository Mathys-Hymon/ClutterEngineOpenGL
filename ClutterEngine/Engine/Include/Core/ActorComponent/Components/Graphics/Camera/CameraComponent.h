#pragma once
#include <Core/ActorComponent/Component.h>
#include <Core/Maths/Matrix/Matrix4Row.h>

namespace clt
{
	enum class ProjectionMode { Orthographic, Perspective };

	class Level;
	class RendererGL;

	class CLUTTER_API CameraComponent : public Component
	{
		Matrix4Row mViewProj;
		ProjectionMode mProjectionMode;

		float mFov;
		float mNearPlane;
		float mFarPlane;

		Vector2 mViewSize;

		void UpdateProjViewMatrix();

		virtual void SetOwner(Actor* pOwner) override;

		static CameraComponent* ACTIVE_CAMERA;

	public:

		CameraComponent(ProjectionMode pProjectionMode = ProjectionMode::Orthographic, float pFOV = 90.0f, float pNearPlane = 0.1f, float pFarPlane = 100.0f);

		virtual void Update() override;

		void SetFOV(float pFOV);
		void SetProjectionMode(ProjectionMode pProjectionMode);
		void SetActive(CameraComponent* cam);
		static CameraComponent* GetActiveCamera();

		const Matrix4Row& GetViewMatrix() const { return mViewProj; }
	};
}