#pragma once

#include "SphereEntity.h"

class PointLightEntity : public SphereEntity {
private:
	vec3 m_Position;
	vec3 m_Color;
public:
	vec3 getColor() const { return m_Color; }
	vec3 getPosition() const { return m_Position; }

	void setPosition(vec3 pos);
	void setColor(vec3 color) { m_Color = color; }
};