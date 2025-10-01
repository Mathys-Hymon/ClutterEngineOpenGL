#pragma once
#include <Core/CCommon.h>
#include <Editor/ContentBrowser.h>
#include <Editor/EditorViewport.h>
#include <Core/ActorComponent/Actor.h>
#include <Editor/Gizmo.h>

namespace clt
{
	class EditorApplication;
	class CLUTTER_API ImGuiLayer
	{
		EditorApplication* mOwner;
		ContentBrowser* mContentBrowser;
		EditorViewport* mViewport;

		Gizmo* mActorGizmo;
		Actor* mFocusedActor;

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