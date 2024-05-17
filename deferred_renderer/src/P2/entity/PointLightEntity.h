#pragma once

#include "SphereEntity.h"

class PointLightEntity : public SphereEntity {
private:
	vec3 m_Color;
public:
	vec3 getColor() const { return m_Color; }

	void setColor(vec3 color) { m_Color = color; }
};