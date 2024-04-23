#pragma once

#include <Empathy/SimpleTypes.h>

class Image {
private:
	u32 m_ImageId;
	i32 m_Channels;
	i32 m_Stride;
	ivec2 m_Size;
public:
	Image() = default;

	bool Load(const char* path);

	u32 getImageId() { return m_ImageId; }
	ivec2 getSize() { return m_Size; }
};