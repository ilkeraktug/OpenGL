#pragma once
#include "Test.h"

#include <memory>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

namespace test {
	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		glm::vec3 translationA;
		glm::vec3 translationB;

		ImVec4 m_ColorA = ImVec4(1.0f, 0.5f, 0.31f, 1.0f);

		glm::mat4 m_Proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
		glm::mat4 m_View;
		glm::mat4 m_Model;
	};
}


