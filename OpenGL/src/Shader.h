#pragma once

#include <unordered_map>

#include "glm\gtc\matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

struct ShaderSource
{
	std::string VertexShader;
	std::string FragmentShader;
	std::string GeometryShader;
};

class Shader
{
private:
	std::string m_Filepath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationsCache;
public:

	Shader(const std::string& filepath);
	Shader(const std::string& filepath, unsigned int slot);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformVec3f(const std::string& name, glm::vec3 vector);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void SetUniformMat3f(const std::string& name, const glm::mat3& matrix);

	unsigned int GetId() { return m_RendererID; }
private:
	ShaderSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);

	int GetUniformLocation(const std::string& name);
};

