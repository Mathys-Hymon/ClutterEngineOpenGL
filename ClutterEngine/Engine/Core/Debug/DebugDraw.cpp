#include "pch.h"
#include <Core/Debug/DebugDraw.h>

using namespace clt;

void DebugDraw::Draw(const Matrix4Row& viewProj)
{
}

void DebugDraw::Close()
{
}

void DebugDraw::DrawLine(const Vector3& start, const Vector3& end, const Color& color, float lineThickness, bool persistant)
{
}

void DebugDraw::DrawBox(const Vector3& center, const Vector3& extents, const Color& color, float lineThickness, const Quaternion& rotation, bool persistant)
{
}

void DebugDraw::DrawSphere(const Vector3& center, float radius, const Color& color, float lineThickness, bool persistant)
{
}

void DebugDraw::FlushPersistantDraw()
{
}

void DebugDraw::FlushPersistantLines()
{
}

void DebugDraw::FlushPersistantBoxes()
{
}

void DebugDraw::FlushPersistantSpheres()
{
}
