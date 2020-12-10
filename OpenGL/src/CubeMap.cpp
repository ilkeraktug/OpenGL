#include "CubeMap.h"

#include <iostream>
CubeMap::CubeMap(const std::string& filePath)
	: m_RendererID(0), m_FilePath(filePath), m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0)
{
	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));

	//stbi_set_flip_vertically_on_load(1);

	for (int i = 0; i < 6; i++)
	{
		std::cout << "Loading texture from : " << (filePath + "/" + cubePositions[i]).c_str() << std::endl;
		m_LocalBuffer = stbi_load((filePath + "/" + cubePositions[i]).c_str(), &m_Width, &m_Height, &m_BPP, 4);

		GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));

		stbi_image_free(m_LocalBuffer);
	}

	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0))
}

CubeMap::CubeMap(int Width, int Height)
	: m_RendererID(0), m_FilePath("0"), m_LocalBuffer(nullptr),
	m_Width(Width), m_Height(Height), m_BPP(0)
{
	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));

	for (size_t i = 0; i < 6; i++)
	{
		GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));
	}

	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
}

CubeMap::~CubeMap()
{
	glDeleteTextures(1, &m_RendererID);
}

void CubeMap::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));
}

void CubeMap::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0))
}

unsigned int CubeMap::GetID()
{
	return m_RendererID;
}
