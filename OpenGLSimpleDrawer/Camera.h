#pragma once
#include <glm.hpp>
#include "Component.h"


using glm::vec3;
using glm::mat4;

class API Camera: public Component
{
	void Start();

public:
	vec3* position;
	vec3 up = vec3(0, 1, 0);
	mat4 perspectiveMatrix;
	vec3 direction = vec3(0,0,1);
	float size = 1;
	Camera();
	~Camera();
	void ResetRatio(float width, float height);
	
	mat4 getViewMatrix();
};

