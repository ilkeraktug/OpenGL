#pragma once

#include <memory>
#include <utility>

#include <glad\glad.h>
#include "GLFW\glfw3.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "CubeMap.h"
#include "Camera.h"
#include "FrameBuffer.h"

#include "Model.h"


namespace test {

	class TestCubeMap : public Test
	{
	public:
		TestCubeMap();
		virtual ~TestCubeMap();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:

		std::unique_ptr<VertexArray> m_SkyboxVAO;

		std::unique_ptr<VertexBuffer> m_SkyboxVBO;

		std::unique_ptr<Shader> m_SkyboxShader;
		std::unique_ptr<Shader> m_ModelShader;

		std::unique_ptr<CubeMap> m_SkyboxTexture;

		obj::Model* loadModel;

		glm::mat4 m_Model;
		glm::mat4 m_View;
		glm::mat4 m_Proj/* = glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.1f, 100.0f)*/;

		glm::vec3 objPosition = glm::vec3(1.0f, 1.0f, 1.0f);

		Camera camera;

		std::unique_ptr<VertexArray> m_CubeVAO;
		std::unique_ptr<VertexBuffer> m_CubeVBO;
	};
}