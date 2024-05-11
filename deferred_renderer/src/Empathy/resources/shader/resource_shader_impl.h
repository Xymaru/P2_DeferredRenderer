#pragma once

#include "../resources_impl.h"

#include "Shader.h"

namespace EM {
	//--SPECIALIZATION FOR SPRITE
	template<>
	inline u32 Resources::Load<Shader>(const char* file)
	{
		return loadResource_impl<Shader, RT_SHADER>(file);
	}

	template<>
	inline Shader* Resources::GetResourceById<Shader>(ResourceId id)
	{
		return static_cast<Shader*>(getResourceById_impl(RT_SHADER, id));
	}

	template<>
	inline const char* Resources::GetResourcePath<Shader>(ResourceId id)
	{
		return getResourcePath_impl(RT_SHADER, id);
	}
}