#include "pch.h"
#include <glad/glad.h>
#include<Graphics/Renderer.h>
#include<Core/ActorComponent/Components/GraphicComponent.h>

using namespace clt;

Renderer::Renderer()
{
	gladLoadGL();

	CLUTTER_LOG("GLAD initialised successfully");
}

void Renderer::AddGraphicComponent(GraphicComponent* pComp)
{
	int compDrawOrder = pComp->GetDrawOrder();
	
	if (!mComponents.empty())
	{
		std::vector<GraphicComponent*>::iterator gc;
		for (gc = mComponents.begin(); gc != mComponents.end(); gc++)
		{
			if (compDrawOrder < (*gc)->GetDrawOrder()) break;
		}
		mComponents.insert(gc, pComp);
	}
	else
	{
		mComponents.emplace_back(pComp);
	}
}

void Renderer::RemoveGraphicComponent(GraphicComponent* pComp)
{
	std::vector<GraphicComponent*>::iterator gc;
	gc = std::find(mComponents.begin(), mComponents.end(), pComp);
	mComponents.erase(gc);
}

void Renderer::BeginDraw()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);		 // Define the background Color
	glClear(GL_COLOR_BUFFER_BIT);				 // Clear the background color and depth
	glDepthFunc(GL_LESS);
}

void Renderer::Draw()
{
	for (GraphicComponent* comp : mComponents)
	{
		comp->Draw(*this);
	}
}

void Renderer::EndDraw()
{
}