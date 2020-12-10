#pragma once

#include <glad\glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GlLogCall(#x, __LINE__, __FILE__))

void GLClearError();
bool GlLogCall(const char* function, int line, const char* file);

class Renderer
{
private:
public:
    void Clear();
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};

