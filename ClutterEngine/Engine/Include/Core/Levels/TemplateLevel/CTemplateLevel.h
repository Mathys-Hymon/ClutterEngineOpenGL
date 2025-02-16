#pragma once
#include <Core/Levels/CLevel.h>

namespace clt
{
	class CLUTTER_API CTemplateLevel : public CLevel
	{
	public:
		CTemplateLevel() = default;
		~CTemplateLevel() = default;

		void Load() override {};
		void Update() override {};
		void Close() override {};
	};

}