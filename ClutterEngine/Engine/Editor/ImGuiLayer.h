#pragma once
#include <Core/CCommon.h>
#include <Editor/ContentBrowser.h>
#include <Editor/EditorViewport.h>
#include <Core/ActorComponent/Actor.h>

namespace clt
{
	class EditorApplication;
	class CLUTTER_API ImGuiLayer
	{
		EditorApplication* mOwner;
		ContentBrowser* mContentBrowser;
		EditorViewport* mViewport;

		Actor* mFocusedActor;

		int mSelectedCamera = 0;
		float mPosition[3]{ 0,0,0 };
		float mRotation[3]{ 0,0,0 };
		float mScale[3]{ 1,1,1 };

		void DrawGizmoCamera();

	public:
		ImGuiLayer(EditorApplication* owner , FrameBuffer* frameBuffer);
		~ImGuiLayer();

		void SetEditorTheme();

		EditorApplication* GetOwner() { return mOwner; }

		void BeginFrame();
		void EndFrame();
		void DrawUI();
	};
}