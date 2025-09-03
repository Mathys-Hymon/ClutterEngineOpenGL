#include <glad/glad.h>            // glad EN PREMIER
#include <GLFW/glfw3.h>           // ensuite glfw
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>

#include <Application/EditorApplication.h>


const unsigned int width = 800;
const unsigned int height = 800;

int main()
{
    EditorApplication editor(500, 300);
	return 0;
}