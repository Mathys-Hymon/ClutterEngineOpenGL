#pragma once
#include <Core/CCommon.h>

namespace clt
{
	class CLUTTER_API ImGuiLayer
	{

	public:
		ImGuiLayer();
		~ImGuiLayer();

		void BeginFrame();
		void EndFrame();
		void DrawUI();
	};
}