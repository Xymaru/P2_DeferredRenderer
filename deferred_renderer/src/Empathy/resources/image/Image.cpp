#include "Image.h"
#include <glad/glad.h>

#include <stb.h>

#include <Empathy/filesystem/FileSystem.h>

namespace EM {
	bool Image::Load(const char* path)
	{
		EM::Memory img_mem = EM::FileSystem::ReadAll(path);

		int w, h, ch;

		unsigned char* image = stbi_load_from_memory((stbi_uc*)img_mem.getBlock(), (int)img_mem.Size(), &w, &h, &ch, STBI_rgb_alpha);

		if (!image) {
			return false;
		}

		glGenTextures(1, &m_ImageId);
		glBindTexture(GL_TEXTURE_2D, m_ImageId);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(image);

		m_Size.x = w;
		m_Size.y = h;

		m_Channels = ch;

		return true;
	}
}