#pragma once

#include <Empathy/SimpleTypes.h>
#include <Empathy/Resources.h>

#include <P2/camera/Camera.h>
#include <vector>

class Entity {
protected:
	glm::mat4 m_Transform;

	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;
	
	void updateTransform();
public:
	Entity();
	~Entity();

	void setPosition(vec3 position);
	void setRotation(vec3 rotation);
	void setScale(vec3 scale);

	virtual void Init(){}
	virtual void Render(Camera* camera, const std::vector<Entity*>& point_lights){}
};