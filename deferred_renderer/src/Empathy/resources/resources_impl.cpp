#include "resources_impl.h"

namespace EM {
	std::vector<Resources::ResourceData*> Resources::mResources[RT_LAST];

	u32 Resources::getResourcePosition(ResourceType rt, const char * file)
	{
		size_t size = mResources[rt].size();

		u32 resourceId = EM_INVALID_RESOURCE;

		for (size_t i = 0; i < size; i++) {
			if (mResources[rt][i]->filePath == file) {
				resourceId = static_cast<u32>(i);
				break;
			}
		}

		return resourceId;
	}

	const char* Resources::getResourcePath_impl(ResourceType rt, ResourceId id)
	{
		return mResources[rt][id]->filePath.c_str();
	}

	void* Resources::getResourceById_impl(ResourceType rt, ResourceId id)
	{
		if (id >= 0 && id < mResources[rt].size()) {
			return mResources[rt][id]->resource;
		}

		return nullptr;
	}
	u32 Resources::push_resource(ResourceType rt, void* resource, const char* file)
	{
		ResourceData* r_data = new ResourceData();

		r_data->filePath = file;

		r_data->resource = resource;

		u32 id = static_cast<u32>(mResources[rt].size());

		mResources[rt].push_back(r_data);

		return id;
	}
}