#pragma once

#include <vector>

#include "../entity/Entity.h"
#include "../camera/Camera.h"
#include "../rendering/Framebuffer.h"

class Scene {
protected:
	std::vector<Entity*> m_Entities;
	std::vector<Entity*> m_PointLights;

	Camera* m_SceneCamera;

	Framebuffer m_SceneFrameBuffer;

	EM::Shader* m_ScreenShader;
	u32 m_ScreenVAO;

	glm::mat4 m_OrthoProj;
	glm::mat4 m_View;
	glm::mat4 m_Model;

	EM::Uniform* m_UProj;
	EM::Uniform* m_UView;
	EM::Uniform* m_UModel;

	EM::Uniform* m_Albedo;
	EM::Uniform* m_Normals;
	EM::Uniform* m_Position;

	EM::PointLightUniform m_PointLightsUniforms[16];
	EM::Uniform* m_PointLightCountUniform;

	EM::Uniform* m_CameraPosition;
public:
	Scene();
	~Scene();

	virtual void Init();

	virtual void Update(){}

	virtual void Render();

	u32 getAlbedoTexture() { return m_SceneFrameBuffer.getColorAttachment(0); }
	u32 getNormalsTexture() { return m_SceneFrameBuffer.getColorAttachment(1); }
	u32 getPositionTexture() { return m_SceneFrameBuffer.getColorAttachment(2); }
	u32 getDepthTexture() { return m_SceneFrameBuffer.getColorAttachment(3); }
};