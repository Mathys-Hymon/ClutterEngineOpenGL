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
			virtual void Draw() = 0;
			virtual const char* GetName() const = 0;
		};
	}
}