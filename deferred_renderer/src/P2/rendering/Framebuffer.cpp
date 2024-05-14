#include "Framebuffer.h"
#include <Empathy/Debug.h>

#include <glad/glad.h>

void Framebuffer::checkStatus()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	GLenum fb_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	switch (fb_status) {
		case GL_FRAMEBUFFER_UNDEFINED:	EM_ERROR("GL_FRAMEBUFFER_UNDEFINED"); break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:	EM_ERROR("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"); break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:	EM_ERROR("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"); break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:	EM_ERROR("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"); break;
		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:	EM_ERROR("GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS"); break;
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:	EM_ERROR("GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE"); break;
		case GL_FRAMEBUFFER_UNSUPPORTED:	EM_ERROR("GL_FRAMEBUFFER_UNSUPPORTED"); break;
		case GL_FRAMEBUFFER_COMPLETE:	EM_INFO("Framebuffer completed!"); break;
		default: EM_ERROR("Unknown framebuffer status error.");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Init(int width, int height)
{
	m_Size = { width, height };

	glGenFramebuffers(1, &m_FBO);

	// Base color attachment
	AddColorAttachment();

	// Depth attachment
	glGenTextures(1, &m_DepthAttachment);
	glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_Size.x, m_Size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_DepthAttachment, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	checkStatus();
}

void Framebuffer::AddColorAttachment()
{
	u32 color_attachment;
	glGenTextures(1, &color_attachment);
	glBindTexture(GL_TEXTURE_2D, color_attachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Size.x, m_Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	u32 color_attachment_index = GL_COLOR_ATTACHMENT0 + (i32)m_ColorAttachments.size();

	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glFramebufferTexture(GL_FRAMEBUFFER, color_attachment_index, color_attachment, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_ColorAttachments.push_back(color_attachment);
	m_ColorAttachmentIndex.push_back(color_attachment_index);
}

void Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glDrawBuffers((i32)m_ColorAttachmentIndex.size(), m_ColorAttachmentIndex.data());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Framebuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}