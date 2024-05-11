#include "Image.h"
#include <glad/glad.h>

#include <stb.h>

#include <Empathy/filesystem/FileSystem.h>
#include <Empathy/Debug.h>

namespace EM {
	bool Image::Load(const char* file)
	{
		EM::Memory img_mem = EM::FileSystem::ReadAll(file);

		if (img_mem.IsEmpty()) {
			return false;
		}

		int w, h, ch;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* image = stbi_load(file, &w, &h, &ch, 0);//stbi_load_from_memory((stbi_uc*)img_mem.getBlock(), (int)img_mem.size(), &w, &h, &ch, 0);

		if (!image) {
			return false;
		}

		u32 internal_format = GL_RGB;
		u32 data_format = GL_RGB;
		u32 data_type = GL_UNSIGNED_BYTE;

		switch (ch) {
		case 1:
			data_format = internal_format = GL_RED;
			break;
		case 3:
			data_format = internal_format = GL_RGB;
			break;
		case 4:
			data_format = internal_format = GL_RGBA;
			break;
		default:
			EM_ERROR("Unsupported number of channels loading file: {}", file);
		}

		// Generate opengl texture
		glGenTextures(1, &m_ImageId);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_ImageId);

		glTexImage2D(GL_TEXTURE_2D, 0, internal_format, w, h, 0, data_format, data_type, image);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(image);

		m_Size.x = w;
		m_Size.y = h;
		m_Stride = w * ch;

		m_Channels = ch;

		return true;
	}
}