#pragma once
#include <Core/CCommon.h>
#include "Core/Maths/Vectors/Vector2.h"

class GLFWwindow;

namespace clt
{

    class CEngine;

    /**
     * @brief Represents a window in the Clutter engine.
     * 
     * Handles window creation, resizing, renaming, and buffer swapping.
     */
    class CLUTTER_API Window 
    {
        /**
         * @brief Default constructor. Private to enforce singleton pattern.
         */
        Window() = default;

        /**
         * @brief Initializes the window with the specified parameters.
         * @param width The width of the window.
         * @param height The height of the window.
         * @param name The title of the window.
         * @param vsync Whether to enable vertical synchronization.
         */
        void InternalInit(u32 width, u32 height, const std::string& name, bool vsync);

        GLFWwindow* mGlfwWindow = nullptr; ///< Pointer to the underlying GLFW window.
        Vector2 mDimensions = { 0.f, 0.f }; ///< Current dimensions of the window.
        bool mIsInitialized = false; ///< Indicates if the window has been initialized.

        friend class CEngine;

    public:

        /**
         * @brief Gets the singleton instance of the Window.
         * @return Reference to the Window instance.
         */
        static Window& Get();

        Window(const Window&) = delete;
        void operator=(const Window&) = delete;

        /**
         * @brief Destructor. Cleans up window resources.
         */
        ~Window();

        /**
         * @brief Gets the current dimensions of the window.
         * @return The window dimensions as a Vector2.
         */
        Vector2 GetDimensions() const { return mDimensions; }

        /**
         * @brief Gets the underlying GLFW window pointer.
         * @return Pointer to the GLFWwindow.
         */
        GLFWwindow* GetGLFWWindow() const { return mGlfwWindow; }

        /**
         * @brief Resizes the viewport of the window.
         * @param startWidth The starting width of the viewport.
         * @param startHeight The starting height of the viewport.
         * @param width The new width of the viewport.
         * @param height The new height of the viewport.
         */
        void ResizeViewport(unsigned int startWidth, unsigned int startHeight, unsigned int width, unsigned int height);

        /**
         * @brief Renames the window viewport.
         * @param name The new name for the window.
         */
        void RenameViewport(const char* name);

        /**
         * @brief Checks if the window should close.
         * @return True if the window should close, false otherwise.
         */
        bool ShouldClose() const;

        /**
         * @brief Swaps the front and back buffers of the window.
         */
        void SwapBuffers() const;

        /**
         * @brief Closes the window.
         */
        void Close();
    };
}
