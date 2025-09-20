#pragma once
#include <Bullet/bullet/btBulletDynamicsCommon.h>
#include <Core/Debug/DebugDraw.h>

namespace clt
{
	class CLUTTER_API BulletDebugDraw : btIDebugDraw
	{
		DebugDraw* mDebug;
		int mDebugMode;

	public:

        explicit BulletDebugDraw(DebugDraw* debugDraw);

        void setDebugMode(int debugMode) override;
        int getDebugMode() const override;

        void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
        void drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB,
            btScalar distance, int lifeTime, const btVector3& color) override;
        void reportErrorWarning(const char* warningString) override;
        void draw3dText(const btVector3& location, const char* textString) override;
        void flushLines() override;
	};
}