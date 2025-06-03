#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Transforms/Transform2D.h>
#include <Core/Assets/AssetsType/Texture.h>
#include <Core/Assets/Assets.h>
#include <Graphics/UI/UIPanel.h>

/**
 * @brief Enum representing anchor positions for UI elements.
 */
enum class CLUTTER_API Anchor
{
	Center,         /**< Center anchor */
	Top,            /**< Top anchor */
	Bottom,         /**< Bottom anchor */

	Left,           /**< Left anchor */
	UpLeft,         /**< Upper left anchor */
	BottomLeft,     /**< Bottom left anchor */

	Right,          /**< Right anchor */
	UpRight,        /**< Upper right anchor */
	BottomRight,    /**< Bottom right anchor */
};

namespace clt
{
	/**
  * @brief Base class for UI widget elements.
  */
	class CLUTTER_API WidgetElement
	{
		int mZOrder;                /**< Z-order for rendering priority */
		Vector2 mAnchorOffset;      /**< Offset from the anchor position */
		UIPanel* mOwner;            /**< Pointer to the owning UIPanel */
		Anchor mAnchor;             /**< Current anchor position */

	protected:
		Transform2D mTransform;     /**< 2D transform for position, scale, rotation */

		/**
   * @brief Sets the owner UIPanel of this widget.
   * @param pOwner Pointer to the UIPanel owner.
   */
		void SetOwner(UIPanel* pOwner) { mOwner = pOwner; };

		friend UIPanel;

	public:

		bool mVisibility;           /**< Visibility flag */

		/**
   * @brief Constructs a WidgetElement with given size, position, and Z-order.
   * @param size Size of the widget (default: {1,1}).
   * @param position Position of the widget (default: {0,0}).
   * @param ZOrder Z-order for rendering (default: 0).
   */
		WidgetElement(Vector2 size = { 1,1 }, Vector2 position = { 0, 0 }, int ZOrder = 0) : mZOrder(ZOrder), mVisibility(true), mOwner(nullptr), mAnchor(Anchor::Center), mAnchorOffset(Vector2::Zero)
		{
			mTransform.scale.x =  size.x;
			mTransform.scale.y = -size.y;
			mTransform.location = position;
		};

		/**
   * @brief Default destructor.
   */
		~WidgetElement() = default;

		/**
   * @brief Updates the widget element. Override in derived classes.
   */
		virtual void Update() {};

		/**
   * @brief Draws the widget element. Must be implemented by derived classes.
   * @param renderer Pointer to the renderer.
   */
		virtual void Draw(RendererGL* renderer) = 0;

		/**
   * @brief Gets the Z-order of the widget.
   * @return The Z-order value.
   */
		int GetZOrder() const { return mZOrder; };

		/**
   * @brief Sets the Z-order and notifies the owner if changed.
   * @param ZOrder New Z-order value.
   */
		void SetZOrder(int ZOrder)
		{
			if (ZOrder != mZOrder)
			{
				mZOrder = ZOrder;
				mOwner->UpdateWidgetOrder(this);
			}
		}

		/**
   * @brief Gets the size of the widget.
   * @return The size as a Vector2.
   */
		virtual Vector2 GetSize()  const 
		{ 
			return {
     mTransform.scale.x,
				-mTransform.scale.y
					};
		};

		/**
   * @brief Gets the position of the widget.
   * @return The position as a Vector2.
   */
		Vector2 GetPosition() const { return mTransform.location; };

		/**
   * @brief Gets the rotation of the widget.
   * @return The rotation in degrees.
   */
		float GetRotation()   const { return mTransform.rotation; };

		/**
   * @brief Gets the transform of the widget.
   * @return The Transform2D object.
   */
		virtual Transform2D GetTransform() const 
		{
			return mTransform;
		};

		/**
   * @brief Sets the size of the widget.
   * @param size The new size as a Vector2.
   */
		void SetSize(Vector2 size) 
		{ 
			mTransform.scale.x =  size.x;
			mTransform.scale.y = -size.y;
		};

		/**
   * @brief Sets the size of the widget (uniform scale).
   * @param size The new size as a float.
   */
		void SetSize(float size)
		{
			mTransform.scale.x = size;
			mTransform.scale.y = -size;
		};

		/**
   * @brief Sets the anchor position of the widget.
   * @param anchor The new anchor.
   */
		void SetAnchor(Anchor anchor)
		{

		}

		/**
   * @brief Sets the position of the widget.
   * @param position The new position as a Vector2.
   */
		void SetPosition(Vector2 position) { mTransform.location = position; };

		/**
   * @brief Sets the rotation of the widget.
   * @param rotation The new rotation in degrees.
   */
		void SetRotation(float rotation)   { mTransform.rotation = rotation; };

		/**
   * @brief Toggles the visibility of the widget.
   */
		void ToggleVisibility() { mVisibility = !mVisibility; };
	};
}
