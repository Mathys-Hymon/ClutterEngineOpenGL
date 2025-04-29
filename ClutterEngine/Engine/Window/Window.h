#pragma once
#include <Core/CCommon.h>
#include "Core/Maths/Vectors/Vector2.h"

class GLFWwindow;

namespace clt
{
    /**
     * @brief A class representing a window in the Clutter Engine.
     */
    class CLUTTER_API Window {
    public:
        /**
         * @brief Constructs a new Window object.
         * @param pWidth The width of the window.
         * @param pHeight The height of the window.
         * @param pName The name of the window. Default is "Clutter Engine".
         */
        Window(u32 pWidth, u32 pHeight, std::string pName = "Clutter Engine", bool vsync = true);

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        Window(const Window&) = delete;

        /**
         * @brief Destroys the Window object.
         */
        ~Window();

        /**
         * @brief Deleted assignment operator to prevent copying.
         */
        void operator=(const Window&) = delete;

        /**
         * @brief Gets the dimensions of the window.
         * @return A Vector2 representing the dimensions of the window.
         */
        inline Vector2 GetDimensions() const { return mDimensions; };

        /**
         * @brief Gets the GLFW window object.
         * @return A pointer to the GLFWwindow.
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

    private:
        GLFWwindow* mGlfwWindow; ///< The GLFW window object.
        Vector2 mDimensions; ///< The dimensions of the window.
    };
}
