#pragma once

#include "Renderer.h"

class FrameBuffer
{
public:
	FrameBuffer(int width, int height);
	~FrameBuffer();

	void Bind();
	void BindRenderBuffer();
	void BindTexture();
	void Unbind();
	void UnbindRenderBuffer();
	void UnbindTexture();
private:
	int m_Width;
	int m_Height;

	unsigned int m_RendererID;
	unsigned int m_TextureID;
	unsigned int m_RenderBufferID;

};

