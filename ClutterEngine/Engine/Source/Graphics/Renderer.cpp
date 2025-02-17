#include "pch.h"
#include <glad/glad.h>
#include<Graphics/Renderer.h>
#include<Core/ActorComponent/Actor.h>
#include<Core/ActorComponent/Components/Graphics/SpriteComponent.h>

using namespace clt;

Renderer::Renderer()
{
	gladLoadGL();
	Assets::Get().SetRenderer(this);
	CLUTTER_LOG("GLAD initialised successfully");
}

Renderer::~Renderer()
{
	Assets::Get().ClearTextures();
}

void Renderer::RegisterTextureUsage(Texture* pTexture)
{
	mBindedTextures.insert(pTexture);
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

	for (Texture* tex : mBindedTextures)
	{
		tex->Bind();
	}
}

void Renderer::Draw()
{
	for (GraphicComponent* comp : mComponents)
	{
		comp->Draw(*this);
	}
}

void Renderer::DrawSprite(const Actor& pActor, const Texture& pTexture, CRectangle pRect, Vector2 pOrigin) const
{
}

void Renderer::EndDraw()
{
	for (Texture* tex : mBindedTextures)
	{
		tex->UnBind();
	}
}