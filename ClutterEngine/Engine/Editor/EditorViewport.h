#pragma once
#include <Core/CCommon.h>
#include <Graphics/FrameBuffer/FrameBuffer.h>

namespace clt
{
	class ImGuiLayer;
	class EditorApplication;
	class CLUTTER_API EditorViewport
	{
		FrameBuffer* mSceneFramebuffer;
		ImGuiLayer* mOwner;
		EditorApplication* mApp;

		GLuint moveIconID;
		GLuint moveIconActiveID;
		GLuint rotateIconID;
		GLuint rotateIconActiveID;
		GLuint scaleIconID;
		GLuint scaleIconActiveID;

		void DrawGizmoCamera();

	public:

		EditorViewport(ImGuiLayer* owner, FrameBuffer* sceneFramebuffer);

		void Draw();
	};
}