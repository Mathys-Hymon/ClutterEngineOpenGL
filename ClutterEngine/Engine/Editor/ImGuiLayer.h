#pragma once
#include <Core/CCommon.h>
#include <Editor/ContentBrowser.h>
#include <Editor/EditorViewport.h>
#include <Core/ActorComponent/Actor.h>
#include <Editor/Gizmo.h>
#include <Editor/Graph/Material/MaterialGraphEditorPanel.h>

namespace clt
{
	class EditorApplication;
	class CLUTTER_API ImGuiLayer
	{
		EditorApplication* mOwner;

		Gizmo* mActorGizmo{ nullptr };
		Actor* mFocusedActor{ nullptr };

	public:
		ImGuiLayer(EditorApplication* owner , class FrameBuffer* frameBuffer);
		~ImGuiLayer();

		void SetEditorTheme();
		void DrawGraphEditor();

		EditorApplication* GetOwner() { return mOwner; }

		void BeginFrame();
		void EndFrame();
		void DrawUI();
	};
}