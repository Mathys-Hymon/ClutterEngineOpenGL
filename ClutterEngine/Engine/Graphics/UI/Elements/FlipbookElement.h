#pragma once
#include <Graphics/UI/Elements/SpriteElement.h>

namespace clt
{
	/**
  * @brief UI element for displaying animated flipbook sprites.
  * 
  * FlipbookElement manages a sequence of textures to create a frame-by-frame animation.
  * It supports playback controls such as play, pause, looping, and FPS adjustment.
  */
	class CLUTTER_API FlipbookElement : public SpriteElement
	{
		std::vector<Texture*> mFlipbookTextures; ///< List of textures representing animation frames.
		bool mLooping;                          ///< Whether the animation should loop.
		bool mIsPaused;                         ///< Whether the animation is currently paused.
		float mCurrentFrame;                    ///< Current frame index (can be fractional for interpolation).
		float mNextFrame;                       ///< Next frame index.
		float mAnimFps;                         ///< Animation frames per second.

	public:
		/**
   * @brief Deleted default constructor.
   */
		FlipbookElement() = delete;

		/**
   * @brief Constructs a FlipbookElement with the given textures and parameters.
   * @param pTexture Vector of Texture pointers for the flipbook frames.
   * @param pLooping Whether the animation should loop (default: true).
   * @param pAnimFps Animation frames per second (default: 24).
   * @param size Size of the element (default: {1.0f, 1.0f}).
   * @param position Position of the element (default: {0, 0}).
   * @param ZOrder Z-order for rendering (default: 0).
   */
		FlipbookElement(const std::vector<Texture*> pTexture, bool pLooping = true, float pAnimFps = 24, Vector2 size = { 1.0f ,1.0f }, Vector2 position = { 0, 0 }, int ZOrder = 0) 
			: SpriteElement(pTexture[0],size, position, ZOrder), mFlipbookTextures(pTexture), mLooping(pLooping), mIsPaused(false), mAnimFps(pAnimFps), mCurrentFrame(0), mNextFrame(1)
		{};

		/**
   * @brief Gets the flipbook textures.
   * @return Vector of Texture pointers.
   */
		std::vector<Texture*> GetFlipbookTextures() const { return mFlipbookTextures; };

		/**
   * @brief Checks if the animation is set to loop.
   * @return True if looping, false otherwise.
   */
		bool GetLooping() const { return mLooping; };

		/**
   * @brief Sets the flipbook textures.
   * @param pTextures Vector of Texture pointers to set.
   */
		void SetFlipbookTextures(const std::vector<Texture*> pTextures);

		/**
   * @brief Sets the animation frames per second.
   * @param pFps Frames per second.
   */
		void SetFlipbookFps(float pFps) { mAnimFps = pFps; };

		/**
   * @brief Sets whether the animation should loop.
   * @param pLooping True to enable looping, false to disable.
   */
		void SetLooping(bool pLooping) { mLooping = pLooping; };

		/**
   * @brief Gets the animation frames per second.
   * @return Frames per second.
   */
		float GetFlipbookFps() const { return mAnimFps; };

		/**
   * @brief Starts or resumes the animation.
   */
		void Play() { mIsPaused = false; };

		/**
   * @brief Starts the animation from the first frame.
   */
		void PlayFromStart() 
		{
			mCurrentFrame = 0;
			mNextFrame = 1;
			mIsPaused = false;
		}

		/**
   * @brief Pauses the animation.
   */
		void Pause() { mIsPaused = true; };

		/**
   * @brief Toggles the paused state of the animation.
   */
		void Toggle() { mIsPaused = !mIsPaused; };

		/**
   * @brief Updates the animation state. Should be called every frame.
   */
		virtual void Update() override;
	};
}
