#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>

class Camera
{
public:
	enum class CameraType {
		INVALID,
		ORTHOGRAPHIC,
		PERSPECTIVE
	};
private:
	CameraType m_CameraType;

	float m_FOV;

	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraRot;

	glm::vec3 m_CameraFront;
	glm::vec3 m_CameraUp;

	glm::mat4 m_View;
	glm::mat4 m_Projection;

	float m_NearPlaneDist;
	float m_FarPlaneDist;
	float m_AspectRatio;

	int m_TargetWidth;
	int m_TargetHeight;

	void updateView();
public:
	Camera();
	~Camera();

	void SetPerspective(const float fov, const int width, const int height, const float nearPlaneDistance = 0.1f, const float farPlaneDistance = 100.0f);
	void SetOrthographic(const int width, const int height, const float nearPlaneDistance = 0.1f, const float farPlaneDistance = 100.0f);

	void setAspectRatio(const float aspectRatio);
	float getAspectRatio() { return m_AspectRatio; }

	void setResolution(const int width, const int height);

	void setFOV(const float fov);
	float getFOV() { return m_FOV; }

	void setPosition(const glm::vec3 position);
	inline void setRotation(const glm::vec3 rot);

	void setFront(const glm::vec3 front);

	glm::vec3 getPosition() const { return m_CameraPos; }
	glm::vec3 getFront() const { return m_CameraFront; }
	glm::vec3 getUp() const { return m_CameraUp; }
	glm::vec3 getRotation() const { return m_CameraRot; }

	float getFar() const { return m_FarPlaneDist; }
	float getNear() const { return m_NearPlaneDist; }

	void translate(glm::vec3 translation);
	void rotate(glm::vec3 rotation);
	void lookat(const glm::vec3 position);

	CameraType GetCameraType() const { return m_CameraType; }

	glm::mat4 getView() const { return m_View; }
	glm::mat4 getProjection() const { return m_Projection; }
};