#include "Scene.h"
#include <P2/Application.h>

#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include "../entity/PointLightEntity.h"
#include "../entity/DirectionalLightEntity.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	size_t e_size = m_Entities.size();

	for (int i = 0; i < e_size; i++) {
		delete m_Entities[i];
	}

	delete m_SceneCamera;
}

void Scene::Init()
{
	ivec2 resolution = Application::GetInstance()->getTargetResolution();

	m_SceneCamera = new Camera();

	m_SceneCamera->SetPerspective(45.0f, resolution.x, resolution.y);

	m_SceneFrameBuffer.Init(resolution.x, resolution.y);
	m_SceneFrameBuffer.AddColorAttachment(GL_RGBA16F, GL_RGBA, GL_FLOAT); // For normals
	m_SceneFrameBuffer.AddColorAttachment(GL_RGBA16F, GL_RGBA, GL_FLOAT); // For position
	m_SceneFrameBuffer.AddColorAttachment(GL_RGBA16F, GL_RGBA, GL_FLOAT); // For depth

	ResourceId screen_shader_id = EM::Resources::Load<EM::Shader>("assets/shaders/screen_shader.glsl");
	m_ScreenShader = EM::Resources::GetResourceById<EM::Shader>(screen_shader_id);

	m_UProj = m_ScreenShader->getUniform("u_Projection");
	m_UView = m_ScreenShader->getUniform("u_View");
	m_UModel = m_ScreenShader->getUniform("u_Model");

	//----- Create ortho camera ----
	// Init orthographic projection
	m_OrthoProj = glm::ortho(0.0f, (float)resolution.x, (float)resolution.y, 0.0f, 0.1f, 100.0f);
	// Init main camera view
	m_View = glm::mat4(1.0f);
	m_View = glm::translate(m_View, glm::vec3(0.0f, 0.0f, -3.0f));
	// Init model
	m_Model = glm::mat4(1.0f);
	m_Model = glm::translate(m_Model, glm::vec3(resolution.x / 2.0f, resolution.y / 2.0f, 0.0f));
	m_Model = glm::scale(m_Model, glm::vec3((float)resolution.x, (float)resolution.y, 1.0f));

	// Camera uniform
	m_CameraPosition = m_ScreenShader->getUniform("u_CameraPos");

	// Point light uniforms
	m_PointLightCountUniform = m_ScreenShader->getUniform("u_PointLightCount");

	for (int i = 0; i < 16; i++) {
		m_PointLightsUniforms[i].pos = m_ScreenShader->getUniform(EM_FMT("u_PointLights[{}].position", i).c_str());
		m_PointLightsUniforms[i].color = m_ScreenShader->getUniform(EM_FMT("u_PointLights[{}].color", i).c_str());
	}

	// Directional light uniforms
	m_DirectionalLightCountUniform = m_ScreenShader->getUniform("u_DirectionalLightCount");

	for (int i = 0; i < 16; i++) {
		m_DirectionalLightsUniforms[i].pos = m_ScreenShader->getUniform(EM_FMT("u_DirectionalLights[{}].direction", i).c_str());
		m_DirectionalLightsUniforms[i].color = m_ScreenShader->getUniform(EM_FMT("u_DirectionalLights[{}].color", i).c_str());
	}

	// Texture uniforms
	m_Albedo = m_ScreenShader->getUniform("u_Albedo");
	m_Normals = m_ScreenShader->getUniform("u_Normals");
	m_Position = m_ScreenShader->getUniform("u_Positions");

	//----- Generate vao -----
	// Quad vertices
	float vertices[] = {
		// Positions			// Texture coords
		0.5f,  0.5f, 0.0f,		1.0f, 1.0f, // Top right -> 1.0f, 1.0f
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f, // Bottom right -> 1.0f, 0.0f
	   -0.5f, -0.5f, 0.0f,		0.0f, 0.0f, // Bottom left -> 0.0f, 0.0f
	   -0.5f,  0.5f, 0.0f,		0.0f, 1.0f  // Top left -> 0.0f, 1.0f
	};

	// Quad indices
	unsigned int indexes[] = {
		0, 1, 3, 1, 2, 3
	};

	glGenVertexArrays(1, &m_ScreenVAO);
	glBindVertexArray(m_ScreenVAO);

	u32 vbo, ebo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);
}

void Scene::Render()
{
	//----------- Render scene -------------------
	m_SceneFrameBuffer.Bind();

	size_t e_size = m_Entities.size();

	for (int i = 0; i < e_size; i++) {
		m_Entities[i]->Render(m_SceneCamera);
	}

	m_SceneFrameBuffer.Unbind();
	
	//------------ Render to screen --------------
	glDepthMask(GL_FALSE);

	m_ScreenShader->Bind();
	
	if (m_CameraPosition) {
		glUniform3fv(m_CameraPosition->location, 1, glm::value_ptr(m_SceneCamera->getPosition()));
	}

	if(m_Albedo) glUniform1i(m_Albedo->location, 0);
	if(m_Normals) glUniform1i(m_Normals->location, 1);
	if(m_Position) glUniform1i(m_Position->location, 2);

	glUniformMatrix4fv(m_UProj->location, 1, GL_FALSE, glm::value_ptr(m_OrthoProj));
	glUniformMatrix4fv(m_UView->location, 1, GL_FALSE, glm::value_ptr(m_View));
	glUniformMatrix4fv(m_UModel->location, 1, GL_FALSE, glm::value_ptr(m_Model));

	// Bind point lights
	u32 p_light_count = m_PointLights.size();

	if(m_PointLightCountUniform) glUniform1ui(m_PointLightCountUniform->location, p_light_count);

	for (u32 i = 0; i < p_light_count; i++) {
		EM::LightUniform& point_uniform = m_PointLightsUniforms[i];
		PointLightEntity* point_light = (PointLightEntity*)m_PointLights[i];

		if(point_uniform.pos) glUniform3fv(point_uniform.pos->location, 1, glm::value_ptr(point_light->getPosition()));
		if(point_uniform.color) glUniform3fv(point_uniform.color->location, 1, glm::value_ptr(point_light->getColor()));
	}

	// Bind directional lights
	u32 d_light_count = m_DirectionalLights.size();

	if(m_DirectionalLightCountUniform) glUniform1ui(m_DirectionalLightCountUniform->location, d_light_count);

	for (u32 i = 0; i < d_light_count; i++) {
		EM::LightUniform& dir_uniform = m_DirectionalLightsUniforms[i];
		DirectionalLightEntity* dir_light = (DirectionalLightEntity*)m_DirectionalLights[i];

		if(dir_uniform.pos) glUniform3fv(dir_uniform.pos->location, 1, glm::value_ptr(dir_light->getDirection()));
		if(dir_uniform.color) glUniform3fv(dir_uniform.color->location, 1, glm::value_ptr(dir_light->getColor()));
	}

	// Bind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_SceneFrameBuffer.getColorAttachment(0));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_SceneFrameBuffer.getColorAttachment(1));

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_SceneFrameBuffer.getColorAttachment(2));

	glBindVertexArray(m_ScreenVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	m_ScreenShader->Unbind();

	glDepthMask(GL_TRUE);

	glActiveTexture(GL_TEXTURE0);
}