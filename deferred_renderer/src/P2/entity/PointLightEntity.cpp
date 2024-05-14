#include "PointLightEntity.h"

void PointLightEntity::setPosition(vec3 pos)
{
	m_Position = pos;

	m_Transform = glm::mat4(1.0f);
	m_Transform = glm::translate(m_Transform, m_Position);
}