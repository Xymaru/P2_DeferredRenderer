#pragma once

#include <Empathy/SimpleTypes.h>
#include <Empathy/Resources.h>

class Entity {
public:
	Entity();
	~Entity();

	virtual void Init(){}
	virtual void Render(){}
};