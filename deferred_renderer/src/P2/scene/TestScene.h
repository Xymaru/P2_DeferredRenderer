#pragma once
#include "Scene.h"

class TestScene : public Scene {
private:
	float m_CameraSpeed;

	float m_CamSensitivity;

	float m_CameraPitch;
	float m_CameraYaw;
public:
	TestScene();
	~TestScene();

	void Init() override;
	void Update() override;
};