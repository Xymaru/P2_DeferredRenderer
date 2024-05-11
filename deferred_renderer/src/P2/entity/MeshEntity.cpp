#include "MeshEntity.h"

MeshEntity::MeshEntity() : 
	m_Model(nullptr),
	m_TextureShader(nullptr),
	m_TextureUniform(nullptr)
{
	
}

MeshEntity::~MeshEntity()
{
}

void MeshEntity::Init()
{
	ResourceId model_id = EM::Resources::Load<EM::Model>("assets/patrick/patrick.obj");
	ResourceId texture_shader_id = EM::Resources::Load<EM::Shader>("assets/shaders/texture_shader.glsl");

	m_Model = EM::Resources::GetResourceById<EM::Model>(model_id);

	m_TextureShader = EM::Resources::GetResourceById<EM::Shader>(texture_shader_id);
	m_TextureUniform = m_TextureShader->getUniform("u_Texture");
}

void MeshEntity::Render()
{
	m_TextureShader->Bind();

	m_Model->Render();

	m_TextureShader->Unbind();
}