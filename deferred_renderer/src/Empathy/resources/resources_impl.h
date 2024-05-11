#pragma once
#pragma warning(disable : 4251)

#include <Empathy/SimpleTypes.h>

#include <string>
#include <vector>

#include <Empathy/Debug.h>

typedef u32 ResourceId;

constexpr ResourceId EM_INVALID_RESOURCE = U32_MAX;

namespace EM {
	class Resources
	{
	private:
		Resources() = default;
		~Resources() = default;

		// Enum that indicates all the resources that can be loaded by the engine
		enum ResourceType {
			RT_IMAGE,
			RT_SHADER,
			RT_MODEL,
			RT_LAST
		};

		struct ResourceData {
			// Path to resource
			std::string filePath;

			// Any type
			void* resource;
		};

		static std::vector<ResourceData*> mResources[RT_LAST];

		static u32 getResourcePosition(ResourceType rt, const char* file);

		static const char* getResourcePath_impl(ResourceType rt, ResourceId id);
		static void* getResourceById_impl(ResourceType rt, ResourceId id);
		static u32 push_resource(ResourceType rt, void* resource, const char* file);

		template<class T, ResourceType I>
		static ResourceId loadResource_impl(const char* file) {
			u32 resourceId = getResourcePosition(I, file);

			if (resourceId == EM_INVALID_RESOURCE) {
				T* rsrc = new T();

				if (rsrc->Load(file)) {
					resourceId = push_resource(I, rsrc, file);

					//EM_INFO("Loaded resource at path [{}]", file);
					EM::Debug::Log("Resources::Load", EM_FMT("Loaded resource at path: {}", file));
				}
				else {
					//EM_ERROR("Couldn't load resource at path [{}]", file);
					EM::Debug::LogError("Resources::Load", EM_FMT("Couldn't load resource at path: {}", file));


					delete rsrc;
				}
			}

			return resourceId;
		}
	public:
		template<class T> static ResourceId Load(const char* file);
		template<class T> static T* GetResourceById(ResourceId id);
		
		template<class T> static const char* GetResourcePath(ResourceId id);
	};
}