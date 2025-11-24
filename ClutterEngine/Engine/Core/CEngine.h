#pragma once
#include <Core/CCommon.h>
#include <Core/Levels/LevelManager.h>
#include <Physics/IPhysics.h>
#include <Graphics/RendererGL.h>
#include <Window/Window.h>

#include <memory>

namespace clt
{
	/**
  * @class CEngine
  * @brief The main engine class responsible for initializing and managing the game engine components.
  */
	class CLUTTER_API CEngine
	{
		std::unique_ptr<IRenderer> mRenderer; ///< The renderer instance.

		std::unique_ptr<LevelManager> mLevelManager; ///< The level manager instance.
		std::unique_ptr<IPhysics> mPhysics;

		std::string mName;
		float mRefreshFrameRate;

	public:
	/**
   * @brief Default constructor.
   */
		CEngine();

		/**
   * @brief Default destructor.
   */
		~CEngine() = default;

		/**
   * @brief Initializes the engine with the specified parameters.
   * @param pLevels The levels to be managed by the level manager.
   */
		void Init(const std::string& path, std::vector<Level*> pLevels);

		/**
   * @brief Updates the engine state.
   */
		void Update();

		void Close();

		/**
   * @brief Gets the renderer instance.
   * @return A pointer to the renderer instance.
   */
		IRenderer* GetRenderer() const { return mRenderer.get(); }

		bool IsEditorMode() const
		{
			#ifdef EDITOR
				return true;
			#else
				return false;
			#endif
		}
		/**
   * @brief Gets the level manager instance.
   * @return A pointer to the level manager instance.
   */
		LevelManager* GetLevelManager() const { return mLevelManager.get(); }
		IPhysics* GetPhysics() const { return mPhysics.get(); };
	};
}
