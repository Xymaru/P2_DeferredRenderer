#include "TestScene.h"

#include "../entity/MeshEntity.h"
#include "../entity/SphereEntity.h"
#include "../entity/PointLightEntity.h"

#include <P2/Input.h>

TestScene::TestScene() :
	m_CameraSpeed(0.01f),
	m_CameraPitch(0.0f),
	m_CameraYaw(-90.0f),
	m_CamSensitivity(0.5f)
{}

TestScene::~TestScene()
{
	size_t e_size = m_Entities.size();

	for (size_t i = 0; i < e_size; i++) {
		delete m_Entities[i];
	}
}

void TestScene::Init()
{
	Scene::Init();

	m_SceneCamera->setPosition(vec3(0.0f, 0.0f, 10.0f));

	vec3 positions[9] = {
		glm::vec3(0.0f),
		glm::vec3(8.0f, 0.0f, 1.0f),
		glm::vec3(-3.0f, 0.0f, 3.0f),
		glm::vec3(3.0f, 0.0f, -15.0f),
		glm::vec3(10.0f, 0.0f, 10.0f),
		glm::vec3(-15.0f, 0.0f, 15.0f),
		glm::vec3(0.0f, 0.0f, 15.0f),
		glm::vec3(-20.0f, 0.0f, 3.0f),
		glm::vec3(-15.0f, 0.0f, -15.0f)
	};

	//------- Patricks -------
	for (int i = 0; i < 9; i++) {
		MeshEntity* patrick = new MeshEntity();
		patrick->Init();
		patrick->setPosition(positions[i]);
		patrick->setRotation(vec3(0.0f, i*45, 0.0f));
		m_Entities.push_back(patrick);
	}

	vec3 light_positions[5] = {
		vec3(2.0f, -2.0f, 2.0f),
		vec3(-2.0f, 5.0f, 7.0f),
		vec3(-6.0f, 8.0f, -5.0f),
		vec3(-15.0f, 0.0f, 2.0f),
		vec3(10.0f, 0.0f, -8.0f),
	};

	//------- Lights -------
	for (int i = 0; i < 5; i++) {
		PointLightEntity* point = new PointLightEntity();
		point->Init();
		point->setPosition(light_positions[i]);
		point->setColor(vec3(1.0f));
		m_PointLights.push_back(point);
		m_Entities.push_back(point);
	}

}

void TestScene::Update()
{
	Scene::Update();

	static bool cam_control = false;

	if (Input::IsMouseDown(1)) {
		Input::MouseHideAndLock();

		cam_control = true;
	}
	else if (Input::IsMouseUp(1)) {
		Input::MouseShowAndUnlock();

		cam_control = false;
	}

	if (cam_control) {
		// Camera position
		vec3 cam_pos = m_SceneCamera->getPosition();

		if (Input::IsKeyPressed(KeyCode::W)) {
			cam_pos += m_SceneCamera->getFront() * m_CameraSpeed;
		}

		if (Input::IsKeyPressed(KeyCode::S)) {
			cam_pos -= m_SceneCamera->getFront() * m_CameraSpeed;
		}

		if (Input::IsKeyPressed(KeyCode::A)) {
			cam_pos -= glm::normalize(glm::cross(m_SceneCamera->getFront(), m_SceneCamera->getUp())) * m_CameraSpeed;
		}

		if (Input::IsKeyPressed(KeyCode::D)) {
			cam_pos += glm::normalize(glm::cross(m_SceneCamera->getFront(), m_SceneCamera->getUp())) * m_CameraSpeed;
		}

		if (Input::IsKeyPressed(KeyCode::SPACE)) {
			cam_pos += m_SceneCamera->getUp() * m_CameraSpeed;
		}

		if (Input::IsKeyPressed(KeyCode::LEFT_SHIFT)) {
			cam_pos -= m_SceneCamera->getUp() * m_CameraSpeed;
		}

		m_SceneCamera->setPosition(cam_pos);

		// Rotation
		ivec2 direction = Input::GetRelativeMousePositionNormalized();

		if (direction.x != 0 || direction.y != 0) {
			float xoffset = direction.x * m_CamSensitivity;
			float yoffset = -direction.y * m_CamSensitivity;

			m_CameraYaw += xoffset;
			m_CameraPitch += yoffset;

			if (m_CameraPitch > 89.0f) m_CameraPitch = 89.0f;
			if (m_CameraPitch < -89.0f) m_CameraPitch = -89.0f;

			m_SceneCamera->setRotation(vec3(m_CameraYaw, m_CameraPitch, 0.0f));
		}
	}
}