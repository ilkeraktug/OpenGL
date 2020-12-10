#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "imgui.h"
#include "backends\imgui_impl_glfw.h"
#include "backends\imgui_impl_opengl3.h"

#include "tests\TestClearColor.h"
#include "tests\TestTexture2D.h"
#include "tests\TestLighting.h"
#include "tests\Camera.h"
#include "tests\TestAdvanced.h"
#include "tests\TestShadows.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
    window = glfwCreateWindow(1280, 768, "Hello World", NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
    ImGui::StyleColorsDark();

    std::cout << "[OpenGL] Ver : " << glGetString(GL_VERSION) << " Renderer : " << glGetString(GL_RENDERER) << std::endl;      
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);

    test::Test* currentTest = new test::Test();
    test::TestMenu* testMenu = new test::TestMenu(currentTest);

    //testMenu->RegisterMenu<test::TestClearColor>("Clear Color");
    //testMenu->RegisterMenu<test::TestTexture2D>("Texture2D");
    //testMenu->RegisterMenu<test::TestLighting>("Lighting");
    //testMenu->RegisterMenu<test::TestAdvanced>("Advanced");
    //testMenu->RegisterMenu<test::TestShadows>("Shadows");
    //currentTest = testMenu->GetWindow<test::TestShadows>();
    //currentTest = testMenu;
    //currentTest = testMenu->GetWindowAssimp<test::TestAssimp>("res/obj/backpack.obj");

    while (!glfwWindowShouldClose(window))
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if (currentTest)
        {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            ImGui::Begin("TestMenu");
            if (currentTest != testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        }

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}