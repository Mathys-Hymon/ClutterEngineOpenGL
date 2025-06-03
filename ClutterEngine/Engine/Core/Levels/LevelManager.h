#pragma once
#include <Core/CCommon.h>
#include<Core/Levels/Level.h>
#include<Graphics/RendererGL.h>

namespace clt
{
	/**
  * @class LevelManager
  * @brief Manages the levels within the game engine.
  *
  * This class is responsible for handling the loading, updating, and management
  * of different game levels. It maintains a collection of levels and manages
  * the currently active level.
  */
	class CLUTTER_API LevelManager
	{
		/**
   * @brief Map of level names to level pointers.
   */
		std::unordered_map<std::string, Level*> mLevels;
		
		/**
   * @brief Pointer to the currently active level.
   */
		Level* mActualLevel;

		/**
   * @brief Pointer to the level that is to be loaded.
   */
		Level* mLevelToLoad;

	public:
		/**
   * @brief Constructs a LevelManager with a list of levels.
   * @param pLevels Vector of pointers to levels to be managed.
   * @param pRenderer Pointer to the renderer used by the levels.
   * @param pPhysics Pointer to the physics engine used by the levels.
   */
		LevelManager(std::vector<Level*>& pLevels, RendererGL* pRenderer, Physics* pPhysics);

		/**
   * @brief Destructor for LevelManager.
   */
		~LevelManager();

		/**
   * @brief Updates the current level.
   *
   * This function should be called every frame to update the active level's state.
   */
		void Update();

		/**
   * @brief Loads a level by its name.
   * @param levelName The name of the level to load.
   *
   * This function sets the specified level as the next level to be loaded.
   */
		void LoadLevel(const std::string& levelName);
	};
}
