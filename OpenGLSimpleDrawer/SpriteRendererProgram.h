#pragma once
#include "Program.h"
#include "Transform.h"

class SpriteRendererProgram : public Program 
{
public:
	GLuint uvAttributeLocation;
	GLuint viewMatrixLocation;
	GLuint modelMatrixLocation;
	GLuint CreateProgram();
	void PreRenderSetup();

	void SetTransform(Transform* transform);
	SpriteRendererProgram();
	~SpriteRendererProgram();
};

