#include "TestLighting.h"
#include "Texture.h"
#include "VertexBufferLayout.h"

#include <math.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
namespace test {
	TestLighting::TestLighting()
        :camera(&m_Proj, &m_View, 800.0f, 600.0f)
    {
        glEnable(GL_DEPTH_TEST);
		m_VertexArray = std::make_unique<VertexArray>();
        float vertices[] = {
        //Position            //Normal             //TexCoords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
        };

		m_VertexArray->Bind();
		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		VertexBufferLayout layout;
		layout.Push<float>(3);
        layout.Push<float>(3); 
        layout.Push<float>(2);
		m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5 ,6, 6, 7, 4
		};

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);
		m_IndexBuffer->Bind();

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
        m_ObjectShader = std::make_unique<Shader>("res/shaders/Object.shader");
        m_DiffShader = std::make_unique<Shader>("res/shaders/Diff.shader");

        m_objectDiffuse = std::make_unique<Texture>("res/textures/container_diffuse.png");
        m_objectSpecular = std::make_unique<Texture>("res/textures/container_specular.png");
	}

	TestLighting::~TestLighting()
	{
        glDisable(GL_DEPTH_TEST);
	}

    void TestLighting::OnUpdate(float deltaTime)
    {
        camera.OnUpdate();
    }


	void TestLighting::OnRender()
	{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        camera.OnRender();
		m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(translationA.x, translationA.y, translationA.z));
        glm::mat4 lightPosition = m_Proj * m_View * m_Model;
        {
            //Light
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", lightPosition);
            m_Shader->SetUniform4f("u_Color", m_LightColor.x, m_LightColor.y, m_LightColor.z, m_LightColor.w);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
            m_Shader->Unbind();
        }
        {
            //Object
            m_ObjectShader->Bind();
            m_ObjectModel = glm::translate(glm::mat4(1.0f), glm::vec3(translationB.x, translationB.y, translationB.z));
            glm::mat3 normalTransform = glm::transpose(glm::inverse(glm::mat3(m_View * m_Model)));
            glm::vec3 lightProporties[] = {
                glm::vec3(lightAmbient, lightAmbient, lightAmbient) * glm::vec3(m_LightColor),
                glm::vec3(lightDiffuse, lightDiffuse, lightDiffuse) * glm::vec3(m_LightColor),
                glm::vec3(lightSpecular, lightSpecular, lightSpecular) * glm::vec3(m_LightColor)
            };
            m_objectDiffuse->Bind();
            m_objectSpecular->Bind(1);
            m_ObjectShader->SetUniform1i("u_Material.Diffuse", 0);
            m_ObjectShader->SetUniform1i("u_Material.Specular", 1);
            m_ObjectShader->SetUniform1f("u_Material.Shininess", 32.0f);

            m_ObjectShader->SetUniformMat4f("u_Proj", m_Proj);
            m_ObjectShader->SetUniformMat4f("u_View", m_View);
            m_ObjectShader->SetUniformMat4f("u_Model", m_ObjectModel);
            m_ObjectShader->SetUniformMat3f("u_NormalTransform", normalTransform);

            //m_ObjectShader->SetUniform3f("u_Material.Ambient", 0.0215f, 0.1745f, 0.0215f);
            //m_ObjectShader->SetUniform3f("u_Material.Diffuse", 0.07568f, 0.61424f, 0.07568f);
            //m_ObjectShader->SetUniform3f("u_Material.Specular", 0.633f, 0.727811f, 0.633f);

            glm::vec3 camPos = camera.GetCameraPosition();
            glm::vec3 camFr = camera.GetCameraFront();
            m_ObjectShader->SetUniform4f("u_DirLight.Direction", 0.0f, -1.0f, 0.0f, 0.0f);
            m_ObjectShader->SetUniformVec3f("u_DirLight.Ambient", lightProporties[0]);
            m_ObjectShader->SetUniformVec3f("u_DirLight.Diffuse", lightProporties[1]);
            m_ObjectShader->SetUniformVec3f("u_DirLight.Specular", lightProporties[2]);

            m_ObjectShader->SetUniform4f("u_PointLight.Position", translationA.x, translationA.y, translationA.z, 1.0f);
            m_ObjectShader->SetUniformVec3f("u_PointLight.Ambient", lightProporties[0]);
            m_ObjectShader->SetUniformVec3f("u_PointLight.Diffuse", lightProporties[1]);
            m_ObjectShader->SetUniformVec3f("u_PointLight.Specular", lightProporties[2]);
            m_ObjectShader->SetUniform1f("u_PointLight.Constant", 1.0f);
            m_ObjectShader->SetUniform1f("u_PointLight.Linear", 0.22f);
            m_ObjectShader->SetUniform1f("u_PointLight.Quadratic", 0.20f);


            m_ObjectShader->SetUniform4f("u_SpotLight.Position", camPos.x, camPos.y, camPos.z, 1.0f);
            m_ObjectShader->SetUniform3f("u_SpotLight.Direction", camFr.x, camFr.y, camFr.z);
            m_ObjectShader->SetUniformVec3f("u_SpotLight.Ambient", lightProporties[0]);
            m_ObjectShader->SetUniformVec3f("u_SpotLight.Diffuse", lightProporties[1]);
            m_ObjectShader->SetUniformVec3f("u_SpotLight.Specular", lightProporties[2]);
            m_ObjectShader->SetUniform1f("u_SpotLight.Constant", 1.0f);
            m_ObjectShader->SetUniform1f("u_SpotLight.Linear", 0.22f);
            m_ObjectShader->SetUniform1f("u_SpotLight.Quadratic", 0.20f);
            m_ObjectShader->SetUniform1f("u_SpotLight.CutoffAngle", glm::cos(glm::radians(12.5f)));
            m_ObjectShader->SetUniform1f("u_SpotLight.OuterCutoffAngle", glm::cos(glm::radians(17.5f)));

            m_ObjectShader->SetUniform4f("u_Camera.Position", camPos.x, camPos.y, camPos.z, 1.0f);

            glDrawArrays(GL_TRIANGLES, 0, 36);
            m_ObjectShader->Unbind();
        }

        {
           /* m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(translationA.x, translationA.y, translationA.z));
            glm::mat4 lightPosition = m_Proj * m_View * m_Model;
            {
                //Light
                m_DiffShader->Bind();
                m_DiffShader->SetUniformMat4f("u_MVP", lightPosition);
                //glDrawArrays(GL_TRIANGLES, 0, 36);
                u_Model->Draw(*m_ObjectShader);
                m_DiffShader->Unbind();
            }*/
        }
	}

	void TestLighting::OnImGuiRender()
	{
        ImGui::Begin("Translation");
        ImGui::SliderFloat3("DirecLight Pos", &translationA.x, -10.0f, 10.0f);
        ImGui::SliderFloat3("Cube Pos", &translationB.x, -10.0f, 10.0f);
        ImGui::SliderFloat("Light Ambient", &lightAmbient, 0.0f, 1.0f);
        ImGui::SliderFloat("Light Diffuse", &lightDiffuse, 0.0f, 1.0f);
        ImGui::SliderFloat("Light Specular", &lightSpecular, 0.0f, 1.0f);
        ImGui::ColorEdit4("Light Color", &m_LightColor.x);

        if (ImGui::Button("Reset"))
        {
            translationB = glm::vec3(-0.5f, 0.5f, -3.5f);

            lightAmbient = 0.15f;
        }

        camera.OnImGuiRender();
        ImGui::Text("%f", ImGui::GetIO().Framerate);
        ImGui::End();
	}
}