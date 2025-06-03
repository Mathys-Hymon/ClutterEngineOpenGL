#pragma once
#include <Core/CCommon.h>
#include "Core/Maths/Color.h"

namespace clt
{
	/**
  * @brief Enum representing the type of renderer.
  */
	enum class RendererType
	{
		OPENGL ///< OpenGL renderer type
	};

	class CEngine;

	/**
  * @brief Interface for all renderer implementations.
  */
	class CLUTTER_API IRenderer
	{
	protected:
		/**
   * @brief Indicates if wireframe mode is enabled.
   */
		bool mWireframe;

		/**
   * @brief The background color used by the renderer.
   */
		Color mBackgroundColor;

	public:

		/**
   * @brief Virtual destructor for IRenderer.
   */
		~IRenderer() = default;

		/**
   * @brief Initializes the renderer with the engine and background color.
   * @param pEngine Pointer to the engine instance.
   * @param backgroundColor The background color to use.
   */
		virtual void Initialize(CEngine* pEngine, Color backgroundColor) = 0;

		/**
   * @brief Enables or disables wireframe rendering mode.
   * @param wireframe True to enable wireframe mode, false to disable.
   */
		virtual void WireframeMode(bool wireframe) = 0;

		/**
   * @brief Toggles the wireframe rendering mode.
   */
		virtual void ToggleWireframe() = 0;

		/**
   * @brief Begins the drawing process.
   */
		virtual void BeginDraw() = 0;

		/**
   * @brief Executes the drawing commands.
   */
		virtual void Draw() = 0;

		/**
   * @brief Ends the drawing process.
   */
		virtual void EndDraw() = 0;

		/**
   * @brief Closes and cleans up the renderer.
   */
		virtual void Close() = 0;

		/**
   * @brief Gets the type of the renderer.
   * @return The renderer type.
   */
		const virtual RendererType GetType() const = 0;

		/**
   * @brief Gets the engine associated with the renderer.
   * @return Pointer to the engine instance.
   */
		const virtual CEngine* GetEngine() const = 0;
	};
}
