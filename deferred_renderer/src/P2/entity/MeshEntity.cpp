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

	for (int i = 0; i < 16; i++) {
		m_PointLights[i].pos = m_TextureShader->getUniform(EM_FMT("u_PointLights[{}].position", i).c_str());
		m_PointLights[i].color = m_TextureShader->getUniform(EM_FMT("u_PointLights[{}].color", i).c_str());
	}

	m_PointLightCount = m_TextureShader->getUniform("u_PointLightCount");
}

void MeshEntity::Render(Camera* camera, const std::vector<Entity*>& point_lights)
{
	m_TextureShader->Bind();

	// Set lights
	u32 p_lights = (u32)point_lights.size();

	glUniform1ui(m_PointLightCount->location, p_lights);

	PointLightEntity* point_light = nullptr;

	for (u32 i = 0; i < p_lights; i++) {
		point_light = (PointLightEntity*)point_lights[i];

		glUniform3fv(m_PointLights[i].pos->location, 1, glm::value_ptr(point_light->getPosition()));
		glUniform3fv(m_PointLights[i].color->location, 1, glm::value_ptr(point_light->getColor()));
	}

	// Set MVP
	glUniformMatrix4fv(m_ProjectionUniform->location, 1, GL_FALSE, glm::value_ptr(camera->getProjection()));
	glUniformMatrix4fv(m_ViewUniform->location, 1, GL_FALSE, glm::value_ptr(camera->getView()));
	glUniformMatrix4fv(m_ModelUniform->location, 1, GL_FALSE, glm::value_ptr(m_Transform));

	m_Model->Render();

	m_TextureShader->Unbind();
}