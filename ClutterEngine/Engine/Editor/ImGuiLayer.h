#pragma once
#include <Core/CCommon.h>
#include <Graphics/FrameBuffer/FrameBuffer.h>

namespace clt
{
	class CLUTTER_API ImGuiLayer
	{
		FrameBuffer* mSceneFramebuffer;
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void BeginFrame();
		void EndFrame();
		void DrawUI();
	};
}