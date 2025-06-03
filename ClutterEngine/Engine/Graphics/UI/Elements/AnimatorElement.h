#pragma once
#include <Graphics/UI/Elements/FlipbookElement.h>

namespace clt
{
	/**
  * @brief UI element that manages and plays multiple flipbook animations.
  * 
  * AnimatorElement allows switching between named flipbook animations at runtime.
  */
	class CLUTTER_API AnimatorElement : public FlipbookElement
	{
		/**
   * @brief Map of animation names to their corresponding FlipbookElement pointers.
   */
		std::unordered_map<std::string, FlipbookElement*> mAnims;

	public:
		/**
   * @brief Constructs an AnimatorElement with an initial animation.
   * @param pAnimName Name of the initial animation.
   * @param pTextures Textures for the initial animation.
   * @param pLooping Whether the animation should loop.
   * @param pAnimFps Frames per second for the animation.
   * @param pSize Size of the element.
   * @param pPosition Position of the element.
   * @param zOrder Z-order for rendering.
   */
		AnimatorElement(std::string pAnimName, const std::vector<Texture*>& pTextures, bool pLooping = true, float pAnimFps = 24, Vector2 pSize = { 1.0f, 1.0f }, Vector2 pPosition = { 0.0f, 0.0f }, int zOrder = 0);

		/**
   * @brief Deleted default constructor.
   */
		AnimatorElement() = delete;

		/**
   * @brief Deleted copy constructor.
   */
		AnimatorElement(const FlipbookElement&) = delete;

		/**
   * @brief Deleted copy assignment operator.
   */
		AnimatorElement& operator = (const FlipbookElement&) = delete;

		/**
   * @brief Destructor.
   */
		virtual ~AnimatorElement();

		/**
   * @brief Adds a new animation to the animator.
   * @param pAnimName Name of the animation.
   * @param pTextures Textures for the animation.
   * @param pLooping Whether the animation should loop.
   * @param pAnimFps Frames per second for the animation.
   * @param pDrawOrder Draw order for the animation.
   */
		void AddNewAnim(std::string pAnimName, const std::vector<Texture*>& pTextures, bool pLooping = true, float pAnimFps = 24, int pDrawOrder = 100);

		/**
   * @brief Plays the animation with the given name.
   * @param pAnimName Name of the animation to play.
   */
		void PlayAnim(std::string pAnimName);

		/**
   * @brief Removes the animation with the given name.
   * @param pAnimName Name of the animation to remove.
   */
		void RemoveAnim(std::string pAnimName);

		/**
   * @brief Gets the FlipbookElement for the given animation name.
   * @param pAnimName Name of the animation.
   * @return Pointer to the FlipbookElement, or nullptr if not found.
   */
		FlipbookElement* GetAnim(std::string pAnimName) { return mAnims[pAnimName]; };
	};
}
