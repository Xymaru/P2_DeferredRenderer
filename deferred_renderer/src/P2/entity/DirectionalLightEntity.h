#pragma once

#include "Entity.h"

class DirectionalLightEntity : public Entity {
private:
	vec3 m_Direction;
	vec3 m_Color;
public:
	void setDirection(vec3 direction) { m_Direction = direction; }
	vec3 getDirection() const { return m_Direction; }

	void setColor(vec3 color) { m_Color = color; }
	vec3 getColor() const { return m_Color; }
};