#pragma once
#include <Core/CCommon.h>
#include<Core/Levels/Level.h>
#include<Graphics/RendererGL.h>

namespace clt
{
	/**
  * @class CLevelManager
  * @brief Manages the levels within the game engine.
  */
	class CLUTTER_API LevelManager
	{
		/// Map of level names to level pointers.
		std::unordered_map<std::string, Level*> mLevels;
		
		/// Pointer to the currently active level.
		Level* mActualLevel;

	public:
		/**
   * @brief Constructs a CLevelManager with a list of levels.
   * @param pLevels Vector of pointers to levels to be managed.
   */
		LevelManager(std::vector<Level*>& pLevels, RendererGL* pRenderer, Physics* pPhysics);

		/**
   * @brief Destructor for CLevelManager.
   */
		~LevelManager();

		/**
   * @brief Updates the current level.
   */
		void Update();
	};
}