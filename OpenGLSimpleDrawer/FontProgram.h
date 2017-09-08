#pragma once
#include "Program.h"
#include "glm.hpp"

using glm::mat4;
class FontProgram : public Program
{
	GLuint transformMatLocation;
	GLuint viewMatLocation;

	static mat4 screenMat;
public:
	FontProgram();
	~FontProgram();
	GLuint CreateProgram();
	void PreRenderSetup();
	void SetTransform(glm::mat4, bool isOnScren = true);

	
};

