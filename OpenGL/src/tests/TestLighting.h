#pragma once
#include "Test.h"

#include <memory>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "Camera.h"
#include "Model.h"

namespace test {

	class TestLighting : public Test {
	public:
		TestLighting();
		~TestLighting();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:

		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Shader> m_ObjectShader;
		std::unique_ptr<Shader> m_DiffShader;

		std::unique_ptr<Texture> m_objectDiffuse;
		std::unique_ptr<Texture> m_objectSpecular;

		std::unique_ptr<Camera> m_Camera;

		glm::vec3 translationA;
		glm::vec3 translationB;

		float lightAmbient = 1.0f;
		float lightDiffuse = 1.0f;
		float lightSpecular = 1.0f;

		glm::vec4 m_LightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 m_ObjectColor = glm::vec4(1.0f, 0.5f, 0.31f, 1.0f);

		glm::mat4 m_Proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.01f, 100.0f);
		glm::mat4 m_View;
		glm::mat4 m_Model;
		glm::mat4 m_ObjectModel;

		Camera camera;

		std::unique_ptr<obj::Model> u_Model;
	};
}