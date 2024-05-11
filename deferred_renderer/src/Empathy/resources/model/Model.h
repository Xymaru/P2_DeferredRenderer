#pragma once

#include <vector>
#include <string>

#include <Empathy/SimpleTypes.h>

struct aiMaterial;
struct aiMesh;
struct aiScene;
struct aiNode;

namespace EM {
	struct VertexBufferAttrib {
		int id;
		int count;
		int offset;
	};

	struct VertexBufferLayout {
		std::vector<VertexBufferAttrib> attribs;
		int stride;
	};

	struct Material {
		std::string name;
		vec3 albedo;
		vec3 emissive;
		f32 smoothness;

		u32 diffuse_texture;
		u32 emissive_texture;
		u32 specular_texture;
		u32 normals_texture;
		u32 bump_texture;
	};

	struct Submesh {
		std::string name;

		VertexBufferLayout layout;
		std::vector<float> vertices;
		std::vector<u32> indices;
		u32 mat_index;
		u32 voffset;
		u32 ioffset;

		u32 vao;
	};

	class Model {
	private:
		u32 m_VBO, m_IBO;

		std::vector<Material*> m_Materials;
		std::vector<Submesh*> m_Submeshes;

		void processMaterial(aiMaterial* mat, const std::string& directory);
		void processMesh(aiMesh* mesh);
		void processNode(const aiScene* scene, const aiNode* node);
	public:
		Model();
		~Model();

		bool Load(const char* file);

		void Render();
	};
}