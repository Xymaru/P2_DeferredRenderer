#pragma once

#include "Entity.h"
#include <Empathy/Resources.h>

class MeshEntity : public Entity {
private:
	EM::Model* m_Model;

	EM::Shader* m_TextureShader;

	EM::Uniform* m_TextureUniform;

	EM::Uniform* m_ProjectionUniform;
	EM::Uniform* m_ViewUniform;
	EM::Uniform* m_ModelUniform;

	EM::PointLightUniform m_PointLights[16];
	EM::Uniform* m_PointLightCount;
public:
	MeshEntity();
	~MeshEntity();

	void Init() override;
	void Render(Camera* camera, const std::vector<Entity*>& point_lights) override;
};