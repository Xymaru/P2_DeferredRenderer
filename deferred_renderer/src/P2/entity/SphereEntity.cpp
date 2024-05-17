#include "SphereEntity.h"
#include <glad/glad.h>

#include <Empathy/SimpleTypes.h>
#include <glm/gtc/type_ptr.hpp>

SphereEntity::SphereEntity() :
	m_ColorShader(nullptr),
	m_VAO(0)
{}

SphereEntity::~SphereEntity()
{
}


void SphereEntity::generateData()
{
	const int V = 32;
	const int H = 16;
	const float pi = 3.1416f;

	// Vertex data
	for (int h = 0; h < H; h++) {
		for (int v = 0; v < V + 1; v++) {
			float nh = float(h) / H;
			float nv = float(v) / V - 0.5f;

			float angleh = 2 * pi * nh;
			float anglev = -pi * nv;

			float vx = sinf(angleh) * cosf(anglev);
			float vy = -sinf(anglev);
			float vz = cosf(angleh) * cosf(anglev);

			// Position
			m_Vertices.push_back(vx);
			m_Vertices.push_back(vy);
			m_Vertices.push_back(vz);

			// Normals
			m_Vertices.push_back(vx);
			m_Vertices.push_back(vy);
			m_Vertices.push_back(vz);
		}
	}

	// Index data
	for (unsigned int h = 0; h < H; h++) {
		for (unsigned int v = 0; v < V; v++) {
			const u32 i0 = (h + 0) * (V+1) + v;
			const u32 i1 = ((h + 1) % H) * (V + 1) + v;
			const u32 i2 = ((h + 1) % H) * (V + 1) + v + 1;
			const u32 i3 = (h + 0) * (V + 1) + v;
			const u32 i4 = ((h + 1) % H) * (V + 1) + v + 1;
			const u32 i5 = (h + 0) * (V + 1) + v + 1;

			m_Indices.push_back(i0);
			m_Indices.push_back(i1);
			m_Indices.push_back(i2);
			m_Indices.push_back(i3);
			m_Indices.push_back(i4);
			m_Indices.push_back(i5);
		}
	}

	// Generate buffers
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	u32 vbo, ibo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), m_Vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(u32), m_Indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);
}

void SphereEntity::Init()
{
	generateData();

	ResourceId color_shader_id = EM::Resources::Load<EM::Shader>("assets/shaders/color_shader.glsl");

	m_ColorShader = EM::Resources::GetResourceById<EM::Shader>(color_shader_id);

	m_ProjectionUniform = m_ColorShader->getUniform("u_Projection");
	m_ViewUniform = m_ColorShader->getUniform("u_View");
	m_ModelUniform = m_ColorShader->getUniform("u_Model");
}

void SphereEntity::Render(Camera* camera)
{
	return;
	m_ColorShader->Bind();

	// Set MVP
	glUniformMatrix4fv(m_ProjectionUniform->location, 1, GL_FALSE, glm::value_ptr(camera->getProjection()));
	glUniformMatrix4fv(m_ViewUniform->location, 1, GL_FALSE, glm::value_ptr(camera->getView()));
	glUniformMatrix4fv(m_ModelUniform->location, 1, GL_FALSE, glm::value_ptr(m_Transform));

	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	m_ColorShader->Unbind();
}