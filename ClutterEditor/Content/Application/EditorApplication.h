#pragma once
#include <Core/CEngine.h>
#include <Application/Application.h>

namespace clt
{
	class CLUTTER_API EditorApplication : public Application {

		virtual void Update() override;
		virtual void Render() override;

	public:

		EditorApplication();
		~EditorApplication() = default;

		void OpenProject(const std::string& path);
	};
}