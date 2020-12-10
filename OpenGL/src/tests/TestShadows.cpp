#include "TestShadows.h"

#include "VertexBufferLayout.h"
#include <random>

namespace test {
	TestShadows::TestShadows()
		: camera(&m_Proj, &m_View, m_ScreenWidth, m_ScreenHeight)
	{
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		//triangle 1
		glm::vec3 edge1 = m_Point2 - m_Point1;
		glm::vec3 edge2 = m_Point3 - m_Point1;

		glm::vec2 deltaUV1 = m_UV2 - m_UV1;
		glm::vec2 deltaUV2 = m_UV3 - m_UV1;

		float det = (1.0f) / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		m_Tangent1.x = (det * deltaUV2.y * edge1.x) - (det * deltaUV1.y * edge2.x);
		m_Tangent1.y = (det * deltaUV2.y * edge1.y) - (det * deltaUV1.y * edge2.y);
		m_Tangent1.z = (det * deltaUV2.y * edge1.z) - (det * deltaUV1.y * edge2.z);

		m_Bitangent1.x = -(det * deltaUV2.x * edge1.x) + (det * deltaUV1.x * edge2.x);
		m_Bitangent1.y = -(det * deltaUV2.x * edge1.y) + (det * deltaUV1.x * edge2.y);
		m_Bitangent1.z = -(det * deltaUV2.x * edge1.z) + (det * deltaUV1.x * edge2.z);
		//triangle 2
		edge1 = m_Point3 - m_Point1;
		edge2 = m_Point4 - m_Point1;

		deltaUV1 = m_UV3 - m_UV1;
		deltaUV2 = m_UV4 - m_UV1;

		det = (1.0f) / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		m_Tangent2.x = (det * deltaUV2.y * edge1.x) - (det * deltaUV1.y * edge2.x);
		m_Tangent2.y = (det * deltaUV2.y * edge1.y) - (det * deltaUV1.y * edge2.y);
		m_Tangent2.z = (det * deltaUV2.y * edge1.z) - (det * deltaUV1.y * edge2.z);

		m_Bitangent2.x = -(det * deltaUV2.x * edge1.x) + (det * deltaUV1.x * edge2.x);
		m_Bitangent2.y = -(det * deltaUV2.x * edge1.y) + (det * deltaUV1.x * edge2.y);
		m_Bitangent2.z = -(det * deltaUV2.x * edge1.z) + (det * deltaUV1.x * edge2.z);

		float vertexBuffer[] = {
			m_Point1.x, m_Point1.y, m_Point1.z, m_Normal.x, m_Normal.y, m_Normal.z, m_UV1.x, m_UV1.y, m_Tangent1.x, m_Tangent1.y, m_Tangent1.z, m_Bitangent1.x, m_Bitangent1.y, m_Bitangent1.z,
			m_Point2.x, m_Point2.y, m_Point2.z, m_Normal.x, m_Normal.y, m_Normal.z, m_UV2.x, m_UV2.y, m_Tangent1.x, m_Tangent1.y, m_Tangent1.z, m_Bitangent1.x, m_Bitangent1.y, m_Bitangent1.z,
			m_Point3.x, m_Point3.y, m_Point3.z, m_Normal.x, m_Normal.y, m_Normal.z, m_UV3.x, m_UV3.y, m_Tangent1.x, m_Tangent1.y, m_Tangent1.z, m_Bitangent1.x, m_Bitangent1.y, m_Bitangent1.z,

			m_Point1.x, m_Point1.y, m_Point1.z, m_Normal.x, m_Normal.y, m_Normal.z, m_UV1.x, m_UV1.y, m_Tangent2.x, m_Tangent2.y, m_Tangent2.z, m_Bitangent2.x, m_Bitangent2.y, m_Bitangent2.z,
			m_Point3.x, m_Point3.y, m_Point3.z, m_Normal.x, m_Normal.y, m_Normal.z, m_UV3.x, m_UV3.y, m_Tangent2.x, m_Tangent2.y, m_Tangent2.z, m_Bitangent2.x, m_Bitangent2.y, m_Bitangent2.z,
			m_Point4.x, m_Point4.y, m_Point4.z, m_Normal.x, m_Normal.y, m_Normal.z, m_UV4.x, m_UV4.y, m_Tangent2.x, m_Tangent2.y, m_Tangent2.z, m_Bitangent2.x, m_Bitangent2.y, m_Bitangent2.z,
		};

		float cubeVertices[] = {
			// back face
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
			// front face
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			// left face
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			// right face
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
			// bottom face
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			// top face
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
		};

		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};

		m_PlaneVAO = std::make_unique<VertexArray>();
		m_PlaneVAO->Bind();

		m_PlaneVBO = std::make_unique<VertexBuffer>(vertexBuffer, sizeof(vertexBuffer));
		m_PlaneVBO->Bind();
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		layout.Push<float>(3);
		layout.Push<float>(3);
		m_PlaneVAO->AddBuffer(*m_PlaneVBO, layout);
		m_PlaneVAO->Unbind();

		m_CubeVAO = std::make_unique<VertexArray>();
		m_CubeVAO->Bind();

		m_CubeVBO = std::make_unique<VertexBuffer>(cubeVertices, sizeof(cubeVertices));
		m_CubeVBO->Bind();
		VertexBufferLayout layoutCube;
		layoutCube.Push<float>(3);
		layoutCube.Push<float>(3);
		layoutCube.Push<float>(2);
		m_CubeVAO->AddBuffer(*m_CubeVBO, layoutCube);
		m_CubeVAO->Unbind();

		m_QuadVAO = std::make_unique<VertexArray>();
		m_QuadVAO->Bind();

		m_QuadVBO = std::make_unique<VertexBuffer>(quadVertices, sizeof(quadVertices));
		m_QuadVBO->Bind();
		VertexBufferLayout quadLayout;
		quadLayout.Push<float>(3);
		quadLayout.Push<float>(2);
		m_QuadVAO->AddBuffer(*m_QuadVBO, quadLayout);
		m_QuadVAO->Unbind();

		objectPositions.push_back(glm::vec3(-3.0, -0.5, -3.0));
		objectPositions.push_back(glm::vec3(0.0, -0.5, -3.0));
		objectPositions.push_back(glm::vec3(3.0, -0.5, -3.0));
		objectPositions.push_back(glm::vec3(-3.0, -0.5, 0.0));
		objectPositions.push_back(glm::vec3(0.0, -0.5, 0.0));
		objectPositions.push_back(glm::vec3(3.0, -0.5, 0.0));
		objectPositions.push_back(glm::vec3(-3.0, -0.5, 3.0));
		objectPositions.push_back(glm::vec3(0.0, -0.5, 3.0));
		objectPositions.push_back(glm::vec3(3.0, -0.5, 3.0));

		m_Shader = std::make_unique<Shader>("res/shaders/NormalMap.shader");
		m_DenemeShader = std::make_unique<Shader>("res/shaders/Deneme.shader");
		m_HDRShader = std::make_unique<Shader>("res/shaders/HDR.shader");
		m_NormalShader = std::make_unique<Shader>("res/shaders/Normal.shader", 1);
		m_LightShader = std::make_unique<Shader>("res/shaders/Light.shader");
		m_FinalShader = std::make_unique<Shader>("res/shaders/final.shader");
		m_BlurShader = std::make_unique<Shader>("res/shaders/blur.shader");
		m_DiffShader = std::make_unique<Shader>("res/shaders/Diff.shader");
		m_DeferredShader = std::make_unique<Shader>("res/shaders/Deferred.shader");
		m_ModelShader = std::make_unique<Shader>("res/shaders/Model.shader");
		m_SceneShader = std::make_unique<Shader>("res/shaders/Scene.shader");
		m_LightCubeShader = std::make_unique<Shader>("res/shaders/LightCube.shader");

		m_DeferringShader = std::make_unique<Shader>("res/shaders/DeferringShader.shader");
		m_SSAOShader = std::make_unique<Shader>("res/shaders/SSAO.shader");
		m_SSAOBlurShader = std::make_unique<Shader>("res/shaders/ssaoBlur.shader");
		m_SSAOFinalShader = std::make_unique<Shader>("res/shaders/ssaoFinal.shader");

		m_Textures.emplace("Diffuse", new Texture("res/textures/brick/bricks2.jpg"));
		m_Textures.emplace("Normal", new Texture("res/textures/brick/bricks2_normal.jpg"));
		m_Textures.emplace("Height", new Texture("res/textures/brick/bricks2_disp.jpg"));

		m_Textures.emplace("Wood", new Texture("res/textures/container_diffuse.png"));

		m_Textures.emplace("ToyDiffuse", new Texture("res/textures/toy/wood.png"));
		m_Textures.emplace("ToyNormal", new Texture("res/textures/toy/toy_box_normal.png"));
		m_Textures.emplace("ToyHeight", new Texture("res/textures/toy/toy_box_disp.png"));
		//loadModel = new obj::Model("res/obj/nanosuit/source/scene.fbx");

		lightPositions.emplace_back(glm::vec3(2.0, 4.0, -2.0));
		lightColors.emplace_back(glm::vec3(0.2, 0.2, 0.7));

		GLCall(glGenRenderbuffers(1, &hdrRenderBuffer));
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, hdrRenderBuffer));
		GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_ScreenWidth, m_ScreenHeight));
	
		glGenBuffers(1, &uniformBlock);
		glBindBuffer(GL_UNIFORM_BUFFER, uniformBlock);
		glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindBufferRange(GL_UNIFORM_BUFFER, 0, uniformBlock, 0, 2 * sizeof(glm::mat4));

		glUniformBlockBinding(m_DenemeShader->GetId(), glGetUniformBlockIndex(m_DenemeShader->GetId(), "matrices"), 0);
		glUniformBlockBinding(m_LightShader->GetId(), glGetUniformBlockIndex(m_LightShader->GetId(), "matrices"), 0);
		//model = new obj::Model("res/obj/backpack/backpack.obj");

		GLCall(glGenFramebuffers(1, &gBuffer));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, gBuffer));

		GLCall(glGenTextures(1, &gPosition));
		GLCall(glBindTexture(GL_TEXTURE_2D, gPosition));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_ScreenWidth, m_ScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0));

		GLCall(glGenTextures(1, &gNormal));
		GLCall(glBindTexture(GL_TEXTURE_2D, gNormal));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_ScreenWidth, m_ScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0));

		unsigned int colorBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };

		GLCall(glGenTextures(1, &gAlbedoSpec));
		GLCall(glBindTexture(GL_TEXTURE_2D, gAlbedoSpec));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_ScreenWidth, m_ScreenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0));
		GLCall(glDrawBuffers(3, colorBuffers));

		glGenRenderbuffers(1, &bloomRBO);
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, bloomRBO));
		GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_ScreenWidth, m_ScreenHeight));
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, bloomRBO);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

		glGenFramebuffers(1, &ssaoFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
		glGenTextures(1, &ssaoTexture);
		glBindTexture(GL_TEXTURE_2D, ssaoTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_ScreenWidth, m_ScreenHeight, 0, GL_RED, GL_FLOAT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoTexture, 0);

		glGenFramebuffers(1, &ssaoBlurFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);
		glGenTextures(1, &ssaoBlurTexture);
		glBindTexture(GL_TEXTURE_2D, ssaoBlurTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_ScreenWidth, m_ScreenHeight, 0, GL_RED, GL_FLOAT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoBlurTexture, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		std::uniform_real_distribution<float> randomFloat(0.0f, 1.0f);
		std::default_random_engine engine;

		for (int i = 0; i < 64; i++)
		{
			glm::vec3 sample = glm::vec3(
				randomFloat(engine) * 2.0f - 1.0f, 
				randomFloat(engine) * 2.0f - 1.0f,
				randomFloat(engine));

			sample = glm::normalize(sample);
			sample *= randomFloat(engine);

			float scale = (float)i / 64.0f;
			scale = lerp(0.1f, 1.0f, scale * scale);

			sample *= scale;
			ssaoKernel.emplace_back(sample);
		}

		for (int i = 0; i < 16; i++)
		{
			ssaoRotate.emplace_back(
				glm::vec3(
					randomFloat(engine) * 2.0f - 1.0f,
					randomFloat(engine) * 2.0f - 1.0f,
					0.0f
			));
		}

		glGenTextures(1, &noiseTexture);
		glBindTexture(GL_TEXTURE_2D, noiseTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 4, 4, 0, GL_RGBA, GL_FLOAT, &ssaoRotate[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		model = new obj::Model("res/obj/backpack/backpack.obj");
		glViewport(0, 0, m_ScreenWidth, m_ScreenHeight);

	}
	TestShadows::~TestShadows()
	{
	}
	void TestShadows::OnUpdate(float deltaTime)
	{
		camera.OnUpdate();
	}
	void TestShadows::OnRender()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.OnRender();
		{
			glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_CubeVAO->Bind();
			m_DeferringShader->Bind();

			m_DeferringShader->SetUniformMat4f("u_Proj", m_Proj);
			m_DeferringShader->SetUniformMat4f("u_View", m_View);
			m_Model = glm::mat4(1.0f);
			m_Model = glm::translate(m_Model, glm::vec3(0.0, 7.0f, 0.0f));
			m_Model = glm::scale(m_Model, glm::vec3(7.5f, 7.5f, 7.5f));
			m_DeferringShader->SetUniformMat4f("u_Model", m_Model);
			m_DeferringShader->SetUniform1i("isInverseNormal", m_IsInverse);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			m_CubeVAO->Unbind();
			m_Model = glm::mat4(1.0f);
			m_Model = glm::translate(m_Model, glm::vec3(0.0f, 0.5f, 0.0));
			m_Model = glm::rotate(m_Model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
			m_Model = glm::scale(m_Model, glm::vec3(1.0f));
			m_DeferringShader->SetUniformMat4f("u_Model", m_Model);
			model->Draw(*m_DeferringShader);
			 
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		{
			glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_QuadVAO->Bind();
			m_SSAOShader->Bind();
			
			m_SSAOShader->SetUniformMat4f("u_Proj", m_Proj);
			for (int i = 0; i < 64; i++)
				m_SSAOShader->SetUniformVec3f("samplers[" + std::to_string(i) + "]", ssaoKernel.at(i));
			m_SSAOShader->SetUniform1f("bias", bias);
			m_SSAOShader->SetUniform1f("radius", radius);
			m_SSAOShader->SetUniform1f("str", str);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, gPosition);
			m_SSAOShader->SetUniform1i("gPosition", 0);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, gNormal);
			m_SSAOShader->SetUniform1i("gNormal", 1);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, noiseTexture);
			m_SSAOShader->SetUniform1i("ssaoNoise", 2);
			
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			
			m_QuadVAO->Unbind();
			m_SSAOShader->Unbind();
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		{
			glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);
			glClear(GL_COLOR_BUFFER_BIT);

			m_QuadVAO->Bind();
			m_SSAOBlurShader->Bind();
			m_SSAOBlurShader->SetUniform1i("ssaoTexture", 0);
			glBindTexture(GL_TEXTURE_2D, ssaoTexture);
			glActiveTexture(GL_TEXTURE0);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			m_QuadVAO->Unbind();
			m_SSAOBlurShader->Unbind();
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_QuadVAO->Bind();
			m_SSAOFinalShader->Bind();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, gPosition);
			m_SSAOFinalShader->SetUniform1i("gPosition", 0);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, gNormal);
			m_SSAOFinalShader->SetUniform1i("gNormal", 1);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
			m_SSAOFinalShader->SetUniform1i("gAlbedo", 2);
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, ssaoBlurTexture);
			m_SSAOFinalShader->SetUniform1i("SSAO", 3);
			glm::vec3 viewLight = glm::vec3(m_View * glm::vec4(lightPositions.at(0), 1.0f));
			m_SSAOFinalShader->SetUniformVec3f("u_Light.Position", viewLight);
			m_SSAOFinalShader->SetUniformVec3f("u_Light.Color", lightColors.at(0));
			m_SSAOFinalShader->SetUniform1f("u_Light.Linear", linear);
			m_SSAOFinalShader->SetUniform1f("u_Light.Quadratic", quadratic);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			m_QuadVAO->Unbind();
			m_SSAOFinalShader->Unbind();

		}


	}
	void TestShadows::OnImGuiRender()
	{
		ImGui::Begin("Translations");
		ImGui::SliderFloat3("Light0 Translation", &lightPositions.at(0).x, -50.0f, 50.0f);
		ImGui::ColorEdit3("Color", &lightColors.at(0).x);

		ImGui::SliderFloat("Bias", &bias, 0.01f, 0.1f);
		ImGui::SliderFloat("Radius", &radius, 0, 1.0f);
		ImGui::SliderFloat("Str", &str, 0, 16.0f);

		ImGui::SliderFloat("Linear", &linear, 0.01f, 0.1f);
		ImGui::SliderFloat("Quadratic", &quadratic, 0.01f, 0.1f);

		ImGui::Checkbox("Is Inverse Normal", &m_IsInverse);
		ImGui::End();
		camera.OnImGuiRender();
	}
}