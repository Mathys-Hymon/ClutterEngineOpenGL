#pragma once
#include <Core/CCommon.h>
#include<Core/Levels/CLevel.h>
#include <map>

namespace clt
{
	/**
  * @class CLevelManager
  * @brief Manages the levels within the game engine.
  */
	class CLUTTER_API CLevelManager
	{
		/// Map of level names to level pointers.
		std::map<std::string, CLevel*> mLevels;
		
		/// Pointer to the currently active level.
		CLevel* mActualLevel;

	public:
		/**
   * @brief Constructs a CLevelManager with a list of levels.
   * @param pLevels Vector of pointers to levels to be managed.
   */
		CLevelManager(std::vector<CLevel*>& pLevels);

		/**
   * @brief Destructor for CLevelManager.
   */
		~CLevelManager();

		/**
   * @brief Updates the current level.
   */
		void Update();
	};
}