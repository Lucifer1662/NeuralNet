#pragma once
#include <glm.hpp>
using glm::vec2;

class Input
{
public:
	static bool keyDown[348];

	static vec2 mousePosition;
	static vec2 mouseMovement;

	static bool KeyDown(int key) {
		return keyDown[key];
	}

};

