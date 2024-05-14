#include "Entity.h"
#include <glm/gtc/matrix_transform.hpp>

void Entity::updateTransform()
{
	m_Transform = glm::mat4(1.0f);
	m_Transform = glm::translate(m_Transform, m_Position);
	m_Transform = glm::rotate(m_Transform, glm::radians(m_Rotation.x), vec3(1.0f, 0.0f, 0.0f));
	m_Transform = glm::rotate(m_Transform, glm::radians(m_Rotation.y), vec3(0.0f, 1.0f, 0.0f));
	m_Transform = glm::rotate(m_Transform, glm::radians(m_Rotation.z), vec3(0.0f, 0.0f, 1.0f));
	m_Transform = glm::scale(m_Transform, m_Scale);
}

Entity::Entity() : 
	m_Position(0.0f),
	m_Rotation(0.0f),
	m_Scale(1.0f),
	m_Transform(1.0f)
{}

Entity::~Entity()
{

}

void Entity::setPosition(vec3 position)
{
	m_Position = position;

	updateTransform();
}

void Entity::setRotation(vec3 rotation)
{
	m_Rotation = rotation;
	
	updateTransform();
}

void Entity::setScale(vec3 scale)
{
	m_Scale = scale;

	updateTransform();
}