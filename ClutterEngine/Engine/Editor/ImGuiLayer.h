#pragma once
#include <Core/CCommon.h>
#include <Graphics/FrameBuffer/FrameBuffer.h>

namespace clt
{
	class EditorApplication;
	class CLUTTER_API ImGuiLayer
	{
		FrameBuffer* mSceneFramebuffer;
		EditorApplication* mOwner;

		int mSelectedCamera = 0;
		float mPosition[3]{ 0,0,0 };
		float mRotation[3]{ 0,0,0 };
		float mScale[3]{ 1,1,1 };

	public:
		ImGuiLayer(EditorApplication* owner , FrameBuffer* frameBuffer);
		~ImGuiLayer();

		void SetEditorTheme();

		void BeginFrame();
		void EndFrame();
		void DrawUI();
	};
}