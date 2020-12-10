#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int width, int height)
	: m_Width(width), m_Height(height)
{
	GLCall(glGenFramebuffers(1, &m_RendererID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));

	GLCall(glGenTextures(1, &m_TextureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0));

	GLCall(glGenRenderbuffers(1, &m_RenderBufferID));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferID));

	GLCall(Unbind());
	GLCall(UnbindRenderBuffer());
	GLCall(UnbindTexture());
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_RendererID);
	glDeleteRenderbuffers(1, &m_RenderBufferID);
	glDeleteTextures(1, &m_TextureID);
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
}

void FrameBuffer::BindRenderBuffer()
{
	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID);
}

void FrameBuffer::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void FrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::UnbindRenderBuffer()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void FrameBuffer::UnbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
