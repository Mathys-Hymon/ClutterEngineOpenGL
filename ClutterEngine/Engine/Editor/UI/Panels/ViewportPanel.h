#pragma once
#include <Core/CCommon.h>
#include <Editor/UI/IEditorPanel.h>
#include <Editor/Gizmo.h>

namespace clt
{
	namespace editor
	{
		class CLUTTER_API ViewportPanel : public IEditorPanel
		{
			EditorContext* ctx;
			
			Gizmo* mActorGizmo{nullptr};

			GLuint moveIconID;
			GLuint moveIconActiveID;
			GLuint rotateIconID;
			GLuint rotateIconActiveID;
			GLuint scaleIconID;
			GLuint scaleIconActiveID;

		public:
			ViewportPanel(EditorContext* context);
			const char* GetName() const override;
			void Draw() override;
		};
	}
}