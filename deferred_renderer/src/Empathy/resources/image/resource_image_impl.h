#pragma once

#include "../resources_impl.h"

#include "Image.h"

namespace EM {
	//--SPECIALIZATION FOR SPRITE
	template<>
	inline u32 Resources::Load<Image>(const char* file)
	{
		u32 resourceId = getResourcePosition(RT_IMAGE, file);

		if (resourceId == EM_INVALID_RESOURCE) {
			Image* image = new Image();

			if (image->Load(file)) {
				resourceId = push_resource(RT_IMAGE, image, file);

				EM_INFO("Loaded image at path [{}]", file);
			}
			else {
				EM_ERROR("Couldn't load image at path [{}]", file);

				delete image;
			}
		}

		return resourceId;
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