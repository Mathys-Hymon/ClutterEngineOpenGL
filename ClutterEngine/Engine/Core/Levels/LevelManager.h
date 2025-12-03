#pragma once
#include <Core/CCommon.h>
#include<Core/Levels/Level.h>

namespace clt
{
	/**
  * @class CLevelManager
  * @brief Manages the levels within the game engine.
  */
	class CLUTTER_API LevelManager
	{
		/// Map of level names to level pointers.
		std::unordered_map<std::string, std::string> mLevelsPath;
		
		/// Pointer to the currently active level.
		Level* mCurrentLevel;
		Level* mLevelToLoad;

	public:
		/**
   * @brief Constructs a CLevelManager with a list of levels.
   * @param pLevelsPath Vector of pointers to levels to be managed.
   */
		LevelManager(std::vector<const std::string&> pLevelsPath, std::vector<Level*>& pLevels, IRenderer* pRenderer, IPhysics* pPhysics);

		/**
	* @brief Destructor for CLevelManager.
	*/
		~LevelManager();

		/**
   * @brief Updates the current level.
   */
		void Update();
		
		void SaveLevel(const std::string& filePath);
		bool LoadLevel(const std::string& filePath);

		Level* GetCurrentLevel() const { return mCurrentLevel; };
		std::string GetCurrentLevelName() const { return mCurrentLevel->mTitle; };
	};
}