#include "Camera.h"

#include "imgui.h"

#include <glad\glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace test {

	Camera::Camera()
	{

	}

	Camera::Camera(glm::mat4* proj, glm::mat4* view, float width, float height)
		:m_Proj(proj), m_View(view), m_ScreenWidth(width), m_ScreenHeight(height)
	{
		m_AspectRatio = m_ScreenWidth / m_ScreenHeight;
		*m_Proj = glm::perspective(glm::radians(m_FOV), m_AspectRatio, 0.1f, 100.0f);
		*m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 3.0f));
		
		m_CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
		m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		m_CameraTarget = glm::vec3(0.0f);
		m_CameraUp = m_WorldUp;
	}
	Camera::~Camera()
	{
		
	}
	
	void Camera::OnUpdate()
	{
		Calculate();
		CalculateDeltaTime();
		Move();
	}

	void Camera::OnRender() 
	{
		*m_Proj = glm::perspective(glm::radians(m_FOV), m_AspectRatio, 0.1f, 100.0f);
		*m_View = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_WorldUp);
	}

	void Camera::OnImGuiRender()
	{
		ImGui::Begin("Camera");
		ImGui::SliderFloat3("CameraMovement", &m_CameraMovement.x, -25.0f, 25.0f);
		if (ImGui::Button("Reset"))
			Reset();
		ImGui::SliderFloat3("Camera Angles", &m_CameraAngles.x, -180.0f, 180.0f);
		ImGui::SliderFloat("FOV", &m_FOV, 0.0f, 90.0f);
		ImGui::End();
	}


	void Camera::Calculate()
	{

		m_CameraRight = glm::normalize(glm::cross(m_CameraFront, m_CameraUp));

		m_Direction.x = cos(glm::radians(m_CameraAngles.y)) * cos(glm::radians(m_CameraAngles.x));
		m_Direction.y = sin(glm::radians(m_CameraAngles.x));
		m_Direction.z = sin(glm::radians(m_CameraAngles.y)) * cos(glm::radians(m_CameraAngles.x));

		m_CameraFront = glm::normalize(m_Direction);
	}

	void Camera::Move() const
	{
		m_CameraPosition.x = m_CameraMovement.x;
		m_CameraPosition.y = m_CameraMovement.y;
		m_CameraPosition.z = m_CameraMovement.z;
	}

	void Camera::Rotate()
	{
		//m_CameraPosition.x = sin(glfwGetTime()) * 10.0f;
		//m_CameraPosition.z = cos(glfwGetTime()) * 10.0f;
	}

	void Camera::Reset()
	{
		m_CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
		m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		m_CameraTarget = glm::vec3(0.0f);

		m_CameraMovement = ImVec4();
		m_CameraAngles = glm::vec3(0.0f, -90.0f, 0.0f);
	}
	void Camera::CalculateDeltaTime()
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
}