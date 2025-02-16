#pragma once
#include <Core/Levels/Level.h>

namespace clt
{
	class CLUTTER_API TemplateLevel : public Level
	{
	public:
		TemplateLevel() = default;
		~TemplateLevel() = default;

		void Load() override {};
		void Update() override {};
		void Close() override {};
	};

}