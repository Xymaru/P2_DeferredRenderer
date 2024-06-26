#pragma once

#include <Empathy/SimpleTypes.h>

namespace EM {
	class Image {
	private:
		u32 m_ImageId;
		i32 m_Channels;
		i32 m_Stride;
		ivec2 m_Size;
	public:
		Image() = default;

		bool Load(const char* file);

		u32 getImageId() { return m_ImageId; }
		ivec2 getSize() { return m_Size; }
	};
}