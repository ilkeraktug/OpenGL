#pragma once

#include <array>
#include "Renderer.h"
#include "stb/stb_image.h"

class CubeMap {
public:
	CubeMap(const std::string& filePath);
	CubeMap(int Width, int Height);
	~CubeMap();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	unsigned int GetID();
private:
	unsigned int m_RendererID;

	std::string m_FilePath;
	int m_Width, m_Height, m_BPP;
	unsigned char* m_LocalBuffer;

	std::array<std::string, 6> cubePositions = { "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"};
};