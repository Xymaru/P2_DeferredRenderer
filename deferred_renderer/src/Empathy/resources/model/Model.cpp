#include "Model.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Empathy/Debug.h>
#include <Empathy/filesystem/FileSystem.h>

#include <Empathy/Resources.h>

#include <glad/glad.h>

namespace EM {
	void Model::processMaterial(aiMaterial* material, const std::string& directory)
	{
		aiString name;
		aiColor3D diffuse;
		aiColor3D emissive;
		aiColor3D specular;
		ai_real shininess;

		material->Get(AI_MATKEY_NAME, name);
		material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
		material->Get(AI_MATKEY_COLOR_EMISSIVE, emissive);
		material->Get(AI_MATKEY_COLOR_SPECULAR, specular);
		material->Get(AI_MATKEY_SHININESS, shininess);

		Material* mat = new Material();
		mat->name = name.C_Str();
		mat->albedo = vec3(diffuse.r, diffuse.g, diffuse.b);
		mat->emissive = vec3(emissive.r, emissive.g, emissive.b);
		mat->smoothness = shininess / 256.0f;

		mat->diffuse_texture = EM_INVALID_RESOURCE;
		mat->emissive_texture = EM_INVALID_RESOURCE;
		mat->specular_texture = EM_INVALID_RESOURCE;
		mat->normals_texture = EM_INVALID_RESOURCE;
		mat->bump_texture = EM_INVALID_RESOURCE;

		aiString aiFilename;
		std::string filepath;

		//--------- DIFFUSE TEXTURE
		if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			material->GetTexture(aiTextureType_DIFFUSE, 0, &aiFilename);

			filepath = directory + "/" + aiFilename.C_Str();

			mat->diffuse_texture = Resources::Load<Image>(filepath.c_str());
		}

		//--------- EMMISSIVE TEXTURE
		if (material->GetTextureCount(aiTextureType_EMISSIVE) > 0) {
			material->GetTexture(aiTextureType_EMISSIVE, 0, &aiFilename);

			filepath = directory + "/" + aiFilename.C_Str();

			mat->emissive_texture = Resources::Load<Image>(filepath.c_str());
		}

		//--------- SPECULAR TEXTURE
		if (material->GetTextureCount(aiTextureType_SPECULAR) > 0) {
			material->GetTexture(aiTextureType_SPECULAR, 0, &aiFilename);

			filepath = directory + "/" + aiFilename.C_Str();

			mat->specular_texture = Resources::Load<Image>(filepath.c_str());
		}

		//--------- NORMALS TEXTURE
		if (material->GetTextureCount(aiTextureType_NORMALS) > 0) {
			material->GetTexture(aiTextureType_NORMALS, 0, &aiFilename);

			filepath = directory + "/" + aiFilename.C_Str();

			mat->normals_texture = Resources::Load<Image>(filepath.c_str());
		}

		//--------- BUMP TEXTURE
		if (material->GetTextureCount(aiTextureType_HEIGHT) > 0) {
			material->GetTexture(aiTextureType_HEIGHT, 0, &aiFilename);

			filepath = directory + "/" + aiFilename.C_Str();

			mat->bump_texture = Resources::Load<Image>(filepath.c_str());
		}

		m_Materials.push_back(mat);
	}

	void Model::processMesh(aiMesh* mesh)
	{
		std::vector<float> vertices;
		std::vector<u32> indices;

		bool hasTexCoords = false;
		bool hasTangentSpace = false;

		for (u32 i = 0; i < mesh->mNumVertices; i++) {
			vertices.push_back(mesh->mVertices[i].x);
			vertices.push_back(mesh->mVertices[i].y);
			vertices.push_back(mesh->mVertices[i].z);

			vertices.push_back(mesh->mNormals[i].x);
			vertices.push_back(mesh->mNormals[i].y);
			vertices.push_back(mesh->mNormals[i].z);

			// If mesh has uvs
			if (mesh->mTextureCoords[0]) {
				hasTexCoords = true;
				vertices.push_back(mesh->mTextureCoords[0][i].x);
				vertices.push_back(mesh->mTextureCoords[0][i].y);
			}

			if (mesh->mTangents != nullptr && mesh->mBitangents) {
				hasTangentSpace = true;

				vertices.push_back(mesh->mTangents[i].x);
				vertices.push_back(mesh->mTangents[i].y);
				vertices.push_back(mesh->mTangents[i].z);

				vertices.push_back(-mesh->mBitangents[i].x);
				vertices.push_back(-mesh->mBitangents[i].y);
				vertices.push_back(-mesh->mBitangents[i].z);
			}
		}

		aiFace face;
		for (u32 i = 0; i < mesh->mNumFaces; i++) {
			face = mesh->mFaces[i];
			for (u32 j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		// Calculate vertex formatting
		VertexBufferLayout vblayout = {};
		vblayout.attribs.push_back(VertexBufferAttrib{ 0, 3, 0 }); // position
		vblayout.attribs.push_back(VertexBufferAttrib{ 1, 3, 3 * sizeof(float) }); // normals
		vblayout.stride = 6 * sizeof(float);

		if (hasTexCoords) {
			vblayout.attribs.push_back(VertexBufferAttrib{ 2, 2, vblayout.stride }); // texcoords
			vblayout.stride += 2 * sizeof(float);
		}

		if (hasTangentSpace) {
			vblayout.attribs.push_back(VertexBufferAttrib{ 3, 3, vblayout.stride }); // tangets
			vblayout.stride += 3 * sizeof(float);

			vblayout.attribs.push_back(VertexBufferAttrib{ 4, 3, vblayout.stride }); // bitangents
			vblayout.stride += 3 * sizeof(float);
		}

		Submesh* submesh = new Submesh();
		submesh->name = mesh->mName.C_Str();
		submesh->layout = vblayout;
		submesh->vertices.swap(vertices);
		submesh->indices.swap(indices);
		submesh->mat_index = mesh->mMaterialIndex;

		m_Submeshes.push_back(submesh);
	}

	void Model::processNode(const aiScene* scene, const aiNode* node)
	{
		// Process all meshes in node
		for (u32 i = 0; i < node->mNumMeshes; i++) {
			processMesh(scene->mMeshes[node->mMeshes[i]]);
		}

		// Process all child nodes
		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			processNode(scene, node->mChildren[i]);
		}
	}

	Model::Model()
	{

	}

	Model::~Model()
	{
		size_t m_size = m_Materials.size();

		for (size_t i = 0; i < m_size; i++) {
			delete m_Materials[i];
		}

		size_t sm_size = m_Submeshes.size();

		for (size_t i = 0; i < sm_size; i++) {
			delete m_Submeshes[i];
		}
	}

	bool Model::Load(const char* file)
	{
		const aiScene* scene = aiImportFile(file,
			aiProcess_Triangulate |
			aiProcess_GenSmoothNormals |
			aiProcess_CalcTangentSpace |
			aiProcess_JoinIdenticalVertices |
			aiProcess_PreTransformVertices |
			aiProcess_ImproveCacheLocality |
			aiProcess_OptimizeMeshes |
			aiProcess_SortByPType
		);

		if (!scene) {
			EM_ERROR("Error loading mesh at path {}, error: {}", file, aiGetErrorString());
			return false;
		}

		std::string directory = EM::FileSystem::GetParentDirectory(file);

		// Process materials
		for (u32 i = 0; i < scene->mNumMaterials; i++) {
			processMaterial(scene->mMaterials[i], directory);
		}

		// Process meshes
		processNode(scene, scene->mRootNode);

		aiReleaseImport(scene);

		// Build opengl buffers
		u32 vbsize = 0;
		u32 ibsize = 0;

		for (u32 i = 0; i < m_Submeshes.size(); i++) {
			vbsize += m_Submeshes[i]->vertices.size() * sizeof(float);
			ibsize += m_Submeshes[i]->indices.size() * sizeof(u32);
		}

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vbsize, NULL, GL_STATIC_DRAW);

		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibsize, NULL, GL_STATIC_DRAW);

		u32 ioffset = 0;
		u32 voffset = 0;

		for (u32 i = 0; i < m_Submeshes.size(); i++) {
			Submesh* submesh = m_Submeshes[i];

			const void* vdata = submesh->vertices.data();
			const u32 vsize = submesh->vertices.size() * sizeof(float);

			glBufferSubData(GL_ARRAY_BUFFER, voffset, vsize, vdata);

			submesh->voffset = voffset;
			voffset += vsize;

			const void* idata = submesh->indices.data();
			const u32 isize = submesh->indices.size() * sizeof(u32);

			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, ioffset, isize, idata);

			submesh->ioffset = ioffset;
			ioffset += isize;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Now, generate vaos for each submesh
		for (u32 i = 0; i < m_Submeshes.size(); i++) {
			Submesh* submesh = m_Submeshes[i];

			glGenVertexArrays(1, &submesh->vao);
			glBindVertexArray(submesh->vao);

			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

			VertexBufferLayout& layout = submesh->layout;

			for (u32 j = 0; j < submesh->layout.attribs.size(); j++) {
				VertexBufferAttrib& attrib = submesh->layout.attribs[j];
				const u32 offset = attrib.offset + submesh->voffset;

				glEnableVertexAttribArray(attrib.id);
				glVertexAttribPointer(attrib.id, attrib.count, GL_FLOAT, GL_FALSE, layout.stride, (void*)offset);
			}

			glBindVertexArray(0);
		}

		return true;
	}

	void Model::Render()
	{
		for (u32 i = 0; i < m_Submeshes.size(); i++) {
			Submesh* submesh = m_Submeshes[i];
			Material* mat = m_Materials[submesh->mat_index];

			glBindVertexArray(submesh->vao);

			Image* img = Resources::GetResourceById<Image>(mat->diffuse_texture);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, img->getImageId());

			glDrawElements(GL_TRIANGLES, submesh->indices.size(), GL_UNSIGNED_INT, (void*)submesh->ioffset);
		}

		glBindVertexArray(0);
	}
}