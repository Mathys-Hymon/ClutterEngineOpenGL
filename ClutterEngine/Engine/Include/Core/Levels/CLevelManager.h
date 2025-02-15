#pragma once
#include <Core/CCommon.h>
#include<Core/Levels/CLevel.h>
#include <map>

namespace clt
{
	class CLUTTER_API CLevelManager
	{
		std::map<std::string, CLevel*> mLevels;
		CLevel* mActualLevel;

	public:
		CLevelManager(std::vector<CLevel*>& pLevels);
		~CLevelManager();

		void Update();
	};
}