#pragma once
#include <Core/CCommon.h>
#include <vector>
#include <Core/ActorComponent/Components/Graphics/SpriteComponent.h>

namespace clt
{
	class CLUTTER_API FlipbookComponent : public SpriteComponent
	{
		std::vector<Texture*> mFlipbookTextures;
		float mCurrentFrame;
		float mAnimFps;

	public:
		FlipbookComponent(const std::vector<Texture*>& pTexture, int pDrawOrder = 100);
		FlipbookComponent() = delete;
		FlipbookComponent(const FlipbookComponent&) = delete;
		FlipbookComponent& operator = (const FlipbookComponent&) = delete;

		virtual ~FlipbookComponent();

		float GetFlipbookFps() const { return mAnimFps; }
		void SetFlipbookTextures(const std::vector<Texture*> pTextures);
		void SetFlipbookFps(float pFps);

		void Update() override;
	};
}
