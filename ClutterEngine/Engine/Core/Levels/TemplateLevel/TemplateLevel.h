#pragma once
#include <Core/Levels/Level.h>

namespace clt
{
	/**
  * @class TemplateLevel
  * @brief Example implementation of a Level in the Clutter Engine.
  *
  * This class serves as a template for creating new levels.
  * It inherits from the Level base class and provides
  * default implementations for the required methods.
  */
	class CLUTTER_API TemplateLevel : public Level
	{
	public:
		/**
   * @brief Default constructor.
   */
		TemplateLevel() = default;

		/**
   * @brief Default destructor.
   */
		~TemplateLevel() = default;

		/**
   * @brief Loads the level resources and initializes the level.
   * Override this method to implement custom loading logic.
   */
		void Load() override {};

		/**
   * @brief Updates the level state.
   * Override this method to implement custom update logic.
   */
		void Update() override {};

		/**
   * @brief Cleans up and closes the level.
   * Override this method to implement custom cleanup logic.
   */
		void Close() override {};
	};

}
