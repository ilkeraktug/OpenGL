#include "Renderer.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GlLogCall(const char* function, int line, const char* file)
{
    while (unsigned int error = glGetError())
    {
        std::cout << "[OpenGL Error] " << error << " at " << function << "line : " << line << " at file : " << file << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    va.Bind();
    //ib.Bind();
    shader.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

