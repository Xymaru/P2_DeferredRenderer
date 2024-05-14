#pragma once

#include <Empathy/SimpleTypes.h>
#include <vector>

class Framebuffer {
private:
	ivec2 m_Size;

	u32 m_FBO;

	std::vector<u32> m_ColorAttachments;
	std::vector<u32> m_ColorAttachmentIndex;
	u32 m_DepthAttachment;

	bool m_Completed;

	void checkStatus();
public:
	virtual void Init(int width, int height);

	void AddColorAttachment();

	size_t getColorAttachmentCount() { return m_ColorAttachments.size(); }
	u32* getColorAttachments() { return m_ColorAttachments.data(); }
	u32 getColorAttachment(int index) { return m_ColorAttachments[index]; }

	u32 getDepthAttachment() { return m_DepthAttachment; }

	void Bind();

	void Unbind();
};