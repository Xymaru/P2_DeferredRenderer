#pragma once

#include "Entity.h"

#include <Empathy/Resources.h>
#include <vector>

class SphereEntity : public Entity {
private:
	std::vector<float> m_Vertices;
	std::vector<u32> m_Indices;

	u32 m_VAO;

	EM::Shader* m_ColorShader;

	EM::Uniform* m_ProjectionUniform;
	EM::Uniform* m_ViewUniform;
	EM::Uniform* m_ModelUniform;

	void generateData();
public:
	SphereEntity();
	~SphereEntity();

	void Init() override;
	void Render(Camera* camera, const std::vector<Entity*>& point_lights) override;
};