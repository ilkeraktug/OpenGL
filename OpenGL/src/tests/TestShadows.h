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
	class TestShadows : public Test{
	public:
		TestShadows();
		~TestShadows();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_PlaneVAO;
		std::unique_ptr<VertexArray> m_CubeVAO;
		std::unique_ptr<VertexArray> m_QuadVAO;

		std::unique_ptr<VertexBuffer> m_PlaneVBO;
		std::unique_ptr<VertexBuffer> m_CubeVBO;
		std::unique_ptr<VertexBuffer> m_QuadVBO;

		std::unordered_map<std::string, Texture*> m_Textures;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Shader> m_DenemeShader;
		std::unique_ptr<Shader> m_NormalShader;
		std::unique_ptr<Shader> m_HDRShader;
		std::unique_ptr<Shader> m_LightShader;
		std::unique_ptr<Shader> m_FinalShader;
		std::unique_ptr<Shader> m_BlurShader;
		std::unique_ptr<Shader> m_DiffShader;
		std::unique_ptr<Shader> m_DeferredShader;
		std::unique_ptr<Shader> m_ModelShader;
		std::unique_ptr<Shader> m_SceneShader;
		std::unique_ptr<Shader> m_LightCubeShader;

		std::unique_ptr<Shader> m_DeferringShader;
		std::unique_ptr<Shader> m_SSAOShader;
		std::unique_ptr<Shader> m_SSAOBlurShader;
		std::unique_ptr<Shader> m_SSAOFinalShader;

		int m_ScreenWidth = 1280, m_ScreenHeight = 768;

		unsigned int gBuffer, gPosition, gNormal, gAlbedoSpec;

		Camera camera;

		glm::mat4 m_Model;
		glm::mat4 m_View;
		glm::mat4 m_Proj;

		glm::vec3 m_LightPosition = glm::vec3(-2.0f, 4.0f, -1.0f);
		glm::vec3 m_LightColor = glm::vec3(-2.0f, 4.0f, -1.0f);

		glm::vec3 m_Point1 = glm::vec3(-1.0f,  1.0f, 0.0f);
		glm::vec3 m_Point2 = glm::vec3(-1.0f, -1.0f, 0.0f);
		glm::vec3 m_Point3 = glm::vec3( 1.0f, -1.0f, 0.0f);
		glm::vec3 m_Point4 = glm::vec3( 1.0f,  1.0f, 0.0f);

		glm::vec2 m_UV1 = glm::vec2(0.0f, 1.0f);
		glm::vec2 m_UV2 = glm::vec2(0.0f, 0.0f);
		glm::vec2 m_UV3 = glm::vec2(1.0f, 0.0f);
		glm::vec2 m_UV4 = glm::vec2(1.0f, 1.0f);

		glm::vec3 m_Normal = glm::vec3(0.0f, 0.0f, 1.0f);

		glm::vec3 m_Tangent1;
		glm::vec3 m_Tangent2;

		glm::vec3 m_Bitangent1;
		glm::vec3 m_Bitangent2;

		glm::vec3 m_PlaneTranslation = glm::vec3(-1.0f, 0.0f, -5.0f);
		glm::vec3 m_PlaneTranslation2 = glm::vec3(1.0f, 0.0f, -5.0f);

		glm::vec3 m_CubeTranslation = glm::vec3(0.0f, 0.0f, -25.0);

		float m_PlaneRotate;
		float m_PlaneRotate2;

		float m_Exposure = 0.1f;

		obj::Model* loadModel;

		unsigned int hdrFrameBuffer, hdrTexture, hdrRenderBuffer, bloomFBO, bloomRBO;
		unsigned int bloomTexture[2];
		const unsigned int colorAttachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };

		unsigned int pingpongFBO[2];
		unsigned int pingpongColorbuffers[2];

		unsigned int uniformBlock;

		bool m_IsInverse = true;
		bool m_IsHdrON = true;
		float bias = 0.025, radius = 0.5, linear = 0.09, quadratic = 0.032, str = 8.0f;
		unsigned int ssaoFBO, ssaoBlurFBO, ssaoTexture, ssaoBlurTexture, noiseTexture;

		std::vector<glm::vec3> lightPositions;
		std::vector<glm::vec3> lightColors;
		std::vector<glm::vec3> objectPositions;
		std::vector<glm::vec3> ssaoKernel;
		std::vector<glm::vec3> ssaoRotate;


		obj::Model* model;

		glm::vec3 m_Left = glm::vec3(-1.4f, -1.9f, 9.0f);
		glm::vec3 m_Right = glm::vec3(0.0f, -1.8f, 4.0f);
		glm::vec3 m_Down = glm::vec3(0.8f, -1.7f, 6.0f);
	private:
		float lerp(float a, float b, float f)
		{
			return a + f * (b - a);
		}
	};
}