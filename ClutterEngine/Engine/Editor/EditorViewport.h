// #pragma once
// #include <Core/CCommon.h>
// #include <Graphics/FrameBuffer/FrameBuffer.h>
// #include <Editor/Gizmo.h>
// #include <Core/ActorComponent/Actor.h>
//
// namespace clt
// {
// 	class ImGuiLayer;
// 	class EditorApplication;
// 	class CLUTTER_API EditorViewport
// 	{
// 		FrameBuffer* mSceneFramebuffer;
// 		ImGuiLayer* mOwner;
// 		EditorApplication* mApp;
//
// 		Gizmo* mActorGizmo;
//
// 		GLuint moveIconID;
// 		GLuint moveIconActiveID;
// 		GLuint rotateIconID;
// 		GLuint rotateIconActiveID;
// 		GLuint scaleIconID;
// 		GLuint scaleIconActiveID;
//
// 		void DrawGizmoCamera(const Vector2& startViewport,const Vector2& endViewport);
//
// 	public:
//
// 		EditorViewport(ImGuiLayer* owner, FrameBuffer* sceneFramebuffer);
// 		~EditorViewport() = default;
//
// 		void Draw(Actor* focusedActor);
// 	};
// }