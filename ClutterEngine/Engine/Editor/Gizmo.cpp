#include "pch.h"
#include "Gizmo.h"
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "ImGuizmo.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace clt;

void Gizmo::Draw()
{
	auto cam = CameraComponent::GetActiveCamera();

	ImGuizmo::SetOrthographic(cam->GetProjectionMode() == ProjectionMode::Orthographic);
	ImGuizmo::SetDrawlist();

	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

	glm::mat4 model = mTransform.GetMat4Transform().ToGLM();

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

	ImGuizmo::Manipulate(glm::value_ptr(cam->GetViewMatrix().ToGLM()), glm::value_ptr(cam->GetProjectionMatrix().ToGLM()), op, ImGuizmo::LOCAL, glm::value_ptr(model));

	if (ImGuizmo::IsUsing())
	{
		glm::vec3 translation, rotation, scale;

		ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(model),
			glm::value_ptr(translation),
			glm::value_ptr(rotation),
			glm::value_ptr(scale));

		mTransform.SetLocation(Vector3(translation.x, translation.y, translation.z));
		mTransform.SetRotation(Vector3(rotation.x, rotation.y, rotation.z));
		mTransform.SetScale(Vector3(scale.x, scale.y, scale.z));
	}
}