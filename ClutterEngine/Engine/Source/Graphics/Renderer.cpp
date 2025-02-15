#include "pch.h"
#include <GLFW/glfw3.h>
#include<Graphics/Renderer.h>

using namespace clt;

Renderer::Renderer()
{
}

bool Renderer::Initialize(Window& pWindow)
{
    return false;
}

void Renderer::AddGraphicComponent(GraphicComponent* pComp)
{
}

void Renderer::RemoveGraphicComponent(GraphicComponent* pComp)
{
}

void Renderer::BeginDraw()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);		 // Define the background Color
	glClear(GL_COLOR_BUFFER_BIT);				 // Clear the background color and depth
	glDepthFunc(GL_LESS);
}

void Renderer::Draw()
{
}

void Renderer::EndDraw()
{
}