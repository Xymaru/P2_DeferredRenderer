#pragma once

#include "../resources_impl.h"

#include "Model.h"

namespace EM {
	//--SPECIALIZATION FOR MODEL
	template<>
	inline u32 Resources::Load<Model>(const char* file)
	{
		return loadResource_impl<Model, RT_MODEL>(file);
	}

	template<>
	inline Model* Resources::GetResourceById<Model>(ResourceId id)
	{
		return static_cast<Model*>(getResourceById_impl(RT_MODEL, id));
	}

	template<>
	inline const char* Resources::GetResourcePath<Model>(ResourceId id)
	{
		return getResourcePath_impl(RT_MODEL, id);
	}
}