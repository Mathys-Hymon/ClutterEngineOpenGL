#pragma once
#include <Core/ActorComponent/Components/Graphics/FlipbookComponent.h>

namespace clt
{
	class CLUTTER_API AnimatorComponent : public FlipbookComponent
	{
		std::unordered_map<std::string, FlipbookComponent*> mAnims;

	public:
		AnimatorComponent(std::string pAnimName, const std::vector<Texture*>& pTextures, bool pLooping = true, int pDrawOrder = 100);
		AnimatorComponent() = delete;
		AnimatorComponent(const FlipbookComponent&) = delete;
		AnimatorComponent& operator = (const FlipbookComponent&) = delete;

		virtual ~AnimatorComponent() {};

		void AddNewAnim(std::string pAnimName, const std::vector<Texture*>& pTextures, bool pLooping = true, int pDrawOrder = 100);
		void PlayAnim(std::string pAnimName);
		void RemoveAnim(std::string pAnimName);

		FlipbookComponent* GetAnim(std::string pAnimName) { return mAnims[pAnimName]; };
	};
}