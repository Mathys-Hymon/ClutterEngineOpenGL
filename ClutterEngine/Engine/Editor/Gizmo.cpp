#include "pch.h"
#include "Gizmo.h"
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>

#ifdef EDITOR
#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "ImGuizmo.h"
#endif

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace clt;

void Gizmo::Draw(const Vector2& startViewport, const Vector2& endViewport)
{
#ifdef EDITOR

	auto cam = CameraComponent::GetActiveCamera();

	ImGuizmo::SetOrthographic(cam->GetProjectionMode() == ProjectionMode::Orthographic);
	ImGuizmo::SetDrawlist();

	float windowWidth = (float)ImGui::GetWindowWidth();
	float windowHeight = (float)ImGui::GetWindowHeight();

	ImGuiIO& io = ImGui::GetIO();

	float rectX = startViewport.x;
	float rectY = startViewport.y;
	float rectW = endViewport.x - startViewport.x;
	float rectH = endViewport.y - startViewport.y;

	ImGuizmo::SetRect(rectX, rectY, rectW, rectH);

	glm::mat4 model = glm::transpose(mTransform.GetMat4Transform().ToGLM());

	ImGuizmo::OPERATION op;

	switch (mMode)
	{
	case GizmoMode::Translate:
		op = ImGuizmo::TRANSLATE;
		break;
	case GizmoMode::Rotate:
		op = ImGuizmo::ROTATE;
		break;
	case GizmoMode::Scale:
		op = ImGuizmo::SCALE;
		break;
	default:
		op = ImGuizmo::TRANSLATE;
		break;
	}

	glm::mat4 glmView = glm::transpose(cam->GetViewMatrix().ToGLM());
	glm::mat4 glmProj = glm::transpose(cam->GetProjectionMatrix().ToGLM());

	ImGuizmo::Manipulate(glm::value_ptr(glmView), glm::value_ptr(glmProj), op, ImGuizmo::LOCAL, glm::value_ptr(model));

	if (ImGuizmo::IsUsing())
	{
		glm::vec3 translation, Euler, scale;

		ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(model),
			glm::value_ptr(translation),
			glm::value_ptr(Euler),
			glm::value_ptr(scale));

		glm::quat rotation = glm::quat(glm::radians(Euler));

		mTransform.SetLocation(Vector3(translation.x, translation.y, translation.z));
		mTransform.SetRotation(rotation);
		mTransform.SetScale(Vector3(scale.x, scale.y, scale.z));
	}

#endif
}