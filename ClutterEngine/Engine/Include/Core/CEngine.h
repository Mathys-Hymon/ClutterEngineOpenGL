#pragma once
#include <Core/CCommon.h>
#include <Window/Window.h>
#include <Core/Levels/LevelManager.h>
#include <Graphics/Renderer.h>

#include <memory>

namespace clt
{
	/**
  * @class CEngine
  * @brief The main engine class responsible for initializing and managing the game engine components.
  */
	class CLUTTER_API CEngine
	{
		std::unique_ptr<Window> mWindow; ///< The window instance.
		std::unique_ptr<Renderer> mRenderer; ///< The renderer instance.
		std::unique_ptr<LevelManager> mLevelManager; ///< The level manager instance.
	public:
	/**
   * @brief Default constructor.
   */
		CEngine() = default;

		/**
   * @brief Default destructor.
   */
		~CEngine() = default;

		/**
   * @brief Initializes the engine with the specified parameters.
   * @param pWidth The width of the window.
   * @param pHeight The height of the window.
   * @param pName The name of the window.
   * @param pLevels The levels to be managed by the level manager.
   */
		void Init(int pWidth, int pHeight, std::string pName, std::vector<Level*> pLevels);

		/**
   * @brief Updates the engine state.
   */
		void Update();

		/**
   * @brief Gets the window instance.
   * @return A pointer to the window instance.
   */
		Window* GetWindow() const { return mWindow.get(); }

		/**
   * @brief Gets the renderer instance.
   * @return A pointer to the renderer instance.
   */
		Renderer* GetRenderer() const { return mRenderer.get(); }

		/**
   * @brief Gets the level manager instance.
   * @return A pointer to the level manager instance.
   */
		LevelManager* GetLevelManager() const { return mLevelManager.get(); }
	};
}
