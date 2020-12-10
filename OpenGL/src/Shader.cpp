#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <glad\glad.h>
#include "GLFW\glfw3.h"


Shader::Shader(const std::string& filepath)
    :m_Filepath(filepath), m_RendererID(0)
{
    ShaderSource shaders = ParseShader(filepath);
    m_RendererID = CreateShader(shaders.VertexShader, shaders.FragmentShader);
}

Shader::Shader(const std::string& filepath, unsigned int slot)
{
    ShaderSource shaders = ParseShader(filepath);
    m_RendererID = CreateShader(shaders.VertexShader, shaders.FragmentShader, shaders.GeometryShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformVec3f(const std::string& name, glm::vec3 vector)
{
    glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniformMat3f(const std::string& name, const glm::mat3& matrix)
{
    glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

ShaderSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream shader(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2
    };

    ShaderType type = ShaderType::NONE;

    std::stringstream stream[3];
    std::string line;
    while (std::getline(shader, line))
    {
        if (line.find("shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
            else if (line.find("geometry") != std::string::npos)
                type = ShaderType::GEOMETRY;
        }
        else
            stream[int(type)] << line << "\n";
    }
    return { stream[0].str(), stream[1].str(), stream[2].str() };
}

unsigned int Shader::CompileShader(int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);

    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(shader, length, &length, message);

        if(type == GL_VERTEX_SHADER)
            std::cout << "[ERROR]" << "Vertex Shader " << message << std::endl;
        else if (type == GL_FRAGMENT_SHADER)
            std::cout << "[ERROR]" << "Fragment Shader " << message << std::endl;
        else
            std::cout << "[ERROR]" << "Geometry Shader " << message << std::endl;

        delete[] message;
    }

    return shader;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader)
{
    unsigned int program = glCreateProgram();

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    unsigned int gs = CompileShader(GL_GEOMETRY_SHADER, geometryShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glAttachShader(program, gs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    glDeleteShader(gs);

    return program;
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationsCache.find(name) != m_UniformLocationsCache.end())
        return m_UniformLocationsCache[name];
    
    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
        std::cout <<"At shader ID : " << m_RendererID << " " << name << " doesnt exist. " << std::endl;
    m_UniformLocationsCache[name] = location;
    return location;
}
