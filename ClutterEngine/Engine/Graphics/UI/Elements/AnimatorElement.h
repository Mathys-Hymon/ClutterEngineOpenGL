#pragma once
#include <Graphics/UI/Elements/FlipbookElement.h>

namespace clt
{
	class CLUTTER_API AnimatorElement : public FlipbookElement
	{
		std::unordered_map<std::string, FlipbookElement*> mAnims;

	public:
		AnimatorElement(std::string pAnimName, const std::vector<Texture*>& pTextures, bool pLooping = true, float pAnimFps = 24, Vector2 pSize = { 1.0f, 1.0f }, Vector2 pPosition = { 0.0f, 0.0f }, int zOrder = 100);
		AnimatorElement() = delete;
		AnimatorElement(const FlipbookElement&) = delete;
		AnimatorElement& operator = (const FlipbookElement&) = delete;

		virtual ~AnimatorElement();

		void AddNewAnim(std::string pAnimName, const std::vector<Texture*>& pTextures, bool pLooping = true, float pAnimFps = 24, int pDrawOrder = 100);

		void PlayAnim(std::string pAnimName);
		void RemoveAnim(std::string pAnimName);

		FlipbookElement* GetAnim(std::string pAnimName) { return mAnims[pAnimName]; };
	};
}