#pragma once

#include "../resources_impl.h"

#include "Shader.h"

namespace EM {
	// SPECIALIZATION FOR SHADER
	/*template<>
	inline ResourceId Resources::Load<Shader>(const char* file) {
		u32 position = getResourcePosition(RT_SHADER, file);
		u32 size = static_cast<u32>(mResources[RT_SHADER].size());

		ResourceId resourceId;

		if (position == size) {
			ResourceData* resource = new ResourceData();

			Shader* shader = new Shader();
			shader->Init(file);

			resource->filePath = file;
			resource->resource = shader;

			resourceId = size;

			mResources[RT_SHADER].push_back(resource);

			std::string message = "Loaded resource " + resource->filePath + " successfully.";

			Debug::Log("Resources", message.c_str());
		}
		else {
			resourceId = position;
		}

		return resourceId;
	}

	template<>
	inline Shader* Resources::GetResourceById<Shader>(ResourceId id) {
		Shader* resource = NULL;

		if (id >= 0 && id < mResources[RT_SHADER].size()) {
			resource = static_cast<Shader*>(mResources[RT_SHADER][id]->resource);
		}

		return resource;
	}

	template<>
	inline const char* Resources::GetResourcePath<Shader>(ResourceId id)
	{
		return mResources[RT_SHADER][id]->filePath.c_str();
	}*/
}