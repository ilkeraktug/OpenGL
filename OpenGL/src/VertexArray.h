#pragma once


#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
private:
	//unsigned int m_RendererID;
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};

