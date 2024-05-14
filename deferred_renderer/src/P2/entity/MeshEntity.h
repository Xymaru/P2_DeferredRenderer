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
public:
	MeshEntity();
	~MeshEntity();

	void Init() override;
	void Render(Camera* camera) override;
};