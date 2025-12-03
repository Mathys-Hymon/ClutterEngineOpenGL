#pragma once
#include <Core/ActorComponent/Component.h>
#include <Core/Maths/Matrix/Matrix4Row.h>

enum class ProjectionMode { Orthographic, Perspective };

namespace clt
{
	class Level;
	class RendererGL;

	class CLUTTER_API CameraComponent : public Component
	{
		bool mDirty;

		Matrix4Row mView;
		Matrix4Row mProj;
		ProjectionMode mProjectionMode;

		float mFov;
		float mOrthoHeight;
		float mNearPlane;
		float mFarPlane;

		Vector2 mViewSize;

		void UpdateMatrices();

		virtual void SetOwner(Actor* pOwner) override;

		static CameraComponent* ACTIVE_CAMERA;

	public:
		CLUTTER_CLASS(CameraComponent);
		
		void SetupProperties() override 
		{
			CPROPERTY(mFov, clt::PropMode::ReadWrite);
			CPROPERTY(mProjectionMode, clt::PropMode::ReadWrite);
			CPROPERTY(mOrthoHeight, clt::PropMode::ReadWrite);
			CPROPERTY(mNearPlane, clt::PropMode::ReadWrite);
			CPROPERTY(mFarPlane, clt::PropMode::ReadWrite);
			CPROPERTY(mViewSize, clt::PropMode::ReadWrite);
		}
		
		CameraComponent(float pFOV = 70.0f, ProjectionMode pProjectionMode = ProjectionMode::Perspective, float pNearPlane = 0.1f, float pFarPlane = 10000.0f);

		~CameraComponent();

		virtual void Update() override;

		void SetFOV(float pFOV);
		void SetOrthoHeight(float pHeight);
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

		const ProjectionMode GetProjectionMode()
		{
			return mProjectionMode;
		}
	};
}