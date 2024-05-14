#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
	// Initialize camera transform
	m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_CameraRot = glm::vec3(0.0f, 0.0f, 0.0f);

	// Initialize camera distance planes
	m_NearPlaneDist = 0.1f;
	m_FarPlaneDist = 1000.0f;

	// Initialize camera view
	updateView();

	// Start camera as INVALID
	m_CameraType = CameraType::INVALID;
}


Camera::~Camera()
{

}

void Camera::updateView()
{
	m_View = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
}

void Camera::setRotation(const glm::vec3 rot)
{
	m_CameraRot = rot;

	glm::vec3 direction;
	direction.x = cos(glm::radians(rot.x)) * cos(glm::radians(rot.y));
	direction.y = sin(glm::radians(rot.y));
	direction.z = sin(glm::radians(rot.x)) * cos(glm::radians(rot.y));

	glm::vec3 front = glm::normalize(direction);
	setFront({ front.x, front.y, front.z });
}

void Camera::setAspectRatio(const float aspectRatio)
{
	m_AspectRatio = aspectRatio;

	if(m_CameraType == CameraType::PERSPECTIVE)
		m_Projection = glm::perspective(glm::radians(m_FOV), aspectRatio, m_NearPlaneDist, m_FarPlaneDist);
}

void Camera::setResolution(const int width, const int height)
{
	m_AspectRatio = width / (float)height;

	if (m_CameraType == CameraType::PERSPECTIVE)
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlaneDist, m_FarPlaneDist);
	else if(m_CameraType == CameraType::ORTHOGRAPHIC)
		m_Projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
}

void Camera::setFOV(const float fov)
{
	m_FOV = fov;

	if (m_CameraType == CameraType::PERSPECTIVE)
		m_Projection = glm::perspective(glm::radians(fov), m_AspectRatio, m_NearPlaneDist, m_FarPlaneDist);
}

void Camera::setPosition(const glm::vec3 position)
{
	m_CameraPos = position;

	updateView();
}

void Camera::setFront(const glm::vec3 front)
{
	m_CameraFront = front;

	updateView();
}

void Camera::translate(glm::vec3 translation)
{
	m_CameraPos += translation;

	updateView();
}

void Camera::rotate(glm::vec3 rotation)
{
	m_CameraRot += rotation;

	setRotation(m_CameraRot);
}

void Camera::lookat(const glm::vec3 position)
{
	m_CameraFront = position - m_CameraPos;

	m_View = glm::lookAt(m_CameraPos, position, m_CameraUp);
}

void Camera::SetPerspective(const float fov, const int width, const int height, const float nearPlaneDistance, const float farPlaneDistance)
{
	m_CameraType = CameraType::PERSPECTIVE;

	m_TargetWidth = width;
	m_TargetHeight = height;
	m_AspectRatio = width / (float)height;
	
	m_FOV = fov;
	m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, nearPlaneDistance, farPlaneDistance);

	m_NearPlaneDist = nearPlaneDistance;
	m_FarPlaneDist = farPlaneDistance;
}

void Camera::SetOrthographic(const int width, const int height, const float nearPlaneDistance, const float farPlaneDistance)
{
	m_CameraType = CameraType::ORTHOGRAPHIC;

	m_TargetWidth = width;
	m_TargetHeight = height;

	m_Projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, nearPlaneDistance, farPlaneDistance);

	m_AspectRatio = width / (float)height;
	m_NearPlaneDist = nearPlaneDistance;
	m_FarPlaneDist = farPlaneDistance;
}