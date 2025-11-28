#pragma once
#include <Core/CCommon.h>

namespace clt
{
	namespace editor
	{
		class CLUTTER_API IEditorPanel
		{
		public:
			virtual ~IEditorPanel() = default;

			virtual const char* GetName() const = 0;
			virtual enum ImGuiWindowFlags GetWindowFlags() const = 0;

			virtual void Draw() = 0;

			virtual void OnAttach() = 0;
			virtual void OnDetach() = 0;
		};
	}
}