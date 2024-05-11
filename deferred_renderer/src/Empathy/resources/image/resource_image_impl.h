#pragma once

#include "../resources_impl.h"

#include "Image.h"

namespace EM {
	//--SPECIALIZATION FOR SPRITE
	template<>
	inline u32 Resources::Load<Image>(const char* file)
	{
		return loadResource_impl<Image, RT_IMAGE>(file);
	}

	template<>
	inline Image* Resources::GetResourceById<Image>(ResourceId id)
	{
		return static_cast<Image*>(getResourceById_impl(RT_IMAGE, id));
	}

	template<>
	inline const char* Resources::GetResourcePath<Image>(ResourceId id)
	{
		return getResourcePath_impl(RT_IMAGE, id);
	}
}