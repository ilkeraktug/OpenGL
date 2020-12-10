#include "TestAdvanced.h"

#include "VertexBufferLayout.h"
namespace test {

    TestAdvanced::TestAdvanced()
        : camera(&m_Proj, &m_View, 1280.0f, 768.0f)
    {
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glDepthFunc(GL_LESS));

        /* glEnable(GL_PROGRAM_POINT_SIZE);
         GLCall(glEnable(GL_CULL_FACE));
         GLCall(glCullFace(GL_BACK));
         GLCall(glFrontFace(GL_CW));*/

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        m_CubeVAO = std::make_unique<VertexArray>();
        m_PlaneVAO = std::make_unique<VertexArray>();
        m_SkyboxVAO = std::make_unique<VertexArray>();
        m_QuadVAO = std::make_unique<VertexArray>();

        float cubeVertices[] = {
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

        float planeVertices[] = {
            // positions            // normals         // texcoords
         10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

         10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
         10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
        };

        float skyboxVertices[] = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
        };

        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };

        int index = 0;
        float offset = 0.1f;
        for (int y = -10; y < 10; y += 2)
        {
            for (int x = -10; x < 10; x += 2)
            {
                glm::vec2 translation;
                translation.x = (float)x / 10.0f + offset;
                translation.y = (float)y / 10.0f + offset;
                translations[index++] = translation;
            }
        }

        m_QuadVAO->Bind();
        m_QuadVBO = std::make_unique<VertexBuffer>(quadVertices, sizeof(quadVertices));
        VertexBufferLayout other;
        other.Push<float>(3);
        other.Push<float>(3);
        other.Push<float>(2);
        m_QuadVAO->AddBuffer(*m_QuadVBO, other);
        unsigned int instanceVBO;
        glGenBuffers(1, &instanceVBO);
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glVertexAttribDivisor(2, 1);
        m_QuadVAO->Unbind();

        m_SkyboxVAO->Bind();
        m_SkyboxVBO = std::make_unique<VertexBuffer>(skyboxVertices, sizeof(skyboxVertices));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        m_SkyboxVAO->AddBuffer(*m_SkyboxVBO, layout);
        m_SkyboxVAO->Unbind();

        m_CubeVAO->Bind();
        m_CubeVBO = std::make_unique<VertexBuffer>(cubeVertices, sizeof(cubeVertices));
        layout.Push<float>(2);
        m_CubeVAO->AddBuffer(*m_CubeVBO, other);
        m_CubeVAO->Unbind();

        m_PlaneVAO->Bind();
        m_PlaneVBO = std::make_unique<VertexBuffer>(planeVertices, sizeof(planeVertices));
        m_PlaneVAO->AddBuffer(*m_PlaneVBO, other);
        m_PlaneVAO->Unbind();

        m_Shader = std::make_unique<Shader>("res/shaders/Advanced.shader");
        m_DiffShader = std::make_unique<Shader>("res/shaders/Diff.shader");
        m_BasicShader = std::make_unique<Shader>("res/shaders/Geometry.shader", 1);
        m_SkyboxShader = std::make_unique<Shader>("res/shaders/Skybox.shader");
        m_QuadShader = std::make_unique<Shader>("res/shaders/Quad.shader");
        m_NormalShader = std::make_unique<Shader>("res/shaders/Normal.shader", 1);
        m_LightShader = std::make_unique<Shader>("res/shaders/LightShader.shader");
        m_PointLightShader = std::make_unique<Shader>("res/shaders/PointLight.shader", 1);


        m_SkyboxTexture = std::make_unique<CubeMap>("res/textures/skybox");
        m_MetalTexture = std::make_unique<Texture>("res/obj/teapot/diffuse.jpg");

        m_Textures.emplace("Marble", new Texture("res/textures/marble.jpg"));
        m_Textures.emplace("Wood", new Texture("res/textures/wood.png"));
        glTextureParameteri(m_Textures["Wood"]->GetId(), GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_Textures["Wood"]->GetId(), GL_TEXTURE_WRAP_T, GL_REPEAT);
        //loadModel = new obj::Model("res/obj/backpack/backpack.obj");


        m_FrameBuffer = std::make_unique<FrameBuffer>(1280, 768);

        glGenFramebuffers(1, &depthMapFBO);


        GLCall(glGenTextures(1, &shadowTex));
        GLCall(glBindTexture(GL_TEXTURE_2D, shadowTex));
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_ShadowWidth, m_ShadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO));
        GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowTex, 0));
        GLCall(glDrawBuffer(GL_NONE));
        GLCall(glReadBuffer(GL_NONE));
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Frame Buffer Succed" << std::endl;
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

        m_PointLightTexture = std::make_unique<CubeMap>(m_ShadowWidth, m_ShadowHeight);
        GLCall(glGenFramebuffers(1, &pointDepthMapFBO));
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, pointDepthMapFBO));
        GLCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_PointLightTexture->GetID(), 0));
        GLCall(glReadBuffer(GL_NONE));
        GLCall(glDrawBuffer(GL_NONE));
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
            std::cout << "CubeMap Frame Buffer Succed" << std::endl;
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

    }

    TestAdvanced::~TestAdvanced()
    {

    }
    void TestAdvanced::OnRender()
    {
        camera.OnRender();
        std::vector<glm::mat4> m_ShadowTransform;
        m_ShadowTransform.push_back(m_ShadowProjection *
            glm::lookAt(m_LightPosition, m_LightPosition + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
        m_ShadowTransform.push_back(m_ShadowProjection *
            glm::lookAt(m_LightPosition, m_LightPosition + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
        m_ShadowTransform.push_back(m_ShadowProjection *
            glm::lookAt(m_LightPosition, m_LightPosition + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
        m_ShadowTransform.push_back(m_ShadowProjection *
            glm::lookAt(m_LightPosition, m_LightPosition + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
        m_ShadowTransform.push_back(m_ShadowProjection *
            glm::lookAt(m_LightPosition, m_LightPosition + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
        m_ShadowTransform.push_back(m_ShadowProjection *
            glm::lookAt(m_LightPosition, m_LightPosition + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        {
            glDisable(GL_DEPTH_TEST);
            m_SkyboxShader->Bind();
            m_SkyboxVAO->Bind();
            glm::mat4 mvp = m_Proj * glm::mat4(glm::mat3(m_View));
            m_SkyboxShader->SetUniformMat4f("u_MVP", mvp);
            m_SkyboxTexture->Bind(0);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glEnable(GL_DEPTH_TEST);
            m_SkyboxShader->Unbind();
        }
        {
            glViewport(0, 0, m_ShadowWidth, m_ShadowHeight);
            glBindFramebuffer(GL_FRAMEBUFFER, pointDepthMapFBO);
            glClear(GL_DEPTH_BUFFER_BIT);
            m_PointLightShader->Bind();
            m_CubeVAO->Bind();
            for (size_t i = 0; i < 6; i++)
            {
                m_PointLightShader->SetUniformMat4f("u_ShadowMat[" + std::to_string(i) + "]", m_ShadowTransform[i]);
            }

            m_PointLightShader->SetUniform1f("u_FarPlane", 25.0f);
            m_PointLightShader->SetUniformVec3f("u_LightPos", m_LightPosition);

            m_Model = glm::translate(glm::mat4(1.0f), CubeTranslationA);
            m_PointLightShader->SetUniformMat4f("u_Model", m_Model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            m_Model = glm::translate(glm::mat4(1.0f), CubeTranslationB);
            m_PointLightShader->SetUniformMat4f("u_Model", m_Model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            m_Model = glm::translate(glm::mat4(1.0f), CubeTranslationC);
            m_PointLightShader->SetUniformMat4f("u_Model", m_Model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            m_CubeVAO->Unbind();

            m_PlaneVAO->Bind();
            m_Model = glm::translate(glm::mat4(1.0f), PlaneTranslationA);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            m_PointLightShader->SetUniformMat4f("u_Model", m_Model);
            
            m_PlaneVAO->Unbind();
            m_PointLightShader->Unbind();
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        {
            glViewport(0, 0, 1280, 768);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            m_CubeVAO->Bind();
            m_QuadShader->Bind();
            m_Textures["Wood"]->Bind(1);
            m_PointLightTexture->Bind(2);
            m_QuadShader->SetUniform1f("u_FarPlane", 25.0f);

            m_Model = glm::translate(glm::mat4(1.0f), CubeTranslationA);
            m_QuadShader->SetUniformMat4f("u_Proj", m_Proj);
            m_QuadShader->SetUniformMat4f("u_View", m_View);
            m_QuadShader->SetUniformMat4f("u_Model", m_Model);

            m_QuadShader->SetUniformVec3f("u_LightPos", m_LightPosition);
            m_QuadShader->SetUniformVec3f("u_CamPos", camera.GetCameraPosition());

            m_QuadShader->SetUniform1i("diffuseTexture", 1);
            m_QuadShader->SetUniform1i("cubeDepthTexture", 2);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            m_Model = glm::translate(glm::mat4(1.0f), CubeTranslationB);
            m_QuadShader->SetUniformMat4f("u_Model", m_Model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            m_Model = glm::translate(glm::mat4(1.0f), CubeTranslationC);
            m_QuadShader->SetUniformMat4f("u_Model", m_Model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
            m_CubeVAO->Unbind();

            m_PlaneVAO->Bind();
            m_Model = glm::translate(glm::mat4(1.0f), PlaneTranslationA);
            m_QuadShader->SetUniformMat4f("u_Model", m_Model);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            m_PlaneVAO->Unbind();
            m_QuadShader->Unbind();
        }
    }

	void TestAdvanced::OnUpdate(float deltaTime)
	{
        camera.OnUpdate();
	}
	void TestAdvanced::OnImGuiRender()
	{
        ImGui::Begin("Translate");
        ImGui::SliderFloat3("Cube A", &CubeTranslationA.x, -50.0f, 50.0f);
        ImGui::SliderFloat3("Cube B", &CubeTranslationB.x, -50.0f, 50.0f);
        ImGui::SliderFloat3("Cube C", &CubeTranslationC.x, -50.0f, 50.0f);
        ImGui::SliderFloat3("Plane A", &PlaneTranslationA.x, -50.0f, 50.0f);

        ImGui::SliderFloat3("LightPosition", &m_LightPosition.x, -50.0f, 50.0f);
        if (ImGui::Button("Reset"))
            m_LightPosition = glm::vec3(-2.0f, 4.0f, -1.0f);

        ImGui::End();
        camera.OnImGuiRender();
	}
}

