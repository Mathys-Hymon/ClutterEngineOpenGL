#pragma once  
#include <Core/ActorComponent/Component.h>  
#include <Core/Levels/Level.h>  
#include <Graphics/Renderer.h>  
#include <Core/ActorComponent/Actor.h>  

namespace clt  
{  
/**  
* @class GraphicComponent  
* @brief A component responsible for graphical representation of an actor.  
*/  
class CLUTTER_API GraphicComponent : public Component  
{  
protected:  
/**  
 * @brief The order in which the component should be drawn.  
 */  
int mDrawOrder;

public:  
/**  
 * @brief Constructor for GraphicComponent.  
 * @param pOwner Pointer to the owner actor.  
 * @param pDrawOrder The draw order of the component. Default is 0.  
 */  
GraphicComponent(Actor* pOwner, int pDrawOrder = 0) : mDrawOrder(pDrawOrder), Component(pOwner, pDrawOrder)  
{  
	pOwner->GetLevel().GetRenderer().AddGraphicComponent(this);  
};  

/**
 * @brief Destructor for GraphicComponent.
 */
virtual ~GraphicComponent()
{
	mOwner->GetLevel().GetRenderer().RemoveGraphicComponent(this);
};

/**  
 * @brief Draws the component using the provided renderer.  
 * @param pRenderer Reference to the renderer.  
 */  

virtual void Draw(Renderer& pRenderer) = 0;

/**  
 * @brief Gets the draw order of the component.  
 * @return The draw order.  
 */  
int GetDrawOrder() const { return mDrawOrder; };  
};  
}