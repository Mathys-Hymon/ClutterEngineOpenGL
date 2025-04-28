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
		bool mDirty;

		Matrix4Row mView;
		Matrix4Row mProj;
		ProjectionMode mProjectionMode;

		float mFov;
		float mNearPlane;
		float mFarPlane;

		Vector2 mViewSize;

		void UpdateMatrices();

		virtual void SetOwner(Actor* pOwner) override;

		static CameraComponent* ACTIVE_CAMERA;

	public:

		CameraComponent(float pFOV = 70.0f, ProjectionMode pProjectionMode = ProjectionMode::Perspective, float pNearPlane = 0.1f, float pFarPlane = 10000.0f);

		virtual void Update() override;

		void SetFOV(float pFOV);
		void SetProjectionMode(ProjectionMode pProjectionMode);
		void SetActive(CameraComponent* cam);
		void SetActive();

		static CameraComponent* GetActiveCamera();

		const Matrix4Row& GetViewMatrix() 
		{
			if (mDirty) UpdateMatrices();
			return mView; 
		}
		const Matrix4Row& GetProjectionMatrix() 
		{ 
			if (mDirty) UpdateMatrices();
			return mProj; 
		}
		const Matrix4Row& GetViewProjMatrices() 
		{ 
			if (mDirty) UpdateMatrices();
			return mView * mProj; 
		}
	};
}