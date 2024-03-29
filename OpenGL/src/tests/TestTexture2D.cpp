#include "TestTexture2D.h"

#include "VertexBufferLayout.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
namespace test {

	TestTexture2D::TestTexture2D()
	{
		m_VertexArray = std::make_unique<VertexArray>();

		float positions[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, //0
			 0.5f, -0.5f, 1.0f, 0.0f,//1
			 0.5f,  0.5f, 1.0f, 1.0f,//2
			-0.5f,  0.5f, 0.0f, 1.0f//3
		};

		m_VertexArray->Bind();
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);
		m_IndexBuffer->Bind();

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");

	}
	TestTexture2D::~TestTexture2D()
	{
	}
	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}
	void TestTexture2D::OnRender()
	{
		Renderer renderer;
		m_Shader->Bind();
		Texture texture("res/textures/face.jpg");
		texture.Bind();
		glClearColor(0.5f, 0.4f, 0.8f, 1.0f);
		renderer.Clear();

		{
			m_Shader->SetUniform1i("u_Texture", 0);
			renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat2("Translation A", &translationA.x, -0.5f, 0.5f);
		ImGui::SliderFloat2("Translation B", &translationB.x, -0.5f, 0.5f);
		ImGui::ColorEdit4("ColorA", &m_ColorA.x);
		ImGui::Text("Fps = %0.1f", ImGui::GetIO().Framerate);
	}
}


