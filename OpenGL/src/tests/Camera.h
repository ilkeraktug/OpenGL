#pragma once
#include "imgui.h"

#include "glm\gtc\matrix_transform.hpp"

namespace test {

	class Camera {
	public:
		Camera();
		Camera(glm::mat4* proj, glm::mat4* view, float width, float height);
		~Camera();

		void OnUpdate();
		void OnRender();
		void OnImGuiRender();

		glm::vec3 GetCameraPosition() { return m_CameraPosition; }
		glm::vec3 GetCameraFront() { return m_CameraFront; }
	private:

		float m_FOV = 45.0f;

		glm::mat4* m_Proj;
		glm::mat4* m_View;

		float m_ScreenWidth;
		float m_ScreenHeight;
		float m_AspectRatio;

		mutable glm::vec3 m_CameraPosition;
		glm::vec3 m_CameraTarget;
		glm::vec3 m_CameraFront;
		glm::vec3 m_CameraUp;
		glm::vec3 m_CameraRight;

		const glm::vec3 m_WorldUp = glm::vec3(0.0f, 0.1f, 0.0f);

		mutable ImVec4 m_CameraMovement = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		glm::vec3 m_Direction;
		glm::vec3 m_CameraAngles = glm::vec3(0.0f, -90.0f, 0.0f);
	private:
		void Calculate();
		void LookAt();
		void Move() const;
		void Rotate();
		void Reset();

		void CalculateDeltaTime();
	};
}