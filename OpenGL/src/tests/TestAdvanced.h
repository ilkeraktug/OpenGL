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
	class TestAdvanced : public Test {
	public:

		TestAdvanced();
		~TestAdvanced();

		void OnRender() override;
		void OnUpdate(float deltaTime) override;
		void OnImGuiRender() override;

	private:
		size_t ubo, ubo2, ubo3;

		std::unique_ptr<VertexArray> m_CubeVAO;
		std::unique_ptr<VertexArray> m_PlaneVAO;
		std::unique_ptr<VertexArray> m_SkyboxVAO;
		std::unique_ptr<VertexArray> m_QuadVAO;

		std::unique_ptr<VertexBuffer> m_CubeVBO;
		std::unique_ptr<VertexBuffer> m_PlaneVBO;
		std::unique_ptr<VertexBuffer> m_SkyboxVBO;
		std::unique_ptr<VertexBuffer> m_QuadVBO;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Shader> m_DiffShader;
		std::unique_ptr<Shader> m_BasicShader;
		std::unique_ptr<Shader> m_SkyboxShader;
		std::unique_ptr<Shader> m_QuadShader;
		std::unique_ptr<Shader> m_NormalShader;
		std::unique_ptr<Shader> m_LightShader;
		std::unique_ptr<Shader> m_PointLightShader;

		std::unique_ptr<Texture> m_MarbleTexture;
		std::unique_ptr<Texture> m_MetalTexture;
		std::unique_ptr<CubeMap> m_SkyboxTexture;
		std::unique_ptr<CubeMap> m_PointLightTexture;

		std::unique_ptr<FrameBuffer> m_FrameBuffer;

		std::unordered_map<std::string, Texture*> m_Textures;

		obj::Model* loadModel;

		glm::mat4 m_Model;
		glm::mat4 m_View;
		glm::mat4 m_Proj/* = glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.1f, 100.0f)*/;

		glm::vec3 translationA = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 translationB = glm::vec3(1.0f, 1.0f, -10.0f);
		glm::vec3 translationC;

		glm::vec3 CubeTranslationA = glm::vec3(4.0f, -3.5f, -27.0);
		glm::vec3 CubeTranslationB = glm::vec3(2.0f, -3.5f, -24.0);
		glm::vec3 CubeTranslationC = glm::vec3(7.0f, -1.0f, -22.0);

		glm::vec3 PlaneTranslationA = glm::vec3(-1.0f, -4.0f, -27.0f);

		Camera camera;

		float colorPickerA[4];
		float colorPickerB[4];
		float time;

		bool blinn = false;
		glm::vec2 translations[100];

		int m_ShadowWidth = 1000;
		int m_ShadowHeight = 1000;

		unsigned int depthMapFBO, pointDepthMapFBO;
		unsigned int shadowTex, pointShadowTex;

		glm::vec3 m_LightPosition = glm::vec3(-12.0f, -1.0f, -40.0f);
		glm::mat4 m_LightView;
		glm::mat4 m_LightProj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);

		glm::mat4 m_ShadowProjection = glm::perspective(glm::radians(90.0f), (float)m_ShadowWidth / (float)m_ShadowHeight, 1.0f, 25.0f);
	};
}