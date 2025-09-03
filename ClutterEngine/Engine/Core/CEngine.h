#pragma once
#include <Core/CCommon.h>
#include <Window/Window.h>
#include <Core/Levels/LevelManager.h>
#include <Physics/Physics.h>
#include <Graphics/RendererGL.h>
#include <Sound/Sounds.h>

#include <memory>

namespace clt
{
	/**
  * @class CEngine
  * @brief The main engine class responsible for initializing and managing the game engine components.
  */
	class CLUTTER_API CEngine
	{
		std::unique_ptr<RendererGL> mRenderer; ///< The renderer instance.
		std::unique_ptr<Sounds> mSounds;

		std::unique_ptr<LevelManager> mLevelManager; ///< The level manager instance.
		std::unique_ptr<Physics> mPhysics; 

		std::string mName;
		float mRefreshFrameRate;

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
		RendererGL* GetRenderer() const { return mRenderer.get(); }

		bool isEditorMode() const
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
	};
}
