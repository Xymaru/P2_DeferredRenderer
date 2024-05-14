#include "MeshEntity.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "PointLightEntity.h"

MeshEntity::MeshEntity() : 
	m_Model(nullptr),
	m_TextureShader(nullptr),
	m_TextureUniform(nullptr),
	m_ModelUniform(nullptr),
	m_ProjectionUniform(nullptr),
	m_ViewUniform(nullptr)
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

	m_ProjectionUniform = m_TextureShader->getUniform("u_Projection");
	m_ViewUniform = m_TextureShader->getUniform("u_View");
	m_ModelUniform = m_TextureShader->getUniform("u_Model");
}

void MeshEntity::Render(Camera* camera)
{
	m_TextureShader->Bind();

	// Set MVP
	glUniformMatrix4fv(m_ProjectionUniform->location, 1, GL_FALSE, glm::value_ptr(camera->getProjection()));
	glUniformMatrix4fv(m_ViewUniform->location, 1, GL_FALSE, glm::value_ptr(camera->getView()));
	glUniformMatrix4fv(m_ModelUniform->location, 1, GL_FALSE, glm::value_ptr(m_Transform));

	m_Model->Render();

	m_TextureShader->Unbind();
}