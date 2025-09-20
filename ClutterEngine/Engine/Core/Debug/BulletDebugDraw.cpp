#include "pch.h"
#include "BulletDebugDraw.h"
#include <Core/CEngine.h>

using namespace clt;

BulletDebugDraw::BulletDebugDraw(CEngine& engine) : mDebug(nullptr), mDebugMode(DBG_DrawWireframe)
{
    mDebug = engine.GetRenderer()->GetDebugDraw();
}

void BulletDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
    if (!mDebug) return;

    Vector3 start(from.x(), from.y(), from.z());
    Vector3 end(to.x(), to.y(), to.z());
    Color col(color.x(), color.y(), color.z(), 1.0f);

    mDebug->DrawLine(start, end, col, 1.0f, false);
}

void BulletDebugDraw::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{    
    if (!mDebug) return;

    Vector3 point(PointOnB.x(), PointOnB.y(), PointOnB.z());
    Vector3 normal(normalOnB.x(), normalOnB.y(), normalOnB.z());

    Vector3 end = point + normal * distance;
    mDebug->DrawLine(point, point - (normal * 0.25f), Color::Red, 5.0f, false);

    mDebug->DrawBox(point, 0.05f, Color::Red, 3.0f);
}    
     
void BulletDebugDraw::reportErrorWarning(const char* warningString)
{    
    CLUTTER_WARNING("[Bullet Warning] %s", warningString);
}    
     
void BulletDebugDraw::draw3dText(const btVector3& location, const char* textString)
{    
}    
     
void BulletDebugDraw::setDebugMode(int debugMode)
{    
    mDebugMode = debugMode;
}    
     
int  BulletDebugDraw::getDebugMode() const
{
    return mDebugMode;
}
