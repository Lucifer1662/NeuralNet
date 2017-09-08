#pragma once
#include "Component.h"
#include "SpriteRendererProgram.h"

class API DotRenderer : public Component
{
	static SpriteRendererProgram* drProgram;
public:
	DotRenderer();
	~DotRenderer();
	void Start();
	void Render();
	void Update();
};

